from domain.dict_manager import generate_dict, get_cheltuieli_tip, get_cheltuieli_ap,get_sum_cheltuieli_tip, adaugare  \
    , stergere_ch_ap1, stergere_ch_ap2, stergere_cheltuiala_tip,add_undo, get_sum_cheltuieli_ap,generate_zile  \
    , generate_gol, deepcopy

from domain.cheltuiala import set_cheltuiala,get_cheltuiala,get_tip,stergere_ch

from utils.utile import stergere_ultimu_el_tuplu

import testare.teste


def print_menu():
    print("Aplicația permite:\n" +
          "1. Adăugare \n" +
          "2. Ștergere \n" +
          "3. Căutări \n" +
          "4. Rapoarte \n" +
          "5. Filtru \n" +
          "6. Undo \n")

def ad_cheltuiala(d):
    """
    adaugă cheltuială pentru un apartament

    :param d:
    :return:
    """
    try:
         ap=int(input("Selectați apartamentul (1-12) : "))
         tip=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
         suma = int(input("Introduceți suma : "))
    except ValueError:
        print("Nu ati introdus corect datele")
    if ap<1 or ap>12:
         print("Nu exista apartamentul")
    elif tip<1 or tip>5:
        print("Nu exista cheltuiala")
    else:
        set_cheltuiala(ap,tip,suma,d)

def stergere_cheltuiala_1(d):
    """
    Șterge toate cheltuielile de la un apartament

    :param d:
    :return:
    """
    try:
        ap = int(input("Selectați apartamentul (1-12) : "))
    except ValueError:
        print("Nu ati introdus corect datele")
    if ap<1 or ap>12:
         print("Nu exista apartamentul")
    else:
        stergere_ch_ap1(ap,d)

def stergere_cheltuiala_2(d):
    """
    Șterge cheltuielile de la apartamente consecutive (Ex. se dau două
numere de apartament 2 și 5 și se șterg toate cheltuielile de la
apartamentele 1,2,3,4 și 5)

    :param d:
    :return:
    """
    try:
        ap1 = int(input("Selectați primul apartament (1-12) : "))
        ap2 = int(input("Selectați ultimul apartament (1-12) : "))
    except ValueError:
        print("Nu ati introdus corect datele")
    if (ap1<1 or ap1>12) or (ap2<1 or ap2>12):
        print("Nu exista apartamentul")
    else:
        stergere_ch_ap2(ap1,ap2,d)

def stergere_3(d):
    """
    Șterge cheltuielile de un anumit tip de la toate apartamentele

    :param d:
    :return:
    """
    try:
         tip = int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    except ValueError:
         print("Nu ati introdus corect datele")
    if tip>=1 and tip<=5:
        stergere_cheltuiala_tip(tip,d)
    else:
        print("Nu exista cheltuiala!")

def cautare_1(d):
    """
    Tipărește toate apartamentele care au cheltuieli mai mari decât o sumă dată

    :param d:
    :return:
    """
    try:
        s=int(input("Introduceti suma : "))
    except ValueError:
        print("Nu ati introdus corect datele")
    l=[]
    for i in range(12):
        if get_sum_cheltuieli_ap(d,i)>=s:
            l.append("ap. "+str(i+1))
    return l

def cautare_2(d):
    """
Tipărește cheltuielile de un anumit tip de la toate apartamentele

    :param d:
    :return:
    """
    try:
        c = int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    except ValueError:
        print("Nu ati introdus corect datele")
    if c>=1 and c<=5:
         l=get_cheltuieli_tip(c,d)
         return l
    else:
        print("Nu exista cheltuiala!")

def cautare_3(d):
    """
    Tipărește toate cheltuielile efectuate înainte de o zi și mai mari decât o
sumă (se dă suma și ziua)

    :param d:
    :return:
    """
    try:
        s = int(input("Introduceti suma: "))
        z = int(input("Selectati ziua(1-31): "))
    except ValueError:
        print("Nu ati introdus corect datele")
    if z<=0 or z>31:
        print("Nu exista ziua")
    else:
       zi=generate_zile()
       o=generate_gol()
       for i in d:
           for j in range(12):
               if zi[i][j]>=z and get_cheltuiala(j,i,d)>=s:
                   o[i].append(get_cheltuiala(j,i,d))
       return o

def raport_1(d):
    """
   Tipărește suma totală pentru un tip de cheltuială

    :param d:
    :return:
    """
    try:
        c = int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    except ValueError:
        print("Nu ati introdus corect datele")
    if c>=1 and c<=5:
        return get_sum_cheltuieli_tip(c,d)
    else:
        print("Nu exista cheltuiala!")

def raport_2(d):
    """
Tipărește toate apartamentele sortate după un tip de cheltuială

    :param d:
    :return:
    """
    try:
        c = int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    except ValueError:
        print("Nu ati introdus corect datele")
    if c>=1 and c<=5:
       l = []
       mx = -1
       mx1 = 999999
       while len(l) != 12:
           for i in d[get_tip(c)]:
               if i > mx and i < mx1:
                   mx = i
           l.append(mx)
           mx1 = mx
           mx = -1
       return l
    else:
        print("Nu exista cheltuiala!")

def raport_3(d):
    """
    Tipărește totalul de cheltuieli pentru un apartament dat

    :param d:
    :return:
    """
    try:
        ap = int(input("Selectați apartamentul (1-12) : "))
    except ValueError:
        print("Nu ati introdus corect datele")
    if ap>=1 and ap<=12:
        return get_cheltuieli_ap(ap,d)
    else:
        print("Nu exista ap.!")

def filtru_1(d):
    """
    Elimină toate cheltuielile de un anumit tip

    :param d:
    :return:
    """
    try:
        c = int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    except ValueError:
        print("Nu ati introdus corect datele")
    if c>=1 and c<=5:
        stergere_cheltuiala_tip(c,d)
    else:
        print("Nu exista cheltuiala!")

def filtru_2(d):
    """
    Elimină toate cheltuielile mai mici decât o sumă dată
    :param d:
    :return:
    """
    try:
        s = int(input("Introduceti suma : "))
    except ValueError:
        print("Nu ati introdus corect datele")

    for i in d:
        for j in range(12):
            if d[i][j]<s:
                d[i][j]=-1


def undo_dict(d,l,nr):
    """
    Reface ultima operație (lista de cheltuieli revine la ce exista înainte de
ultima operație care a modificat lista). – Nu folosiți funcția deepCopy
    :param d:
    :param l:
    :return:
    """
    if nr>1:
       d=l[nr-2]
       return d
    else:
        print("Nu se poate realiza undo!")




def start():
    d=generate_dict()
    undol=()
    undol=add_undo(deepcopy(d),undol)
    nr=1


    while True:
        print_menu()
        opt = input("Optiunea dumneavoastra este:")
        if opt == '1':
            ad_cheltuiala(d)
            undol = add_undo(deepcopy(d), undol)
            nr=nr+1


        elif opt == '2':
            print("Alegeti : ")
            a = input("a-Șterge toate cheltuielile de la un apartament \n" +
                      "b-Șterge cheltuielile de la apartamente consecutive \n" +
                      "c-Șterge cheltuielile de un anumit tip de la toate apartamentele \n")
            if a=='a':
                stergere_cheltuiala_1(d)
                undol = add_undo(deepcopy(d), undol)
                nr = nr + 1
            elif a=='b':
                stergere_cheltuiala_2(d)
                undol = add_undo(deepcopy(d), undol)
                nr = nr + 1
            elif a=='c':
                stergere_3(d)
                undol = add_undo(deepcopy(d), undol)
                nr = nr + 1
            else:
                print("Nu ati selectat optiunea corectă!")


        elif opt=='3':
            print("Alegeti : ")
            a = input("a-Tipărește toate apartamentele care au cheltuieli mai mari decât o sumă dată \n" +
                      "b-Tipărește cheltuielile de un anumit tip de la toate apartamentele \n" +
                      "c-Tipărește toate cheltuielile efectuate înainte de o zi și mai mari decât o sumă (se dă suma și ziua) \n")
            if a=='a':
                print(cautare_1(d))
            elif a=='b':
                print(cautare_2(d))
            elif a=='c':
                print(cautare_3(d))
            else:
                print("Nu ati selectat optiunea corectă!")


        elif opt=='4':
            print("Alegeti : ")
            a = input("a-Tipărește suma totală pentru un tip de cheltuială \n" +
                      "b-Tipărește toate apartamentele sortate după un tip de cheltuială \n" +
                      "c-Tipărește totalul de cheltuieli pentru un apartament dat \n")
            if a=='a':
                print(raport_1(d))
            elif a=='b':
                print(raport_2(d))
            elif a=='c':
                print(raport_3(d))
            else:
                print("Nu ati selectat optiunea corectă!")

        elif opt=='5':
            print("Alegeti : ")
            a = input("a-Elimină toate cheltuielile de un anumit tip \n" +
                      "b-Elimină toate cheltuielile mai mici decât o sumă dată \n")
            if a=='a':
                filtru_1(d)
                undol = add_undo(deepcopy(d), undol)
                nr = nr + 1
            elif a=='b':
                filtru_2(d)
                undol = add_undo(deepcopy(d), undol)
                nr = nr + 1

        elif opt=='6':
            d=undo_dict(d,undol,nr)
            if nr>1:
                print("Undo realizat cu succes!")
                nr=nr-1
                undol=stergere_ultimu_el_tuplu(undol)

        else:
            print("Inchidere program")
            break








