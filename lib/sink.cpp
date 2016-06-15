# include "sink.h"

#include <algorithm>    // std::min
#include <string>		// string::compare

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

	for (int i = 0; i<process; i++) {
		//static_cast<TimeContinuousAmplitudeContinuousComplex *> (inputSignals[0])->bufferGet();
		if (((inputSignals[0])->getType()).compare("TimeContinuousAmplitudeContinuousComplex")) {
			static_cast<TimeContinuousAmplitudeContinuousComplex *> (inputSignals[0])->bufferGet();
			if (numberOfSamples > 0) numberOfSamples--;
		}
	}
	
	if (Sink::displayNumberOfSamples) cout << numberOfSamples << "\n";

	return true;
}
