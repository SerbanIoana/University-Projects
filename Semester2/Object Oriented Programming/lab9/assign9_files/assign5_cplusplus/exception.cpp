#include "exception.h"

Exception::Exception(string exceptionMessage)
{
	this->message = exceptionMessage;
}

string Exception::get_message() const
{
	return this->message;
}