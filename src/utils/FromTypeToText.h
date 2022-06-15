#pragma once

#include <string>





#define GET_STRING_FROM_TOKEN(tokens) #tokens

template<typename Type>
std::string typeToString()
{
	return std::string(GET_STRING_FROM_TOKEN(Type));
}