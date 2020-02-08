// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <genesis.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>
#include <arith_uint256.h>
#include <pthread.h>

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit =            uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 2 * 60; // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 24-minutes
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 240; // 1250 * 2 minutes
        consensus.nModifierInterval = 10 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 100;

        // POW block consensus
        consensus.nPOWBlockEpoch = 131400;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.firstSuperBlock = 11;
        consensus.lastSuperBlock = 30;
        consensus.superBlockReward = 875000 * COIN; // 875000 * COIN
        consensus.nLastPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00"); // 350000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");  // 380000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0xb4;
        vAlertPubKey = ParseHex("040dfdb01ea59c8facb7fa8c575431f21dd3eaa40f52ae45f0adbf6dfbd4b5af95ca97e13bef548004f3f53423092aadfae68ef47ec8510d954db5e7bd6e3ddae5");
        nDefaultPort = 8138;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1580608922, 300001726, 0x1e0fffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("d94eb9a5b373e71e14bda4ac81bb0680d6d9e7c8aa3de41b4147f09547038076"));
        assert(genesis.hashMerkleRoot == uint256S("0d9f5fbfdd8c2890b5c12702e66cdfc1ce437d2df2acc548ebf28497044e1826"));

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("mainnet1.torus.com");
        vSeeds.emplace_back("35.202.30.156");
        vSeeds.emplace_back("35.241.128.74");
        vSeeds.emplace_back("35.198.225.108");

        base58Prefixes[PUBKEY_ADDRESS] = {0x42}; // T
        base58Prefixes[SCRIPT_ADDRESS] = {0x3c};
        base58Prefixes[SECRET_KEY]     = {0x6c};

        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // xpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // xprv

        // human readable prefix to bench32 address
        bech32_hrp = "trs";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nMiningRequiresPeers = 3;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("d94eb9a5b373e71e14bda4ac81bb0680d6d9e7c8aa3de41b4147f09547038076")},
            }
        };

        chainTxData = ChainTxData{
                // Data as of block ???
                0, // * UNIX timestamp of last known number of transactions
                0,     // * total number of transactions between genesis and that timestamp
                //   (the tx=... number in the SetBestChain debug.log lines)
                0 // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 2 * 60;  // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 24-minute
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 100; // test net min age is 200 confirms
        consensus.nModifierInterval = 10 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 50; // 100 confirmations

        // POW block consensus
        consensus.nPOWBlockEpoch = 400;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.firstSuperBlock = 11;
        consensus.lastSuperBlock = 30;
        consensus.superBlockReward = 875000 * COIN;
        consensus.nLastPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 5138;
        nPruneAfterHeight = 1000;
        vAlertPubKey = ParseHex("0454426aa9b1ab0d64ff6858b2621df5f9bd0be1bf07d48cce2544a7c5d496c5b57056c4dbb04493722f680d33ea455c45f107c91ec3f7c5ea5a2853f619b2f208");

        genesis = CreateGenesisBlock(1581060735, 4194968095, 0x1f00ffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("4d6fb95f1a44a63269340aff42b7eab34d010807fbd973dac068a9c9449f53b7"));
        assert(genesis.hashMerkleRoot == uint256S("f38ae7a4d18c580f4421a3b2e0b9edeecf31214d7c5fc809824fed09ba08b291"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("35.232.215.22");
        vSeeds.emplace_back("35.184.53.101");
        vSeeds.emplace_back("34.66.27.84");

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        // human readable prefix to bench32 address
        bech32_hrp = "trst";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        nMiningRequiresPeers = 2;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
                {
                        {0, uint256S("4d6fb95f1a44a63269340aff42b7eab34d010807fbd973dac068a9c9449f53b7")},
            }
        };

        chainTxData = ChainTxData{
                0,
                0,
                0
        };

    }
};

/**
 * Regression test
 */

class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.powLimit =            uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.nTargetTimespan = 3 * 24 * 60 * 60; // two weeks
        consensus.nStakeTargetSpacing = 2 * 60; // 2-minute block spacing
        consensus.nTargetSpacingWorkMax = 12 * consensus.nStakeTargetSpacing; // 2-hour
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 100; // test net min age is 1 day
        consensus.nModifierInterval = 2 * 60; // Modifier interval: time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 50;

        // POW block consensus
        consensus.nPOWBlockEpoch = 400;
        consensus.powBlockRewardAtEpoch[0] = 304.5 * COIN;
        consensus.powBlockRewardAtEpoch[1] = 228.3 * COIN;
        consensus.powBlockRewardAtEpoch[2] = 152.2 * COIN;
        consensus.powBlockRewardAtEpoch[3] = 76.1 * COIN;
        consensus.firstSuperBlock = 11;
        consensus.lastSuperBlock = 30;
        consensus.superBlockReward = 875000 * COIN;
        consensus.nLastPOWBlock = consensus.nPOWBlockEpoch * 4; //4 epoch

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 4138;
        nPruneAfterHeight = 1000;
        vAlertPubKey = ParseHex("04383862439513e940f6fcbf62d365c162a5256920c2c25b0b4266fdee4a443d71cfe224dbccff6fdb2ea57a37eb0cbec5637ebea06f63c70ca093672fbdc27643");

        genesis = CreateGenesisBlock(1565755832, 500004681, 0x1f00ffff, 1, 0);
//        MineGenesisBlock(genesis, consensus.powLimit);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("2e322dab7102a5c45bcad41da1f03827bf1249d0ed52ed6c5e1d4f2cb2abc410"));
        assert(genesis.hashMerkleRoot == uint256S("e8527c2d6be07695855d99922c97edc7f4e08946e1a26815d159f8b0deda5eac"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        checkpointData = {
            {
                {0, uint256S("2e322dab7102a5c45bcad41da1f03827bf1249d0ed52ed6c5e1d4f2cb2abc410")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = {0x80}; // t
        base58Prefixes[SCRIPT_ADDRESS] = {0x7a};
        base58Prefixes[SECRET_KEY]     = {0x2e};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        bech32_hrp = "trsrt";

        nMiningRequiresPeers = 0;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
    }
};

static std::unique_ptr <CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr <CChainParams> CreateChainParams(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
