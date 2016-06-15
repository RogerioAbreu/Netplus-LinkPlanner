# include "m_qam_transmitter.h"
# include "sink.h"

int main(){

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	
	BandpassSignal S1{ "S1.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(1.0 / 50e9);
	B1.setPatternLength(5);
	B1.setNumberOfBits(10000);
	B1.setNumberOfSamplesPerSymbol(16);
	B1.setRollOffFactor(0.3);
	B1.setIqAmplitudes({ { 1, 0 }, { -1, 0 } });
	B1.setSaveInternalSignals(true);

	Sink B2{ vector<Signal*> { &S1 }, vector<Signal*> {} };

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}
