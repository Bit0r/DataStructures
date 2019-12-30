#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    char number[64];
} Item;
typedef struct node {
    Item data;
    struct node *pre;
    struct node *next;
} Node;
typedef struct {
    Node *front;
    Node *rear;
    int items;
} List;

void menushow();
void listini(List *);
void listins(List *);
void listsearch(List *);
void listdel(List *);
void listprint(List *);
void add(List *, Item *);
Node *query(List *);

int main() {
    int opt;
    List book = {NULL, NULL, 0};
    menushow();
    while (scanf("%d", &opt) == 1 && opt) {
        getchar();
        switch (opt) {
        case 1:
            listini(&book);
            break;
        case 2:
            listins(&book);
            break;
        case 3:
            listsearch(&book);
            break;
        case 4:
            listdel(&book);
            break;
        case 5:
            listprint(&book);
            break;
        default:
            puts("\n输入错误，请输入0~5");
        }
        puts("\n请继续输入需要的操作，输入0退出");
    }
    return 0;
}

void menushow() {
    puts("\n输入相应数字，选择你需要的操作\n\
	1.建立通讯录链表\n\
	2.插入通讯者结点\n\
	3.查询通讯者结点\n\
	4.删除通讯者结点\n\
	5.输出通讯者结点\n\
	0.退出管理系统");
}

void add(List *plist, Item *temp) {
    Node *pnew = malloc(sizeof(Node));
    pnew->data = *temp;
    pnew->pre = plist->rear;
    if (plist->front == NULL) {
        plist->front = plist->rear = pnew;
        plist->items = 1;
    } else {
        plist->rear->next = pnew;
        plist->rear = pnew;
        plist->items++;
    }
}

void listsearch(List *plist) {
    Node *result = query(plist);
    if (result != NULL) {
        puts("姓名\t电话号码");
        printf("%s\t%s\n", result->data.name, result->data.number);
    } else
        puts("查无此人");
}

void listprint(List *plist) {
    puts("姓名\t号码");
    for (Node *cur = plist->front; cur != NULL; cur = cur->next)
        printf("%s\t%s\n", cur->data.name, cur->data.number);
}

void listini(List *plist) {
    Item temp;
    int n;
    fprintf(stdout, "请输入你需要添加的通讯录项数：");
    scanf("%d", &n);
    puts("姓名\t电话号码");
    for (int i = 0; i < n; i++) {
        scanf("%s%s", &temp.name, &temp.number);
        add(plist, &temp);
    }
}

Node *query(List *plist) {
    char name[64];
    Node *cur;
    fputs("通讯者姓名:", stdout);
    scanf("%s", name);
    for (cur = plist->front; cur != NULL; cur = cur->next)
        if (strcmp(name, cur->data.name) == 0)
            return cur;
    return NULL;
}

void listins(List *plist) {
    Item temp;
    puts("姓名\t电话号码");
    scanf("%s%s", &temp.name, &temp.number);
    add(plist, &temp);
}

void listdel(List *plist) {
    Node *result = query(plist);
    if (result == plist->front) { //该项为第一项
        plist->front = result->next;
        plist->front->pre = NULL;
        free(result);
        plist->items--;
    } else if (result == plist->rear) { //该项为最后一项
        plist->rear = result->pre;
        plist->rear->next = NULL;
        free(result);
        plist->items--;
    } else if (result != NULL) { //该项在中间
        result->pre->next = result->next;
        result->next->pre = result->pre;
        free(result);
        plist->items--;
    } else {
        puts("查无此人");
    }
}
