# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitcoinsilver_cli*         | RPC client functionality used by *bitcoinsilver-cli* executable |
| *libbitcoinsilver_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitcoinsilver_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitcoinsilver_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitcoinsilver_node* and *libbitcoinsilver_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinsilverconsensus*    | Shared library build of static *libbitcoinsilver_consensus* library |
| *libbitcoinsilver_kernel*      | Consensus engine and support library used for validation by *libbitcoinsilver_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinsilverqt*           | GUI functionality used by *bitcoinsilver-qt* and *bitcoinsilver-gui* executables |
| *libbitcoinsilver_ipc*         | IPC functionality used by *bitcoinsilver-node*, *bitcoinsilver-wallet*, *bitcoinsilver-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitcoinsilver_node*        | P2P and RPC server functionality used by *bitcoinsilverd* and *bitcoinsilver-qt* executables. |
| *libbitcoinsilver_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitcoinsilver_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitcoinsilver_wallet*      | Wallet functionality used by *bitcoinsilverd* and *bitcoinsilver-wallet* executables. |
| *libbitcoinsilver_wallet_tool* | Lower-level wallet functionality used by *bitcoinsilver-wallet* executable. |
| *libbitcoinsilver_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitcoinsilverd* and *bitcoinsilver-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitcoinsilver_consensus* and *libbitcoinsilver_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitcoinsilver_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitcoinsilver_node* code lives in `src/node/` in the `node::` namespace
  - *libbitcoinsilver_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitcoinsilver_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitcoinsilver_util* code lives in `src/util/` in the `util::` namespace
  - *libbitcoinsilver_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitcoinsilver-cli[bitcoinsilver-cli]-->libbitcoinsilver_cli;

bitcoinsilverd[bitcoinsilverd]-->libbitcoinsilver_node;
bitcoinsilverd[bitcoinsilverd]-->libbitcoinsilver_wallet;

bitcoinsilver-qt[bitcoinsilver-qt]-->libbitcoinsilver_node;
bitcoinsilver-qt[bitcoinsilver-qt]-->libbitcoinsilverqt;
bitcoinsilver-qt[bitcoinsilver-qt]-->libbitcoinsilver_wallet;

bitcoinsilver-wallet[bitcoinsilver-wallet]-->libbitcoinsilver_wallet;
bitcoinsilver-wallet[bitcoinsilver-wallet]-->libbitcoinsilver_wallet_tool;

libbitcoinsilver_cli-->libbitcoinsilver_util;
libbitcoinsilver_cli-->libbitcoinsilver_common;

libbitcoinsilver_common-->libbitcoinsilver_consensus;
libbitcoinsilver_common-->libbitcoinsilver_util;

libbitcoinsilver_kernel-->libbitcoinsilver_consensus;
libbitcoinsilver_kernel-->libbitcoinsilver_util;

libbitcoinsilver_node-->libbitcoinsilver_consensus;
libbitcoinsilver_node-->libbitcoinsilver_kernel;
libbitcoinsilver_node-->libbitcoinsilver_common;
libbitcoinsilver_node-->libbitcoinsilver_util;

libbitcoinsilverqt-->libbitcoinsilver_common;
libbitcoinsilverqt-->libbitcoinsilver_util;

libbitcoinsilver_wallet-->libbitcoinsilver_common;
libbitcoinsilver_wallet-->libbitcoinsilver_util;

libbitcoinsilver_wallet_tool-->libbitcoinsilver_wallet;
libbitcoinsilver_wallet_tool-->libbitcoinsilver_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitcoinsilver-qt,bitcoinsilverd,bitcoinsilver-cli,bitcoinsilver-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitcoinsilver_wallet* and *libbitcoinsilver_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitcoinsilver_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitcoinsilver_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitcoinsilver_common* should serve a similar function as *libbitcoinsilver_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitcoinsilver_util* and *libbitcoinsilver_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitcoinsilver-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitcoinsilver_kernel* is not supposed to depend on *libbitcoinsilver_common*, only *libbitcoinsilver_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitcoinsilver_kernel* should only depend on *libbitcoinsilver_util* and *libbitcoinsilver_consensus*.

- The only thing that should depend on *libbitcoinsilver_kernel* internally should be *libbitcoinsilver_node*. GUI and wallet libraries *libbitcoinsilverqt* and *libbitcoinsilver_wallet* in particular should not depend on *libbitcoinsilver_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitcoinsilver_consensus*, *libbitcoinsilver_common*, and *libbitcoinsilver_util*, instead of *libbitcoinsilver_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitcoinsilverqt*, *libbitcoinsilver_node*, *libbitcoinsilver_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitcoinsilver_node* to *libbitcoinsilver_kernel* as part of [The libbitcoinsilverkernel Project #24303](https://github.com/MrVistos/bitcoinsilver/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/MrVistos/bitcoinsilver/issues/15732)
