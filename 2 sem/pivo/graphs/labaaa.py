import networkx as nx
G=nx.Graph()
G.add_node("1")
G.add_node("2")
G.add_node("3")
G.add_node("4")
G.add_node("5")
G.add_node("6")
G.add_edges_from(
    [
        ("1", "2"),
        ("2", "3"),
        ("3", "4"),
        ("4", "5"),
        ("5", "6"),
        ("6", "1"),
        
    ]
)
critical_nodes=list(nx.articulation_points(G))
print(critical_nodes)
print(G)