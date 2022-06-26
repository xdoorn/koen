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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Koen {
	namespace UnitTest
	{
		TEST_CLASS(GenerateTest)
		{
		public:

			// Expressions:
			// "W Ke1 Rd1f1 => d2 e2 f2"
			void assertGenerateMoves(string i_expression)
			{
				BitBoard bitboard;
				clearBitBoard(bitboard);

				vector<string> leftRight = split(i_expression, "=>");
				string left = trim(leftRight.at(0));
				string right = trim(leftRight.at(1));

				for (auto leftItem : split(left))
				{
					if (leftItem == "W" || leftItem == "B")
					{
						if (leftItem == "B")
						{
							bitboard.side = B;
							bitboard.xside = W;
						}
					}
					else
					{
						int c = colorSymbolToInteger[(int) leftItem[0] - 'A'];
						int p = pieceSymbolToInteger[(int) leftItem[0] - 'A'];

						for (int i = 0; i <= leftItem.size() / 2; i += 2)
						{
							int file = leftItem[i + 1] - 'a';
							int rank = 7 - (leftItem[i + 2] - '1');
							int s = (rank * 8) + file;

							BIT_SET(bitboard.pieces[c][p], s);
							BIT_SET(bitboard.army[c], s);
							BIT_SET(bitboard.occupied, s);
							BIT_CLEAR(bitboard.xoccupied, s);
						}
					}
				}

				Logger::WriteMessage("\n\n");
				Logger::WriteMessage(toBitBoard2DString(bitboard).c_str());
				Logger::WriteMessage("\n\n");

				vector<Move> moves = generateMoves(bitboard);

				for (string rightItem : split(right))
				{
					bool hasFound = false;
					
					for (Move move : moves)
					{
						string toString = toMoveString(move).substr(2, 2);
						if (rightItem == toString)
						{
							hasFound = true;
							break;
						}
					}

					wstring error = toWString("Move to '" + rightItem + "' was not generated!");
					Assert::IsTrue(hasFound, error.c_str());
				}
			}


			TEST_METHOD(test_Generate)
			{
				assertGenerateMoves("Ke1 Rd1f1 => d2 e2 f2");
				assertGenerateMoves("B ke1 rd1f1 => d2 e2 f2");
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