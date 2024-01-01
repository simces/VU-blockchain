#include "generators.h"




// -----------------------------------------------------------------------------------------------
// myhash gen
// -----------------------------------------------------------------------------------------------
std::string myHashGen(std::string hashInput) {

    // salt'as
    const std::string salt = "nKd_n3aTsP3siT";
    hashInput += salt;

    const unsigned long long prime1 = 709607;
    const unsigned long long prime2 = 295099;
    unsigned long long hash = prime1;

    for (char c : hashInput) {
        hash ^= (hash << 5) + (hash >> 2) + static_cast<unsigned int>(c);
    }

    hash += prime2 * hashInput.length();

    std::string hashOutput;
    const std::string hex = "0123456789abcdef";

    // hash generavimas (64 chars)
    for (int i = 0; i < 64; i++) {
        hash = (hash * prime1) ^ (hash >> 3);
        hashOutput += hex[hash % 16];
    }

    return hashOutput;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/metroff/VU_BC_Hash
// https://github.com/metroff/VU_BC_Hash/blob/main/include/hash.cpp
// -----------------------------------------------------------------------------------------------
template <typename I> std::string toHexString(I w, size_t hex_len = sizeof(I)<<1) {
    static const char* digits = "0123456789abcdef";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

// Bits rotation
int leftRotate(int n, unsigned int d) {
    return (n << d)|(n >> (32 - d));
}

unsigned int rightRotate(unsigned int n, unsigned int d)
{
    return (n >> d)|(n << (32 - d));
}

// Main hash function
std::string metroffHashGen(const std::string& input) {
    std::string output = "";
    // Initial values
    unsigned int hexes[8] = {3189621198, 405587210, 2844532716, 1761483275, 152458759, 2779224377, 4151057064, 1000842129};

    int length = input.length();

    int num = 1153;
    int sum = num;

    // Number transformations 
    for (int i = 0; i < length; i++){
        sum = num|(int(input[i])%num);
        num = leftRotate(num, 5) + int(input[i]) - num;
    }
    // Initial value rotation more "random" values
    for (int i = 1; i < sum % 100; i++) {
         hexes[i%8] = rightRotate(hexes[i%8], 16);
    }
    // More mixups to reduce collisions and for avalanche
    for (int i = 0; i < 8; i++) {
        hexes[i] ^= (~hexes[7-i]) * num;
        hexes[7-i] |= (~hexes[i]) * sum;
    }
    // Converting values to string
    for (int i = 0; i < 8; i++) {
        output += toHexString<unsigned int>(hexes[i]);
    }

    return output;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/Miautawn/VU-blockchain/tree/master/hash-generator
// https://github.com/Miautawn/VU-blockchain/blob/master/hash-generator/helpers/hash.cpp
// -----------------------------------------------------------------------------------------------
std::string integer_to_hex(unsigned int input) {
    static const char* digits = "0123456789abcdef";
    std::string result;
    for (int i = (sizeof(int) * 2) - 1; i >= 0; --i) {
        result += digits[(input >> (i * 4)) & 0xF];
    }
    return result;
}


// hashing function
std::string miautawnHashGen(std::string input) {

    // initialize the hex variables
    unsigned int HEX[8] = {1399877492, 1818847080, 1949048949, 1747722349, 1869573740, 1768384628, 0740324712, 0544766072};

    const unsigned int input_length = input.length();
    
    // initialize the bitset arrays for the input and their copies
    std::bitset<32> bit_map[input_length];
    std::bitset<32> copy;

    // variables for the sum and hex
    int sum = 0;
    std::string full_hex = "";

    //add the input to bitset array and encode it
    for (int i = 0; i < input_length; i++) {

        
        bit_map[i] = input[i];
        const unsigned long char_value = bit_map[i].to_ulong();
        sum += char_value;

        // create a copy of the char bitset
        copy = bit_map[i];
        
        // reverse the char bitset
        std::string a = bit_map[i].to_string();
        std::reverse(a.begin(), a.end());
        bit_map[i] = std::bitset<32>(a);


        // push the bits to the left and right
        bit_map[i] >>= ((char_value + sum + input_length) % 16);
        copy <<= ((char_value + sum + input_length) % 32);

        // merge the bits of the copy and the char
        bit_map[i] ^= copy;

        // shuffle the hex variable with the resulting char
        HEX[i % 8] ^= bit_map[i].to_ulong();
    }


    // make an avelanche effect
    for (int i = 0; i < 4; i++) {
        
        HEX[4+i] ^= HEX[i];
        HEX[i+1] ^= HEX[i+4];

        full_hex += integer_to_hex(HEX[i]);
        full_hex += integer_to_hex(HEX[i+1]);
    }

    return full_hex;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/Vabasou/Hash_Function
// https://github.com/Vabasou/Hash_Function/blob/master/hash.cpp
// -----------------------------------------------------------------------------------------------
std::string vabasouHashGen(const std::string &input) {
    const int main = 1097;

    unsigned int seed = main;
    for (char c : input) {
    seed = (seed << 7) - seed + int(c) + 47 * input.length();
    }

    std::string seedString = std::to_string(seed);
    int seedStringSize = seedString.size();

    std::string pattern = "0123456789abcdef";
    int patternSize = pattern.size();

    std::string hash;
    int changingNumber = 31;
    unsigned int index = main * seed;
    for (int i = 0; i < 64; i++) {
        index += seedString[changingNumber % seedStringSize] + i * main / (main & 5);
        hash += pattern[index % patternSize];
        changingNumber++;
    }
    return hash;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/VadimasKo/HashGenerator
// https://github.com/VadimasKo/HashGenerator/blob/master/Main.cpp
// -----------------------------------------------------------------------------------------------
const std::string initialKey = "1011110011011001010101101011001011000111001111110100101110010001011100000001011010101011010100111001001100011111010001000011111010101000000110010001110010110011010010101010010110001001110001001011110100000010110010000101110100100001101111010100011110001010";
std::map<std::string, std::string> hexMap {
  {"0001", "1"},
  {"0010", "2"},
  {"0011", "3"},
  {"0100", "4"},
  {"0101", "5"},
  {"0110", "6"},
  {"0111", "7"},
  {"1000", "8"},
  {"1001", "9"},
  {"1010", "A"},
  {"1011", "B"},
  {"1100", "C"},
  {"1101", "D"},
  {"1110", "E"},
  {"1111", "F"},
};

std::vector<std::string> stringSplit(std::string input) {
  int splitSize = 64;
  std::vector<std::string> splits;

  for(int i = 0; i < input.size(); i+=splitSize) {
    splits.push_back(input.substr(i,splitSize));
  }

  return splits;
}

void convertToBitStrings(std::vector<std::string> &splits) {
  std::vector<std::string> bufferVector;

  for(std::string split : splits) {
    std::string buffer;
    for(char symbol : split) {
      buffer.append(std::bitset<4>(symbol).to_string());
    }
    if(buffer.size() < 256) buffer.append(std::string(256 - buffer.size(),'0'));
    bufferVector.push_back(buffer);
  }

  splits = bufferVector;
}


std::string andGate(std::string input1, std::string input2) {
  std::string outPut;
  for(int i = 0; i<input1.size(); i++) {
    (input1[i] == input2[i] == 1) ? outPut.push_back('1') : outPut.push_back('0');
  }
  return outPut;
}

void shiftRight(std::string &input) {
  input.insert(input.begin(), input[input.size()-1]);
  input.pop_back();
}

std::string mergeBitStrings(std::vector<std::string> &splits) {
  if(splits.size() < 3) splits.push_back(initialKey);

  std::string mergedStrings = splits[0];
  for(std::string split: splits) {
    shiftRight(split);
    mergedStrings = andGate(mergedStrings, split);
  }
  shiftRight(mergedStrings);
  return mergedStrings;
}

std::string binaryToHex(std::string input) {
  std::string output;
  for(int i = 0; i < input.size(); i+=4) {
    output.append(hexMap[input.substr(i,4)]);
  }
  return output;
}


std::string vadimasKoHashGen(const std::string &input) {
    std::vector<std::string> splits = stringSplit(input);
    convertToBitStrings(splits);
    std::string mergedBitString = mergeBitStrings(splits);
    std::string hashOutput = binaryToHex(mergedBitString);

    return hashOutput;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/MaciukasM/VU-hash-function
// https://github.com/MaciukasM/VU-hash-function/blob/main/funkcijos.cpp
// -----------------------------------------------------------------------------------------------
#define M_PI 3.14159265358979323846

std::string maciukasMHashGen(std::string duomenys)
{
    std::string hash; // cia saugojamas hashas
    unsigned int temp = 12345; //kintamasis, kuriame laikomas skaicius, kuri vis keisime dauginant is ivairiu skaiciu (is pradziu sudauginsime su simboliu ascii vertemis ir pan.)
    int ascii = 0; //skaicius gautas is 'temp', kuri naudosim grazinti kokia nors ascii reiksme i hasha

    unsigned int sum = 0; //ascii reiksmiu suma (testavimui)
    //int s = 10000;

    for(int i = 0; i<duomenys.length(); i++) //input'as keicia pati skaiciu
    {
        sum += int(duomenys[i]); //(testavimui)
        temp = (temp * (int(duomenys[i])+2)*2)+i+sum;
        temp<<2;
        temp = temp*temp*temp;

        //if(i == 1022 || i == 1023 || i == 1024 || i == 1025 || i == 1062 || i == 1063) cout<<"i: "<<i<<" "<<temp<<" "<<int(duomenys[i])+2<<endl;
    }

    //cout<<"s: "<<s<<endl; //(testavimui)

    std::string paverstasSkaicius; //vertimui skaiciu i string
    char simbolis; //char'as kuris eis i hasha (gaunamas is 'ascii' reiksmes)

    //hash'o sudarymas
    for(int i = 0; i<64; i++)
    {
        temp = temp * M_PI;
        paverstasSkaicius = std::to_string(temp);
        ascii = (paverstasSkaicius[1]*paverstasSkaicius[3] + paverstasSkaicius[4]*paverstasSkaicius.back() + paverstasSkaicius[2]*i + temp/2) % 16 + 48; //gaunam ascii reiksmes 48-63
        //if(i==0) cout<<"a: "<<temp<<endl; //testavimui
        if (ascii>57) ascii += 39; //kad gauti raides a-f
        simbolis = ascii;
        hash += simbolis;
    }
    return hash;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/Paulius-U/Blok-grandini-technologijos
// https://github.com/Paulius-U/Blok-grandini-technologijos/blob/main/Hash.cpp
// -----------------------------------------------------------------------------------------------
bool Pirminis(int x) {
    if (x <= 1) return false;
    if (x % 2 == 0) return x == 2;
    for (int i = 3; i <= sqrt(x); i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

std::string pauliusUHashGen(const std::string& duomenys) {
    std::bitset<256> out = 0;
    unsigned int temp = 12345;
    int pirm[10000], kiek = 0;

    for (int i = 0; i <= 100000; i++) {
        if (Pirminis(i)) {
            pirm[kiek] = i;
            kiek++;
        }
    }

    for (size_t in = 0; in < duomenys.length(); in++) {
        for (int i = 0; i < 256; i++) {
            std::bitset<256> t = duomenys[in];
            t ^= pirm[(i * in) % kiek];
            t <<= i;
            out ^= t;

            if (in > 16) {
                out[(in + 1) % 256] = out[i];
                out.flip(8);
            } else if (in > 8) {
                out[in - 4] = out[i];
                out.flip(4);
            } else if (in > 4) {
                out[in + 16] = out[i];
                t <<= 5;
            } else {
                out[in + 5] = out[i];
                out.flip(9);
                t <<= 3;
            }

            if (i % 3 == 0) {
                out[(in + 24) % 256] = out[i];
                out.flip(2);
                t <<= 4;
            } else if (i % 5 == 0) {
                out[in % 256] = out[i];
                t >>= 3;
            } else {
                out.flip(7);
                out[in % 256] = out[i * 18];
                t <<= 6;
            }

            if (i == 2) {
                out[(in + 14) % 256] = out[i + 6];
                out.flip(5);
                t >>= 1;
            }

            if (i + in > 16) {
                out[(in + 4) % 256] = out[i * 9];
                t <<= 3;
                out[(in * 10) % 256] = out[i + 4];
                t >>= 2;
                out[(in + 5) % 256] = out[i + 12];
                t <<= 7;
            }
        }
    }

    std::string hash;
    std::string temp_str = out.to_string();
    for (int i = 0; i < 64; i++) {
        std::bitset<4> bss1(temp_str.substr(i * 4, 4));
        if (bss1.to_ulong() <= 9) {
            hash += static_cast<char>(bss1.to_ulong() + '0');
        } else {
            hash += static_cast<char>(bss1.to_ulong() + 'a' - 10);
        }
    }

    return hash;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/linccer/blockchain
// https://github.com/linccer/blockchain/blob/main/main.cpp
// -----------------------------------------------------------------------------------------------
void add(std::vector<int>& vec, unsigned long long x) {
    unsigned long long carry = x;

    for (auto &i : vec) {
        carry += i;
        i = carry % 16;
        carry /= 16;
    }

    while (carry > 0) {
        vec.push_back(carry % 16);
        carry /= 16;
    }
}

void square(std::vector<int>& vec) {
    std::vector<int> result(vec.size() * 2, 0);

    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec.size(); ++j) {
            result[i + j] += vec[i] * vec[j];
        }
    }

    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] >= 16) {
            if (i + 1 < result.size()) {
                result[i + 1] += result[i] / 16;
            }
            result[i] %= 16;
        }
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    vec = result;
}

// Main Hash Function
std::string linccerHashGen(const std::string& input) {
    const int X = 73;
    std::vector<int> value;
    unsigned long long unicode;

    for (char ch : input) {
        unicode = static_cast<int>(ch);
        unicode = unicode * std::pow(X, (input.length() % 10));
        add(value, unicode);
    }

    while (value.size() < 64) {
        square(value);
    }

    std::string output;
    for (int i : value) {
        if (i < 10) output += std::to_string(i);
        else {
            char hexChar = 'a' + (i - 10);
            output += hexChar;
        }
    }

    std::reverse(output.begin(), output.end());

    while (output.length() > 64) {
        int position = output.length() % 10;
        output.erase(position, 1);
    }

    return output;
}



// -----------------------------------------------------------------------------------------------
// https://github.com/TheFeish/Hash
// https://github.com/TheFeish/Hash/blob/V0.1/Hash/hashFunc.cpp
// -----------------------------------------------------------------------------------------------
unsigned int hashDec(int p, int m, std::string s) {
	unsigned int hash = 0;
	int pow = p;
	for (auto c : s) {
		hash = (hash + c * pow) % m;
		pow = (pow * p) % m;

	}
	return hash;
}

std::string hashHex(unsigned int h1, unsigned int h2) {
	std::stringstream hash;

	std::default_random_engine rng1{ h1 };
	std::default_random_engine rng2{ h2 };

	std::uniform_int_distribution<> dist{ 0, 15 };

	for (int i = 0; i < 32; i++) {
		hash << std::hex << dist(rng1);
		hash << std::hex << dist(rng2);
	}

	return hash.str();
}

std::string theFeishHashGen(std::string s) {
	return hashHex(hashDec(257, (int)(1e9 + 7), s), hashDec(263, (int)(1e9 + 9), s));
}


// -----------------------------------------------------------------------------------------------
// https://github.com/KlaidasK/Blockchain
// https://github.com/KlaidasK/Blockchain/blob/main/v0.1.cpp
// -----------------------------------------------------------------------------------------------
std::string klaidasKHashGen(const std::string& input) {

    if (input.empty()) {
        return "Nera teksto";
    }

   
    unsigned char hash[32];

    int sum=0;
    int k = 0;
    
    for (int i = 0; i < 32; i++){

        for (int ii = 0; ii < input.length(); ii++) {
            sum = sum + static_cast<int>(input[ii]) * 23^k;
            
            hash[i] ^= sum;
        }
        k++;
        
    }

    // Konvertavimas hash į hex 64 ilgio
    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}




// -----------------------------------------------------------------------------------------------
// https://github.com/JFour404/blockChainTech/tree/main
// https://github.com/JFour404/blockChainTech/blob/main/src/hashF.cpp
// -----------------------------------------------------------------------------------------------
string jFour404HashGen(string text){
    vector<int> hash = hashNo1(text);
    string hexHash = binaryToHex(hash);
    
    return hexHash;
}

vector<int> hashNo1(string text){
    int i = 0, seedSum = 0;
    vector <int> hash = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0};
    
    for (char symbol: text){
            wint_t seed = seedGen (symbol);
            seedSum += seed;
        }

    size_t textSize = text.size(); 
    vector<int> lag = sequenceGen (textSize, seedSum);
    vector<int> newHash;

    for (char symbol: text) {
        wint_t seed = seedGen (symbol);
        int seq = lag[i];
        newHash = bitsGen(seed);
        shiftRight (newHash, seq);
        hash = hashTornado (hash, newHash);
        i++;
    }

    return hash;
}



void baseHash (vector<int>& eulerisBi) {
    char skc;
    string konst = "e.txt";
    
    ifstream open_f("../data/" + konst);
    if (!open_f) throw runtime_error("Failas nerastas arba nepavyko atidaryti.");

    while (open_f.get(skc)) {
        if (isdigit(skc)) {
            int intSkc = skc - '0';
            if (intSkc >= 5) eulerisBi.push_back(1);
            else eulerisBi.push_back(0);
        }
    }

    open_f.close(); 
}

vector<int> sequenceGen (unsigned int textSize, int seedSum){
    mt19937 generator(textSize + seedSum);
    uniform_int_distribution<int> distribution(0, 255);

    vector<int> randomSeq;

    for (int i = 0; i < textSize; ++i) {
        int seq = distribution(generator); 
        randomSeq.push_back(seq);
    }

    return randomSeq;
}

wint_t seedGen (char symbol){
    wint_t seed = static_cast<wint_t>(symbol);
    return seed;
}

vector <int> bitsGen (unsigned int seed){
    mt19937 generator((seed));
    bernoulli_distribution distribution(0.5);

    vector<int> randomBits;

    for (int i = 0; i < 256; ++i) {
        int bit = distribution(generator); 
        randomBits.push_back(bit);
    }

    return randomBits;
}

void shiftRight (vector<int>& hash, int seq){
    if (hash.empty() || seq <= 0) {
        return;
    }

    int size = hash.size();
    seq %= size;

    vector<int> temp(size);

    for (int i = 0; i < size; ++i) {
        int newIdex = (i+seq) % size;
        temp[newIdex] = hash[i];
    }

    hash = temp;
}

vector <int> hashTornado (vector<int> prevHash, vector<int> newHash){
    vector<int> hash;
    int size = prevHash.size();

    for (int i = 0; i < size; ++i){
        if (prevHash[i] == 0 && newHash[i] == 0) 
            hash.push_back(0);
        else
        if (prevHash[i] == 0 && newHash[i] == 1) 
            hash.push_back(1);
        else
        if (prevHash[i] == 1 && newHash[i] == 0) 
            hash.push_back(1);
        else
        if (prevHash[i] == 1 && newHash[i] == 1) 
            hash.push_back(0);
    }

    return hash;
}

//binaryHash -> hexHash
string binaryToHex(vector <int> hashBi) {
    int i = 0;
    string temp1;
    string temp4 = "";
    int tempInt;
    string tempHex;

    for (int d : hashBi) {
        if (i==3) {
            temp1 = to_string(d);
            temp4 += temp1;
            
            tempInt = stoi(temp4);

                switch (tempInt) {
                    case 0:
                        tempHex += "0";
                        break;
                    case 1:
                        tempHex += "1";
                        break;
                    case 10:
                        tempHex += "2";
                        break;
                    case 11:
                        tempHex += "3";
                        break;
                    case 100:
                        tempHex += "4";
                        break;
                    case 101:
                        tempHex += "5";
                        break;
                    case 110:
                        tempHex += "6";
                        break;
                    case 111:
                        tempHex += "7";
                        break;
                    case 1000:
                        tempHex += "8";
                        break;
                    case 1001:
                        tempHex += "9";
                        break;
                    case 1010:
                        tempHex += "a";
                        break;
                    case 1011:
                        tempHex += "b";
                        break;
                    case 1100:
                        tempHex += "c";
                        break;
                    case 1101:
                        tempHex += "d";
                        break;
                    case 1110:
                        tempHex += "e";
                        break;
                    case 1111:
                        tempHex += "f";
                        break;
                    default:
                        tempHex += "0";
                
                }

            temp4 = "";
            i = 0;
        } else {
            temp1 = to_string(d);
            temp4 += temp1;
            i++;
        } 
    } 

    return tempHex;
}


