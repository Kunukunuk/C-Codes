#include <iostream>
#include<fstream>

using namespace std;

class stack{
	
	int top;
	int *StackArry;
	public:

	stack(int i);
	~stack();
	int pop();
	void push(int x);
	bool isEmpty();
};

stack::stack(int i){
	top = -1;
	StackArry = new int[i];
}

stack::~stack(){
	delete[] StackArry;
}
void stack::push(int x){
	
	top++;
	StackArry [top] = x;

}

int stack::pop(){
	int i = StackArry[top];
	if(top == -1){
		return 0;
	}
	top--;	
	return i;
	
}

bool stack::isEmpty(){
	
	if(top == -1){
		return true;
	}
	return false;
}

int main(int argc, char **argv) {
	int count = 0;
	ifstream inFile;
	int intItem ;
	inFile.open( argv[1] );
	
	while(inFile >> intItem){
		cout << intItem << " ";
		count++;
	}
	cout<< endl;
	
	inFile.close();
	inFile.open(argv[1]);
	stack sta(count);
	while(inFile >>intItem){
		sta.push(intItem);
	}
	cout<< endl;
	while(!sta.isEmpty()){
		cout<< sta.pop()<< " ";
	}
	inFile.close();
	sta.~stack();
}
