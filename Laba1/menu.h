#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "base.h"
typedef struct tagFileNames
{
	char index[LEN];//indexFileName
	char data[LEN];//dataFileName
	char tour[LEN];//progressFileName
	char rubbish[LEN];//rubishFileName
	char tourRubbish[LEN];//progressFileName

} fileNames;

void menu();