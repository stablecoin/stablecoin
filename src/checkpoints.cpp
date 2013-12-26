// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 StableCoin Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0x0a59605118489aa9cde58e64210d3d56e246758fbabcd1482e54bf4032545221"))
			(     1000, uint256("0xebce88a0891a2b4cd24c9e1baace8381bb38963a603d5ac4ec67f85b2bbb3838"))
			(     5000, uint256("0xdb8b18987a8af6fb5e7df2cedf2ba8eaa8c26990b93b82fe05cd1cd2656211a2"))
			(     8000, uint256("0xc6e73ae9841cc79cdd825d5b5faadf3be6c4312b2ddb19f29ab8133d4b3cd679"))
			(     35120, uint256("0xccb94eddd81fb5dcbedd6b503f0ed2291c494c72a844447d8edd94ea8f7bff28"))
			(     276000, uint256("0xd187fa6c813cafd086c3e653f29acdd7eee87e053d8c3724a6e35950a8339734"))
			(     312200, uint256("0x3f86beee80b99d469857b7d411469efe5b3c418287ba993df6eb235a95db92c7"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
