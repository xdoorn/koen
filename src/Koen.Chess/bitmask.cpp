/***********************************\
 *                                 *
 *  Koen © 2022, Xander van Doorn  *
 *                                 *
\***********************************/

#include "pch.h"
#include "bitmask.h"
#include <format>


string toBitMaskHexString(BITMASK i_bitmask)
{
  return format("0x{:0>16X}", i_bitmask);
}


string toBitMask2DString(BITMASK i_bitmask, bool i_includeHexValue)
{
  string result = "";

  for (int s = 0; s < 64; s++)
  {
    int file = s % 8;
    int rank = 8 - (s / 8);
    
    if (file == FILE_A)
    {
      result += std::to_string(rank);
      result += "|";
    }

    if (BIT_CHECK(i_bitmask, s))
    {
      result += " 1";
    }
    else
    {
      result += " 0";
    }

    if (i_includeHexValue && rank == RANK_4 && file == FILE_H)
    {
      result += "\t\t" + toBitMaskHexString(i_bitmask);
    }

    if (file == FILE_H)
    {
      result += "\n";
    }
  }

  result += "  ----------------\n";
  result += "   a b c d e f g h";

  return result;
}


string toBitMaskArrayVariable(BITMASK i_bitmask[64], string i_variableName)
{
  string result = "const BITMASK ";
  result += i_variableName;
  result += "[64] =\n{\n";

  for (int s = 0; s < 64; ++s)
  {
    if (s % 8 == 0)
    {
      result += "  ";
    }

    result += toBitMaskHexString(i_bitmask[s]) + ", ";

    if (s % 8 == 7)
    {
      result += "\n";
    }
  }

  result += "};";

  return result;
}