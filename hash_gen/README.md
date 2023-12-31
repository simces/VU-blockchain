# 1 laboratorinis darbas, hash generatoriaus kūrimas

### Table of Contents
1. [Overview of the algorithm](#overview-of-the-algorithm)
2. [Hash generation function is deterministic](#hash-generation-function-is-deterministic)
3. [Custom hash function efficiency](#custom-hash-function-efficiency)
4. [Collision testing](#collision-testing)
5. [Avalanche effect testing](#avalanche-effect-testing)
6. [Hash algorithm comparison](#hash-algorithm-comparison)

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

---

### Hash algorithm comparison

In an attempt to dive a bit deeper into the comparisons, I've decided to compare all the algorithms I could get my hands on. Some of them are from the time when I took the course initially in **2021**, and some of them are from **2023**. Also, I would like to apologize in advance if I imported the algorithms incorrectly, which would cause them to slow down/malfunction, and not display accurate results. 

All the algorithms (and their authors) from 2021:

1. [metroff](https://github.com/metroff/VU_BC_Hash/blob/main/include/hash.cpp)
2. [Miautawn](https://github.com/Miautawn/VU-blockchain/blob/master/hash-generator/helpers/hash.cpp)
3. [Vabasou](https://github.com/Vabasou/Hash_Function/blob/master/hash.cpp)
4. [VadimasKo](https://github.com/VadimasKo/HashGenerator/blob/master/Main.cpp)
5. [MaciukasM](https://github.com/MaciukasM/VU-hash-function/blob/main/funkcijos.cpp)
6. [Paulius-U](https://github.com/Paulius-U/Blok-grandini-technologijos/blob/main/Hash.cpp)

The algorithms (and their authors) from 2023:

7. [linccer](https://github.com/linccer/blockchain/blob/main/main.cpp)
8. [TheFeish](https://github.com/TheFeish/Hash/blob/V0.1/Hash/hashFunc.cpp)
9. [KlaidasK](https://github.com/KlaidasK/Blockchain/blob/main/v0.1.cpp)
10. [JFour404](https://github.com/JFour404/blockChainTech/blob/main/src/hashF.cpp)

The first quick test – checking whether the hash functions are deterministic. Apart from one interesting result `0000, asd`, all of the hashes passed the initial check. Specific inputs always resulted in the same specific outputs, and they all looked different enough to not cause a concern. 

The second test – speed. In an attempt to make testing as fair as possible, the program runs through a specific number of lines in the `konstitucija.txt` file 10 times, and then I repeat these tests 3 times to get the most accurate results possible. 

![image](https://github.com/simces/VU-blockchain/assets/78842398/23aa4590-1c18-4b6d-bb93-f79a5cd1beae)

Based on the initial results it was clear that we had a lot of different approaches to the solution, since the speeds of the hash functions were so vastly different. When making the graph I decided to remove some of the main outliers, because otherwise, the graphs wouldn't be very informative. 

![image](https://github.com/simces/VU-blockchain/assets/78842398/de682de2-1c46-4460-9054-3a1a986da4bb)

And after averaging everything out, we can find the overall fastest algorithms. It's important to mention, that a fast algorithm isn't necessarily better, since it may be more vulnerable cryptographically, which is the most important thing when it comes to hash functions. 

![image](https://github.com/simces/VU-blockchain/assets/78842398/7bf415af-af4b-4465-9c77-4f45e772a8a2)

The next step – collision testing. To make it fair for all the different algorithms, they all used the same testing file, consisting of `100 000` different string pairs, of random lengths. 






