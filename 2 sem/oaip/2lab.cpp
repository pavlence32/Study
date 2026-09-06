#include <iostream>
#include <ctime>
using namespace std;
struct Ocher
{
    int data;
    Ocher *next, *prev;
} *begin, *end;
void push(Ocher **begin, Ocher **end, int n)
{
    Ocher *p = new Ocher;
    if (*begin != NULL)
    {
        p->data = n;
        p->prev = *end;
        (*end)->next = p;
        p->next = NULL;
        *end = p;
        return;
    }
    p->data = n;
    p->next = NULL;
    p->prev = NULL;
    *begin = p;
    *end = p;
}
void prosmonach(Ocher *begin)
{
    Ocher *p = begin;
    while (p != NULL)
    {
        cout << p->data << '\n';
        p = p->next;
    }
}
void prosmokonec(Ocher *end)
{
    Ocher *p = end;
    while (p != NULL)
    {
        cout << p->data << '\n';
        p = p->prev;
    }
}
void dobavnach(Ocher **begin, int n)
{
    cout << "what add" << '\n';
    cin >> n;
    Ocher *p = new Ocher;
    (*begin)->prev = p;
    p->prev = NULL;
    p->next = *begin;
    p->data = n;
    *begin = p;
}
void del(Ocher **begin, Ocher **end)
{
    Ocher *p = new Ocher;
    p = *begin;
    while (p != NULL)
    {
        Ocher *nextt = p->next;
        if (p == *begin)
        {
            *begin = p->next;
            p->prev = NULL;
        }
        else if (p->next == NULL)
        {
            *begin = NULL;
            *end = NULL;
        }
        else
        {
            p->prev->next = p->next;
            p->next->prev = p->prev->next;
        }
        delete (p);
        p = nextt;
    }
}
void individ(Ocher *begin, Ocher *end)
{
    Ocher *p = begin;
    int max = p->data;
    while (p != NULL)
    {
        if (p->data > max)
            max = p->data;
        p = p->next;
    }
    p = begin->next;
    Ocher *beginbu = NULL;
    Ocher *endbu = NULL;
    while (p->data != max)
    {
        push(&beginbu, &endbu, p->data);
        p = p->next;
    }
    // функцию удаления добавь
    del(&begin, &end);
    prosmonach(beginbu);
}
void ydalmax(Ocher **begin, Ocher **end)
{

    Ocher *p = *begin;

    int max = (*begin)->data;

    while (p != NULL)
    {
        if (p->data > max)
        {
            max = p->data;
        }
        p = p->next;
    }

    p = *begin;
    while (p != NULL)
    {

        Ocher *next = p->next;

        if (p->data == max && p == *begin)
        {

            if (p->next != NULL)
            {
                p->next->prev = NULL;
                *begin = p->next;
            }
            else
            {
                *begin = NULL;
                *end = NULL;
            }
            delete p;
        }

        else if (p->data == max && p == *end)
        {
            *end = p->prev;
            if (*end)
                (*end)->next = NULL;
            delete p;
        }
        else if (p->data == max)
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        }

        p = next;
    }
}

int main()
{
    srand(time(NULL));
    Ocher *begin = NULL;
    Ocher *end = NULL;
    int chos, n;
    while (true)
    {
        cout << "1-CREATE" << '\n';
        cout << "2-DOBAVNACH" << '\n';
        cout << "3-DOBAVKONEC" << '\n';
        cout << "4-PROSMOTRNACH" << '\n';
        cout << "5-PROSMOTRKONEC" << '\n';
        cout << "6-INDIVID" << '\n';
        cout << "7-ydalen" << '\n';
        cin >> chos;
        switch (chos)
        {
        case 1:
            int buf;
            cout << "how many members" << '\n';
            cin >> buf;
            for (int i = 0; i < buf; i++)
                push(&begin, &end, rand() % 101 - 50);
            break;
        case 2:
            int g;
            dobavnach(&begin, g);
            break;
        case 3:
            cout << "what add" << '\n';
            int add;
            cin >> add;
            push(&begin, &end, add);
            break;
        case 4:
            prosmonach(begin);
            break;
        case 5:
            prosmokonec(end);
            break;
        case 6:
            individ(begin, end);
            break;
        case 7:
            ydalmax(&begin, &end);
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "error" << '\n';
            break;
        }
    }
    return 0;
}