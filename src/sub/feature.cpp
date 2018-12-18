#include <cmath>
#include <math.h>
class feature {
public:
	int range;
	int bearing; //degrees?
	int signiture; //signiture 
	int correspondence;
	int x;
	int y;
public:
	void create(int r, int b, int s, int c, int x_in, int y_in);
	void update(int x_sensor, int y_sensor);
};

//-----------------------------------------------------------------------------------------------------------------------------------
	void feature:: create(int r, int b, int s, int c, int x_in, int y_in) {
	range = r;
	bearing = b;
	signiture = s;
	correspondence = c;
	x = x_in;
	y = y_in;

}

	void feature::update(int x_sensor, int y_sensor){

		range = (int) sqrt(
			((x_sensor-x)*(x_sensor-x))

			+((y_sensor-y)*(y_sensor-y)));

		bearing = (int) atan2((y_sensor-y),(x_sensor-x));

	}
