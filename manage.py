#!/usr/bin/env python

from __future__ import annotations

import aiohttp
import asyncio
import click
import os
import random

from aiofile import AIOFile
from dataclasses import dataclass
from typing import List


loop = asyncio.get_event_loop()

BLACK = 0
WHITE = 1


@dataclass
class pgn:
    black_elo: int
    white_elo: int
    black: str
    white: str
    variant: str
    moves: List[int]


@dataclass
class board:
    me: int
    opp: int
    turn: int

    def __init__(self):
        self.me = 1 << 28 | 1 << 35
        self.opp = 1 << 27 | 1 << 36
        self.turn = BLACK

    def black(self) -> int:
        if self.turn == BLACK:
            return self.me
        return self.opp

    def white(self) -> int:
        if self.turn == WHITE:
            return self.me
        return self.opp

    def show(self) -> str:
        moves = self.get_moves()
        print('+-a-b-c-d-e-f-g-h-+')
        for y in range(8):
            print('{} '.format(y+1), end='')
            for x in range(8):
                mask = 1 << ((y*8) + x)
                if self.black() & mask:
                    print('○ ', end='')
                elif self.white() & mask:
                    print('● ', end='')
                elif moves & mask:
                    print('· ', end='')
                else:
                    print('  ', end='')
            print('|')
        print('+-----------------+')

    def do_move(self, move: int) -> board:
        if (self.me | self.opp) & (1 << move):
            raise ValueError('invalid move: {}'.format(move))

        flipped = 0
        for dx, dy in [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]:
            s = 1
            while True:
                curx = int(move % 8) + (dx * s)
                cury = int(move / 8) + (dy * s)
                if curx < 0 or curx >= 8 or cury < 0 or cury >= 8:
                    break

                cur = 8*cury + curx
                if self.opp & (1 << cur):
                    s += 1
                else:
                    if (self.me & (1 << cur)) and (s >= 2):
                        for p in range(1, s):
                            f = move + (p*(8*dy+dx))
                            flipped |= (1 << f)
                    break

        child = board()
        child.opp = self.me | flipped | (1 << move)
        child.me = self.opp & ~child.opp
        child.turn = 1 - self.turn
        return child

    def get_moves(self) -> int:
        mask = self.opp & 0x7E7E7E7E7E7E7E7E

        flipL = mask & (self.me << 1)
        flipL |= mask & (flipL << 1)
        maskL = mask & (mask << 1)
        flipL |= maskL & (flipL << (2 * 1))
        flipL |= maskL & (flipL << (2 * 1))
        flipR = mask & (self.me >> 1)
        flipR |= mask & (flipR >> 1)
        maskR = mask & (mask >> 1)
        flipR |= maskR & (flipR >> (2 * 1))
        flipR |= maskR & (flipR >> (2 * 1))
        movesSet = (flipL << 1) | (flipR >> 1)

        flipL = mask & (self.me << 7)
        flipL |= mask & (flipL << 7)
        maskL = mask & (mask << 7)
        flipL |= maskL & (flipL << (2 * 7))
        flipL |= maskL & (flipL << (2 * 7))
        flipR = mask & (self.me >> 7)
        flipR |= mask & (flipR >> 7)
        maskR = mask & (mask >> 7)
        flipR |= maskR & (flipR >> (2 * 7))
        flipR |= maskR & (flipR >> (2 * 7))
        movesSet |= (flipL << 7) | (flipR >> 7)

        flipL = mask & (self.me << 9)
        flipL |= mask & (flipL << 9)
        maskL = mask & (mask << 9)
        flipL |= maskL & (flipL << (2 * 9))
        flipL |= maskL & (flipL << (2 * 9))
        flipR = mask & (self.me >> 9)
        flipR |= mask & (flipR >> 9)
        maskR = mask & (mask >> 9)
        flipR |= maskR & (flipR >> (2 * 9))
        flipR |= maskR & (flipR >> (2 * 9))
        movesSet |= (flipL << 9) | (flipR >> 9)

        flipL = self.opp & (self.me << 8)
        flipL |= self.opp & (flipL << 8)
        maskL = self.opp & (self.opp << 8)
        flipL |= maskL & (flipL << (2 * 8))
        flipL |= maskL & (flipL << (2 * 8))
        flipR = self.opp & (self.me >> 8)
        flipR |= self.opp & (flipR >> 8)
        maskR = self.opp & (self.opp >> 8)
        flipR |= maskR & (flipR >> (2 * 8))
        flipR |= maskR & (flipR >> (2 * 8))
        movesSet |= (flipL << 8) | (flipR >> 8)

        return movesSet & ~(self.me | self.opp)

    def get_children(self) -> List[board]:
        children = []
        moves = self.get_moves()
        for i in range(64):
            if moves & (1 << i):
                children.append(self.do_move(i))
        return children


class bot:

    @classmethod
    def heuristic(b: board) -> int:
        raise NotImplementedError

    @classmethod
    def search(b: board, depth: int) -> int:
        raise NotImplementedError

    @classmethod
    def _alpha_beta(b: board, alpha: int, beta: int) -> int:
        raise NotImplementedError


@click.group()
def cli():
    pass


@cli.command()
def show_board():
    b = board()
    while True:
        b.show()
        b = random.choice(b.get_children())


@cli.command()
@click.argument('start', type=int)
@click.argument('end', type=int)
def get_pgn(start, end):

    async def run(start, end):
        async with aiohttp.ClientSession() as session:
            for i in range(start, end):

                if i % 100 == 0:
                    print(f'Downloading game {i}')

                url = f'https://www.playok.com/p/?g=rv{i}.txt'

                async with session.get(url) as response:
                    response.raise_for_status()
                    async with AIOFile(f'pgn/rv{i}.txt', 'w+') as file:
                        await file.write(await response.text())

    loop.run_until_complete(run(start, end))


def field_to_index(field: str) -> int:
    if len(field) != 2:
        raise ValueError("field too long")
    x = ord(field[0]) - ord('a')
    y = ord(field[1]) - ord('1')
    if x not in range(8) or y not in range(8):
        raise ValueError("invalid field: {}".format(field))
    return 8*y + x


def parse_pgn(filename) -> pgn:

    contents = open(filename, 'r').read()

    info = {}
    moves = []

    for line in contents.split('\n'):
        if line.startswith('['):
            space_pos = line.find(' ')
            key = line[1:space_pos]
            value = line[space_pos+2:-2]
            info[key] = value
            continue

        if line.strip() == '':
            continue

        for word in line.split(' '):
            if word[0] not in 'abcdefgh':
                continue
            moves.append(field_to_index(word))

    return pgn(
        black=info['Black'],
        white=info['White'],
        black_elo=int(info['BlackElo']),
        white_elo=int(info['WhiteElo']),
        variant=info.get('Variant', 'normal'),
        moves=moves,
    )


@cli.command()
@click.argument('path', type=str)
def parse_pgn_folder(path):

    good = 0
    total = 0

    for filename in os.listdir(path):
        game = parse_pgn(os.path.join(path, filename))

        if game.white_elo >= 1500 and game.black_elo >= 1500 and game.variant == 'normal':
            good += 1

        total += 1

        if total % 100 == 0:
            print('good = {:6} | total = {:6} | {:6} %'.format(
                good, total, 100*good/total))


@cli.command()
@click.argument('filename', type=str)
def parse_pgn_file(filename):
    game = parse_pgn(filename)
    b = board()
    for move in game.moves:
        b.show()
        b = b.do_move(move)
    b.show()


if __name__ == '__main__':
    cli()
