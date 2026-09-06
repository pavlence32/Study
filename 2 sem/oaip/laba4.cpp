#include <iostream>
#include <string.h>
using namespace std;
struct info
{
    char fio[20];
    int nomer;
};
struct Tree
{
    info data;
    Tree *left;
    Tree *right;
} *root;
Tree *coren(Tree *begin, info s)
{
    Tree *p = new Tree;
    p->data = s;
    p->left = NULL;
    p->right = NULL;
    begin = p;
    return begin;
}
void list(Tree **begin, info s)
{
    if (!(*begin))
    {
        cout << "No root";
        return;
    }
    if ((*begin)->data.nomer == s.nomer)
    {
        cout << "Same data as root";
        return;
    }
    Tree *p = *begin;
    Tree *prev = NULL;
    while (p)
    {
        if (s.nomer == p->data.nomer)
        {
            cout << "Same data";
            return;
        }
        prev = p;
        s.nomer > p->data.nomer ? p = p->right : p = p->left;
    }
    Tree *now = new Tree;
    now->data = s;
    now->left = NULL;
    now->right = NULL;
    s.nomer > prev->data.nomer ? prev->right = now : prev->left = now;
}
void deletev(Tree **begin, info s)
{
    if (*begin == NULL) { cout << "No root\n"; return; }
    Tree *p = *begin;
    Tree *prev = NULL;
    while (p && p->data.nomer != s.nomer)
    {
        prev = p;
        p->data.nomer > s.nomer ? p = p->left : p = p->right;
    }
    if (!p) { cout << "Not found\n"; return; }
    if (p->left && p->right)
    {
        Tree *prevBuf = p;
        Tree *buf = p->left;
        while (buf->right) { prevBuf = buf; buf = buf->right; }
        p->data = buf->data;
        
        if (prevBuf == p) prevBuf->left = buf->left;
        else              prevBuf->right = buf->left;
        delete buf;
        return;
    }
    Tree *child = (p->left) ? p->left : p->right;
    if (prev == NULL)           *begin = child;        
    else if (prev->left == p)   prev->left = child;
    else                        prev->right = child;
    delete p;
}
void poisk(Tree *begin, info s)
{
    if (begin == NULL) { cout << "No root\n"; return; }
    Tree *p = begin;
    while (p)
    {
        if (p->data.nomer == s.nomer)
        {
            cout << "Surname: " << p->data.fio << "\n";
            return;
        }
        p->data.nomer > s.nomer ? p = p->left : p = p->right;
    }
    cout << "Not found\n";
}
void treeprintinf(Tree *begin)
{
    Tree *tree = begin;
    if (tree != NULL)
    {
        treeprintinf(tree->left);
        cout << tree->data.fio << ":";
        cout << tree->data.nomer << " ";
        treeprintinf(tree->right);
    }
}
void tomasi(Tree *begin, info *arr, int n, int *i)
{
    Tree *tree = begin;
    if (tree != NULL && *i < n)
    {
        tomasi(tree->left, arr, n, i);
        arr[*i] = tree->data;
        (*i)++;
        tomasi(tree->right, arr, n, i);
    }
}
void prefi(Tree *begin)
{
    Tree *tree = begin;
    if (tree != NULL)
    {
        cout << tree->data.nomer << ":";
        cout << tree->data.fio << " ";
        prefi(tree->left);
        prefi(tree->right);
    }
}
void view_tree(Tree * root, int level) {
  if (root) {
    view_tree(root->right, level + 1);
    for (int i = 0; i < level; i++) cout << "    ";
    cout << root->data.nomer << endl;
    view_tree(root->left, level + 1);
  }
}
void prefidd(Tree *begin, int *sum)
{
    Tree *tree = begin;
    if (tree != NULL)
    {
        *(sum) += strlen(tree->data.fio);
        prefidd(tree->left, sum);
        prefidd(tree->right, sum);
    }
}
void post(Tree *begin)
{
    Tree *tree = begin;
    if (tree != NULL)
    {
        post(tree->left);
        post(tree->right);
        cout << tree->data.fio << ":";
        cout << tree->data.nomer << " ";
    }
}
int countuNodes(Tree *root)
{
    if (root == NULL)
        return 0;

    return 1 + countuNodes(root->left) + countuNodes(root->right);
}
void deleted(Tree **begin)
{
    if (*begin != NULL)
    {
        deleted(&(*begin)->left);
        deleted(&(*begin)->right);
        delete (*begin);
    }
}

Tree *buildBalanced(info *arr, int left, int right)
{
    if (left > right) return NULL;
    
    int mid = (left + right) / 2;
    
    Tree *node = new Tree;
    node->data = arr[mid];
    node->left  = buildBalanced(arr, left, mid - 1);
    node->right = buildBalanced(arr, mid + 1, right);
    
    return node;
}

Tree *balans(Tree *begin)
{
    int n = countuNodes(begin);
    info *arr = new info[n];
    int i = 0;
    tomasi(begin, arr, n, &i);  
    
    Tree *newRoot = buildBalanced(arr, 0, n - 1);  
    
    deleted(&begin);
    delete[] arr;
    return newRoot;
}
int summastr(Tree *begin)
{
    Tree *tree = begin;
    int sim = 0;
    prefidd(tree, &sim);
    return sim;
}
int main()
{
    Tree *begin = NULL;
    int choice;
    info s;

    while (true)
    {
        cout << "1. Add root\n";
        cout << "2. Add uzel\n";
        cout << "3. delete uzel\n";
        cout << "4. Poisk\n";
        cout << "5. Infiksis obxod\n";
        cout << "6. Prefi obxod\n";
        cout << "7. Post obxod\n";
        cout << "8. Kolichestvo simvolow\n";
        cout << "9. Balancer\n";
        cout<< " 10. View\n";
        cout << "0. Exit\n";
        cout << "choice: ";
        cin >> choice;

        if (choice == 0)
        {
            deleted(&begin);
            break;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter fio and number: ";
            cin >> s.fio >> s.nomer;
            begin = coren(begin, s);
            break;

        case 2:
            cout << "Enter fio and nomer: ";
            cin >> s.fio >> s.nomer;
            list(&begin, s);
            break;

        case 3:
            cout << "Enter number for delete: ";
            cin >> s.nomer;
            deletev(&begin, s);
            break;

        case 4:
            cout << "Enter number for poisk : ";
            cin >> s.nomer;
            poisk(begin, s);
            break;

        case 5:
            cout << "Infiksis obxod: ";
            treeprintinf(begin);
            break;

        case 6:
            cout << "Prefi obxod: ";
            prefi(begin);
            break;

        case 7:
            cout << "Posti obxod: ";
            post(begin);
            break;

        case 8:
            cout << "Number summ: " << summastr(begin) << "\n";
            break;

        case 9:
            begin = balans(begin);
            cout << "balanced\n";
            view_tree(begin,0);
            break;
        case 10:
            view_tree(begin,0);
            break;

        default:
            cout << "not corect\n";
            break;
        }
    }
    return 0;
}
