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

		for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
			for (int unsigned j = 0; j<(ModuleBlocks[i]->inputSignals).size(); j++) {
				(ModuleBlocks[i]->inputSignals[j])->writeHeader();
			}
		}

		for (int unsigned j = 0; j<(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals).size(); j++)
			ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[j]->writeHeader();

		/* 2016-07-05
		S1.setFirstValueToBeSaved(1);
		S2.setFirstValueToBeSaved(1);
		S3.setFirstValueToBeSaved(1);
		S4.setFirstValueToBeSaved(1);
		S5.setFirstValueToBeSaved(1);
		S6.setFirstValueToBeSaved( (int) (S6.samplesPerSymbol*(B5.impulseResponseTimeLength/2-1/2)) + 1);
		S7.setFirstValueToBeSaved( (int) (S6.samplesPerSymbol*(B5.impulseResponseTimeLength/2-1/2)) + 1);
		S8.setFirstValueToBeSaved( (int) (S6.samplesPerSymbol*(B5.impulseResponseTimeLength/2-1/2)) + 1);
		*/
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

		if (firstTime) {

			firstTime = false;

			outputSignals[0]->setSymbolPeriod(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getSymbolPeriod());
			outputSignals[0]->setSamplingPeriod(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getSamplingPeriod());
			outputSignals[0]->setFirstValueToBeSaved(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getFirstValueToBeSaved());

		}

		int ready = ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->ready();
		int space = outputSignals[0]->space();
		int length = (ready <= space) ? ready : space;

		t_complex signalValue;
		for (int i = 0; i < length; i++) {
				ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->bufferGet(&signalValue);
				outputSignals[0]->bufferPut(signalValue);
		}
		

	} while (Continue);

	return Alive;
}


void MQamTransmitter::setBitPeriod(double bPeriod) {

	B1.setBitPeriod(bPeriod);

	S1.setSymbolPeriod(bPeriod); 
	S1.setSamplingPeriod(bPeriod);

	S2.setSymbolPeriod(2*bPeriod);
	S2.setSamplingPeriod(2*bPeriod);

	S3.setSymbolPeriod(2*bPeriod);
	S3.setSamplingPeriod(2*bPeriod);

	S4.setSymbolPeriod(S2.getSymbolPeriod());
	S4.setSamplingPeriod(S2.getSamplingPeriod()/B3.numberOfSamplesPerSymbol);

	S5.setSymbolPeriod(S3.getSymbolPeriod());
	S5.setSamplingPeriod(S3.getSamplingPeriod()/B4.numberOfSamplesPerSymbol);

	S6.setSymbolPeriod(S4.getSymbolPeriod());
	S6.setSamplingPeriod(S4.getSamplingPeriod());

	S7.setSymbolPeriod(S5.getSymbolPeriod());
	S7.setSamplingPeriod(S5.getSamplingPeriod());

	S8.setSymbolPeriod(S6.getSymbolPeriod());
	S8.setSamplingPeriod(S6.getSamplingPeriod());

	outputSignals[0]->setSymbolPeriod(S8.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(S8.getSamplingPeriod());

};

void MQamTransmitter::setNumberOfSamplesPerSymbol(int n) {

	B3.numberOfSamplesPerSymbol = n;  
	B4.numberOfSamplesPerSymbol = n; 

	S4.setSymbolPeriod(S2.getSymbolPeriod());
	S4.setSamplingPeriod(S2.getSamplingPeriod() / B3.numberOfSamplesPerSymbol);

	S5.setSymbolPeriod(S3.getSymbolPeriod());
	S5.setSamplingPeriod(S3.getSamplingPeriod() / B4.numberOfSamplesPerSymbol);

	S6.setSymbolPeriod(S4.getSymbolPeriod());
	S6.setSamplingPeriod(S4.getSamplingPeriod());

	S7.setSymbolPeriod(S5.getSymbolPeriod());
	S7.setSamplingPeriod(S5.getSamplingPeriod());

	S8.setSymbolPeriod(S6.getSymbolPeriod());
	S8.setSamplingPeriod(S6.getSamplingPeriod());

	outputSignals[0]->setSymbolPeriod(S8.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(S8.getSamplingPeriod());

};

void MQamTransmitter::setBuffersLength(int bLength) {
	S1.bufferLength = bLength;
	S2.bufferLength = bLength;
	S3.bufferLength = bLength;
	S4.bufferLength = bLength;
	S5.bufferLength = bLength;
	S6.bufferLength = bLength;
	S7.bufferLength = bLength;
	S8.bufferLength = bLength;
};

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

