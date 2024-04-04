"""
P5. Administrator de bloc
Creaplicație pentru gestiunea cheltuielilor lunare de la apartamentele unui
bloc de locuințe. Aplicația stochează cheltuielile pentru fiecare apartament:
suma și tipul cheltuielii (tip poate fi una dintre: apa, canal, încălzire, gaz, altele). 

"""


def run():
    #d={
    #    "apa":[-1]*12,
    #    "canal":[-1]*12,
    #    "incalzire":[-1]*12,
    #    "gaz":[-1]*12,
    #    "altele":[-1]*12
    #    }
    zi={
         "apa":[8,20,15,6,7,14,9,1,31,21,11,26],
        "canal":[25,21,31,26,19,24,15,16,3,13,20,6],
        "incalzire":[14,20,28,31,23,7,2,26,13,12,19,7],
        "gaz":[1,19,15,17,2,3,14,10,29,18,21,4],
        "altele":[5,14,20,8,2,18,23,12,22,27,19,13]
        }
    d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }

    undol=()
    x=list(undol)
    x.append(d)
    undol=tuple(x)


    from f6 import add_undo
    print(undol)
    print("Aplicația permite:\n"+
    "1. Adăugare \n"+
    "2. Ștergere \n"+
    "3. Căutări \n"+
    "4. Rapoarte \n"+
    "5. Filtru \n"+
    "6. Undo \n")


    

    while True:
        opt=(input("Optiunea este: "))

        if opt=='1':
            from f1 import adaugare
            print("Adăugare\modificare cheltuială  \n")
            n=int(input("Selectați apartamentul (1-12) : "))
            c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
            s=int(input("Introduceți suma : "))
            if (n>=1 and n<=12) and (c>=1 and c<=5):
                 d=adaugare(d,n,c,s)
                 undol=undol+(d,)
            else:
                print("Nu ati introdus corect datele!")
            

        elif opt=='2':
            from f2 import stergere1,stergere2,stergere3
            print("Alegeti : ")
            a=input("a-Șterge toate cheltuielile de la un apartament \n"+
                  "b-Șterge cheltuielile de la apartamente consecutive \n"+
                  "c-Șterge cheltuielile de un anumit tip de la toate apartamentele \n")
            if a=='a':
                n=int(input("Alegeti apartamentul(1-12) : "))
                if n>=1 and n<=12:
                    d=stergere1(d,n)
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='b':
                x=int(input("Alegeti primul apartament(1-12) : "))
                y=int(input("Alegeti ultimul apartament(1-12) : "))
                if (x>=1 and x<=12) and (y>=1 and y<=12):
                     d=stergere2(d,x,y)
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='c':
                c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
                if c>=1 and c<=5:
                     d=stergere3(d,c)
                else:
                    print("Nu ati introdus corect datele!")
            else:
                print("Nu ati selectat optiunea corectă!")
            undol=undol+(d,)

        elif opt=='3':
            from f3 import cautare1,cautare2,cautare3
            print("Alegeti : ")
            a=input("a-Tipărește toate apartamentele care au cheltuieli mai mari decât o sumă dată \n"+
                  "b-Tipărește cheltuielile de un anumit tip de la toate apartamentele \n"+
                  "c-Tipărește toate cheltuielile efectuate înainte de o zi și mai mari decât o sumă (se dă suma și ziua) \n")
            if a=='a':
                s=int(input("Introduceti suma: "))
                print(cautare1(d,s))
            elif a=='b':
                c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
                if c>=1 and c<=5:
                     print(cautare2(d,c))
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='c':
                s=int(input("Introduceti suma: "))
                z=int(input("Selectati ziua(1-31): "))
                if z>=1 and z<=31:
                      print(cautare3(d,zi,s,z))
                else:
                    print("Nu ati introdus corect datele!")
            else:
                print("Nu ati selectat optiunea corectă!")



        elif opt=='4':
            from f4 import raport1,raport2,raport3
            print("Alegeti : ")
            a=input("a-Tipărește suma totală pentru un tip de cheltuială \n"+
                  "b-Tipărește toate apartamentele sortate după un tip de cheltuială \n"+
                  "c-Tipărește totalul de cheltuieli pentru un apartament dat \n")
            if a=='a':
                c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
                if c>=1 and c<=5:
                    print(raport1(d,c))
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='b':
                c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
                if c>=1 and c<=5:
                    print(raport2(d,c))
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='c':
                n=int(input("Alegeti apartamentul(1-12) : "))
                if n>=1 and n<=12:
                    print(raport3(d,n))
                else:
                    print("Nu ati introdus corect datele!")
            else:
                print("Nu ati selectat optiunea corectă!")

        elif opt=='5':
            from f5 import filtrare1,filtrare2
            print("Alegeti : ")
            a=input("a-Elimină toate cheltuielile de un anumit tip \n"+
                  "b-Elimină toate cheltuielile mai mici decât o sumă dată \n")
            if a=='a':
                c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
                if c>=1 and c<=5:
                    d=filtrare1(d,c)
                else:
                    print("Nu ati introdus corect datele!")
            elif a=='b':
                s=int(input("Introduceti suma: "))
                d=filtrare2(d,s)
            else:
                print("Nu ati selectat optiunea corectă!")
            undol=undol+(d,)
        elif opt=='6':
            print("Undo")
        else:
           print("Inchidere program")
           break
        print(undol)

        
        

import teste_admin_bloc

run()

