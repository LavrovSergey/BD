#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "base.h"
typedef struct tagFileNames
{
	char index[LEN];
	char data[LEN];
	char tour[LEN];
	char rubbish[LEN];
	char tourRubbish[LEN];

} fileNames;

void menu();