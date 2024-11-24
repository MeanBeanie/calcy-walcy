#pragma once
#include <queue>
#include <string>

// NOTE differentiating between number and decimal is useless, just there cause lazy
enum Type {
	NONE = -2,
	WORD = 0,
	NUMBER,
	DECIMAL,
	ADD,
	SUB = 4,
	MUL,
	DIV,
	EXPONENT,
	PARENTHESIS = 8,
};

struct Token{
	Token(){}
	Token(std::string r, Type t, float v): raw(r), type(t), value(v) {}

	std::string raw;
	Type type;
	float value;
};

std::queue<Token> tokenize(std::string str);
