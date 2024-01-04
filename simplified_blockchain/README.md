# 2 laboratorinis darbas, supaprastintos blokų grandinės kūrimas

### users.txt

We generate `1000` users with the properties `name`, `publicKey` and `balance` as such:

```
----------------------------------------------------------------------
Name: member1
Public key: d89ade13f8fe73fa9cdc396e5f2e9e7519890e96a1de3390ed066685196a73da
Balance: 31304
----------------------------------------------------------------------
```

---

### transactions.txt

Once we have the big list of users, we generate a pool of `10000` transactions between them, with the properties `transactionId`, `senderKey`, `receiverKey` and the `amount` as such:

```
----------------------------------------------------------------------
Transaction ID: cfaf44c551900e51f0666cf2e987f040c590eb4e13bafcd40e9e77717940857f
Sender public key: f2890204ed2a1715b6a194eb42cb06c355900660a57319a98bc515b2ad6c73bc
Receiver public key: cbcfa9062264e5713fedc9266e71dabed85fe75f264ede37d285d4a9a5717ba9
Transaction amount: 10414
----------------------------------------------------------------------
```

---

### block.txt

We then create a block, and populate it with transactions from our previously mentioned transaction pool, clearing the pool as we go. 

The block itself stores info such as `blockNr`, `blockHash`, `prevBlockHash`, `timestamp`, `difficulty`, `merkleHash`, `version`, `nonce`, `transactionNr`, `transactionVolume` as well as all the transactions that are in it. 

```
Block number: 6
Block hash: 00000c39896e7bcb4a392c3d83f626281592089c796a92e775dc3b44c598f2e9
Previous block hash: 0000020622440287fa985159cd200422cbed28fe59abe53f4eb226a98b64adeb
Mined on: Jan 04, 2024, 05:45:28 AM
Difficulty: 5
Merkle root hash: f285b0a15171b04af0cb442c7d0a1590a39664c5590c9087da7bafa17f8b64e3
Version: 1
Nonce: 7759
Transaction number: 100
Transactions volume: 755693
```

---

### remainingTransactions.txt

Once that's done, we then check to see, if all the transactions from the pool have been added to blocks, and deleted. 

```

[null]

```

