#include "particle.cpp"
#include "motion_model.cpp"
#include "measurement_model.cpp"
using namespace std;


//vector<particle> generateParticles(vector<particle> particles, int setSize);
vector<particle> mcl(vector<particle> inParticles, control movement, int sampleSize, mclmap in_map);

//-----------------------------------------------------------------------------------------------------------------------------------

vector<particle> mcl(vector<particle> inParticles ,control movement, int sampleSize, mclmap in_map){
	vector<particle> predSample;
	vector<particle> resample;
	mclmap new_map = in_map;
	
	predSample.clear();
	resample.clear();
	//predicitive sampling
	particle p;
	int pose[3] = {0,0,0};
	int weight = 0;
	p.setPose(pose); 
	p.setWeight(weight);

	for (int i = 0; i < sampleSize; i++) {
		
		p = motion_model(p, inParticles.at(i), movement);

		int totalWeight = 0;
		for(int j =0; j < in_map.Map.size(); j++){
//			printf("here %d %d\n",i,j);

		 totalWeight += MeasurmentModel(in_map.Map.at(j), p, in_map);//p has pose, mclmap.at(i) has feature and correspondence, Map is the mclmap
				//printf("MeasurmentModel applied: %d\n",totalWeight);
					//printf("here %d %d\n",i,j);


		}
		p.weight = totalWeight/in_map.Map.size(); //takes the average weight based on the particle checked against each feature in the map


		predSample.push_back(p);
						//printf("after models applied- count: %d\n", i);

	}

	for(int i =0; i < sampleSize-3; i++){

		//draw i with prob proportional with w[i]
		particle selected = predSample.at(0);
		int location = 0;
		for (int j = 1; j < predSample.size(); j++) {
			if (predSample.at(j).weight >= selected.weight) {
				selected = predSample.at(j);
				location = j;

			}
		}
		resample.push_back(selected);
		predSample.at(location).weight = -1;//sets weight so it wont be selected again
	}

	return resample;
}



