// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Copyright (c) 2017-2018 The Sierra developers
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


static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000490e35cda9b52316cf10f26967c1f83add26bfb413359371c93fb3bc8ae"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1538228310, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000e498e3312453ed1a1f42039c2af8c19db4a003c9e94fb18c2882ab2c47a"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
	1538228311,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x7f365045cb445aea0178a45f7c8d9af0ada6f6b1d1668e881a000fc9c72a4c11"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
	1538228312,
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
        pchMessageStart[0] = 0x79;
        pchMessageStart[1] = 0x8D;
        pchMessageStart[2] = 0xA7;
        pchMessageStart[3] = 0xBE;
        vAlertPubKey = ParseHex("0471c6d5dcf6b3adaac373367186b2fc3b4f29c1831fab8497a5ade80213199f4519226ef74d955482f534291b298a0fb33a21d9d647b70a8a665c2d76f2d6faa8");
        nDefaultPort = 13660;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Sierra starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Sierra: 5 minutes
        nTargetSpacing = 2 * 60;  // Sierra: 1 minute
        nLastPOWBlock = 1000;
        nMaturity = 80;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 10000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for
        nMaxMoneyOut = 25000000 * COIN;

        const char* pszTimestamp = "Shift To Renewables To Become A Growing Trend In Mining";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f6d850ec539461a1d77b93eb84b081821c1794412ed0c5d040c354a0b7860174e7a64bb6a598758d159989271bdcd1a9097ee9efe2c855b18b4d4cdcee62e582") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1538228310;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 20564164;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=0000005fb5bc70df5d3f470497fbf5ec34606df0ca5ca6157424a441cfaa9329, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010250, nBits=1e00fff0, nNonce=121211724, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000490e35cda9b52316cf10f26967c1f83add26bfb413359371c93fb3bc8ae"));
        assert(genesis.hashMerkleRoot == uint256("0x8e69370d573d44f0b2079f2c5bf8b05d343c4b868145dfffbeb641c6d0710bb7"));

        vSeeds.push_back(CDNSSeedData("35.192.43.4", "35.192.43.4"));
		vSeeds.push_back(CDNSSeedData("35.232.185.35", "35.232.185.35"));
		vSeeds.push_back(CDNSSeedData("185.87.194.125", "185.87.194.125"));
		vSeeds.push_back(CDNSSeedData("35.227.50.190", "35.227.50.190"));
		vSeeds.push_back(CDNSSeedData("185.22.232.55", "185.22.232.55"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 163);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 1977 0x800007b9
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x07)(0xb9).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "0454a953cff4eb0d174bcd9bd996f945e172e3aac1df0614b708a32be04dd5b0ff8929d8d70987a856fcf400afbba467f828c29230914cdcbfed2f22cd38a39684";
        strDarksendPoolDummyAddress = "SZcAHb6H4TZkD9s4XqXzATwtTxcJgGx4jK";
        nStartMasternodePayments = 1538228310;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("0477122982aea42be9e151cd7b94e4dce3cb0e31f1a5e54fc59b0f1a6aa1d764b4ffab14c7b9f1ddd9c94e22417c664200b2f05e4ea80d0d3f7a470f73edd101f5");
        nDefaultPort = 23660;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 10; // Sierra: 10 seconds
        nTargetSpacing = 10;  // Sierra: 10 seconds
        nLastPOWBlock = 2000;
        nMaturity = 2;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1538228311;
        genesis.nNonce = 22845291;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=0000008d766907f5113186ac3e9f198d8d2d96987e6b4a1fc65723050366d94b, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010251, nBits=1e00fff0, nNonce=20767169, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e498e3312453ed1a1f42039c2af8c19db4a003c9e94fb18c2882ab2c47a"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
        vSeeds.push_back(CDNSSeedData("testnet.sierracoin.si", "testnet.sierracoin.si"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 192);
        // Testnet Sierra BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Sierra BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Sierra BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04e03c9692c6d94357a276311b04f1c03a00deadc5eda261b221c3cc0b168e7e96007944ccebd3bf75350739db7a0a793c722266f1584ea7e397dd6f86509dd2ad";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1519010250;
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
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nDefaultPort = 33660;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Sierra: 5 minutes
        nTargetSpacing = 2 * 60;  // Sierra: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1538228312;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 20542300;

        //GenerateGenesisBlock(genesis);
        /*
        CBlock(hash=00000049606f05027a9c1035dbc85f068122b03085c4766389fb69e71508f23e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=03c8762ec4b0597a4437f8fafb7046a718f9f1089aabf9b06ba9560d105febfc, nTime=1519010252, nBits=1e00fff0, nNonce=14592436, vtx=1)
          CTransaction(hash=03c8762ec4, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01043a466562727561727920313874682c2032303138202d20537769747a65726c616e6420656d6272616365732063727970746f63757272656e63792e)
            CTxOut(nValue=0.00000000, scriptPubKey=040fbf75ea45bf7eb65f9075e8342b)
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x39fbc45de1b12e38a4088caf311df902204a2bb8d62aa966a28fb25d7b9e9968"));

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
        nDefaultPort = 33660;
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
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
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
