# MEMO

<image src="img/logo.png" width=600/>
MEMO: High-Throughput Blockchain using Memoization

A blockchain is a digital ledger of transactions that is duplicated and distributed across the entire network of computer systems on the blockchain. Blockchains make it difficult or impossible to change, hack, or cheat the system and are one of the most disrupting technologies of the past several decades. However, this decentralized technology is orders of magnitude slower and less energy efficient than existing centralized payment processing approaches such as credit cards run by VISA and Mastercard. Blockchain implementations such as Bitcoin are here to stay, but they currently have a disproportionate carbon footprint and slow transaction speeds (e.g. 7 transactions per sec with tens of minutes confirmation times). Our new digital currency MEMO is a high-throughput blockchain using memoization. It achieves over one thousand transactions per second with confirmations in seconds through larger blocks with smaller block times, and has the potential to achieve over a million transactions per second through sharding. MEMO achieves energy efficiency on par with centralized solutions as well as proof of stake blockchains using an improved Proof of Space consensus using the novel CryptoMemoiz algorithm to implement cryptographic puzzle memoization. CryptoMemoiz leverages XSearch indexing to reduce I/O, large memory, and significant compute resource requirements. MEMO was designed to be lightweight enough to operate on small nodes such as Raspberry PIs, as well as making use of high-end servers with 100+ cores, hundreds of gigabytes of memory, and multiple NVMe storage devices.

### Circulation

MEMO crypto is a high throughput blockchain based on the energy efficient Proof of Space consensus using the novel CryptoMemoiz algorithm to implement cryptographic puzzle memoization. Proof of Space is more energy efficient than Proof of Work
Initial Difficulty: 42 bits prefix (good for 1 find between 64TB and 128TB netspace, or about 8 finds between 512TB and 1024TB)

- winners for a block will be multiple with current approach, one will be selected based on a predetermined algorithm to create block, but all winners will receive equal payout of mining reward; transaction fees will go to winner assembling block
  BlockTime: 3.1536 seconds (~10M blocks per year)
- Block Size: 4096 transactions
- Halving Period: Every 10M blocks, approximately every 12 months
- Initial coin rewards: 23 coins; every 12 months, reduce to next smaller prime number [23, 19, 17, 13, 11, 7, 5, 3, 2, 0]; 10th reduction should make the reward 0 coins
- Initial fees for transactions: 0.001 coin + 1%, reduce by 0.1% every halving period, until fee is 0.001 coin + 0.1% which will remain as a fixed fee for all transactions
- Maximum supply of coins: 1,000,000,000

### Getting Started

_Windows_:
Windows is not currently supported as a build environment. You may run the [dcrptd miner](https://github.com/De-Crypted/dcrptd-miner/releases) to mine MEMO

_Mac OSX_ build pre-requirements

```
brew install leveldb
brew install cmake
pip3 install conan
```

_Ubuntu 18.04 LTS_ install pre-requirements

```
sudo apt update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 1
sudo pip3 install conan==1.59
```

_Ubuntu 20.04 LTS_ install pre-requirements

```
sudo apt-get update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 1
sudo pip3 install conan==1.59
```

_Ubuntu 22.04 LTS_ install pre-requirements

```
sudo apt-get update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.10 1
sudo pip3 install conan==1.59
```

### Building

```
git clone https://github.com/tanand4/MEMO.git
cd MEMO
mkdir build
cd build
conan install .. --build=missing
cd ..
cmake .
```

\*Ubuntu 18.04 Requires a code change to build server
in src/server/server.cpp change:

```
Line 10
#include <filesystem>
to
#include <experimental/filesystem>

Lines 50, 52, & 58
std::filesystem::...
to
std::experimental::filesystem::...
```

To compile the miner run the following command:

```
make miner
```

You will also need the keygen app to create a wallet for your miner:

```
make keygen
```

To compile the node server:

```
make server
```

### Usage

Start by generating `keys.json`.

```
./bin/keygen
```

**_Keep a copy of this file in a safe location_** -- it contains pub/private keys to the wallet that the miner will mint coins to. If you lose this file you lose your coins. We recommend keeping an extra copy on a unique thumbdrive (that you don't re-use) the moment you generate it.

To start mining:

```
./bin/miner
```

To host a node:

```
./bin/server
```

Some server running args:

```
-n (Custom Name, shows on peer list)
-p (Custom Port, default is 3000)
--testnet (Run in testnet mode, good for testing your mining setup)
```

Full list of arguments can be found here: https://github.com/tanand4/MEMO/blob/master/src/core/config.cpp
