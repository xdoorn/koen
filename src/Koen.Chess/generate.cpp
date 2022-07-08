
#include <Debugapi.h>
#include <windows.h>
#include "pch.h"
#include "generate.h"
#include "stringutilities.h"


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
      addMoveCapture(moves, K, from, to, i_bitBoard.board[to]);
    
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm2, to);
    }

    bm2 = bm_kingmoves[from] & i_bitBoard.xoccupied;
    while (bm2)
    {
      int to = bitScan(bm2);
      addMove(moves, K, from, to);
      
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm2, to);
    }
  }

  return moves;
}


void addMove(vector<Move>& io_moves, int i_piece, int i_from, int i_to)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.capturedPiece = E;
  io_moves.push_back(move);
}


void addMoveCapture(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_capturedPiece)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.capturedPiece = i_capturedPiece;
  io_moves.push_back(move);
}


void makeMove(Move i_move, BitBoard& io_bitBoard)
{  
  BITMASK bm_from = static_cast<unsigned long long>(1) << i_move.from;
  BITMASK bm_to = static_cast<unsigned long long>(1) << i_move.to;
  BITMASK bm_fromTo = bm_from ^ bm_to;

  // Move piece from source to destination square.
  BITMASK_FLIP(io_bitBoard.pieces[io_bitBoard.side][i_move.piece], bm_fromTo);
  BITMASK_FLIP(io_bitBoard.army[io_bitBoard.side], bm_fromTo);
  io_bitBoard.board[i_move.to] = io_bitBoard.board[i_move.from];

  // Reset source square.
  BITMASK_FLIP(io_bitBoard.occupied, bm_from);
  BITMASK_FLIP(io_bitBoard.xoccupied, bm_from);
  io_bitBoard.board[i_move.from] = E;

  // Capture opponent piece on destination square.
  if (i_move.capturedPiece != E)
  {
    BITMASK_FLIP(io_bitBoard.pieces[io_bitBoard.xside][i_move.capturedPiece], bm_to);
    BITMASK_FLIP(io_bitBoard.army[io_bitBoard.xside], bm_to);
  }

  // Flip side to move.
  io_bitBoard.side ^= 1;
  io_bitBoard.xside ^= 1;
}


void unmakeMove(Move i_move, BitBoard& io_bitBoard)
{
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