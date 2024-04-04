
def stergere1(d:dict,n:int):
    """
    Șterge toate cheltuielile de la un apartament

    d-dict

    n-int, nr.apartament, 1<=n<=12
    
    return d

    """
    for i in d:
        d[i][n-1]=-1
    return(d)

def stergere2(d:dict,a:int,b:int):
    """
    Șterge cheltuielile de la apartamente consecutive (Ex. se dau două
numere de apartament 2 și 5 și se șterg toate cheltuielile de la
apartamentele 1,2,3,4 și 5)

    d-dictionar

    a,b-int, a<b,1<=a,b<=12

    return d

    """
    for i in range(a,b+1):
        stergere1(d,i)
    return d

def stergere3(d:list,c:int):
    """
    Șterge cheltuielile de un anumit tip de la toate apartamentele

    d-dict 

    c-int, tipul cheltuielii

    return d
    """
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
    d[c]=[-1]*12
    return d

def test_stergere1():
    d={
         "apa":[80,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,-1,-1,-1,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1]
        }
    stergere1(d,3)
    assert(d["apa"]==[80,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1])
    assert(d["incalzire"]==[-1,-1,-1,-1,-1,-1,-1,-1,-1,90,-1,-1])
    assert(d["gaz"]==[-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1])

def test_stergere2():
    d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
    stergere2(d,3,6)
    assert(d["apa"]==[80,20,-1,-1,-1,-1,69,-1,-1,-1,-1,-1])
    assert(d["incalzire"]==[-1,-1,-1,-1,-1,-1,-1,-1,-1,90,-1,-1])
    assert(d["gaz"]==[-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1])

def test_stergere3():
    d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
    stergere3(d,1)
    assert(d["apa"]==[-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1])
    assert(d["incalzire"]==[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1])

   