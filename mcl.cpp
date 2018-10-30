#include <vector>
#include <cmath>
#include <math>
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

	int Tvel;
	int Rvel;
	int duration;

	control(int T, int R, int D){
		Tvel = T;
		Rvel = R;
		duration = D
	}

};
class feature{
	int range;
	int bearing; //degrees?
	int signiture; //signiture 
	int correspondence;

	void create(int r,b,s,c){
		range = r;
		bearing = b;
		signiture = s;
		correspondence = c;
	}
}

class map{
	vector<feature> map;	

	map(){
		populateMap(3);
	}
	static void populateMap(int numOfFeatures){

		for(int i =0; i< numOfFeatures; i++){
			feature f;
			f.create(i,i,i,i);
		}
	}

}

int main(){

}


vector<particle> mcl(vector<particle> inParticles ,control movement, int sampleSize){
	vector<particle> predSample;
	std::vector<particle> resample;
	map Map;
	control Movement;
	//Xbar = X = NUll
	predSample.clear();
	resample.clear();
	//predicitive sampling
	particle p;
	for(int i =0; i < sampleSize; i++){
		motion_model(p, inParticles.at(i),Movement);

		p.setWeight = MeasurmentModel(p, Map.map.at(i))
		predSample.add(p);
	}
	particle prs;//particle resampled
	for(int i =0; i < sampleSize; i++){
		//draw i with prob proportional with w[i]
		resample.add(prs);
	}
}


//Velocity Motion Model
//positive rotation is left
//positive translation is forward 
void motion_model(particle new, particle previous, control move){ 
 
//int update[3]; //updated pose x,y,theta
int xCenter;
int yCenter;

xCenter = (previous.Pose[0] - (move.Tvel/move.Rvel)*sin(previous.Pose[2]));
yCenter = (previous.Pose[1] + (move.Tvel/move.Rvel)*cos(previous.Pose[2]));

new.pose[0] = xCenter + (move.Tvel/move.Rvel)*sin(previous.pose[2]+ (move.Rvel*move.duration));
new.pose[1] = yCenter - (move.Tvel/move.Rvel)*cos(previous.pose[2]+ (move.Rvel*move.duration));
new.pose[2] = move.Rvel*move.duration;
}

int  MeasurmentModel(feature feature,particle p){//occupancy grid map???
		j=feature.correspondence
		int tRange; // r-hat
		tRange = sqrt(((map.getX(j)-p.pose[0])*(map.getX(i)-p.pose[0]))+((map.getY(j)-p.pose[1])*(map.getY(j)-p.pose[1])))
		int rBearing; //Phi-hat
		tBearing = atan2((map.getY(j)-p.pose[1]),(map.getX(j)-p.pose[0]));
		int q; //numerical probablity p(f[i] at time t | c[i] at time t, m, x at time t)
		q = prob(feature.range - tRange,StandardDevR) * prob(feature.bearing - tBearing, StandardDevB) * prob(feature.signiture - signiture(j), StandardDevS); 
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


