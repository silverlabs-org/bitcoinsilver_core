// Copyright (c) 2019 The Bitcoin_Silver Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SILVER_NET_TYPES_H
#define BITCOIN_SILVER_NET_TYPES_H

#include <map>

class CBanEntry;
class CSubNet;

using banmap_t = std::map<CSubNet, CBanEntry>;

#endif // BITCOIN_SILVER_NET_TYPES_H
