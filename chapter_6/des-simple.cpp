#include <bits/stdc++.h>
using namespace std;

const int InitialPermutation[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

const int FinalPermutation[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

const int ExpansionTable[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

const int StraightPermutation[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};


const int SBox[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 0, 5},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 15, 3, 12, 0},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 4, 15, 2, 8, 1, 6, 11, 5, 0, 12, 10, 9},
        {13, 0, 11, 5, 12, 2, 15, 13, 8, 4, 14, 10, 3, 7, 4, 12},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 2, 10, 1, 7, 6, 4, 10, 13, 0, 5, 11, 8, 6}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 5, 12, 2, 15, 13, 8, 4, 14, 10, 3, 7, 4, 12},
        {7, 13, 14, 3, 4, 15, 2, 8, 1, 6, 11, 5, 0, 12, 10, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 6, 11, 13, 0, 5, 3, 4, 9, 15, 10, 8, 12}
    }
};

bitset<64> hex_to_bits(const string& hex) {
    bitset<64> bits;
    for (size_t i = 0; i < hex.length(); ++i) {
        int val = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : (hex[i] - 'a' + 10);
        for (int j = 3; j >= 0; --j) {
            bits[(i * 4 + 3 - j)] = (val >> j) & 1;
        }
    }
    return bits;
}

// Convert binary to hex
string bits_to_hex(const bitset<64>& bits) {
    string hex = "";
    for (int i = 0; i < 16; ++i) {
        int val = 0;
        for (int j = 0; j < 4; ++j) {
            val = (val << 1) | bits[i * 4 + j];
        }
        hex += (val < 10) ? (char)('0' + val) : (char)('a' + val - 10);
    }
    return hex;
}

// Permutation
bitset<32> permute32(const bitset<32>& in, const int table[32]) {
    bitset<32> out;
    for (int i = 0; i < 32; ++i) {
        out[i] = in[table[i] - 1];
    }
    return out;
}

bitset<48> permute48(const bitset<32>& in, const int table[48]) {
    bitset<48> out;
    for (int i = 0; i < 48; ++i) {
        out[i] = in[table[i] - 1];
    }
    return out;
}

// S-box substitution
bitset<32> sbox_substitute(const bitset<48>& in) {
    bitset<32> out;
    for (int i = 0; i < 8; ++i) {
        int row = (in[i*6] << 1) | in[i*6 + 5];
        int col = (in[i*6 + 1] << 3) | (in[i*6 + 2] << 2) | (in[i*6 + 3] << 1) | in[i*6 + 4];
        int val = SBox[i][row][col];
        for (int j = 0; j < 4; ++j) {
            out[i*4 + 3 - j] = (val >> j) & 1;
        }
    }
    return out;
}

// DES round (simplified, using same key for all rounds)
void des_round(bitset<32>& left, bitset<32>& right, const bitset<48>& key) {
    bitset<48> expanded = permute48(right, ExpansionTable);
    bitset<48> xored = expanded ^ key;
    bitset<32> substituted = sbox_substitute(xored);
    bitset<32> permuted = permute32(substituted, StraightPermutation);
    bitset<32> newLeft = right;
    bitset<32> newRight = left ^ permuted;
    left = newLeft;
    right = newRight;
}

// Main DES encryption
string des_encrypt(const string& plaintext_hex, const string& key_hex) {
    bitset<64> plaintext = hex_to_bits(plaintext_hex);
    
    // Initial Permutation
    bitset<64> permuted;
    for (int i = 0; i < 64; ++i) {
        permuted[i] = plaintext[InitialPermutation[i] - 1];
    }
    
    bitset<32> left(permuted.to_string().substr(0, 32));
    bitset<32> right(permuted.to_string().substr(32));
    
    // Extract key (simplified: just use first 48 bits)
    bitset<48> key;
    bitset<64> key_bits = hex_to_bits(key_hex);
    for (int i = 0; i < 48; ++i) {
        key[i] = key_bits[i];
    }
    
    // 16 rounds
    for (int round = 0; round < 16; ++round) {
        des_round(left, right, key);
    }
    
    // Combine right and left (note the order)
    bitset<64> combined;
    for (int i = 0; i < 32; ++i) {
        combined[i] = right[i];
        combined[i + 32] = left[i];
    }
    
    // Final Permutation
    bitset<64> ciphertext;
    for (int i = 0; i < 64; ++i) {
        ciphertext[i] = combined[FinalPermutation[i] - 1];
    }
    
    return bits_to_hex(ciphertext);
}

int main() {
    string plaintext, key;
    cout << "Enter plaintext (64-bit hex):" << endl;
    cin >> plaintext;
    cout << "Enter key (64-bit hex):" << endl;
    cin >> key;
    
    string ciphertext = des_encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;
    
    return 0;
}
