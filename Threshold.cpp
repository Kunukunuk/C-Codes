#include <iostream>
#include <fstream>

using namespace std;

class Threshold{
	
	int numRows, numCols, minVal, maxVal;
	int thre_val, pixel_val;
	ifstream inFile;
	ofstream outFile;
	
	public:
	Threshold(char* input){
		inFile.open(input);
		inFile >> numRows >> numCols >> minVal >> maxVal;
	}
	
	void computeThreshold(){
		cout << "What threshold value would you like? \n";
		cin >> thre_val;
		outFile.open("Thr_"+ to_string(thre_val) + ".txt");
		outFile << numRows << " " << numCols << " " << 0 << " " << 1 << endl;
		
		for(int i =0; i< numRows ; i++){
			for( int j = 0; j< numCols; j++){
				inFile >> pixel_val;
				if(pixel_val < thre_val){
					outFile<< 0 << " ";
				}
				else{
					outFile << 1 << " ";
				}
			}
			outFile << endl;
		}
		
		inFile.close();
		outFile.close();	
	}
	
};
int main(int argc, char ** argv){
	
	Threshold Threshold(argv[1]);
	Threshold.computeThreshold();

}
