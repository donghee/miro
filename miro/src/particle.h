class Particle {
public:

	ofPoint p, v, f;		// position
	float	r, rSpeed;
	bool	bDead;			// the bool flag we use for removing

	// -----------------------------------------
	Particle() {
		bDead = false;
	}

	// this function is called to test and see
	// if the particle is ready to be removed.
	// -----------------------------------------
	static bool removeMe(const Particle& prt) {
		return 	prt.bDead;
	}

	// -----------------------------------------
	void setup() {
		r = ofRandom(3, 70);			// size of particle
		rSpeed = ofRandom(0.1, 0.6);	// rate of shrinking
		f.set(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));
		v.set(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));

	}

	// -----------------------------------------
	void update() {

		if(r > 0)	r -= rSpeed;
		if(r <= 0)  bDead = true;

		v += f;
		p += v;
		v *=  0.50;

	}

	// -----------------------------------------
	void draw() {
		ofCircle(p.x, p.y, r);
	}

};

