def filtrare1(d:dict,c:int):
    """
    Elimină toate cheltuielile de un anumit tip

    d-dictionar

    c-int ; reprezinta tipul cheltuielii

    returneaza un dictionar
    
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

def filtrare2(d:dict,s:int):
    """
    Elimină toate cheltuielile mai mici decât o sumă dată

    "d-dictionar

    s-int; reprezinta suma

    returneaza un dictionar
    
    """
    for i in d:
        for a in range(len(d[i])):
            if d[i][a]<s:
                d[i][a]=-1
    return d


def testf1():
     d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
     filtrare1(d,1)
     assert(d["apa"]==[-1]*12)
     assert(d["canal"]==[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1])
     filtrare1(d,2)
     assert(d["canal"]==[-1]*12)

def testf2():
     d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
     filtrare2(d,50)
     assert(d["apa"]==[80,-1,50,-1,-1,-1,69,-1,-1,-1,-1,-1])
     assert(d["altele"]==[-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1])
     filtrare2(d,200)
     assert(d["gaz"]==[-1]*12)

