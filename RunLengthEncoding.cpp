#include <iostream>
#include <fstream>

using namespace std;

class runlengthEncoding{
	int numRows, numCols, minVal, maxVal;
	int currentcolor = 0, length = 0;
	int** Array;
	ifstream inFile;
	ofstream outFile;
	
	public:
	runlengthEncoding(char* input, char* output){
		inFile.open(input);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		outFile.open(output);
		Array = new int*[numRows];
		for(int i =0; i< numRows; i++){
			Array[i] = new int[numCols];
		}
		loadImage();
		outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
		for(int i = 0; i< numRows; i++){
			for(int j =0; j< numCols; j++){
				if( Array[i][j] == 0 ){
						if(length != 0){
							outFile << length << endl;
							length = 0;
							currentcolor = 0;
						}
				}
				else{
					if(currentcolor != Array[i][j]){
						currentcolor = Array[i][j];
						if(length == 0){
							outFile << i << " " << j << " " << currentcolor << " ";
							length = 1;
						}
						else if(length !=0 ){
							outFile << length << endl;
							outFile << i << " " << j << " " << currentcolor << " ";
							if(j == numCols-1 && Array[i][j] != 0){
								length = 1;
								outFile << length << endl;
							}
							length = 0;
						}
						length = 1;
					}
					else if((j == numCols-1 && Array[i][j] != 0)){
							length++;
							outFile << length << endl;
							length = 0;
							currentcolor = 0;
					}
					else{
						length++;
					}
				}
			}
		}
		inFile.close();
		outFile.close();
	}
	
	void loadImage(){
		
		for(int i=0; i<numRows; i++){
			for(int j =0; j< numCols; j++){
				inFile >> Array[i][j];	
			}
		}
		
	}
};

int main(int argc, char** argv){
	runlengthEncoding run(argv[1], argv[2]);
}
