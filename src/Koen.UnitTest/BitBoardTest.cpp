/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../Koen.Chess/bitboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Koen {
	namespace UnitTest
	{
		TEST_CLASS(BitBoardTest)
		{
		public:
			TEST_METHOD(test_ClearBitBoard)
			{
				BitBoard bitBoard;
				
				clearBitBoard(bitBoard);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][P]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][N]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][B]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][R]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][Q]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[W][K]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][P]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][N]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][B]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][R]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][Q]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.pieces[B][K]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.army[W]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.army[B]);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.castle);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.enpassant);
				Assert::AreEqual<BITMASK>(bm_empty, bitBoard.occupied);
				Assert::AreEqual<BITMASK>(bm_full, bitBoard.xoccupied);
			}


			TEST_METHOD(test_BitBoardFenConversionVisaVersa)
			{
				// Arrange
				BitBoard bitBoard;
				string expectedFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

				// Act
				fenToBitBoard(expectedFen, bitBoard);
				string actualFen = bitBoardToFen(bitBoard);

				// Assert
				Logger::WriteMessage(actualFen.c_str());
				Assert::AreEqual(expectedFen, actualFen);
			}
		};
	}
}
