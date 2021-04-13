#pragma once
#include <string>

using namespace std;

class Exception
{
private:
	string message;
public:
	Exception(string exceptionMessage);
	string get_message() const;
};