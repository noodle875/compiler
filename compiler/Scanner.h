#pragma once
#include <vector>
#include "Token.h"

using namespace std;

enum class CharType {
	Unknown,
	WhiteSpace,
	NumberLiteral,
	StringLiteral,
	IdentifierAndKeyword,
	OperatorAndPunctuator
};

auto scan(string) -> vector<Token>;
