#include "listH.h"
#include <iostream>

using namespace std;


PNod creare_rec(){
  TElem x;
  cout<<"x=";
  cin>>x;
  if (x==0)
    return NULL;
  else{
    PNod p=new Nod();
    p->e=x;
    p->urm=creare_rec();
    return p;
  }
}

Lista creare(){
   Lista l;
   l._prim=creare_rec();
}

void tipar_rec(PNod p){
   if (p!=NULL){
     cout<<p->e<<" ";
     tipar_rec(p->urm);
   }
}

void tipar(Lista l){
   tipar_rec(l._prim);
}

void distrug_rec(PNod p){
   if (p!=NULL){
     distrug_rec(p->urm);
     delete p;
   }
}

void distrug(Lista l) {
	//se elibereaza memoria alocata nodurilor listei
    distrug_rec(l._prim);
}

PNod getLastElem_rec(PNod original_p)
{
    if (original_p->urm == NULL)
        return original_p;
    else
        return getLastElem_rec(original_p->urm);
}

TElem getLastElem(Lista l)
{
    TElem new_elem;
    new_elem = getLastElem_rec(l._prim)->e;
    return new_elem;
}

PNod deleteNN_rec(PNod original_p, int n, int c)
{
    //cout<<endl<<"current elem "<<original_p->e;
    if(original_p == NULL)
        return NULL;
    if(c==n)
    {
        PNod p=new Nod();
        if(original_p->urm != NULL)
        {
            p->e=original_p->urm->e;
            //cout<<endl<<"some p "<<p->e;
            p->urm=deleteNN_rec(original_p->urm, n, 1);
            //delete(original_p);
        }
        else
            p=NULL;
        return p;
    }
    else
    {
        if(original_p->urm!=NULL)
            original_p->urm=deleteNN_rec(original_p->urm, n, c+1);
        return original_p;
    }
}

Lista deleteNN(Lista l, int n)
{
    Lista new_list;
    new_list._prim = deleteNN_rec(l._prim, n, 1);
    return new_list;
}
