# 1 laboratorinis darbas, hash generatoriaus kūrimas

### Table of Contents
1. [Overview of the Algorithm](#overview-of-the-algorithm)
2. [Hash Generation Function is Deterministic](#hash-generation-function-is-deterministic)
3. [Custom Hash Function Efficiency](#custom-hash-function-efficiency)
4. [Collision Testing](#collision-testing)
5. [Avalanche Effect Testing](#avalanche-effect-testing)

---

### Overview of the algorithm
**Appending salt to the input:** The function takes the input string and appends a predefined salt value to it. This salt is a constant string `"nKd_n3aTsP3siT"`. 

**Initializing the hash value:** 
The function initializes a hash value using a prime number, `prime1 = 709607`. 

**Iterating over each char:** 
For every character in the salted input, the function performs a series of bitwise operations:
- It first calculates the character's ASCII value and performs bitwise operations (`<<` left shift and `>>` right shift) on the hash value.
- It then combines these shifted hash values with the ASCII value of the character.

**Adding length-based value:** 
After processing all characters, the function adds a value based on the length of the input (multiplied by `prime2 = 295099`) to the hash. This step ensures that strings of different lengths will produce different hashes.

**Generating hex hash output:** 
Finally, the function generates a 64-character hexadecimal string as the hash output:
- It iteratively modifies the hash value using bitwise operations involving `prime1`.
- For each iteration, it selects one hexadecimal digit (from the string `hex = "0123456789abcdef"`) based on the current hash value (using `hash % 16`) and appends it to the output string.
- This process is repeated 64 times to generate a 64-character long hash.
---

### Hash generation function is deterministic

The custom hash function can safely be considered deterministic, since a specific input always results in the same specific hash. This was confirmed by running the same input files multiple times, and they always produced the same hash.

---
### Custom hash function efficiency

Based on the image below we can see, that the custom hash algorithm holds up against the most popular ones in terms of speed (_the time is displayed in milliseconds_), but it might just be because of it's relative simplicity, which doesn't stop it from performing well enough in avalanche and collision testing. Speed testing is done using the provided _konstitucija.txt_ file.

![image](https://github.com/simces/vu-blockchain/assets/78842398/2d345e34-2cf4-412a-874c-c82dc3574073) 

![image](https://github.com/simces/vu-blockchain/assets/78842398/a493c5f8-032a-46c7-85fe-f350aa61ddbe)

---

### Collision testing

As I've mentioned before, the collision tests were also a success. After testing over a million pairs of inputs of different sizes, not a single collision was found. The inputs tested: `250 000` random strings of lengths `10, 100, 500, 1000`. And of course, it's no surprise that I didn't manage to find a collision in the other well known algorithms. 

![image](https://github.com/simces/vu-blockchain/assets/78842398/e03200ec-af41-4f00-8fda-ef26d738a38a)

---
### Avalanche effect testing

The initial tests of the avalanche effect were done using two `1500` character length inputs, where just one char is different, right in the middle of the file. Resulting hashes show that the custom hash generator has successfully passed the first test.

<p align="center">
  <img src="https://github.com/simces/vu-blockchain/assets/78842398/478fa65d-5205-418f-bef3-620b75cdfab4">
</p>

Secondary tests were a bit more automated, since I used a big generated file of `100 000` input pairs of different lengths (`10, 100, 500, 1000`), in which just one char was different (for example, a pair is `sKjB1nf9XK` and `sKfB1nf9XK`). 

<p align="center">
  <img src="https://github.com/simces/vu-blockchain/assets/78842398/83bdf730-4021-4597-88d4-0f61797ba9a4">
</p>

I think it's safe to say that these tests were also a success, since, on average, the hashes of the pairs were very different, and on rare ocassions – completely different (all 64 hex chars are different). 
