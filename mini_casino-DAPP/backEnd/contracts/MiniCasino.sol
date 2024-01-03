// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

contract MiniCasino {
    uint256 public constant RATE = 100; // 100 tokens per 0.01 ETH
    mapping(address => uint256) public chipBalances;

    function buyChips(uint256 ethAmount) public payable {
        require(ethAmount >= 0.01 ether, "Minimum purchase is 0.01 ETH");
        require(msg.value == ethAmount, "Sent ETH must match the purchase amount");
        
        uint256 tokensToBuy = (ethAmount / 0.01 ether) * RATE;
        chipBalances[msg.sender] += tokensToBuy;
    }

    function getChipBalance() public view returns (uint256) {
        return chipBalances[msg.sender];
    }
}
