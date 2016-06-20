# ifndef PROGRAM_INCLUDE_IQ_MODULATOR_H_
# define PROGRAM_INCLUDE_IQ_MODULATOR_H_

# include "netplus.h"

// Implements a IQ modulator.
class IqModulator : public Block {
 public:

	 /* Input Parameters */

	 t_real outputOpticalPower{ 1e-3 };

	 /* Methods */

	 IqModulator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	 bool runBlock(void);

	 void setOutputOpticalPower(t_real outOpticalPower) { outputOpticalPower = outOpticalPower; }
};

# endif // PROGRAM_INCLUDE_NETPLUS_H_


