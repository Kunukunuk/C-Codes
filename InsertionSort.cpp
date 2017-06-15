#include <iostream>
#include <fstream>

using namespace std;

class listNode{
	friend class linkedList;
	public:
	int data;
	listNode* next;
	
	listNode(){
		data = -9999;
	
	}
	
	listNode(int value){
		data = value;
	}
	
	~listNode(){
		while(next != NULL){
			delete next;
		}
	}
};

class linkedList{
	listNode* listHead;
	public :
	linkedList(){
		listNode *dummy = new listNode();
		dummy -> next = NULL;
		listHead = dummy; 
	}
	
	bool isEmpty(){
		if(listHead -> next == NULL){
			return true;
		}
		return false;
	}
	
	void listInsert(int value){
		listNode *temp = findSpot(value);
		listNode *newnode = new listNode(value);
		newnode -> next =  temp -> next;
		temp -> next = newnode;
		
	}
	
	void listDelete(int value){
		
	}
	
	listNode* findSpot(int value){
		listNode* spot = listHead;
		while((spot -> next != NULL) && (spot -> next->data <= value)){
			spot = spot -> next;
		}
		return spot;
	}
	
	string printList(int value){
		string line;
		listNode *current = listHead -> next;
		line = "Insert data " + to_string(value) + ": ("  + to_string(listHead -> data) + ", " + to_string(current -> data) + ") -->";
		
		while(current -> next != NULL){
			line = line + "(" + to_string(current -> data) + ", " + to_string(current -> next -> data) + ") --> " ; 
			current = current -> next;
		}
		line = line + "(" + to_string(current -> data) + ", -1)\n";
		return line;
	}
};

 int main (int argc, char **argv){
 	int intItem;
 	ifstream inFile;
 	ofstream outFile;
 	inFile.open(argv[1]);
	outFile.open(argv[2]);
 	linkedList lls;
 	while(inFile >> intItem){
 		
 		if(lls.findSpot(intItem) -> data == intItem){
 			outFile << "Insert Data " << intItem << ": " << intItem << " is already in the list."<< endl;
		}
		else{
		lls.listInsert(intItem);
		outFile << lls.printList(intItem);
		}

	 }
	 inFile.close();
	 outFile.close();
 }
