import igraph as ig

persons_friends = [
    ('1', '5'),
    ('2', '3'),
    ('0', '3'),
    ('1', '2')
]

g = ig.Graph.TupleList(persons_friends, directed=False)

max_degree = max(g.degree())
best_pers = g.vs.select(_degree=max_degree)["name"]

print("\nСамые популярные пользователи:", *best_pers)