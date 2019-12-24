#ifndef _MAIN_H
#define _MAIN_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void menushow();
int ItemCmp(Item *,Item *);
bool ItemMake(FILE *,Item *);

#endif