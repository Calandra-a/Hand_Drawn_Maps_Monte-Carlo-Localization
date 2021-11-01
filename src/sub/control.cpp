class control {
public:
	int Tvel;
	int Rvel;
	int duration;

	control(int T, int R, int D);

};

//-----------------------------------------------------------------------------------------------------------------------------------
	control::control(int T, int R, int D) {
		Tvel = T;
		Rvel = R;
		duration = D;
	}