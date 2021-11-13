class Node:
    def __init__(self, prev=None, info=None, next=None):
        self.prev = prev
        self.info = info
        self.next = next

    def __repr__(self):
        return self.info

class Lista:
    def __init__(self):
        self.first = None
        self.count = 0

    def __repr__(self):
        cur = self.first
        lista = ["None"]
        for i in range(self.count):
            lista.append(str(cur.info))
            cur = cur.next
        lista.append("None")
        return " <-> ".join(lista)


def kreacija(elementi):
    lista = Lista()
    node_elementi = []
    for elem in elementi:
        node_elementi.append(Node(info=elem))

    for i in range(len(elementi)):
        if lista.first == None:
            lista.first = node_elementi[i]
            if i < len(node_elementi) - 1:
                node_elementi[i].next = node_elementi[i+1]
        else:
            node_elementi[i].prev = node_elementi[i-1]
            if i < len(node_elementi) - 1:
                node_elementi[i].next = node_elementi[i+1]
        lista.count += 1

    return lista


def dodaj_clana(lista, clan):
    cur = lista.first
    for i in range(lista.count):
        if cur.info == clan:
            return 0
        cur = cur.next

    node = Node(info=clan)
    cur = lista.first
    bef = None
    if clan < cur.info:
        cur.prev = node
        node.next = cur
        lista.first = node
        lista.count += 1
        return 1

    for i in range(lista.count):
        if clan < cur.info:
            cur.prev = node
            node.next = cur
            bef.next = node
            node.prev = bef
            lista.count += 1
            return 1
        bef = cur
        cur = cur.next

    if cur == None:
        node.prev = bef
        bef.next = node
        lista.count += 1
        return 1

def brisanje(lista, element):
    cur = lista.first
    for i in range(lista.count):
        if cur.info != element:
            cur = cur.next
    if cur == lista.first and lista.count == 1:
        del cur
        lista.count -= 1
        lista.first = None
    elif cur == lista.first and lista.count > 1:
        sledeci = cur.next
        if sledeci != None:
            sledeci.prev = None
            del cur
            lista.count -= 1
            lista.first = sledeci
            return 1
    else:
        prethodni = cur.prev
        sledeci = cur.next
        if sledeci != None:
            prethodni.next = sledeci
            sledeci.prev = prethodni
            del cur
            lista.count -= 1
            return 1
        else:
            prethodni.next = None
            del cur
            lista.count -= 1
            return 1

    return 0


def obrisi_skup(lista):
    if lista != None:
        for i in range(lista.count):
            brisanje(lista, lista.first.info)
    del lista


def provera_pripadnosti(lista, element):
    cur = lista.first
    for i in range(lista.count):
        if cur.info == element:
            print("Element {} PRIPADA skupu".format(element))
            return None
        cur = cur.next
        if cur == None:
            print("Element {} NE PRIPADA skup".format(element))
            return None

def presek(lista1, lista2):
    vrednosti = []
    cur1 = lista1.first
    for i in range(lista1.count):
        cur2 = lista2.first
        for j in range(lista2.count):
            if cur1.info == cur2.info:
                vrednosti.append(cur1.info)
            cur2 = cur2.next
        cur1 = cur1.next

    vrednosti.sort()
    return kreacija(vrednosti)

def unija(lista1, lista2):
    vrednosti = []
    cur1 = lista1.first
    cur2 = lista2.first
    for i in range(lista1.count):
        if cur1.info not in vrednosti:
            vrednosti.append(cur1.info)
        cur1 = cur1.next
    for j in range(lista2.count):
        if cur2.info not in vrednosti:
            vrednosti.append(cur2.info)
        cur2 = cur2.next
    vrednosti.sort()
    return kreacija(vrednosti)

def razlika(lista1, lista2):
    pogod = []
    cur1 = lista1.first
    for i in range(lista1.count):
        cur2 = lista2.first
        j = 0
        while j != lista2.count:
            if cur1.info == cur2.info:
                break
            else:
                cur2 = cur2.next
                j += 1
            if j == lista2.count:
                pogod.append(cur1.info)

        cur1 = cur1.next

    return kreacija(pogod)

print("Uneti redni broj za zeljnu operaciju: ")
print(" 0. Prestanak rada")
print(" 1. Kreiranje novog skupa")
print(" 2. Dodavanje clana skupu")
print(" 3. Brisanje clana iz skupa")
print(" 4. Ispis zadatog skupa")
print(" 5. Operacije nad skupovima (podmeni)")
print(" 6. Brisanje zadatog skupa")
br = None
dictionary = {}
key = 0
while br != 0:
    try:
        try:
            print("--------------------")
            br = int(input("Vas broj: ").strip("."))
        except:
            print("Uneli ste pogresan zahtev")
            exit()

        if br == 0:
            exit()
        elif br == 1:
            key += 1
            try:
                elementi = list(int(elem) for elem in input("Skup: ").split())
            except ValueError:
                print("Potrebno je uneti cele brojeve")
                break
            elementi = set(elementi)
            elementi = list(elementi)
            elementi.sort()
            lista = kreacija(elementi)
            dictionary[key] = lista
            print("Skup [ {} ] je uspesno sacuvan sa imenom: {}".format(lista, key))
        elif br == 2:
            ime = int(input("U koji skup zelite da dodate element: "))
            try:
                element = int(input("Element: "))
            except:
                print("Element mora biti ceo broj")
                break
            g = dodaj_clana(dictionary[ime], element)
            if g == 1:
                print("Element je uspesno dodat u skup")
                print(dictionary[ime])
            elif g == 0:
                print("Element je vec u skupu")
                print(dictionary[ime])
        elif br == 3:
            ime = int(input("Skup iz kog zelite element da obrisete: "))
            try:
                element = int(input("Element: "))
            except:
                print("Element mora biti ceo broj")
                break
            try:
                if brisanje(dictionary[ime], element):
                    print("Uspesno obrisan element")
                    print(dictionary[ime])
                else:
                    print("Neuspesno brisanje")
            except:
                print("Taj element ne postoju u {} skupu".format(ime))
        elif br == 4:
            try:
                ime = int(input("Skup koji zelite da ispisete: "))
            except:
                print("Nevalidno ime skupa")
                break
            print(dictionary[ime])
        elif br == 5:
            print("Odaberite operaciju koju zelite da sprovedete: ")
            print(" a) Provera pripadnosti elementa skupu")
            print(" b) Odredjivanje kardinalnosti skupa")
            print(" c) Unija")
            print(" d) Presek")
            print(" e) Razlika")
            print("    Bilo sta za povratak")

            slovo = input("Slovo: ").strip(")")
            if slovo != "a" and slovo != "b" and slovo != "c" and slovo != "d" and slovo != "e":
                print("Taj unos je nepostojeci")

            if slovo == "a":
                try:
                    ime = int(input("Skup: "))
                except:
                    print("Ime mora biti ceo broj")
                    break
                try:
                    element = int(input("Element: "))
                except:
                    print("Element mora biti ceo broj")
                    break
                provera_pripadnosti(dictionary[ime], element)
            elif slovo == "b":
                try:
                    ime = int(input("Skup: "))
                except:
                    print("Ime mora biti ceo broj")
                    break
                print("Skup {} ima {} elemenata".format(ime, dictionary[ime].count))
            elif slovo == "c":
                try:
                    amount = int(input("Uniju koliko skupova zelite(MIN 2, MAX 5): "))
                except:
                    print("Broj skupova mora biti ceo broj")
                    break
                if amount < 2 or amount > 5:
                    print("Nedozvoljena kolicina skupova")
                    break
                skupovi = []
                for i in range(amount):
                    try:
                        ime = int(input("Skup: "))
                    except:
                        print("Ime mora biti ceo broj")
                        quit()
                    skupovi.append(dictionary[ime])
                new = skupovi[0]
                for i in range(1, len(skupovi)):
                    new = unija(new, skupovi[i])

                key += 1
                dictionary[key] = new
                print("Unija zadatih skupova je {} sacuvan sa imenom {}".format(new, key))

            elif slovo == "d":
                try:
                    amount = int(input("Presek koliko skupova zelite(MIN 2, MAX 5): "))
                except:
                    print("Broj skupova mora biti ceo broj")
                    quit()

                if amount < 2 or amount > 5:
                    print("Nedozvoljena kolicina skupova")
                    break
                skupovi = []
                for i in range(amount):
                    try:
                        ime = int(input("Skup: "))
                    except:
                        print("Ime mora biti ceo broj")
                        quit()
                    skupovi.append(dictionary[ime])
                new = skupovi[0]
                for i in range(1, len(skupovi)):
                    new = presek(new, skupovi[i])

                key += 1
                dictionary[key] = new
                print("Presek zadatih skupova je {} sacuvan sa imenom {}".format(new, key))
            elif slovo == "e":
                try:
                    amount = int(input("Razliku koliko skupova zelite(MIN 2, MAX 5): "))
                except:
                    print("Broj skupova mora biti ceo broj")
                    quit()
                if amount < 2 or amount > 5:
                    print("Nedozvoljena kolicina skupova")
                    break
                skupovi = []
                for i in range(amount):
                    try:
                        ime = int(input("Skup: "))
                    except:
                        print("Ime mora biti ceo broj")
                        quit()
                    skupovi.append(dictionary[ime])
                new = skupovi[0]
                for i in range(1, len(skupovi)):
                    new = razlika(new, skupovi[i])

                key += 1
                dictionary[key] = new
                print("Razlika zadatih skupova je {} sacuvan sa imenom {}".format(new, key))
        elif br == 6:
            try:
                ime = int(input("Skup koji zelite da obrisete: "))
            except:
                print("Nevalidno ime skupa")
                break
            obrisi_skup(dictionary[ime])
            del dictionary[ime]
    except KeyError:
        print("Zadati skup ne postoju u memoriji")