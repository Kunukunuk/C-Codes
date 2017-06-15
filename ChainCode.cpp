#include <iostream>
#include <fstream>

using namespace std;

class image{
	friend class chainCode;
	int numRows, numCols, minVal, maxVal;
	int** zeroFramedAry;
	ifstream inFile;
	
	image(){
		
	}
	image(char* input){
		inFile.open(input);
		inFile >> numRows >> numCols >> minVal >> maxVal;
		zeroFramedAry = new int* [numRows+2];
		for(int i =0; i< numRows+2; i++){
			zeroFramedAry[i] = new int[numCols+2];
		}
		zeroFramed();
		loadImage();
		inFile.close();
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
};

class CCproperty{
	friend class chainCode;
	int maxCC;
	struct Property{
		int label, numpixels, minRow, minCol, maxRow, maxCol;
	} * prop;
	ifstream inFile;
	
	CCproperty(char* pp, int max){
		maxCC = max;
		inFile.open(pp);
		prop = new Property[maxCC+1];
		for(int i =1; i< maxCC+1; i++){
			inFile >> prop[i].label >> prop[i].numpixels >> prop[i].minRow >> prop[i].minCol >> prop[i].maxRow >> prop[i].maxCol;
		}
		inFile.close();
	}
};

class chainCode{
	
	int currentCC =0, minRowOffset, maxRowOffset, minColOffset, maxColOffset;
	struct Point{
		int row, col;
	};
	struct Point neighborCoord[8];
	int nextDirTable[8] = {6,6,0,0,2,3,4,4};
	Point currentP, nextP, startP;
	int nextQ, Pchain, lastQ;
	ofstream outFile, outFile2;
	
	public:
	chainCode(char* cc, char* pp, char* chainc, char* debug){
		image img(cc);
		CCproperty ccp(pp, img.maxVal);
		outFile.open(chainc);
		outFile2.open(debug);
		while(currentCC < ccp.maxCC){
		currentCC++;
		minRowOffset = ccp.prop[currentCC].minRow;
		maxRowOffset = ccp.prop[currentCC].maxRow;
		minColOffset = ccp.prop[currentCC].minCol;
		maxColOffset = ccp.prop[currentCC].maxCol;
		prettyPrint(img.zeroFramedAry, minRowOffset, minColOffset, maxRowOffset, maxColOffset); 
		
		for(int i = minRowOffset; i< maxRowOffset +1; i++){
			for(int j = minColOffset; j< maxColOffset+1; j++){
				if(img.zeroFramedAry[i][j] == currentCC){
					outFile << i << " " << j << " " << currentCC << " ";
					startP ={i,j};
					lastQ = 4;
					int temp = 0;
					outFile2 << "Start P's row and col ( "<< startP.row << " " << startP.col << ")"<<endl;
					outFile2 << "CurrentP nextP lastQ nextQ Pchain\n";
					while( true){
						if((currentP.row == startP.row) && (currentP.col == startP.col) ){
							break;
						}
						if(temp == 0){
							currentP = {i,j};
						}
						nextQ = (lastQ+1)%8;
						Pchain = findNextP(currentP, nextQ, currentCC, img.zeroFramedAry);
						nextP = neighborCoord[Pchain];
						outFile << Pchain << " ";
						outFile2 << "("<<currentP.row << " " << currentP.col << ") (" << nextP.row << " " << nextP.col << ")   "; 
						outFile2 << lastQ << " " << nextQ << " " << Pchain << endl;
						lastQ = nextDirTable[Pchain];
						currentP = nextP;
						temp++;
					}
					i =j = 100;
					outFile << endl;
				}
			}
		}
		}
		outFile.close();
		outFile2.close();
	}
	
	void loadNeighborsCoord(Point& CP){
		neighborCoord[0] = {CP.row, CP.col+1};
		neighborCoord[1] = {CP.row-1, CP.col+1};
		neighborCoord[2] = {CP.row-1, CP.col};
		neighborCoord[3] = {CP.row-1, CP.col-1};
		neighborCoord[4] = {CP.row, CP.col-1};
		neighborCoord[5] = {CP.row+1, CP.col-1};
		neighborCoord[6] = {CP.row+1, CP.col};
		neighborCoord[7] = {CP.row+1, CP.col+1};
	}
	
	int findNextP(Point& cP, int nQ, int CC, int** ary){
			loadNeighborsCoord(cP);
			int chainDir;
			int count = 0;
			while(count < 8){
				if(ary[neighborCoord[nQ].row] [neighborCoord[nQ].col] == CC){
					chainDir = nQ;
					break;
				}
				else{
					if(nQ ==7){
						nQ = 0;
					}
					else{
						nQ++;
					}
				}
				count++;
			}
			
			return chainDir;
	}
	
	void prettyPrint(int** array, int minr, int minc, int maxr, int maxc){
		outFile2 << "Pretty Print of bounding box of label " << currentCC << " :\n";
		for(int i = minr; i<  maxr+1; i++){
			for(int j =minc; j < maxc+1; j++){
				if(array[i][j] > 0){
					outFile2 << array[i][j] << " ";
				}
				else {
					outFile2 << "  ";
				}
			}
			outFile2 << endl;
		}
	}
};

int main(int argc, char** argv){
	chainCode chain(argv[1], argv[2], argv[3], argv[4]);
}
