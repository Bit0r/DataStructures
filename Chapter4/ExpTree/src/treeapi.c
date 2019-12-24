#include"treeapi.h"

void TreeDir(Trnode *root){
    TrnodeDir(root,0);
}

void TrnodeDir(Trnode *p,int depth){
    if(p==NULL)
        return;
    printf("%*s%c\n",depth*2,"",p->data);
    TrnodeDir(p->left,depth+1);
    TrnodeDir(p->right,depth+1);
}

void TreeFree(Trnode *root){
    if(root==NULL)
        return;
    TreeFree(root->left);
    TreeFree(root->right);
    free(root);
}