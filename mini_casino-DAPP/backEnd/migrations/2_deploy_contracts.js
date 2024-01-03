var BlackjackToken = artifacts.require("BlackjackToken");
var RouletteToken = artifacts.require("RouletteToken");
var PokerToken = artifacts.require("PokerToken");
var MiniCasino = artifacts.require("MiniCasino");

module.exports = async function(deployer, network, accounts) {
  await deployer.deploy(BlackjackToken);
  const blackjackToken = await BlackjackToken.deployed();

  await deployer.deploy(RouletteToken);
  const rouletteToken = await RouletteToken.deployed();

  await deployer.deploy(PokerToken);
  const pokerToken = await PokerToken.deployed();

  await deployer.deploy(MiniCasino, blackjackToken.address, rouletteToken.address, pokerToken.address);
  const miniCasino = await MiniCasino.deployed();

  const amountOfTokensForCasino = 1000000;
  await blackjackToken.transfer(miniCasino.address, amountOfTokensForCasino);
  await rouletteToken.transfer(miniCasino.address, amountOfTokensForCasino);
  await pokerToken.transfer(miniCasino.address, amountOfTokensForCasino);
};