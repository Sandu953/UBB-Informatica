from ui.console import *
from domain.cheltuiala import *
from domain.dict_manager import *

def print_menu_2():
    print("1.Meniu \n2.Linie comanda")


def print_menu_instructiuni():
    print("Linia de comanda permite : \n")
    print("adaugare - adaugă cheltuială pentru un apartament ex. adaugare 1 3 150 \n")
    print("stergere_ap - sterge toate cheltuielile de la un apartament ex. stergere_ap 5 \n")
    print("stergere_tip - sterge toate cheltuielile de un anumit tip de la toate apartamentele ex. stergere_tip 2 \n")
    print("cautare_tip - tipărește cheltuielile de un anumit tip de la toate apartamentele ex. cautare_tip 1 \n")
    print("raport_ap - tipărește totalul de cheltuieli pentru un apartament dat ex. raport_ap 10  \n")
    print("raport_sum_tip - tipărește suma totală pentru un tip de cheltuială ex. raport_sum_tip 4  \n")
    print("Apartamentele sunt de la 1 la 12 \n")
    print("Cheltuielile sunt : \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n")


# adaugare 1 3 150; stergere_ap 5; stergere_tip 5; cautare_tip 1; raport_ap 10; raport_sum_tip 4


def start():
    d=generate_dict()
    while True:
        print_menu_2()
        opt = input("Optiunea dumneavoastra de meniu este:")
        print("\n")
        if opt=='1':
            start()
        elif opt=='2':
            print_menu_instructiuni()
            line=input("Scrieti linia : ")
            x=line.split("; ")
            for i in x:
                y=i.split()
                if y[0]=="adaugare":
                    set_cheltuiala(int(y[1]),int(y[2]),int(y[3]),d)
                elif y[0]=="stergere_ap":
                    stergere_ch_ap1(int(y[1]),d)
                elif y[0]=="stergere_tip":
                    stergere_cheltuiala_tip(int(y[1]),d)
                elif y[0]=="cautare_tip":
                    print(get_cheltuieli_tip(int(y[1]),d))
                elif y[0]=="raport_ap":
                    print(get_sum_cheltuieli_ap(d,int(y[1])))
                elif y[0]=="raport_sum_tip":
                    print(get_sum_cheltuieli_tip(int(y[1]),d))
                else:
                    print("Nu exista comanda!")


        else:
            print("Inchidere program")
            break
