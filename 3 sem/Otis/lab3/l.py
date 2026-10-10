import matplotlib.pyplot as plt

# Исходные данные
x = [75, 104, 115, 179, 252, 451]
y = [20, 30, 20, 50, 25, 40]
labels = [
    'Kitfort KT-6402',
    'Centek CT-1443',
    'Kitfort KT-6040',
    'Redmond RYM-M5401-E',
    'Steba JM 2',
    'Rommelsbacher JG 80',
]

# Точки границы Парето
pareto_x = [75, 104, 179]
pareto_y = [20, 30, 50]

plt.figure(figsize=(9, 5.5))

# Индивидуальные смещения для каждой подписи (dx, dy), чтобы надписи не пересекались
offsets = [
    (-20, -15),  # Kitfort KT-6402 (сносим чуть влево и вниз)
    (8, 2),  # Centek CT-1443
    (8, -12),  # Kitfort KT-6040 (сносим чуть вправо и вниз)
    (8, 2),  # Redmond RYM-M5401-E
    (8, 2),  # Steba JM 2
    (8, 2),  # Rommelsbacher JG 80
]

# Отрисовка всех точек
plt.scatter(x, y, color='blue', s=50, zorder=5)

# Подписи к точкам с индивидуальными сдвигами
for i, txt in enumerate(labels):
    plt.annotate(
        txt,
        (x[i], y[i]),
        fontsize=8.5,
        xytext=offsets[i],
        textcoords='offset points',
    )

# Отрисовка границы Парето (с отображением точек Парето поверх линии)
plt.plot(
    pareto_x,
    pareto_y,
    color='red',
    linestyle='--',
    linewidth=1.5,
    label='Граница Парето',
    zorder=3,
)
plt.scatter(
    pareto_x, pareto_y, color='red', s=50, zorder=4
)  # подсветим сами точки Парето

# Настройка осей и сетки
plt.xlim(0, 500)
plt.ylim(0, 60)
plt.xlabel('Стоимость, BYN')
plt.ylabel('Мощность, Вт')
plt.title('Множество Парето (Стоимость и Мощность)')
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(loc='upper right')

plt.tight_layout()
plt.savefig('pareto_chart.png', dpi=300)
plt.show()