/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "bitboard.h"


void clearBitBoard(BitBoard& io_bitBoard)
{
  for (int cp = 0; cp < 12; ++cp)
  {
    int c = cp % 2;
    int p = cp / 2;
    io_bitBoard.pieces[c][p] = bm_empty;
  }

  io_bitBoard.army[W] = bm_empty;
  io_bitBoard.army[B] = bm_empty;
  io_bitBoard.castle = bm_empty;
  io_bitBoard.enpassant = bm_empty;
  io_bitBoard.occupied = bm_empty;
  io_bitBoard.xoccupied = bm_full;
}


void startBitBoard(BitBoard& io_bitBoard)
{
  io_bitBoard.pieces[W][P] = bm_rank[RANK_2];
  io_bitBoard.pieces[W][N] = bm_squares[B1] | bm_squares[G1];
  io_bitBoard.pieces[W][B] = bm_squares[C1] | bm_squares[F1];
  io_bitBoard.pieces[W][R] = bm_squares[A1] | bm_squares[H1];
  io_bitBoard.pieces[W][Q] = bm_squares[D1];
  io_bitBoard.pieces[W][K] = bm_squares[E1];
  io_bitBoard.pieces[B][P] = bm_rank[RANK_7];
  io_bitBoard.pieces[B][N] = bm_squares[B8] | bm_squares[G8];
  io_bitBoard.pieces[B][B] = bm_squares[C8] | bm_squares[F8];
  io_bitBoard.pieces[B][R] = bm_squares[A8] | bm_squares[H8];
  io_bitBoard.pieces[B][Q] = bm_squares[D8];
  io_bitBoard.pieces[B][K] = bm_squares[E8];

  io_bitBoard.army[W] = bm_rank[RANK_1] | bm_rank[RANK_2];
  io_bitBoard.army[B] = bm_rank[RANK_7] | bm_rank[RANK_8];
  io_bitBoard.castle = bm_empty; // TODO
  io_bitBoard.enpassant = bm_empty;
  io_bitBoard.occupied = io_bitBoard.army[W] | io_bitBoard.army[B];
  io_bitBoard.xoccupied = ~io_bitBoard.occupied;
}


void fenToBitBoard(string i_fen, BitBoard& io_bitBoard)
{
  clearBitBoard(io_bitBoard);

  int s = 0;
  for (char const& symbol : i_fen)
  {
    if (isdigit(symbol))
    {
      s += symbol - '0';
      continue;
    }

    if (symbol == '/')
    {
      continue;
    }

    int c = colorSymbolToInteger[(int) symbol - 'A'];
    int p = pieceSymbolToInteger[(int) symbol - 'A'];

    BIT_SET(io_bitBoard.pieces[c][p], s);
    BIT_SET(io_bitBoard.army[c], s);
    BIT_SET(io_bitBoard.occupied, s);
    BIT_CLEAR(io_bitBoard.xoccupied, s);

    ++s;
  }
}


string bitBoardToFen(BitBoard i_bitBoard)
{
  string fen = "";

  int consecutiveEmptySquares = 0;
  for (int s = 0; s < 64; ++s)
  {
    string symbol = "";
    for (int cp = 0; cp < 12; ++cp)
    {
      int c = cp % 2;
      int p = cp / 2;

      if (BIT_CHECK(i_bitBoard.pieces[c][p], s))
      {
        symbol = pieceToSymbol[c][p];
        break;
      }
    }

    if (symbol == "")
    {
      consecutiveEmptySquares++;
    }
    else
    {
      if (consecutiveEmptySquares != 0)
      {
        fen += to_string(consecutiveEmptySquares);
        consecutiveEmptySquares = 0;
      }

      fen += symbol;
    }

    if (s % 8 == 7)
    {
      if (consecutiveEmptySquares != 0)
      {
        fen += to_string(consecutiveEmptySquares);
        consecutiveEmptySquares = 0;
      }

      if (s != 63)
      {
        fen += "/";
      }
    }
  }

  return fen;
}


string toBitBoard2DString(BitBoard i_bitBoard)
{
  string result = "";

  for (int s = 0; s < 64; s++)
  {
    int file = s % 8;
    int rank = 8 - (s / 8);

    if (file == FILE_A)
    {
      result += std::to_string(rank);
      result += "|";
    }

    if (BIT_CHECK(i_bitBoard.xoccupied, s))
    {
      result += " 0";
    }
    else
    {
      for (int cp = 0; cp < 12; ++cp)
      {
        int c = cp % 2;
        int p = cp / 2;

        if (BIT_CHECK(i_bitBoard.pieces[c][p], s))
        {
          result += ' ' + pieceToSymbol[c][p];
        }
      }
    }

    if (file == FILE_H)
    {
      result += "\n";
    }
  }

  result += "  ----------------\n";
  result += "   a b c d e f g h";

  return result;
}