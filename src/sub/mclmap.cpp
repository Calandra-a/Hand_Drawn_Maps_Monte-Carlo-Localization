#include "feature.cpp"
#include <vector>


class mclmap {
public:
	 vector<feature> Map;

	mclmap(vector<feature>);
	void update(int,int);
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void testUpdater(int, int);
};

//Constructor

	mclmap::mclmap(vector<feature> input){
		Map = input;
	}

void mclmap::update(int x, int y){
	for (int i=0; i < Map.size(); i++){
		Map.at(i).update(x,y);
	}
}

//Hardcoded maps to run experiments -> will be replaced with feature extractor later
//"simulates perfect sensor data"

void mclmap::test1(){
int pose1[2] = {422,-372};
int pose2[2] = {453,433};
testUpdater(pose1[0],pose1[1]);
testUpdater(pose2[0],pose2[1]);
} 
void mclmap::test2(){
int pose1[2] = {422,-372};
int pose2[2] = {453,433};
testUpdater(pose1[0],pose1[1]);
testUpdater(pose2[0],pose2[1]);
} 

void mclmap::test3(){
int pose1[2] = {452,435};
int pose2[2] = {422,-372};
testUpdater(pose1[0],pose1[1]);
testUpdater(pose2[0],pose2[1]);
} 

void mclmap::test4(){
	
} 
void mclmap::test5(){
	
} 
void mclmap::testUpdater(int x, int y){
	for (int i =0; i < Map.size(); i++){
	if((abs(Map.at(i).x - x)<60) &&(abs(Map.at(i).y - y)<60)){
		Map.at(i).x = x;
		Map.at(i).y = y;
	}
}
}