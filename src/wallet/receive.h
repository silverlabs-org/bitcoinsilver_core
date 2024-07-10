// Copyright (c) 2021 The Bitcoin_Silver Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SILVER_WALLET_RECEIVE_H
#define BITCOIN_SILVER_WALLET_RECEIVE_H

#include <amount.h>
#include <wallet/ismine.h>
#include <wallet/transaction.h>
#include <wallet/wallet.h>

struct COutputEntry
{
    CTxDestination destination;
    CAmount amount;
    int vout;
};

#endif // BITCOIN_SILVER_WALLET_RECEIVE_H
