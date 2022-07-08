/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include <format>
#include "pch.h"
#include "CppUnitTest.h"
#include "../Koen.Chess/bitboard.h"
#include "../Koen.Chess/generate.h"
#include "../Koen.Chess/stringutilities.h"
#include "../Koen.Chess/testutilities.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Koen {
	namespace UnitTest
	{
		TEST_CLASS(GenerateTest)
		{
		public:

			TEST_METHOD(test_Generate)
			{
				assertGenerateMoves("Ke1 Xd1f1 => d2 e2 f2 !d1 !f1");
				assertGenerateMoves("Ke1 xd1f1 => d2 e2 f2 xd1 xf1");
				assertGenerateMoves("B ke1 Xd1f1 => d2 e2 f2 xd1 xf1");
				assertGenerateMoves("B ke1 xd1f1 => d2 e2 f2 !d1 !f1");
			}


			TEST_METHOD(test_MakeMove)
			{
				// Arrange
				BitBoard bitBoard;
				fenToBitBoard("8/8/8/3k4/4Q3/8/8/8", bitBoard); // TODO + " w - -0 1"
				bitBoard.side = B;
				bitBoard.xside = W;

				Move move;
				move.piece = K;
				move.from = D5;
				move.to = E4;
				move.capturedPiece = Q;
				
				// Act
				makeMove(move, bitBoard);
				
				// Assert
				string expectedFen = "8/8/8/8/4k3/8/8/8"; // TODO + " w - -0 1"
				Logger::WriteMessage(toBitBoard1DString(bitBoard).c_str());

				Assert::AreEqual(expectedFen, bitBoardToFen(bitBoard));
			}


			TEST_METHOD(test_ToMoveString)
			{
				// Arrange
				Move normalMove, captureMove;
				normalMove.from = A1;
				captureMove.from = A1;
				normalMove.to = H8;
				captureMove.to = H8;
				normalMove.capturedPiece = E;
				captureMove.capturedPiece = P;
				
				// Act
				string normalMoveStr = toMoveString(normalMove);
				string captureMoveStr = toMoveString(captureMove);

				// Assert
				Logger::WriteMessage(normalMoveStr.c_str());
				Logger::WriteMessage(captureMoveStr.c_str());
				Assert::AreEqual<string>("a1h8", normalMoveStr);
				Assert::AreEqual<string>("a1xh8", captureMoveStr);
			}
		};
	}
}