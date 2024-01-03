const contractAddress = '0xacC110CBA9Bd0b3Ef9B0d854ec85d74721280656'; 
const contractABI = [
  {
    "inputs": [],
    "name": "RATE",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function",
    "constant": true
  },
  {
    "inputs": [
      {
        "internalType": "address",
        "name": "",
        "type": "address"
      }
    ],
    "name": "chipBalances",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function",
    "constant": true
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "ethAmount",
        "type": "uint256"
      }
    ],
    "name": "buyChips",
    "outputs": [],
    "stateMutability": "payable",
    "type": "function",
    "payable": true
  },
  {
    "inputs": [],
    "name": "getChipBalance",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function",
    "constant": true
  }
];


let miniCasino;


function initializeContract() {
  miniCasino = new web3.eth.Contract(contractABI, contractAddress);
}


function startApp() {
}


window.addEventListener('load', async () => {
    if (window.ethereum) {
        window.web3 = new Web3(window.ethereum);
        try {
            await window.ethereum.request({ method: 'eth_requestAccounts' });
            initializeContract(); 
            startApp(); 
        } catch (error) {
            console.error('User denied account access');
        }
    }
    else {
        console.error('Non-Ethereum browser detected.');
    }
});


document.getElementById('connectWallet').onclick = async () => {
    try {
        const accounts = await ethereum.request({ method: 'eth_requestAccounts' });
        const account = accounts[0];
        console.log(`Connected account: ${account}`);
    } catch (error) {
        console.error('Could not connect to wallet:', error);
    }
};


document.getElementById('buyChips').onclick = async () => {
    const accounts = await web3.eth.getAccounts();
    miniCasino.methods.buyChips().send({ from: accounts[0], value: web3.utils.toWei('1', 'ether') })
        .on('transactionHash', (hash) => {
            console.log(`Transaction sent: ${hash}`);
        })
        .on('receipt', (receipt) => {
            console.log(`Transaction confirmed: ${receipt.transactionHash}`);
            // Update user balance
            updateUserBalance(accounts[0]);
        })
        .on('error', (error) => {
            console.error('Transaction failed:', error);
        });
};

async function updateUserBalance(account) {
    const balance = await miniCasino.methods.getChipBalance().call({ from: account });
    document.getElementById('balance').innerText = balance;
}

// Initial balance update
document.addEventListener('DOMContentLoaded', async () => {
    const accounts = await web3.eth.getAccounts();
    if (accounts.length > 0) {
        updateUserBalance(accounts[0]);
    }
});


document.getElementById('submitPurchase').onclick = async () => {
  const ethAmount = document.getElementById('ethAmount').value;
  const tokensToBuy = web3.utils.toWei(ethAmount, 'ether');
  const accounts = await web3.eth.getAccounts();
  miniCasino.methods.buyChips(tokensToBuy).send({ from: accounts[0], value: tokensToBuy })
      .on('transactionHash', (hash) => {
          console.log(`Transaction sent: ${hash}`);
      })
      .on('receipt', (receipt) => {
          console.log(`Transaction confirmed: ${receipt.transactionHash}`);
          updateUserBalance(accounts[0]);
      })
      .on('error', (error) => {
          console.error('Transaction failed:', error);
      });
};
