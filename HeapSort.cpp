#include <iostream>
#include <fstream>

using namespace std;

class HeapSort{
	int intItem;
	int *heapAry, count = 2, size;
	public :
	HeapSort(int arySize){
		size = arySize+1;
		heapAry = new int[size];
		heapAry[0] = 0;
		
	}
	~HeapSort(){
		delete []heapAry;
	}
	void buildHeap(char *data,ofstream &outFile){
		ifstream inFile(data);
		while(inFile >> intItem){
			if(isHeapFull()){
				outFile << " FULL " << endl;
			}
			outFile << "Inserting this number: " << intItem << endl;
			insertOneDataItem(intItem);
			printHeap(outFile);
		}
		inFile.close();
	}
	void deleteHeap(ofstream &outFile){
		while(!isHeapEmpty()){
		deleteRoot(outFile);
		bubbleDown();
		printHeap(outFile);
		}
		
	}
	void insertOneDataItem(int value){
	
		if(isHeapEmpty()){
			heapAry[1] = value;
			heapAry[0]++;
		}
		else if(isHeapFull()){
			
		}
		else{
			heapAry[count] = value;
			count++;
			heapAry[0]++;
			bubbleUp();
		}
	}
	void deleteRoot(ofstream &outFile){
		
		outFile << "Deleting the root : "<< heapAry[1] << endl;
		int last = heapAry[0];
		heapAry[1] = heapAry[last];
		heapAry[0]--;
	}
	void bubbleUp(){
		
		for(int last = heapAry[0]; last>= 1; last-=2){
			 if(heapAry[last]< heapAry[last/2] && last != 1){
				int temp = heapAry[last];
				heapAry[last] = heapAry[last/2];
				heapAry[last/2] = temp;
			}
		}
	}
	void bubbleDown(){
		
		
		int parent = 1;
		int lkid = parent*2;
		int rkid = parent*2+1;
		while(heapAry[parent] > heapAry[lkid] || heapAry[parent] > heapAry[rkid] ){
			if(lkid < rkid && lkid < heapAry[parent] ){
				int temp = heapAry[parent];
				heapAry[parent] = heapAry[lkid];
				heapAry[lkid] = temp;
				parent = lkid;
				lkid = 2*parent;
				rkid = lkid+1;
			}
			else if(rkid < lkid && rkid < heapAry[parent]){
				int temp = heapAry[parent];
				heapAry[parent] = heapAry[rkid];
				heapAry[rkid] = temp;
				parent = rkid;
				lkid = 2*parent;
				rkid = lkid+1;
			}
	 }
	}
	bool isHeapEmpty(){
		if(heapAry[0] == 0){
			return true;
		}
		return false;
		
	}
	bool isHeapFull(){
		if(heapAry[0] == size ){
			return true;
		}
		return false;
	}
	void printHeap(ofstream &outFile){
		outFile << "this is the first 10 items: " << endl; 
		for(int i = 1; i< 10; i++){
			outFile <<heapAry[i] << endl;
		}
	}
};

int main(int argc, char **argv){
	
	ifstream inFile;
	ofstream outFile;
	int data, count;
	inFile.open(argv[1]);
	outFile.open(argv[2]);
	while(inFile >> data){
		count++;
	}
	inFile.close();
	HeapSort heap(count);
	heap.buildHeap(argv[1], outFile);
	heap.deleteHeap(outFile);
	outFile.close();
	
}
