<<<<<<< HEAD
# include "sink.h"

#include <algorithm>    // std::min
#include <string>		// string::compare
=======
# include "netplus.h"
# include "sink.h"

# include <algorithm>   // std::min
# include <string>		// compare
>>>>>>> refs/remotes/origin/master

using namespace std;

Sink::Sink(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) {

	Block::numberOfInputSignals = InputSig.size();
	Block::numberOfOutputSignals = OutputSig.size();

	Block::inputSignals = InputSig;

}

bool Sink::runBlock(void)
{

	int ready = inputSignals[0]->ready();

	int process{ 0 };
	if (Sink::numberOfSamples >= 0) {
		process = std::min((long int)ready, Sink::numberOfSamples);
	}
	else {
		process = ready;
	}
	 
	if ((process == 0) || (Sink::numberOfSamples == 0)) return false;

<<<<<<< HEAD
	for (int i = 0; i<process; i++) {
		//static_cast<TimeContinuousAmplitudeContinuousComplex *> (inputSignals[0])->bufferGet();
		if (((inputSignals[0])->getType()).compare("TimeContinuousAmplitudeContinuousComplex")) {
			static_cast<TimeContinuousAmplitudeContinuousComplex *> (inputSignals[0])->bufferGet();
			if (numberOfSamples > 0) numberOfSamples--;
		}
	}
	
	if (Sink::displayNumberOfSamples) cout << numberOfSamples << "\n";
=======
/*	if ((inputSignals[0])->getType().compare("TimeDiscreteAmplitudeDiscreteReal"))
		for (int i = 0; i<process; i++) static_cast<TimeDiscreteAmplitudeDiscreteReal *>(inputSignals[0])->bufferGet();

	if ((inputSignals[0])->getType().compare("Binary"))
		for (int i = 0; i<process; i++) static_cast<Binary *>(inputSignals[0])->bufferGet();

	if ((inputSignals[0])->getType().compare("TimeDiscreteAmplitudeContinuousReal"))
		for (int i = 0; i<process; i++) static_cast<TimeDiscreteAmplitudeContinuousReal *>(inputSignals[0])->bufferGet();

	if ((inputSignals[0])->getType().compare("TimeDiscreteAmplitudeContinuousComplex"))
	for (int i = 0; i<process; i++) static_cast<TimeDiscreteAmplitudeContinuousComplex *>(inputSignals[0])->bufferGet();

	if ((inputSignals[0])->getType().compare("TimeContinuousAmplitudeDiscreteReal"))
		for (int i = 0; i<process; i++) static_cast<TimeContinuousAmplitudeDiscreteReal *>(inputSignals[0])->bufferGet();

	if ((inputSignals[0])->getType().compare("TimeContinuousAmplitudeContinuousComplex"))
		for (int i = 0; i<process; i++) static_cast<TimeContinuousAmplitudeContinuousComplex *>(inputSignals[0])->bufferGet();*/


	for (int i = 0; i<process; i++) (inputSignals[0])->bufferGet();

	numberOfSamples = numberOfSamples - process;
	if (displayNumberOfSamples) cout << numberOfSamples << "\n";
>>>>>>> refs/remotes/origin/master

	return true;
}
