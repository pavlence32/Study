import math
from turtle import *


def hearta(t):
    return 15 * math.sin(t) ** 3


def heartb(t):
    return (12 * math.cos(t)
            - 5 * math.cos(2 * t)
            - 2 * math.cos(3 * t)
            - math.cos(4 * t))


speed(0)
bgcolor("black")
color("red")

penup()  # чтобы не рисовать линии от (0,0)

for i in range(6000):
    t = i * 0.01  # переводим в радианы
    goto(hearta(t) * 20, heartb(t) * 20)
    pendown()

hideturtle()
done()
