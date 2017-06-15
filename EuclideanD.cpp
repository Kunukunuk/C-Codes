#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

class EuclideanD{
	
	int numRows, numCols, minVal, maxVal;
	double newMin, newMax;
	double** zeroFramedAry;
	double NeighborAry[5] = {0};
	double diagonal = sqrt(2);
	ifstream inFile;
	ofstream outFile, outFile2;
	
	public:
	EuclideanD(char* input, char* output, char* output2){
		inFile.open(input);
		outFile.open(output);
		outFile2.open(output2);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		zeroFramedAry = new double*[numRows+2];
		for(int i =0; i< numRows+2; i++){
			zeroFramedAry[i] = new double[numCols+2];
		}
		newMin = minVal;
		newMax = maxVal;
		zeroFramed();
		loadImage();
		firstPassEuclideanDistance();
		prettyPrintDistance(1);
		secondPassEuclideanDistance();
		prettyPrintDistance(2);
		outFile << setprecision(3) <<numRows << " "<< numCols << " " << newMin << " " << newMax << endl;
		for(int i =1; i < numRows+1; i++){
			for(int j=1; j< numCols+1; j++){
				outFile << zeroFramedAry[i][j];
				if(zeroFramedAry[i][j] != 0 && (zeroFramedAry[i][j] - int(zeroFramedAry[i][j])) > 0.0){
					outFile << " ";
				}
				else{
					outFile << "    ";
				}
			}
			outFile << endl;
		}
		inFile.close();
		outFile.close();
		outFile2.close();
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
	
	void firstPassEuclideanDistance(){
		for(int i =1; i< numRows+1; i++){
			for(int j =1; j< numCols+1; j++){
				if(zeroFramedAry[i][j] > 0){
					zeroFramedAry[i][j] = findMin(i,j,1);
				}
			}
		}
	}
	
	void secondPassEuclideanDistance(){
		for(int i =numRows; i >= 1; i--){
			for(int j =numCols; j >= 1; j--){
				if(zeroFramedAry[i][j] > 0){
					zeroFramedAry[i][j]= findMin(i,j,2);
					if(newMax < zeroFramedAry[i][j]){
						newMax = zeroFramedAry[i][j];
					}
				}
			}
		}
	}
	
	double findMin(int row, int col, int pass){
		double min = 999.99;
		loadNeighbors(row, col, pass);
		if(pass == 2){
			min = NeighborAry[4];
		}
		for(int i=0; i<4; i++){
			if(pass ==1 && i%2==0 && min > NeighborAry[i]){
				min = NeighborAry[i];
			}
			else if(pass ==1 && i%2!=0 && min > NeighborAry[i]){
				min = NeighborAry[i];
			}
			else if(pass ==2){
				if(i%2==0 && min > NeighborAry[i]){
					min = NeighborAry[i];
				}
				else if(i%2!=0 && min > NeighborAry[i]){
					min = NeighborAry[i];
				}
			}
		}
		return min;
	}
	
	void loadNeighbors(int row, int col, int pass){
		for(int i =0; i<5; i++){
			if(i <3 && pass ==1){
				NeighborAry[i] = zeroFramedAry[row-1][col-1+i];
			}
			else if(pass ==1 && i >=3){
				NeighborAry[i] = zeroFramedAry[row][col-4 +i];
			}
			else if(pass ==2 && i<3){
				NeighborAry[i] = zeroFramedAry[row+1][col+1-i];
			}
			else if(pass ==2 && i>=3){
				NeighborAry[i] = zeroFramedAry[row][col+4-i];
			}
		}
		for(int i=0; i<4; i++){
			if(i%2==0){
				NeighborAry[i] = NeighborAry[i]+diagonal;
			}
			else if(i%2 !=0 ){
				NeighborAry[i] = NeighborAry[i]+1;
			}
		}
	}
	
	void prettyPrintDistance(int pass){
		outFile2 << "This is the pretty print of pass "<< pass << endl;
		for(int i = 1; i< numRows+2; i++){
			for(int j =1; j < numCols+2; j++){
				if(zeroFramedAry[i][j] > 0){
					outFile2 << int(zeroFramedAry[i][j] +0.5)<< " ";
				}
				else {
					outFile2 << "  ";
				}
			}
			outFile2<< endl;
		}
	}
};
int main(int argc, char** argv){
	
	EuclideanD distan(argv[1], argv[2], argv[3]);
}
