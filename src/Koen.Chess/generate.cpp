
#include <Debugapi.h>
#include <windows.h>
#include "pch.h"
#include "generate.h"
#include "stringutilities.h"


vector<Move> generateMoves(BitBoard i_bitBoard)
{
  vector<Move> moves;

  generateCastleMoves(i_bitBoard, moves);

  // King
  BITMASK bm_piece = i_bitBoard.pieces[i_bitBoard.side][K];
  if (bm_piece)
  { // Expect always one king on the board, therefore no loop here.
    int from = bitScan(bm_piece);

    BITMASK bm_to = bm_kingmoves[from] & i_bitBoard.army[i_bitBoard.xside];
    while (bm_to)
    {
      int to = bitScan(bm_to);
      addMoveCapture(moves, K, from, to, i_bitBoard.squares[to]);
    
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm_to, to);
    }

    bm_to = bm_kingmoves[from] & i_bitBoard.xoccupied;
    while (bm_to)
    {
      int to = bitScan(bm_to);
      addMove(moves, K, from, to);
      
      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm_to, to);
    }
  }

  // Pawn
  bm_piece = i_bitBoard.pieces[i_bitBoard.side][P];
  while (bm_piece)
  {
    int from = bitScan(bm_piece);
    int to = ix_destination[ix_white_or_black_directions[i_bitBoard.side][NORTH]][from];

    if (bm_squares[to] & i_bitBoard.xoccupied)
    { // Pawn can go to north
      if (bm_squares[from] & bm_second_or_seventh_rank[i_bitBoard.xside])
      { // Pawn is promoted on the 8th rank.
        addMovePromotion(moves, P, from, to, N);
        addMovePromotion(moves, P, from, to, B);
        addMovePromotion(moves, P, from, to, R);
        addMovePromotion(moves, P, from, to, Q);
      }
      else
      {
        addMove(moves, P, from, to);
        
        to = ix_destination[ix_white_or_black_directions[i_bitBoard.side][NORTH]][to];
        if (bm_squares[from] & bm_second_or_seventh_rank[i_bitBoard.side])
        { // When pawn is on initial square and north (2) is empty:
          if (bm_squares[to] & i_bitBoard.xoccupied)
          {
            addMove(moves, P, from, to);
          }
        }
      }
    }

    for (int d = NORTHEAST; d <= NORTHWEST; d += NORTHWEST - NORTHEAST)
    {
      int x = ix_white_or_black_directions[i_bitBoard.side][d];

      to = ix_destination[x][from];
      if (bm_squares[to] & i_bitBoard.army[i_bitBoard.xside])
      { // When square to north-east is captured:
        if (bm_squares[from] & bm_second_or_seventh_rank[i_bitBoard.xside])
        { // Pawn is promoted on the 8th rank.
          addMovePromotionCapture(moves, P, from, to, N, i_bitBoard.squares[to]);
          addMovePromotionCapture(moves, P, from, to, B, i_bitBoard.squares[to]);
          addMovePromotionCapture(moves, P, from, to, R, i_bitBoard.squares[to]);
          addMovePromotionCapture(moves, P, from, to, Q, i_bitBoard.squares[to]);
        }
        else
        {
          addMoveCapture(moves, P, from, to, i_bitBoard.squares[to]);
        }
      }

      if (bm_squares[to] & i_bitBoard.enpassant)
      {
        addMoveCapture(moves, P, from, to, EP);
      }
    }

    // Remove the bit to go to next bit later.
    BIT_CLEAR(bm_piece, from);
  }

  // Knight
  bm_piece = i_bitBoard.pieces[i_bitBoard.side][N];
  while (bm_piece)
  {
    int from = bitScan(bm_piece);

    BITMASK bm_to = bm_knightmoves[from] & i_bitBoard.army[i_bitBoard.xside];
    while (bm_to)
    {
      int to = bitScan(bm_to);
      addMoveCapture(moves, N, from, to, i_bitBoard.squares[to]);

      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm_to, to);
    }

    bm_to = bm_knightmoves[from] & i_bitBoard.xoccupied;
    while (bm_to)
    {
      int to = bitScan(bm_to);
      addMove(moves, N, from, to);

      // Remove the bit to go to next bit later.
      BIT_CLEAR(bm_to, to);
    }

    // Remove the bit to go to next bit later.
    BIT_CLEAR(bm_piece, from);
  }

  // Bishop, Rook, Queen
  for (int brq = 0; brq < 3; ++brq)
  {
    bm_piece = i_bitBoard.pieces[i_bitBoard.side][ix_slider_pieces[brq]];
    while (bm_piece)
    {
      int from = bitScan(bm_piece);

      for (int d = ix_slider_directions[brq][0]; d < 8; d += ix_slider_directions[brq][1])
      {
        for (int to = ix_destination[d][from]; to >= 0; to = ix_destination[d][to])
        {
          if (bm_squares[to] & i_bitBoard.army[i_bitBoard.side])
          { 
            // Cannot capture or jump friendly piece.
            break;
          }

          if (bm_squares[to] & i_bitBoard.army[i_bitBoard.xside])
          {
            // Capture enemy piece, however cannot jump.
            addMoveCapture(moves, ix_slider_pieces[brq], from, to, i_bitBoard.squares[to]);
            break;
          }

          // Move to empty square.
          addMove(moves, ix_slider_pieces[brq], from, to);
        }
      }

      // Remove the bit to go to next bit.
      BIT_CLEAR(bm_piece, from);
    }
  }

  return moves;
}


void generateCastleMoves(BitBoard i_bitBoard, vector<Move>& io_moves)
{
  if (i_bitBoard.castle & i_bitBoard.xoccupied & bm_castle[i_bitBoard.side][CASTLE_LONG])
  {
    addMove(io_moves, K, castle_source_move[i_bitBoard.side], castle_destination_move[i_bitBoard.side][CASTLE_LONG]);
  }

  if (i_bitBoard.castle & i_bitBoard.xoccupied & bm_castle[i_bitBoard.side][CASTLE_SHORT])
  {
    addMove(io_moves, K, castle_source_move[i_bitBoard.side], castle_destination_move[i_bitBoard.side][CASTLE_SHORT]);
  }
}


void addMove(vector<Move>& io_moves, int i_piece, int i_from, int i_to)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.promotedPiece = E;
  move.capturedPiece = E;
  io_moves.push_back(move);
}


void addMoveCapture(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_capturedPiece)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.promotedPiece = E;
  move.capturedPiece = i_capturedPiece;
  io_moves.push_back(move);
}

void addMovePromotion(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_promotedPiece)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.promotedPiece = i_promotedPiece;
  move.capturedPiece = E;
  io_moves.push_back(move);
}


void addMovePromotionCapture(vector<Move>& io_moves, int i_piece, int i_from, int i_to, int i_promotedPiece, int i_capturedPiece)
{
  Move move;
  move.piece = i_piece;
  move.from = i_from;
  move.to = i_to;
  move.promotedPiece = i_promotedPiece;
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
  io_bitBoard.squares[i_move.to] = io_bitBoard.squares[i_move.from];

  // Reset source square.
  BITMASK_FLIP(io_bitBoard.occupied, bm_from);
  BITMASK_FLIP(io_bitBoard.xoccupied, bm_from);
  io_bitBoard.squares[i_move.from] = E;

  // Capture opponent piece on destination square.
  if (i_move.capturedPiece < X)
  {
    BITMASK_FLIP(io_bitBoard.pieces[io_bitBoard.xside][i_move.capturedPiece], bm_to);
    BITMASK_FLIP(io_bitBoard.army[io_bitBoard.xside], bm_to);
  }

  if (i_move.capturedPiece == EP)
  { // Capture pawn enpassant
    int direction = ix_white_or_black_directions[io_bitBoard.side][SOUTH];
    int captureSquare = ix_destination[direction][i_move.to];
    BITMASK bm_capture = bm_squares[captureSquare];
    BITMASK_FLIP(io_bitBoard.pieces[io_bitBoard.xside][P], bm_capture);
    BITMASK_FLIP(io_bitBoard.army[io_bitBoard.xside], bm_capture);
    io_bitBoard.squares[captureSquare] = E;
  }

  if (i_move.promotedPiece != E)
  { // Promote piece
    BITMASK_CLEAR(io_bitBoard.pieces[io_bitBoard.side][P], bm_to);
    BITMASK_SET(io_bitBoard.pieces[io_bitBoard.side][i_move.promotedPiece], bm_to);
    io_bitBoard.squares[i_move.to] = i_move.promotedPiece;
  }

  if (i_move.piece == K)
  {
    BITMASK_CLEAR(io_bitBoard.castle, bm_castle[io_bitBoard.side][CASTLE_LONG] | bm_castle[io_bitBoard.side][CASTLE_SHORT]);

    if (abs(i_move.from - i_move.to) == 2)
    { // Is castle? Then lift over the rook over the king.
      io_bitBoard.squares[ix_castle_rook_from[i_move.to]] = E;
      io_bitBoard.squares[ix_castle_rook_to[i_move.to]] = R;
      BITMASK_FLIP(io_bitBoard.pieces[io_bitBoard.side][R], bm_castle_rook_flip[i_move.to]);
      BITMASK_FLIP(io_bitBoard.army[io_bitBoard.side], bm_castle_rook_flip[i_move.to]);
      BITMASK_FLIP(io_bitBoard.occupied, bm_castle_rook_flip[i_move.to]);
      BITMASK_FLIP(io_bitBoard.xoccupied, bm_castle_rook_flip[i_move.to]);
    }
  }

  if (i_move.piece == R)
  {
    // Remove castle rights
    BITMASK_CLEAR(io_bitBoard.castle, bm_castle_rook_from[io_bitBoard.side][i_move.from]);
  }

  // Update enpassant permission.
  if (i_move.piece == P && abs(i_move.from - i_move.to) == 16)
  {
    BITMASK_SET(io_bitBoard.enpassant, bm_squares[ix_white_or_black_directions[io_bitBoard.side][SOUTH]]);
  }
  else
  {
    io_bitBoard.enpassant = bm_empty;
  }

  if (i_move.piece == P || i_move.capturedPiece != E)
  {
    io_bitBoard.halfMove50DrawRule = 0;
  }
  else
  {
    ++io_bitBoard.halfMove50DrawRule;
  }

  if (io_bitBoard.side == B)
  {
    ++io_bitBoard.fullMoveNumber;
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

  if (i_move.piece != P)
  {
    result += pieceToSymbol[W][i_move.piece];
  }

  result += squareNames[i_move.from];

  if (i_move.capturedPiece != E)
  {
    result += "x";
  }

  result += squareNames[i_move.to];

  if (i_move.promotedPiece > P && i_move.promotedPiece < K)
  {
    result += pieceToSymbol[W][i_move.promotedPiece];
  }

  if (result == "Ke1c1" || result == "Ke8c8")
  {
    result = "0-0-0";
  }
  else if (result == "Ke1g1" || result == "Ke8g8")
  {
    result = "0-0";
  }
  
  return result;
}