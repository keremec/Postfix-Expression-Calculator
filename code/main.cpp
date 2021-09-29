#include <iostream>
#include <string>
#include <fstream>
#include "myStack.h"

#define MAX_VALUE 100


class infixToPostfix {
public:
    void convertToPostfix();

    static bool precedence(char opr1, char opr2);

    void getInfix(string x);

    void showInfix();

    void showPostfix();

    explicit infixToPostfix(string = "");

    string getPfx();

private:
    string infx;
    string pfx;
};

void infixToPostfix::getInfix(string x) {
    x.pop_back();
    infx = move(x);
}

void infixToPostfix::showInfix() {
    cout << "Infix Expression: " << infx << endl;
}

void infixToPostfix::showPostfix() {
    cout << "Postfix Expression: " << pfx << endl;
}

infixToPostfix::infixToPostfix(string x) {
    x.pop_back();
    infx = move(x);
}

string infixToPostfix::getPfx() {
    return pfx;
}

void infixToPostfix::convertToPostfix() {
    stackType<char> stack(MAX_VALUE);
    for (char i : infx) {
        if (i == '(') { stack.push(i); }
        else if (i == ')') {
            while (stack.top() != '(') {
                pfx += stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else if (i == '+' || i == '-') {
            if (!stack.isEmptyStack()) {
                if (stack.top() == '(') {
                    stack.push(i);
                }
                else {
                    pfx += stack.top();
                    stack.pop();
                    if (!stack.isEmptyStack()) {
                        if (stack.top() == '+' || stack.top() == '-') {
                            pfx += stack.top();
                            stack.pop();
                        }
                    }
                    stack.push(i);
                }
            }
            else { stack.push(i); }
        }
        else if (i == '*' || i == '/') {
            if (!stack.isEmptyStack()) {
                if (stack.top() == '*' || stack.top() == '/') {
                    pfx += stack.top();
                    stack.pop();
                    if (!stack.isEmptyStack()) {
                        if (stack.top() == '*' || stack.top() == '/') {
                            pfx += stack.top();
                            stack.pop();
                        }
                    }
                    stack.push(i);
                }
                else { stack.push(i); }
            }
            else { stack.push(i); }
        }
        else { pfx += i; }
    }
    while (!stack.isEmptyStack()) {
        pfx += stack.top();
        stack.pop();
    }
}

bool infixToPostfix::precedence(char opr1, char opr2) {
    return (opr1 == '*' || opr1 == '/' || opr2 == '+' || opr2 == '-');
}


int evaluatePostfix(char *exp) {
    stackType<char> stack(MAX_VALUE);
    for (int i = 0; exp[i]; ++i) {
        if (isalpha(exp[i])) { return -1; }
        if (isdigit(exp[i])) { stack.push(exp[i] - '0'); }
        else {
            int val1 = stack.top();
            stack.pop();
            int val2 = stack.top();
            stack.pop();
            switch (exp[i]) {
                case '+':
                    stack.push(val2 + val1);
                    break;
                case '-':
                    stack.push(val2 - val1);
                    break;
                case '*':
                    stack.push(val2 * val1);
                    break;
                case '/':
                    stack.push(val2 / val1);
                    break;
            }
        }
    }
    return stack.top();
}

int main() {
    ifstream file("infixData.txt");

    string infx;
    string pfx;
    while (getline(file, infx)) {
        infixToPostfix A(infx);
        A.getInfix(infx);
        A.convertToPostfix();
        A.showInfix();
        A.showPostfix();
        pfx = A.getPfx();
        char *exp = &pfx[0];
        int e = evaluatePostfix(exp);
        if (e != -1) { cout << "Result of Postfix Expression: " << e << endl; }
        cout << endl;
    }
    return 0;
}
