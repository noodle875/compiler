#pragma once;
#include <tuple>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Token.h"
#include "Node.h"
#include "Code.h"

using namespace std;

auto printSyntaxTree(Program*) -> void;
auto scan(string) -> vector<Token>;
auto parse(vector<Token>) -> Program*;
auto interpret(Program*) -> void;
auto generate(Program*) -> tuple<vector<Code>, map<string, size_t>>;
auto printObjectCode(tuple<vector<Code>, map<string, size_t>>) -> void;
auto execute(tuple<vector<Code>, map<string, size_t>>) -> void;