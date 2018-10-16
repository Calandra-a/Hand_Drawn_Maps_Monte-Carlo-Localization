#include <vector>
#include <cmath>
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
		Tvel = t;
		Rvel = R;
		duration = D
	}

}

int main(){

}


vector<particle> mcl(vector<particle> pearTickles ,control movement, int sampleSize){
	vector<particle> predSample;
	std::vector<particle> resample;
	//Xbar = X = NUll
	predSample.clear();
	resample.clear();
	//predicitive sampling
	particle p;
	for(int i =0; i < sampleSize; i++){
		motion_model(p, pearTickles.at(m),control movement);

		//p.setWeight = MeasurmentModel
		//predSample.add(p);
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
int motion_model(particle new, particle previous, control move){ 

int update[3]; //updated pose x,y,theta
int xCenter;
int yCenter;

xCenter = (previous.Pose[0] - (move.Tvel/move.Rvel)*sin(previous.Pose[2]));
yCenter = (previous.Pose[1] + (move.Tvel/move.Rvel)*cos(previous.Pose[2]));

update[0] = xCenter + (move.Tvel/move.Rvel)*sin(previous.pose[2]+ (move.Rvel*move.duration));
update[1] = yCenter - (move.Tvel/move.Rvel)*cos(previous.pose[2]+ (move.Rvel*move.duration));
update[2] = move.Rvel*move.duration;
}