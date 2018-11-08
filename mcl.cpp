#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include "boost_1_68_0\boost\math\distributions\normal.hpp"

using namespace std;
using boost::math::normal; // typedef provides default type is double.
//-----------------------------------------------------------------------------------------------------------------------------------
class particle{

public:
int pose[3];
int weight;

public:
	void setPose(int newPose[3]){
		pose[0] = newPose[0];//update x
		pose[1] = newPose[1];//update y
		pose[2] = newPose[2];//update theta
	}
	void setWeight(int weight){

	}
};

//-----------------------------------------------------------------------------------------------------------------------------------
class control{
public:
	int Tvel;
	int Rvel;
	int duration;

	control(int T, int R, int D){
		Tvel = T;
		Rvel = R;
		duration = D;
	}

};
//-----------------------------------------------------------------------------------------------------------------------------------
class feature{
public:
	int range;
	int bearing; //degrees?
	int signiture; //signiture 
	int correspondence;
	int x;
	int y;
public:
	void create(int r,int b,int s,int c, int x_in, int y_in){
		range = r;
		bearing = b;
		signiture = s;
		correspondence = c;
		x = x_in;
		y = y_in;

	}
};
//-----------------------------------------------------------------------------------------------------------------------------------
class map{
public:
	static vector<feature> Map;	

	map(){
		populateMap(3);
	}
	static void populateMap(int numOfFeatures){

		for(int i =0; i< numOfFeatures; i++){
			feature f;
			f.create(i,i,i,i,i,i);
			Map.push_back(f);
		}
	}

};
//-----------------------------------------------------------------------------------------------------------------------------------
int main(){
	vector<particle> particles;
	control movement(1, 1, 1);
	int sampleSize = 10;
	mcl(particles, movement, sampleSize);
	return 0;
}

void generateParticles(vector<particle> particles, int setSize) {
	for (int i = 0; i < setSize; i++) {
		int x = rand() % 15;//randoms 0-15
		int y = rand() % 15;
		int t = rand() % 15;
		cout << x << y << t;
		particle p;
		int pose[3] = { x,y,t };
		p.setPose(pose);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------

vector<particle> mcl(vector<particle> inParticles ,control movement, int sampleSize){
	vector<particle> predSample;
	std::vector<particle> resample;
	map new_map;
	//control Movement(1,1,1);
	//Xbar = X = NUll
	predSample.clear();
	resample.clear();
	//predicitive sampling
	particle p;
	for(int i =0; i < sampleSize; i++){
		motion_model(p, inParticles.at(i),movement);
		p.setWeight = MeasurmentModel(new_map.Map.at(i), p, new_map);// p has pose, map.at(i) has feature and correspondence, Map is the map
		predSample.push_back(p);
	}

	for(int i =0; i < sampleSize; i++){
		//draw i with prob proportional with w[i]
		particle selected = predSample.at(0);
		int location = 0;
		for (int i = 1; i < predSample.size(); i++) {
			if (predSample.at(i).weight > selected.weight) {
				selected = predSample.at(i);
				location = i;
			}
		}
		resample.push_back(selected);
		predSample.erase(predSample.begin+location);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------
//Velocity Motion Model
//positive rotation is left
//positive translation is forward 
void motion_model(particle p_new, particle previous, control move){
 
//int update[3]; //updated pose x,y,theta
int xCenter;
int yCenter;

xCenter = (previous.Pose[0] - (move.Tvel/move.Rvel)*sin(previous.Pose[2]));
yCenter = (previous.Pose[1] + (move.Tvel/move.Rvel)*cos(previous.Pose[2]));

p_new.pose[0] = xCenter + (move.Tvel/move.Rvel)*sin(previous.pose[2]+ (move.Rvel*move.duration));
p_new.pose[1] = yCenter - (move.Tvel/move.Rvel)*cos(previous.pose[2]+ (move.Rvel*move.duration));
p_new.pose[2] = move.Rvel*move.duration;
}

//-----------------------------------------------------------------------------------------------------------------------------------
int  MeasurmentModel(feature feature,particle p, map Map){//occupancy grid map???
	int j = feature.correspondence;
		int tRange; // r-hat
		
		tRange = sqrt(
			((Map.Map.at(j).x-p.pose[0])*(Map.Map.at(j).x-p.pose[0]))
			+((Map.Map.at(j).y-p.pose[1])*(Map.Map.at(j).y-p.pose[1])));

		int tBearing; //Phi-hat
		
		tBearing = atan2((Map.Map.at(j).y-p.pose[1]),(Map.Map.at(j).x-p.pose[0]));
		
		double q; //numerical probablity p(f[i] at time t | c[i] at time t, m, x at time t)
		normal dist;
		dist.mean = ((double)feature.range - (double)tRange);
		dist.standard_deviation = 1;

		

		//q = normal_distribution
		return q; 
}




/*TODO
q = prob in measurement model
-draw i with prob proportional with w[i]
-write main
*/