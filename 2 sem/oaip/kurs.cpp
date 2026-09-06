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
    char punnaz[10];
    float vremotp;
    float vrempri;
};
int dobav(const char *filename)
{
    FILE *p = fopen(filename, "ab");
    if (p == NULL)
    {
        cout << "File dont open";
        return 1;
    }
    cout << "Adding new record: " << endl;
    System s;
    cout << "record number:" << endl;
    cin >> s.nomer;
    cin.ignore();
    cout << "Type of transport" << endl;
    cin.getline(s.typeav, 10);
    cout << "Destination :" << endl;
    cin.getline(s.punnaz, 10);
    cout << "Departure time" << endl;
    cin >> s.vremotp;
    cout << "Arrival time" << endl;
    cin >> s.vrempri;
    fwrite(&s, sizeof(s), 1, p);
    fclose(p);
    return 0;
}
int ydalen(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    cout << "Enter numer to delete:" << endl;
    int buf = 0;
    cin >> buf;
    System s;
    fseek(p, 0, SEEK_END);
    int lenght = ftell(p) / sizeof(System);
    for (int i = 0; i < lenght; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&s, sizeof(s), 1, p);
        if (buf == s.nomer)
        {
        }
    }
    fclose(p);
    return 0;
}
int izme(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    int buf, chos;
    cout << "Enter number: " << endl;
    cin >> buf;
    System s;
    fseek(p, 0, SEEK_END);
    for (int i = 0; i < ftell(p) / sizeof(System); i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&s, sizeof(s), 1, p);
        if (s.nomer == buf)
        {
            cout << "What to change: " << endl;
            cout << "1-Flight number :" << endl;
            cout << "2-Type" << endl;
            cout << "3-Destination" << endl;
            cout << "4-Departure time" << endl;
            cout << "5-Arrival time" << endl;
            cin >> chos;
            switch (chos)
            {
            case 1:
            {
                int nimer;
                cout << "Enter new number: " << endl;
                cin >> nimer;
                s.nomer = nimer;
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 2:
            {
                char yut[100];
                cout << "Enter new type: " << endl;
                cin.getline(yut, sizeof(yut));
                strcpy(s.typeav, yut);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 3:
            {
                char yut[100];
                cout << "Enter new destination: " << endl;
                cin.getline(yut, sizeof(yut));
                strcpy(s.punnaz, yut);
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 4:
            {
                float h;
                cout << "Enter new departure time:  " << endl;
                cin >> h;
                s.vremotp = h;
                fwrite(&s, sizeof(System), 1, p);
                break;
            }
            case 5:
            {
                float h;
                cout << "Enter new arrival time: " << endl;
                cin >> h;
                s.vrempri = h;
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

int partition(const char *filename, int low, int high)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    fseek(p, high * sizeof(System), SEEK_SET);
    System pivot;
    fread(&pivot, sizeof(System), 1, p);
    int i = low - 1;
    System buf;
    System buf2;
    for (int j = low; j < high; j++)
    {
        fseek(p, j * sizeof(System), SEEK_SET);
        fread(&buf2, sizeof(System), 1, p);
        if (strcmp(buf2.punnaz, pivot.punnaz) > 0)
        {
            i += 1;
            fseek(p, i * sizeof(System), SEEK_SET);
            fread(&buf, sizeof(System), 1, p);
            fseek(p, i * sizeof(System), SEEK_SET);
            fwrite(&buf2, sizeof(System), 1, p);
            fseek(p, j * sizeof(System), SEEK_SET);
            fwrite(&buf, sizeof(System), 1, p);
        }
    }
    fseek(p, (i + 1) * sizeof(System), SEEK_SET);
    fread(&buf, sizeof(System), 1, p);

    fseek(p, (i + 1) * sizeof(System), SEEK_SET);
    fwrite(&pivot, sizeof(System), 1, p);

    fseek(p, high * sizeof(System), SEEK_SET);
    fwrite(&buf, sizeof(System), 1, p);
    fclose(p);
    return i + 1;
}
void quickSort(const char *filename, int low, int high)
{
    if (low < high)
    {

        int pivot_index = partition(filename, low, high);

        quickSort(filename, low, pivot_index - 1);
        quickSort(filename, pivot_index + 1, high);
    }
}
int vstafsort(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    if (p = NULL)
    {
        cout << "Dont open";
        return 1;
    }
    float current;
    System buf, buf1;
    int j;
    fseek(p, 0, SEEK_END);
    for (int i = 1; i < ftell(p) / sizeof(System); i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&buf, sizeof(buf), 1, p);
        current = buf.vrempri;
        j = i - 1;
        while (j >= 0 && buf.vrempri > current)
        {
            fseek(p, (j + 1) * sizeof(System), SEEK_SET);
            fread(&buf1, sizeof(buf), 1, p);
            buf1.vrempri = buf.vrempri;
            fwrite(&buf1, sizeof(buf), 1, p);
            j -= 1;
        }
        buf1.vrempri = current;
        fwrite(&buf1, sizeof(System), 1, p);
    }
    return 0;
}
int viborsort(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    System min, s, buf;
    int h;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 0; i < n; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&min, sizeof(min), 1, p);
        h = i;
        for (int j = i + 1; j < n; j++)
        {
            fseek(p, j * sizeof(System), SEEK_SET);
            fread(&s, sizeof(s), 1, p);
            if (s.vremotp < min.vremotp)
            {
                min = s;
                h = j;
            }
        }

        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&buf, sizeof(buf), 1, p);
        fseek(p, i * sizeof(System), SEEK_SET);
        fwrite(&min, sizeof(min), 1, p);
        fseek(p, h * sizeof(System), SEEK_SET);
        fwrite(&buf, sizeof(buf), 1, p);
    }
    return 0;
}
int create(const char *filename)
{
    int choose;
    FILE *p = fopen(filename, "wb");
    if (p == NULL)
    {
        cout << "dont open";
        return 1;
    }
    cout << "Example: 25 Bmw London 12.45 13.09" << endl;
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
        cin.getline(s.punnaz, 10);
        cout << "Departure time" << endl;
        cin >> s.vremotp;
        cout << "Arrival time" << endl;
        cin >> s.vrempri;
        fwrite(&s, sizeof(s), 1, p);
        cout << "more?" << "\n";
        cin >> choose;
        if (choose == 1)
            break;
    }
    fclose(p);
    return 0;
}
int pros(const char *filename)
{
    FILE *p = fopen(filename, "rb");
    System s;
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    while (fread(&s, sizeof(s), 1, p) == 1)
    {
        cout << s.nomer << endl;
        cout << s.typeav << endl;
        cout << s.punnaz << endl;
        cout << s.vremotp << endl;
        cout << s.vrempri << endl;
    }
    fclose(p);
    return 0;
}
int delete_by_route(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }

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
int vremotp(const char *filename)
{
    FILE *p = fopen(filename, "rb");
    if (p == NULL)
    {
        cout << "Dont open ";
        return 1;
    }
    System s;
    float buf;
    while (true)
    {
        cout << "Enter departure time" << '\n';
        cin >> buf;
        if (buf * 100 - int(buf * 100) != 0)
            cout << "not correct time";
        else
            break;
    }
    while (fread(&s, sizeof(s), 1, p) == 1)
    {
        if (s.vremotp == buf)
        {
            cout << "Found:" << '\n';
            cout << "Destination" << s.punnaz << '\n';
            cout << "Number" << s.nomer << '\n';
            cout << "Flight type" << s.typeav << '\n';
            cout << "Arrival time" << s.vrempri << '\n';
            cout << endl;
        }
    }
    fclose(p);
    return 0;
}
int punnaz(const char *filename)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    System a, b;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            fseek(p, j * sizeof(System), SEEK_SET);
            fread(&a, sizeof(System), 1, p);
            fread(&b, sizeof(System), 1, p);
            if (strcmp(a.punnaz, b.punnaz) > 0)
            {
                fseek(p, j * sizeof(System), SEEK_SET);
                fwrite(&b, sizeof(System), 1, p);
                fwrite(&a, sizeof(System), 1, p);
            }
        }
    }
    char arrr[15];
    cout << "Enter destination" << '\n';
    cin.getline(arrr, sizeof(arrr));
    fseek(p, 0, SEEK_END);
    int left = 0;
    int right = ftell(p) / sizeof(System) - 1;
    System s;
    while (left <= right)
    {
        int mid = (right + left) / 2;
        fseek(p, mid * sizeof(System), SEEK_SET);
        fread(&s, sizeof(System), 1, p);
        int buf = strcmp(s.punnaz, arrr);
        if (buf == 0)
        {
            cout << "Result: " << '\n';
            cout << "Number: " << s.nomer << '\n';
            cout << "Type:" << s.typeav << '\n';
            cout << "Departure time: " << s.vremotp << '\n';
            cout << "Arrival time: " << s.vrempri << '\n';
            return 0;
        }
        else if (buf < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return 0;
}
int poiskpriz(const char *filename, const char *filenamh)
{
    FILE *p = fopen(filename, "rb+");
    if (p == NULL)
    {
        cout << "Dont open";
        return 1;
    }
    char bufe[15];
    float vrem;
    cout << "Enter destination " << endl;
    cin.getline(bufe, sizeof(bufe));
    cout << "Enter time" << endl;
    cin >> vrem;
    System a, b, s;
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            fseek(p, j * sizeof(System), SEEK_SET);
            fread(&a, sizeof(System), 1, p);
            fread(&b, sizeof(System), 1, p);
            if (a.vremotp > b.vremotp)
            {
                fseek(p, j * sizeof(System), SEEK_SET);
                fwrite(&b, sizeof(System), 1, p);
                fwrite(&a, sizeof(System), 1, p);
            }
        }
    }
    FILE *g = fopen(filenamh, "w");
    if (g == NULL)
    {
        cout << "Dont open txt";
        return 1;
    }
    while (fread(&s, sizeof(System), 1, p) == 1)
    {
        if (s.vrempri >= vrem && strcmp(bufe, s.punnaz) == 0)
            fprintf(g, "%s %f\n", s.typeav, s.vremotp);
    }
    fclose(g);
    fclose(p);
    return 0;
}
int staticiok(const char *filename)
{
    FILE *p = fopen(filename, "rb");
    if (p == NULL)
    {
        cout << "Cannot open file";
        return 1;
    }
    char typebuf[100];
    float vremya;
    cout << "Enter type and minimum departure time: " << endl;
    cin.getline(typebuf, sizeof(typebuf));
    cin >> vremya;
    System s;
    fseek(p, 0, SEEK_END);
    for (int i = 0; i < ftell(p) / sizeof(System); i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&s, sizeof(System), 1, p);
        if (strcmp(typebuf, s.typeav) == 0 && s.vremotp >= vremya)
        {
            cout << "Type: " << s.typeav << endl;
            cout << "Departure time: " << s.vremotp << endl;
        }
    }
    fclose(p);
    return 0;
}
int poiskpriz(const char *filename, const char *bufname, const char *filenamh)
{
    FILE *p = fopen(filename, "rb+");
    if (!p)
    {
        cout << "Dont open";
        return 1;
    }
    System s;
    FILE *f = fopen(bufname, "wb");
    if (!f)
    {
        cout << "Dont open";
        return 1;
    }
    fseek(p, 0, SEEK_END);
    int n = ftell(p) / sizeof(System);
    for (int i = 0; i < n; i++)
    {
        fseek(p, i * sizeof(System), SEEK_SET);
        fread(&s, sizeof(s), 1, p);
        fseek(f, i * sizeof(System), SEEK_SET);
        fwrite(&s, sizeof(s), 1, f);
    }
    System g;
    for (int j = 0; j < n; j++)
    {
    }
    char bufe[15];
    char vrem[6];
    cout << "Enter destination " << endl;
    cin.ignore();
    cin.getline(bufe, sizeof(bufe));
    cout << "Enter time" << endl;
    cin.getline(vrem, 6);
    FILE *k = fopen(filenamh, "w");
    if (k == NULL)
    {
        cout << "Dont open txt";
        fclose(p);
        fclose(f);
        return 1;
    }
    fseek(f, 0, SEEK_SET);
    while (fread(&s, sizeof(System), 1, f) == 1)
    {
    }
    fclose(k);
    fclose(p);
    fclose(f);
    return 0;
}
int main()
{
    const char *filename = "data.bin";
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
            punnaz(filename);
            break;

        case 5:
            poiskpriz(filename, filetxt);
            break;

        case 6:
        {
            FILE *p = fopen(filename, "rb");
            if (p == NULL)
            {
                cout << "Dont open" << endl;
                break;
            }
            fseek(p, 0, SEEK_END);
            int n = ftell(p) / sizeof(System);
            fclose(p);

            if (n == 0)
            {
                cout << "File is empty" << endl;
                break;
            }

            quickSort(filename, 0, n - 1);
            break;
        }

        case 0:
            cout << "Number" << endl;
            return 0;

        default:
            cout << "Not correct choose" << endl;
            break;
        }
    }
    return 0;
}
