#include <iostream>
#include <fstream>
using namespace std;

class morph{
	
	int numRowsIMG, numColsIMG, minValIMG, maxValIMG;
	int numRowsStrctElem, numColsStrctElem, minValStrctElem, maxValStrctElem;
	int rowOrigin, colOrigin, rowFrameSize, colFrameSize;
	int** imgAry,** morphAry,** structElem,** resultAry;
	ifstream inFile1, inFile2;
	ofstream outFile1, outFile2, outFile3, outFile4;
	public:
	morph(char* input1, char* input2, char* dila, char* ero, char* closin, char* openin){
		inFile1.open(input1);
		inFile2.open(input2);
		outFile1.open(dila);
		outFile2.open(ero);
		outFile3.open(closin);
		outFile4.open(openin);
		inFile1 >> numRowsIMG >> numColsIMG >> minValIMG >> maxValIMG;
		inFile2 >> numRowsStrctElem >> numColsStrctElem >> minValStrctElem >> maxValStrctElem;
		inFile2 >> rowOrigin >> colOrigin;
		computeFrameSize();
		imgAry = new int*[numRowsIMG+rowFrameSize*2];
		for(int i =0; i<numRowsIMG+rowFrameSize*2; i++){
			imgAry[i] = new int[numColsIMG+colFrameSize*2];
		}
		loadImage();
		zeroFramedImage();
		cout << "input image" << endl;
		prettyPrint(imgAry, 0);
		morphAry = new int*[numRowsIMG+rowFrameSize*2];
		for(int i =0; i<numRowsIMG+rowFrameSize*2; i++){
			morphAry[i] = new int[numColsIMG+colFrameSize*2];
		}
		resultAry = new int*[numRowsIMG+rowFrameSize*2];
		for(int i =0; i<numRowsIMG+rowFrameSize*2; i++){
			resultAry[i] = new int[numColsIMG+colFrameSize*2];
		}
		structElem = new int*[numRowsStrctElem];
		for(int i=0; i< numRowsStrctElem; i++){
			structElem[i] = new int[numColsStrctElem];
		}
		loadstruct();
		cout << "Structuring Element" << endl;
		prettyPrint(structElem,1);
		dilation(imgAry, morphAry);
		cout << "Dilation Result" << endl;
		prettyPrint(morphAry, 0);
		outPutResult(outFile1);
		morphReset();
		erosion(imgAry, morphAry);
		cout << "Erosion Result" << endl;
		prettyPrint(morphAry,0);
		outPutResult(outFile2);
		morphReset();
		cout << "Closing Result" << endl;
		closing();
		prettyPrint(morphAry,0);
		outPutResult(outFile3);
		morphReset();
		opening();
		cout << "Opening Result" << endl;
		prettyPrint(morphAry,0);
		outPutResult(outFile4);
		morphReset();
		inFile1.close();
		inFile2.close();
		outFile1.close();
		outFile2.close();
		outFile3.close();
		outFile4.close();
	}
	
	void computeFrameSize(){
		rowFrameSize = numRowsStrctElem/2;
		colFrameSize = numColsStrctElem/2;
	}
	void loadImage(){
		for(int i = rowFrameSize; i <= numRowsIMG; i++){
			for(int j =colFrameSize; j <= numColsIMG; j++){
				inFile1 >> imgAry[i][j];
			}
		}
	}
	void loadstruct(){
		for(int i =0; i< numRowsStrctElem; i++){
			for(int j =0; j < numColsStrctElem; j++){
				inFile2 >> structElem[i][j];
			}
		}
	}
	void zeroFramedImage(){
		for(int i=0; i< numRowsIMG+rowFrameSize; i++){
			imgAry[i][0] = 0;
			imgAry[i][numColsIMG+colFrameSize] = 0;
		}
		for(int i = 0; i < numColsIMG+colFrameSize; i++){
			imgAry[0][i]= 0;
			imgAry[numRowsIMG+rowFrameSize][i] = 0;
		}
	}
	void dilation(int** inAry, int** outAry){
		for(int i = rowFrameSize; i <= numRowsIMG; i++){
			for(int j = colFrameSize; j <= numColsIMG; j++){
				if(inAry[i][j] == structElem[rowOrigin][colOrigin]){
					for(int s=0; s< numRowsStrctElem; s++){
						for(int k=0; k< numColsStrctElem; k++){
							if(structElem[s][k] == 1 ){
								outAry[i-1+s][j-1+k] = structElem[s][k];
							}
						}
					}
				}
			}
		}
	}
	void erosion(int** inAry, int** outAry){
		for(int i = rowFrameSize; i <= numRowsIMG; i++){
			for(int j = colFrameSize; j <= numColsIMG; j++){
				if(inAry[i][j] == structElem[rowOrigin][colOrigin]){
					int check = false;
					for(int s=0; s< numRowsStrctElem; s++){
						for(int k=0; k< numColsStrctElem; k++){
							if(structElem[s][k] == 1){
								if(inAry[i-1+s][j-1+k] == structElem[s][k]){
									check = true;
								}
								else{
									check = false;
									s = k =100;
								}
							}
						}
					}
					if(check){
						outAry[i][j] = 1;
					}
				}
			}
		}
	}
	void closing(){
		dilation(imgAry, morphAry); 
		for(int i =0; i < numRowsIMG+rowFrameSize; i++){
			for(int j=0; j< numColsIMG+colFrameSize; j++){
				resultAry[i][j] = morphAry[i][j];
			}
		}
		morphReset();
		erosion(resultAry, morphAry);
		
	}
	void opening(){
		erosion(imgAry, morphAry);
		for(int i =0; i < numRowsIMG+rowFrameSize; i++){
			for(int j=0; j< numColsIMG+colFrameSize; j++){
				resultAry[i][j] = morphAry[i][j];
			}
		}
		morphReset();
		dilation(resultAry, morphAry);
	}
	void prettyPrint(int** Ary, int smallary){
		if(smallary == 1){
			for(int i=0; i< numRowsStrctElem; i++){
				for(int j=0; j< numColsStrctElem; j++){
					if(Ary[i][j] > 0){
						cout << Ary[i][j];
					}
					else{
						cout << " ";
					}
				}
				cout<< endl;
			}
		}
		else{
			for(int i =rowFrameSize; i <= numRowsIMG; i++){
				for(int j =colFrameSize; j<= numColsIMG; j++){
					if(Ary[i][j] > 0){
						cout <<Ary[i][j];
					}
					else{
						cout << " ";
					}
				}
				cout<< endl;
			}
		}
	}
	void outPutResult(ofstream& outFile){
		outFile << numRowsIMG << " " << numColsIMG << " " << minValIMG << " " << maxValIMG << endl;
		for(int i=1; i <= numRowsIMG; i++){
			for(int j=1; j<= numColsIMG; j++){
				outFile << morphAry[i][j];
			}
			outFile << endl;
		}
	}
	
	void morphReset(){
		for(int i= 0; i < numRowsIMG+rowFrameSize; i++){
			for(int j=0; j< numColsIMG+colFrameSize; j++){
				morphAry[i][j] = 0;
			}
		}
	}
	
};

int main(int argc, char** argv){
	morph more(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}
