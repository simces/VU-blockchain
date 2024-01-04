const web3 = new Web3(Web3.givenProvider || "ws://localhost:8545");

const blackjackTokenABI = [
    {
      "inputs": [],
      "stateMutability": "nonpayable",
      "type": "constructor"
    },
    {
      "anonymous": false,
      "inputs": [
        {
          "indexed": true,
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "indexed": true,
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "indexed": false,
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "Transfer",
      "type": "event"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "",
          "type": "address"
        }
      ],
      "name": "balanceOf",
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
      "inputs": [],
      "name": "name",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "symbol",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "totalSupply",
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
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transfer",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transferFrom",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    }
  ];
const rouletteTokenABI = [
    {
      "inputs": [],
      "stateMutability": "nonpayable",
      "type": "constructor"
    },
    {
      "anonymous": false,
      "inputs": [
        {
          "indexed": true,
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "indexed": true,
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "indexed": false,
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "Transfer",
      "type": "event"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "",
          "type": "address"
        }
      ],
      "name": "balanceOf",
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
      "inputs": [],
      "name": "name",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "symbol",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "totalSupply",
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
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transfer",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transferFrom",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    }
  ];
const pokerTokenABI = [
    {
      "inputs": [],
      "stateMutability": "nonpayable",
      "type": "constructor"
    },
    {
      "anonymous": false,
      "inputs": [
        {
          "indexed": true,
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "indexed": true,
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "indexed": false,
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "Transfer",
      "type": "event"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "",
          "type": "address"
        }
      ],
      "name": "balanceOf",
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
      "inputs": [],
      "name": "name",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "symbol",
      "outputs": [
        {
          "internalType": "string",
          "name": "",
          "type": "string"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "totalSupply",
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
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transfer",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    },
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "from",
          "type": "address"
        },
        {
          "internalType": "address",
          "name": "to",
          "type": "address"
        },
        {
          "internalType": "uint256",
          "name": "value",
          "type": "uint256"
        }
      ],
      "name": "transferFrom",
      "outputs": [
        {
          "internalType": "bool",
          "name": "success",
          "type": "bool"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "function"
    }
  ];
const miniCasinoABI = [
    {
      "inputs": [
        {
          "internalType": "address",
          "name": "blackjackTokenAddress",
          "type": "address"
        },
        {
          "internalType": "address",
          "name": "rouletteTokenAddress",
          "type": "address"
        },
        {
          "internalType": "address",
          "name": "pokerTokenAddress",
          "type": "address"
        }
      ],
      "stateMutability": "nonpayable",
      "type": "constructor"
    },
    {
      "stateMutability": "payable",
      "type": "fallback",
      "payable": true
    },
    {
      "inputs": [],
      "name": "BUY_PRICE",
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
      "inputs": [],
      "name": "SELL_PRICE",
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
      "inputs": [],
      "name": "blackjackToken",
      "outputs": [
        {
          "internalType": "contract BlackjackToken",
          "name": "",
          "type": "address"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "pokerToken",
      "outputs": [
        {
          "internalType": "contract PokerToken",
          "name": "",
          "type": "address"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "inputs": [],
      "name": "rouletteToken",
      "outputs": [
        {
          "internalType": "contract RouletteToken",
          "name": "",
          "type": "address"
        }
      ],
      "stateMutability": "view",
      "type": "function",
      "constant": true
    },
    {
      "stateMutability": "payable",
      "type": "receive",
      "payable": true
    },
    {
      "inputs": [],
      "name": "buyBlackjackTokens",
      "outputs": [],
      "stateMutability": "payable",
      "type": "function",
      "payable": true
    },
    {
      "inputs": [
        {
          "internalType": "uint256",
          "name": "tokensToSell",
          "type": "uint256"
        }
      ],
      "name": "sellBlackjackTokens",
      "outputs": [],
      "stateMutability": "nonpayable",
      "type": "function"
    },
    {
      "inputs": [],
      "name": "buyRouletteTokens",
      "outputs": [],
      "stateMutability": "payable",
      "type": "function",
      "payable": true
    },
    {
      "inputs": [
        {
          "internalType": "uint256",
          "name": "tokensToSell",
          "type": "uint256"
        }
      ],
      "name": "sellRouletteTokens",
      "outputs": [],
      "stateMutability": "nonpayable",
      "type": "function"
    },
    {
      "inputs": [],
      "name": "buyPokerTokens",
      "outputs": [],
      "stateMutability": "payable",
      "type": "function",
      "payable": true
    },
    {
      "inputs": [
        {
          "internalType": "uint256",
          "name": "tokensToSell",
          "type": "uint256"
        }
      ],
      "name": "sellPokerTokens",
      "outputs": [],
      "stateMutability": "nonpayable",
      "type": "function"
    }
  ];

const blackjackTokenAddress = '0x2Aaec6E82DFe3387eB046865f4744Fd5846FeB5F'; // Replace with actual address
const rouletteTokenAddress = '0x911DA06e1e50584Cc081932c8B8E8f57b4aa0b06'; // Replace with actual address
const pokerTokenAddress = '0xF35497C42e3D9Ccae3B5B84d4c5cC6e7eDEaf1Ce';     // Replace with actual address
const miniCasinoAddress = '0xb2C9A8E62b4D4584F371588195b5A653CC7DDE5A';     // Replace with actual address

let blackjackToken, rouletteToken, pokerToken, miniCasino;

async function updateUserInfo() {
    const userAddress = ethereum.selectedAddress;
    document.getElementById("userAddress").innerText = `Welcome: ${userAddress}`;

    const userEthBalance = await web3.eth.getBalance(userAddress);
    document.getElementById("userEthBalance").innerText = `Your ETH Balance: ${web3.utils.fromWei(userEthBalance, 'ether')} ETH`;

    updateTokenBalances(userAddress);
    updateCasinoBalances();
}

async function updateTokenBalances(userAddress) {
    const userBlackjackBalance = await blackjackToken.methods['balanceOf'](userAddress).call();
    document.getElementById("userBlackjackBalance").innerText = `Your Blackjack Token Balance: ${userBlackjackBalance}`;

    const userRouletteBalance = await rouletteToken.methods['balanceOf'](userAddress).call();
    document.getElementById("userRouletteBalance").innerText = `Your Roulette Token Balance: ${userRouletteBalance}`;

    const userPokerBalance = await pokerToken.methods['balanceOf'](userAddress).call();
    document.getElementById("userPokerBalance").innerText = `Your Poker Token Balance: ${userPokerBalance}`;
}

async function updateCasinoBalances() {
    const casinoEthBalance = await web3.eth.getBalance(miniCasino._address);
    document.getElementById("casinoEthBalance").innerText = `Casino ETH Balance: ${web3.utils.fromWei(casinoEthBalance, 'ether')} ETH`;

    const casinoBlackjackBalance = await blackjackToken.methods['balanceOf'](miniCasino._address).call();
    document.getElementById("casinoBlackjackBalance").innerText = `Casino Blackjack Token Balance: ${casinoBlackjackBalance}`;

    const casinoRouletteBalance = await rouletteToken.methods['balanceOf'](miniCasino._address).call();
    document.getElementById("casinoRouletteBalance").innerText = `Casino Roulette Token Balance: ${casinoRouletteBalance}`;

    const casinoPokerBalance = await pokerToken.methods['balanceOf'](miniCasino._address).call();
    document.getElementById("casinoPokerBalance").innerText = `Casino Poker Token Balance: ${casinoPokerBalance}`;
}



window.addEventListener('load', async () => {
    if (window.ethereum) {

        const web3 = new Web3(window.ethereum);

        await ethereum.request({ method: 'eth_requestAccounts' });

        blackjackToken = new web3.eth.Contract(blackjackTokenABI, blackjackTokenAddress);
        console.log(blackjackToken.methods);

        rouletteToken = new web3.eth.Contract(rouletteTokenABI, rouletteTokenAddress);
        pokerToken = new web3.eth.Contract(pokerTokenABI, pokerTokenAddress);
        miniCasino = new web3.eth.Contract(miniCasinoABI, miniCasinoAddress);

        updateUserInfo();
    } else {
        console.error("Please install MetaMask!");
    }
});

async function buyBlackjackTokens() {
    const amount = document.getElementById("buyBlackjackAmount").value;
    const amountInWei = web3.utils.toWei(amount, 'ether');
    await miniCasino.methods.buyBlackjackTokens().send({from: ethereum.selectedAddress, value: amountInWei});
}

async function sellBlackjackTokens() {
    const amount = document.getElementById("sellBlackjackAmount").value;
    await miniCasino.methods.sellBlackjackTokens(amount).send({from: ethereum.selectedAddress});
}

async function buyRouletteTokens() {
    const amount = document.getElementById("buyRouletteAmount").value;
    const amountInWei = web3.utils.toWei(amount, 'ether');
    await miniCasino.methods.buyRouletteTokens().send({from: ethereum.selectedAddress, value: amountInWei});
}

async function sellRouletteTokens() {
    const amount = document.getElementById("sellRouletteAmount").value;
    await miniCasino.methods.sellRouletteTokens(amount).send({from: ethereum.selectedAddress});
}

async function buyPokerTokens() {
    const amount = document.getElementById("buyPokerAmount").value;
    const amountInWei = web3.utils.toWei(amount, 'ether');
    await miniCasino.methods.buyPokerTokens().send({from: ethereum.selectedAddress, value: amountInWei});
}

async function sellPokerTokens() {
    const amount = document.getElementById("sellPokerAmount").value;
    await miniCasino.methods.sellPokerTokens(amount).send({from: ethereum.selectedAddress});
}

