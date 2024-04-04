from domain.cheltuiala import get_cheltuiala, get_tip, set_cheltuiala

def generate_dict():
      d={
         "apa":[80,20,50,6,7,45,69,-1,-1,-1,-1,-1],
        "canal":[-1,-1,100,3,8,66,-1,-1,-1,-1,-1,-1],
        "incalzire":[-1,-1,60,5,2,100,-1,-1,-1,90,-1,-1],
        "gaz":[-1,-1,150,50,10,20,-1,-1,-1,-1,-1,-1],
        "altele":[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1]
        }
      return d

def generate_zile():
    zi = {
        "apa": [8, 20, 15, 6, 7, 14, 9, 1, 31, 21, 11, 26],
        "canal": [25, 21, 31, 26, 19, 24, 15, 16, 3, 13, 20, 6],
        "incalzire": [14, 20, 28, 31, 23, 7, 2, 26, 13, 12, 19, 7],
        "gaz": [1, 19, 15, 17, 2, 3, 14, 10, 29, 18, 21, 4],
        "altele": [5, 14, 20, 8, 2, 18, 23, 12, 22, 27, 19, 13]
    }
    return zi

def generate_gol():
    d={
        "apa": [],
        "canal": [],
        "incalzire": [],
        "gaz": [],
        "altele": []
    }
    return d
def get_cheltuieli_tip(tip, d):
    """

    :param tip: tipul cheltuielii
    :return: returneaza o lista cu cheltuielile de un anumit tip
    """
    return d[get_tip(tip)]

def get_cheltuieli_ap(ap, d):
    """

    :param ap: rep. nr ap
    :return: returneaza o lista cu toate cheltuielile unui apartament
    """
    l=[]
    for i in d:
        l.append(get_cheltuiala(ap,i,d))
    return l

def get_sum_cheltuieli_tip(tip, d):
    """

    :param tip:
    :param d:
    :return:returneaza suma cheltuielilor de un anumit tip
    """
    s=0
    for i in d[get_tip(tip)]:
        if i!=-1:
            s=s+i
    return s

def get_sum_cheltuieli_ap(d,ap):
    """

    :param d:
    :param ap:
    :return: returneaza suma cheltuielilor unui ap
    """
    s=0
    for i in d:
        if(d[i][ap-1]!=-1):
            s=s+d[i][ap-1]
    return s

def adaugare(ap,tip,suma,d):
    """

    :param ap: int
    :param tip: tipul cheltuielii
    :param d: dictionar
    :param suma: int
    :return: returneaza cheltuiala modificata
    """
    return set_cheltuiala(ap,get_tip(tip),suma,d)

def stergere_ch_ap1(ap,d):
    """
    sterge toate cheltuielile unui apartament
    :param ap:
    :param d:
    :return:
    """
    for i in d:
        set_cheltuiala(ap,i,-1,d)

def stergere_ch_ap2(ap1,ap2,d):
    """
     sterge toate cheltuielile de la ap1 pana la ap2
    :param ap1:
    :param ap2:
    :param d:
    :return:
    """
    for i in range(ap1,ap2+1):
        stergere_ch_ap1(i,d)

def stergere_cheltuiala_tip(tip,d):
    """
    sterge toate cheltuielile de un anumit tip
    :param tip:
    :param d:
    :return:
    """
    d[get_tip(tip)]=[-1]*12

def add_undo(d, undo: tuple):
    """
    adauga in tuple dictionarul d
    :param d:
    :param undo:
    :return:
    """
    x = (d,)
    undo = undo + x
    return undo


def deepcopy(d:dict):
    """
    face o copie dictionarului
    :param d:
    :return:
    """
    return {key: value[:] for key, value in d.items()}



