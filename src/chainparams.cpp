// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Ethf developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (0, uint256("0x000006d773ad0eec0566aba0fe359ff5bd03289a73d666104bb97775a6f20194"))
		(900, uint256("0000000d4f7d50e71c9bd2214d8a5dd7f358efbb287e21dd41536011c54a133e"))
		(2067, uint256("000000000006b0ab13d2df3f0f4ee8796f0a427ad33438698761f28453eac226"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1518850880,// * UNIX timestamp of last checkpoint block
    2535,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000098fa34547f9e97c124633ff5a4f0d9d40a1779a20559613f3674073dfd1"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1518611401,
    0,
    250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x6e2781271a53aca9920db9a89adf88b6f5957b68777cbfc20dcf75bff79b0c3c"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1518611402,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0x09;
        pchMessageStart[2] = 0x07;
        pchMessageStart[3] = 0x19;
	vAlertPubKey = ParseHex("04aa2bb55b61762bc0b33726e8049b579540393e1e10e9aa9718f4afde632005dc6af863fde711396d1de08e7a12a508c2a43ab47a08270e4f839938ac6c662c73");
        nDefaultPort = 52545;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Ethf starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 90; // Ethf: 1.5 minutes
        nTargetSpacingSlowLaunch = 5 * 90;  // Ethf: 7.5 minutes (Slow launch - Block 300)
	nTargetSpacing = 1 * 90; // Ethf: 1.5min after block 300
        nLastPOWBlock = 144000; // after 5 month 
	nRampToBlock = 120; // For start masternodes payment  3 h
        nMaturity = 66; // 99 Minutes
	nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
	nMaxMoneyOut = 21525720 * COIN; // Year 2

        const char* pszTimestamp = "Ethereum future 2018 is future today";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04216228d2c781d11b5eb02625fa8b6d24a6ca80e86907527758f8deabea15642c51d6db2ee098030e0d0f8ed69b5a80f06c2ec0f8999ac5a6f74554c70259f2e9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1518611400;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();;
        genesis.nNonce = 0x28fb40; 


	hashGenesisBlock = genesis.GetHash();
        hashGenesisBlock == uint256("0x000006d773ad0eec0566aba0fe359ff5bd03289a73d666104bb97775a6f20194");
        genesis.hashMerkleRoot == uint256("0x557d44e68f4dee3ca3eb9cd65d82bda1fd75ff09551efa81824d136051f4479b");

		vSeeds.push_back(CDNSSeedData("ethereumfuture.net", "dnsseed.ethereumfuture.net"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 95); // f
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); 
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 214);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2A)(0x22)(0x31).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x20)(0x32)(0x2A).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type 
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x14)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        
	convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        
	fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        
	nPoolMaxTransactions = 3;
        strSporkKey = "04bfe20ede9eec80460f064764896c47207f7cbd742449b3f447b84dd1106bb64060c618bbf49ce8931ce4b16435ad41c3d594d69c716ebbd07116340593f0721c";
        strObfuscationPoolDummyAddress = "fU2hQKFvqrTY5LDxAmo43aii9mHSaz2TPa";
        nStartMasternodePayments = 1518620400; 
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb4;
        pchMessageStart[1] = 0xd3;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xa5;

	vAlertPubKey = ParseHex("04f6be39e0ae2a2f381133f81eb6657efdc160716cd738f896fcb45995b676c708d6a4157f22d4ad53b5e3cb64aa7f6332c83fd31d47f2ee19ef0e4353f552dea2");
        nDefaultPort = 42135;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 90; // 90 Seconds
        nTargetSpacing = 5 * 90;  // 360 Seconds
        nLastPOWBlock = 1000;
        nMaturity = 15;
	nMaxMoneyOut = 33284220 * COIN; // 2032 Maximum

	//! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1518611401;
        genesis.nNonce = 0x26ca93;

	
		genesis.nBits = bnProofOfWorkLimit.GetCompact();

	hashGenesisBlock == uint256("0x0000098fa34547f9e97c124633ff5a4f0d9d40a1779a20559613f3674073dfd1");
	genesis.hashMerkleRoot == uint256("0x557d44e68f4dee3ca3eb9cd65d82bda1fd75ff09551efa81824d136051f4479b");
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("ethereumfuture.net", "test01.ethereumfuture.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 35); // Testnet ethf addresses start with 'F'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 14);  // Testnet ethf script addresses start with '6' or '7'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ethf BIP32 pubkeys start 
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa1).convert_to_container<std::vector<unsigned char> >();
        // Testnet ethf BIP32 prvkeys start 
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x38).convert_to_container<std::vector<unsigned char> >();
        // Testnet ethf BIP44 coin type 
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x05)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "049fe7381f73b375c50d494015f1ac98e659609b79bb11dd537e7ca802102c3e353615361bc5eba4e4f340fb3f9ec9a7ce6ae90a12a9503a6caff52930dabf359e";
        strObfuscationPoolDummyAddress = "FU2hQKFvqrTY5LDxAmo43aii9mHSaz2TPa";
        nStartMasternodePayments = 1518620401; 
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0x8c;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Ethf: 1 day
        nTargetSpacing = 1 * 60;        // Ethf: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1518611402;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0x303b;




		hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51479;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51481;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;
CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}
const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
