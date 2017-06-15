#include <iostream>
#include <fstream>

using namespace std;

class Median{
	
	int numRows, numCols, minVal, maxVal, newMin = 999, newMax = -999;
	int** tempAry, ** mirrorFramedAry;
	int neighborAry[9] = {0};
	ifstream inFile;
	ofstream outFile;
	
	public:
		
		Median(char* input, char* output){
			inFile.open(input);
			outFile.open(output);
			inFile >> numRows >> numCols >> minVal >> maxVal;
			
			mirrorFramedAry = new int*[numRows+2];
			tempAry = new int*[numRows+2];
			for(int i =0; i< numRows+2 ; i++){
				mirrorFramedAry[i] = new int[numCols+2];
				tempAry[i] = new int[numCols+2];
			}
			
			loadImage();
			mirrorFramed();
			
			for(int i =1; i< numRows+1; i++){
				for(int j=1; j< numCols+1 ; j++){
					loadNeighbors(i, j);
					
						for(int k =0; k< 5; k++){
							for(int h = k+1; h<9 ; h++){
								if(neighborAry[k] > neighborAry[h]){
									int temp = neighborAry[k];
									neighborAry[k] = neighborAry[h];
									neighborAry[h] = temp;
								}
							}
						}
						tempAry[i][j] = neighborAry[4];
						if(tempAry[i][j] > newMax){
							newMax = tempAry[i][j];
						}
						else if( tempAry[i][j] < newMin){
							newMin = tempAry[i][j];
						}
				}
			}
			
			outFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
			
			for(int i =1; i < numRows+1; i++){
				for(int j=1; j< numCols+1; j++){
					outFile << tempAry[i][j] << " ";
				}
				outFile << endl;
			}
			
			inFile.close();
			outFile.close();
		}
		
		void mirrorFramed(){
			for(int i = 0; i < numRows+2; i++){
				mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
				mirrorFramedAry[i][numCols+1] = mirrorFramedAry[i][numCols];
			}
			
			for(int j =0; j< numCols+2; j++){
				mirrorFramedAry[0][j] = mirrorFramedAry[1][j];
				mirrorFramedAry[numRows+1][j] = mirrorFramedAry[numRows][j];
			}
			
		}
		void loadImage(){
			
				for(int i =1; i <= numRows; i++){
					for(int j =1; j <= numCols; j++){
						inFile >> mirrorFramedAry[i][j];
						
					}
			}
			
		}
		
		void loadNeighbors(int row, int col){
			for(int i =0; i< 9; i++){
				if(i <3){
					neighborAry[i] = mirrorFramedAry[row-1][(col-1) + i];
				}
				else if(i>=3 && i<6){
					neighborAry[i] = mirrorFramedAry[row][(col-1) +(i-3)];
				}
				else{
					neighborAry[i] = mirrorFramedAry[row+1][(col-1)+ (i-6)];
				}
			}
			
		}
		
		
};

int main(int argc, char **argv){
	Median median(argv[1], argv[2]);
}
