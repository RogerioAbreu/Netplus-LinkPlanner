# ifndef M_QAM_MAPPER_H_
# define M_QAM_MAPPER_H_

# include <vector>
#include <math.h>       // log2 

# include "netplus.h"

using namespace std;

/* Realizes the M-QAM mapping. */
class MQamMapper : public Block {
public:
	MQamMapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);

	bool runBlock(void);

	void setM(int mValue){ m = mValue; };		// m should be of the form m = 2^n, with n integer;

private:
	t_real amplitude {1};
	t_integer m{ 4 };
	t_binary *binaryValue = new t_binary[(int) log2(m)];
	int auxBinaryValue{ 0 };


};

#endif