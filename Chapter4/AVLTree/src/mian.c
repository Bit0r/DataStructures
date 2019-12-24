#include"treeapi.h"
#include"main.h"

int main(int argc,char *argv[]){
    Tree dictionary;
	int opt;
    FILE *pf=fopen(argv[1],"r");
    TreeIni(&dictionary);
	TreeMake(&dictionary,pf);
	menushow();
	while(scanf("%d",&opt)==1&&opt){
		getchar();
		switch(opt){
			case 1:TreeShow(&dictionary);break;
			case 2:TreeSearch(&dictionary);break;
			default:puts("\n输入错误，请输入0~2");
		}
		puts("\n请继续输入需要的操作，输入0退出");
	}
	return 0;
}

void menushow(){
	puts("\n输入相应数字，选择你需要的操作\n\
	1.输出所有单词和出现次数\n\
	2.查询该单词出现的次数\n\
	0.退出");
}

int ItemCmp(Item *item1,Item *item2){
    return strcmp(item1->word,item2->word);
}

bool ItemMake(FILE *pf,Item *pitem){
	if(1!=fscanf(pf,"%s",pitem->word))
        return false;
    else
		return true;
}