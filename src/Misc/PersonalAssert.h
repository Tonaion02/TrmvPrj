#pragma once

#include <stdio.h>





#define GET_STRING_FROM_TOKEN(tokens) #tokens

#ifdef DEBUG
#define ASSERT(condition)			{\
										if (!condition)\
										{\
											printf("%s\n", GET_STRING_FROM_TOKEN(condition));\
											printf("Erorr in file: %s in function: %s\n", __FILE__, __FUNCTION__);\
											__debugbreak();										\
										}														\
									}
#else
#define ASSERT(condition) ;
#endif