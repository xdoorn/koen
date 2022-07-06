#pragma once

#include <string>
#include <vector>

using namespace std;

const string WHITESPACE = " \n\r\t\f\v";


vector<string> split(const string& i_string, const string& i_separator = " ", bool i_shouldTrimValue = true);
string ltrim(const string& i_string);
string rtrim(const string& i_string);
string trim(const string& i_string);
wstring toWString(const string& i_string);
bool startsWith(const string& i_string, const string& i_subString);