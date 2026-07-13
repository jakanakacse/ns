#include <bits/stdc++.h>
using namespace std;

// DES Permutation and Substitution Tables
const int InitialPermutationTable[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

const int FinalPermutationTable[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

const int ExpansionPermutationTable[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

const int StraightPermutationTable[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};

const int SBoxes[8][4][16] = {
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

// Permute: apply permutation table
void permute(const vector<int>& inBlock, vector<int>& outBlock, const int table[], int size) {
    outBlock.assign(size, 0);
    for (int i = 0; i < size; ++i) {
        outBlock[i] = inBlock[table[i] - 1];
    }
}

// Split: divide block into left and right halves
void split(const vector<int>& inBlock, vector<int>& leftBlock, vector<int>& rightBlock) {
    leftBlock.assign(inBlock.begin(), inBlock.begin() + 32);
    rightBlock.assign(inBlock.begin() + 32, inBlock.end());
}

// Combine: merge left and right blocks
void combine(const vector<int>& leftBlock, const vector<int>& rightBlock, vector<int>& outBlock) {
    outBlock = leftBlock;
    outBlock.insert(outBlock.end(), rightBlock.begin(), rightBlock.end());
}

// Swapper: swap left and right blocks
void swapper(vector<int>& leftBlock, vector<int>& rightBlock) {
    swap(leftBlock, rightBlock);
}

// Exclusive OR
void exclusiveOr(const vector<int>& block1, const vector<int>& block2, vector<int>& outBlock) {
    outBlock.assign(block1.size(), 0);
    for (size_t i = 0; i < block1.size(); ++i) {
        outBlock[i] = block1[i] ^ block2[i];
    }
}

// Substitute: apply S-box substitution
void substitute(const vector<int>& inBlock, vector<int>& outBlock) {
    outBlock.clear();
    for (int i = 0; i < 8; ++i) {
        int row = (inBlock[i*6] << 1) | inBlock[i*6 + 5];
        int col = (inBlock[i*6 + 1] << 3) | (inBlock[i*6 + 2] << 2) | (inBlock[i*6 + 3] << 1) | inBlock[i*6 + 4];
        int value = SBoxes[i][row][col];
        outBlock.push_back((value >> 3) & 1);
        outBlock.push_back((value >> 2) & 1);
        outBlock.push_back((value >> 1) & 1);
        outBlock.push_back(value & 1);
    }
}

// Function F
void fonction(const vector<int>& inBlock, const vector<int>& roundKey, vector<int>& outBlock) {
    vector<int> T1, T2, T3;
    permute(inBlock, T1, ExpansionPermutationTable, 48);
    exclusiveOr(T1, roundKey, T2);
    substitute(T2, T3);
    permute(T3, outBlock, StraightPermutationTable, 32);
}

// Mixer
void mixer(vector<int>& leftBlock, vector<int>& rightBlock, const vector<int>& roundKey) {
    vector<int> T1 = rightBlock;
    vector<int> T2, T3;
    fonction(T1, roundKey, T2);
    exclusiveOr(leftBlock, T2, T3);
    leftBlock = T3;
}

// Main DES cipher
void des_cipher(const vector<int>& plainBlock, vector<vector<int>>& roundKeys, vector<int>& cipherBlock) {
    vector<int> inBlock, outBlock, leftBlock, rightBlock;
    
    // Initial Permutation
    permute(plainBlock, inBlock, InitialPermutationTable, 64);
    
    // Split into left and right
    split(inBlock, leftBlock, rightBlock);
    
    // 16 rounds
    for (int round = 0; round < 16; ++round) {
        mixer(leftBlock, rightBlock, roundKeys[round]);
        if (round != 15) {
            swapper(leftBlock, rightBlock);
        }
    }
    
    // Combine
    combine(leftBlock, rightBlock, outBlock);
    
    // Final Permutation
    permute(outBlock, cipherBlock, FinalPermutationTable, 64);
}

// Convert hex string to binary vector
vector<int> hex_to_binary(const string& hex) {
    vector<int> binary;
    for (char c : hex) {
        int val = (c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10);
        for (int i = 3; i >= 0; --i) {
            binary.push_back((val >> i) & 1);
        }
    }
    return binary;
}

// Convert binary vector to hex string
string binary_to_hex(const vector<int>& binary) {
    string hex = "";
    for (size_t i = 0; i < binary.size(); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; ++j) {
            val = (val << 1) | binary[i + j];
        }
        hex += (val < 10) ? (char)('0' + val) : (char)('a' + val - 10);
    }
    return hex;
}

int main() {
    string plaintext_hex, key_hex;
    cout << "Enter plaintext (64-bit hex):" << endl;
    cin >> plaintext_hex;
    cout << "Enter key (64-bit hex):" << endl;
    cin >> key_hex;
    
    // Simplified: use same round key for all 16 rounds (normally generated from key schedule)
    vector<int> key_binary = hex_to_binary(key_hex);
    vector<vector<int>> roundKeys(16, key_binary);
    
    vector<int> plaintext = hex_to_binary(plaintext_hex);
    vector<int> ciphertext(64);
    
    des_cipher(plaintext, roundKeys, ciphertext);
    
    cout << "Ciphertext (hex): " << binary_to_hex(ciphertext) << endl;
    
    return 0;
}
