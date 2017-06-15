#include <iostream>
#include <fstream>

using namespace std;

void prettyprint(char* input){
	
	int numRows, numCols, minVal, maxVal, pixel_val;
	
	ifstream inFile;
	ofstream outFile;
	
	inFile.open(input);
	string str(input);
	str = str.substr(0, str.length()-4);
	outFile.open(str + "_PP.txt");
	
	inFile >> numRows >> numCols >> minVal >> maxVal;
	for(int i =0; i< numRows; i++){
		for(int j=0; j< numCols; j++){
			inFile >> pixel_val;
			if(pixel_val > 0){
				outFile << pixel_val << " ";
			}
			else{
				outFile<< " ";
			}
		}
		outFile << endl;
	}
	
	inFile.close();
	outFile.close();
	
}


int main(int argc, char ** argv){
	
	prettyprint(argv[1]);
	
}
