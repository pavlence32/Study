# Постановка задачи.
# Вершины — города, рёбра — дороги, вес — время в пути (чем меньше, тем лучше). 

# Нужно:
# - проверить связность сети и характеристики расстояний,
# - найти кратчайшие пути между выбранными городами,
# - построить минимальное остовное дерево как «минимальный набор дорог» для связности,
# - оценить устойчивость сети при отключении важных городов (изменение размера крупнейшей компоненты и диаметра).

import igraph as ig

# ---------------------------------------------------------
# 1. ДАНО: города и дороги между ними (время в пути, часы)
# ---------------------------------------------------------

roads_raw = [
    ("A", "B", 3.0),
    ("A", "C", 2.5),
    ("B", "C", 1.0),
    ("B", "D", 4.0),
    ("C", "D", 2.0),
    ("C", "E", 3.5),
    ("D", "E", 1.5),
    ("D", "F", 4.0),
    ("E", "F", 2.0),
    ("E", "G", 3.0),
    ("F", "G", 2.5),
    ("B", "H", 5.0),
    ("H", "G", 4.0),
]

# Собираем список всех городов (имён вершин)
cities = sorted({u for u, v, t in roads_raw} | {v for u, v, t in roads_raw})

# Строим отображение: имя города -> номер вершины
city_to_idx = {name: i for i, name in enumerate(cities)}

# Формируем список рёбер и список весов (времени)
edges = []
times = []
for u, v, t in roads_raw:
    u_idx = city_to_idx[u]
    v_idx = city_to_idx[v]
    edges.append((u_idx, v_idx))
    times.append(t)

# Создаём неориентированный граф
g = ig.Graph(
    n=len(cities),   # количество вершин
    edges=edges,
    directed=False
)

# Сохраняем имена городов и времена как атрибуты
g.vs["name"] = cities
g.es["time"] = times

print("=== Свойства графа ===")
print(g.summary())
print("Города:", g.vs["name"])
print("Дороги (рёбра):")
for e in g.es:
    u, v = e.tuple
    print(f"{g.vs[u]['name']} - {g.vs[v]['name']}, время = {e['time']} ч")

# ---------------------------------------------------------
# 2. БАЗОВЫЕ ХАРАКТЕРИСТИКИ
# ---------------------------------------------------------

print("\n=== Связность ===")
is_conn = g.is_connected()
print("Сеть связна?", is_conn)

components = g.components()
print("Число компонент:", components.n)
print("Размер каждой компоненты:", components.sizes())

print("\n=== Диаметры ===")
# Диаметр по числу рёбер (без учёта времени)
diam_edges = g.diameter()
print("Диаметр по числу рёбер:", diam_edges)

# Диаметр с учётом времени (по весам)
diam_time = g.diameter(weights=g.es["time"])
print("Диаметр по времени (примерная оценка):", diam_time)

# ---------------------------------------------------------
# 3. КРАТЧАЙШИЙ ПУТЬ ПО ВРЕМЕНИ МЕЖДУ ДВУМЯ ГОРОДАМИ
# ---------------------------------------------------------

print("\n=== Кратчайший путь по времени из A в G ===")

# Находим индексы вершин по имени
src_name = "A"
dst_name = "G"
src = g.vs.find(name=src_name).index
dst = g.vs.find(name=dst_name).index

# Находим путь как последовательность вершин
vpath = g.get_shortest_paths(
    src,
    to=dst,
    weights=g.es["time"],
    output="vpath"
)[0]

# Находим путь как последовательность рёбер
epath = g.get_shortest_paths(
    src,
    to=dst,
    weights=g.es["time"],
    output="epath"
)[0]

# Переводим номера вершин в имена городов
path_cities = [g.vs[v]["name"] for v in vpath]

# Суммируем времена по рёбрам
total_time = 0.0
for e_id in epath:
    total_time += g.es[e_id]["time"]

print("Маршрут:", " -> ".join(path_cities))
print("Общее время в пути:", total_time, "ч")

# ---------------------------------------------------------
# 4. МИНИМАЛЬНОЕ ОСТОВНОЕ ДЕРЕВО (MST)
# ---------------------------------------------------------

print("\n=== Минимальное остовное дерево (MST) ===")

# Строим MST по весам 'time'
mst = g.spanning_tree(weights=g.es["time"])

print(mst.summary())
print("Рёбра MST:")
total_mst_time = 0.0
for e in mst.es:
    u, v = e.tuple
    u_name = mst.vs[u]["name"]
    v_name = mst.vs[v]["name"]
    t = e["time"]
    total_mst_time += t
    print(f"{u_name} - {v_name}, время = {t} ч")

print("Суммарное время всех дорог в MST:", total_mst_time, "ч")

# ---------------------------------------------------------
# 5. УСТОЙЧИВОСТЬ СЕТИ: УДАЛЯЕМ ВАЖНЫЕ ГОРОДА
# ---------------------------------------------------------

print("\n=== Устойчивость сети при удалении городов ===")

# Степень вершины = сколько дорог из города
deg = g.degree()
g.vs["degree"] = deg

print("Степени вершин (количество дорог):")
for v in g.vs:
    print(f"{v['name']}: degree = {v['degree']}")

# Выберем 3 самых "нагруженных" города по степени
sorted_by_degree = sorted(g.vs, key=lambda v: v["degree"], reverse=True)
critical = sorted_by_degree[:3]
critical_names = [v["name"] for v in critical]
print("\nСамые нагруженные города:", critical_names)

# Базовые значения (до удаления)
base_largest_size = g.vcount()
base_diameter_time = g.diameter(weights=g.es["time"])
print(
    f"\nБез удалений: размер крупнейшей компоненты = {base_largest_size}, "
    f"диаметр по времени ≈ {base_diameter_time:.2f}"
)

# Удаляем список городов и смотрим, что получилось
def remove_cities_and_measure(graph, remove_names):
    # делаем копию, чтобы не изменять исходный граф
    gc = graph.copy()

    # находим индексы вершин, которые надо удалить
    to_delete = []
    for name in remove_names:
        idx = gc.vs.find(name=name).index
        to_delete.append(idx)

    # удаляем
    gc.delete_vertices(to_delete)

    # смотрим на компоненты
    comps = gc.components()
    largest = comps.giant()  # крупнейшая компонента

    size_largest = largest.vcount()
    diam_largest_time = largest.diameter(weights=largest.es["time"])

    return size_largest, diam_largest_time

# Сценарии: удаляем один, два, три критичных города
for k in range(1, len(critical_names) + 1):
    removed_list = critical_names[:k]
    size_largest, diam_largest_time = remove_cities_and_measure(g, removed_list)
    print(
        f"Удаляем {removed_list}: "
        f"размер крупнейшей компоненты = {size_largest}, "
        f"диаметр по времени ≈ {diam_largest_time:.2f}"
    )