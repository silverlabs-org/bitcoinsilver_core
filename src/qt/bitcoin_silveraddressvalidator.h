// Copyright (c) 2011-2020 The Bitcoin_Silver Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SILVER_QT_BITCOIN_SILVERADDRESSVALIDATOR_H
#define BITCOIN_SILVER_QT_BITCOIN_SILVERADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class Bitcoin_SilverAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit Bitcoin_SilverAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Bitcoin_Silver address widget validator, checks for a valid bitcoin_silver address.
 */
class Bitcoin_SilverAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit Bitcoin_SilverAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // BITCOIN_SILVER_QT_BITCOIN_SILVERADDRESSVALIDATOR_H
