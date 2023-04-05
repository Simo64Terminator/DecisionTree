#ifndef ARRAYLISTUTILITY_H
#define ARRAYLISTUTILITY_H

#include <iostream>

using namespace std;

namespace list{

// Dynamic Array definitions

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

	List createEmpty();					// Create empty d_Array
	void addBack(Elem, List&);			// Add element at the bottom of d_array
	void add(int, Elem, List&);			// Add element in n position of d_array
	bool findElem(Elem, List);
	bool isEmpty(List);

	int size(const List&);				// Returns d_array size

}

#endif
