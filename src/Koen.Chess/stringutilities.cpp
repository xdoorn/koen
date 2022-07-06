#include "pch.h"
#include "stringutilities.h"


vector<string> split(const string& i_string, const string& i_separator, bool i_shouldTrimValue)
{
	vector<string> words;

	string str = i_string;
	int index = -1;
	do
	{
		index = str.find(i_separator);

		if (index >= 0)
		{
			string left = str.substr(0, index);
			if (i_shouldTrimValue)
			{
				left = trim(left);
			}

			words.push_back(left);
			str = str.erase(0, index + i_separator.size());
		}
	} while (index >= 0);

	if (i_shouldTrimValue)
	{
		str = trim(str);
	}

	words.push_back(str);

	return words;
}


string ltrim(const string& i_string)
{
	size_t start = i_string.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : i_string.substr(start);
}


string rtrim(const string& i_string)
{
	size_t end = i_string.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : i_string.substr(0, end + 1);
}


string trim(const string& i_string) 
{
	return rtrim(ltrim(i_string));
}


wstring toWString(const string& i_string)
{
	return wstring(i_string.begin(), i_string.end());
}


bool startsWith(const string& i_string, const string& i_subString)
{
	return i_string.compare(0, i_subString.size(), i_subString) == 0;
}