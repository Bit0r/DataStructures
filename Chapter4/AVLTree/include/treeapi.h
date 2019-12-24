#ifndef _TREEAPI_H
#define _TREEAPI_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#define MIN(X,Y) (((X)<(Y))?(X):(Y))

typedef struct{
    char word[32];
}Item;
typedef struct trnode{
    Item data;
    struct trnode *left;
    struct trnode *right;
    short repeat;
    unsigned char height;
}Trnode;
typedef struct{
    Trnode *root;
    int size;
}Tree;

typedef struct{
    Trnode *parent;
    Trnode *child;
}Pair;

Pair ItemSearch(Tree *,Item *);
Trnode *TrnodeMake(FILE *);
void TrnodeOut(Trnode *);
void TreeIni(Tree *);
bool TreeAdd(Tree *,FILE *);
void TreeSearch(Tree *);
void TreeShow(Tree *);
void TrnodeShow(Trnode *);
void TreeMake(Tree *,FILE *);
int TrnodeHeight(Trnode *);
Trnode *TrnodeAdd(Trnode *,Trnode *);
Trnode *SingleLeft(Trnode *);
Trnode *SingleRight(Trnode *);
Trnode *DoubleLeft(Trnode *);
Trnode *DoubleRight(Trnode *);

#endif