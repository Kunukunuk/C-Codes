#include <iostream>
#include <fstream>

using namespace std;

class ConnectedCC{
	int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel =0;
	int** zeroFramedAry;
	int* EQAry;
	int NeighborAry[3] = {0};
	int usedLabel = 0;
	struct Property{
		int label, numpixels;
		int boundBox[4] = {999,999, -999, -999};
	};
	
	ifstream inFile;
	ofstream outFile, outFile2, outFile3;
	
	public:
	ConnectedCC(char* input, char* output, char* output2, char* output3){
		inFile.open(input);
		outFile.open(output);
		outFile2.open(output2);
		outFile3.open(output3);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		zeroFramedAry = new int* [numRows+2];
		for(int i =0; i< numRows+2; i++){
			zeroFramedAry[i] = new int[numCols+2];
		}
		EQAry = new int[(numRows*numCols)/4];
		for(int i =0; i < (numRows*numCols)/4; i++){
			EQAry[i] = i;
		}
		zeroFramed();
		loadImage();
		ConnectCC_Pass1();
		prettyPrint(1);
		manageEQAry(1);
		ConnectCC_Pass2();
		prettyPrint(2);
		manageEQAry(2);
		updateEQAry();
		manageEQAry(4);
		ConnectCC_Pass3();
		prettyPrint(3);
		manageEQAry(3);
		
		outFile2 << numRows << " " << numCols << " " << newMin << " " << newMax << " " << endl;
		for(int i =1; i <numRows+1; i++){
			for(int j =1; j<numCols+1; j++){
				outFile2 << zeroFramedAry[i][j] << " ";
			}
			outFile2 << endl;
		}	
		
		inFile.close();
		outFile.close();
		outFile2.close();
		outFile3.close();
	}
	
	void zeroFramed(){
		for(int i = 0; i< numRows+2; i++){
			zeroFramedAry[i][0] = 0;
			zeroFramedAry[i][numCols+1] = 0;
		}
		
		for(int j = 0; j< numCols+2; j++){
			zeroFramedAry[0][j] = 0;
			zeroFramedAry[numRows+1][j] = 0;
		}
		
	}
	
	void loadImage(){
		
		for(int i=1; i<=numRows; i++){
			for(int j =1; j<= numCols; j++){
				inFile >> zeroFramedAry[i][j];	
			}
		}
		
	}
	
	void loadNeighbors(int row, int col, int pass){
		if(pass == 1){
			for(int i =0; i<3; i++){
				if(i == 2){
					NeighborAry[i] = zeroFramedAry[row][col];
				}
				else{
					NeighborAry[i] = zeroFramedAry[(row-1) + i][col-i];
				}
			}
		}
		else if( pass == 2){
			for(int i =0; i <3; i++){
				if(i ==2){
					NeighborAry[i] = zeroFramedAry[row][col];
				}
				else{
					NeighborAry[i] = zeroFramedAry[(row+1) -i][col+i];
				}
			}
		}
	}
	
	void ConnectCC_Pass1(){
		for(int i =1; i< numRows+1; i++){
			for(int j =1; j< numCols+1; j++){
				if(zeroFramedAry[i][j] > 0 ){
					loadNeighbors(i, j, 1);
					if(NeighborAry[0] == 0 && NeighborAry[1] ==0){
						newLabel++;
						EQAry[newLabel] = newLabel;
						zeroFramedAry[i][j] = newLabel;
					}
					else if(NeighborAry[0] > 0 || NeighborAry[1] > 0){
						if(NeighborAry[0]  > 0 && NeighborAry[1] ==0){
							newMin = NeighborAry[0];
							newMax = newMin;
							zeroFramedAry[i][j] = newMin;
						}
						else if(NeighborAry[1] > 0 && NeighborAry[0] == 0){
							newMin = NeighborAry[1];
							newMax = newMin;
							zeroFramedAry[i][j] = newMin;
						}
						else if(NeighborAry[0] >0 && NeighborAry[1] > 0){
							if(NeighborAry[0] > NeighborAry[1]){
								newMin = NeighborAry[1];
								newMax = NeighborAry[0];
								zeroFramedAry[i][j] = newMin;
							}
							else{
								newMin = NeighborAry[0];
								newMax = NeighborAry[1];
								zeroFramedAry[i][j] = newMin;
							}
						}
					}
					
				}
			}
		}
	}
	void ConnectCC_Pass2(){
		for(int i = numRows ; i>= 1; i--){
			for(int j = numCols; j >= 1; j--){
				if(zeroFramedAry[i][j] > 0){
					loadNeighbors(i,j, 2);
					if(NeighborAry[0] > 0 || NeighborAry[1] > 0){
						if(NeighborAry[0] > 0 && NeighborAry[1] ==0 && NeighborAry[0] < zeroFramedAry[i][j]){
							newMin = NeighborAry[0];
							newMax = zeroFramedAry[i][j];
							EQAry[newMax] = newMin;
							zeroFramedAry[i][j] = newMin;
						}
						else if(NeighborAry[0] ==0 && NeighborAry[1] > 0 && NeighborAry[1] < zeroFramedAry[i][j]){
							newMin = NeighborAry[1];
							newMax = zeroFramedAry[i][j];
							EQAry[newMax] = newMin;
							zeroFramedAry[i][j] = newMin;
						}
						else if(NeighborAry[0] > 0 && NeighborAry[1] > 0 && NeighborAry[0] != NeighborAry[1]){
							if(NeighborAry[0] < NeighborAry[1] && NeighborAry[0] < zeroFramedAry[i][j]){
								newMin = NeighborAry[0];
								if(zeroFramedAry[i][j] < NeighborAry[1]){
									newMax = NeighborAry[1];
								}
								else{
									newMax = zeroFramedAry[i][j];
								}
								EQAry[zeroFramedAry[i+1][j]] = newMin;
								zeroFramedAry[i][j+1] = newMin;
								EQAry[newMax] = newMin;
								zeroFramedAry[i][j] = newMin;
							}
							else if( NeighborAry[0] > NeighborAry[1] && NeighborAry[1] < zeroFramedAry[i][j] ){
								newMin = NeighborAry[1];
								if(zeroFramedAry[i][j] < NeighborAry[0]){
									newMax = NeighborAry[0];
								}
								else{
									newMax = zeroFramedAry[i][j];
								}
								EQAry[zeroFramedAry[i][j+1]] = newMin;
								zeroFramedAry[i][j+1] = newMin;
								EQAry[newMax] = newMin;
								zeroFramedAry[i][j] = newMin;
							}
						}
						else if(NeighborAry[0] > 0 && NeighborAry[1] > 0 && NeighborAry[0] == NeighborAry[1]){
							newMin = NeighborAry[0];
							newMax = zeroFramedAry[i][j];
							EQAry[newMax] = newMin;
							zeroFramedAry[i][j] = newMin;
						}
					}
				}
			}
		}
		
	}
	void ConnectCC_Pass3(){
		
		int count[newLabel] = {0};
		newMin = 0;
		newMax = 0;
		struct Property propcc[newLabel];
		for(int i =1; i<= numRows; i++){
			for(int j =1; j<= numCols; j++){
				if(zeroFramedAry[i][j] > 0){
					zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
					if(newMin > zeroFramedAry[i][j]){
						newMin = zeroFramedAry[i][j];
					}
					if(newMax < zeroFramedAry[i][j]){
						newMax = zeroFramedAry[i][j];
					}
					count[zeroFramedAry[i][j]]++;
					loadNeighbors(i, j, 1);
					if(NeighborAry[0] ==0 && NeighborAry[1] == 0 && i < propcc[zeroFramedAry[i][j]].boundBox[0]){
						propcc[zeroFramedAry[i][j]].boundBox[0] = i; 
					}
					if(NeighborAry[0] ==0 && NeighborAry[1] == 0 && j < propcc[zeroFramedAry[i][j]].boundBox[1]){
						propcc[zeroFramedAry[i][j]].boundBox[1] = j;
					}
					loadNeighbors(i,j, 2);
					if(NeighborAry[0] ==0 && NeighborAry[1] == 0 && i > propcc[zeroFramedAry[i][j]].boundBox[3]){
						propcc[zeroFramedAry[i][j]].boundBox[2] = i; 
					}
					if(NeighborAry[0] ==0 && NeighborAry[1] == 0 && j > propcc[zeroFramedAry[i][j]].boundBox[3]){
						propcc[zeroFramedAry[i][j]].boundBox[3] = j;
					}
				}
			}
		}
		for(int i =1; i <= usedLabel; i++){
			propcc[i].label = i;
			propcc[i].numpixels = count[i];
			outFile3 << "Label :" << propcc[i].label << endl;
			outFile3 << "Number of pixels: " << propcc[i].numpixels << endl;
			outFile3 << "Minrow Mincol Maxrow Maxcol" << endl;
			outFile3 << propcc[i].boundBox[0] << "      " << propcc[i].boundBox[1] << "      " << propcc[i].boundBox[2] << "      " << propcc[i].boundBox[3] << "      \n";
		}	
		
		
	}
	
	void updateEQAry(){
		for(int i =1 ; i<= newLabel; i++){
			if(EQAry[i] == i){
				usedLabel++;
				EQAry[i] = usedLabel;
			}
			else if( EQAry[i] != i){
				EQAry[i] = EQAry[EQAry[i]];
			}
		}
	}
	
	void manageEQAry(int pass){
		if(pass == 4){
			outFile << "This is the EQAry of pass after managing" << endl;
		}
		else{
			outFile << "This is the EQAry of pass " << pass << endl;
		}

		for(int i = 0; i<=newLabel; i++){
			outFile << EQAry[i] << " ";
		}
		outFile << endl;
	}
	
	void prettyPrint(int pass){
		
		outFile << "This is the pretty print of pass "<< pass << endl;
		for(int i = 1; i< numRows+2; i++){
			for(int j =1; j < numCols+2; j++){
				if(zeroFramedAry[i][j] > 0){
					outFile << zeroFramedAry[i][j] << " ";
				}
				else {
					outFile << "  ";
				}
			}
			outFile<< endl;
		}
	}
};

int main(int argc, char** argv){
	ConnectedCC con(argv[1], argv[2], argv[3], argv[4]);
}
