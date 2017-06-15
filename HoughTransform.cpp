#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class HoughTransform{
	
	class xyCoord{
		public:
			int x,y;
	};
	
	xyCoord point;
	int angleInDegree;
	double pi = 3.14159;
	double angleInRadians;
	int numRows = 180, numCols, minVal, maxVal;
	int** HoughAry;
	ofstream outFile1, outFile2;
	
	public:
	HoughTransform(int** Ary, int row, int col, int min, int max, char* output1, char* output2){
		outFile1.open(output1);
		outFile2.open(output2);
		numCols = (int)sqrt(pow(row,2) + pow(col,2));
		minVal = min;
		maxVal = max;
		HoughAry = new int*[numRows];
		for(int i =0; i< numRows; i++){
			HoughAry[i] = new int[numCols];
		}
		for(int i =0; i< numRows; i++){
			for(int j =0; j< numCols; j++){
				HoughAry[i][j] = 0;
			}
		}
		for( int i =0 ; i< row; i++){
			for(int j =0; j< col; j++){
				if(Ary[i][j] > 0){
					point = {j,i};
					for(angleInDegree = 0; angleInDegree < numRows; angleInDegree++){
						angleInRadians = (double)angleInDegree/180*pi;
						int dist = abs(computeDistance(point, angleInRadians));
						HoughAry[angleInDegree][dist]++;
						if(HoughAry[angleInDegree][dist] > maxVal){
							maxVal = HoughAry[angleInDegree][dist];
						}
					}
				}
			}
		}
		determineHeader(HoughAry);
		prettyPrint(HoughAry);
		outFile1.close();
		outFile2.close();
	}
	
	int computeDistance(xyCoord point, double angle){
		int dist = sqrt(pow(point.x,2) + pow(point.y,2)) * cos(angle - atan2(point.y,point.x) - pi/2);
		return dist;
	}
	
	void determineHeader(int ** Ary){
		outFile1 << numRows << " " << numCols << " " << minVal << " "  << maxVal << endl;	
		for (int i =0; i < numRows; i++){
			for(int j =0; j< numCols; j++){
				outFile1 << Ary[i][j] << " ";
			}
			outFile1 << endl;
		}
	}
	
	void prettyPrint(int ** Ary){
		for(int i =0; i< numRows; i++){
			for(int j =0; j< numCols; j++){
				if(Ary[i][j] > 0){
					outFile2 << ".";
				}
				else{
					outFile2 << " ";
				}
			}
			outFile2 << endl;
		}	
	}
};

class ImageProcessing{
	int numRows, numCols, minVal, maxVal;
	int ** imgAry;
	ifstream inFile;
	
	public:
	ImageProcessing(char* input, char* output1, char* output2){
		inFile.open(input);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		imgAry = new int* [numRows];
		for(int i =0; i < numRows; i++){
			imgAry[i] = new int[numCols];
		}
		loadImage();
		HoughTransform hough(imgAry, numRows, numCols, minVal, maxVal, output1, output2);
		inFile.close();
	}
	
	void loadImage(){
		for(int i =0; i < numRows; i++){
			for(int j =0; j< numCols; j++){
				inFile >> imgAry[i][j];
			}
		}
	}
	
};

int main(int argc, char** argv){
	ImageProcessing img(argv[1], argv[2], argv[3]);
}
