#include <iostream>
#include <fstream>

using namespace std;

class listBinTreeNode {
	friend class HuffmanLinkedList;
	public:
	string chStr;
	int prob;
	listBinTreeNode *next = NULL;
	listBinTreeNode *left = NULL;
	listBinTreeNode *right = NULL;
	public:
	listBinTreeNode(int pro, string chac){
		prob = pro;
		chStr = chac;
	}
	
	listBinTreeNode(){
		prob = 0;
		chStr = "dummy";
	}
	
	~listBinTreeNode(){
		delete next;
		//delete left;
		//delete right;
		
	}
	
	string printNode(listBinTreeNode *T){
		string node;
		if( T -> next == NULL){
			node =  node + T -> chStr + ", "+ to_string(T -> prob) + ", "+ "NULL" + ", "+T -> left -> chStr +", " +T -> right -> chStr + "\n";
			
		}
		else if( T -> left == NULL || T -> right ==NULL){
			node = node + T -> chStr + ", "+ to_string(T -> prob) + ", "+ T -> next -> chStr + ", "+"NULL" +", " + "NULL" + "\n";
		}
		else{
			node = node + T -> chStr + ", "+ to_string(T -> prob) + ", "+ T -> next -> chStr + ", "+T -> left -> chStr +", " +T -> right -> chStr + "\n";
		}
		return node;
	}
};

class HuffmanLinkedList{
	public:
	listBinTreeNode *listHead;
	listBinTreeNode *oldListHead;
	public:
	HuffmanLinkedList(){
		listBinTreeNode *dummy = new listBinTreeNode();
		dummy -> next = NULL;
		listHead = dummy;
	}
	
	void listInsert(listBinTreeNode* T){
		listBinTreeNode* temp = findSpot(T -> prob);
		T -> next = temp -> next;
		temp -> next = T;
		
	}
	
	listBinTreeNode* findSpot(int number){
		listBinTreeNode* spot = listHead;
		while( spot -> next != NULL && spot -> next -> prob < number){
			spot = spot -> next;
		}
		return spot;
	}
	
	string printList(){
		string list;
		if(isEmpty()){
			list = "listHead -->(" + listHead -> chStr + ", " + to_string(listHead -> prob) + ", NULL )--> NULL\n"; 
		}else{
		list = "listHead -->(" + listHead -> chStr + ", " + to_string(listHead -> prob) + ", " + listHead -> next -> chStr +")-->";
		listBinTreeNode* current = listHead;
		while(current -> next -> next != NULL){
			list = list + "(" + current -> next -> chStr +", " + to_string(current -> next -> prob) + ", " + current -> next -> next -> chStr + ")-->";
			current = current -> next;
		}
		list = list + "(" + current -> next -> chStr + ", " + to_string(current-> next -> prob) + ", " + "NULL"+ ")-->" +"NULL\n";
		}
		return list;
	}
	
	bool isEmpty(){
		if(listHead -> next == NULL){
			return true;
		}
		return false;
	}
	
};

class HuffmanBinaryTree{
	string chStr;
	int prob;
	string code;
	listBinTreeNode *root;
	public:
	void preOrderTraversal(listBinTreeNode *T, ofstream &outfile){
		
		if(T == NULL){
			return;
		}
		else{
			outfile << T -> printNode(T),
			preOrderTraversal( T -> left, outfile),
			preOrderTraversal( T -> right, outfile);
		}
		
	}
	
	HuffmanBinaryTree(listBinTreeNode* T, ofstream &outfile1, ofstream &outfile2){
		root = T;
		constructCharCode(root, code, outfile1);
		preOrderTraversal(root, outfile2);
	}
	
	~HuffmanBinaryTree(){
		delete root;
	}
	
	void constructCharCode(listBinTreeNode *T, string code, ofstream &outfile){
		
		if(T == NULL){
			return;
		}
		else if( T -> left ==NULL || T -> right == NULL){
			outfile << T ->  chStr << " ";
			outfile << code << endl;
		}
		else{
		constructCharCode( T -> left, code+"0", outfile),
		constructCharCode( T -> right, code+"1", outfile);
		}
	}
};

	int main(int argc, char **argv){
		
		ifstream inFile;
		ofstream outfile1, outfile2, outfile3;
		int data;
		string character;
		inFile.open(argv[1]);
		outfile1.open(argv[2]);
		outfile2.open(argv[3]);
		outfile3.open(argv[4]);
		HuffmanLinkedList list;
		while( inFile >> character >> data){
			
			listBinTreeNode* newNode = new listBinTreeNode(data, character);
			list.listInsert(newNode);
			outfile3 << list.printList();
		}
		inFile.close();
		outfile3 << "End of construction of ordered linked list.\n";
		outfile3 << "CurrentchStr, currrentprob, nextchStr, leftchStr, rightchStr\n";
		
		list.oldListHead = new listBinTreeNode();
		list.oldListHead -> next = list.listHead -> next;
		list.listHead = list.listHead -> next;
		int sumprob;
		string concatchar;
		while(!list.isEmpty()){
		sumprob = list.listHead -> prob + list.listHead -> next -> prob;
		concatchar = list.listHead -> chStr + list.listHead -> next -> chStr;
		listBinTreeNode* newNode = new listBinTreeNode(sumprob, concatchar);
		newNode -> left = list.listHead ;
		newNode -> right = list.listHead -> next;
		list.listInsert(newNode);
		list.listHead = list.listHead -> next -> next;

		outfile3 << list.listHead -> printNode(newNode);
		outfile3 << list.printList();
	
		}
		outfile2 << "CurrentchStr, currrentprob, nextchStr, leftchStr, rightchStr\n";
		HuffmanBinaryTree tree(list.listHead, outfile1, outfile2);
		
		outfile1.close();
		outfile2.close();
		outfile3.close();
	}
