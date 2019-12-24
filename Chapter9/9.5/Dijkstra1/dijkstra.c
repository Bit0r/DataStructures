#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    bool known;
    int distance, path;
} Shortest;

Shortest box[64];
int graph[64][64];
int n, s;

void input() {
    int u, v, w, i, j;
    scanf("%d%d", &n, &s);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = INT_MAX;
    while (scanf("%d%d%d", &u, &v, &w))
        graph[u][v] = w;
}

void InitBox() {
    for (int i = 0; i < n; i++) {
        box[i].known = false;      //将所以点加入未知集合Q
        box[i].distance = INT_MAX; //使用INT_MAX来代替infinity
        box[i].path = -1;
    }
    box[s].distance = 0;
    // 因为出发点到出发点间不需移动任何距离，所以可以直接将s到s的最小距离设为0
}

int FindMin() {
    int min = INT_MAX, u = 0;
    for (int i = 0; i < n; i++)
        if (box[i].known == false && min > box[i].distance) {
            u = i;
            min = box[i].distance;
        }
    //如果查找失败就返回-1，成功则返回u
    if (min == INT_MAX)
        return -1;
    else
        return u;
}

void dijkstra() {
    InitBox();
    int u, v;
    while ((u = FindMin()) != -1) {
        box[u].known = true; //将点u加入已知集合S
        //通过u拓展未知集合Q中的每一条相邻边
        for (v = 0; v < n; v++) {
            if (box[v].known == false && INT_MAX != graph[u][v] &&
                box[v].distance > box[u].distance + graph[u][v]) {
                box[v].distance = box[u].distance + graph[u][v];
                box[v].path = u;
            }
        }
    }
}

//递归打印路径
void printpath(int end) {
    if (end == s)
        printf("%d", s);
    else {
        printpath(box[end].path);
        printf("->%d", end);
    }
}

void output() {
    for (int i = 0; i < n; i++) {
        printpath(i);
        printf("(%d)\n", box[i].distance);
    }
}

int main() {
    input();
    dijkstra();
    output();
    return 0;
}