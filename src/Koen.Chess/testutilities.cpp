#include "pch.h"
#include "CppUnitTest.h"
#include "generate.h"
#include "bitboard.h"
#include "stringutilities.h"
#include "testutilities.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


BitBoard arrangeBitBoard(string i_setupExpression)
{
	BitBoard bitboard;
	clearBitBoard(bitboard);

	for (auto item : split(i_setupExpression))
	{
		if (item == "W" || item == "B")
		{
			if (item == "B")
			{
				bitboard.side = B;
				bitboard.xside = W;
			}
		}
		else
		{
			int c = colorSymbolToInteger[(int)item[0] - 'A'];
			int p = pieceSymbolToInteger[(int)item[0] - 'A'];

			for (int i = 0; i <= item.size() / 2; i += 2)
			{
				int file = item[i + 1] - 'a';
				int rank = 7 - (item[i + 2] - '1');
				int s = (rank * 8) + file;

				if (p != 9)
				{
					BIT_SET(bitboard.pieces[c][p], s);
				}

				BIT_SET(bitboard.army[c], s);
				BIT_SET(bitboard.occupied, s);
				BIT_CLEAR(bitboard.xoccupied, s);
			}
		}
	}

	return bitboard;
}


string assertMoves(BitBoard i_bitBoard, vector<Move> i_moves, string i_expectedMovesExpression)
{
	for (string expectedMove : split(i_expectedMovesExpression))
	{
		bool hasNotOperator = startsWith(expectedMove, "!");
		string compareMoveString = (hasNotOperator) ? expectedMove.substr(1) : expectedMove;

		bool hasFound = false;
		for (Move move : i_moves)
		{
			string moveToString = toMoveString(move).substr(2, 2);
			
			if (compareMoveString == moveToString)
			{
				hasFound = true;
				break;
			}
		}

		if ((hasFound && hasNotOperator) || !hasFound && !hasNotOperator)
		{
			return "Assert move failed: " + expectedMove;
		}
	}

	return "";
}


void assertGenerateMoves(string i_expression)
{
	vector<string> leftRight = split(i_expression, "=>");
	string setupExpression = trim(leftRight.at(0));
	string expectedMovesExpression = trim(leftRight.at(1));
	
	// Arrange
	BitBoard bitboard = arrangeBitBoard(setupExpression);

	Logger::WriteMessage("\n\n");
	Logger::WriteMessage(toBitBoard2DString(bitboard).c_str());
	Logger::WriteMessage("\n\n");

	// Act
	vector<Move> moves = generateMoves(bitboard);

	// Assert
	string error = assertMoves(bitboard, moves, expectedMovesExpression);	
	if (error != "")
	{
		error += " for '" + i_expression + "'";
		Assert::Fail(toWString(error).c_str());
	}
}