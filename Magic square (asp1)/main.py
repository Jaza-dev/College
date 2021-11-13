import copy
import math

class MagicniKvadrat:
    def __init__(self, n):
        self.n = n
        self.sum = None
        self.elementi = None
        self.kvadrat = None
        self.preostali = None

    def __repr__(self):
        ispis = []
        for i in range(self.n):
            temp = self.kvadrat.copy()
            temp[i] = [str(elem) for elem in temp[i]]
            ispis.append(" ".join(temp[i]))
        return "  ".join(ispis)


def provera_validnosti_skupa_elemenata(lista):
    lista.sort()
    d = lista[1] - lista[0]
    for i in range(2, len(lista)):
        if not (d == (lista[i] - lista[i-1])):
            return False

    return True


def init_kvadrat():

    while True:
        try:
            #unos dimenzija kvadrata
            n = int(input("Dimenzije magicnog kvadrata: "))
            if n == 2:
                raise IndexError
            kvadrat = MagicniKvadrat(n)
            kvadrat.n = n
            break
        except IndexError:
            print("Ne moze se napraviti magicni kvadrat 2x2")
        except:
            print("Ne validna dimenzija kvadrata!")

    #unos 0 u kvadrat
    k = [[0 for elem in range(n)] for elem in range(n)]
    kvadrat.kvadrat = k
    print(kvadrat)

    #dodavanje inicijalnih elemenata
    inicijalni = [] #inicijalni elementi u kvadratu
    i = 0
    while True:
        try:
            print("Uneti pocetne elemete za validaciju (ENTER za zavrsetak)")
            init_vredsnot = [int(elem) for elem in input("vrsta kolona element: ").split(" ")]
            if k[init_vredsnot[0] - 1][init_vredsnot[1] - 1] == 0:
                k[init_vredsnot[0] - 1][init_vredsnot[1] - 1] = init_vredsnot[2]
                inicijalni.append(init_vredsnot[2])
                print(kvadrat)
                i += 1
            else:
                print("To mesto je vec zauzeto")
            kvadrat.kvadrat = k
        except:
            print("POCETNO STANJE KVADRATA:\n{}".format(kvadrat))
            kvadrat.elementi = inicijalni
            break


    while True:
        try:
            #kreacija liste elemenata koji ce biti u kvadratu
            preostali = [int(elem) for elem in input("Uneti skup elemenata kvadrata: ").split(" ")] #skup elemenata koji se trebaju dodati
            kvadrat.preostali = preostali
            if len(preostali) <= n*n:
                el = inicijalni.copy() #svi elementi koji ce biti u kvadratu
                el.extend(preostali)
                # dodajem ih u listu u kojoj cuvam sve elemente koji ce biti u kvadratu za proveru dal je aritm. niz
                print(preostali)
                print(el)
                if provera_validnosti_skupa_elemenata(el):
                    kvadrat.elementi = el
                    print("POTENCIJALNI MAGICNI KVADRAT")
                else:
                    raise IndexError
                break
            else:
                print("Pogresan broj elemenata skupa")
        except IndexError:
            print("NE MOZE SE NAPRAVITI MAGICNI KVADRAT OD ZADATOG SKUPA")
            break
        except:
            print("Neispravan unos")
    return kvadrat


def magicna_konstanta(kvadrat):
    if kvadrat.n == 1:
        return kvadrat.elementi[0]
    elif kvadrat.n == 3:
        return kvadrat.elementi[1] + kvadrat.elementi[5] + kvadrat.elementi[6]
    elif kvadrat.n == 4:
        return kvadrat.elementi[0] + kvadrat.elementi[3] + kvadrat.elementi[13] + kvadrat.elementi[14]
    elif kvadrat.n == 5:
        return kvadrat.elementi[0] + kvadrat.elementi[7] + kvadrat.elementi[14] + kvadrat.elementi[16] + kvadrat.elementi[23]

def ispis_liste_listi(lista):
    ispis = []
    for i in range(len(lista)):
        temp = lista.copy()
        temp[i] = [str(elem) for elem in temp[i]]
        ispis.append(" ".join(temp[i]))
    return "  ".join(ispis)

def ispis_dict(mapa):
    ispis = []
    for key in mapa:
        for pozicija in mapa[key]:
            ispis.append(ispis_liste_listi(mapa[key][pozicija]))
    return "\t\t".join(ispis)

def stablo(preostali, k):
    global kvadrat
    global resenja
    n = kvadrat.n
    konstanta = magicna_konstanta(kvadrat)
    k_copy1 = copy.deepcopy(k)
    k_copy2 = copy.deepcopy(k)
    k_copy3 = copy.deepcopy(k)
    k_copy4 = copy.deepcopy(k)
    mapa = dict.fromkeys(preostali)
    pozicije = []
    for i in range(n):
        for j in range(n):
            if k[i][j] == 0:
                pozicije.append((i, j))

    for key in mapa:
        pozicije_copy = copy.deepcopy(pozicije)
        for pozicija in pozicije_copy:
            ne_dodaj = False
            sum_vrsta = 0
            sum_kolona = 0
            sum_vrsta += key
            sum_kolona += key

            marker_vrsta = 1
            for kolona in range(n):
                element_vrsta = k_copy1[pozicija[0]][kolona]
                sum_vrsta += element_vrsta
                #sluzi da oznaci da li je taj key poslednji ili ne koji se dodaje u toj vrsti
                if element_vrsta != 0:
                    marker_vrsta += 1
            if marker_vrsta == n and sum_vrsta != konstanta:
                ne_dodaj = True
            if marker_vrsta < n and sum_vrsta > konstanta:
                ne_dodaj = True

            marker_kolona = 1
            for vrsta in range(n):
                element_kolona = k_copy2[vrsta][pozicija[1]]
                sum_kolona += element_kolona
                if element_kolona != 0:
                    marker_kolona += 1
            if marker_kolona == n and sum_kolona != konstanta:
                ne_dodaj = True
            if marker_kolona < n and sum_kolona > konstanta:
                ne_dodaj = True

            # provera dijagonala da li mogu zadovoljiti magicnost
            #-----------------------------------------------
            gl_dijagonala = 0
            marker_gl_dijagonala = 0
            for i in range(n):
                gl_dijagonala += k_copy3[i][i]
                if k_copy3[i][i] != 0:
                    marker_gl_dijagonala += 1
            if marker_gl_dijagonala == n and gl_dijagonala != konstanta:
                ne_dodaj = True
            if marker_gl_dijagonala < n and gl_dijagonala > konstanta:
                ne_dodaj = True

            spor_dijagonala = 0
            marker_spor_dijagonala = 0
            for j in range(n):
                spor_dijagonala += k_copy4[n-j-1][n-j-1]
                if k_copy4[j][j] != 0:
                    marker_spor_dijagonala += 1
            if marker_spor_dijagonala == n and spor_dijagonala != konstanta:
                ne_dodaj = True
            if marker_spor_dijagonala < n and spor_dijagonala > konstanta:
                ne_dodaj = True
            #-----------------------------------------------

            #obelezavaju se deadendovi sa False i od kojih se dalje moze napraviti stablo sa True
            if ne_dodaj:
                indeks = pozicije_copy.index(pozicija)
                pozicije_copy.remove(pozicija)
                pozicija = list(pozicija)
                pozicija.append(False)
                pozicija = tuple(pozicija)
                pozicije_copy.insert(indeks, pozicija)

            else:
                indeks = pozicije_copy.index(pozicija)
                pozicije_copy.remove(pozicija)
                pozicija = list(pozicija)
                pozicija.append(True)
                pozicija = tuple(pozicija)
                pozicije_copy.insert(indeks, pozicija)

        mapa[key] = dict.fromkeys(pozicije_copy)


    broj_iteracija = 0
    for key in mapa:
        for torka in mapa[key]:
            magicni = copy.deepcopy(k)
            magicni[torka[0]][torka[1]] = key
            mapa[key][torka] = magicni
            broj_iteracija += 1

    #print(mapa)
    #print("=========================================================================================================\n")
    return mapa


def formatiranje_stabla(lista):
    tekst = []
    for mapa in lista:
        tekst.append("\t" + "{}".format(ispis_dict(mapa)))

    print("\t" + "\t".join(tekst))

def savrsen_kvadrat(k, mag_konst):
    n = len(k)
    if n == 1:
        return True
    elif n == 3:
        return False
    elif n == 4:
        if (k[0][1] + k[1][2] + k[2][3] + k[3][0]) != mag_konst:
            return False
        elif (k[0][2] + k[1][3] + k[2][0] + k[3][1] != mag_konst):
            return False
        elif (k[0][3] + k[1][0] + k[2][1] + k[3][2] != mag_konst):
            return False
        elif (k[0][0] + k[1][3] + k[2][2] + k[3][1] != mag_konst):
            return False
        elif (k[0][1] + k[1][0] + k[2][3] + k[3][2] != mag_konst):
            return False
        elif (k[0][2] + k[1][1] + k[2][0] + k[3][3] != mag_konst):
            return False
    elif n == 5:
        if (k[0][1] + k[1][0] + k[2][4] + k[3][3] + k[4][2] != mag_konst):
            return False
        elif (k[0][0] + k[1][4] + k[2][3] + k[3][2] + k[4][1] != mag_konst):
            return False
        elif (k[0][2] + k[1][1] + k[2][0] + k[3][4] + k[4][3] != mag_konst):
            return False
        elif (k[0][3] + k[1][2] + k[2][1] + k[3][0] + k[4][4] != mag_konst):
            return False
        elif (k[0][4] + k[1][0] + k[2][1] + k[3][2] + k[4][3] != mag_konst):
            return False
        elif (k[0][3] + k[1][4] + k[2][0] + k[3][1] + k[4][2] != mag_konst):
            return False
        elif (k[0][2] + k[1][3] + k[2][4] + k[3][0] + k[4][1] != mag_konst):
            return False
        elif (k[0][1] + k[1][2] + k[2][3] + k[3][4] + k[4][0] != mag_konst):
            return False
    return True

#MAIN DEO PROGRAMA

while True:
    print("Uneti redni broj opcije koju zelite: ")
    print("1. Unos magicnog kvadrata")
    print("2. Magicna konstanta")
    print("3. Kreacija STABLA ODLUCIVANJA")
    print("4. Preorder ispis resenja")
    print("5. Provera da li je kvadrat savrsen")
    while True:
        try:
            x = int(input("Vas broj: "))
            break
        except:
            print("Neispravan unos")

    if x == 1:
        kvadrat = init_kvadrat()
    elif x == 2:
        try:
            print("Magicna konstanta je {}".format(magicna_konstanta(kvadrat)))
        except NameError:
            print("Nije memorisan nijedan kvadrat")
    elif x == 3:
        resenja = []
        try:
            marker = 0
            print(ispis_liste_listi(kvadrat.kvadrat))
            mapa = stablo(kvadrat.preostali, kvadrat.kvadrat)
            formatiranje_stabla([mapa])
            nivo = []
            preostali = None
            while True:
                #init svih ostalih nivoa > 2
                if len(nivo) > 0:
                    sl_nivo = []
                    for mapa in nivo:
                        preostali = list(mapa.keys())
                        for key in mapa:
                            preostali = list(mapa.keys())
                            preostali.remove(key)
                            if len(preostali) == 0:
                                break
                            for pozicija in mapa[key]:
                                if pozicija[2]:
                                    sl_nivo.append(stablo(preostali, mapa[key][pozicija]))
                    if preostali != None and len(preostali) == 0:
                        #dodavanje svi krajnjih true listova u resenja
                        for mapa in nivo:
                            for key in mapa:
                                for pozicija in mapa[key]:
                                    resenja.append(mapa[key][pozicija])
                        break
                    formatiranje_stabla(sl_nivo)
                    nivo = sl_nivo
                else:
                    #init drugo nivoa
                    if marker != 0:
                        raise KeyError
                    preostali = list(mapa.keys())
                    for key in mapa:
                        preostali = list(mapa.keys())
                        preostali.remove(key)
                        for pozicija in mapa[key]:
                            if pozicija[2]:
                                nivo.append(stablo(preostali, mapa[key][pozicija]))
                    marker += 1

                    formatiranje_stabla(nivo)
        except KeyError:
            print("Kvadrat ne moze biti magican")
        except IndexError:
            print("Nevalidan kvadrat")
    elif x == 4:
        #preorder_ispis()
        pass
    elif x == 5:
        mag_konst = magicna_konstanta(kvadrat)
        resenja = set(tuple(tuple(item)) for item in resenja)
        for k in resenja:
            if savrsen_kvadrat(k, mag_konst):
                print("SAVRSEN KVADRAT: {}".format(ispis_liste_listi(k)))
            else:
                print("NIJE SAVRSEN KVADRAT: {}".format(ispis_liste_listi(k)))
