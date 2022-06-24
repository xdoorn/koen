#include "pch.h"
#include "generate.h"


vector<Move> generateMoves(BitBoard i_bitBoard)
{
  vector<Move> moves;

  BITMASK bm1 = i_bitBoard.pieces[i_bitBoard.side][K];
  if (bm1)
  { // Expect always one king on the board, therefore no loop here.
    int from = bitScan(bm1);

    BITMASK bm2 = bm_kingmoves[from] & ~i_bitBoard.army[i_bitBoard.side];
    while (bm2)
    {
      int to = bitScan(bm2);
      addMove(moves, from, to);
      
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm2, to);
    }
  }

  return moves;
}


void addMove(vector<Move>& io_moves, int i_from, int i_to)
{
  Move move;
  move.from = i_from;
  move.to = i_to;
  io_moves.push_back(move);
}


string toMoveString(Move i_move)
{
  string result = "";

  result += squareNames[i_move.from];
  result += squareNames[i_move.to];
  
  return result;
}