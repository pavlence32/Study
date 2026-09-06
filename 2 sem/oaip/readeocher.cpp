#include <iostream>
using namespace std;
struct Ocher
{
    int info;
    Ocher *next;
    Ocher *prev;
};
void create(Ocher *&begin, Ocher *&end, int m)
{
    Ocher *p = new Ocher;
    if (!begin)
    {
        begin = p;
        end = p;
        p->next = NULL;
        p->prev = NULL;
        p->info = m;
    }
    else
    {
        end->next = p;
        p->prev = end;
        p->next = NULL;
        p->info = m;
        end = p;
    }
}
void deleteuzel(Ocher *&p, Ocher *&begin, Ocher *&end)
{
    if (!p->prev)
    {
        begin = p->next;
        p->next->prev = NULL;
        delete (p);
    }
    else if (!p->next)
    {
        p->prev->next = NULL;
        end = p->prev;
        delete (p);
    }
    else
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete (p);
    }
}
void change(Ocher *&begin, Ocher *&end)
{
    Ocher *p = begin;
    int min = p->info;
    Ocher *buf = new Ocher;
    while (p)
    {
        if (p->info < min)
        {
            min = p->info;
            buf = p;
        }
        p = p->next;
    }
    Ocher *begindo = begin;
    Ocher *prevforbeg = buf->prev;
    Ocher *mibforbeg = buf->next;
    Ocher *prevnext = buf->next->prev;
    Ocher *nextprev = buf->prev->next;
    Ocher *bufe = begin->next;
    begin = buf;
    buf->prev = NULL;
    buf->next = bufe;
    begin->next->prev = buf; // вот так реально меняется указатель в узле
    begindo->next = mibforbeg;
    begindo->prev = prevforbeg;
    begindo->prev->next = prevnext;
    begindo->next->prev = nextprev;
}

void vstavka(Ocher *&p, int m)
{
    Ocher *ptr = new Ocher;
    p->prev->next = ptr;
    ptr->prev = p->prev;
    p->prev = ptr;
    ptr->next = p;
    ptr->info = m;
}
void task(Ocher *begin)
{
    Ocher *buf = begin;
    int i = 0;
    while (buf)
    {
        i++;
        if (i % 3 == 0)
        {
            vstavka(buf, 67);
        }
        buf = buf->next;
    }
}

Ocher *tonewocher(Ocher *&p, Ocher *&begin, Ocher *&end, Ocher *&endnew)
{
    Ocher *buf = new Ocher;
    Ocher *beginnew = new Ocher;
    while (buf)
    {
        if (buf->info < 0)
        {
            create(beginnew, endnew, buf->info);
            deleteuzel(buf, begin, end);
        }
    }
    return beginnew;
}
void vstafperedkaztret(Ocher *&b, Ocher *&e)
{
    Ocher *p = b;
    int i = 1, buf;
    while (p && p->next)
    {
        if (i % 3 == 0)
        {
            Ocher *tmp = new Ocher;
            cout << "what add\n";
            cin >> buf;
            tmp->info = buf;
            tmp->next = p;
            tmp->prev = p->prev;
            p->prev->next = tmp;
            p->prev = tmp;
        }
        i++;
        p = p->next;
    }
}
void delkazhtret(Ocher *&b, Ocher *&e)
{
    Ocher *p = b;
    Ocher *tmp = NULL;
    int i = 1, buf;
    while (p && p->next)
    {
        if (i % 3 == 0)
        {
            tmp = p;
            if (e == p)
                e = p->prev;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p = p->next;
            i++;
            delete (tmp);
        }
        else
        {
            i++;
            p = p->next;
        }
    }
}
void peremeshpolozh(Ocher *&b, Ocher *&e, Ocher *&b1, Ocher *&e1)
{
    Ocher *p = b;
    Ocher *tmp = NULL;
    while (p)
    {
        if (p->info < 0)
        {
            tmp = p->next;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            if (e == p)
                e = p->prev;
            if (!b1)
            {
                b1 = p;
                e1 = p;
                p->next = NULL;
                p->prev = NULL;
            }
            else
            {
                e1->next = p;
                p->prev = e1;
                p->next = NULL;
                e1 = p;
            }
            p = tmp;
        }
        else
        {
            p = p->next;
        }
    }
}
void delnechet(Ocher *&begin, Ocher *&end)
{
    Ocher *p = begin;
    while (p)
    {
        if (p->info % 2 != 0)
        {
            Ocher *t = p->next;
            if (p == begin)
            {
                begin = p->next;
                p->next->prev = NULL;
            }
            else if (p == end)
            {
                end = p->prev;
                p->prev->next = NULL;
            }
            else
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            delete p;
            p = t;
        }
        else
            p = p->next;
    }
}
void peremeshepopoz(Ocher *&b, Ocher *&e, Ocher *&b1, Ocher *&e1)
{
    Ocher *p = b;
    int i = 1;
    while (p)
    {
        if (i % 2 != 0)
        {
            Ocher *t = p->next;
            if (p->next)
                p->next->prev = p->prev;
            if (p->prev)
                p->prev->next = p->next;
            if (p == b)
                b = p->next;
            if (p == e)
                e = p->prev;
            if (!b1)
            {
                p->next = NULL;
                p->prev = NULL;
                b1 = p;
                e1 = p;
            }
            else
            {
                e1->next = p;
                p->prev = e1;
                p->next = NULL;
                e1 = p;
            }
            p = t;
        }
        else
            p = p->next;
        i++;
    }
}
void mid(Ocher *&begin, Ocher *&end)
{
    if (!begin || begin == end)
        return;
    Ocher *p = begin->next->next->next->next;
    Ocher *q = new Ocher;
    q->info = 7676767676767;
    q->prev = p;
    q->next = p->next;
    p->next->prev = q;
    p->next = q;
}
int main()
{
    Ocher *begin = NULL, *end = NULL;
    Ocher *begin1 = NULL, *end1 = NULL;
    create(begin, end, 1);
    create(begin, end, 2);
    create(begin, end, -3);
    create(begin, end, 4);
    create(begin, end, -5);
    cout << "before all: ";
    Ocher *p = begin;
    while (p)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;
    peremeshepopoz(begin, end, begin1, end1);
    cout << "Before (main): ";
    p = begin;
    while (p)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;
    cout << "After (new): ";
    p = begin1;
    while (p)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << endl;
    return 0;
}