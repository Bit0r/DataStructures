#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int coef;
    int power;
} Item;
typedef struct node {
    Item monominal;
    struct node *next;
} Node;
typedef struct {
    Node *front;
    Node *rear;
    int items;
} List;

void listini(List *);
void listadd(List *, Item *);
void listsort(List *);
void listmerge(List *, List *);
void listfree(List *);
void output(List *);

int main() {
    List polynomial1 = {NULL, NULL, 0}, polynomial2 = {NULL, NULL, 0};
    listini(&polynomial1);
    listini(&polynomial2);
    listsort(&polynomial1);
    listsort(&polynomial2);
    listmerge(&polynomial1, &polynomial2);
    output(&polynomial1);
    return 0;
}

void listini(List *plist) {
    int i;
    Item temp;
    Node *pnew = malloc(sizeof(List));
    pnew->next = NULL;
    plist->front = plist->rear = pnew;
    fputs("请输入多项式的项数：", stdout);
    scanf("%d", &plist->items);
    puts("请输入每个单项式的系数和幂，每行一个单项式");
    for (i = 0; i < plist->items; i++) {
        scanf("%d%d", &temp.coef, &temp.power);
        listadd(plist, &temp);
    }
}

void listadd(List *plist, Item *temp) {
    Node *pnew = malloc(sizeof(Node));
    pnew->monominal = *temp;
    pnew->next = NULL;
    plist->rear->next = pnew;
    plist->rear = pnew;
}

void listsort(List *plist) {
    Item temp;
    Node *p1, *p2, *t;
    for (p1 = plist->front->next; p1 != NULL; p1 = p1->next) {
        for (p2 = p1->next, t = p1; p2 != NULL; p2 = p2->next)
            if (t->monominal.power < p2->monominal.power)
                t = p2;
        if (t != p1) {
            temp = t->monominal;
            t->monominal = p1->monominal;
            p1->monominal = temp;
        }
    }
}

void listmerge(List *plist1, List *plist2) {
    Node *p1, *p2, *temp;
    for (p2 = plist2->front; p2->next != NULL;) {
        for (p1 = plist1->front;
             p1->next != NULL &&
             p1->next->monominal.power >= p2->next->monominal.power;
             p1 = p1->next) {
            if (p1->next->monominal.power == p2->next->monominal.power) {
                p1->next->monominal.coef += p2->next->monominal.coef;
                if (p1->next->monominal.coef == 0) {
                    temp = p1->next;
                    p1->next = temp->next;
                    free(temp);
                }
                p2 = p2->next;
            }
        }
        if (p1->next != NULL && p2->next != NULL &&
            p2->next->monominal.power > p1->next->monominal.power) {
            temp = p2->next;
            p2->next = temp->next;
            temp->next = p1->next;
            p1->next = temp;
        }
    }
}

void listfree(List *plist) {
    Node *cur, *temp;
    for (temp = plist->front, cur = temp->next; cur != NULL;
         temp = cur, cur = cur->next)
        free(temp);
    free(temp);
}

void output(List *plist) {
    Node *cur;
    for (cur = plist->front->next; cur->next != NULL; cur = cur->next) {
        if (cur->monominal.coef != 1)
            printf("%d", cur->monominal.coef);
        if (cur->monominal.power != 1)
            printf("x^%d+", cur->monominal.power);
        else
            fputs("x+", stdout);
    }
    if (cur->monominal.power == 0)
        printf("%d", cur->monominal.coef);
    else {
        if (cur->monominal.coef != 1)
            printf("%d", cur->monominal.coef);
        if (cur->monominal.power != 1)
            printf("x^%d", cur->monominal.power);
        else
            fputs("x", stdout);
    }
}