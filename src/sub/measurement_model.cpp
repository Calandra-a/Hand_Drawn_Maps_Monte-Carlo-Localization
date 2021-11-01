
 #include <cstdlib>
#include "mclmap.cpp"

int prob(int delta);

int  MeasurmentModel(feature feature, particle p, mclmap Map);

int  MeasurmentModel(feature feature,particle p, mclmap Map){//occupancy grid mclmap???

	int j = feature.correspondence;
		int tRange; // r-hat
		
		tRange = (int) sqrt(
			((Map.Map.at(j).x-p.pose[0])*(Map.Map.at(j).x-p.pose[0]))
			+((Map.Map.at(j).y-p.pose[1])*(Map.Map.at(j).y-p.pose[1])));

		int tBearing; //Phi-hat
		
		tBearing = (int) atan2((Map.Map.at(j).y-p.pose[1]),(Map.Map.at(j).x-p.pose[0]));
		

		int deltaR, deltaB, deltaS;
		
		deltaR = feature.range - tRange;
		deltaB = feature.bearing - tBearing;
		deltaS = feature.signiture - Map.Map.at(j).correspondence;
		int error = rand() % 30;


		int q; //numerical probablity p(f[i] at time t | c[i] at time t, m, x at time t)
		q = (prob(deltaR) + prob(deltaB) + prob(deltaS))/3;
		q -= error;
		return q; 
}
int prob(int delta) {
	int prob;
	prob = 100 - (delta / 100); //100% - delta(percentage)
	return prob;
}