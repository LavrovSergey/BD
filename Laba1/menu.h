#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "base.h"
typedef struct FileNames
{
	char ID[length];
	char data[length];
	char tour[length];
	char rubbish[length];
	char tourRubbish[length];

} files;

void menu();