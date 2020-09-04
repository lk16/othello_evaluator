from .board import Board, MOVE_PASS

EXACT_SCORE_FACTOR = 1000
MIN_HEURISTIC = -64 * EXACT_SCORE_FACTOR
MAX_HEURISTIC = 64 * EXACT_SCORE_FACTOR

CORNER_MASK = 0x8100000000000081


class Bot:
    def __init__(self, depth: int):
        self.depth = depth

    @classmethod
    def heuristic(cls, board: Board) -> int:
        me_corners = bin(board.me & CORNER_MASK).count('1')
        opp_corners = bin(board.opp & CORNER_MASK).count('1')

        me_moves = bin(board.get_moves()).count('1')
        opp_moves = bin(board.do_move(MOVE_PASS).get_moves()).count('1')

        return me_moves - opp_moves + 3*(me_corners - opp_corners)

    def search(self, board: Board) -> int:
        return self._alpha_beta(board, MIN_HEURISTIC, MAX_HEURISTIC, self.depth)

    def _alpha_beta(self, board: Board, alpha: int, beta: int, depth: int) -> int:
        if depth == 0:
            return self.heuristic(board)

        children = board.get_children()

        if not children:
            board = board.do_move(MOVE_PASS)
            if not board.get_moves():
                return EXACT_SCORE_FACTOR * board.exact_score()
            return -self._alpha_beta(board, -beta, -alpha, depth)

        for child in children:
            heur = -self._alpha_beta(child, -beta, -alpha, depth-1)

            if heur >= beta:
                return beta

            if heur > alpha:
                alpha = heur

        return alpha
