#include"treeapi.h"
#include"main.h"

Pair ItemSearch(Tree *ptree,Item *target){
    int result;
    Pair look={NULL,ptree->root};
    while(look.child!=NULL){
        result=ItemCmp(target,&look.child->data);
        if(result<0){
            look.parent=look.child;
            look.child=look.child->left;
        }
        else if(result>0){
            look.parent=look.child;
            look.child=look.child->right;
        }
        else
            break;
    }
    return look;
}

void TreeIni(Tree *ptree){
    ptree->root=NULL;
    ptree->size=0;
}

void TreeMake(Tree *ptree,FILE *pfile){
    while(TreeAdd(ptree,pfile))
        continue;
}

Trnode *TrnodeMake(FILE *pfile){
    Trnode *pnew;
    pnew=malloc(sizeof(Trnode));
    if(ItemMake(pfile,&pnew->data)==false)
        return NULL;
    pnew->left=pnew->right=NULL;
    pnew->repeat=1;
    pnew->height=0;
    return pnew;
}

bool TreeAdd(Tree *ptree,FILE *pfile){
    Trnode *pnew=TrnodeMake(pfile);
    if(pnew==NULL)
        return false;
    if(ptree->root==NULL){
        ptree->root=pnew;
        ptree->size=1;
    }
    else
        ptree->root=TrnodeAdd(ptree->root,pnew);
    return true;
}

void TreeShow(Tree *ptree){
    TrnodeShow(ptree->root);
}

void TrnodeShow(Trnode *root){
    if(root==NULL)
        return;
    TrnodeShow(root->left);
    TrnodeOut(root);
    TrnodeShow(root->right);
}

void TrnodeOut(Trnode *ptrnode){
    if(ptrnode==NULL){
        puts("没有这一项!");
        return;
    }
    int times=ptrnode->repeat;
    if(times>0){
        printf("%s",ptrnode->data.word);
        if(times>=1)
            printf("(Repeated %hd times)\n",times);
    }
}

void TreeSearch(Tree *ptree){
    Item target;
    fputs("请输入您需要查找的项:",stdout);
    ItemMake(stdin,&target);
    Pair look=ItemSearch(ptree,&target);
    TrnodeOut(look.child);
}

int TrnodeHeight(Trnode *ptrnode){
    if(ptrnode==NULL)
        return -1;
    else
        return ptrnode->height;
}

Trnode *TrnodeAdd(Trnode *root,Trnode *pnew){
    int result=ItemCmp(&pnew->data,&root->data);
    if(result<0){
        if(root->left==NULL)
            root->left=pnew;
        else
            root->left=TrnodeAdd(root->left,pnew);
        if(TrnodeHeight(root->left)-TrnodeHeight(root->right)==2){
            if(ItemCmp(&pnew->data,&root->left->data)<0)
                root=SingleLeft(root);
            else
                root=DoubleLeft(root);
        }
    }else if(result>0){
        if(root->right==NULL)
            root->right=pnew;
        else
            root->right=TrnodeAdd(root->right,pnew);
        if(TrnodeHeight(root->right)-TrnodeHeight(root->left)==2){
            if(ItemCmp(&pnew->data,&root->right->data)>0)
                root=SingleRight(root);
            else
                root=DoubleRight(root);
        }
    }else{
        root->repeat++;
        free(pnew);
    }
    return root;
}

Trnode *SingleLeft(Trnode *k2){
    Trnode *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height=MAX(TrnodeHeight(k2->left),TrnodeHeight(k2->left))+1;
    k1->height=MAX(TrnodeHeight(k1->left),TrnodeHeight(k1->left))+1;
    return k1;
}

Trnode *SingleRight(Trnode *k2){
    Trnode *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    k2->height=MAX(TrnodeHeight(k2->left),TrnodeHeight(k2->left))+1;
    k1->height=MAX(TrnodeHeight(k1->left),TrnodeHeight(k1->left))+1;
    return k1;
}

Trnode *DoubleLeft(Trnode *k3){
    Trnode *k1=k3->left,*k2=k1->right;
    k3->left=SingleRight(k1);
    return SingleLeft(k3);
}

Trnode *DoubleRight(Trnode *k3){
    Trnode *k1=k3->right,*k2=k1->left;
    k2->right=SingleLeft(k1);
    return SingleRight(k3);
}

/* Trnode *DoubleLeft(Trnode *k3){
    Trnode *k1=k3->left,*k2=k1->right;
    k1->right=k2->left;
    k3->left=k2->right;
    k2->left=k1;
    k2->right=k3;
    k1->height=MAX(TrnodeHeight(k1->left),TrnodeHeight(k1->left))+1;
    k2->height=MAX(TrnodeHeight(k2->left),TrnodeHeight(k2->left))+1;
    k3->height=MAX(k1->height,k2->height)+1;//这里的两个节点必定不为空
    return k2;
} */

/* Trnode *DoubleRight(Trnode *k3){
    Trnode *k1=k3->left,*k2=k1->right;
    k1->left=k2->right;
    k3->right=k2->left;
    k2->left=k3;
    k2->right=k1;
    k1->height=MAX(TrnodeHeight(k1->left),TrnodeHeight(k1->left))+1;
    k2->height=MAX(TrnodeHeight(k2->left),TrnodeHeight(k2->left))+1;
    k3->height=MAX(k1->height,k2->height)+1;//这里的两个节点必定不为空
    return k2;
} */
