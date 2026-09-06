#include <iostream>
#include <string.h>
using namespace std;
struct Stack
{
    double data;
    Stack *next;
} *begin;
int priority(char a)
{
    if (a == '+' || a == '-')
        return 1;
    else if (a == '*' || a == '/')
        return 2;
    else if (a == '^')
        return 3;
    else if (a == ')')
        return 4;
    else if (a == '(')
        return 0;
    else
        return -1;
}
Stack *push(Stack **begin, char c)
{
    Stack *ptr = new struct Stack;
    ptr->data = c;
    ptr->next = *begin;
    return ptr;
}
Stack *pushch(Stack **begin, double r)
{
    Stack *ptr = new struct Stack;
    ptr->data = r;
    ptr->next = *begin;
    return ptr;
}
Stack *del(Stack **nach)
{
    Stack *ptr = *nach;
    while (ptr != NULL)
    {
        ptr = (*nach)->next;
        delete (*nach);
        *nach = ptr;
    }
    return *nach;
}
Stack *dobov(Stack **nach, char a)
{
    Stack *ptr = new Stack;
    ptr->data = a;
    ptr->next = *nach;
    *nach = ptr;
    return ptr;
}
Stack *ydalposol(Stack **nach)
{
    Stack *ptr = *nach;
    *nach = (*nach)->next;
    delete (ptr);
    return *nach;
}
char *preobroz(const char *arr, Stack **begin)
{
    char *rez = new char[100];
    int j = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
            rez[j++] = arr[i];
        else if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/')
        {
            while (*begin != NULL && (*begin)->data != '(' && priority((*begin)->data) >= priority(arr[i]))
            {
                rez[j++] = (*begin)->data;
                *begin = ydalposol(&(*begin));
            }
            *begin = push(&(*begin), arr[i]);
        }
        else if (arr[i] == '(')
        {
            *begin = push(&(*begin), arr[i]);
        }
        else if (arr[i] == ')')
        {

            while ((*begin)->data != '(')
            {
                //(*begin)->data=rez[i];
                rez[j++] = (*begin)->data;
                ydalposol(&(*begin));
            }
            Stack *ptr = (*begin)->next;
            delete (*begin);
            *begin = ptr;
        }
    }
    while (*begin != NULL)
    {
        rez[j++] = (*begin)->data;
        *begin = ydalposol(&(*begin));
    }
    rez[j] = '\0';
    return rez;
}
double preobrozf(char *arr, Stack **begin)
{
    int l = 0;
    char rez[100];
    double skorer[26];
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            cout << "Enter value " << arr[i] << endl;
            cin >> skorer[arr[i] - 'a'];
        }
    }

    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            *begin = pushch(&(*begin), skorer[arr[i] - 'a']);
        }
        else if (arr[i] == '+')
        {
            /*Stack *ptr = (*begin)->next->next;
            int buf;
            buf = (*begin)->data + (*begin)->next->data;
            while (*begin != ptr)
                *begin = ydalposol(&(*begin));
                push(&(*begin),buf);
                buf=0;
                */
            double a, b;
            a = (*begin)->data;
            *begin = ydalposol(&(*begin));
            b = (*begin)->data;
            *begin = ydalposol(&(*begin));
            *begin = pushch(&(*begin), b + a);
        }
        else if (arr[i] == '-')
        {
            double a = 0, b = 0;
            a = (*begin)->data;
            *begin = ydalposol(&(*begin));
            b = (*begin)->data;
            *begin = ydalposol(&(*begin));
            *begin = pushch(&(*begin), b - a);
        }
        else if (arr[i] == '*')
        {
            double a = 0, b = 0;
            a = (*begin)->data;
            *begin = ydalposol(&(*begin));
            b = (*begin)->data;
            *begin = ydalposol(&(*begin));
            *begin = pushch(&(*begin), b * a);
        }
        else if (arr[i] == '/')
        {
            double a = 0, b = 0;
            a = (*begin)->data;
            *begin = ydalposol(&(*begin));
            b = (*begin)->data;
            *begin = ydalposol(&(*begin));
            *begin = pushch(&(*begin), b / a);
        }
    }
    return (*begin)->data;
}

int main()
{
    char arr[100];
    Stack *begin = NULL;
    cout << "Enter expression: " << '\n';
    cin.getline(arr, sizeof(arr));
    char *tmp = preobroz(arr, &begin);
    cout << tmp << endl;
    delete[] tmp;
    begin = del(&begin);
    char *tmp2 = preobroz(arr, &begin);
    cout << preobrozf(tmp2, &begin);
    delete[] tmp2;
    return 0;
}