#pragma once
//-----------------------------------------------------------------------------//
#ifndef __JSON_H_ 
#define __JSON_H_ 
//-----------------------------------------------------------------------------//
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------//
struct treeObject {
	char parent[1000];
	char item[1000];
	uint16_t parent_index;
};
//-----------------------------------------------------------------------------//
void jsonInit(char *jsonAssign);
void get(char *result);
bool select(uint8_t index);
bool jReturn(void);
//-----------------------------------------------------------------------------//
#endif