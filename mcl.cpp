#include <vector>
#include <cmath>
#include <math.h>
#include <boost/math/distributions/normal.hpp>

using namespace std;

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

int main(){

}


vector<particle> mcl(vector<particle> inParticles ,control movement, int sampleSize){
	vector<particle> predSample;
	std::vector<particle> resample;
	map new_map;
	control Movement(1,1,1);
	//Xbar = X = NUll
	predSample.clear();
	resample.clear();
	//predicitive sampling
	particle p;
	for(int i =0; i < sampleSize; i++){
		motion_model(p, inParticles.at(i),Movement);

		p.setWeight = MeasurmentModel(new_map.Map.at(i), p, new_map);// p has pose, map.at(i) has feature and correspondence, Map is the map
		predSample.push_back(p);
	}
	particle prs;//particle resampled
	for(int i =0; i < sampleSize; i++){
		//draw i with prob proportional with w[i]
		resample.push_back(prs);
	}
}


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

int  MeasurmentModel(feature feature,particle p, map Map){//occupancy grid map???
	int j = feature.correspondence;
		int tRange; // r-hat
		
		tRange = sqrt(
			((Map.Map.at(j).x-p.pose[0])*(Map.Map.at(j).x-p.pose[0]))
			+((Map.Map.at(j).y-p.pose[1])*(Map.Map.at(j).y-p.pose[1])));

		int tBearing; //Phi-hat
		
		tBearing = atan2((Map.Map.at(j).y-p.pose[1]),(Map.Map.at(j).x-p.pose[0]));
		
		int q; //numerical probablity p(f[i] at time t | c[i] at time t, m, x at time t)
		
		q = prob(feature.range - tRange,StandardDevR) * prob(feature.bearing - tBearing, StandardDevB) * prob(feature.signiture - Map.Map.at(j).correspondence, StandardDevS); 

		//q = normal_distribution
		return q; 
}




/*TODO
feature extractor to generate
-map - Vector of features
-features - to populate map
-establish releated correspondence to each feature
-draw i with prob proportional with w[i]
-write main
*/