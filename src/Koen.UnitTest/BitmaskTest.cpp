/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../Koen.Chess/bitmask.h"
#include <vector>

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


			TEST_METHOD(test_bitScan)
			{
				// Arrange
				BITMASK bm = bm_camp[W];

				// Act
				while (bm)
				{
					int s = bitScan(bm);
					BIT_CLEAR(bm, s);

					// Assert
					Assert::IsTrue(s >= A4 && s <= H1);
				}
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

			
			TEST_METHOD(test_bm_rangemoves)
			{
				// Arrange
				BITMASK north_moves[64];
				BITMASK northeast_moves[64];
				BITMASK east_moves[64];
				BITMASK southeast_moves[64];
				BITMASK south_moves[64];
				BITMASK southwest_moves[64];
				BITMASK west_moves[64];
				BITMASK northwest_moves[64];

				for (int s = 0; s < 64; ++s)
				{
					int file = s % 8;
					int rank = s / 8;

					// Act North direction
					north_moves[s] = bm_empty;
					for (int n = 1; n <= rank; ++n)
					{
						BIT_SET(north_moves[s], s - (n * 8));
					}

					// Act North East direction
					northeast_moves[s] = bm_empty;
					for (int ne = 1; ne <= min(7 - file, rank); ++ne)
					{
						BIT_SET(northeast_moves[s], s - (ne * 7));
					}

					// Act East direction
					east_moves[s] = bm_empty;
					for (int e = 1; e <= 7 - file; ++e)
					{
						BIT_SET(east_moves[s], s + (e * 1));
					}

					// Act South East direction
					southeast_moves[s] = bm_empty;
					for (int se = 1; se <= min(7 - file, 7 - rank); ++se)
					{
						BIT_SET(southeast_moves[s], s + (se * 9));
					}

					// Act South direction
					south_moves[s] = bm_empty;
					for (int n = 1; n <= (7 - rank); ++n)
					{
						BIT_SET(south_moves[s], s + (n * 8));
					}

					// Act South West direction
					southwest_moves[s] = bm_empty;
					for (int sw = 1; sw <= min(file, 7 - rank); ++sw)
					{
						BIT_SET(southwest_moves[s], s + (sw * 7));
					}

					// Act West direction
					west_moves[s] = bm_empty;
					for (int w = 1; w <= file; ++w)
					{
						BIT_SET(west_moves[s], s - (w * 1));
					}

					// Act North West direction
					northwest_moves[s] = bm_empty;
					for (int nw = 1; nw <= min(file, rank); ++nw)
					{
						BIT_SET(northwest_moves[s], s - (nw * 9));
					}

					BITMASK queenmove = bm_empty;
					queenmove ^= north_moves[s] ^ northeast_moves[s] ^ east_moves[s] ^ southeast_moves[s];
					queenmove ^= south_moves[s] ^ southwest_moves[s] ^ west_moves[s] ^ northwest_moves[s];
					Logger::WriteMessage("\n\n");
					Logger::WriteMessage(toBitMask2DString(queenmove).c_str());

					Assert::AreEqual<BITMASK>(north_moves[s], bm_rangemoves[NORTH][s]);
					Assert::AreEqual<BITMASK>(northeast_moves[s], bm_rangemoves[NORTHEAST][s]);
					Assert::AreEqual<BITMASK>(east_moves[s], bm_rangemoves[EAST][s]);
					Assert::AreEqual<BITMASK>(southeast_moves[s], bm_rangemoves[SOUTHEAST][s]);
					Assert::AreEqual<BITMASK>(south_moves[s], bm_rangemoves[SOUTH][s]);
					Assert::AreEqual<BITMASK>(southwest_moves[s], bm_rangemoves[SOUTHWEST][s]);
					Assert::AreEqual<BITMASK>(west_moves[s], bm_rangemoves[WEST][s]);
					Assert::AreEqual<BITMASK>(northwest_moves[s], bm_rangemoves[NORTHWEST][s]);
				}

				Logger::WriteMessage(toBitMaskArrayVariable(north_moves, "bm_rangemoves[NORTH]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(northeast_moves, "bm_rangemoves[NORTHEAST]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(east_moves, "bm_rangemoves[EAST]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(southeast_moves, "bm_rangemoves[SOUTHEAST]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(south_moves, "bm_rangemoves[SOUTH]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(southwest_moves, "bm_rangemoves[SOUTHWEST]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(west_moves, "bm_rangemoves[WEST]").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(northwest_moves, "bm_rangemoves[NORTHWEST]").c_str());
			}


			TEST_METHOD(test_bm_castle)
			{
				// Arrange
				BITMASK castle[64] = { 0 };
				BITMASK castle_rook_flip[64] = { 0 };

				for (int s = 0; s < 64; ++s)
				{
					castle[s] = 0;
					castle_rook_flip[s] = 0;
				}

				BIT_SET(castle[0], B1);
				BIT_SET(castle[0], C1);
				BIT_SET(castle[0], D1);
				BIT_SET(castle[1], F1);
				BIT_SET(castle[1], G1);
				BIT_SET(castle[2], B8);
				BIT_SET(castle[2], C8);
				BIT_SET(castle[2], D8);
				BIT_SET(castle[3], F8);
				BIT_SET(castle[3], G8);

				BIT_SET(castle_rook_flip[C1], A1);
				BIT_SET(castle_rook_flip[C1], D1);
				BIT_SET(castle_rook_flip[G1], F1);
				BIT_SET(castle_rook_flip[G1], H1);
				BIT_SET(castle_rook_flip[C8], A8);
				BIT_SET(castle_rook_flip[C8], D8);
				BIT_SET(castle_rook_flip[G8], F8);
				BIT_SET(castle_rook_flip[G8], H8);
				
				Logger::WriteMessage(toBitMaskArrayVariable(castle, "bm_castle").c_str());
				Logger::WriteMessage(toBitMaskArrayVariable(castle_rook_flip, "bm_castle_rook_flip").c_str());

				// Assert
				Assert::AreEqual<BITMASK>(castle[0], bm_castle[W][CASTLE_LONG]);
				Assert::AreEqual<BITMASK>(castle[1], bm_castle[W][CASTLE_SHORT]);
				Assert::AreEqual<BITMASK>(castle[2], bm_castle[B][CASTLE_LONG]);
				Assert::AreEqual<BITMASK>(castle[3], bm_castle[B][CASTLE_SHORT]);
				Assert::AreEqual<BITMASK>(castle_rook_flip[C1], bm_castle_rook_flip[C1]);
				Assert::AreEqual<BITMASK>(castle_rook_flip[G1], bm_castle_rook_flip[G1]);
				Assert::AreEqual<BITMASK>(castle_rook_flip[C8], bm_castle_rook_flip[C8]);
				Assert::AreEqual<BITMASK>(castle_rook_flip[G8], bm_castle_rook_flip[G8]);
			}
		};
	}
}
