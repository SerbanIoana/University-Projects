#ifndef LISTH_H_INCLUDED
#define LISTH_H_INCLUDED

//tip de data generic (pentru moment este intreg)
typedef int TElem;

//referire a structurii Nod;
struct Nod;

//se defineste tipul PNod ca fiind adresa unui Nod
typedef Nod *PNod;

typedef struct Nod{
    TElem e;
	PNod urm;
};

typedef struct{
//prim este adresa primului Nod din lista
	PNod _prim;
} Lista;

//operatii pe lista - INTERFATA

//crearea unei liste din valori citite pana la 0
    Lista creare();
//tiparirea elementelor unei liste
    void tipar(Lista l);
// destructorul listei
	void distruge(Lista l);

//14. a. Determine the last element of a list.
TElem getLastElem(Lista l);

//b. Delete elements from a list, from position n to n.
Lista deleteNN(Lista l, int n);

#endif // LISTH_H_INCLUDED
