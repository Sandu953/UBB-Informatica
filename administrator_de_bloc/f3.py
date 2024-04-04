def cautare1(d:dict,s:int):
    """
    Tipărește toate apartamentele care au cheltuieli mai mari decât o sumă dată
    
    d-dictionar 
    s-int

    return lista
    """
    l=[]
    for i in range(12):
        c=0
        for a in d:
            if d[a][i]!=-1:
                c=c+d[a][i]
        if c>=s:
            l.append("ap."+str(i+1))
    return l

def cautare2(d:dict,c:int):
    """
    Tipărește cheltuielile de un anumit tip de la toate apartamentele

    d-dictionar

    c-int; reprezinta tipul cheltuielii

    returneaza o lista
    
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
    l=d[c]
    return l


def cautare3(d:dict,zi:dict,s:int,z:int):
    """
    Tipărește toate cheltuielile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)

    d-dictionar

    zi-dictionar; reprezinta zilele in care s-au efectuat cheltuielile

    s-int

    zi int

    returneaza un dictionar
    
    """
    o={
        "apa":[],
     "canal":[],
     "incalzire":[],
     "gaz":[],
     "altele":[]  
        
        
        }
    for c in d:
        for i in range(12):
            if zi[c][i]>=z and d[c][i]>=s:
                o[c].append(d[c][i])
    return o


def test_cautare1():
    d={
         "apa":[80,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,-1,-1,-1,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1]
        }
    assert(cautare1(d,20)==['ap.1', 'ap.3', 'ap.10'])
    assert(cautare1(d,400)==[])

def test_cautare2():
    d={
         "apa":[80,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,-1,-1,-1,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1]
        }
    assert(cautare2(d,3)==[-1,-1,60,-1,-1,-1,-1,-1,-1,90,-1,-1])
    assert(cautare2(d,1)==[80,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1])

def test_cautare3():
    d={
         "apa":[80,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,-1,-1,-1,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1]
        }
    zi={
         "apa":[8,20,15,6,7,14,9,1,31,21,11,26],
        "canal":[25,21,31,26,19,24,15,16,3,13,20,6],
        "incalzire":[14,20,28,31,23,7,2,26,13,12,19,7],
        "gaz":[1,19,15,17,2,3,14,10,29,18,21,4],
        "altele":[5,14,20,8,2,18,23,12,22,27,19,13]
        }
    assert(cautare3(d,zi,30,6)=={'apa': [80, 50], 'canal': [100], 'incalzire': [60, 90], 'gaz': [150], 'altele': [30]})