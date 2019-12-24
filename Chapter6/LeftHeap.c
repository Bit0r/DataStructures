#include<stdio.h>
#include<stdlib.h>

typedef struct trnode{
	int data;
	struct trnode *left;
	struct trnode *right;
	int npl;
}Trnode;

Trnode *merge(Trnode *,Trnode *);
Trnode *merge1(Trnode *,Trnode *);
Trnode *LeftHeapIns(Trnode *,int);
Trnode *LeftHeapDel(Trnode *,int *);
void DirShow(Trnode *,int);

int main(){
	int i;
	Trnode *h;
	for(i=0;i<15;i++)
		h=LeftHeapIns(h,i);
	DirShow(h,0);
	return 0;
}

Trnode *merge(Trnode *h1,Trnode *h2){
	if(h1==NULL)//如果一棵树是空树，则返回另一颗树
		return h2;
	if(h2==NULL)
		return h1;
	if(h1->data<h2->data)//选取根节点更小的树作为主树，因为堆的根节点最小
		return merge1(h1,h2);
	else
		return merge1(h2,h1);
}

Trnode *merge1(Trnode *h1,Trnode *h2){
	if(h1->left==NULL)//如果主树的根节点的左节点为空，证明该树为单节点
		h1->left=h2;//则将另一颗树变成左子树
	else{
		//如果主树左节点非空，就合并右子树和副树，以防止该堆变成单链
		h1->right=merge(h1->right,h2);

		if(h1->left->npl<h1->right->npl){//如果合并后的新树，其左子树的零路长小于右子树的零路长
			Trnode *temp=h1->left;//则交换左子树和右子树
			h1->left=h1->right;
			h1->right=temp;
		}
		h1->npl=h1->right->npl+1;//更新主树的零路长
	}
	return h1;
}

Trnode *LeftHeapIns(Trnode *h,int x){
	Trnode *pnew=malloc(sizeof(Trnode));//创造一个单节点树
	pnew->npl=0;
	pnew->left=pnew->right=NULL;
	pnew->data=x;
	return merge(h,pnew);//合并主树和新节点
}

Trnode *LeftHeapDel(Trnode *h,int *px){
	if(px!=NULL)
		*px=h->data;
	Trnode *h1=h->left,*h2=h->right;//将左子树与右子树独立
	free(h);//删除根节点
	return merge(h1,h2);//再将两棵树合并
}

void DirShow(Trnode *h,int layer){
	if(h==NULL)
		return;
	for(int i=0;i<layer;i++)
		putchar('\t');
	printf("%d\n",h->data);
	DirShow(h->left,layer+1);
	DirShow(h->right,layer+1);
}