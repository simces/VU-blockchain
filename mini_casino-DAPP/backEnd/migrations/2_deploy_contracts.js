const MiniCasino = artifacts.require("MiniCasino");

module.exports = function (deployer) {
  deployer.deploy(MiniCasino);
};
