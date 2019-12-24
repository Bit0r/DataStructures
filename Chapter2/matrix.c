#include <stdio.h>

typedef struct {
    int tup[64][3];
    int len;
    int rows;
    int cols;
} Matrix;

void matrix_input(Matrix *matrix) {
    //前3个数为数据的组数，矩阵的列数，矩阵的的行数
    scanf("%d%d%d", &matrix->len, &matrix->rows, &matrix->cols);
    //第二行开始，每行一组数据，表示矩阵的一个非零元(i,j,a[i][j])
    for (int i = 0; i < matrix->len; i++)
        scanf("%d%d%d", &matrix->tup[i][0], &matrix->tup[i][1],
              &matrix->tup[i][2]);
}

int matrix_find(Matrix *matrix, int i, int j) {
    int index;
    for (index = 0; index < matrix->len; index++)
        if (matrix->tup[index][0] == i && matrix->tup[index][1] == j)
            return index;
    return -1;
}

void matrix_add(Matrix *a, Matrix *b, Matrix *c) {
    if(a->rows!=b->rows||a->cols!=b->cols){
        puts("矩阵a和矩阵b不是同型矩阵，不能相加");
        return;
    }
    int i, j;
    c->len = 0;
    c->rows = a->rows;
    c->cols = a->cols;
    for (i = 0; i < a->len; i++) {
        j = matrix_find(b, a->tup[i][0], a->tup[i][1]);
        if (j == -1) {
            c->tup[c->len][0] = a->tup[i][0];
            c->tup[c->len][1] = a->tup[i][1];
            c->tup[c->len][2] = a->tup[i][2];
            c->len++;
        } else if (a->tup[i][2] + b->tup[j][2] != 0) {
            c->tup[c->len][0] = a->tup[i][0];
            c->tup[c->len][1] = a->tup[i][1];
            c->tup[c->len][2] = a->tup[i][2] + b->tup[j][2];
            c->len++;
        }
    }
    for (j = 0; j < b->len; j++) {
        i = matrix_find(a, b->tup[j][0], b->tup[j][1]);
        if (i == -1) {
            c->tup[c->len][0] = b->tup[j][0];
            c->tup[c->len][1] = b->tup[j][1];
            c->tup[c->len][2] = b->tup[j][2];
            c->len++;
        }
    }
}

void matrix_mult(Matrix *a, Matrix *b, Matrix *c) {
    if (a->cols != b->rows) {
        puts("矩阵a的列数不等于矩阵b的行数，不能进行矩阵乘法");
        return;
    }
    int i, j, index_a, index_b, count, s,temp[a->cols];
    c->rows = a->rows;
    c->cols = b->cols;
    c->len = 0;
    for (i = 1; i <= a->rows; i++) {
        for (j = 1; j <= b->cols; j++) {
            for(count =0;count <a->cols;count++)
                temp[count] = matrix_find(a, i, count+1);
            for (count = 1, s = 0; count <= a->cols; count++) {
                index_a=temp[count-1];
                if (index_a != -1) {
                    index_b = matrix_find(b, count, j);
                    if (index_b != -1)
                        s += a->tup[index_a][2] * b->tup[index_b][2];
                }
            }
            if (s != 0) {
                c->tup[c->len][0] = i;
                c->tup[c->len][1] = j;
                c->tup[c->len][2] = s;
                c->len++;
            }
        }
    }
}

void matrix_print(Matrix *matrix) {
    int i, j, index;
    for (i = 1; i <= matrix->rows; i++) {
        for (j = 1; j <= matrix->cols; j++) {
            index = matrix_find(matrix, i, j);
            if (index != -1)
                printf("%4d", matrix->tup[index][2]);
            else
                printf("   0");
            putchar(' ');
        }
        putchar('\n');
    }
}

int main() {
    Matrix a, b, c, d;
    matrix_input(&a);
    matrix_input(&b);
    matrix_add(&a, &b, &c);
    matrix_print(&c);
    putchar('\n');
    matrix_mult(&a, &b, &d);
    matrix_print(&d);
    return 0;
}