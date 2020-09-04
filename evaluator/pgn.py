from dataclasses import dataclass
from typing import List


@dataclass
class Pgn:
    black_elo: int
    white_elo: int
    black: str
    white: str
    variant: str
    moves: List[int]
