from domain.cheltuiala import *
from domain.dict_manager import *
from utils.utile import *



def test_get_tip():
    assert(get_tip(1)=='apa')
    assert(get_tip(5)=='altele')

def test_get_cheltuial():
    d=generate_dict()
    assert(get_cheltuiala(1,1,d)==80)
    assert(get_cheltuiala(3,2,d)==100)

def test_set_cheltuiala():
    d=generate_dict()
    set_cheltuiala(1, 1, 5, d)
    set_cheltuiala(1, 2, 60, d)
    assert(get_cheltuiala(1,1,d)==5)
    assert(get_cheltuiala(1,2,d)==60)

def test_stergere_cheltuiala():
    d=generate_dict()
    stergere_ch(1,1,d)
    stergere_ch(1,2,d)
    assert(get_cheltuiala(1,1,d)==-1)
    assert(get_cheltuiala(1,2,d)==-1)

def test_get_cheltuieli_tip():
    d=generate_dict()
    assert(get_cheltuieli_tip(1,d)==[80,20,50,6,7,45,69,-1,-1,-1,-1,-1])
    assert(get_cheltuieli_tip(5,d)==[-1,-1,30,21,32,43,54,-1,-1,-1,-1,-1])

def test_get_cheltuieli_ap():
    d=generate_dict()
    assert(get_cheltuieli_ap(1,d)==[80,-1,-1,-1,-1])
    assert(get_cheltuieli_ap(3,d)==[50,100,60,150,30])

def test_get_sum_cheltuieli_tip():
    d=generate_dict()
    assert(get_sum_cheltuieli_tip(1,d)==277)
    assert(get_sum_cheltuieli_tip(5,d)==180)

def test_get_sum_cheltuieli_ap():
    d=generate_dict()
    assert(get_sum_cheltuieli_ap(d,1)==80)
    assert(get_sum_cheltuieli_ap(d,3)==390)

def test_adaugare():
    d=generate_dict()
    adaugare(1,1,12,d)
    assert(d[get_tip(1)][0]==12)
    adaugare(5,3,14,d)
    assert(d[get_tip(3)][4]==14)

def test_stergere_ch_ap1():
    d=generate_dict()
    stergere_ch_ap1(1,d)
    assert(get_cheltuieli_ap(1,d)==[-1]*5)
    stergere_ch_ap1(3, d)
    assert (get_cheltuieli_ap(3, d) == [-1] * 5)

def test_stergere_ch_ap2():
    d=generate_dict()
    stergere_ch_ap2(1,2,d)
    assert(get_cheltuieli_tip(1,d)==[-1,-1,50,6,7,45,69,-1,-1,-1,-1,-1])
    assert(get_cheltuieli_ap(2,d)==[-1]*5)

def test_stergere_cheltuiala_tip():
    d=generate_dict()
    stergere_cheltuiala_tip(1,d)
    assert(get_cheltuieli_tip(1,d)==[-1]*12)

def test_add_undo():
    u=()
    d=generate_dict()
    assert(add_undo(d,u)==(d,))

def test_versiune_china_deepcopy():
    d=generate_dict()
    assert(deepcopy(d)==d)
    d2={}
    d2=deepcopy(d)
    assert(d==d2)

def test_stergere_ultimu_el_tuplu():
    u=(1,2,3,4,5)
    assert(stergere_ultimu_el_tuplu(u)==(1,2,3,4))
    assert(stergere_ultimu_el_tuplu((1,))==())



test_get_tip()
test_get_cheltuial()
test_set_cheltuiala()
test_stergere_cheltuiala()
test_get_cheltuieli_tip()
test_get_cheltuieli_ap()
test_get_sum_cheltuieli_tip()
test_get_sum_cheltuieli_ap()
test_adaugare()
test_stergere_ch_ap1()
test_stergere_ch_ap2()
test_stergere_cheltuiala_tip()
test_add_undo()
test_versiune_china_deepcopy()
test_stergere_ultimu_el_tuplu()