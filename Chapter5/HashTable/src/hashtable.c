#include"hashtable.h"

unsigned Hash(char *str,unsigned capacity){
    unsigned hash;
    for(hash=5381;*str;str++)
        hash+=(hash<<5)+*str;
    return hash%capacity;
}

void ItemAdd(Table arr[],Item *pitem){
    unsigned index=Hash(pitem->word,CAPACITY);
    Node *pnew=malloc(sizeof(Node)),*temp;
    pnew->data=*pitem;
    pnew->repeat=1;
    if(arr[index].front==NULL){//该表项为空的情况
        pnew->next=NULL;
        arr[index].front=pnew;
        arr[index].size=1;
    }else if((temp=ListFind(arr[index].front,pitem))!=NULL){//该表项已经有这个项
        temp->repeat++;
        free(pnew);
    }else{//该表项没有这个项
        pnew->next=arr[index].front;
        arr[index].front=pnew;
        arr[index].size++;
    }
}

void ItemDel(Table arr[],Item *pitem){
    unsigned index=Hash(pitem->word,CAPACITY);
    Node *temp,*cur;
    if(ItemCmp(&arr[index].front->data,pitem)==0){//项是表头的情况
        temp=arr[index].front;
        arr[index].front=temp->next;
        free(temp);
    }else{
        for(cur=arr[index].front;cur!=NULL;cur=cur->next)
            if(ItemCmp(&cur->next->data,pitem)==0)
                break;
        if(cur->next!=NULL){
            temp=cur->next;
            cur->next=temp->next;
            free(temp);
        }
    }
}

Node *ListFind(Node *front,Item *pitem){
    for(Node *cur=front;cur!=NULL;cur=cur->next)
        if(ItemCmp(&cur->data,pitem)==0)
            return cur;
    return NULL;
}

void TableShow(Table arr[]){
    unsigned i;
    Node *cur;
    for(i=0;i<CAPACITY;i++){
        if(arr[i].size==0)
            continue;
        for(cur=arr[i].front;cur!=NULL;cur=cur->next){
            ItemOut(&cur->data);
            if(cur->repeat>1)
                printf("(Repeat %d times)\n",cur->repeat);
            else
                putchar('\n');
        }
    }
}

void TableIni(Table arr[],FILE *pf){
    Item temp;
    for(int i=0;i<CAPACITY;i++){
        arr[i].front=NULL;
        arr[i].size=0;
    }
    while(ItemMake(pf,&temp))
        ItemAdd(arr,&temp);
}

void TableFind(Table arr[]){
    Item temp;
    ItemMake(stdin,&temp);
    unsigned index=Hash(temp.word,CAPACITY);
    Node *find=ListFind(arr[index].front,&temp);
    if(find==NULL)
        puts("没有这个项!");
    else{
        ItemOut(&find->data);
        if(find->repeat>1)
            printf("(Repeat %d times)\n",find->repeat);
        else
            putchar('\n');
    }
}

void TableDel(Table arr[]){
    Item temp;
    if(ItemMake(stdin,&temp))
        ItemDel(arr,&temp);
}

void DirShow(Table arr[]){
    for(int i=0;i<CAPACITY;i++){
        if(arr[i].size==0)
            continue;
        for(Node *cur=arr[i].front;cur!=NULL;cur=cur->next){
            ItemOut(&cur->data);
            putchar(' ');
        }
        putchar('\n');
    }
}