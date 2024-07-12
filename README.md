
# Bitcoin Silver

Bitcoin Silver is a fork of Bitcoin designed to provide a faster network and continuous development. This README provides an overview of the project, installation instructions, and details on how to contribute.

## Overview

Bitcoin Silver aims to enhance the original Bitcoin network by:
- **Faster Transactions**: Improving transaction speeds to ensure a more efficient and scalable network.
- **Continuous Development**: Regular updates and community-driven enhancements to keep the network secure and up-to-date.

## Features

- **Speed**: Reduced block generation time to increase transaction throughput.
- **Security**: Enhanced security protocols to protect against attacks.
- **Scalability**: Optimized to handle a larger number of transactions per second.
- **Community-Driven**: Open-source project with contributions from developers worldwide.

## Specification

<table>
<tr><td>Coin Name</td><td>Bitcoin Silver</td></tr>
<tr><td>Ticker</td><td>BTCS</td></tr>
<tr><td>Algorithm</td><td>SHA256</td></tr>
<tr><td>Block Time</td><td>5 Min.</td></tr>
<tr><td>Maximum Supply</td><td>21,000,000 BTCS</td></tr>
<tr><td>Coin Maturity</td><td>100 Block</td></tr>
<tr><td>Address Prefix</td><td>1</td></tr>
<tr><td>Halving Interval</td><td>210,000 Block</td></tr>
<tr><td>RPC Port</td><td>8332, 8334</td></tr>
<tr><td>Network Port</td><td>8333</td></tr>
</table>

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:
- **Operating System**: Linux, macOS, or Windows.
- **Dependencies**: Ensure you have `git`, `cmake`, and `gcc` or equivalent installed.

### Installation

1. **Clone the Repository**
```bash
   git clone https://github.com/username/bitcoinsilver.git
   cd bitcoinsilver
```

2. **Build the Source Code**
```bash
   mkdir build
   cd build
   cmake ..
   make
```

   3. **Run the Node**
```bash
   ./bitcoinsilverd
```
## Usage

### Wallet Setup

1.  **Generate a New Wallet**
```bash
   ./bitcoinsilver-cli createwallet "mywallet"
```
    
-   **Get Wallet Address**
```bash
   ./bitcoinsilver-cli getnewaddress
```
### Mining

Start mining with the following command:
```bash
  ./bitcoinsilver-cli generatetoaddress n "mywalletaddress"
```
Replace `n` with the number of blocks you want to mine and `"mywalletaddress"` with your actual wallet address.

## Contributing

We welcome contributions from the community! To get started:

1.  Fork the repository on GitHub.
2.  Create a new branch (`git checkout -b feature/YourFeature`).
3.  Make your changes and commit them (`git commit -am 'Add new feature'`).
4.  Push to the branch (`git push origin feature/YourFeature`).
5.  Create a new Pull Request.

### Reporting Issues

If you encounter any issues, please report them on our [GitHub Issues](https://github.com/MrVistos/bitcoinsilver/issues) page.

[<img src="https://camo.githubusercontent.com/b15646585366435f766c6e4e0e1999d2a6ea59925bb78836519aabd882169c59/68747470733a2f2f63646e2e7261776769742e636f6d2f4e4e54696e2f646973636f72642d6c6f676f2f66343333333334342f7372632f6173736574732f616e696d61746564646973636f72642e737667">](https://discord.gg/MCGn7dzvgd)
