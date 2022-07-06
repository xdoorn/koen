#pragma once


BitBoard arrangeBitBoard(string i_setupExpression);
string assertMoves(BitBoard i_bitBoard, vector<Move> i_moves, string i_expectedMovesExpression);
void assertGenerateMoves(string i_expression);