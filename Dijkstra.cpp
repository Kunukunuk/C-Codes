#include <iostream>
#include <fstream>

using namespace std;

class DijkstraSSS{
	int numNodes, sourceNode, minNode, currentNode, newCost;
	int** costMatrix;
	int* fatherAry;
	int* markedAry;
	int* bestCostAry;
	public:
	void loadCostMatrix(ifstream & inFile, char *input){
		int fromNode, toNode, cost;
		while(inFile >> fromNode>> toNode>> cost){
			for(int i =1; i<= numNodes; i++){
				for(int j = 1; j <= numNodes; j++){
					if(i == fromNode && j == toNode){
						costMatrix[i][j] = cost;
					}
				}
			}
		}
		
	}
	
	void loadBestCostAry(int sourceNode){
		for(int i =1; i<=numNodes; i++){
			bestCostAry[i] = costMatrix[sourceNode][i];	
		}
	}
	
	void loadFatherAry(int sourceNode){
		for(int i = 1; i<= numNodes; i++){
			fatherAry[i] = sourceNode;
		}
		
	}
	
	void loadMarkedAry(){
		
		for(int i = 1; i<= numNodes; i++){
			markedAry[i] = 0;
		}
		
	}
	
	int computeCost(int min, int current){
		int newcost;
		newcost = bestCostAry[min] + costMatrix[min][current];
		return newcost; 
	}
	
	void markMinNode(int min){
		markedAry[min] = min;
	}
	
	void changeFather(int node, int minNode){
		fatherAry[node] = minNode;
	}
	
	void changeCost(int node, int newCost){
		bestCostAry[node] = newCost;
	}
	
	string debugPrint(){
		string line = "";
		line = line + "The source Node is: " + to_string(sourceNode) + "\n";
		line = line + "The father Array is:";
		for(int i =1 ; i <= numNodes; i++){
			line = line + to_string(fatherAry[i]) + ", ";
		}
		line = line + "\n";
		line = line + "The bestCostAry is: ";
		for(int i =1 ; i <= numNodes; i++){
			line = line + to_string(bestCostAry[i]) + ", ";
		}
		line = line + "\n";
		line = line + "The markedAry is: ";
		for(int i =1 ; i <= numNodes; i++){
			line = line + to_string(markedAry[i]) + ", ";
		}
		line = line + "\n";
		return line;
	}
	
	string printShortestPath(int source){
		string line = "";
		line = line + "====================================================================\n";
		line = line + "Source node = " + to_string(source) + "\n";
		line = line + "The shortest paths from node " + to_string(source) +  " are:\n";
		for(int i =1; i<= numNodes; i++){
			line = line + "The path from " + to_string(source) + " to " + to_string(i) + " : ";
			line = line + to_string(source) + "-->" + to_string(i) + " : cost = "  + to_string(bestCostAry[i]) + "\n";
		}
		return line;
	}
	
	bool allMarked(){
		for(int i =1; i <= numNodes; i++){
			if(markedAry[i] == 0){
				return false;
			}
		}
		return true;
	}
	
	DijkstraSSS(char* input, char* output1, char* output2){
		ifstream inFile;
		inFile.open(input);
		ofstream outfile1, outfile2;
		outfile1.open(output1);
		outfile2.open(output2);
		inFile >> numNodes;
		costMatrix = new int* [numNodes+1];
		for(int i =1; i<= numNodes; i++){
			costMatrix[i] = new int [numNodes+1];
		}
		
		for(int i =1; i<= numNodes; i++){
			for(int j = 1 ; j <= numNodes; j++){
			if(i == j){
					costMatrix[i][j] = 0;
				}
				else{
					costMatrix[i][j] = 99999;
				}
			}
		}
		fatherAry = new int [numNodes+1];
		markedAry = new int [numNodes+1];
		bestCostAry = new int [numNodes+1];
		for(int i = 1; i <= numNodes; i++){
			fatherAry[i] = i;
			markedAry[i] = 0;
			bestCostAry[i] = 9999;
		}
		
		loadCostMatrix(inFile, input);
		inFile.close();
		sourceNode = 1;
		outfile1 << "There are " + to_string(numNodes) + " nodes in the input graph.\n";
		while(sourceNode <= numNodes){
		
		loadBestCostAry(sourceNode);
		loadFatherAry(sourceNode);
		loadMarkedAry();
		
		while(!allMarked()){
			int min = 999999;
			for(int i = 1; i<= numNodes; i++){
				if(bestCostAry[i] < min && markedAry[i] ==0){
					min = bestCostAry[i];
					minNode = i;
				}
			}
			markMinNode(minNode);
			outfile2 << "Debug for " << minNode << endl;
			outfile2 << debugPrint();
			int tempNode = 1;
			while(tempNode <= numNodes){
				if(markedAry[tempNode] == 0){
					currentNode = tempNode;
					newCost = computeCost(minNode, currentNode);
					if(newCost < bestCostAry[currentNode]){
						changeFather(currentNode, minNode);
						changeCost(currentNode, newCost);
						outfile2 << debugPrint();
					}
				}	
				tempNode++;
			}
		}
		currentNode = 1;
		while(currentNode <= numNodes){
			if(currentNode == sourceNode){
			outfile1 << printShortestPath(currentNode);
			}
			currentNode++;
			
		}
		sourceNode++;
		}
		outfile1.close();
		outfile2.close();
	}
	~DijkstraSSS(){
		delete [] fatherAry;
		delete [] markedAry;
		delete [] bestCostAry;
		delete [] costMatrix;
	}
};

int main(int argc, char **argv){
	DijkstraSSS dijk(argv[1], argv[2], argv[3]);
}
