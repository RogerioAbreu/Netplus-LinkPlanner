# ifndef M_QAM_TRANSMITTER_H_
# define M_QAM_TRANSMITTER_H_

# include "netplus.h"
# include "binary_source.h"
# include "m_qam_mapper.h"
# include "pulse_shaper.h"
# include "iq_modulator.h"

//using namespace std;


class MQamTransmitter : public Block {

	/* State Variables */

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1;

	TimeDiscreteAmplitudeDiscreteReal S2;

	TimeDiscreteAmplitudeDiscreteReal S3;

	TimeContinuousAmplitudeDiscreteReal S4;

	TimeContinuousAmplitudeDiscreteReal S5;

	TimeContinuousAmplitudeContinuousReal S6;

	TimeContinuousAmplitudeContinuousReal S7;

	BandpassSignal S8;


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };

	MQamMapper B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2, &S3 } };

	DiscreteToContinuousTime B3{ vector<Signal*> { &S2 }, vector<Signal*> { &S4 } };

	DiscreteToContinuousTime B4{ vector<Signal*> { &S3 }, vector<Signal*> { &S5 } };

	PulseShaper B5{ vector<Signal*> { &S4 }, vector<Signal*> { &S6 } };

	PulseShaper B6{ vector<Signal*> { &S5 }, vector<Signal*> { &S7 } };

	IqModulator B7{ vector<Signal*> { &S6, &S7 }, vector<Signal*> { &S8 } };


	vector<Block*> ModuleBlocks;
	bool firstTime{ true };

public:

	/* Input Parameters */

	bool saveInternalSignals{ false };

	/* Methods */

	MQamTransmitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	~MQamTransmitter(void);

	bool runBlock(void);

	/* Set Methods */

	void setMode(BinarySourceMode m) { B1.mode = m; }
	void setProbabilityOfZero(double pZero) { B1.probabilityOfZero = pZero; }
	void setBitStream(string bStream) { B1.bitStream = bStream; }
	void setNumberOfBits(long int nOfBits) { B1.numberOfBits = nOfBits; }
	void setPatternLength(int pLength) { B1.patternLength = pLength; }
	void setBitPeriod(double bPeriod) { B1.bitPeriod = bPeriod;	S1.symbolPeriod = bPeriod; S1.samplingPeriod = bPeriod; };

	void setM(int mValue){B2.m = mValue;};
	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues){ B2.m = iqAmplitudesValues.size(); B2.iqAmplitudes.resize(B2.m); B2.iqAmplitudes = iqAmplitudesValues; };
	
	void setNumberOfSamplesPerSymbol(int n) { B3.numberOfSamplesPerSymbol = n;  B4.numberOfSamplesPerSymbol = n; };

	void setRollOffFactor(double rOffFactor){ B5.rollOffFactor = rOffFactor; B6.rollOffFactor = rOffFactor; };

	void setSaveInternalSignals(bool sSignals);

};

#endif