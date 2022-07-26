#include <iostream>
#include <stack>

using namespace std;

bool isNum(char ch){
    if(ch >= '0' && ch <= '9'){
        return true;
    }
    else{
        return false;
    }
}

int priority(char op)
{
    int a;

    switch (op){
        case '+':
        case '-':
            a = 1;
            break;

        case '*':
        case '/':
        case '%':
            a = 2;
            break;

        default:
            a = 0;
            break;
    }

    return a;
}

int postf(char *fix, char *temp, int index)
{
    int i = 0, top = 0;
    char stack[100] = {'\0'};
    char op;

    while (1)
    {
        op = fix[i];
        switch (op)
        {
        case '\0':
            index++;
            temp[index] = ' ';
            while (top > 0)
            {
                index++;
                temp[index] = stack[top];
                top--;
            }
            return index;

        case '(':
            //if (top < strlen(stack))// if (top < (sizeof(stack) / sizeof(char)))
            //{
                top++;
                stack[top] = op;
            //}
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            index++;
            temp[index] = ' ';
            while (priority(stack[top]) >= priority(op))
            {
                index++;
                temp[index] = ' ';
                index++;
                temp[index] = stack[top];
                top--;
            }

            //if (top < (sizeof(stack) / sizeof(char)))
            //{
                top++;
                stack[top] = op;
            //}
            break;

        case ')':
            while (stack[top] != '(')
            {
                index++;
                temp[index] = stack[top];
                top--;
            }
            top--;
            break;
        default:
            index++;
            temp[index] = op;

            break;
        }

        i++;
    }
}

int eval(char *my, int index)
{

    int num;
    int a, b;
    //cout << "debug";
    stack<int> st;
    int i = 0;
    while(i < index)
    {
        if (my[i] == '+')
        {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop(); 
            st.push(a + b);
            i++;
        }
        else if (my[i] == '-')
        {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.push(b - a);
            i++;
        }
        else if (my[i] == '*')
        {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.push(a * b);
            i++;
        }
        else if (my[i] == '/')
        {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.push(b / a);
            i++;
        }
        else if (my[i] == '%')
        {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.push(b % a);
            i++;
        }
        else // num or ' ' 
        {
            num = 0;
            int flag = 0;
            while(isNum(my[i])){
                num = num * 10 + my[i] - '0';
                flag = 1;
                i++;
            }
            if(flag == 1){
                st.push(num);
            }
            else{
                i++;
            }
        }
    }
    a = st.top();
    return a;
}
int main()
{
    char in[100];
    cin.getline(in,1000);
    char temp[100];
    int index = -1;
    int c = postf(in, temp, index);
/*
    for (int i = 0; i < c + 1; i++)
    {
        cout << temp[i];
    }*/
    cout << eval(temp, c + 1);
}