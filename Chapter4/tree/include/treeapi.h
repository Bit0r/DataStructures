#ifndef _TREEAPI_H
#define _TREEAPI_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char word[32];
}Item;
typedef struct trnode{
    Item data;
    struct trnode *left;
    struct trnode *right;
    short repeat;
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
void TreeDel(Tree *);
void TreeShow(Tree *);
void TrnodeShow(Trnode *);
void TreeMake(Tree *,FILE *);
void TreeDel(Tree *);
void TrnodeDel(Trnode **);
void TrnodeSwap(Trnode *);
void TreeSwap(Tree *);
void DirShow(Tree *);
void DirTrnode(Trnode *,char);
void PrintName(Trnode *,char);

#endif
