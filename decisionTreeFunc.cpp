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
	
	// Scorrimento
	Edge auxE = t->edgeList;
	
	while(!isEmpty(auxE))
	{
		// Mostro l'etichetta dell'arco e quali nodi collega
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
		{
			cout << "\n - Variabile " << i+1 << ": " << lst.list[i];	//Mostro il contenuto della lista
		}
	
	cout << "\n";
}


// Aux function for printVariables (recoursive)
void d_tree::setVariables(const Tree& t, list::List& lst){
	
	//Se è vuoto, ritorna
	if(isEmpty(t) || (isEmpty(t->edgeList))) return;
	
	//Recupero l'etichetta del nodo senza l'underscore
	Label l = normalizeVariable(t->label);
	
	//Se non c'è un elemento nella lista con quell'etichetta, allora aggiungo nella lista, altrimenti non faccio nulla
	if(!list::findElem(l, lst))
	{
		list::addBack(l, lst);
	}
	
	//Chiamata ricorsiva per esplorare l'albero
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


// Cerco un nodo con un certo label (ricorsivo)
bool d_tree::member(const Label l, const Tree& t){

	//Se l'albero è vuoto restituisco false (non ho trovato il nodo)
	if(isEmpty(t))
		return false;

	//Se trovo un nodo con label l, allora ritorno true
	if(t->label == l)
		return true;
		
	//Punta a scorrere le liste di archi
	Edge aux = t->edgeList;
	
	//Scorrimento finchè non trovo un elemento con quell'etichetta o finchè non arrivo fino alla fine delle chiamate ricorsive
	while(aux != emptyEdge)
	{
		if(!member(l, aux->node))
			aux = aux->nextEdge;
		else
			return true;
	}
	
	return false;
}


//Recupero l'indirizzo del nodo che cerco (ricorsivo, suggerito disegno di un albero di questo tipo per comprendere)
Tree d_tree::getNode(const Label l, const Tree& t){
	
//Versione lista di archi
	
	//Se l'albero è vuoto o l'etichetta è vuota, restituisco un nodo vuoto
	if(isEmpty(t) || l==emptyLabel)
		return emptyTree;
		
	//Se trovo un nodo con l'etichetta l, allora ritorno l'indirizzo del nodo
	if(t->label == l)
		return t;
	
	//Suggerita simulazione con disegno per una comprensione maggiore
	Edge aux = t->edgeList;
	Tree resNode;
	
	while(aux != emptyEdge)
	{
		resNode = getNode(l, aux->node);
		if(resNode == emptyTree)
			aux = aux->nextEdge;
		else
			return resNode;						//Resistuisco il nodo nel caso lo trovo, riavvolgendo tutte le chiamate ricorsive
	}
	
	// Ho esaurito la lista degli archi, torno indietro di una ricorsione
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
		
		// Slides on all l's children
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
		case '!':							//Diverso
			if(edgeLabel[1] == '=')
				break;
			else
				return false;				// Not found
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


// Ricorsiva (versione scelta una alla volta)
d_tree::Label d_tree::compareMono(const Tree& t)
{
	//Se è vuoto ritorno emptyLabel
	if(isEmpty(t)) return emptyLabel;
	
	//Se viene trovato un nodo foglia, allora ritorno l'etichetta dell'arco
	if(isEmpty(((t->edgeList)->node)->edgeList)) return (t->edgeList)->label;
	
	//Viene scelta l'etichetta dall'utente
	Label l = userChoice(t);
	
	//Scorrimento nell'albero
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


//Ausiliaria, usata per far scegliere all'utente una stringa
d_tree::Label d_tree::userChoice(const Tree& t)
{	
	//Scorrimento nella lista degli archi
	Edge tmp = t->edgeList;

	//Mostra le possibili variabili
	cout << "\n - Tipo: " << t->label << " - Le possibili decisioni sono:\n";
	while(!isEmpty(tmp)){
		cout << " - " << tmp->label << "\n";
		tmp = tmp->nextEdge;
	}
	cout << "\n";
	
	//Inserimento
	cout << "Inserisci il valore/la stringa: ";
	Label aux;
	cin >> aux;
	removeBlanksAndLower(aux);
	
	return aux;
}


/*****PREDICTION FUNCTIONS MULTIPLE CHOICE*****/


//Funzione principale per la predizione
d_tree::Label d_tree::compareMultiMain(const Tree& t)
{
	//Preparazione coda insieme di coppie
	Couple couples = setCouples(couples);
	
	//Predizione usando coda insieme di coppie
	return compareMulti(t, couples);
}


//Predizione ricorsiva con insiemi di coppie
d_tree::Label d_tree::compareMulti(const Tree& t, Couple& c)
{
	//Se è vuoto, allora ritorno emptyLabel
	if(isEmpty(t)) return emptyLabel;
	
	////Se viene trovato un nodo foglia (che precede l'arco con la soluzione della predizione), allora ritorno l'etichetta dell'arco
	if(isEmpty(((t->edgeList)->node)->edgeList)) return (t->edgeList)->label;
	
	//Se la coda si svuota prima del dovuto, allora ritorno emptyLabel
	if(isEmpty(c)) return emptyLabel;
	
	//Preparo la coppia
	Couple tmpC = dequeue(c);
	
	//Se la variabile nella coppia non è uguale alla variabile del nodo corrente, allora ritorno emptyLabel
	if(normalizeVariable(t->label) != tmpC->variable)
		return emptyLabel;

	//Scorrimento
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


//Aggiunta nella coda degli insiemi di coppie
void d_tree::enqueue(const Label lvariabile, const Label lvalore, Couple& c)
{
	//Preparazione Coppia
	Couple newCouple = new coupleValues;
	newCouple->variable = lvariabile;
	newCouple->value = lvalore;
	newCouple->next = emptyCouple;
	
	//Se la coda è vuota, assegno il puntatore al nuovo elemento
	if(isEmpty(c))
	{
		c = newCouple;
		return;
	}
	
	//Scorro finchè non arrivo in fondo ed assegno la coppia al suo posto
	Couple auxC = c;
	
	while(auxC->next != emptyCouple)
		auxC = auxC->next;
	
	auxC->next = newCouple;
}


//Eliminazione nella coda degli insiemi di coppie
d_tree::Couple d_tree::dequeue(Couple& c)
{
	//Creo una copia della coppia
	Couple tmp = c;
	
	Couple auxC = new coupleValues;
	auxC->value = tmp->value;
	auxC->variable = tmp->variable;
	auxC->next = emptyCouple;
	
	//Sposto il puntatote della coda al prossimo elemento
	c = tmp->next;
	
	//Elimino la coppia dalla coda
	delete tmp;
	
	//Ritorno la copia
	return auxC;
}


//Preparazione elementi coda insiemi di coppie
d_tree::Couple d_tree::setCouples(Couple& c)
{
	//Creo la coda vuota
	c = createEmptyCouple();
	
	//Preparo le etichette della variabile e del valore
	Label lvariabile, lvalore;
	
	//Per mostrare quante coppie sono già state inserite
	int num = 1;
	
	do
	{
		cout << "Inserisci la variabile della coppia " << num << " (inserire $#$#$ per terminare l'inserimento): ";
		cin >> lvariabile;
		
		//Se viene inserito il valore corrispondente a emptyLabel ($#$#$) significa che ho terminato l'inserimento
		if(lvariabile != emptyLabel)
		{
			cout << "Inserisci il valore della coppia " << num << ": ";
			cin >> lvalore;
			
			removeBlanksAndLower(lvariabile);
			removeBlanksAndLower(lvalore);
			
			enqueue(lvariabile, lvalore, c);
			
			++num;
		}
	}
	while(lvariabile != emptyLabel);
	
	//Ritorno la coda
	return c;
}


//Creazione coda vuota
d_tree::Couple d_tree::createEmptyCouple()
{
	return emptyCouple;
}


//Ritorna se la coda è vuota o menoero di decisione così come descritto sopra e modificarlo con le operazioni
bool d_tree::isEmpty(const Couple c)
{
	return (c == emptyCouple);
}


/*****AUX FUNCTIONS FOR PREDICTION TREE (FOR BOTH TYPES OF CHOICES)*****/


//Comparazione valore inserito dall'utente e valore nell'arco
bool d_tree::compareEdge(Label l, Edge auxE)
{
	//Definisco l'operazione contenuta nell'arco
	op operation = opDefinition(auxE->label);
	
	//Isolo l'etichetta nell'arco senza l'operatore di confronto
	Label edgeValue = auxE->label.substr(operation.dim, auxE->label.size());
	
	//Se l'etichetta che ha inserito l'utente è un numero allora entro qui...
	if(isNumber(l))
	{
		//Converto l'etichetta dell'utente in un numero
		int lInt = stoi(l);
		
		int eInt;
		
		//Se anche l'etichetta dell'arco è un numero, converto l'etichetta dell'arco...
		if(isNumber(edgeValue))
			eInt = stoi(edgeValue);
		else
			return false;	//Nel caso l'etichetta dell'arco sia alfanumerica (non posso confrontare un numero con una stringa alfanumerica) ritorno false
		
		//Ritorno se il confronto ha successo o meno
		return(compareInt(operation, lInt, eInt));
	}
	else		//Altrimenti se l'utente ha scritto un'etichetta alfanumerica entro qui
	{
		//Se l'etichetta nell'arco è un numero (non posso confrontare una stringa alfanumerica con un numero), ritorno false
		if(isNumber(edgeValue))
			return false;
		
		//Se l'operazione contenuta nell'arco è diversa da 'uguale' o 'diverso', ritorno false
		if(operation.k != OP_UGUALE && operation.k != OP_DIVERSO)
			return false;
		
		//Ritorno se il confronto ha successo o meno
		return((operation.k == OP_UGUALE && !l.compare(edgeValue)) || (operation.k == OP_DIVERSO && l.compare(edgeValue)));
	}
}


//Definizione operatore nell'arco
d_tree::op d_tree::opDefinition(const Label a)
{
	//Preparo lo struct per definire il tipo di operazione e la dimensione dell'operatore nella stringa
	op o;
	
	//A seconda del caso definisco in modo diverso l'operazione
	switch(a[0]){
		case '!':
			if(a[1] == '=')
			{
				o.dim = 2;
				o.k = OP_DIVERSO;
			}
			else
				throw runtime_error("\nErrore - Carattere 'diverso' incompleto");
				
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
			throw runtime_error("\nErrore - Carattere di comparazione non trovato in un arco\n");
			break;
	}
	
	//Ritorno la definizione dell'operatore
	return o;	
}


//Comprensione se la stringa inserita è un valore o una stringa
bool d_tree::isNumber(const Label l)
{
	//Se trovo anche solo una lettera nella stringa, significa che è una stringa alfanumerica, e non un numero 
	//(Aggiunta post-correzione)
	for(unsigned int i = 0; i < l.size(); ++i)
	{
		if((l[i] >= 'a') && (l[i] <= 'z'))
			return false;
	}

	//Non è stata trovata nessuna lettera nella stringa inserita, quindi è un numero
	return true;
}


//Ritorno se il confronto è vero o falso
bool d_tree::compareInt(op o, int I1, int I2)
{
	//Si analizza il tipo di operazione e si confrontano in maniera adeguata le etichette
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

