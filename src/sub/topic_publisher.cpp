#include <ros/ros.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
 #include <tf/tf.h>
#include <time.h>
 #include "mcl.cpp"
#include "TemplateMatching.cpp"

void pose( int,  char**);

//ros::Publisher pub_pose;
/// Global Variables
vector<particle> startparticles;
Mat img; Mat templ; 
 int sensorLocation[2];
void recvString(const nav_msgs::Odometry::ConstPtr& msg)
{	

    	float x,y;
    	x = msg->pose.pose.position.x;
   		y = msg->pose.pose.position.y;

		particle p;
		int pose[3];

		//convert Meter -> CM
		x *= 100; 
		y *= 100;

		sensorLocation[0] = (int)x;
		sensorLocation[1] = (int)y;
		struct timespec ts;
    	clock_gettime(CLOCK_MONOTONIC, &ts);

    	/* using nano-seconds instead of seconds */
    	srand((time_t)ts.tv_nsec);
		
		int xE1 = rand() % 50;
		int xE2 = rand() % 50;
		int errorX = xE1-xE2;
		int yE1 = rand() % 50;
		int yE2 = rand() % 50;
		int errorY = yE1-yE2;
		int tE1 = rand() % 50;
		int tE2 = rand() % 50;
		int errorT = tE1-tE2;

		//printf("%d %d %d\n", errorX,errorY,errorT);

		pose[0] = (int)x + errorX;
		pose[1] = (int)y + errorY;

		tf::Quaternion q(
		msg->pose.pose.orientation.x,
		msg->pose.pose.orientation.y,
		msg->pose.pose.orientation.z,
		msg->pose.pose.orientation.w);
		tf::Matrix3x3 m(q);


		double roll, pitch, yaw;

		m.getRPY(roll, pitch, yaw);
		
		//RAD -> Centi-RAD
		yaw *= 100;
		pose [2] = (int)yaw + errorT;
		
		p.setPose(pose);

		//printf("X: %d Y: %d T: %d\n",pose[0],pose[1],pose[2]);

		startparticles.push_back(p);

    //ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
    //ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    //ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);

}

int main(int argc, char **argv) {
	

	Mat img = imread( argv[1], 1 );
 	Mat templ = imread( argv[2], 1 );
 	Mat templ2 = imread(argv[3],1);
 	mclmap in_map(match(img, templ));

 	in_map.test3();
 	in_map.update(sensorLocation[0],sensorLocation[1]);

	for (int i =0; i < 30; i++){
		pose( argc,  argv);
	}
	//printf("particle x: %d", startparticles.at(0).pose[0]);
	if(startparticles.size() > 15){
		for (int i = 15; i< startparticles.size(); i++){
			startparticles.pop_back();	
		}
	}

	for(int i = 0; i< startparticles.size(); i++){
				printf("%d:%d:%d\n",startparticles.at(i).pose[0],startparticles.at(i).pose[1],startparticles.at(i).pose[2]);

	}

	control movement(1, 1, 1);
	int sampleSize = 15;


	vector<particle> newParticles;
	newParticles = mcl(startparticles, movement, sampleSize, in_map);
	cout<<"\n";
	
	for (int i = 0; i<newParticles.size(); i++){
		newParticles.at(i).getPose();
	}

	return 0;
}

void pose(int argc, char **argv){
	ros::init(argc, argv, "topic_publisher");
	ros::NodeHandle node;
    ros::Rate r(5	); // 5 hz


	ros::Subscriber sub_string = node.subscribe("/odom", 1, recvString);

	//pub_pose = node.advertise<std_msgs::Float64>("/topic_out", 1);
	r.sleep();
	ros::spinOnce();


}