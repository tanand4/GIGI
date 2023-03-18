# GIGI

<image src="img/logo.png" width=600/>
Cryptocurrencies leveraging the distributed nature of blockchain technology are becoming popular day by
day, they provide a safe, secure and a distributed approach for removing centralization of financial
institutions. With all these boons comes a bane of high carbon footprint of mining proof of work
cryptocurrencies. GiGi tries to deal with this aspect of reducing the carbon footprint of cryptocurrencies by
using a proof of space concept by leveraging the fast XSearch algorithm. GiGi has big block size and less
block generation time which will allow it to perform more transactions in a limited time compared to other
proof of space coins. The code base is pretty light weight and hence can be used on Raspberry Pi
clusters having large storage capacity to create farms for mining

### Circulation

GIGI is minted by miners who earn rewards. Mining payments occur using the _thwothirding_ algorithm, which yields a total final circulation of ~100M PDN:

- 50 PDN per block until block 666666
- 50\*(2/3) PDN per block from blocks 666667 to 2\*666666
- 50\*(2/3)^2 PDN per block from blocks 2\*66666+1 to 3\*666666
  etc.

#### Comparison with halving

Block reward changes are more often and have less impact compared to halving:
<image src="img/reward.png" width=600/>

The payout curve is smoother in twothirding compared to halving:

<image src="img/circulation.png" width=600/>

### Technical Implementation

Pandanite is written from the ground up in C++. We want the Pandanite source code to be simple, elegant, and easy to understand. Rather than adding duct-tape to an existing currency, we built Pandanite from scratch with lots of love. There are a few optimizations that we have made to help further our core objectives:

- Switched encryption scheme from [secp256k1](https://github.com/bitcoin-core/secp256k1) (which is used by ETH & BTC) to [ED25519](https://ed25519.cr.yp.to/) -- results in 8x speedup during verification and public keys half the size.
- Up to 25,000 transactions per block, 90 second block time

### Getting Started

_Windows_:
Windows is not currently supported as a build environment. You may run the [dcrptd miner](https://github.com/De-Crypted/dcrptd-miner/releases) to mine Pandanite

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
git clone https://github.com/tanand4/GIGI.git
cd GIGI
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

Full list of arguments can be found here: https://github.com/tanand4/GIGI/blob/master/src/core/config.cpp

### Docker

Pandanite is pre-built for amd64 and arm64 with [GitHub Actions](https://github.com/pandanite-crypto/pandanite/actions) and distributed with the [GitHub Container Registry](https://github.com/pandanite-crypto/pandanite/pkgs/container/pandanite)

#### Running with Docker

with `docker`

```shell
docker run -d --name pandanite -p 3000:3000 -v $(pwd)/pandanite-data:/pandanite/data ghcr.io/pandanite-crypto/pandanite:latest server
docker logs -f pandanite
```

You can follow the progress of server sync from `http://localhost:3000`

Running with `docker-compose` is recommended to easily add more options like cpu usage limits and a health checks:

```yaml
version: "3.4"

services:
  pandanite:
    image: ghcr.io/pandanite-crypto/pandanite:latest
    command: server
    ports:
      - 3000:3000
    volumes:
      - ./pandanite-data:/pandanite/data
    restart: unless-stopped
    cpus: 8
    healthcheck:
      test: ["CMD", "curl", "-sf", "http://127.0.0.1:3000"]
      interval: 10s
      timeout: 3s
      retries: 3
      start_period: 10s
```

#### Building with docker

Clone this repository and then

```shell
docker build . -t pandanite
docker run [OPTIONS] pandanite server
```

Running CI build locally

```shell
docker run --privileged --rm tonistiigi/binfmt --install all
docker buildx create --use

GITHUB_REPOSITORY=NeedsSomeValue GITHUB_SHA=NeedsSomeValue docker buildx bake --progress=plain
```
