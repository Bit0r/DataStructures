#include "treeapi.h"
#include <stdlib.h>
#include <string.h>

Trnode *CRTree(char s[], int i, int j) {
    Trnode *pnew;
    int k, plus = 0, posi;
    if (i == j) {
        pnew = malloc(sizeof(Trnode));
        pnew->data = s[i];
        pnew->left = pnew->right = NULL;
        return pnew;
    }
    for (k = i; k <= j; k++)
        if (s[k] == '+' || s[k] == '-') {
            plus++;
            posi = k;
        }
    if (plus == 0)
        for (k = i; k <= j; k++)
            if (s[k] == '*' || s[k] == '/') {
                plus++;
                posi = k;
            }
    if (plus) {
        pnew = malloc(sizeof(Trnode));
        pnew->data = s[posi];
        pnew->left = CRTree(s, i, posi - 1);
        pnew->right = CRTree(s, posi + 1, j);
        return pnew;
    } else
        return NULL;
}
double Comp(Trnode *root) {
    double v1, v2;
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return root->data - '0';
    v1 = Comp(root->left);
    v2 = Comp(root->right);
    switch (root->data) {
    case '+':
        return v1 + v2;
    case '-':
        return v1 - v2;
    case '*':
        return v1 * v2;
    case '/':
        if (v2 != 0)
            return v1 / v2;
        else
            exit(EXIT_FAILURE);
    }
}

int main(){
    Trnode *exp;
    char s[1024]="1+2*3-4/5";
    printf("算术表达式%s\n",s);
    exp=CRTree(s,0,strlen(s)-1);
    puts("对应二叉树：");
    TreeDir(exp);
    printf("\n算术表达式的值：%g\n",Comp(exp));
    TreeFree(exp);
    return 0;
}