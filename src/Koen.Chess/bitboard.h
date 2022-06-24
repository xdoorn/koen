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
  int side;
  int xside;
} BitBoard;


const string pieceToSymbol[2][6]
{
  { "P", "B", "N", "R", "Q", "K"},
  { "p", "b", "n", "r", "q", "k"},
};


// Piece symbol like PNBRQK & pnbrqk to color integer conversion (e.g. W = 0, B = 1, Else = 9)
// The table starts relative from ASCII's 'A'.
const int colorSymbolToInteger[]
{
  9, W, 9, 9, 9, 9, 9, 9, 9, 9, W, 9, 9, W, 9, W, W, W,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  9, B, 9, 9, 9, 9, 9, 9, 9, 9, B, 9, 9, B, 9, B, B, B,
};


// Piece symbol like PNBRQK & pnbrqk to piece integer conversion (e.g. P = 0, B = 1, N = 2, R = 3, Q = 4, K = 5, Else = 9)
// The table starts relative from ASCII's 'A'.
const int pieceSymbolToInteger[]
{
  9, B, 9, 9, 9, 9, 9, 9, 9, 9, K, 9, 9, N, 9, P, Q, R,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  9, B, 9, 9, 9, 9, 9, 9, 9, 9, K, 9, 9, N, 9, P, Q, R,
};


void clearBitBoard(BitBoard& io_bitBoard);
void startBitBoard(BitBoard& io_bitBoard);
void fenToBitBoard(string i_fen, BitBoard& io_bitBoard);
string bitBoardToFen(BitBoard i_bitBoard);
string toBitBoard2DString(BitBoard i_bitBoard);

