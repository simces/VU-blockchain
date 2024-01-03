// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

contract MiniCasino {
    mapping(address => uint256) public chipBalances;

    function buyChips() public payable {
        require(msg.value > 0, "Send ETH to buy chips");
        chipBalances[msg.sender] += msg.value;
    }

    function getChipBalance() public view returns (uint256) {
        return chipBalances[msg.sender];
    }
}
