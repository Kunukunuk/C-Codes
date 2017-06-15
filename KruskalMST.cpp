#include <iostream>
#include <fstream>

using namespace std;
//Did not need to use it
/*class graphNode{
	int nodeID;
	graphNode * next;
	
	graphNode(int nID){
		nodeID = nID;
		next = NULL;
	}
	
	~graphNode(){
		delete next;
	}
	
	void insert(){
		
	}
	
	void Delete(){
		
	}
};*/

class undirectedEdge{
	public:
	int Ni,Nj,edgeCost;
	undirectedEdge* next;
	
	string printEdge(undirectedEdge * edge){
		string line = "";
		line = line + "Dummy Node:";
		while(edge -> next != NULL){
			line = line + "From node " + to_string(edge -> Ni) + " to " +  to_string(edge -> Nj) + " edgeCost: " + to_string(edge -> edgeCost) + "\n";
			edge = edge -> next;
		}
		line = line + "From node " + to_string(edge -> Ni) + " to " +  to_string(edge -> Nj) + " edgeCost: " + to_string(edge -> edgeCost) + "\n";
		return line;	
		
	}
	
	undirectedEdge(int ni, int nj, int cost){
		Ni = ni;
		Nj = nj;
		edgeCost = cost;
		next = NULL;
	}
	
	~undirectedEdge(){
		delete next;
	}
	
	undirectedEdge* findSpot(undirectedEdge * LH, int cost){
		undirectedEdge* spot = LH;
		while( spot -> next != NULL && spot -> next -> edgeCost < cost){
			spot = spot -> next;
		}
		return spot;
	}
	
	void insert(undirectedEdge* LH,undirectedEdge* edge){
		undirectedEdge* temp = findSpot(LH, edge -> edgeCost);
		edge -> next = temp -> next;
		temp -> next = edge;
	}
	
	void Delete(undirectedEdge* LH,undirectedEdge* edge){
		undirectedEdge* temp = findSpot(LH, edge -> edgeCost);
		temp -> next = temp -> next -> next;
	}
};

class KruskalMST{
	int numNodes, numSets, totalCost;
	int* inWhichSet;
	undirectedEdge* edgeListHead;
	undirectedEdge* MSTofG;
	public:
	string printList(undirectedEdge* List){
		string line = "";
		line = line + "Dummy Node: ";
		while(List -> next != NULL){
			line = line + "From node " + to_string(List -> Ni) + " to " +  to_string(List -> Nj) + " cost: " + to_string(List -> edgeCost) + "\n";
			List = List -> next;
		}
		line = line + "From node " + to_string(List -> Ni) + " to " +  to_string(List -> Nj) + " cost: " + to_string(List -> edgeCost) + "\n";
		line = line + "The total cost of the MST is: " + to_string(totalCost) + "\n"; 
		return line;
	}
	
	void mergeTwoSets( int ni, int nj){
		int min, max;
	
		if( inWhichSet[ni] <= inWhichSet[nj]){
			min = inWhichSet[ni];
			max = inWhichSet[nj];
		}else{
			min = inWhichSet[nj];
			max = inWhichSet[ni];
		}
		int index = min;
		while(index <= numNodes){
			if(inWhichSet[index]== max){
				inWhichSet[index] = min;	
			}
			index++;
		}
	}
	
	KruskalMST(char* input, char* output1, char* output2){
		
		undirectedEdge* dummy = new undirectedEdge(0, 0, 0);
		dummy -> next = NULL;
		edgeListHead = dummy;
		undirectedEdge* dum = new undirectedEdge(0, 0, 0);
		dum -> next = NULL;
		MSTofG = dum;
		int node1, node2, cost;
		ifstream inFile;
		ofstream outFile1, outFile2;
		inFile.open(input);
		outFile1.open(output1);
		outFile2.open(output2);
		inFile >> numNodes;
		numSets = numNodes;
		totalCost =0;
		inWhichSet = new int[numNodes +1];
		for(int i =1; i<=numNodes; i++){
			inWhichSet[i] = i;
		}
		while(inFile >> node1 >> node2 >> cost){
			undirectedEdge* newEdge = new undirectedEdge(node1, node2, cost);
			edgeListHead -> insert(edgeListHead, newEdge);
		}
		
		inFile.close();
		outFile2 << edgeListHead -> printEdge(edgeListHead);
		while(numSets >1){
		undirectedEdge* minEdge = edgeListHead -> next;
		edgeListHead -> Delete(edgeListHead, minEdge);
		if(inWhichSet[minEdge -> Ni] == inWhichSet[minEdge -> Nj]){
			
		}else{

		MSTofG -> insert(MSTofG, minEdge);
		totalCost = totalCost + minEdge -> edgeCost;
		mergeTwoSets(minEdge -> Ni, minEdge -> Nj);
		numSets--;
		outFile2 << printList(MSTofG);
		}
		for(int i= 1; i< numNodes+1; i++){
		outFile2 << "inwhichset array of " << i << " is "<< inWhichSet[i] << endl;
		}
		}
		
		outFile1 << printList(MSTofG);
		outFile1.close();
		outFile2.close();
	}
};

int main(int argc, char ** argv){
	
	KruskalMST mst(argv[1], argv[2], argv[3]);
	
}
