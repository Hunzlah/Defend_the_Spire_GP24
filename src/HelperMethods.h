#pragma once
#include <cstdio>  // for snprintf
#include <cstdlib> // for malloc / free

char* IntToCharPointer(int value) {
    // Allocate enough space for the string (max 11 chars for int32 + null terminator)
    char* result = new char[12]; 
    std::snprintf(result, 12, "%d", value); // Convert int to string
    return result;
}
float GetRandomNumberInRange(int max)
{
    return (float)(rand() % max);
}