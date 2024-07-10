// Copyright (c) 2020 The Bitcoin_Silver Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SILVER_WALLET_DUMP_H
#define BITCOIN_SILVER_WALLET_DUMP_H

#include <fs.h>

class CWallet;

struct bilingual_str;

bool DumpWallet(CWallet& wallet, bilingual_str& error);
bool CreateFromDump(const std::string& name, const fs::path& wallet_path, bilingual_str& error, std::vector<bilingual_str>& warnings);

#endif // BITCOIN_SILVER_WALLET_DUMP_H
