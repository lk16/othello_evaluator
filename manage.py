#!/usr/bin/env python
import aiohttp
import asyncio
import click
import os
import subprocess

from aiofile import AIOFile
from evaluator.board import Board, BLACK, MOVE_PASS, WHITE
from evaluator.pgn import Pgn
from evaluator.bot import Bot


loop = asyncio.get_event_loop()


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
                    async with AIOFile(f'pgn/rv{i}.txt', 'w+') as file:
                        await file.write(await response.text())

    loop.run_until_complete(run(start, end))


def parse_pgn(filename) -> Pgn:

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
            if word[0] not in 'abcdefgh-':
                continue
            moves.append(Board.field_to_index(word))

    return Pgn(
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


def evaluate(board: Board) -> int:
    process = subprocess.run(
        ["./heuristics/heuristics", hex(board.me), hex(board.opp)],
        capture_output=True,
    )
    if process.returncode != 0:
        raise Exception("Heuristics process failed: {}".format(process.stdout.decode('utf-8')))

    result_line = process.stdout.decode('utf-8').split('\n')[-2]
    if not result_line.startswith('result = '):
        raise ValueError("expected result line")

    return int(result_line.split(' ')[-1].strip())


@cli.command()
@click.argument('filename', type=str)
def parse_pgn_file(filename):
    game = parse_pgn(filename)
    board = Board()
    board.show()

    for move in game.moves:
        if board.get_moves() == 0:
            board = board.do_move(move)
            continue

        children = board.get_children()
        best_heur = -64000
        best_child = None
        for child in children:
            heur = -evaluate(child)
            print('child heuristic: {}'.format(heur))
            if heur > best_heur:
                best_heur = heur
                best_child = child

        chosen_child = board.do_move(move)

        if chosen_child == best_child:
            print('correct move')
            best_child.show()

        else:
            print('wrong move')
            chosen_child.show()
            print('better move:')
            best_child.show()

        board = chosen_child

    print('White {} - {} Black'.format(
        board.count(WHITE),
        board.count(BLACK),
    ))


if __name__ == '__main__':
    cli()
