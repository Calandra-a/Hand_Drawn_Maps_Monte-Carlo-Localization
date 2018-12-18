#include <cmath>
#include <math.h>
 #include <cstdlib>
#include "control.cpp"

particle motion_model(particle p_new, particle previous, control move);
//Velocity Motion Model
//positive rotation is left
//positive translation is forward 
particle motion_model(particle p_new, particle previous, control move){
 

int xCenter;
int yCenter;

xCenter = (previous.pose[0] - (move.Tvel/move.Rvel)*sin(previous.pose[2]));
yCenter = (previous.pose[1] + (move.Tvel/move.Rvel)*cos(previous.pose[2]));

p_new.pose[0] = xCenter + (move.Tvel/move.Rvel)*sin(previous.pose[2]+ (move.Rvel*move.duration));
p_new.pose[1] = yCenter - (move.Tvel/move.Rvel)*cos(previous.pose[2]+ (move.Rvel*move.duration));
p_new.pose[2] = previous.pose[2] + move.Rvel*move.duration;


return p_new;
}
