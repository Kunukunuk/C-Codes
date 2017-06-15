#include <iostream>
#include <fstream>

using namespace std;


class listNode{
	friend class linkedlistStack;
	public:
	int data;
	listNode* next;
	
	listNode(){
		data = 0;
		
	}
	
	listNode(int value){
		data = value;
		
	}
	
	~listNode();
};

class linkedlistStack{
	
	public :
	listNode *top;
	linkedlistStack(){
		top = NULL;
	}
	~linkedlistStack(){
		
	}
	void push(int value){
		
		listNode *node = new listNode(value);
		cout<< node->data << " " << node -> next<< endl;
		node -> next = top;
		top = node;
	}
	
	int pop(){
		int temp = top -> data;
		if(top == NULL){
			return 0;
		}
		top = top -> next;
		return temp;
	}
	
	bool isEmpty(){
		if(top == NULL){
			return false;
		}
		return true;
	}
};


int main(int argc, char **argv){
	
	int intItem;
	ifstream inFile;
	linkedlistStack lls;
	inFile.open(argv[1]);
	while(inFile >> intItem){
		lls.push(intItem);
	}
	inFile.close();
	cout<< endl;
	int finish = 1;
	while(finish!=0){
		cout<< lls.pop() <<" "<< endl;
			if(lls.isEmpty()== false){
			finish = 0;
		}
	}
}
