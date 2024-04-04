
def get_tip(tip):
    """
    returneaza tipul cheii in format string pentru a fi folosit la cheile dictionarului
    :param tip: tipul cheltuielii
    :type: tip: int
    :return: str
    """

    c=tip
    if c == 1:
        c = 'apa'
    elif c == 2:
        c = 'canal'
    elif c == 3:
        c = 'incalzire'
    elif c == 4:
        c = 'gaz'
    elif c == 5:
        c = 'altele'

    return c

def get_cheltuiala(ap, tip, d):
    """
    :param ap:
    :param tip:
    :param d:
    :return: returneaza cheltuiala apartamentului
    """
    return d[get_tip(tip)][ap-1]


def set_cheltuiala(ap,tip,suma,d):
    """
    schimba cheltuiala de la un ap
    :param ap: 
    :param tip: 
    :param suma: 
    :param d: 
    :return: 
    """
    d[get_tip(tip)][ap-1]=suma


def stergere_ch(ap,tip,d):
    """
    sterge o cheltuila de la un ap
    :param ap:
    :param tip:
    :param d:
    :return:
    """
    d[get_tip(tip)][ap-1]=-1



