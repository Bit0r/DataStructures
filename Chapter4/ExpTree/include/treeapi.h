#ifndef _TREEAPI_H
#define _TREEAPI_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct trnode{
    char data;
    struct trnode *left;
    struct trnode *right;
}Trnode;

void TreeDir(Trnode *);
void TrnodeDir(Trnode *,int);
void TreeFree(Trnode *);

#endif