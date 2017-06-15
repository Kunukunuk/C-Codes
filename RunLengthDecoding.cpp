#include <iostream>
#include <fstream>

using namespace std;

class runlengthDecoding{
	int numRows, numCols, minVal, maxVal, row, col;
	int currentcolor = 0, length = 0;
	ifstream inFile;
	ofstream outFile;
	public:
	runlengthDecoding(char* input, char* output){
		inFile.open(input);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		outFile.open(output);

		outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
		inFile >> row >> col >> currentcolor >> length;
		for(int i = 0; i < numRows; i++){
			for(int j =0; j < numCols; j++){
				if(i == row && j < col+length-1 && j>= col){
					outFile << currentcolor << " ";
				}
				else if(i == row && j >= col+length-1){
					if(j == col+length-1){
						outFile << currentcolor << " ";
					}
					else{
						outFile << "0 ";
					}
					inFile >> row >> col >> currentcolor >> length;
				}
				else{
					outFile << "0 ";
				}
			}
			outFile << endl;
		}
		inFile.close();
		outFile.close();
	}
};

int main(int argc, char** argv){
	runlengthDecoding run(argv[1], argv[2]);
}
