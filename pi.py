#ODREDJIVANJE PI POMOCU NASUMICNIH BROJEVA
import random

def pi():
    krug = 0
    kvad = 0
    for i in range(1000000):
        x, y = kordinata()
        if x*x + y*y < 1:
            krug += 1
        else:
            kvad += 1
    return 4*krug/1000000

def kordinata():
    x, y = random.random(), random.random()
    return x, y

print(pi())