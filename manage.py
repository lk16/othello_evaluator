#!/usr/bin/env python

import aiohttp
import asyncio
import click
import os

from aiofile import AIOFile
from dataclasses import dataclass
from typing import List


loop = asyncio.get_event_loop()


@dataclass
class pgn:
    black_elo: int
    white_elo: int
    black: str
    white: str
    variant: str
    moves: List[str]


@click.group()
def cli():
    pass


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
                    async with AIOFile(f"pgn/rv{i}.txt", 'w+') as file:
                        await file.write(await response.text())

    loop.run_until_complete(run(start, end))


def parse_pgn(filename):

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
            moves.append(word)

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

        if game.white_elo >= 1500 and game.black_elo >= 1500:
            good += 1

        total += 1

        if total % 100 == 0:
            print('good = {:6} | total = {:6} | {:6} %'.format(
                good, total, 100*good/total))


if __name__ == '__main__':
    cli()
