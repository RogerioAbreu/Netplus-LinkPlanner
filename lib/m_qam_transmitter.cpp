# include "m_qam_transmitter.h"

MQamTransmitter::MQamTransmitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig){

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = B7.outputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = B7.outputSignals[0]->samplingPeriod;

	ModuleBlocks = { &B1, &B2, &B3, &B4, &B5, &B6, &B7 };

}

MQamTransmitter::~MQamTransmitter(void) {

	for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
		ModuleBlocks[i]->terminateBlock();
	}

	for (int unsigned j = 0; j<(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals).size(); j++)
		ModuleBlocks[ModuleBlocks.size()-1]->outputSignals[0]->close();
}

bool MQamTransmitter::runBlock() {

	if (firstTime) {

		firstTime = false;

		for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
			for (int unsigned j = 0; j<(ModuleBlocks[i]->inputSignals).size(); j++) {
				(ModuleBlocks[i]->inputSignals[j])->writeHeader();
			}
		}

		for (int unsigned j = 0; j<(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals).size(); j++)
			ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[j]->writeHeader();

		S6.setFirstValueToBeSaved( B5.impulseResponseLength + 1 );
		S7.setFirstValueToBeSaved( B5.impulseResponseLength + 1 );
		S8.setFirstValueToBeSaved( B5.impulseResponseLength + 1 );
	}

	bool Alive{ false };

	bool Continue{ true };
	do {

		Continue = false;

		for (unsigned int i = 0; i < ModuleBlocks.size(); i++) {
			bool aux = ModuleBlocks[i]->runBlock();
			Continue = (Continue || aux);
			Alive = (Alive || Continue);
		}

		int ready = ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->ready();
		int space = outputSignals[0]->space();
		int length = (ready <= space) ? ready : space;

		t_complex value;
		for (int i = 0; i < length; i++) {
				ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->bufferGet(&value);
				outputSignals[0]->bufferPut(value);
		}
		

	} while (Continue);

	return Alive;
}


void MQamTransmitter::setSaveInternalSignals(bool sSignals) {
	
	if (sSignals) {
		
		saveInternalSignals = true;

		S1.setFileName("MQAM1.sgn");
		S2.setFileName("MQAM2.sgn");
		S3.setFileName("MQAM3.sgn");
		S4.setFileName("MQAM4.sgn");
		S5.setFileName("MQAM5.sgn");
		S6.setFileName("MQAM6.sgn");
		S7.setFileName("MQAM7.sgn");
		S8.setFileName("MQAM8.sgn");
	}

	return;
}

