/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "bitboard.h"
#include "stringutilities.h"


void clearBitBoard(BitBoard& io_bitBoard)
{
  for (int cp = 0; cp < 12; ++cp)
  {
    int c = cp % 2;
    int p = cp / 2;
    io_bitBoard.pieces[c][p] = bm_empty;
  }

  for (int s = 0; s < 64; ++s)
  {
    io_bitBoard.board[s] = E;
  }

  io_bitBoard.army[W] = bm_empty;
  io_bitBoard.army[B] = bm_empty;
  io_bitBoard.occupied = bm_empty;
  io_bitBoard.xoccupied = bm_full;
  io_bitBoard.side = W;
  io_bitBoard.xside = B;
  io_bitBoard.castle = bm_empty;
  io_bitBoard.enpassant = bm_empty;
  io_bitBoard.halfMove50DrawRule = 0;
  io_bitBoard.fullMoveNumber = 0;
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
  io_bitBoard.occupied = io_bitBoard.army[W] | io_bitBoard.army[B];
  io_bitBoard.xoccupied = ~io_bitBoard.occupied;
  for (int s = 0; s < 64; ++s)
  {
    io_bitBoard.board[s] = initialBoard[s];
  }

  io_bitBoard.side = W;
  io_bitBoard.xside = B;
  io_bitBoard.castle = bm_squares[A1] | bm_squares[H1] | bm_squares[A8] | bm_squares[H8];
  io_bitBoard.enpassant = bm_empty;
  io_bitBoard.fullMoveNumber = 0;
  io_bitBoard.halfMove50DrawRule = 0;
}


void setupBitBoard(BitBoard& io_bitBoard, int i_color, int i_piece, int i_square)
{
  io_bitBoard.board[i_square] = i_piece;

  if (i_piece == E)
  {
    for (int c = 0; c < 2; ++c)
    {
      BIT_CLEAR(io_bitBoard.army[c], i_square);

      for (int p = 0; p < 6; ++p)
      {
        BIT_CLEAR(io_bitBoard.pieces[c][p], i_square);
      }
    }

    BIT_CLEAR(io_bitBoard.occupied, i_square);
    BIT_SET(io_bitBoard.xoccupied, i_square);
  }
  else
  {
    BIT_SET(io_bitBoard.pieces[i_color][i_piece], i_square);
    BIT_SET(io_bitBoard.army[i_color], i_square);
    BIT_SET(io_bitBoard.occupied, i_square);
    BIT_CLEAR(io_bitBoard.xoccupied, i_square);
  }

  BIT_SET(io_bitBoard.castle, A1);
  BIT_SET(io_bitBoard.castle, H1);
  BIT_SET(io_bitBoard.castle, A8);
  BIT_SET(io_bitBoard.castle, H8);
}


void fenToBitBoard(string i_fen, BitBoard& io_bitBoard)
{
  clearBitBoard(io_bitBoard);

  vector<string> fenParts = split(i_fen, " ", true);
  string position = fenParts[0];
  string side = fenParts[1];
  string castle = fenParts[2];
  string enpassant = fenParts[3];
  string halfMove50DrawRule = fenParts[4];
  string fullMoveNumber = fenParts[5];

  // Position
  int s = 0;
  for (char const& symbol : position)
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

    int c = colorSymbolToInteger[(int) (symbol - 'A')];
    int p = pieceSymbolToInteger[(int) (symbol - 'A')];

    BIT_SET(io_bitBoard.pieces[c][p], s);
    BIT_SET(io_bitBoard.army[c], s);
    BIT_SET(io_bitBoard.occupied, s);
    BIT_CLEAR(io_bitBoard.xoccupied, s);
    io_bitBoard.board[s] = p;

    ++s;
  }

  // Side [w/b]
  io_bitBoard.side = side == "b";
  io_bitBoard.xside = side == "w";

  // Castle KQkq
  if (castle == "-")
  {
    io_bitBoard.castle = bm_empty;
  }
  if (castle.find("K") != string::npos)
  {
    BIT_SET(io_bitBoard.castle, H1);
  }
  if (castle.find("Q") != string::npos)
  {
    BIT_SET(io_bitBoard.castle, A1);
  }
  if (castle.find("k") != string::npos)
  {
    BIT_SET(io_bitBoard.castle, H8);
  }
  if (castle.find("q") != string::npos)
  {
    BIT_SET(io_bitBoard.castle, A8);
  }

  // Enpassant
  io_bitBoard.enpassant = bm_empty;
  if (enpassant != "-")
  {
    int file = (int) enpassant[0] - 'a';
    int rank = 8 - (enpassant[1] - '0');
    int square = rank * 8 + file;
    BIT_SET(io_bitBoard.enpassant, square);
  }

  // Half Move (50-draw-rule)
  io_bitBoard.halfMove50DrawRule = stoi(halfMove50DrawRule);

  // Full Move number.
  io_bitBoard.fullMoveNumber = stoi(fullMoveNumber);
}


string bitBoardToFen(BitBoard i_bitBoard)
{
  string fen = "";

  // Position
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

  // Side
  fen += (i_bitBoard.side == W) ? " w" : " b";

  // Castle
  if (!i_bitBoard.castle)
  {
    fen += " -";
  }
  else
  {
    fen += " ";
    if (BIT_CHECK(i_bitBoard.castle, H1))
    {
      fen += "K";
    }
    if (BIT_CHECK(i_bitBoard.castle, A1))
    {
      fen += "Q";
    }
    if (BIT_CHECK(i_bitBoard.castle, H8))
    {
      fen += "k";
    }
    if (BIT_CHECK(i_bitBoard.castle, A8))
    {
      fen += "q";
    }
  }

  // Enpassant
  fen += " ";
  if (i_bitBoard.enpassant)
  {
    int square = bitScan(i_bitBoard.enpassant);
    int file = square % 8;
    int rank = 8 - square / 8;
    fen += (char) file + 'a';
    fen += to_string(rank);
  }
  else
  {
    fen += "-";
  }

  // Half Move (50-draw-rule)
  fen += " " + to_string(i_bitBoard.halfMove50DrawRule);

  // Full Move number.
  fen += " " + to_string(i_bitBoard.fullMoveNumber);

  return fen;
}


string toBitBoard1DString(BitBoard i_bitBoard)
{
  string result = "";

  result += "Occupied   = \t" + toBitMask1DString(i_bitBoard.occupied);
  result += "\nXoccupied  = \t" + toBitMask1DString(i_bitBoard.xoccupied);
  result += "\nArmy[W]    = \t" + toBitMask1DString(i_bitBoard.army[W]);
  result += "\nPawns[W]   = \t" + toBitMask1DString(i_bitBoard.pieces[W][P]);
  result += "\nKnights[W] = \t" + toBitMask1DString(i_bitBoard.pieces[W][N]);
  result += "\nBishops[W] = \t" + toBitMask1DString(i_bitBoard.pieces[W][B]);
  result += "\nRooks[W]   = \t" + toBitMask1DString(i_bitBoard.pieces[W][R]);
  result += "\nQueens[W]  = \t" + toBitMask1DString(i_bitBoard.pieces[W][Q]);
  result += "\nKing[W]    = \t" + toBitMask1DString(i_bitBoard.pieces[W][K]);
  result += "\nArmy[B]    = \t" + toBitMask1DString(i_bitBoard.army[B]);
  result += "\nPawns[B]   = \t" + toBitMask1DString(i_bitBoard.pieces[B][P]);
  result += "\nKnights[B] = \t" + toBitMask1DString(i_bitBoard.pieces[B][N]);
  result += "\nBishops[B] = \t" + toBitMask1DString(i_bitBoard.pieces[B][B]);
  result += "\nRooks[B]   = \t" + toBitMask1DString(i_bitBoard.pieces[B][R]);
  result += "\nQueens[B]  = \t" + toBitMask1DString(i_bitBoard.pieces[B][Q]);
  result += "\nKing[B]    = \t" + toBitMask1DString(i_bitBoard.pieces[B][K]);

  return result;
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
      int c = BIT_CHECK(i_bitBoard.army[W], s) ? W : B;
      int p = i_bitBoard.board[s];
      result += ' ' + pieceToSymbol[c][p];
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