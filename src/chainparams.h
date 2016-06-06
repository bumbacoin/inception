// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COIN_CHAIN_PARAMS_H
#define COIN_CHAIN_PARAMS_H

#include "bignum.h"
#include "uint256.h"
#include "util.h"

#include <vector>

using namespace std;

#define MESSAGE_START_SIZE 4
typedef unsigned char MessageStartChars[MESSAGE_START_SIZE];

class CAddress;
class CBlock;

struct CDNSSeedData {
    string name, host;
    CDNSSeedData(const string &strName, const string &strHost) : name(strName), host(strHost) {}
};

/**
 * CChainParams defines various tweakable parameters of a given instance of the
 * Inception system. There are three: the main network on which people trade goods
 * and services, the public test network which gets reset from time to time and
 * a regression test mode which is intended for private networks only. It has
 * minimal difficulty to ensure that blocks can be found instantly.
 */
class CChainParams
{
public:
    static const string MAIN;
    static const string TESTNET;
    static const string REGTEST;

    /*
    enum Network {
        MAIN,
        TESTNET,
        REGTEST,

        MAX_NETWORK_TYPES
    };
*/
    enum Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,
        EXT_PUBLIC_KEY,
        EXT_SECRET_KEY,

        MAX_BASE58_TYPES
    };

    const uint256& HashGenesisBlock() const { return hashGenesisBlock; }
    const MessageStartChars& MessageStart() const { return pchMessageStart; }
    const vector<unsigned char>& AlertKey() const { return vAlertPubKey; }
    int GetDefaultPort() const { return nDefaultPort; }
    virtual const CBlock& GenesisBlock() const = 0;
    virtual bool RequireRPCPassword() const { return true; }
    const string& DataDir() const { return strDataDir; }
    string NetworkIDString() const { return strNetworkID; }
    const vector<CDNSSeedData>& DNSSeeds() const { return vSeeds; }
    const std::vector<unsigned char> &Base58Prefix(Base58Type type) const { return base58Prefixes[type]; }
    virtual const vector<CAddress>& FixedSeeds() const = 0;
    int RPCPort() const { return nRPCPort; }
    int64_t TargetSpacing() const { return nTargetSpacing; }
    int64_t TargetTimespan() const { return nTargetTimespan; }
    int LastPoWBlock() const { return nLastPoWBlock; }
    int FirstPoSBlock() const { return nFirstPoSBlock; }
    const CBigNum& ProofOfWorkLimit() const { return bnProofOfWorkLimit; }
    int64_t ProofOfWorkReward() const { return nProofOfWorkReward; }
    int SubsidyHalvingInterval() const { return nSubsidyHalvingInterval; }
    const CBigNum& ProofOfStakeLimit() const { return bnProofOfStakeLimit; }
    int64_t ProofOfStakeReward() const { return nProofOfStakeReward; }
    unsigned int ModifierInterval() const { return nModifierInterval; }
    unsigned int StakeMinAge() const { return nStakeMinAge; }
    unsigned int StakeMaxAge() const { return nStakeMaxAge; }
    int CoinbaseMaturity() const { return nCoinbaseMaturity; }


protected:
    CChainParams() {};

    uint256 hashGenesisBlock;
    MessageStartChars pchMessageStart;
    // Raw pub key bytes for the broadcast alert signing key.
    vector<unsigned char> vAlertPubKey;
    int nDefaultPort;
    int nRPCPort;
    CBigNum bnProofOfWorkLimit;
    CBigNum bnProofOfStakeLimit;
    int nSubsidyHalvingInterval;
    string strNetworkID;
    string strDataDir;
    vector<CDNSSeedData> vSeeds;
    std::vector<unsigned char> base58Prefixes[MAX_BASE58_TYPES];
    int64_t nTargetSpacing;
    int64_t nTargetTimespan;
    int nLastPoWBlock;
    int nFirstPoSBlock;
    int64_t nProofOfWorkReward;
    int64_t nProofOfStakeReward;
    unsigned int nModifierInterval;
    unsigned int nStakeMinAge;
    unsigned int nStakeMaxAge;
    int nCoinbaseMaturity;

};

/**
 * Return the currently selected parameters. This won't change after app startup
 * outside of the unit tests.
 */
const CChainParams &Params();

//const CChainParams &Params(CChainParams::Network network);
const CChainParams &Params(const string &chain);

/** Sets the params returned by Params() to those for the given network. */
//void SelectParams(CChainParams::Network network);
void SelectParams(const string &chain);

/**
 * Looks for -regtest or -testnet and then calls SelectParams as appropriate.
 * Returns false if an invalid combination is given.
 */
bool SelectParamsFromCommandLine();

inline bool TestNet() {
    // Note: it's deliberate that this returns "false" for regression test mode.
    return Params().NetworkIDString() == CChainParams::TESTNET;
}

#endif // COIN_CHAIN_PARAMS_H
