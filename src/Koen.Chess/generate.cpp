#include "pch.h"
#include "generate.h"


vector<Move> generateMoves()
{
  vector<Move> moves;

  Move move1;
  move1.from = D1;
  move1.to = D8;
  moves.push_back(move1);

  Move move2;
  move2.from = A8;
  move2.to = H1;
  moves.push_back(move2);

  return moves;
}


string toMoveString(Move i_move)
{
  string result = "";

  result += squareNames[i_move.from];
  result += squareNames[i_move.to];
  
  return result;
}