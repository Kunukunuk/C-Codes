#include <iostream>
#include <fstream>

using namespace std;

class Histogram{
	
	int* histogram;
	int numRows, numCols, minVal, maxVal;
	int pij;
	ifstream inFile;
	ofstream outFile;
	
	public:
	Histogram(char* input, char* output){
		
		inFile.open(input);
		outFile.open(output);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		
		histogram = new int[maxVal+1];
		for(int i =0; i <= maxVal; i++){
			histogram[i] = 0;
		}
		
		computeHistogram();
	}
	
	~Histogram(){
		delete[] histogram;
	}
	
	void computeHistogram(){
		
		while(inFile >> pij){
			histogram[pij]++;
		}
		for(int i= 0; i <= maxVal; i++){
			if(histogram[i] == 0){
				outFile << "( " << i << "): 0 \n";
			}	
			else if(histogram[i] <80){
				outFile << "( " << i << "): " << histogram[i] << " ";
				for (int j = 1; j <=histogram[i]; j++){
					outFile << "+";
				}
				outFile<< endl;
			}
			else{
				outFile << "( " << i << "): " << histogram[i] << " " ;
				for(int k = 1; k <= 80; k++){
					outFile<< "+";
				}
				outFile<< endl;
			}
		}
		
		inFile.close();
		outFile.close();
	}

};

int main( int argc, char **argv){
	
	Histogram histogram(argv[1], argv[2]);
}
