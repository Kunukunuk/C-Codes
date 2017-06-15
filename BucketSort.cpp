#include <iostream>
#include <fstream>

using namespace std;

class bucketSort{
	
	int *bucketAry;
	int bucketSize, offSet, minData, maxData;
	int count =0;
	public:
	void findMinMax(int value){
		int temp = value;
		if(count ==0){
			minData = value;
			maxData = value;
		}
		else if(temp > maxData){
			maxData = temp;	
		}
		else if(temp < minData){
			minData = temp;
		}
		count++;
	}
	
	void printBucketAry(ofstream &file2){
		
		for(int i = 0; i <= 18; i++){
			file2 << i << " ";
		}
		file2<< endl;
		for(int i = 0; i <= 18; i++){
			if(i>10){
				file2 <<" " <<bucketAry[i] << " ";
			}else{
			file2 << bucketAry[i] << " ";
			}
		}
	}
	
	void printSortedData(ofstream &file1){
		
		for(int index =0; index<= bucketSize ; index++){
			while(bucketAry[index] != 0){
				file1 << index+offSet << endl;
				bucketAry[index]--;
			}
		}
	}
	
	int getIndex(int value){
		return value;
	}
	
	bucketSort(char* input, ofstream &file2){
		int Data;
		ifstream inFile;
		inFile.open(input);
		while(inFile >> Data){
			findMinMax(Data);
		}
		inFile.close();
		bucketSize = maxData-minData;
		offSet = minData;
		bucketAry = new int[bucketSize+1];
		for(int i =0; i <= bucketSize; i++){
			bucketAry[i] = 0;
		}
		inFile.open(input);
		
		while(inFile >> Data){
			int index = getIndex(Data-offSet);
			bucketAry[index]++;
			file2 << Data <<" " << index << " " << endl;
		}
		inFile.close();
		
	}
	
	~bucketSort(){
		delete []bucketAry;
	}
	
};

int main(int argc, char **argv){
	
	ofstream outfile1, outfile2;
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);
	bucketSort bucket(argv[1], outfile2);
	bucket.printBucketAry(outfile2);
	bucket.printSortedData(outfile1);

	outfile1.close();
	outfile2.close();
}

