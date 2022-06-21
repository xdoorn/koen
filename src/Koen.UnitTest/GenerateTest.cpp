/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../Koen.Chess/bitboard.h"
#include "../Koen.Chess/generate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Koen {
	namespace UnitTest
	{
		TEST_CLASS(GenerateTest)
		{
		public:
			TEST_METHOD(test_Generate)
			{
				// Act
				vector<Move> moves = generateMoves();

				// Assert
				Logger::WriteMessage(toMoveString(moves.at(0)).c_str());
				Logger::WriteMessage("\n");
				Logger::WriteMessage(toMoveString(moves.at(1)).c_str());
				Assert::AreEqual<int>(D1, moves.at(0).from);
				Assert::AreEqual<int>(D8, moves.at(0).to);
				Assert::AreEqual<int>(A8, moves.at(1).from);
				Assert::AreEqual<int>(H1, moves.at(1).to);
			}

			TEST_METHOD(test_ToMoveString)
			{
				// Arrange
				Move move;
				move.from = A1;
				move.to = H8;

				// Act
				string moveStr = toMoveString(move);

				// Assert
				Logger::WriteMessage(moveStr.c_str());
				Assert::AreEqual<string>("a1h8", moveStr);
			}
		};
	}
}