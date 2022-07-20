#pragma once

#include <string>
#include "../Koen.Chess/bitboard.h"
#include "../Koen.Chess/generate.h"

using namespace std;

class TestMoveGeneration
{
public:
  TestMoveGeneration();
  static TestMoveGeneration create();
  TestMoveGeneration arrange(string i_fen);
  TestMoveGeneration arrange(BitBoard i_bitBoard);
  TestMoveGeneration act(string i_move);
  TestMoveGeneration assertLegal(string i_expectedFen, string i_message = "");
  TestMoveGeneration assertIllegal(string i_message = "");

private:
  string m_fen;
  string m_xfen;
  Move m_move;
  Move m_xmove;
};

