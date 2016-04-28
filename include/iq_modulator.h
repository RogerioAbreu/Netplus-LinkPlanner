# ifndef PROGRAM_INCLUDE_IQ_MODULATOR_H_
# define PROGRAM_INCLUDE_IQ_MODULATOR_H_

# include "netplus.h"

// Implements a IQ modulator.
class IQModulator : public Block {
 public:
	 IQMOdulator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	 bool runBlock(void);
 //private:
};

# endif // PROGRAM_INCLUDE_NETPLUS_H_


