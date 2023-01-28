#pragma once
#include <any>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "Node.h"

using namespace std;

struct Object
{
	bool isMarked = false;
	virtual ~Object(){}
};

struct Array : Object
{
	vector<any> values;
};

struct Map : Object
{
	map<string, any> values;
};

auto isSize(any value) -> bool;
auto toSize(any value) -> size_t;

auto isNull(any value) -> bool;

auto isTrue(any value) -> bool;
auto isFalse(any value) -> bool;
auto isBoolean(any value) -> bool;
auto toBoolean(any value) -> bool;

auto isNumber(any value) -> bool;
auto toNumber(any value) -> double;

auto isString(any value) -> bool;
auto toString(any value) -> string;

auto isArray(any value) -> bool;
auto toArray(any value) -> Array*;
auto getValueOfArray(any object, any key) -> any;
auto setValueOfArray(any object, any index, any key) -> any;

auto isMap(any value) -> bool;
auto toMap(any value) -> Map*;
auto getValueOfMap(any object, any value) -> any;
auto setValueOfMap(any object, any key, any value) -> any;

auto isFunction(any value) -> bool;
auto toFunction(any value) -> Function*;

auto isBuiltinFunction(any value) -> bool;
auto toBuiltinFunction(any value) -> function<any(vector<any>)>;

auto operator<<(ostream& stream, any& value)->ostream&;

