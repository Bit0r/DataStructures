#include <ctype.h>
#include <stack>
#include <stdbool.h>
#include <stdio.h>

void trans(char *, char *);
double compvalue(char *);

int main() {
    char exp[128], postexp[128];
    gets(exp);
    trans(exp, postexp);
    puts(postexp);
    printf("%lf\n", compvalue(postexp));
    return 0;
}

void trans(char *exp, char *postexp) {
    std::stack<char> postfix;
    char e;
    while (*exp) {
        switch (*exp) {
        case '(':
            postfix.push('(');
            exp++;
            break;
        case ')':
            e = postfix.top();
            postfix.pop();
            while (e != '(') {
                *postexp++ = e;
                e = postfix.top();
                postfix.pop();
            }
            exp++;
            break;
        case '+':
        case '-':
            while (!postfix.empty()) {
                e = postfix.top();
                if (e != '(') {
                    *postexp++ = e;
                    e = postfix.top();
                    postfix.pop();
                } else
                    break;
            }
            postfix.push(*exp);
            exp++;
            break;
        case '*':
        case '/':
            while (!postfix.empty()) {
                e = postfix.top();
                if (e == '*' || e == '/') {
                    *postexp++ = e;
                    postfix.pop();
                } else
                    break;
            }
            postfix.push(*exp);
            exp++;
            break;
        default:
            for (; isdigit(*exp); exp++, postexp++)
                *postexp = *exp;
            *postexp++ = '#';
        }
    }
    for (; !postfix.empty(); postfix.pop()) {
        e = postfix.top();
        *postexp++ = e;
    }
    *postexp = '\0';
}

double compvalue(char *postexp) {
    std::stack<double> operand;
    double a, b, temp;
    while (*postexp) {
        for (temp = 0; isdigit(*postexp); postexp++)
            temp = temp * 10 + *postexp - '0';
        if (temp) {
            operand.push(temp);
            postexp++;
        }
        if (*postexp == '+' || *postexp == '-' || *postexp == '*' ||
            *postexp == '/') {
            b = operand.top();
            operand.pop();
            a = operand.top();
            operand.pop();
            switch (*postexp) {
            case '+':
                operand.push(a + b);
                break;
            case '-':
                operand.push(a - b);
                break;
            case '*':
                operand.push(a * b);
                break;
            case '/':
                if (b)
                    operand.push(a / b);
                else
                    puts("除0错误");
                break;
            }
            postexp++;
        }
    }
    temp = operand.top();
    operand.pop();
    return temp;
}
