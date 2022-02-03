#SIMULACIJA BACANJE KOCKE (1-6)
import random

def coin():
    n = random.random()
    if n < 0.5:
        n = 0
    else:
        n = 1
    return n

def cube():
    br = coin()
    br = br * 2 + coin()
    br = br * 2 + coin()
    br = br * 2 + coin()
    return br

while True:
    broj = cube()
    if broj != 7 and broj != 0:
        print(broj)
        break



