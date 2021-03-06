#pragma once

#include <format>
#include <string>
#include <vector>
#include "bitboard.h"

using namespace std;

typedef struct
{
  int piece;
  int from;
  int to;
  int capturedPiece;
  int promotedPiece;
} Move;


const string squareNames[64]
{
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
};

const int castle_source_move[2]
{
  E1, E8
};

const int castle_destination_move[2][2]
{
  { C1, G1 },
  { C8, G8 }
};


vector<Move> generateMoves(BitBoard i_bitBoard);
void generateCastleMoves(BitBoard i_bitBoard, vector<Move>& io_moves);
void addMove(vector<Move>& io_moves, int i_piece, int i_from, int i_to);
void addMoveCapture(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_capturedPiece);
void addMovePromotion(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_promotedPiece);
void addMovePromotionCapture(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_promotedPiece, int i_capturedPiece);
void makeMove(Move i_move, BitBoard& io_bitBoard);
void unmakeMove(Move i_move, BitBoard& io_bitBoard);
string toMoveString(Move i_move);

