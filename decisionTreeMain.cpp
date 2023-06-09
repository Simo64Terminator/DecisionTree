#include "decisionTree.h"

using namespace d_tree;

int main(){

	const string menu = "-------------------------------------------------------------------\n\t\t\t\tMENU\n-------------------------------------------------------------------\n1. Read decision tree from file\n2. Insert a labeled node childNode, attached to a node fatherName using an edge edgeLabel\n3. Delete a node\n4. Edit a node\n5. Print current decision tree\n6. Print variables in current tree\n7. Start prediction by inserting values one at a time\n8. Start prediction by inserting all values from start\n0. Exit\n\nChoose ---> ";

	// Defining interface variables (ch = menu | l1,l2,la = fatherLabel,childLabel,edgeLabel | ld = delete | le1,le2 = edit | file_name = name of .txt file used | lp = preditionLabel)
	choice ch;
	Label l1, l2, la, ld, le1, le2, lp;
	string file_name;

	// Shows Menu
	cout << endl << menu;
	cin >> ch;
	
	// Initialize empty tree
	Tree tree = d_tree::createEmpty();
	
	while(ch != 0){
		switch(ch){
			case 1:
				// Reading tree from file
				
				cout << "\nInsert file name (.txt file requested): ";
				cin >> file_name;
				tree = readFromFile(file_name);
				if(!isEmpty(tree))
					cout << "\nSuccess\n";
				else
					cout << "\nFailure\n";
				cout << "\n";
				break;
				
			case 2:
				// Insert a labeled node called childNode attached to a father node called fatherNode, by using a labeled edge called edgeLabel
				
				cout << "\nInsert fatherLabel name (if tree is empty, insert $#$#$): ";
				cin >> l1;
				cout << "\nInsert childLabel to be attached to " << l1 << ": ";
				cin >> l2;
				if(!isEmpty(tree))
				{
					cout << "\nInsert label to be assigned to the edgeInserisci l'etichetta da assegnare all'arco: ";
					cin >> la;
				}
				else
					la = "----";
				
				if(!cin)
				{
					cout << "Failure in inserting data\n";
					break;
				}
				
				removeBlanksAndLower(la);
				removeBlanksAndLower(l1);
				removeBlanksAndLower(l2);
				
				if(addElem(l1, l2, la, tree) == FAIL)
					cout << "\nFailure! (inserting error)\n";
				else
					cout << "\nSuccess!\n";
				
				cout << "\n";
				break;
			
			case 3:
				// Deleting a node
			
				cout << "\nInsert name of node to be deleted: ";
				cin >> ld;
				
				if(!cin)
				{
					cout << "Error in inserting data\n";
					break;
				}
				
				removeBlanksAndLower(ld);
				
				if(deleteElem(ld, tree) == FAIL)
					cout << "\nFailure! (deleting error)\n";
				else
					cout << "\nSuccess!\n";
				
				cout << "\n";
				break;
			
			case 4:
				// Editing node
				
				cout << "\nInsert node name to be edited: ";
				cin >> le1;
				cout << "\nInsert new label to be assigned: ";
				cin >> le2;
				
				if(!cin)
				{
					cout << "Error in inserting data\n";
					break;
				}
				
				removeBlanksAndLower(le1);
				removeBlanksAndLower(le2);
				
				if(editElem(le1, le2, tree) == FAIL)
					cout << "\nFailure! (editing error)\n";
				else
					cout << "\nSuccess!\n";
				
				cout << "\n";
				break;
			
			case 5:
				// Printing decision tree
			
				cout << "\n";
				printTree(tree);
				cout << "\n";
				break;
			
			case 6:
				// Printing variables only
				
				printVariables(tree);
				cout << "\n";
				break;
			
			case 7:
				// Predict by inserting one value at a time
			
				lp = compareMono(tree);
					
				if(lp == emptyLabel)
					cout << "\nFailure! (There's no valid path)\n";
				else
				{
					lp = normalizeValue(lp);
					cout << "\nFinal prediction is: " << lp << "\n";
				}
				
				cout << "\n";
				break;
			
			case 8:
				// Predict by inserting all values
				
				lp = compareMultiMain(tree);
				
				if(lp == emptyLabel)
					cout << "\nFailure! (There's no valid path)\n";
				else
				{
					lp = normalizeValue(lp);
					cout << "\nFinal prediction is: " << lp << "\n";
				}
				
				cout << "\n";
				break;
				
			default:
				cout << "\nInvalid character!\n\n";
		}
		
		cout << menu;
		cin >> ch;
	}

	return 0;
}
