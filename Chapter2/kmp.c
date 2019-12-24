#include <stdio.h>
#include <string.h>

int KMP(char str[], char word[], int nextval[]) {
    int cur = 0, match = 0,length1=strlen(str),length2=strlen(word);
    while (cur < length1 && match < length2) {
        if (match == -1 || str[cur] == word[match]) {
            cur++;
            match++;
        } else
            match = nextval[match];
    }
    if (match == strlen(word))
        return cur - match;
    else
        return -1;
}

void getNextval(char word[], int nextval[]) {
    nextval[0] = -1;
    int i = 0, j = -1;
    while (i < strlen(word)) {
        if (j == -1 || word[i] == word[j]) {
            i++;
            j++;
            if(nextval[i]!=nextval[j])
                nextval[i]=j;
            else
                nextval[i]=nextval[j];
        } else
            j = nextval[j];
    }
}

int main() {
    char str[1024], word[64];
    int next[64];
    gets(str);
    gets(word);
    getNextval(word, next);
    printf("%d", KMP(str, word, next));
    return 0;
}