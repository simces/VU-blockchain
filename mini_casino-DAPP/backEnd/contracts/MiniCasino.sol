// SPDX-License-Identifier: MIT
pragma solidity 0.8.19;

import "./BlackjackToken.sol";
import "./RouletteToken.sol";
import "./PokerToken.sol";

contract MiniCasino {
    BlackjackToken public blackjackToken;
    RouletteToken public rouletteToken;
    PokerToken public pokerToken;

    uint256 public constant BUY_PRICE = 0.1 ether;      // essentially it's 
    uint256 public constant SELL_PRICE = 0.0975 ether;  // a house advantage. 

    constructor(address blackjackTokenAddress, address rouletteTokenAddress, address pokerTokenAddress) {
        blackjackToken = BlackjackToken(blackjackTokenAddress);
        rouletteToken = RouletteToken(rouletteTokenAddress);
        pokerToken = PokerToken(pokerTokenAddress);
    }

    function buyBlackjackTokens() public payable {
        uint256 tokensToBuy = msg.value / BUY_PRICE;
        require(blackjackToken.balanceOf(address(this)) >= tokensToBuy, "Not enough Blackjack tokens in the reserve");
        blackjackToken.transfer(msg.sender, tokensToBuy);
    }

    function sellBlackjackTokens(uint256 tokensToSell) public {
        uint256 etherToReturn = tokensToSell * SELL_PRICE;
        require(blackjackToken.balanceOf(msg.sender) >= tokensToSell, "Not enough Blackjack tokens to sell");
        require(address(this).balance >= etherToReturn, "Not enough Ether in the reserve");
        blackjackToken.transferFrom(msg.sender, address(this), tokensToSell);
        payable(msg.sender).transfer(etherToReturn);
    }

    function buyRouletteTokens() public payable {
        uint256 tokensToBuy = msg.value / BUY_PRICE;
        require(rouletteToken.balanceOf(address(this)) >= tokensToBuy, "Not enough Roulette tokens in the reserve");
        rouletteToken.transfer(msg.sender, tokensToBuy);
    }

    function sellRouletteTokens(uint256 tokensToSell) public {
        uint256 etherToReturn = tokensToSell * SELL_PRICE;
        require(rouletteToken.balanceOf(msg.sender) >= tokensToSell, "Not enough Roulette tokens to sell");
        require(address(this).balance >= etherToReturn, "Not enough Ether in the reserve");
        rouletteToken.transferFrom(msg.sender, address(this), tokensToSell);
        payable(msg.sender).transfer(etherToReturn);
    }

    function buyPokerTokens() public payable {
        uint256 tokensToBuy = msg.value / BUY_PRICE;
        require(pokerToken.balanceOf(address(this)) >= tokensToBuy, "Not enough Poker tokens in the reserve");
        pokerToken.transfer(msg.sender, tokensToBuy);
    }

    function sellPokerTokens(uint256 tokensToSell) public {
        uint256 etherToReturn = tokensToSell * SELL_PRICE;
        require(pokerToken.balanceOf(msg.sender) >= tokensToSell, "Not enough Poker tokens to sell");
        require(address(this).balance >= etherToReturn, "Not enough Ether in the reserve");
        pokerToken.transferFrom(msg.sender, address(this), tokensToSell);
        payable(msg.sender).transfer(etherToReturn);
    }

    // Fallback functions
    receive() external payable {}
    fallback() external payable {}
}