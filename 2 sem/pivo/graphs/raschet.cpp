#include <iostream>
using namespace std;
#define V 5
int algospre(int key[], int intree[]) // вершину с минимальным весом
{
    int min = 100000, minIND = -1;
    for (int i = 0; i < V; i++)
    {
        if (!intree[i] && key[i] < min)
        {
            min = key[i];
            minIND = i;
        }
    }
    return minIND;
}
void algos(int graph[V][V])
{
    int parent[V];
    int key[V];
    int intree[V];
    int buf = 0;
    for (int i = 0; i < V; i++)
    {
        key[i] = 100000;
        intree[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int j = 0; j < V - 1; j++)
    {
        buf = algospre(key, intree);
        intree[buf] = 1;

        for (int v = 0; v < V; v++)
        {
            if (graph[buf][v] && !intree[v] && graph[buf][v] < key[v])
            {
                key[v] = graph[buf][v];
                parent[v] = buf;
            }
        }
    }
    cout << "Rebro ves " << endl;
    int total = 0;
    for (int k = 1; k < V; k++)
    {
        cout << parent[k] << "-" << k << "\t" << graph[parent[k]][k] << endl;
        total += graph[parent[k]][k];
    }
    cout << "Ves: " << total;
}
int main()
{
    int graph[V][V] =
        {
            {0, 1, 0, 3, 0},
            {1, 0, 4, 0, 0},
            {0, 4, 0, 0, 2},
            {3, 0, 0, 0, 5},
            {0, 0, 2, 5, 0},
        };
    algos(graph);
    return 0;
}