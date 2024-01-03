const HDWalletProvider = require('@truffle/hdwallet-provider');
const mnemonic = 'maid busy easily shuffle hat donate embark rebuild armed spin depend swift'; // Replace with your wallet's mnemonic

module.exports = {
  networks: {
    goerli: {
      provider: () => new HDWalletProvider(mnemonic, 'https://goerli.infura.io/v3/0b8d7dcdc4a04887a3903f68b3b81b95'),
      network_id: 5, // Goerli's network id
      gas: 5500000, // Gas limit
      confirmations: 2,
      timeoutBlocks: 200,
      skipDryRun: true
    },
  },

  compilers: {
    solc: {
      version: "0.8.21",      
    }
  },
};


// truffle compile