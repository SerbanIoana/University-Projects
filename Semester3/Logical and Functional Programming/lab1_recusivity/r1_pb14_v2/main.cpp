#include "listH.h"
#include <iostream>

using namespace std;

int main()
{
    Lista list1;
    list1=creare();
    tipar(list1);

    TElem last_elem;
    last_elem=getLastElem(list1);
    cout<<endl<<"The last element in list1 is "<< last_elem << endl;

    Lista list2;
    list2=creare();
    tipar(list2);
    cout<<endl;

    cout<<endl;
    Lista new_list=deleteNN(list2,3);
    tipar(new_list);


    return 0;
}
