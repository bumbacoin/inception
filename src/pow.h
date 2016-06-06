#ifndef POW_H
#define POW_H

#include <stdint.h>

class CBlockIndex;
class uint256;

unsigned int GetNextTargetRequired(const CBlockIndex* pindexLast, bool fProofOfStake);
bool CheckProofOfWork(uint256 hash, unsigned int nBits);

#endif // POW_H
