#include <ros/ros.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>

#include "mcl.cpp"
vector<particle> startparticles;
vector<feature> mclmap ::Map;
void gen(const nav_msgs::Odometry::ConstPtr& msg)
{

    	float x,y;
    	x = msg->pose.pose.position.x;
   		y = msg->pose.pose.position.y;
   		//z.data = msg->pose.pose.position.z;
   		int t =0;
		particle p;
		int pose[3];

		pose[0] = (int)x;
		pose[1] = (int)y;
		pose[2] = 0; //place hodler for now

		p.setPose(pose);


		startparticles.push_back(p);
		
}

/*
UNITS

Distance is in CM... int x = 5 -> 5 cm 

Relation to hand drawn map is
1 pixel =  1 CM
*/


int main(int argc, char **argv) {

	ros::init(argc, argv, "topic_publisher");
	ros::NodeHandle node;
	int startSize = 15;//amount of starting particles 
	for (int i = 0; i < startSize; i++){
	ros::Subscriber sub_string = node.subscribe("/odom", 1, gen);
		ros::spinOnce();
	}


	control movement(1, 1, 1);
	int sampleSize = 10;

	vector<particle> newParticles;
	/*for (int i = 0; i<particles.size(); i++){
		particles.at(i).getPose();
	}*/

	newParticles = mcl(startparticles, movement, sampleSize);
	cout<<"\n";
	/*for (int i = 0; i<newParticles.size(); i++){
		newParticles.at(i).getPose();
	}*/
	//pub_pose = node.advertise<std_msgs::Float64>("/topic_out", 1);
	
	//ros::spin();

	return 0;
}

