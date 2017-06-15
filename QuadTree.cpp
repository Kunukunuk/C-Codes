#include <iostream>
#include <fstream>

using namespace std;

class QuadTreeNode{
	friend class QuadTree;
	friend class image;
	
	int numRows, numCols, minVal, maxVal;
	int color, rowOffset, colOffset;
	
	QuadTreeNode* NW_kid = NULL;
	QuadTreeNode* SW_kid = NULL;
	QuadTreeNode* SE_kid = NULL;
	QuadTreeNode* NE_kid = NULL;
	public:
	void printNode(QuadTreeNode *T, ofstream & outfile){
		if(T -> NW_kid == NULL || T -> SW_kid == NULL || T -> SE_kid == NULL || T -> NE_kid == NULL){
			return;
		}
		else{
		//cout << T->color <<" " << T->numRows <<" " << T->numCols <<" " << T->minVal<< " " <<T->maxVal << " " << T->rowOffset << " " << T->colOffset << " " << T->NW_kid->color<< " " <<  T->SW_kid->color<< " " <<  T->SE_kid->color <<" " <<  T->NE_kid->color << endl;
		outfile << T->color <<" " << T->numRows <<" " << T->numCols <<" " << T->minVal<< " " <<T->maxVal << " " << T->rowOffset << " " << T->colOffset << " " << T->NW_kid->color<< " " <<  T->SW_kid->color<< " " <<  T->SE_kid->color <<" " <<  T->NE_kid->color << endl;
		}
	}
	
	QuadTreeNode(int rows, int cols, int rowoff, int coloff){
		numRows = rows;
		numCols = cols;
		rowOffset = rowoff;
		colOffset = coloff;

	}
	
	~QuadTreeNode(){
		delete NW_kid;
		delete SW_kid;
		delete SE_kid;
		delete NE_kid;
	}
	
};

class QuadTree{
	public:
	QuadTreeNode* rootNode;
	public:
	
	void computeMinMaxValue(QuadTreeNode *T){
		if(T -> color == 0){
			T -> minVal = 0;
			T -> maxVal = 0;
		}
		else if( T -> color == 1){
			T -> minVal = 1;
			T -> maxVal = 1;
		}
		else if( T -> color ==2){
			T -> minVal = 0;
			T -> maxVal = 1;
		}
	}
	
	QuadTree(int row, int col, int **Ary){
		
		QuadTreeNode *root = new QuadTreeNode(row,col,0,0);
		rootNode = root;
		computeOffsets(rootNode);
		computenumRowsCols(rootNode);
		rootNode -> color = computeColor(Ary, rootNode);
		computeMinMaxValue(rootNode);

	}
	
	~QuadTree(){
		delete rootNode;
	}
	
	void BuildQuadTree(QuadTreeNode *T, int** Ary){
		if(T == NULL || T -> color != 2){
			return;
		}
		else{
			QuadTreeNode *NW = new QuadTreeNode(T -> numRows/2, T -> numCols/2, T -> rowOffset, T -> colOffset);
			T -> NW_kid = NW;
			computeOffsets(T -> NW_kid);
			computenumRowsCols(T -> NW_kid);
			T -> NW_kid -> color = computeColor(Ary, T -> NW_kid);
			computeMinMaxValue(T -> NW_kid);
			BuildQuadTree(T -> NW_kid, Ary);
			
			QuadTreeNode *SW = new QuadTreeNode(T -> numRows/2, T -> numCols/2, (T -> rowOffset) + (T -> numRows/2), T -> colOffset);
			T -> SW_kid = SW;
			computeOffsets(T -> SW_kid);
			computenumRowsCols(T -> SW_kid);
			T -> SW_kid -> color = computeColor(Ary, T -> SW_kid);
			computeMinMaxValue(T -> SW_kid);
			BuildQuadTree(T -> SW_kid, Ary);
			
			QuadTreeNode *SE = new QuadTreeNode(T -> numRows/2, T -> numCols/2, T -> rowOffset + T -> numRows/2, T -> colOffset + T -> numRows/2);
			T -> SE_kid = SE;
			computeOffsets(T -> SE_kid);
			computenumRowsCols(T -> SE_kid);
			T -> SE_kid -> color = computeColor(Ary, T -> SE_kid);
			computeMinMaxValue(T -> SE_kid);
			BuildQuadTree(T -> SE_kid, Ary);

			QuadTreeNode *NE = new QuadTreeNode(T -> numRows/2, T -> numCols/2, T -> rowOffset, T -> colOffset + T -> numCols/2);
			T -> NE_kid = NE;
			computeOffsets(T -> NE_kid);
			computenumRowsCols(T -> NE_kid);
			T -> NE_kid -> color = computeColor(Ary, T -> NE_kid);
			computeMinMaxValue(T -> NE_kid);
			BuildQuadTree(T -> NE_kid, Ary);
			
		}
	}
	void printQuadTree(QuadTreeNode *T, ofstream &outfile){
		if(T == NULL){
			return;
		}
		else{
			T -> printNode(T, outfile);
			printQuadTree ( T -> NW_kid, outfile);
			printQuadTree ( T -> SW_kid, outfile);
			printQuadTree ( T -> SE_kid, outfile);
			printQuadTree ( T -> NE_kid, outfile);
		}
	}
	void computeOffsets(QuadTreeNode *T){
		if( T == rootNode){
			T -> rowOffset = T -> rowOffset;
			T -> colOffset = T -> colOffset;
		}
		else if( T == NULL){
			return;
		}
		else if (T ==  T -> NW_kid){
			T -> NW_kid -> rowOffset = T -> rowOffset;
			T -> NW_kid -> colOffset = T -> colOffset; 
		}
		else if (T == T -> SW_kid){
			T -> SW_kid -> rowOffset = (T -> rowOffset) + (T -> numRows/2);
			T -> SW_kid -> colOffset = T -> colOffset;
		}
		else if (T == T -> SE_kid){
			T -> SE_kid -> rowOffset = T -> rowOffset + T -> numRows/2;
			T -> SE_kid -> colOffset = T -> colOffset + T -> numCols/2;
		}
		else if (T == T ->NE_kid){
			T -> NE_kid -> rowOffset = T -> rowOffset;
			T -> NE_kid -> colOffset = T -> colOffset + T -> numCols/2;
		}
		
	}
	
	void computenumRowsCols(QuadTreeNode *T){
		if(T == rootNode){
			T -> numRows = T -> numRows;
			T -> numCols = T -> numCols;
		}
		else if( T == NULL){
			return;
		}
		else if( T == T -> NW_kid){
			T -> NW_kid -> numRows = T -> numRows/2;
			T -> NW_kid -> numCols = T -> numCols/2;
		}
		else if( T == T -> SW_kid){
			T -> SW_kid -> numRows = T -> numRows/2;
			T -> SW_kid -> numCols = T -> numCols/2;
		}
		else if( T == T -> SE_kid ){
			T -> SE_kid -> numRows = T -> numRows/2;
			T -> SE_kid -> numCols = T -> numCols/2;
		}
		else if( T == T -> NE_kid){
			T -> NE_kid -> numRows = T -> numRows/2;
			T -> NE_kid -> numCols = T -> numCols/2;
		}
		
	}
	
	int computeColor(int **Ary, QuadTreeNode *T){
		if(T == NULL){
			return 6;
		}
		int value = 0;
		bool test = true;
		for( int i = T -> rowOffset; i < T -> rowOffset + T -> numRows; i++){
			for( int j = T -> colOffset; j< T -> rowOffset + T -> numRows; j++){
				if( Ary[0][0] == 0 && Ary[i][j] != 0){
					return 2;
				}
				else{
					test = false;
				}
			}
		}
		if(!test){
			return 0;
		}
		else if(test){
			return 1;
		}
	}
};

class image{
	public:
	int numRows, numCols, minVal, maxVal;
	int** imgAry;
	public:
	void makeImgAry(ifstream& inFile, char* input){
		imgAry = new int* [numRows];
		for(int i = 0; i < numRows; i++){
			imgAry[i] = new int[numCols];
		}
	}
	
	void loadImage(ifstream &inFile){
		for(int i =0; i< numRows; i++){
			for(int j=0; j< numCols; j++){
				inFile >> imgAry[i][j];
			}
		}
	}
	
	image(char* input, char* output){
		ifstream inFile;
		inFile.open(input);
		inFile >> numRows >> numCols >>  minVal >> maxVal;
		makeImgAry(inFile, input);
		loadImage(inFile);
		
		inFile.close();
		
	}
};

int main(int argc, char **argv){
	image img(argv[1], argv[2]);
	ofstream outfile1, outfile2;
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);
	QuadTree quad(img.numRows, img.numCols, img.imgAry);
	quad.BuildQuadTree(quad.rootNode, img.imgAry);
	quad.printQuadTree(quad.rootNode, outfile1);

	outfile1.close();
	outfile2.close();
}
