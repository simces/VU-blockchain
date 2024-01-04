# 4 laboratorinis darbas, išmanioji sutartis


### Initial version, testing with `Ganache`


After initializing the `rouletteToken` and `miniCasino`, we check for the current `rouletteToken` count, which returns a `0`

We can also check this by looking at the account, and it's pretty clear, that no transactions happened yet. 

<p align="center">
  <img src="https://github.com/simces/VU-blockchain/assets/78842398/194c10a0-734b-44b2-9a0a-8dd222ea2dc3">
</p>

After sending an instruction to buy `50 ETH` worth of tokens, we check the `rouletteToken` count again, which returns `500`, since in the contract the `BUY_PRICE = 0.01 ether;`

<p align="center">
  <img src="https://github.com/simces/VU-blockchain/assets/78842398/16115f5a-a7f8-424a-8089-f51b7c8f33fe">
</p>

After checking the picture above we can clearly see that the account has lost the funds, which are a bit more than previously mentioned `50 ETH`, since we had to pay for `gas`. The `miniCasino` didn't initialize those transactions, so it was sitting at an expected `50 ETH`. 

<p align="center">
  <img src="https://github.com/simces/VU-blockchain/assets/78842398/118bd553-e6ce-4299-9120-6fab47c7b2d1">
</p>

After selling the tokens back to the casino, the user was sitting at `98.68 ETH`, while the casino had `1.25 ETH`, which was a way to implement a house advantage, a typical thing in typical casinos. 

---

### Final-ish version

Once I managed to confirm that the actual contracts work as intended, it was just a matter of plugging them into an Ethereum test network, `Goerli`. 

![image](https://github.com/simces/VU-blockchain/assets/78842398/3833194c-f9b3-43c6-95ad-1821d1a107c1)

The good news – the `buying` and `selling` of the tokens work with `Metamask`, but I could not implement the actual games & the item store in time, to spend/earn those tokens. 
