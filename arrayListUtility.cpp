#include "arrayListUtility.h"

using namespace list;

// Functions used ONLY for printing


// Creates an empty dynamic array
list::List list::createEmpty()
{
	List l;
	l.size = 0;
	l.maxsize = BLOCKDIM;
	Elem* aux = new Elem[BLOCKDIM];
	l.list = aux;
	
	return l;
}

// re-use add function to do a rear add
void list::addBack(Elem e, List& l)
{
	add(l.size, e, l);
}

// Add in "pos" position
void list::add(int pos, Elem e, List& l)
{
	// Checking "pos" value
	if(pos < 0 || pos > l.size) return;	
	
	// Resizing d_array
	if(l.size == l.maxsize)
	{
		// Creating aux d_array with more space
		List aux;
		aux.size = l.size + 1;
		aux.maxsize = l.maxsize + BLOCKDIM;
		Elem* tmp = new Elem[aux.maxsize];
		aux.list = tmp;
		
		// Saving elements before "pos"
		for(int i = 0; i < pos; ++i)
		{
			aux.list[i] = l.list[i];
		}
		
		// Save new element in "pos"
		aux.list[pos] = e;
		
		// Saving the rest of the old d_array after "pos"
		for(int i = pos+1; i < aux.size; ++i)
		{
			aux.list[i] = l.list[i-1];
		}
		
		// Deleting old d_array and make l point to aux
		delete[] l.list;
		l = aux;
		return;
	}
	
	// Not resizing d_array
	l.size++;
	for(int i = l.size-1; i > pos; --i)
		l.list[i] = l.list[i-1];
	l.list[pos]	= e;
}


int list::size(const List& l)
{
	return l.size;
}


// Checking if "e" exists in d_array "l"
bool list::findElem(Elem e, List l)
{
	for(int i = 0; i < l.size; ++i)
	{
		if(l.list[i] == e)
			return true;
	}
	
	return false;
}


bool list::isEmpty(List l)
{
	return !(size(l));
}
