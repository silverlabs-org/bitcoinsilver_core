Shared Libraries
================

## bitcoin_silverconsensus

The purpose of this library is to make the verification functionality that is critical to Bitcoin_Silver's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `bitcoin_silverconsensus.h` located in `src/script/bitcoin_silverconsensus.h`.

#### Version

`bitcoin_silverconsensus_version` returns an `unsigned int` with the API version *(currently `1`)*.

#### Script Validation

`bitcoin_silverconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `bitcoin_silverconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/bitcoin_silver/bips/blob/master/bip-0016.mediawiki)) subscripts
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/bitcoin_silver/bips/blob/master/bip-0066.mediawiki)) compliance
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/bitcoin_silver/bips/blob/master/bip-0147.mediawiki))
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/bitcoin_silver/bips/blob/master/bip-0065.mediawiki))
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/bitcoin_silver/bips/blob/master/bip-0112.mediawiki))
- `bitcoin_silverconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/bitcoin_silver/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `bitcoin_silverconsensus_ERR_OK` - No errors with input parameters *(see the return value of `bitcoin_silverconsensus_verify_script` for the verification status)*
- `bitcoin_silverconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `bitcoin_silverconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `bitcoin_silverconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `bitcoin_silverconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used
- `bitcoin_silverconsensus_ERR_INVALID_FLAGS` - Script verification `flags` are invalid (i.e. not part of the libconsensus interface)

### Example Implementations
- [NBitcoin_Silver](https://github.com/MetacoSA/NBitcoin_Silver/blob/5e1055cd7c4186dee4227c344af8892aea54faec/NBitcoin_Silver/Script.cs#L979-#L1031) (.NET Bindings)
- [node-libbitcoinconsensus](https://github.com/bitpay/node-libbitcoinconsensus) (Node.js Bindings)
- [java-libbitcoinconsensus](https://github.com/dexX7/java-libbitcoinconsensus) (Java Bindings)
- [bitcoin_silverconsensus-php](https://github.com/Bit-Wasp/bitcoin_silverconsensus-php) (PHP Bindings)
