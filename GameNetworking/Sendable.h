#pragma once
#include<string>
using namespace std;
class Sendable
{
public:

	virtual string encode() = 0;
	virtual Sendable& decode(string const &) = 0;

};

