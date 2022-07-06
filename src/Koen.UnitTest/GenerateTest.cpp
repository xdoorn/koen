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
				assertGenerateMoves("B ke1 xd1f1 => d2 e2 f2 !d1 !f1");
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