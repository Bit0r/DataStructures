#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//typedef enum {empty,full,deleted} Info;//如果一个开放寻址哈希表需要删除，则需三种状态

typedef struct{
    char word[16];
    bool full;//如果这个哈希表不需要删除，所以我用bool类型来表达两个状态
}Cell;
typedef struct{
    unsigned capacity;
    Cell *front;
}Table;

int isprime(int);
unsigned nextprime(int);
bool TableIni(Table *,int);
unsigned Hash(char *,unsigned);
unsigned IndexFind(char *s,Table *);
void TableIns(char *,Table *);
void TableMake(Table *);
void TableShow(Table *);//这个函数用来测试上半部分函数的正确性
unsigned solve(Table *);
unsigned right(Table *,int,int);
unsigned rightdown(Table *,int,int);
unsigned down(Table *,int,int);
unsigned leftdown(Table *,int,int);
unsigned left(Table *,int,int);
unsigned leftup(Table *,int,int);
unsigned up(Table *,int,int);
unsigned rightup(Table *,int,int);

int direct[8][2]={//保存8个方向
        {0,1},//→
        {1,1},//↘
        {1,0},//↓
        {1,-1},//↙
        {0,-1},//←
        {-1,-1},//↖
        {-1,0},//↑
        {-1,1}//↗
    };
char word[16];
char puzzle[4][5]={"this","wats","oahg","fgdt"};

int main(){
    Table dictionary;
    TableIni(&dictionary,4);
    TableMake(&dictionary);
    //TableShow(&dictionary);
    printf("总共存在%u个单词",solve(&dictionary));
    return 0;
}

bool TableIni(Table *ptab,int size){
    if(size<=0){
        fputs("表的大小必须是正数,初始化失败!",stderr);
        return false;
    }
    ptab->capacity=nextprime(2*size);//生成的表容量必须是素数而且是实际数据的两倍，不然会发生大量冲突
    ptab->front=malloc(sizeof(Cell)*ptab->capacity);
    for(int i=0;i<ptab->capacity;i++)
        ptab->front[i].full=false;
    return true;
}

int isprime(int x){
    if(x<2)
        return 0;
    if(x==2)
        return 1;
    if(x%2==0)
        return 0;
    for(int i=3;i*i<=x;i+=2)
        if(x%i==0)
            return 0;
    return 1;
}

unsigned nextprime(int x){
    unsigned i;
    for(i=x;!isprime(i);i++)
        continue;
    return i;
}

unsigned Hash(char *str,unsigned capacity){//著名的time33函数
    unsigned hash;
    for(hash=5381;*str;str++)
        hash+=(hash<<5)+*str;
    return hash%capacity;
}

unsigned IndexFind(char *str,Table *ptab){
    unsigned index,i;
    index=Hash(str,ptab->capacity);
    for(i=1;ptab->front[index].full==true&&\
    strcmp(str,ptab->front[index].word)!=0;i++){//要先测试是否有元素,才能进行比较
        index+=2*i-1;//这里使用F(i)=i^2,可变形得F(i)=F(i-1)+2*i-1
        if(index>=ptab->capacity)//使用减法而不是取模会更快
            index-=ptab->capacity;
    }
    return index;
}

void TableIns(char *word,Table *ptab){
    unsigned index=IndexFind(word,ptab);
    if(ptab->front[index].full==true)//如果已经有这个元素就直接返回
        return;
    ptab->front[index].full=true;
    strcpy(ptab->front[index].word,word);
}

void TableMake(Table *ptab){
    char temp[4][8]={"this","two","fat","that"};
    for(int i=0;i<4;i++)
        TableIns(temp[i],ptab);
}

void TableShow(Table *ptab){
    for(int i=0;i<ptab->capacity;i++)
        if(ptab->front[i].full==true)
            puts(ptab->front[i].word);
}

unsigned solve(Table *ptab){
    int x=0,y=0,s=0;
    for(x=0;x<4;x++){
        for(y=0;y<4;y++){
            s+=right(ptab,x,y);
            s+=rightdown(ptab,x,y);
            s+=down(ptab,x,y);
            s+=leftdown(ptab,x,y);
            s+=left(ptab,x,y);
            s+=leftup(ptab,x,y);
            s+=up(ptab,x,y);
            s+=rightup(ptab,x,y);
        }
    }
    return s;
}

unsigned right(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[0][0];
        ty += direct[0][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned rightdown(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[1][0];
        ty += direct[1][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned down(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[2][0];
        ty += direct[2][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned leftdown(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[3][0];
        ty += direct[3][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned left(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[4][0];
        ty += direct[4][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned leftup(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[5][0];
        ty += direct[5][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned up(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[6][0];
        ty += direct[6][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}

unsigned rightup(Table *ptab,int x,int y){
    int tx=x,ty=y,i,index;
    unsigned s=0;
    for (i = 0; tx >= 0 && tx < 4 && ty >= 0 && ty < 4; i++){
        word[i] = puzzle[tx][ty];
        tx += direct[7][0];
        ty += direct[7][1];
        if (i < 2)
            continue;
        word[i + 1] = '\0';
        index = IndexFind(word, ptab);
        if (strcmp(word, ptab->front[index].word) == 0){
            s++;
            printf("%s从(%d,%d)到(%d,%d)\n",word,x,y,tx,ty);
        }
    }
    return s;
}