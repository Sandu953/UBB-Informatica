
def adaugare(d:dict,n:int,c:int,s:int):
    """
    adaugae/modificare cheltuieli

    d-dictionarul de cheltuieli
    
    n-int, nr apartamentului, 1<=n<=12

    c-int, tipul cheltuielii, 1<=c<=5

    s-int, valoarea cheltuielii

    return d
    
    """

    l=[]
    #print("adăugare\modificare cheltuială  \n")
    #n=int(input("Selectați apartamentul (1-12) : "))
    #c=int(input("Selectați tipul cheltuielii: \n 1-apa \n 2-canal \n 3-inclzire \n 4-gaz \n 5-altele  \n"))
    #s=int(input("Introduceți suma : "))
    if c==1:
        c='apa'
    elif c==2:
        c='canal'
    elif c==3:
        c='incalzire'
    elif c==4:
        c='gaz'
    elif c==5:
        c='altele'
    l=d[c]
    l[n-1]=s
    d[c]=l
    #t="Cheltuiala la " + str(c) + " in valoare de " + str(s) + " lei a fost " + str(a) + " la apartamentul " +str(n)
    return(d)

def testare_ad():
    d={
         "apa":[-1]*12,
        "canal":[-1]*12,
        "incalzire":[-1]*12,
        "gaz":[-1]*12,
        "altele":[-1]*12
        }
    adaugare(d,3,3,205)
    assert(d["incalzire"]==[-1,-1,205,-1,-1,-1,-1,-1,-1,-1,-1,-1])
    adaugare(d,3,3,0)
    assert(d["incalzire"]==[-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1])

   
