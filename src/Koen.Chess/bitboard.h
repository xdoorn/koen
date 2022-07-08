/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#pragma once

#include <iostream>
#include "bitmask.h"


typedef struct
{
  BITMASK pieces[2][6];
  BITMASK army[2];
  BITMASK occupied;
  BITMASK xoccupied;
  BITMASK castle;
  BITMASK enpassant;
  int board[64];
  int side;
  int xside;
} BitBoard;


const string pieceToSymbol[2][7]
{
  { "P", "B", "N", "R", "Q", "K", "X"},
  { "p", "b", "n", "r", "q", "k", "x"},
};


// Piece symbol like PNBRQK & pnbrqk to color integer conversion (e.g. W = 0, B = 1, E = 7)
// The table starts relative from ASCII's 'A' and ends with 'z'
const int colorSymbolToInteger[]
{
  W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
  W, W, W, W, W, W, W, W, W, W, W, W, W, W,
  B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
  B, B, B, B, B, B, B, B
};


// Piece symbol like PNBRQK & pnbrqk to piece integer conversion (e.g. P = 0, B = 1, N = 2, R = 3, Q = 4, K = 5, X = 6, E = 7)
// The table starts relative from ASCII's 'A' and ends with 'z'
const int pieceSymbolToInteger[]
{
  X, B, X, X, X, X, X, X, X, X, K, X, X, N, X, P, Q, R,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, B, X, X, X, X, X, X, X, X, K, X, X, N, X, P, Q, R, 
  X, X, X, X, X, X, X, X
};


const int initialBoard[64] =
{
  R, N, B, Q, K, B, N, R,
  P, P, P, P, P, P, P, P,
  E, E, E, E, E, E, E, E,
  E, E, E, E, E, E, E, E,
  E, E, E, E, E, E, E, E,
  E, E, E, E, E, E, E, E,
  P, P, P, P, P, P, P, P,
  R, N, B, Q, K, B, N, R
};


void clearBitBoard(BitBoard& io_bitBoard);
void startBitBoard(BitBoard& io_bitBoard);
void setupBitBoard(BitBoard& io_bitBoard, int i_color, int i_piece, int i_square);
void fenToBitBoard(string i_fen, BitBoard& io_bitBoard);
string bitBoardToFen(BitBoard i_bitBoard);
string toBitBoard1DString(BitBoard i_bitBoard);
string toBitBoard2DString(BitBoard i_bitBoard);
