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
#include "TestMoveGeneration.h"


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
				// Test king moves and captures.
				TestMoveGeneration::create()
					.arrange("8/8/8/8/8/8/4b3/3rKr2 w - - 0 1")
						.act("Ke1d2").assertLegal("8/8/8/8/8/8/3Kb3/3r1r2 b - - 1 1", "Legal king move to d2.")
						.act("Ke1f2").assertLegal("8/8/8/8/8/8/4bK2/3r1r2 b - - 1 1", "Legal king move to f2.")
						.act("Ke1xd1").assertLegal("8/8/8/8/8/8/4b3/3K1r2 b - - 0 1", "Legal king move captures enemy rook on d1")
						.act("Ke1xf1").assertLegal("8/8/8/8/8/8/4b3/3r1K2 b - - 0 1", "Legal king move captures enemy rook on f1")
						.act("Ke1xe2").assertLegal("8/8/8/8/8/8/4K3/3r1r2 b - - 0 1", "Legal king move captures enemy bishop on e2")
					.arrange("8/8/8/8/8/8/4b3/3RKR2 w - - 0 1")
						.act("Ke1xd1").assertIllegal("Illegal king move capturing own rook on d1")
						.act("Ke1xf1").assertIllegal("Illegal king move capturing own rook on f1");

				// Test King can castle. 
				// TODO: CASTLE - check is not considered yet!!
				// TODO: CASTLE - attacked squares aren't considered yet!!
				TestMoveGeneration::create()
					.arrange("8/8/8/8/8/8/8/R3K2R w KQkq - 0 1")
						.act("0-0-0").assertLegal("8/8/8/8/8/8/8/2KR3R b kq - 1 1", "Legal white castles long")
						.act("0-0").assertLegal("8/8/8/8/8/8/8/R4RK1 b kq - 1 1", "Legal white castles short");
				  //.act("Ra1a8").assertLegal("R7/8/8/8/8/8/8/4K2R b Kkg - 0 1", "Clear castle long permission because rook had moved.")
					//.act("Rh1h8").assertLegal("7R/8/8/8/8/8/8/R3K3 b Qkg - 0 1", "Clear castle short permission because rook had moved.")

					//.arrange("8/8/8/8/8/8/8/R2BKB1R w KQ - 0 1")
					//	.act("Ke1b1").assertIllegal("Illegal white castles long because d1 is blocked")
					//	.act("Ke1g1").assertIllegal("Illegal white castles long because f1 is blocked");
			}


			TEST_METHOD(test_MakeMove)
			{
				// Arrange
				BitBoard bitBoard;
				fenToBitBoard("8/8/8/3k4/4Q3/8/8/8 w - - 0 1", bitBoard);
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
				string expectedFen = "8/8/8/8/4k3/8/8/8 w - - 0 2";
				Logger::WriteMessage(toBitBoard1DString(bitBoard).c_str());

				Assert::AreEqual(expectedFen, bitBoardToFen(bitBoard));
			}


			TEST_METHOD(test_ToMoveString)
			{
				// Arrange
				Move normalMove;
				normalMove.piece = R;
				normalMove.from = A1;
				normalMove.to = H8;
				normalMove.capturedPiece = E;
				
				Move captureMove;
				captureMove.piece = Q;
				captureMove.from = A1;
				captureMove.to = H8;				
				captureMove.capturedPiece = P;
				
				// Act
				string normalMoveStr = toMoveString(normalMove);
				string captureMoveStr = toMoveString(captureMove);

				// Assert
				Logger::WriteMessage(normalMoveStr.c_str());
				Logger::WriteMessage(captureMoveStr.c_str());
				Assert::AreEqual<string>("Ra1h8", normalMoveStr);
				Assert::AreEqual<string>("Qa1xh8", captureMoveStr);
			}
		};
	}
}