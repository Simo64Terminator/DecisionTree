#include "decisionTree.h"

using namespace d_tree;

int main(){

	const string menu = "-------------------------------------------------------------------\n\t\t\t\tMENU\n-------------------------------------------------------------------\n1. Lettura albero di decisione da file\n2. Inserimento di un nodo etichettato childNode attaccato, usando un arco etichettato edgeLabel, ad un padre etichettato fatherNode\n3. Cancellazione di un nodo dall'albero\n4. Modifica di un nodo dall'albero\n5. Visualizzazione albero di decisione\n6. Stampa variabili dell'albero di decisione\n7. Effettua predizione inserendo i valori uno alla volta\n8. Effettua predizione inserendo tutti i valori all'inizio\n0. Uscita\n\nFornisci la tua scelta ---> ";

	//Definizione variabili interfaccia (ch = menu, l1,l2,la = labelPadre/labelFiglio/labelEdge, ld = delete, le1,le2 = edit, nome_file = nome del .txt usato, lp = labelPrediction)
	choice ch;
	Label l1, l2, la, ld, le1, le2, lp;
	string nome_file;

	//Mostra Menu
	cout << endl << menu;
	cin >> ch;
	
	//Prepara l'albero vuoto
	Tree tree = d_tree::createEmpty();
	
	while(ch != 0){
		switch(ch){
			case 1:
				//Lettura albero da file
				
				cout << "\nInserisci nome file (richiesto un file di tipo .txt): ";
				cin >> nome_file;
				tree = readFromFile(nome_file);
				if(!isEmpty(tree))
					cout << "\nOperazione completata\n";
				else
					cout << "\nOperazione fallita\n";
				cout << "\n";
				break;
				
			case 2:
				//Inserimento di un nodo etichettato childNode attaccato usando un arco etichettato edgeLabel ad un padre etichettato fatherNode
				
				cout << "\nInserisci il nome del labelPadre (se l'albero è vuoto inserire $#$#$): ";
				cin >> l1;
				cout << "\nInserisci il nome del labelFiglio da attaccare a " << l1 << ": ";
				cin >> l2;
				if(!isEmpty(tree))
				{
					cout << "\nInserisci l'etichetta da assegnare all'arco: ";
					cin >> la;
				}
				else
					la = "----";
				
				if(!cin)
				{
					cout << "Errore inserimento dati\n";
					break;
				}
				
				removeBlanksAndLower(la);
				removeBlanksAndLower(l1);
				removeBlanksAndLower(l2);
				if(addElem(l1, l2, la, tree) == FAIL){
					cout << "\nErrore nell'inserimento, operazione annullata\n";
				}
				else{
					cout << "\nOperazione avvenuta con successo!\n";
				}
				cout << "\n";
				break;
			
			case 3:
				//Cancellazione di un nodo dall'albero
			
				cout << "\nInserisci il nome del nodo da eliminare: ";
				cin >> ld;
				
				if(!cin)
				{
					cout << "Errore inserimento dati\n";
					break;
				}
				
				removeBlanksAndLower(ld);
				if(deleteElem(ld, tree) == FAIL){
					cout << "\nErrore nell'eliminazione, operazione annullata\n";
				}
				else{
					cout << "\nOperazione avvenuta con successo!\n";
				}
				cout << "\n";
				break;
			
			case 4:
				//Modifica di un nodo dall'albero
				
				cout << "\nInserisci il nome del nodo da modificare: ";
				cin >> le1;
				cout << "\nInserisci la nuova etichetta da assegnare: ";
				cin >> le2;
				
				if(!cin)
				{
					cout << "Errore inserimento dati\n";
					break;
				}
				
				removeBlanksAndLower(le1);
				removeBlanksAndLower(le2);
				if(editElem(le1, le2, tree) == FAIL)
					cout << "\nErrore nella modifica, operazione annullata\n";
				else
					cout << "\nOperazione avvenuta con successo!\n";
				cout << "\n";
				break;
			
			case 5:
				//Visualizzazione albero di decisione
			
				cout << "\n";
				printTree(tree);
				cout << "\n";
				break;
			
			case 6:
				//Stampa variabili dell'albero di decisione
				
				printVariables(tree);
				cout << "\n";
				break;
			
			case 7:
				//Effettua predizione inserendo i valori uno alla volta
			
				lp = compareMono(tree);
					
				if(lp == emptyLabel)
					cout << "\nLa predizione non può avere luogo in quanto esiste un nodo per il quale non c'è un arco percorribile\n";
				else
				{
					lp = normalizeValue(lp);
					cout << "\nLa predizione finale è: " << lp << "\n";
				}
				
				cout << "\n";
				break;
			
			case 8:
				//Effettua predizione inserendo tutti i valori
				
				lp = compareMultiMain(tree);
				
				if(lp == emptyLabel)
					cout << "\nLa predizione non può avere luogo in quanto esiste un nodo per il quale non c'è un arco percorribile\n";
				else
				{
					lp = normalizeValue(lp);
					cout << "\nLa predizione finale è: " << lp << "\n";
				}
				
				cout << "\n";
				break;
				
			default:
				cout << "\nHai scelto un carattere invalido\n\n";
				
		}
		
		cout << menu;
		cin >> ch;
	}

	return 0;
}
