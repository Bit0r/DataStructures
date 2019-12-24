#ifndef _MAIN_H
#define _MAIN_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CAPACITY 67

typedef struct{
    char word[32];
}Item;

void menushow();
bool ItemMake(FILE *,Item *);
int ItemCmp(Item *,Item *);
void ItemOut(Item *);

#endif