#include "arrayListUtility.h"

using namespace list;

//Creo una lista vuota
list::List list::createEmpty()
{
	List l;
	l.size = 0;
	l.maxsize = BLOCKDIM;
	Elem* aux = new Elem[BLOCKDIM];
	l.list = aux;
	
	return l;
}

//Aggiungo in fondo alla lista usando la funzione add
void list::addBack(Elem e, List& l)
{
	add(l.size, e, l);
}

//Aggiungo un elemento in una posizione data da pos
void list::add(int pos, Elem e, List& l)
{
	//Se la posizione è non valida, allora ritorno
	if(pos < 0 || pos > l.size) return;	
	
	//Scatta il ridimensionamento
	if(l.size == l.maxsize)
	{
		//Creo un nuovo array dinamico con spazio aggiunto
		List aux;
		aux.size = l.size + 1;
		aux.maxsize = l.maxsize + BLOCKDIM;
		Elem* tmp = new Elem[aux.maxsize];
		aux.list = tmp;
		
		//Salvo il contenuto prima di pos
		for(int i = 0; i < pos; ++i)
		{
			aux.list[i] = l.list[i];
		}
		
		//Salvo e in pos
		aux.list[pos] = e;
		
		//Shifto a destra rispetto alla posizione di pos
		for(int i = pos+1; i < aux.size; ++i)
		{
			aux.list[i] = l.list[i-1];
		}
		
		//Elimino il vecchio array dinamico ed applico le modifiche effettuate ad l
		delete[] l.list;
		l = aux;
		return;
	}
	
	//Se non c'è bisogno di ridimensionamento
	l.size++;
	for(int i = l.size-1; i > pos; --i)
		l.list[i] = l.list[i-1];
	l.list[pos]	= e;
}


//Restituisce la dimensione della lista
int list::size(const List& l)
{
	return l.size;
}


//Verifico l'esistenza di un elemento con uno specifico nome
bool list::findElem(Elem e, List l)
{
	for(int i = 0; i < l.size; ++i)
	{
		if(l.list[i] == e)
			return true;
	}
	
	return false;
}


//Restituisce se la lista è vuota o meno
bool list::isEmpty(List l)
{
	return !(size(l));
}
