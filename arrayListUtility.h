#ifndef ARRAYLISTUTILITY_H
#define ARRAYLISTUTILITY_H

#include <iostream>

using namespace std;

namespace list{

//Definizioni array dinamico

	const int BLOCKDIM = 100;

	typedef string Elem;

	const Elem emptyElem = "$#$#$";
	
	struct d_arr{
		Elem* list;
		int size;
		int maxsize;
	};

	typedef d_arr List;


//Funzioni lista

	List createEmpty();					//Creo la lista vuota
	void addBack(Elem, List&);			//Aggiungo un elemento in fondo alla lista
	void add(int, Elem, List&);			//Aggiungo un elemento data la posizione richiesta
	bool findElem(Elem, List);
	bool isEmpty(List);

	int size(const List&);				//Restituisco la dimensione della lista

}

#endif
