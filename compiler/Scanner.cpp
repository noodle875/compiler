#pragma once

#include "Scanner.h"
#include "Token.h"

#include <iostream>

static string::iterator current;

auto isCharType(char c, CharType type) -> bool
{
	switch (type) {
	case CharType::NumberLiteral:
		return '0' <= c && c <= '9';
	case CharType::StringLiteral:
		return 32 <= c && c <= 126 && c != '\'';
	case CharType::IdentifierAndKeyword:
		return '0' <= c && c <= '9' ||
			'a' <= c && c <= 'z' ||
			'A' <= c && c <= 'Z';
	case CharType::OperatorAndPunctuator:
		return 33 <= c && c <= 47 ||
			58 <= c && c <= 64 ||
			91 <= c && c <= 96 ||
			123 <= c && c <= 126;
	default:
		return false;
	}
}

auto getCharType(char c) -> CharType
{
	if (' ' == c || '\t' == c || '\r' == c || '\n' == c)
		return CharType::WhiteSpace;
	if ('0' <= c && c <= '9')
		return CharType::NumberLiteral;
	if (c == '\'')
		return CharType::StringLiteral;
	if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')
		return CharType::IdentifierAndKeyword;
	if (33 <= c && c <= 47 && c != '\'' ||
		58 <= c && c <= 64 ||
		91 <= c && c <= 96 ||
		123 <= c && c <= 126)
		return CharType::OperatorAndPunctuator;
	return CharType::Unknown;
}



auto scanNumberLiteral() -> Token
{
	string string;
	while (isCharType(*current, CharType::NumberLiteral))
		string += *current++;
	if (*current == '.')
	{
		string += *current++;
		while (isCharType(*current, CharType::NumberLiteral))
			string += *current++;
	}
	return Token{ Kind::NumberLiteral,string };
}


auto scanStringLiteral() -> Token
{
	string string;
	current++;
	while (isCharType(*current, CharType::StringLiteral))
		string += *current++;
	if (*current != '\'')
	{
		cout << "���ڿ��� ���� ���ڰ� �����ϴ�.";
		exit(1);
	}
	current++;
	return Token{ Kind::StringLiteral,string };
}

auto scanIdentifierAndKeyword() -> Token
{
	string string;
	while (isCharType(*current, CharType::IdentifierAndKeyword))
		string += *current++;

	auto kind = toKind(string);
	if (kind == Kind::Unknown)
		kind = Kind::Identifier;

	return Token{ kind, string };
}

auto scanOperatorAndPunctuator() -> Token
{
	string string;
	while (isCharType(*current, CharType::OperatorAndPunctuator))
		string += *current++;
	while (string.empty() == false && toKind(string) == Kind::Unknown)
	{
		string.pop_back();
		current--;
	}
	if (string.empty())
	{
		cout << *current << " ����� �� ���� �����Դϴ�.";
		exit(1);
	}
	return Token{ toKind(string),string };
}

auto scan(string sourceCode) -> vector<Token>
{
	vector<Token> result;
	sourceCode += '\0';

	current = sourceCode.begin();
	while (*current != '\0')
	{
		switch (getCharType(*current))
		{
		case CharType::OperatorAndPunctuator:
			result.push_back(scanOperatorAndPunctuator());
			break;
		case CharType::IdentifierAndKeyword:
			result.push_back(scanIdentifierAndKeyword());
			break;
		case CharType::StringLiteral:
			result.push_back(scanStringLiteral());
			break;
		case CharType::NumberLiteral:
			result.push_back(scanNumberLiteral());
			break;
		case CharType::WhiteSpace:
			current += 1;
			break;
		default:
			cout << *current << " ����� �� ���� �����Դϴ�.";
			exit(1);
		}
	}

	result.push_back({ Kind::EndOfToken });
	return result;
	
}