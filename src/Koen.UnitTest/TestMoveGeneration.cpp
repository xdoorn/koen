#include "pch.h"
#include "CppUnitTest.h"
#include "TestMoveGeneration.h"
#include "../Koen.Chess/generate.h"
#include "../Koen.Chess/stringutilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TestMoveGeneration::TestMoveGeneration()
{
}


TestMoveGeneration TestMoveGeneration::create()
{
  return TestMoveGeneration();
}


TestMoveGeneration TestMoveGeneration::arrange(string i_fen)
{
  m_fen = i_fen;
  return *this;
}


TestMoveGeneration TestMoveGeneration::arrange(BitBoard i_bitBoard)
{
  m_fen = bitBoardToFen(i_bitBoard);
  return *this;
}


TestMoveGeneration TestMoveGeneration::act(string i_move)
{
  m_move.piece = E;
  
  BitBoard bitBoard;
  fenToBitBoard(m_fen, bitBoard);

  for (Move move : generateMoves(bitBoard))
  {
    string moveString = toMoveString(move);
    if (moveString == i_move)
    {
      m_move = move;
      break;
    }
  }

  return *this;
}


TestMoveGeneration TestMoveGeneration::assertLegal(string i_expectedFen, string i_message)
{
  Assert::IsFalse(m_move.piece == E, toWString(i_message).c_str());

  BitBoard bitBoard;
  fenToBitBoard(m_fen, bitBoard);

  makeMove(m_move, bitBoard);
  string actualFen = bitBoardToFen(bitBoard);

  Assert::AreEqual<string>(i_expectedFen, actualFen, toWString(i_message).c_str());

  return *this;
}


TestMoveGeneration TestMoveGeneration::assertIllegal(string i_message)
{
  Assert::IsTrue(m_move.piece == E, toWString(i_message).c_str());
  return *this;
}