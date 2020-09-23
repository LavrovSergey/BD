#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "base.h"
typedef struct tagFileNames
{
	char index[length];
	char data[length];
	char tour[length];
	char rubbish[length];
	char tourRubbish[length];

} fileNames;

void menu();