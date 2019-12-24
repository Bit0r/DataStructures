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

Trnode *TrnodeMake(FILE *pfile){
    Trnode *pnew;
    pnew=malloc(sizeof(Trnode));
    if(ItemMake(pfile,&pnew->data)==false)
        return NULL;
    pnew->left=pnew->right=NULL;
    pnew->repeat=1;
    return pnew;
}

bool TreeAdd(Tree *ptree,FILE *pfile){
    Trnode *pnew=TrnodeMake(pfile);
    if(pnew==NULL)
        return false;
    Pair look=ItemSearch(ptree,&pnew->data);
    if(look.parent==NULL&&look.child==NULL){
        ptree->root=pnew;
        ptree->size=1;
    }
    else if(look.child==NULL){
        if(ItemCmp(&pnew->data,&look.parent->data)<0)
            look.parent->left=pnew;
        else
            look.parent->right=pnew;
        ptree->size++;
    }
    else{
        look.child->repeat++;
        free(pnew);
    }
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

void TreeMake(Tree *ptree,FILE *pfile){
    while(TreeAdd(ptree,pfile))
        continue;
}

void TreeDel(Tree *ptree){
    Item target;
    Trnode *temp;
    fputs("请输入您需要删除的项:",stdout);
    ItemMake(stdin,&target);
    Pair look=ItemSearch(ptree,&target);
    if(look.child==NULL){//防止输入错误
        puts("没有该项！");
        return;
    }  
    if(look.parent==NULL)//删除根，用惰性删除
        ptree->root->repeat=0; 
    else if(look.child==look.parent->left)//删除非根节点
        TrnodeDel(&look.parent->left); 
    else
        TrnodeDel(&look.parent->right);
}

void TrnodeDel(Trnode **ptr){
    Trnode *temp,*cur;
    if((*ptr)->left==NULL){//没有左节点(包括叶节点)
        temp=*ptr;
        *ptr=temp->right;
        free(temp);
    }else if((*ptr)->right==NULL){//没有右节点
        temp=*ptr;
        *ptr=temp->left;
        free(temp);
    }else{//有两个节点
        temp=*ptr;
        *ptr=temp->left;
        for(cur=temp->left;cur->right!=NULL;cur=cur->right)
            continue;
        cur->right=temp->right;
        free(temp);
    }
}

void TrnodeSwap(Trnode *root){
    Trnode *temp;
    temp=root->left;
    root->left=root->right;
    root->right=temp;
    if(root->left!=NULL)
        TrnodeSwap(root->left);
    if(root->right!=NULL)
        TrnodeSwap(root->right);
}

void TreeSwap(Tree *ptree){
    TrnodeSwap(ptree->root);
}

void DirShow(Tree *ptree){
    DirTrnode(ptree->root,0);
}

void DirTrnode(Trnode *root,char depth){
    PrintName(root,depth);
    if(root->left!=NULL)
        DirTrnode(root->left,depth+1);
    if(root->right!=NULL)
        DirTrnode(root->right,depth+1);
}

void PrintName(Trnode *ptr,char depth){
    for(char i=0;i<depth;i++)
        putchar('\t');
    puts(ptr->data.word);
}
