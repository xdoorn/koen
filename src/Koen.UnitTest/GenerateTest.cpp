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
						.act("Ke1xd1").assertIllegal("Illegal king move capturing friendly rook on d1")
						.act("Ke1xf1").assertIllegal("Illegal king move capturing friendly rook on f1");

				// Test King can castle. 
				// TODO: CASTLE - check is not considered yet!!
				// TODO: CASTLE - attacked squares aren't considered yet!!
				TestMoveGeneration::create()
					.arrange("8/8/8/8/8/8/8/R3K2R w KQkq - 0 1")
						.act("0-0-0").assertLegal("8/8/8/8/8/8/8/2KR3R b kq - 1 1", "Legal white castles long")
						.act("0-0").assertLegal("8/8/8/8/8/8/8/R4RK1 b kq - 1 1", "Legal white castles short")
						.act("Ra1a8").assertLegal("R7/8/8/8/8/8/8/4K2R b Kkq - 1 1", "Clear castle long permission because rook had moved.")
						.act("Rh1h8").assertLegal("7R/8/8/8/8/8/8/R3K3 b Qkq - 1 1", "Clear castle short permission because rook had moved.")
					.arrange("8/8/8/8/8/8/8/R2BKB1R w KQ - 0 1")
						.act("Ke1b1").assertIllegal("Illegal white castles long because d1 is blocked")
						.act("Ke1g1").assertIllegal("Illegal white castles long because f1 is blocked");

				// Test knight moves.
				TestMoveGeneration::create()
					.arrange("8/8/5q2/3N4/8/2R5/8/8 w - - 0 1")
					.act("Nd5e7").assertLegal("8/4N3/5q2/8/8/2R5/8/8 b - - 1 1", "Legal knight move to north-north-east")
				  .act("Nd5xf6").assertLegal("8/8/5N2/8/8/2R5/8/8 b - - 0 1", "Legal knight move to capture north-east-east")
					.act("Nd5f4").assertLegal("8/8/5q2/8/5N2/2R5/8/8 b - - 1 1", "Legal knight move to south-east-east")
					.act("Nd5e3").assertLegal("8/8/5q2/8/8/2R1N3/8/8 b - - 1 1", "Legal knight move to sourth-south-east")
					.act("Nd5c3").assertIllegal("Illegal knight move to capture friendly rook to south-south-west")
					.act("Nd5b4").assertLegal("8/8/5q2/8/1N6/2R5/8/8 b - - 1 1", "Legal knight move to south-west-west")
					.act("Nd5b6").assertLegal("8/8/1N3q2/8/8/2R5/8/8 b - - 1 1", "Legal knight move to north-west-west")
					.act("Nd5c7").assertLegal("8/2N5/5q2/8/8/2R5/8/8 b - - 1 1", "Legal knight move to north-west");

				// Test bishop moves.
				TestMoveGeneration::create()
					.arrange("8/1R6/8/3B4/8/5r2/8/8 w - - 0 1")
					.act("Bd5d6").assertIllegal("Illegal bishop cannot move to north like rook or queen")
					.act("Bd5e6").assertLegal("8/1R6/4B3/8/8/5r2/8/8 b - - 1 1", "Legal bishop move to north-east (1)")
					.act("Bd5f7").assertLegal("8/1R3B2/8/8/8/5r2/8/8 b - - 1 1", "Legal bishop move to north-east (2)")
					.act("Bd5g8").assertLegal("6B1/1R6/8/8/8/5r2/8/8 b - - 1 1", "Legal bishop move to north-east (3)")
					.act("Bd5e5").assertIllegal("Illegal bishop cannot move to east like rook or queen")
					.act("Bd5e4").assertLegal("8/1R6/8/8/4B3/5r2/8/8 b - - 1 1", "Legal bishop move to south-east (1)")
					.act("Bd5xf3").assertLegal("8/1R6/8/8/8/5B2/8/8 b - - 0 1", "Legal bishop move to capture south-east (2)")
					.act("Bd5g2").assertIllegal("Illegal bishop cannot jump to south-east (3)")
					.act("Bd5h1").assertIllegal("Illegal bishop cannot jump to south-east (4)")
					.act("Bd5d4").assertIllegal("Illegal bishop cannot move to south like rook or queen")
					.act("Bd5c4").assertLegal("8/1R6/8/8/2B5/5r2/8/8 b - - 1 1", "Legal bishop move to south-west (1)")
					.act("Bd5b3").assertLegal("8/1R6/8/8/8/1B3r2/8/8 b - - 1 1", "Legal bishop move to south-west (2)")
					.act("Bd5a2").assertLegal("8/1R6/8/8/8/5r2/B7/8 b - - 1 1", "Legal bishop move to south-west (3)")
					.act("Bd5c5").assertIllegal("Illegal bishop cannot move to west like rook or queen")
					.act("Bd5c6").assertLegal("8/1R6/2B5/8/8/5r2/8/8 b - - 1 1", "Legal bishop move to north-west (1)")
					.act("Bd5b7").assertIllegal("Illegal bishop cannot capture firendly rook to north-west (2)")
					.act("Bd5a8").assertIllegal("Illegal rook cannot jump to north-west (3)");

				// Test rook moves
				TestMoveGeneration::create()
					.arrange("8/3r4/8/3R4/8/8/3B4/8 w - - 0 1")
						.act("Rd5d6").assertLegal("8/3r4/3R4/8/8/8/3B4/8 b - - 1 1", "Legal rook move to north (1)")
						.act("Rd5xd7").assertLegal("8/3R4/8/8/8/8/3B4/8 b - - 0 1", "Legal rook move to capture north (2)")
						.act("Rd5d8").assertIllegal("Illegal rook cannot jump to north (3)")
						.act("Rd5e6").assertIllegal("Illegal rook cannot move to north-east like bishop or queen")
						.act("Rd5e5").assertLegal("8/3r4/8/4R3/8/8/3B4/8 b - - 1 1", "Legal rook move to east (1)")
						.act("Rd5f5").assertLegal("8/3r4/8/5R2/8/8/3B4/8 b - - 1 1", "Legal rook move to east (2)")
						.act("Rd5g5").assertLegal("8/3r4/8/6R1/8/8/3B4/8 b - - 1 1", "Legal rook move to east (3)")
						.act("Rd5h5").assertLegal("8/3r4/8/7R/8/8/3B4/8 b - - 1 1", "Legal rook move to east (4)")
						.act("Rd5e4").assertIllegal("Illegal rook cannot move to south-east like bishop or queen")
						.act("Rd5d4").assertLegal("8/3r4/8/8/3R4/8/3B4/8 b - - 1 1", "Legal rook move to south (1)")
						.act("Rd5d3").assertLegal("8/3r4/8/8/8/3R4/3B4/8 b - - 1 1", "Legal rook move to south (2)")
						.act("Rd5d2").assertIllegal("Illegal rook cannot capture own bishop to south (3)")
						.act("Rd5d1").assertIllegal("Illegal rook cannot jump to south (4)")
						.act("Rd5f4").assertIllegal("Illegal rook cannot move to south-west like bishop or queen")
						.act("Rd5c5").assertLegal("8/3r4/8/2R5/8/8/3B4/8 b - - 1 1", "Legal rook move to west (1)")
						.act("Rd5b5").assertLegal("8/3r4/8/1R6/8/8/3B4/8 b - - 1 1", "Legal rook move to west (2)")
						.act("Rd5a5").assertLegal("8/3r4/8/R7/8/8/3B4/8 b - - 1 1", "Legal rook move to west (3)")
						.act("Rd5f6").assertIllegal("Illegal rook cannot move to north-west like bishop or queen");

				// Test queen moves
				TestMoveGeneration::create()
					.arrange("8/1R1b4/8/1B1Q2B1/8/5r2/3Q4/8 w - - 0 1")
					.act("Qd5d6").assertLegal("8/1R1b4/3Q4/1B4B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to north (1)")
					.act("Qd5xd7").assertLegal("8/1R1Q4/8/1B4B1/8/5r2/3Q4/8 b - - 0 1", "Legal Qd5 move to capture north (2)")
					.act("Qd5d8").assertIllegal("Illegal Qd5 cannot jumb north (3)")
					.act("Qd5e6").assertLegal("8/1R1b4/4Q3/1B4B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to north-east (1)")
					.act("Qd5f7").assertLegal("8/1R1b1Q2/8/1B4B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to north-east (2)")
					.act("Qd5g8").assertLegal("6Q1/1R1b4/8/1B4B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to north-east (3)")
					.act("Qd5e5").assertLegal("8/1R1b4/8/1B2Q1B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to east (1)")
					.act("Qd5f5").assertLegal("8/1R1b4/8/1B3QB1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to east (2)")
					.act("Qd5g5").assertIllegal("Illegal Qd5 cannot capture friendly bishop to east (3)")
					.act("Qd5h5").assertIllegal("Illegal Qd5 cannot jump to east (4)")
				  .act("Qd5e4").assertLegal("8/1R1b4/8/1B4B1/4Q3/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to south-east (1)")
				  .act("Qd5xf3").assertLegal("8/1R1b4/8/1B4B1/8/5Q2/3Q4/8 b - - 0 1", "Legal Qd5 move to capture south-east (2)")
				  .act("Qd5g2").assertIllegal("Illegal Qd5 cannot jump to south-east (3)")
				  .act("Qd5h1").assertIllegal("Illegal Qd5 cannot jump to south-east (4)")
					.act("Qd5d4").assertLegal("8/1R1b4/8/1B4B1/3Q4/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to south (1)")
					.act("Qd5d3").assertLegal("8/1R1b4/8/1B4B1/8/3Q1r2/3Q4/8 b - - 1 1", "Legal Qd5 move to south (2)")
					.act("Qd5d2").assertIllegal("Illegal Qd5 cannot capture frienldy queen to south (3)")
					.act("Qd5d1").assertIllegal("Illegal Qd5 cannot jump to south (4)")
					.act("Qd5c4").assertLegal("8/1R1b4/8/1B4B1/2Q5/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to south-west (1)")
					.act("Qd5b3").assertLegal("8/1R1b4/8/1B4B1/8/1Q3r2/3Q4/8 b - - 1 1", "Legal Qd5 move to south-west (2)")
					.act("Qd5a2").assertLegal("8/1R1b4/8/1B4B1/8/5r2/Q2Q4/8 b - - 1 1", "Legal Qd5 move to south-west (3)")
					.act("Qd5c5").assertLegal("8/1R1b4/8/1BQ3B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to west (1)")
					.act("Qd5b5").assertIllegal("Illegal Qd5 move cannot capture friendly bishop to west (2)")
					.act("Qd5a5").assertIllegal("Illegal Qd5 cannot jump to west (3)")
					.act("Qd5c6").assertLegal("8/1R1b4/2Q5/1B4B1/8/5r2/3Q4/8 b - - 1 1", "Legal Qd5 move to north-west (1)")
					.act("Qd5b7").assertIllegal("Illegal Qd5 cannot capture friendly rook to north-west (2)")
					.act("Qd5a8").assertIllegal("Illegal Qd5 cannot jump to north-west (2)")
					.act("Qd2d4").assertLegal("8/1R1b4/8/1B1Q2B1/3Q4/5r2/8/8 b - - 1 1", "Legal Qd2 move to north (2); which tests iterating two second queen.");
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