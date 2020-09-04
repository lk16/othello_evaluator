
from __future__ import annotations

from dataclasses import dataclass
from typing import List

BLACK = 0
WHITE = 1

MOVE_PASS = -1


@dataclass
class Board:
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

    @classmethod
    def field_to_index(cls, field: str) -> int:
        if len(field) != 2:
            raise ValueError("field too long")
        if field == '--':
            return MOVE_PASS
        x = ord(field[0]) - ord('a')
        y = ord(field[1]) - ord('1')
        if x not in range(8) or y not in range(8):
            raise ValueError("invalid field: {}".format(field))
        return 8*y + x

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

    def do_move(self, move: int) -> Board:
        if move == MOVE_PASS:
            child = Board()
            child.opp = self.me
            child.me = self.opp
            child.turn = 1 - self.turn
            return child

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

        child = Board()
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

        return movesSet & ~(self.me | self.opp) & 0xFFFFFFFFFFFFFFFF

    def get_children(self) -> List[Board]:
        children = []
        moves = self.get_moves()
        for i in range(64):
            if moves & (1 << i):
                children.append(self.do_move(i))
        return children

    def count(self, color: int) -> int:
        if color == WHITE:
            return bin(self.white()).count('1')
        elif color == BLACK:
            return bin(self.black()).count('1')
        raise ValueError('Invalid color {}'.format(color))

    def exact_score(self) -> int:
        me = bin(self.me).count('1')
        opp = bin(self.opp).count('1')
        if me > opp:
            return 64 - (2 * opp)
        if opp > me:
            return -64 + (2 * me)
        return 0
