#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

int myMin(int a, int b) { return (a < b ? a : b); }

struct Node;
void mySwap(Node*& a, Node*& b) {
    Node* t = a;
    a = b;
    b = t;
}

struct Node {
    int id;
    int val;
    int sum;
    int minVal;
    int lazy;
    Node* l;
    Node* r;
    Node* p;
    bool rev;

    Node() {
        id = 0;
        val = sum = minVal = lazy = 0;
        l = r = p = nullptr;
        rev = false;
    }

    Node(int id_, int value_) {
        id = id_;
        val = value_;
        sum = value_;
        minVal = value_;
        lazy = 0;
        l = r = p = nullptr;
        rev = false;
    }

    void push() {
        if (rev) {
            rev = false;
            mySwap(l, r);
            if (l) l->rev ^= true;
            if (r) r->rev ^= true;
        }
        if (lazy != 0) {
            val += lazy;
            sum += lazy;
            minVal += lazy;
            if (l) l->lazy += lazy;
            if (r) r->lazy += lazy;
            lazy = 0;
        }
    }

    bool is_root() {
        return !p || (p->l != this && p->r != this);
    }

    void update() {
        sum = val;
        minVal = val;
        if (l) {
            l->push();
            sum += l->sum;
            minVal = myMin(minVal, l->minVal);
        }
        if (r) {
            r->push();
            sum += r->sum;
            minVal = myMin(minVal, r->minVal);
        }
    }
};

struct LinkCutTree {
    vector<Node> a;

    LinkCutTree(int n, bool useIdValues, const vector<int>& userValues) {
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            int value = useIdValues ? i : userValues[i];
            a[i] = Node(i, value);
        }
    }

    void rotate(Node* x) {
        Node* p = x->p;
        Node* g = p->p;

        if (!p->is_root()) {
            if (g->l == p) g->l = x;
            else if (g->r == p) g->r = x;
        }

        p->push();
        x->push();

        if (p->l == x) {
            p->l = x->r;
            if (x->r) x->r->p = p;
            x->r = p;
        } else {
            p->r = x->l;
            if (x->l) x->l->p = p;
            x->l = p;
        }
        p->p = x;
        x->p = g;

        p->update();
        x->update();
    }

    void splay(Node* x) {
        while (!x->is_root()) {
            Node* p = x->p;
            Node* g = p->p;
            if (!p->is_root()) {
                rotate(((g->r == p) == (p->r == x)) ? p : x);
            }
            rotate(x);
        }
        x->push();
        x->update();
    }

    Node* expose(Node* x) {
        Node* last = nullptr;
        for (Node* y = x; y; y = y->p) {
            splay(y);
            y->r = last;
            y->update();
            last = y;
        }
        splay(x);
        return last;
    }

    void make_root(Node* x) {
        expose(x);
        x->rev ^= true;
        x->push();
    }

    Node* find_root(Node* x) {
        expose(x);
        while (x->l) {
            x->push();
            x = x->l;
        }
        splay(x);
        return x;
    }

    int find_root(int v) {
        return find_root(&a[v])->id;
    }

    void link(int u, int v) {
        Node* x = &a[u];
        Node* y = &a[v];
        make_root(x);
        if (find_root(y) == x) {
            cout << "Ошибка: цикл\n";
            return;
        }
        x->p = y;
    }

    void cut(int u, int v) {
        make_root(&a[u]);
        expose(&a[v]);
        Node* x = &a[v];
        if (x->l) {
            x->l->p = nullptr;
            x->l = nullptr;
            x->update();
        }
    }

    bool connected(int u, int v) {
        return find_root(&a[u]) == find_root(&a[v]);
    }

    void find_path(int u, int v) {
        make_root(&a[u]);
        expose(&a[v]);
        cout << "Путь активирован\n";
    }

    void path_add(int u, int v, int c) {
        make_root(&a[u]);
        expose(&a[v]);
        a[v].lazy += c;
        a[v].push();
        a[v].update();
    }

    int path_min(int u, int v) {
        make_root(&a[u]);
        expose(&a[v]);
        return a[v].minVal;
    }

    int path_sum(int u, int v) {
        make_root(&a[u]);
        expose(&a[v]);
        return a[v].sum;
    }

    

    void dfs_print(int u, int parent, vector<vector<int>>& adj, int depth) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << u << " (val=" << a[u].val << ", sum=" << a[u].sum << ", min=" << a[u].minVal << ")\n";

        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs_print(v, u, adj, depth + 1);
        }
    }

    void print_tree(int root) {
        vector<vector<int>> adj(a.size());

        for (int i = 1; i < a.size(); i++) {
            if (a[i].p) {
                adj[i].push_back(a[i].p->id);
                adj[a[i].p->id].push_back(i);
            }
        }

        cout << "Дерево с корнем " << root << ":\n";
        dfs_print(root, 0, adj, 0);
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    cout << "Использовать id как значения? (1/0): ";
    int flag;
    cin >> flag;
    bool useIdValues = (flag == 1);

    vector<int> userValues(n + 1);
    if (!useIdValues) {
        cout << "Введите значения:\n";
        for (int i = 1; i <= n; i++) cin >> userValues[i];
    }

    LinkCutTree lct(n, useIdValues, userValues);

    cout << "Команды:\n"
         << "  link u v\n"
         << "  cut u v\n"
         << "  conn u v\n"
         << "  root v\n"
         << "  findpath u v\n"
         << "  addpath u v c\n"
         << "  minpath u v\n"
         << "  sumpath u v\n"
         << "  print r\n"
         << "  exit\n";

    while (true) {
        string cmd;
        cout << "> ";
        cin >> cmd;

        if (cmd == "exit") break;

        if (cmd == "link") {
            int u, v; cin >> u >> v;
            lct.link(u, v);
        }
        else if (cmd == "cut") {
            int u, v; cin >> u >> v;
            lct.cut(u, v);
        }
        else if (cmd == "conn") {
            int u, v; cin >> u >> v;
            cout << (lct.connected(u, v) ? "YES\n" : "NO\n");
        }
        else if (cmd == "root") {
            int v; cin >> v;
            cout << lct.find_root(v) << "\n";
        }
        else if (cmd == "findpath") {
            int u, v; cin >> u >> v;
            lct.find_path(u, v);
        }
        else if (cmd == "addpath") {
            int u, v, c; cin >> u >> v >> c;
            lct.path_add(u, v, c);
        }
        else if (cmd == "minpath") {
            int u, v; cin >> u >> v;
            cout << lct.path_min(u, v) << "\n";
        }
        else if (cmd == "sumpath") {
            int u, v; cin >> u >> v;
            cout << lct.path_sum(u, v) << "\n";
        }
        else if (cmd == "print") {
            int r; cin >> r;
            lct.print_tree(r);
        }
        else {
            cout << "Неизвестная команда\n";
        }
    }

    return 0;
}



