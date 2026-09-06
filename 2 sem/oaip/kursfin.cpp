#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
using namespace std;
struct System
{
    int nomer;
    char typeav[10];
    char punnaz[15];
    char vremotp[6];
    char vrempri[6];
};
struct Stack
{
    int low;
    int high;
    Stack *next;
};
FILE *proverka(const char *filename, const char *mode)
{
    FILE *f = fopen(filename, mode);
    if (f == NULL)
    {
        cout << "Dont open\n";
        return NULL;
    }
    return f;
}

Stack *push(Stack *top, int low, int high)
{
    Stack *ptr = new Stack;
    ptr->low = low;
    ptr->high = high;
    ptr->next = top;
    return ptr;
}
Stack *pop(Stack *top, int *low, int *high)
{
    if (top == NULL)
        return NULL;
    *low = top->low;
    *high = top->high;
    Stack *t = top->next;
    delete top;
    return t;
}
void swap(FILE *p, int i, int j)
{
    System a, b;
    fseek(p, i * sizeof(System), SEEK_SET);
    fread(&a, sizeof(System), 1, p);
    fseek(p, j * sizeof(System), SEEK_SET);
    fread(&b, sizeof(System), 1, p);
    fseek(p, i * sizeof(System), SEEK_SET);
    fwrite(&b, sizeof(System), 1, p);
    fseek(p, j * sizeof(System), SEEK_SET);
    fwrite(&a, sizeof(System), 1, p);
}
void copy_file(const char *src, const char *dst)
{
    FILE *s = fopen(src, "rb");
    FILE *d = fopen(dst, "wb");
    System buf;
    while (fread(&buf, sizeof(System), 1, s) == 1)
        fwrite(&buf, sizeof(System), 1, d);
    fclose(s);
    fclose(d);
}
int ydalen(const char *filename)
{
    FILE *p = proverka(filename, "rb+");
    if (!p)
        return 1;
    int route;
    cout << "Vvedite nomer marshruta: ";
    cin >> route;
    System s;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    int found = -1;
    for (int i = 0; i < n; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&s, sizeof(s), 1, p);
        if (s.nomer == route)
        {
            found = i;
            break;
        }
    }
    if (found == -1)
    {
        cout << "Not found";
        fclose(p);
        return 1;
    }
    for (int i = found; i < n - 1; i++)
    {
        fseek(p, (i + 1) * sizeof(System), SEEK_SET);
        fread(&s, sizeof(s), 1, p);
        fseek(p, i * sizeof(System), SEEK_SET);
        fwrite(&s, sizeof(s), 1, p);
    }
    chsize(fileno(p), (n - 1) * sizeof(System));
    fclose(p);
    return 0;
}

int izme(const char *filename)
{
    FILE *p = proverka(filename, "rb+");
    if (!p)
        return 1;
    int buf, chos;
    cout << "Enter number: " << endl;
    cin >> buf;
    System s;
    int i = 0;
    while (fread(&s, sizeof(s), 1, p) == 1)
    {
        if (s.nomer == buf)
        {
            cout << "What to change: " << endl;
            cout << "1-Number :" << endl;
            cout << "2-Type" << endl;
            cout << "3-Destination" << endl;
            cout << "4-Departure time" << endl;
            cout << "5-Arrival time" << endl;
            cin >> chos;
            switch (chos)
            {
            case 1:
            {
                cout << "Enter new number: " << endl;
                cin >> s.nomer;
                fseek(p, -(long)sizeof(System), SEEK_CUR);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 2:
            {
                cout << "Enter new type: " << endl;
                cin.ignore();
                cin.getline(s.typeav, 10);
                fseek(p, -(long)sizeof(System), SEEK_CUR);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 3:
            {
                cout << "Enter new destination: " << endl;
                cin.ignore();
                cin.getline(s.punnaz, 15);
                fseek(p, -(long)sizeof(System), SEEK_CUR);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 4:
            {
                cout << "Enter new departure time:  " << endl;
                cin.ignore();
                cin.getline(s.vremotp, 6);
                fseek(p, -(long)sizeof(System), SEEK_CUR);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 5:
            {
                cout << "Enter new arrival time: " << endl;
                cin.ignore();
                cin.getline(s.vrempri, 6);
                fseek(p, -(long)sizeof(System), SEEK_CUR);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            default:
                cout << "not correct choose";
                return 0;
            }
        }
    }
    fclose(p);
    return 0;
}
void quicksorts(const char *filename)
{
    FILE *g = proverka(filename, "rb+");
    if (!g)
        return;
    fseek(g, 0, SEEK_END);
    Stack *top = NULL;
    int left, right;
    int l, r;
    System bufr, bufl, pivot;
    top = push(top, 0, (ftell(g) / sizeof(System)) - 1);
    while (top != NULL)
    {
        top = pop(top, &left, &right);
        l = left + 1;
        r = right;
        fseek(g, left * sizeof(System), SEEK_SET);
        fread(&pivot, sizeof(System), 1, g);
        while (l <= r)
        {
            fseek(g, l * sizeof(System), SEEK_SET);
            fread(&bufl, sizeof(System), 1, g);
            fseek(g, r * sizeof(System), SEEK_SET);
            fread(&bufr, sizeof(System), 1, g);
            while (l <= r && strcmp(bufl.punnaz, pivot.punnaz) < 0)
            {
                l++;
                fseek(g, l * sizeof(System), SEEK_SET);
                fread(&bufl, sizeof(System), 1, g);
            }
            while (l <= r && strcmp(bufr.punnaz, pivot.punnaz) >= 0)
            {
                r--;
                fseek(g, r * sizeof(System), SEEK_SET);
                fread(&bufr, sizeof(System), 1, g);
            }
            if (l <= r)
            {
                swap(g, l, r);
                l++;
                r--;
            }
        }
        swap(g, left, r);
        if (left < r - 1)
            top = push(top, left, r - 1);
        if (r + 1 < right)
            top = push(top, r + 1, right);
    }
    fclose(g);
}
int vstafsort(const char *filename)
{
    FILE *p = proverka(filename, "rb+");
    if (!p)
        return 1;
    System buf, buf1;
    int j;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 1; i < n; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&buf, sizeof(buf), 1, p);
        j = i - 1;
        while (j >= 0)
        {
            fseek(p, j * sizeof(System), SEEK_SET);
            fread(&buf1, sizeof(buf1), 1, p);
            if (strcmp(buf1.vrempri, buf.vrempri) <= 0)
                break;
            fseek(p, (j + 1) * sizeof(System), SEEK_SET);
            fwrite(&buf1, sizeof(buf1), 1, p);
            j -= 1;
        }
        fseek(p, (j + 1) * sizeof(System), SEEK_SET);
        fwrite(&buf, sizeof(System), 1, p);
    }
    fclose(p);
    return 0;
}
int viborsort(const char *filename)
{
    FILE *p = proverka(filename, "rb+");
    if (!p)
        return 1;
    System min, s;
    int h;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 0; i < n - 1; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&min, sizeof(min), 1, p);
        h = i;
        for (int j = i + 1; j < n; j++)
        {
            fseek(p, j * sizeof(System), SEEK_SET);
            fread(&s, sizeof(s), 1, p);
            if (strcmp(s.vremotp, min.vremotp) < 0)
            {
                min = s;
                h = j;
            }
        }
        if (h == i)
            continue;
        swap(p, i, h);
    }
    fclose(p);
    return 0;
}
int create(const char *filename)
{
    int choose;
    FILE *p = proverka(filename, "wb");
    if (!p)
        return 1;
    cout << "Example: 25 Bmw London 12:45 13:09" << endl;
    cout << "Enter data :" << endl;
    System s;
    while (true)
    {
        cout << " number :" << endl;
        cin >> s.nomer;
        cin.ignore();
        cout << "Type" << endl;
        cin.getline(s.typeav, 10);
        cout << "Destination" << endl;
        cin.getline(s.punnaz, 15);
        cout << "Departure time" << endl;
        cin.getline(s.vremotp, 6);
        cout << "Arrival time" << endl;
        cin.getline(s.vrempri, 6);
        fwrite(&s, sizeof(s), 1, p);
        cout << "more?" << "\n";
        cout << "1-NO";
        cin >> choose;
        if (choose == 1)
            break;
    }
    fclose(p);
    return 0;
}
int dobav(const char *filename)
{
    FILE *p = proverka(filename, "ab");
    if (!p)
        return 1;
    cout << "Adding new record: " << endl;
    System s;
    cout << "record number:" << endl;
    cin >> s.nomer;
    cin.ignore();
    cout << "Type of transport" << endl;
    cin.getline(s.typeav, 10);
    cout << "Destination :" << endl;
    cin.getline(s.punnaz, 15);
    cout << "Departure time" << endl;
    cin.getline(s.vremotp, 6);
    cout << "Arrival time" << endl;
    cin.getline(s.vrempri, 6);
    fwrite(&s, sizeof(s), 1, p);
    fclose(p);
    return 0;
}
int pros(const char *filename)
{
    FILE *p = proverka(filename, "rb");
    if (!p)
        return 1;
    System s;
    while (fread(&s, sizeof(s), 1, p) == 1)
    {
        cout << "Number:" << s.nomer << "| " << "Type:" << s.typeav << "| " << "Destination:" << s.punnaz << "| " << "Departure time:" << s.vremotp << "| " << "Arrival time:" << s.vrempri << endl;
    }
    fclose(p);
    return 0;
}
int vremotp(const char *filename)
{
    FILE *p = proverka(filename, "rb");
    if (!p)
        return 1;
    System s;
    char buf[6];
    cout << "Enter departure time" << '\n';
    cin.getline(buf, 6);
    while (fread(&s, sizeof(s), 1, p) == 1)
    {
        if (strcmp(s.vremotp, buf) == 0)
        {
            cout << "Found:" << '\n';
            cout << "Destination:" << s.punnaz << "| " << "Number:" << s.nomer << "| " << "Type:" << s.typeav << "| " << "Arrival time:" << s.vrempri << endl;
        }
    }
    fclose(p);
    return 0;
}
int punnaz(const char *filename, const char *bufname)
{
    copy_file(filename, bufname);
    quicksorts(bufname);
    FILE *p = proverka(bufname, "rb+");
    if (!p)
        return 1;
    char arrr[15];
    cout << "Enter destination" << '\n';
    cin.getline(arrr, sizeof(arrr));
    fseek(p, 0, SEEK_END);
    int left = 0, i = 0, j = 0;
    int right = ftell(p) / sizeof(System) - 1;
    System s;
    while (left <= right)
    {
        int mid = (right + left) / 2;
        fseek(p, mid * sizeof(System), SEEK_SET);
        fread(&s, sizeof(System), 1, p);
        if (strcmp(s.punnaz, arrr) == 0)
        {
            cout << "Result: " << '\n';
            cout << "Number:" << s.nomer << "| " << "Type:" << s.typeav << "| " << "Departure time:" << s.vremotp << "| " << "Arrival time:" << s.vrempri << endl;
            i = mid - 1;
            j = mid + 1;
            while (i >= left)
            {
                fseek(p, i * sizeof(System), SEEK_SET);
                fread(&s, sizeof(System), 1, p);
                if (strcmp(s.punnaz, arrr) == 0)
                {
                    cout << "Number:" << s.nomer << "| " << "Type:" << s.typeav << "| " << "Departure time:" << s.vremotp << "| " << "Arrival time:" << s.vrempri << endl;
                }
                i--;
            }
            fseek(p, j * sizeof(System), SEEK_SET);
            while (j <= right)
            {
                fread(&s, sizeof(System), 1, p);
                if (strcmp(s.punnaz, arrr) == 0)
                {
                    cout << "Number:" << s.nomer << "| " << "Type:" << s.typeav << "| " << "Departure time:" << s.vremotp << "| " << "Arrival time:" << s.vrempri << endl;
                }
                j++;
            }
            break;
        }
        else if (strcmp(s.punnaz, arrr) < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    fclose(p);
    return 0;
}
int poiskpriz(const char *filename, const char *bufname, const char *filenamh)
{
    copy_file(filename, bufname);
    viborsort(bufname);
    FILE *f = proverka(bufname, "rb+");
    if (!f)
        return 1;
    char bufe[15];
    char vrem[6];
    System s;
    int choose;
    cout << "Where show\n1-console\n2-file\n";
    cin >> choose;
    cin.ignore();
    cout << "Enter destination " << endl;
    cin.getline(bufe, sizeof(bufe));
    cout << "Enter time" << endl;
    cin.getline(vrem, 6);
    switch (choose)
    {
    case 1:
    {
        while (fread(&s, sizeof(System), 1, f) == 1)
        {
            if (strcmp(s.vrempri, vrem) <= 0 && strcmp(bufe, s.punnaz) == 0)
                cout << "Type: " << s.typeav << "\nDeparture: " << s.vremotp << "\n";
        }
        break;
    }
    case 2:
    {
        FILE *k = proverka(filenamh, "w");
        if (!k)
            return 1;
        while (fread(&s, sizeof(System), 1, f) == 1)
        {
            if (strcmp(s.vrempri, vrem) <= 0 && strcmp(bufe, s.punnaz) == 0)
                fprintf(k, "Type: %s Departure: %s\n", s.typeav, s.vremotp);
        }
        fclose(k);
        break;
    }
    default:
        cout << "Not correct choose" << endl;
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}
int staticiok(const char *filename, const char *filenamh)
{
    FILE *p = proverka(filename, "rb");
    if (!p)
        return 1;
    char typebuf[100];
    char vremya[6];
    int y = 0;
    int choose;
    System s;
    cout << "Where show\n1-console\n2-file\n";
    cin >> choose;
    cin.ignore();
    cout << "Enter type and minimum departure time: " << endl;
    cin.getline(typebuf, sizeof(typebuf));
    cin.getline(vremya, 6);
    switch (choose)
    {
    case 1:
    {
        while (fread(&s, sizeof(System), 1, p) == 1)
        {
            if (strcmp(typebuf, s.typeav) == 0 && strcmp(s.vremotp, vremya) > 0)
            {
                cout << "Type: " << s.typeav << "\nDeparture: " << s.vremotp << "\nDestination: " << s.punnaz << "\n\n";
                y++;
            }
        }
        cout << "The number of possible paths: " << y << '\n';
        break;
    }
    case 2:
    {
        FILE *g = proverka(filenamh, "w");
        if (!g)
        {
            fclose(p);
            return 1;
        }
        while (fread(&s, sizeof(System), 1, p) == 1)
        {
            if (strcmp(typebuf, s.typeav) == 0 && strcmp(s.vremotp, vremya) > 0)
            {
                fprintf(g, "Type: %s Departure: %s Destination: %s\n", s.typeav, s.vremotp, s.punnaz);
                y++;
            }
        }
        fprintf(g, "\nThe number of possible paths: %d\n", y);
        fclose(g);
        break;
    }
    default:
        cout << "Not correct choose" << endl;
        fclose(p);
        return 1;
    }
    fclose(p);
    return 0;
}
int main()
{
    char filename[256] = "sigma.bin";
    const char *bufname = "buf.bin";
    const char *filetxt = "result.txt";
    int choose;
    while (true)
    {
        cout << "1. Create file " << endl;
        cout << "2. View all records" << endl;
        cout << "3. Search by departure time" << endl;
        cout << "4. Search by destination" << endl;
        cout << "5. Search (destination + time)" << endl;
        cout << "6. Quick sort by destination" << endl;
        cout << "7. Selection sort by departure time" << endl;
        cout << "8. Insertion sort by arrival time" << endl;
        cout << "9. Statistics" << endl;
        cout << "10. Delete" << endl;
        cout << "11. Added" << endl;
        cout << "12. Change" << endl;
        cout << "13. New file" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";
        cin >> choose;
        cin.ignore();

        switch (choose)
        {
        case 1:
            create(filename);
            break;
        case 2:
            pros(filename);
            break;
        case 3:
            vremotp(filename);
            break;
        case 4:
            punnaz(filename, bufname);
            break;
        case 5:
            poiskpriz(filename, bufname, filetxt);
            break;
        case 6:
            quicksorts(filename);
            pros(filename);
            break;
        case 7:
            viborsort(filename);
            break;
        case 8:
            vstafsort(filename);
            break;
        case 9:
            staticiok(filename, filetxt);
            break;
        case 10:
            ydalen(filename);
            break;
        case 11:
            dobav(filename);
            break;
        case 12:
            izme(filename);
            break;
        case 13:
            int buf;
            cout << "1-Work with old\n2-Work with new\nYour choose: ";
            cin >> buf;
            cin.ignore();
            if (buf == 1)
            {
                cout << "Enter filename: \n";
                cin.getline(filename, 256);
            }
            else
            {
                cout << "Enter new filename: \n";
                cin.getline(filename, 256);
                create(filename);
            }
            break;
        case 0:
            cout << "Exit" << endl;
            return 0;
        default:
            cout << "Not correct choose" << endl;
            break;
        }
    }
    return 0;
}
