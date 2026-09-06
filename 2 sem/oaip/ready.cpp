#include <iostream>
using namespace std;
struct Stack
{
    int info;
    Stack *next;
};
void create(Stack *&begin, int n)
{
    Stack *ptr = new Stack;
    ptr->next = begin;
    ptr->info = n;
    begin = ptr;
}
void taskperenosotric(Stack *&begin, Stack *&beginold)
{
    create(begin, 0);
    Stack *p = begin;
    Stack *t = NULL;
    while (p && p->next)
    {
        if (p->next->info < 0)
        {
            t = p->next;
            p->next = p->next->next;
            t->next = beginold;
            beginold = t;
        }
        else
            p = p->next;
    }
    p = begin;
    begin = begin->next;
    delete p;
}
void delvtoroizad(Stack *&begin)
{
    Stack *p = begin;
    while (p->next->next->next)
        p = p->next;
    Stack *y = p->next;
    p->next = p->next->next;
    delete (y);
}
void maxvnach(Stack *&begin)
{
    create(begin, 0);
    Stack *p = begin->next;
    int max = p->info;
    while (p)
    {
        if (max < p->info)
            max = p->info;
        p = p->next;
    }
    p = begin;
    while (p)
    {
        if (p->next->info == max)
        {
            if (begin->next == p->next)
            {
                p = begin;
                begin = begin->next;
                delete (p);
                return;
            }
            Stack *t = p->next;
            p->next = t->next;
            t->next = begin->next;
            begin->next = t;
            break;
        }
        p = p->next;
    }
    p = begin;
    begin = begin->next;
    delete (p);
}
void dobavperedotr(Stack *&begin)
{
    create(begin, 21);
    Stack *p = begin;
    while (p && p->next)
    {
        if (p->next->info < 0)
        {
            Stack *Q = new Stack;
            Q->info = 9999;
            Q->next = p->next;
            p->next = Q;
            p = Q->next;
        }
        else
            p = p->next;
    }
    p = begin;
    begin = begin->next;
    delete (p);
}
void stekvstaf(Stack *&begin1, Stack *&begin2)
{
    Stack *g = begin2;
    while (g->next)
        g = g->next;
    int choose, i = 1;
    cout << "enter poz\n";
    cin >> choose;
    Stack *p = begin1;
    while (p && i != choose)
    {
        p = p->next;
        i++;
    }
    Stack *buf = p->next;
    p->next = begin2;
    g->next = buf;
}

int main()
{
    Stack *begin = NULL;

    create(begin, 67);
    create(begin, 5);
    create(begin, 1);
    create(begin, 4);
    create(begin, 3);

    cout << "Before: ";
    Stack *p = begin;
    while (p)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;

    maxvnach(begin);

    cout << "After: ";
    p = begin;
    while (p)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;

    return 0;
}
