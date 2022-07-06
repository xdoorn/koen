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
		TEST_CLASS(StringUtilitiesTest)
		{
		public:

			TEST_METHOD(test_Split)
			{
				// Act
				auto defaultTrimmedSplitted = split("ab => cd => ef", "=>");
				auto trimmedSplitted = split("ab => cd => ef", "=>", true);
				auto notTrimmedSplitted = split("ab => cd => ef", "=>", false);

				// Assert
				Assert::AreEqual<string>("ab", defaultTrimmedSplitted.at(0));
				Assert::AreEqual<string>("cd", defaultTrimmedSplitted.at(1));
				Assert::AreEqual<string>("ef", defaultTrimmedSplitted.at(2));
				Assert::AreEqual<string>("ab", trimmedSplitted.at(0));
				Assert::AreEqual<string>("cd", trimmedSplitted.at(1));
				Assert::AreEqual<string>("ef", trimmedSplitted.at(2));
				Assert::AreEqual<string>("ab ", notTrimmedSplitted.at(0));
				Assert::AreEqual<string>(" cd ", notTrimmedSplitted.at(1));
				Assert::AreEqual<string>(" ef", notTrimmedSplitted.at(2));
			}


			TEST_METHOD(test_Trim)
			{
				// Act
				string leftTrimmed = ltrim(" a b ");
				string rightTrimmed = rtrim(" a b ");
				string trimmed = trim(" a b ");

				// Assert
				Assert::AreEqual<string>("a b ", leftTrimmed);
				Assert::AreEqual<string>(" a b", rightTrimmed);
				Assert::AreEqual<string>("a b", trimmed);
			}


			TEST_METHOD(test_ToWString)
			{
				// Act
				wstring wstr = toWString("abcDEF20!@#$%^&*()");

				// Assert
				Assert::AreEqual<wstring>(L"abcDEF20!@#$%^&*()", wstr);
			}


			TEST_METHOD(test_StartsWith)
			{
				// Act
				bool isTrue = startsWith("!e4", "!");
				bool isFalse = startsWith("e4", "!");

				// Assert
				Assert::AreEqual<bool>(true, isTrue);
				Assert::AreEqual<bool>(false, isFalse);
			}
		};
	}
}