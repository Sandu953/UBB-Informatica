def raport1(d:dict,c:int):
    """
    Tipărește suma totală pentru un tip de cheltuială

    d-dictionar 

    c-int, rep. tipul cheltuielii

    return s, s-suma cheltuielilor de un anumit tip
    
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
    s=0
    for i in d[c]:
        if i!=-1:
            s=s+i
    return s

def raport2(d:dict,c:int):
    """
    Tipărește toate apartamentele sortate după un tip de cheltuială

    d-dict

    c-int, rep. tipul cheltuielii

    return l, l-lista apartamentelor sortate
    
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
    l=[]
    mx=-1
    mx1=999999
    while len(l)!=12:
        for i in d[c]:
            if i>mx and i<mx1:
                mx=i
        l.append(mx)
        mx1=mx
        mx=-1
    return l


def raport3(d:dict,n:int):
    """
    Tipărește totalul de cheltuieli pentru un apartament dat

    d-dictionar

    n-int, rep. nr. apartamentului

    return s, s-suma cheltuielilor unui apartament
    
    """
    s=0
    for i in d:
        if(d[i][n-1]!=-1):
            s=s+d[i][n-1]
    return s
def test_raport1():
     d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
     assert(raport1(d,1)==277)
     assert(raport1(d,3)==257)


def test_raport2():
    d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
    
    assert(raport2(d,1)==[80,69,50,45,20,7,6,-1,-1,-1,-1,-1])
    assert(raport2(d,2)==[100,66,8,3,-1,-1,-1,-1,-1,-1,-1,-1,])
def test_raport3():
    d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[100,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[20,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
    assert(raport3(d,3)==390)
    assert(raport3(d,1)==200)



