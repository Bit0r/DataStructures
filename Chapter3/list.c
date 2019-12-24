#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	long jobid;
	char name[32];
	char pdcid[32];
	float amount;
	float price;
	float sum;
}Item;
typedef struct node{
	Item data;
	struct node *pre;
	struct node *next;
}Node;
typedef struct{
	Node *front;
	Node *rear;
	int items;
}List;

void menushow();
void listini(List *);
void listadd(List *,Item *);
void listout(List *,int);
void listsort(List *);
void listins(List *);
void listdel(List *);
void nodeout(Node *);
Node *search(List *);
Node *listmax(List *);

int main(){
    int opt;
	List sales={NULL,NULL,0};
	menushow();
	while(scanf("%d",&opt)==1&&opt){
		getchar();
		switch(opt){
			case 1:listout(&sales,1);break;
			case 2:nodeout(listmax(&sales));break;
			case 3:listout(&sales,0);break;
			case 4:listsort(&sales);break;
			case 5:nodeout(search(&sales));break;
            case 6:listins(&sales);break;
            case 7:listdel(&sales);break;
			case 8:listini(&sales);break;
			default:puts("\n输入错误，请输入0~8");
		}
		puts("\n请继续输入需要的操作，输入0退出");
	}
	return 0;
}

void menushow(){
	puts("\n输入相应数字，选择你需要的操作\n\
	1.输出销售表单\n\
	2.显示总额最大的项\n\
	3.反向输出销售表单\n\
	4.将销售表单降序排序\n\
	5.查询工号,并输出该项\n\
	6.插入一个新项\n\
	7.按工号删除一项\n\
	8.初始化销售菜单\n\
	0.退出管理系统");
}

void listadd(List *plist,Item *temp){
	Node *pnew=malloc(sizeof(Node));
	pnew->data=*temp;
    	pnew->pre=plist->rear;
	if(plist->front==NULL){
		plist->front=plist->rear=pnew;
		plist->items=1;
	}else{
		plist->rear->next=pnew;
		plist->rear=pnew;
		plist->items++;
	}
}

void listini(List *plist){
	Item temp;
	puts("\n请按以下格式输入(按-1退出)\n\
	工号   姓名  产品编号    产品数量       产品价格");
	while(scanf("%ld",&temp.jobid)==1&&temp.jobid>0){
		scanf("%s%s%f%f",temp.name,temp.pdcid,&temp.amount,&temp.price);
		temp.sum=temp.price*temp.amount;
		listadd(plist,&temp);
	}
}

void listout(List *plist,int direction){
	Node *cur;
	if(direction)
		for(cur=plist->front;cur!=NULL;cur=cur->next)
			nodeout(cur);
	else
		for(cur=plist->rear;cur!=NULL;cur=cur->pre)
			nodeout(cur);
}

void nodeout(Node *pnode){
	if(pnode!=NULL)
    	printf("%16ld %4s %16s %16f %16f %16f\n",pnode->data.jobid,\
		pnode->data.name,pnode->data.pdcid,pnode->data.amount,\
		pnode->data.price,pnode->data.sum);
	else
		puts("无此人");
}

Node *search(List *plist){
	long jobid;
	Node *cur;
	fputs("请输入工号:",stdout);
	scanf("%ld",&jobid);
	for(cur=plist->front;cur!=NULL;cur=cur->next)
		if(jobid==cur->data.jobid)
			return cur;
	return NULL;
}

void listsort(List *plist){
	Item temp;
	Node *p1,*p2,*t;
	for(p1=plist->front;p1!=NULL;p1=p1->next){
		for(p2=p1->next,t=p1;p2!=NULL;p2=p2->next)
	    	if(t->data.sum<p2->data.sum)
				t=p2;
		if(t!=p1){
			temp=t->data;
			t->data=p1->data;
			p1->data=temp;
		}
	}
}

Node *listmax(List *plist){
	Node *cur,*max;
	for(cur=max=plist->front;cur!=NULL;cur=cur->next)
		if(max->data.sum<cur->data.sum)
			max=cur;
	return max;
}

void listins(List *plist){
    Node *pnew=malloc(sizeof(Node)),*cur;
    puts("\n请按以下格式输入\n工号   姓名  产品编号    产品数量       产品价格");
    scanf("%ld%s%s%f%f",&pnew->data.jobid,pnew->data.name,pnew->data.pdcid,\
	&pnew->data.amount,&pnew->data.price);
    pnew->data.sum=pnew->data.amount*pnew->data.price;
    plist->items++;
    for(cur=plist->front;cur!=NULL&&cur->data.sum>pnew->data.sum;cur=cur->next)
					continue;
	if(cur==plist->front){//刚好是最大的一项
		pnew->next=plist->front;
		plist->front->pre=pnew;
		plist->front=pnew;
	}else if(cur==NULL){//刚好是最小的一项
        pnew->pre=plist->rear;
        plist->rear->next=pnew;
        plist->rear=pnew;
    }else{//该项在中间
        pnew->pre=cur->pre;
        pnew->next=cur;
        cur->pre->next=pnew;
		cur->pre=pnew;
    }
	plist->items++;
}

void listdel(List *plist){
    Node *result=search(plist);	
    if(result==plist->front){//该项为第一项
		plist->front=result->next;
		plist->front->pre=NULL;
		free(result);
		plist->items--;
	}else if(result==plist->rear){//该项为最后一项
		plist->rear=result->pre;
		plist->rear->next=NULL;
		free(result);
		plist->items--;
	}else if(result!=NULL){//该项在中间
		result->pre->next=result->next;
		result->next->pre=result->pre;
		free(result);
		plist->items--;
	}else{
		puts("无此人");
	}
}
