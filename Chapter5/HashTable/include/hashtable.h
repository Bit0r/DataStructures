#ifndef _TREEAPI_H
#define _TREEAPI_H

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"

typedef struct node{
    Item data;
    struct node *next;
    int repeat;
}Node;
typedef struct{
    int size;
    Node *front;
}Table;

Node *ListFind(Node *,Item *);
void ItemAdd(Table [],Item *);
void ItemDel(Table [],Item *);
void TableDel(Table []);
Node *ListFind(Node *,Item *);
void TableShow(Table []);
void TableIni(Table [],FILE *);
void TableFind(Table []);
void DirShow(Table []);
unsigned Hash(char *,unsigned);

#endif