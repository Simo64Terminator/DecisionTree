#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <stdexcept>
#include "stringUtility.h"
#include "arrayListUtility.h"

using namespace std;
using namespace list;

namespace d_tree{

//Definizioni

	typedef int choice;

	enum ERROR {OK, FAIL};
	
	typedef string Label;
	
	const Label emptyLabel = "$#$#$";
	
	const Label emptyLabelE = "#$#$#";
	
	//Definizioni nodo albero
	
		struct treeNode;

		typedef treeNode* Tree;

		const Tree emptyTree = nullptr;
		
	//Definizioni archi albero
	
		struct treeEdge;
		
		typedef treeEdge* Edge;
		
		const Edge emptyEdge = nullptr;

	//Definizioni algoritmo di predizione

		struct op;	//Definizione operatore di confronto

		//Definizione tipo di operazione
		enum Kind {OP_UGUALE, OP_DIVERSO, OP_MINORE, OP_MAGGIORE, OP_MAGGIOREUGUALE, OP_MINOREUGUALE};
		
		//Definizione coda per le coppie di inserimento
		struct coupleValues;
		
		struct op{
			int dim;
			Kind k;
		};
		
		typedef coupleValues* Couple;
		
		const Couple emptyCouple = nullptr;


//Funzioni per albero (ordinate secondo definizione nell'header)

	//Principali del TDD Tree
	
		//Funzioni di creazione
			
			Tree createEmpty();
	
			ERROR addElem(const Label, const Label, const Label, Tree&);

			Tree createNode(Label);
	
			void createEdge(Tree&, Tree&, const Label);
	
	
		//Funzioni di delete
	
			ERROR deleteElem(const Label, Tree&);
	
			ERROR deleteElemAux(const Label, Tree&);
	
			void deleteChild(const Label, Tree&);
	
	
		//Funzioni di editing
		
			ERROR editElem(const Label, const Label, Tree&);
	
	
		//Funzioni di print
			
			void printTree(const Tree&);
	
			void printTree(const Tree&, int);
	
			void printVariables(const Tree&);
	
			void setVariables(const Tree&, list::List&);
	
	
		//Funzioni ausiliarie del TDD Tree

			bool isEmpty(Tree);

			bool isEmpty(Edge);
	
			bool member(const Label, const Tree&);

			Tree getNode(const Label, const Tree&);
	
			int degree(const Label, const Tree&);
	
			list::List children(const Label l, const Tree& t);

			bool hasChildWithLabel(const Label, const Tree&);

			bool checkEdgeLabel(const Label);

			Label normalizeVariable(Label);

			Label normalizeValue(Label);


	//Funzioni albero predittivo (mono scelta e scelta con insiemi di coppie)
	
		//Funzioni albero predittivo Mono-Scelta
	
			Label compareMono(const Tree&);
	
			Label userChoice(const Tree&);
	
	
		//Funzioni albero predittivo con insiemi di coppie
	
			Label compareMulti(const Tree&, Couple&);
	
			Label compareMultiMain(const Tree&);

			void enqueue(const Label, const Label, Couple&);

			Couple dequeue(Couple&);
	
			Couple setCouples(Couple&);
	
			Couple createEmptyCouple();
		
			bool isEmpty(const Couple);
	
	
		//Funzioni ausiliarie albero predittivo (entrambe le versioni)
	
			bool compareEdge(Label, Edge);
	
			op opDefinition(const Label);
	
			bool isNumber(const Label);
	
			bool compareInt(op, int, int);	
}


//Funzioni per input/output, non facenti parte del TDD Tree
d_tree::Tree readFromFile(string);

#endif
