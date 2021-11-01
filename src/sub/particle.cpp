#include <iostream>
using namespace std;
class particle {
public:
	int pose[3];
	int weight;

public:
	void setPose(int newPose[3]);
	void setWeight(int weight);
	void getPose();
};

//-----------------------------------------------------------------------------------------------------------------------------------
	void particle::setPose(int newPose[3]){
		pose[0] = newPose[0];//update x
		pose[1] = newPose[1];//update y
		pose[2] = newPose[2];//update theta
	}
	void particle::setWeight(int weight){
		weight = this->weight;


	}
	void particle::getPose() {
		cout << "" << pose[0];
		cout << ":" << pose[1];
		cout << ":" << pose[2];
		cout << "\n";
	}