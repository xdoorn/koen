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

  BitBoard bitBoard;
  fenToBitBoard(i_fen, bitBoard);
  BitBoard xBitBoard = mirrorBitBoard(bitBoard);
  m_xfen = bitBoardToFen(xBitBoard);

  return *this;
}


TestMoveGeneration TestMoveGeneration::arrange(BitBoard i_bitBoard)
{
  m_fen = bitBoardToFen(i_bitBoard);

  // Mirror the fen;
  BitBoard xBitBoard = mirrorBitBoard(i_bitBoard);
  m_xfen = bitBoardToFen(xBitBoard);

  return *this;
}


TestMoveGeneration TestMoveGeneration::act(string i_move)
{
  m_move.piece = E;
  m_xmove.piece = E;
  
  BitBoard bitBoard;
  fenToBitBoard(m_fen, bitBoard);

  auto moves = generateMoves(bitBoard);
  for (Move move : moves)
  {
    string moveString = toMoveString(move);
    if (moveString == i_move)
    {
      m_move = move;
      break;
    }
  }

  // Mirror
  BitBoard xBitBoard;
  fenToBitBoard(m_xfen, xBitBoard);

  moves = generateMoves(xBitBoard);
  for (Move move : moves)
  {
    Move xmove;
    xmove.piece = move.piece;
    xmove.from = ix_mirror[move.from];
    xmove.to = ix_mirror[move.to];
    xmove.capturedPiece = move.capturedPiece;
    xmove.promotedPiece = move.promotedPiece;

    string moveString = toMoveString(xmove);
    if (moveString == i_move)
    {
      m_xmove = move;
      break;
    }
  }
  
  return *this;
}


TestMoveGeneration TestMoveGeneration::assertLegal(string i_expectedFen, string i_message)
{
  Assert::IsFalse(m_move.piece == E, toWString(i_message).c_str());
  Assert::IsFalse(m_xmove.piece == E, toWString(i_message + " [Mirror]").c_str());

  BitBoard bitBoard;
  fenToBitBoard(m_fen, bitBoard);
  makeMove(m_move, bitBoard);
  string actualFen = bitBoardToFen(bitBoard);
  Assert::AreEqual<string>(i_expectedFen, actualFen, toWString(i_message).c_str());

  // Mirror
  BitBoard xActualBitBoard;
  fenToBitBoard(m_xfen, xActualBitBoard);
  makeMove(m_xmove, xActualBitBoard);
  string xActualFen = bitBoardToFen(xActualBitBoard);
  BitBoard xExpectedBitBoard;
  fenToBitBoard(i_expectedFen, xExpectedBitBoard);
  xExpectedBitBoard = mirrorBitBoard(xExpectedBitBoard);
  if (xExpectedBitBoard.side == W)
  {
    ++xExpectedBitBoard.fullMoveNumber;
  }
  else
  {
    --xExpectedBitBoard.fullMoveNumber;
  }
  string xExpectedFen = bitBoardToFen(xExpectedBitBoard);
  Assert::AreEqual<string>(xExpectedFen, xActualFen, toWString(i_message + " [Mirror]").c_str());

  return *this;
}


TestMoveGeneration TestMoveGeneration::assertIllegal(string i_message)
{
  Assert::IsTrue(m_move.piece == E, toWString(i_message).c_str());
  Assert::IsTrue(m_xmove.piece == E, toWString(i_message + " [Mirror]").c_str());

  return *this;
}