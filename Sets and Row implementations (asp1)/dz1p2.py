import random

class Node:
    def __init__(self, data):
        self.prev = None
        self.data = data
        self.next = None

    def __repr__(self):
        return self.data


class List:
    def __init__(self):
        self.prvi = None
        self.br_elem = 0

    def __repr__(self):
        cur = self.prvi
        lista = ["None"]
        while cur is not None:
            lista.append(cur.data)
            cur = cur.next
        lista.append("None")
        return " <-> ".join(lista)


class Red:
    def __init__(self):
        self.celo = None
        self.zacelje = None
        self.isempty = True

    def __repr__(self):
        cur = self.celo
        lista = []
        while cur is not None:
            lista.append(cur.data)
            cur = cur.next
        if len(lista) == 0:
            return "PRAZAN"
        else:
            return " <--- ".join(lista)

broj_koraka_simulacije = 0

def kreacija_liste(lista, lista_data):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    lista_node = []
    for i in range(len(lista_data)):
        lista_node.append(Node(data=lista_data[i]))

    for j in range(len(lista_node)):
        if j == 0 and len(lista_node) == 1:
            lista.prvi = lista_node[0]
        elif j == 0 and len(lista_node) > 0:
            lista_node[0].next = lista_node[1]
            lista.prvi = lista_node[0]
        else:
            lista_node[j-1].next = lista_node[j]
            lista_node[j].prev = lista_node[j-1]
        lista.br_elem += 1


def brisanje_iz_liste(lista, element):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    cur = lista.prvi
    bef = None
    nex = None
    if cur == element and lista.br_elem > 1:
        sledeci = cur.next
        lista.prvi = sledeci
        del cur
    elif cur == element and lista.br_elem == 1:
        lista.prvi = None
        del cur
    else:
        while cur != element:
            bef = cur
            cur = cur.next
            nex = cur.next
        if bef is not None:
            bef.next = cur.next
        if nex is not None:
            nex.prev = cur.prev
        del cur

    lista.br_elem -= 1

def brisanje_liste(lista):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    cur = lista.prvi
    while lista.br_elem != 0:
        brisanje_iz_liste(lista, cur)
        cur = cur.next
    del lista

def dodavanje_u_red(red, lista, broj):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    cur = lista.prvi
    for z in range(broj-1):
        cur = cur.next

    if red.isempty:
        data = cur.data
        brisanje_iz_liste(lista, cur)
        red.celo = red.zacelje = Node(data)
        red.isempty = False
    else:
        data = cur.data
        brisanje_iz_liste(lista, cur)
        cur = Node(data=data)
        cur.prev = red.zacelje
        red.zacelje.next = cur
        red.zacelje = cur


def dodavanje_elementa_na_kraj_reda(red, data):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    if red.isempty:
        red.celo = red.zacelje = Node(data)
        red.isempty = False
    else:
        cur = Node(data=data)
        cur.prev = red.zacelje
        red.zacelje.next = cur
        red.zacelje = cur


def uklanjanje_iz_reda(red):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    cur = red.celo
    if red.isempty == False:
        information = cur.data
        red.celo = cur.next
        del cur
        if red.celo == None:
            red.isempty = True

        return information


def upis(red, broj):
    global broj_koraka_simulacije
    broj_koraka_simulacije += 1

    if 0 <= broj <= 0.5:
        data = uklanjanje_iz_reda(red)
        dodavanje_elementa_na_kraj_reda(red, data)
    else:
        student = red.celo.data
        lista_podataka = [podatak for podatak in student.split(" ")]
        try:
            lista_podataka[4] = int(lista_podataka[4]) + 1
        except:
            print("Greska pri upisu")
            exit()
        print("Student {} {} je upisao {} godinu studija".format(lista_podataka[0], lista_podataka[1], lista_podataka[4]))
        uklanjanje_iz_reda(red)

li = List()
red = Red()
try:
    c = int(input("Koliko studenata zelite da upisete: "))
except:
    print("Niste uneli ceo broj")
    exit()
lista_data = []
for i in range(c):
    lista_data.append(input("{}. ".format(i+1)))
lista_data.reverse()
kreacija_liste(li, lista_data)
print("Trenutnan broj studenata u listi: {}".format(li.br_elem))

while li.br_elem > 0:
    r = random.randint(1, li.br_elem)
    dodavanje_u_red(red, li, r)

print("Trenutan red ispred salter: {}".format(red))
while red.isempty == False:
    r = random.random()
    if r >= 0.5:
        print("USPESAN UPIS")
    else:
        print("NEUSPESAN UPIS")

    upis(red, r)

    print("Trentan red: {}".format(red))


print("BROJ KORAKA SIMULACIJE: {}".format(broj_koraka_simulacije))


print("Unestite zeljeni broj za operaciju: ")
print("0. Zaustavi program")
print("1. Dohvatanje studenta iz reda")
print("2. Stavljanje studenta u red")
print("3. Provera da li je red prazan")
print("4. SIMULACIJA")
print("5. Trenutni red")



while True:
    print("--------------------")
    try:
        br = int(input("Vas broj: "))
    except:
        print("Uneli ste pogresan zahtev")
        exit()
    if br == 0:
        break
    elif br == 1:
        indx = input("Kog studenta zelite da dohvatite(indeks): ")
        student = red.celo
        while student != None and student != 0:
            lista = list(podatak for podatak in student.data.split())
            if lista[2] == indx:
                print(student.data)
                student = 0
            else:
                student = student.next
        if student == None:
            print("Student sa tim indeksom nije u redu")
    elif br == 2:
        info = input("Podaci o studentu: ")
        if len(info) >= 20:
            dodavanje_elementa_na_kraj_reda(red, info)
            red.isempty = False
            print("Trenutan red: {}".format(red))
        else:
            print("Niste uneli ispravne podatke o studentu")
    elif br == 3:
        if red.isempty == True:
            print("RED JE PRAZAN")
        else:
            print("RED NIJE PRAZAN")
    elif br == 4:
        print("Trenutan red ispred salter: {}".format(red))
        while red.isempty == False:
            r = random.random()
            if r >= 0.5:
                print("USPESAN UPIS")
            else:
                print("NEUSPESAN UPIS")

            upis(red, r)
            print("Trentan red: {}".format(red))
    elif br == 5:
        print("Trenutan red ispred salter: {}".format(red))