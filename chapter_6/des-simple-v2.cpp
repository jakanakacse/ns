#include <bits/stdc++.h>
using namespace std;

// DES Permutation tables
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

// S-boxes
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

// Convert character to 8 bits
bitset<8> char_to_bits(char c) {
    return bitset<8>(c);
}

// Convert 8 bits to character
char bits_to_char(bitset<8> bits) {
    return (char)bits.to_ullong();
}

// Permutation for 32 bits
bitset<32> permute32(const bitset<32>& in, const int table[32]) {
    bitset<32> out;
    for (int i = 0; i < 32; ++i) {
        out[i] = in[table[i] - 1];
    }
    return out;
}

// Permutation for 48 bits
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

// DES round
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
string des_encrypt(const string& plaintext, const string& key) {
    // Convert plaintext to bits
    bitset<64> plaintext_bits;
    for (int i = 0; i < 8; ++i) {
        bitset<8> byte = char_to_bits(plaintext[i]);
        for (int j = 0; j < 8; ++j) {
            plaintext_bits[i * 8 + j] = byte[j];
        }
    }
    
    // Convert key to bits
    bitset<64> key_bits;
    for (int i = 0; i < 8; ++i) {
        bitset<8> byte = char_to_bits(key[i]);
        for (int j = 0; j < 8; ++j) {
            key_bits[i * 8 + j] = byte[j];
        }
    }
    
    // Initial Permutation
    bitset<64> permuted;
    for (int i = 0; i < 64; ++i) {
        permuted[i] = plaintext_bits[InitialPermutation[i] - 1];
    }
    
    bitset<32> left, right;
    for (int i = 0; i < 32; ++i) {
        left[i] = permuted[i];
        right[i] = permuted[i + 32];
    }
    
    // Extract 48-bit key
    bitset<48> round_key;
    for (int i = 0; i < 48; ++i) {
        round_key[i] = key_bits[i];
    }
    
    // 16 rounds
    for (int round = 0; round < 16; ++round) {
        des_round(left, right, round_key);
    }
    
    // Combine right and left
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
    
    // Convert bits back to string
    string result = "";
    for (int i = 0; i < 8; ++i) {
        bitset<8> byte;
        for (int j = 0; j < 8; ++j) {
            byte[j] = ciphertext[i * 8 + j];
        }
        result += bits_to_char(byte);
    }
    
    return result;
}

int main() {
    string plaintext, key;
    cout << "Enter plaintext (8 characters): ";
    cin >> plaintext;
    cout << "Enter key (8 characters): ";
    cin >> key;
    
    if (plaintext.length() != 8 || key.length() != 8) {
        cout << "Error: plaintext and key must be exactly 8 characters!" << endl;
        return 1;
    }
    
    string ciphertext = des_encrypt(plaintext, key);
    cout << "Ciphertext (hex): ";
    for (char c : ciphertext) {
        cout << hex << (int)(unsigned char)c;
    }
    cout << endl;
    
    return 0;
}
