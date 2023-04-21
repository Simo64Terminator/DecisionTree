#include "decisionTree.h"

using namespace d_tree;


/******************STRUCT DEFINITIONS*****************/

struct d_tree::treeNode{
	Label label;
	treeEdge* edgeList;
};

struct d_tree::treeEdge{
	Label label;
	treeNode* node;
	treeEdge* nextEdge;
};

struct d_tree::coupleValues{
	Label variable;
	Label value;
	coupleValues* next;
};



/**************FUNCTIONS FOR PREDICTION TREE WITH POINTER TO EDGE AND TO NODE LIST IMPLEMENTATION**************/

/**********MAIN TOD TREE FUNCTIONS**********/

/*****CREATION FUNCTIONS*****/


// New Tree
Tree d_tree::createEmpty(){
	return emptyTree;
}


// New node
d_tree::ERROR d_tree::addElem(const Label fatherNode, const Label childNode, const Label edgeLabel, Tree &t){

	// Generating root: if Tree is Empty and user uses $#$#$ as root's father, then we create the root
	if((fatherNode == emptyLabel) && isEmpty(t)){
		t = createNode(childNode);
		return OK;
	}
	
	// If it finds an already existing node or edge, then element will not be inserted
	if(member(childNode, t))
		return FAIL;
	
	if(!checkEdgeLabel(edgeLabel))
		return FAIL;
	
	// Searches father node
	Tree auxT = getNode(fatherNode, t);
	
	// If father node was not found, then returns FAIL, otherwise new node will be created 
	if(auxT == emptyTree)
		return FAIL;
	else
	{
		Tree child = createNode(childNode);
		createEdge(auxT, child, edgeLabel);
	}
	
	return OK;
}


// New Node
Tree d_tree::createNode(Label l){
	Tree aux = new treeNode;
	aux->label = l;
	aux->edgeList = emptyEdge;
	return aux;
}


// New labeled edge
void d_tree::createEdge(Tree& father, Tree& child, const Label edgeLabel)
{
	// New Edge
	Edge auxE = new treeEdge;
	
	// Label applied
	auxE->label = edgeLabel;
	
	// Connecting child
	auxE->node = child;
	
	// Connecting Father
	auxE->nextEdge = father->edgeList;
	father->edgeList = auxE;
}


/*****DELETE FUNCTIONS*****/


// Node elimination (starting with root without children)
d_tree::ERROR d_tree::deleteElem(const Label l, Tree& t){
	
	// Special case: if Tree is not empty and label is equal to root's label, then we want to eliminate the root
	if(!isEmpty(t) && t->label == l)
	{
		if(d_tree::degree(l, t) == 0)	// It checks degree of root: if 0 then it will be eliminated
		{
			delete t;
			t = emptyTree;
			return OK;
		}
		else
			return FAIL;	// Otherwise returns FAIL because we wouldn't know how to connect root's children
	}
	
	return deleteElemAux(l, t); // Other cases not related to root
}


// Recoursive node elimination (not for root)
d_tree::ERROR d_tree::deleteElemAux(const Label l, Tree& t){
	
	// If tree or sub-tree is empty, returns FAIL
	if(isEmpty(t)) return FAIL;
	
	// Checking if node t has a child with label l (the one we want to eliminate)
	if(hasChildWithLabel(l, t))
	{
		deleteChild(l, t);
		return OK;
	}
	
	// Otherwise keeps visiting tree unless finding a node with label l, or when no more nodes can be visited (simulation suggested to better comprehend the algorithm)
	Edge child = t->edgeList;
	
	while(!isEmpty(child))
	{
		if(deleteElemAux(l, child->node) == OK)
			return OK;
		else
			child = child->nextEdge;
	}
	
	return FAIL;	
}


// Deleting node's child (remember that an edges list is used)
void d_tree::deleteChild(const Label l, Tree& t)
{
	Edge auxE = t->edgeList;
	Edge prevE = emptyEdge;

	// Looking for an edge that has a node with label l connected
	while((auxE->node)->label != l){
		prevE = auxE;
		auxE = auxE->nextEdge;
	}
	
	// Pointer to node to be eliminated
	Tree auxT = auxE->node;
	
	
	// Algorithm to save node's children: we connect his edge list to the end of father's edge list
	Edge lastEdge = auxE;
	
	while(!isEmpty(lastEdge->nextEdge))
		lastEdge = lastEdge->nextEdge;
	
	// Saving to the end of edge list
	lastEdge->nextEdge = auxT->edgeList;
	
	
	// If the node to be deleted was in first position of the edgelist, then we need to make father pointing to its next child, otherwise it just updates a child nextEdge pointer
	if(isEmpty(prevE))
		t->edgeList = auxE->nextEdge;
	else
		prevE->nextEdge = auxE->nextEdge;
	
	
	// Deleting
	delete auxE;
	delete auxT;

}


/*****EDITING FUNCTIONS*****/


// Searching a node with label l1, and changes it with l2
d_tree::ERROR d_tree::editElem(const Label l1, const Label l2, Tree& t)
{
	// Finds Node
	Tree auxT = getNode(l1, t);
	
	// If node exists
	if(!isEmpty(auxT))
	{
		auxT->label = l2;
		return OK;
	}
	
	// If node doesn't exist
	return FAIL;
}


/*****PRINTING FUNCTIONS*****/


// Main function used to simplify function call printTree(t,0) (where 0 is used for indentation)
void d_tree::printTree(const Tree& t)
{
	printTree(t, 0);
}


// Aux recoursive function for printTree(t)
void d_tree::printTree(const Tree& t, int depth)
{
	if(isEmpty(t)) return;
	
	string indentT = "--";
	
	// Showing tree depth with indentations ("--")
	for(int i=0; i<depth; ++i)
		cout << indentT;
		
	cout << t->label << endl;
	
	// Scrolling starting from edgeList
	Edge auxE = t->edgeList;
	
	while(!isEmpty(auxE))
	{
		// Shows edge label, and what nodes are connected to it
		for(int i=0; i<depth; ++i)
			cout << indentT;
		cout << "(" << auxE->label << ")";
		
		printTree(auxE->node, depth+1);
		auxE = auxE->nextEdge;
	}
}


void d_tree::printVariables(const Tree& t){
	
	// Creates an empty list
	list::List lst = list::createEmpty();
	
	// Inserting variables into lst
	setVariables(t, lst);
	
	if(list::isEmpty(lst))
		cout << "\nNo variables";
	else
		for(int i = 0; i < lst.size; ++i)
			cout << "\n - Variabile " << i+1 << ": " << lst.list[i];	// Shows list content
	
	cout << "\n";
}


// Aux function for printVariables (recoursive)
void d_tree::setVariables(const Tree& t, list::List& lst){
	
	// If empty returns
	if(isEmpty(t) || (isEmpty(t->edgeList))) return;
	
	// Saving node label without underscore
	Label l = normalizeVariable(t->label);
	
	// If there's no element in the list with same label, then updates the list, otherwise nothing will happen
	if(!list::findElem(l, lst))
		list::addBack(l, lst);
	
	// Recoursive call to explore tree
	Edge auxE = t->edgeList;
	while(!isEmpty(auxE)){
		setVariables(auxE->node, lst);
		auxE = auxE->nextEdge;
	}
}


/*****AUX FUNCTIONS*****/


bool d_tree::isEmpty(Tree t){
	return(t==emptyTree);
}


bool d_tree::isEmpty(Edge e)
{
	return(e == emptyEdge);
}


// Finds a node with label l (recoursive)
bool d_tree::member(const Label l, const Tree& t){

	// If tree or subtree are empty, returns false
	if(isEmpty(t))
		return false;

	// If finds a node with label l, returns true
	if(t->label == l)
		return true;
		
	// Points to edge list
	Edge aux = t->edgeList;
	
	// Scrolling until it finds an element with label l, or at the end of recoursive calls
	while(aux != emptyEdge)
	{
		if(!member(l, aux->node))
			aux = aux->nextEdge;
		else
			return true;
	}
	
	return false;
}


// Returns node with label l (A drawing of this kind of tree is suggested)
Tree d_tree::getNode(const Label l, const Tree& t){
	
	// If Tree is empty, or label is emptyt, returns emptyTree (equals to emptyNode)
	if(isEmpty(t) || l==emptyLabel)
		return emptyTree;
		
	// If finds a node with label l, returns it
	if(t->label == l)
		return t;
	
	// Suggested simulation to better understand the algorithm
	Edge aux = t->edgeList;
	Tree resNode;
	
	while(aux != emptyEdge)
	{
		resNode = getNode(l, aux->node);
		if(resNode == emptyTree)
			aux = aux->nextEdge;
		else
			return resNode;					// Returns node if found
	}
	
	// Empty edge list, going back from one recoursion
	return emptyTree;
}


// Return node's degree
int d_tree::degree(const Label l, const Tree& t){
	
	if(!member(l,t))
		return -1;
	else
		return list::size(children(l, t)); // Returns node's children list dimension 
}


// Returns node's children list
list::List d_tree::children(const Label l, const Tree& t)
{
	// Finds node and prepares an empty list
	Tree auxT = getNode(l, t);
	list::List lst = list::createEmpty();
	
	if(!isEmpty(auxT))
	{
		// Points to l's children
		Edge child = auxT->edgeList;
		
		// Scrolling on all l's children
		while(!isEmpty(child))
		{
			list::addBack((child->node)->label, lst);
			child = child->nextEdge;
		}
	}
	
	return lst;
}


// Searching child with label l (recoursive)
bool d_tree::hasChildWithLabel(const Label l, const Tree& t)
{
	// If tree is empty, then returing false
	if(isEmpty(t)) return false;
	
	// Starting from first child from father's child list
	Edge child = t->edgeList;
	
	// Searching in list
	while(!isEmpty(child))
	{
		if((child->node)->label == l)
			return true; // Found child with label l, returning true...
		else
			child = child->nextEdge;
	}

	// ...otherwise returning false
	return false;
}


// Checking if first character from edge label is an operator
bool d_tree::checkEdgeLabel(const Label edgeLabel)
{
	// Recovering first character from edge label
	char firstChar = edgeLabel[0];

	switch(firstChar){
		case '!':							// Different from
			if(edgeLabel[1] == '=')
				break;
			else
				return false;					// Not found
			break;
		case '=':							// Equal
			break;
			
		case '<':							// Less than
			break;
			
		case '>':							// More than
			break;
		
		default:							// Not found
			return false;
	}
	
	return true;
}


// Eliminating underscore character from string number
d_tree::Label d_tree::normalizeVariable(Label l)
{
	Label aux = l;
	
	// Searching last underscore
	int found = aux.find_last_of("_");

	// Returning substring from 0 to underscore_position-1
	aux = aux.substr(0, found);

	return aux;
}


// Eliminating confront operator from value label
d_tree::Label d_tree::normalizeValue(Label l)
{
	// Defining operation in label
	op operation = opDefinition(l);
	
	// Isolating label without confront operator
	Label normalizedValue = l.substr(operation.dim, l.size());
	
	return normalizedValue;
}


/**********MAIN FUNCTIONS FOR TOD TREE**********/

/*****PREDICTION FUNCTIONS SINGLE CHOICE*****/


// Recoursive (one choice at a time)
d_tree::Label d_tree::compareMono(const Tree& t)
{
	// If empty returns emptyLabel
	if(isEmpty(t)) return emptyLabel;
	
	// If a leaf node is found, then returns edge label
	if(isEmpty(((t->edgeList)->node)->edgeList)) return (t->edgeList)->label;
	
	// User chooses a label
	Label l = userChoice(t);
	
	// Travelling in tree
	Edge auxE = t->edgeList;
	Label result = emptyLabel;

	while(!isEmpty(auxE))
	{
		if(compareEdge(l, auxE))
		{
			result = compareMono(auxE->node);
			auxE = emptyEdge;
		}
		else
			auxE = auxE->nextEdge;
	}
		
	return result;
}


// Auxiliary function, used for letting user choose a string
d_tree::Label d_tree::userChoice(const Tree& t)
{	
	// Scrolling edge list
	Edge tmp = t->edgeList;

	// Shows possible variables
	cout << "\n - Type: " << t->label << " - Possibile decisions are:\n";
	while(!isEmpty(tmp)){
		cout << " - " << tmp->label << "\n";
		tmp = tmp->nextEdge;
	}
	cout << "\n";
	
	// Inserting
	cout << "Insert value/string: ";
	Label aux;
	cin >> aux;
	removeBlanksAndLower(aux);
	
	return aux;
}


/*****PREDICTION FUNCTIONS MULTIPLE CHOICE*****/


// Main prediction function
d_tree::Label d_tree::compareMultiMain(const Tree& t)
{
	// Preparing couples queue
	Couple couples = setCouples(couples);
	
	// Prediction using couples queue
	return compareMulti(t, couples);
}


// Recoursive prediction using couples
d_tree::Label d_tree::compareMulti(const Tree& t, Couple& c)
{
	// If empty returns emptyLabel
	if(isEmpty(t)) return emptyLabel;
	
	//// If a leaf was found (which is after an edge with the solution), returns edgeLabel
	if(isEmpty(((t->edgeList)->node)->edgeList)) return (t->edgeList)->label;
	
	// If queue is empty before it should has, returns emptyLabel
	if(isEmpty(c)) return emptyLabel;
	
	// Preparing couple
	Couple tmpC = dequeue(c);
	
	// If variable in couple not equal to variable in current node, then returns emptyLabel
	if(normalizeVariable(t->label) != tmpC->variable)
		return emptyLabel;

	// Scrolling
	Edge auxE = t->edgeList;
	Label result = emptyLabel;
	
	while(!isEmpty(auxE))
	{
		if(compareEdge(tmpC->value, auxE))
		{
			result = compareMulti(auxE->node, c);
			auxE = emptyEdge;
		}
		else
			auxE = auxE->nextEdge;
	}
	
	return result;
}


// Adding to couple queue
void d_tree::enqueue(const Label lvariabile, const Label lvalore, Couple& c)
{
	// Preparing couple
	Couple newCouple = new coupleValues;
	newCouple->variable = lvariabile;
	newCouple->value = lvalore;
	newCouple->next = emptyCouple;
	
	// If queue is empty, assigning pointer to new element
	if(isEmpty(c))
	{
		c = newCouple;
		return;
	}
	
	// Scrolling unless arrives to the end, assigning couple
	Couple auxC = c;
	
	while(auxC->next != emptyCouple)
		auxC = auxC->next;
	
	auxC->next = newCouple;
}


// Dequeue from couple queue
d_tree::Couple d_tree::dequeue(Couple& c)
{
	// Creating a copy of couple
	Couple tmp = c;
	
	Couple auxC = new coupleValues;
	auxC->value = tmp->value;
	auxC->variable = tmp->variable;
	auxC->next = emptyCouple;
	
	// Changing pointer to next element of the queue
	c = tmp->next;
	
	// Eliminates couple from queue
	delete tmp;
	
	// Returns copy
	return auxC;
}


// Preparing elements for couple queue
d_tree::Couple d_tree::setCouples(Couple& c)
{
	// Creating empty queue
	c = createEmptyCouple();
	
	// Initializes variable and value labels
	Label lvariabile, lvalore;
	
	// To show how many couples were already inserted
	int num = 1;
	
	do
	{
		cout << "Insert the variable in the couple " << num << " (insert $#$#$ to stop inserting): ";
		cin >> lvariabile;
		
		// If emptyLabel is inserted ($#$#$), the loop will be stopped
		if(lvariabile != emptyLabel)
		{
			cout << "Insert the value in the couple " << num << ": ";
			cin >> lvalore;
			
			removeBlanksAndLower(lvariabile);
			removeBlanksAndLower(lvalore);
			
			enqueue(lvariabile, lvalore, c);
			
			++num;
		}
	}
	while(lvariabile != emptyLabel);
	
	// Returns queue
	return c;
}

// Creating empty queue
d_tree::Couple d_tree::createEmptyCouple()
{
	return emptyCouple;
}

// Returns if queue is empty
bool d_tree::isEmpty(const Couple c)
{
	return (c == emptyCouple);
}


/*****AUX FUNCTIONS FOR PREDICTION TREE (FOR BOTH TYPES OF CHOICES)*****/

// Comparing value inserted by user with value in edge
bool d_tree::compareEdge(Label l, Edge auxE)
{
	// Defining operation in edge
	op operation = opDefinition(auxE->label);
	
	// Isolating edge label without comparison operator
	Label edgeValue = auxE->label.substr(operation.dim, auxE->label.size());
	
	// If label inserted by user is a number, then program goes here...
	if(isNumber(l))
	{
		// Converting user label in a number
		int lInt = stoi(l);
		
		int eInt;
		
		// If edge label is a number too, converts it...
		if(isNumber(edgeValue))
			eInt = stoi(edgeValue);
		else
			return false;	// ... otherwise (if edge label is alphanumeric) returns false (can't compare alphanumeric with numeric label)
		
		// Returns if comparison is succedeed or not
		return(compareInt(operation, lInt, eInt));
	}
	else		// Otherwise if user wrote an alphanumeric label, program enters here
	{
		// If edge label is a number, returns false (can't compare alphanumeric with numeric label)
		if(isNumber(edgeValue))
			return false;
		
		// If operation in edge isn't 'equal' or 'not equal', return false
		if(operation.k != OP_UGUALE && operation.k != OP_DIVERSO)
			return false;
		
		// Returns if compare operation succedes or not
		return((operation.k == OP_UGUALE && !l.compare(edgeValue)) || (operation.k == OP_DIVERSO && l.compare(edgeValue)));
	}
}


// Defining operator in edge
d_tree::op d_tree::opDefinition(const Label a)
{
	// Preparo lo struct per definire il tipo di operazione e la dimensione dell'operatore nella stringa
	op o;
	
	// Choosing correct operation from label a
	switch(a[0]){
		case '!':
			if(a[1] == '=')
			{
				o.dim = 2;
				o.k = OP_DIVERSO;
			}
			else
				throw runtime_error("\nError, character 'not equal' not complete");
				
			break;
		case '=':
			o.dim = 1;
			o.k = OP_UGUALE;
			break;
		case '<':
			if(a[1] == '=')
			{
				o.dim = 2;
				o.k = OP_MINOREUGUALE;
			}
			else
			{
				o.dim = 1;
				o.k = OP_MINORE;
			}
			break;
		case '>':
			if(a[1] == '=')
			{
				o.dim = 2;
				o.k = OP_MAGGIOREUGUALE;
			}
			else
			{
				o.dim = 1;
				o.k = OP_MAGGIORE;
			}
			break;
		default:
			throw runtime_error("\nError - Compare character not found\n");
			break;
	}
	
	// Returns operator definition
	return o;	
}


// Checking if label l is a value or a string
bool d_tree::isNumber(const Label l)
{
	// If one letter is found, l is an alphanumeric string, returns false 
	for(unsigned int i = 0; i < l.size(); ++i)
	{
		if((l[i] >= 'a') && (l[i] <= 'z'))
			return false;
	}

	// No letter was found, l is a number
	return true;
}


// Returns if comparison is true or false
bool d_tree::compareInt(op o, int I1, int I2)
{
	// Analizing operation type and compares labels l1 and l2
	switch(o.k){
		case OP_UGUALE:
			if(I1 == I2)
				return true;
			break;
		case OP_DIVERSO:
			if(I1 != I2)
				return true;
			break;
		case OP_MINOREUGUALE:
			if(I1 <= I2)
				return true;
			break;
		case OP_MINORE:
			if(I1 < I2)
				return true;
			break;
		case OP_MAGGIOREUGUALE:
			if(I1 >= I2)
				return true;
			break;
		case OP_MAGGIORE:
			if(I1 > I2)
				return true;
			break;
		default:
			return false;
	}

	return false;
}


/******************INPUT FROM FILE FUNCTIONS******************/


//Inserimento effettivo
Tree readFromStream(istream& str)
{
	Tree t = d_tree::createEmpty();
	string line;
	Label rootLabel, fatherLabel, childLabel, edgeLabel;
	getline(str, line);
	
	istringstream instream;
	
	//Inserimento radice nell'albero (convenzione: la prima linea rappresenta la radice)
	instream.clear();
	instream.str(line);
	instream >> rootLabel;
	
	//Aggiunta post-correzione
	removeBlanksAndLower(rootLabel);
	
	addElem(emptyLabel, rootLabel, emptyLabelE, t);
	
	//Inserimento altri elementi
	getline(str, line);
	instream.clear();
	instream.str(line);
	while(!str.eof())
	{
		instream >> fatherLabel;
		removeBlanksAndLower(fatherLabel);
		
		while(!instream.eof())
		{
			instream >> childLabel;
			removeBlanksAndLower(childLabel);
			instream >> edgeLabel;
			removeBlanksAndLower(edgeLabel);
			addElem(fatherLabel, childLabel, edgeLabel, t);
		}
		
		getline(str, line);
		instream.clear();
		instream.str(line);
	}
	
	str.clear();
	return t;
}


// Checking if file exists, then this function calls readFromStream to create the tree
Tree readFromFile(string nome_file)
{
	ifstream ifs(nome_file.c_str()); // Opening input file stream
	if(!ifs)
	{
		cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n";
		return d_tree::createEmpty();
	}

	return readFromStream(ifs);
}

