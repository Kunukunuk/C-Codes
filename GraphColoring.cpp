#include <iostream>
#include <fstream>

using namespace std;

class graphColoring{
	int** adjacencyMatrix;
	int uncolorNode;
	int newColor, numNodes;
	bool edge = false;
	public:
	graphColoring(char* input, char* output){
		ifstream inFile;
		ofstream outFile;
		inFile.open(input);
		outFile.open(output);
		inFile >> numNodes;
		
		adjacencyMatrix = new int*[numNodes+1];
		for(int i = 1; i<=numNodes; i++){
			adjacencyMatrix[i] = new int[numNodes+1];
		}
		for(int i = 1; i<= numNodes; i++){
			for(int j = 1; j<=numNodes; j++){
				adjacencyMatrix[i][j] = 0;
			}
		}
		loadadjaMatrix(inFile, input, outFile);
		outFile << "Original adjacencyMatrix : \n" <<printadjacencyMatrix();
		newColor = 1;
		for(int i = 1; i<=numNodes; i++){
			for(int j =1; j<= numNodes; j++){
				if(adjacencyMatrix[j][j] == 0){
					uncolorNode = j;				
					if(adjacencyMatrix[i][j] == 0){
						for(int k = 1; k<= numNodes; k++){
							if(adjacencyMatrix[k][k] == newColor){
								if(adjacencyMatrix[j][k] == 1){
									edge = true;
									break;
								}
							}else{
								edge = false;
							}
						}
							if(!edge){
								adjacencyMatrix[uncolorNode][uncolorNode] = newColor;
							}
						}
					}
				}
				if(isAllColored()){
					break;
				}
				newColor++;
		}
		outFile << "\nTotal color used : " + to_string(newColor) + "\n\n";
		outFile << "Final adjacencyMatrix: \n"<<printadjacencyMatrix();
		inFile.close();
		outFile.close();
	}
	
	void loadadjaMatrix(ifstream &inFile, char* input, ofstream &outFile){
		int node1, node2;
		
		outFile << "Intput Pairs: \n";
		while(inFile >> node1 >> node2){
			for(int i =1; i<=numNodes; i++){
				for(int j =1; j<=numNodes; j++){
					if(i == node1 && j == node2){
						outFile << node1 << " " << node2 << endl;
						adjacencyMatrix[i][j] = 1;
						adjacencyMatrix[j][i] = 1;
					}
				}
			}
		}
	}
	
	string printadjacencyMatrix(){
		string output = "";
		for(int i = 1; i <=numNodes; i++){
			for(int j = 1; j<= numNodes; j++){
				output = output + to_string(adjacencyMatrix[i][j]) + " ";
			}
			output = output + "\n";
		}
		
		return output;
	}

	bool isAllColored(){
		for(int i =1; i <= numNodes; i++){
			if(adjacencyMatrix[i][i] == 0){
				return false;
			}
		}
		return true;
	}
	
	~graphColoring(){
		delete [] adjacencyMatrix;
	}
};

int main(int argc, char **argv){
	
	graphColoring gc(argv[1], argv[2]);
	
}
