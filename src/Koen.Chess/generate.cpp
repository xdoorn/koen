#include "pch.h"
#include "generate.h"


vector<Move> generateMoves(BitBoard i_bitBoard)
{
  vector<Move> moves;

  BITMASK bm1 = i_bitBoard.pieces[i_bitBoard.side][K];
  if (bm1)
  { // Expect always one king on the board, therefore no loop here.
    int from = bitScan(bm1);

    BITMASK bm2 = bm_kingmoves[from] & i_bitBoard.army[i_bitBoard.xside];
    while (bm2)
    {
      int to = bitScan(bm2);
      addMoveCapture(moves, from, to, i_bitBoard.board[to]);
    
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm2, to);
    }

    bm2 = bm_kingmoves[from] & i_bitBoard.xoccupied;
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
  move.capturedPiece = E;
  io_moves.push_back(move);
}


void addMoveCapture(vector<Move>& io_moves, int i_from, int i_to, int i_capturedPiece)
{
  Move move;
  move.from = i_from;
  move.to = i_to;
  move.capturedPiece = i_capturedPiece;
  io_moves.push_back(move);
}


string toMoveString(Move i_move)
{
  string result = "";

  result += squareNames[i_move.from];

  if (i_move.capturedPiece != E)
  {
    result += "x";
  }

  result += squareNames[i_move.to];
  
  return result;
}