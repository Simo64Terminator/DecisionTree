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

// Base Definitions

	typedef int choice;

	enum ERROR {OK, FAIL};
	
	typedef string Label;
	
	const Label emptyLabel = "$#$#$";
	
	const Label emptyLabelE = "#$#$#";
	
	// Tree Node Definitions
	
		struct treeNode;

		typedef treeNode* Tree;

		const Tree emptyTree = nullptr;
		
	// Tree Edge Definitions
	
		struct treeEdge;
		
		typedef treeEdge* Edge;
		
		const Edge emptyEdge = nullptr;

	// Prediction Algorithm Definitions

		struct op;	// Comparison Operator

		// Operation Types
		enum Kind {EQUAL_OP, NOT_EQUAL_OP, LESS_THAN_OP, MORE_THAN_OP, MORE_OR_EQUAL_THAN_OP, LESS_OR_EQUAL_THAN_OP};
		
		// Definitions used to determine value and operator
		struct coupleValues;
		
		struct op{
			int dim;
			Kind k;
		};
		
		typedef coupleValues* Couple;
		
		const Couple emptyCouple = nullptr;


// Tree Functions (ordinate secondo definizione nell'header)

	// TOD Tree Base Functions
	
		// Creation Functions
			
			Tree createEmpty();
	
			ERROR addElem(const Label, const Label, const Label, Tree&);

			Tree createNode(Label);
	
			void createEdge(Tree&, Tree&, const Label);
	
	
		// Delete functions
	
			ERROR deleteElem(const Label, Tree&);
	
			ERROR deleteElemAux(const Label, Tree&);
	
			void deleteChild(const Label, Tree&);
	
	
		// Editing Functions
		
			ERROR editElem(const Label, const Label, Tree&);
	
	
		// Printing Functions
			
			void printTree(const Tree&);
	
			void printTree(const Tree&, int);
	
			void printVariables(const Tree&);
	
			void setVariables(const Tree&, list::List&);
	
	
		// Auxiliary TOD Tree Functions

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


	// Prediction Tree Functions (single choice and multiple choice)
	
		// Single Choice Functions
	
			Label compareMono(const Tree&);
	
			Label userChoice(const Tree&);
	
	
		// Multiple Choice functions
	
			Label compareMulti(const Tree&, Couple&);
	
			Label compareMultiMain(const Tree&);

			void enqueue(const Label, const Label, Couple&);

			Couple dequeue(Couple&);
	
			Couple setCouples(Couple&);
	
			Couple createEmptyCouple();
		
			bool isEmpty(const Couple);
	
	
		// Auxiliary Functions
	
			bool compareEdge(Label, Edge);
	
			op opDefinition(const Label);		// Defines Operator
	
			bool isNumber(const Label);
	
			bool compareInt(op, int, int);	
}


// Input/Output Functions (not part of TOD Tree)
d_tree::Tree readFromFile(string);

#endif
