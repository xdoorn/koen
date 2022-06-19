/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../Koen.Chess/bitmask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Koen {
	namespace UnitTest
	{
		TEST_CLASS(BitMaskTest)
		{
		public:

			TEST_METHOD(test_BIT_SET)
			{
				// Arrange
				BITMASK bitmask = 0x0;
				
				// Act
				BIT_SET(bitmask, 0);
				BIT_SET(bitmask, 1);
				BIT_SET(bitmask, 2);
				BIT_SET(bitmask, 3);
				BIT_SET(bitmask, 4);
				BIT_SET(bitmask, 5);
				BIT_SET(bitmask, 6);
				BIT_SET(bitmask, 7);
				BITMASK_SET(bitmask, 0xFF00000000000000);

				Logger::WriteMessage(toBitMask2DString(bitmask).c_str());

				// Assert
				Assert::AreEqual<BITMASK>(0xFF000000000000FF, bitmask);
			}


			TEST_METHOD(test_BIT_CLEAR)
			{
				// Arrange
				BITMASK bitmask = bm_full;

				// Act
				BIT_CLEAR(bitmask, 0);
				BIT_CLEAR(bitmask, 1);
				BIT_CLEAR(bitmask, 2);
				BIT_CLEAR(bitmask, 3);
				BIT_CLEAR(bitmask, 4);
				BIT_CLEAR(bitmask, 5);
				BIT_CLEAR(bitmask, 6);
				BIT_CLEAR(bitmask, 7);
				BITMASK_CLEAR(bitmask, 0xFF00000000000000);

				Logger::WriteMessage(toBitMask2DString(bitmask).c_str());

				// Assert
				Assert::AreEqual<BITMASK>(0x00FFFFFFFFFFFF00, bitmask);
			}


			TEST_METHOD(test_BIT_FLIP)
			{
				// Arrange
				BITMASK bitmask = 0x0FFFFFFFFFFFFFFF;

				// Act
				BIT_FLIP(bitmask, 0);
				BIT_FLIP(bitmask, 1);
				BIT_FLIP(bitmask, 2);
				BIT_FLIP(bitmask, 3);
				BIT_FLIP(bitmask, 4);
				BIT_FLIP(bitmask, 5);
				BIT_FLIP(bitmask, 6);
				BIT_FLIP(bitmask, 7);
				BITMASK_FLIP(bitmask, 0xFF00000000000000);

				Logger::WriteMessage(toBitMask2DString(bitmask).c_str());

				// Assert
				Assert::AreEqual<BITMASK>(0xF0FFFFFFFFFFFF00, bitmask);
			}


			TEST_METHOD(test_BIT_CHECK)
			{
				// Arrange
				BITMASK bitmask = bm_camp[B];
				Logger::WriteMessage(toBitMask2DString(bitmask).c_str());

				// Assert BIT_CHECK
				Assert::IsFalse(BIT_CHECK(bitmask, A1), L"BIT_CHECK A1 = FALSE");
				Assert::IsFalse(BIT_CHECK(bitmask, H1), L"BIT_CHECK H1 = FALSE");
				Assert::IsFalse(BIT_CHECK(bitmask, A4), L"BIT_CHECK A4 = FALSE");
				Assert::IsFalse(BIT_CHECK(bitmask, H4), L"BIT_CHECK H4 = FALSE");
				Assert::IsTrue(BIT_CHECK(bitmask, A5), L"BIT_CHECK A5 = TRUE");
				Assert::IsTrue(BIT_CHECK(bitmask, H5), L"BIT_CHECK H5 = TRUE");
				Assert::IsTrue(BIT_CHECK(bitmask, A8), L"BIT_CHECK A8 = TRUE");
				Assert::IsTrue(BIT_CHECK(bitmask, H8), L"BIT_CHECK H8 = TRUE");

				// Assert BITMASK_CHECK_ALL
				Assert::IsFalse(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_1]), L"BITMASK_CHECK_ALL 1th rank = FALSE");
				Assert::IsFalse(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_2]), L"BITMASK_CHECK_ALL 2th rank = FALSE");
				Assert::IsFalse(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_3]), L"BITMASK_CHECK_ALL 3th rank = FALSE");
				Assert::IsFalse(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_4]), L"BITMASK_CHECK_ALL 4th rank = FALSE");				
				Assert::IsFalse(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_1] | bm_rank[RANK_8]), L"BITMASK_CHECK_ALL 1th and 8th rank = FALSE");
				Assert::IsTrue(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_5]), L"BITMASK_CHECK_ALL 5th rank = TRUE");
				Assert::IsTrue(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_6]), L"BITMASK_CHECK_ALL 6th rank = TRUE");
				Assert::IsTrue(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_7]), L"BITMASK_CHECK_ALL 7th rank = TRUE");
				Assert::IsTrue(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_8]), L"BITMASK_CHECK_ALL 8th rank = TRUE");
				Assert::IsTrue(BITMASK_CHECK_ALL(bitmask, bm_rank[RANK_7] | bm_rank[RANK_8]), L"BITMASK_CHECK_ALL 7th and 8th rank = TRUE");

				// Assert 
				Assert::IsFalse(BITMASK_CHECK_ANY(bitmask, bm_rank[RANK_1]), L"BITMASK_CHECK_ANY 1th rank = FALSE");
				Assert::IsTrue(BITMASK_CHECK_ANY(bitmask, bm_file[FILE_A] | bm_rank[RANK_1]), L"BITMASK_CHECK_ANY A file and 1th rank = TRUE");
			}


			TEST_METHOD(test_bm_file)
			{
				// Arrange
				BITMASK bitmask[64] = {};

				for (int f = 0; f < 8; ++f)
				{
					// Act
					for (int r = 0; r < 8; ++r)
					{
						BIT_SET(bitmask[f], f + (r * 8));
					}

					// Assert
					Assert::AreEqual<BITMASK>(bitmask[f % 8], bm_file[f]);
				}
			}


			TEST_METHOD(test_bm_squares)
			{ 
				// Arrange
				BITMASK bitmask[64] = { 0 };
				BITMASK xbitmask[64] = { 0 };

				// Act
				for (int s = 0; s < 64; ++s)
				{
					BIT_SET(bitmask[s], s);

					xbitmask[s] = bm_full;
					BIT_CLEAR(xbitmask[s], s);
				}

				Logger::WriteMessage(toBitMaskArrayVariable(bitmask, "bm_squares").c_str());
				Logger::WriteMessage("\n\n");
				Logger::WriteMessage(toBitMaskArrayVariable(xbitmask, "bm_xsquares").c_str());
			}


			TEST_METHOD(test_bm_kingmoves)
			{
				// Arrange
				BITMASK kingmoves[64];

				for (int s = 0; s < 64; ++s)
				{
					kingmoves[s] = 0;

					// Act
					BITMASK kingsquare = bm_squares[s];
				  if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_8] | bm_file[FILE_A]))
					{
						kingmoves[s] |= kingsquare >> 9; // NW
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_8]))
					{
						kingmoves[s] |= kingsquare >> 8; // North
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_8] | bm_file[FILE_H]))
					{
						kingmoves[s] |= kingsquare >> 7; // NE
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_file[FILE_H]))
					{
						kingmoves[s] |= kingsquare << 1; // E
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_1] | bm_file[FILE_H]))
					{
						kingmoves[s] |= kingsquare << 9; // SE
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_1]))
					{
						kingmoves[s] |= kingsquare << 8; // S
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_rank[RANK_1] | bm_file[FILE_A]))
					{
						kingmoves[s] |= kingsquare << 7; // SW
					}
					if (!BITMASK_CHECK_ANY(kingsquare, bm_file[FILE_A]))
					{
						kingmoves[s] |= kingsquare >> 1; // W
					}

					// Assert
					Assert::AreEqual(kingmoves[s], bm_kingmoves[s]);
				}

				Logger::WriteMessage(toBitMaskArrayVariable(kingmoves, "bm_kingmoves").c_str());
			}
		};
	}
}
