# include "m_qam_transmitter.h"

MQamTransmitter::MQamTransmitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig){

	
	ModuleBlocks = { &B1, &B2, &B3, &B4, &B5, &B6, &B7 };


	for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
		for (int unsigned j = 0; j<(ModuleBlocks[i]->inputSignals).size(); j++) {
			(ModuleBlocks[i]->inputSignals[j])->writeHeader();
		}
	}

}

MQamTransmitter::~MQamTransmitter(void) {

	for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
		ModuleBlocks[i]->terminateBlock();
	}
}

bool MQamTransmitter::runBlock() {

	bool Alive{ false };

	bool Continue{ true };
	do {
		Continue = false;
		for (unsigned int i = 0; i < ModuleBlocks.size(); i++) {
			bool aux = ModuleBlocks[i]->runBlock();
			Continue = (Continue || aux);
			Alive = (Alive || Continue);
		}
	} while (Continue);

	return Alive;
}


