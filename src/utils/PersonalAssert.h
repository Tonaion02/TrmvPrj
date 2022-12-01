#pragma once

#include <cstdio>





#define GET_STRING_FROM_TOKEN(tokens) #tokens

#define ASSERT(condition) ;

#ifdef DEBUG
#ifdef WINDOWS
#define ASSERT(condition)			{\
										if (!condition)\
										{\
											printf("%s\n", GET_STRING_FROM_TOKEN(condition));\
											printf("Erorr in file: %s in function: %s\n", __FILE__, __FUNCTION__);\
											__debugbreak();										\
										}														\
									}
#endif

#ifdef LINUX
#define ASSERT(condition)			{\
										if(!condition)\
										{\
											printf("%s\n", GET_STRING_FROM_TOKEN(condition));\
											printf("Erorr in file: %s in function: %s\n", __FILE__, __FUNCTION__);\
											__builtin_trap();\
										}\
									}
#endif

#endif