# ifndef SINK_H_
# define SINK_H_

# include "netplus.h"

class Sink : public Block {

	/* State Variables */

<<<<<<< HEAD
public:

	/* Input Parameters */

	long int numberOfSamples{ -1 };		// number of smaples to be processed, -1 means infinit
	bool displayNumberOfSamples{ false };

	/* Methods */

	Sink(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
=======
	bool displayNumberOfSamples{ false };

public:
>>>>>>> refs/remotes/origin/master

	/* Input Parameters */

<<<<<<< HEAD
	void setNumberOfSamples(long int nOfSamples){ numberOfSamples = nOfSamples; };

	void setDisplayNumberOfSamples(bool option){ displayNumberOfSamples = option; };
=======
	long int numberOfSamples{ -1 };

	/* Methods */

	Sink(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);

	bool runBlock(void);

	void setNumberOfSamples(long int nOfSamples){ numberOfSamples = nOfSamples; };

	void setDisplayNumberOfSamples(bool opt) { displayNumberOfSamples = opt; };
>>>>>>> refs/remotes/origin/master

};

#endif