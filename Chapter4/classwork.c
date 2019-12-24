#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trnode {
    int data;
    struct trnode *left, *right;
} Trnode;

Trnode *find(Trnode *root, int data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return find(root->left, data);
    else
        return find(root->right, data);
}

void insert(Trnode *root, int data) {
    Trnode *parent = NULL, *child = root;
    while (child != NULL && child->data != data) {
        parent = child;
        if (data < child->data)
            child = child->left;
        else
            child = child->right;
    }
    if (child == NULL) {
        Trnode *pnew = calloc(1, sizeof(Trnode));
        pnew->left = pnew->right = NULL;
        pnew->data = data;
        if (data < parent->data)
            parent->left = pnew;
        else
            parent->right = pnew;
    }
}

Trnode *init() {
    Trnode *root;
    root = calloc(1, sizeof(Trnode));
    scanf("%d", &root->data);
    root->left = root->right = NULL;
    return root;
}

Trnode *input() {
    Trnode *root;
    int n, i, temp;
    fputs("请输入二叉树节点个数：",stdout);
    scanf("%d", &n);
    puts("请输入二叉树节点数据");
    root = init();
    for (i = 1; i < n; i++) {
        scanf("%d", &temp);
        insert(root, temp);
    }
    return root;
}

int main() {
    int data;
    Trnode *root = NULL;
    root = input();
    fputs("请输入需要查询的数字：",stdout);
    scanf("%d", &data);
    if (find(root, data) != NULL)
        puts("存在这个数！");
    else
        puts("查询失败！");
    return 0;
}