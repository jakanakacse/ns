#include <bits/stdc++.h>
using namespace std;

string encrypt_block(string block, vector<int> key) {
    string result = "";
    for (int i = 0; i < key.size(); ++i) {
        result += block[key[i] - 1];
    }
    return result;
}

string decrypt_block(string block, vector<int> key) {
    string result(block.size(), ' ');
    for (int i = 0; i < key.size(); ++i) {
        result[key[i] - 1] = block[i];
    }
    return result;
}

string pad_text(string text, int block_size) {
    string padded = text;
    while (padded.size() % block_size != 0) {
        padded += 'z';
    }
    return padded;
}

string encrypt(string plaintext, vector<int> key) {
    int block_size = key.size();
    string padded = pad_text(plaintext, block_size);
    string ciphertext = "";
    
    for (int i = 0; i < padded.size(); i += block_size) {
        string block = padded.substr(i, block_size);
        ciphertext += encrypt_block(block, key);
    }
    return ciphertext;
}

string decrypt(string ciphertext, vector<int> key) {
    int block_size = key.size();
    string plaintext = "";
    
    for (int i = 0; i < ciphertext.size(); i += block_size) {
        string block = ciphertext.substr(i, block_size);
        plaintext += decrypt_block(block, key);
    }
    return plaintext;
}

int main() {
    string plaintext;
    int block_size;
    
    cout << "Enter plaintext:" << endl;
    getline(cin, plaintext);
    
    cout << "Enter block size:" << endl;
    cin >> block_size;
    
    cout << "Enter permutation key (space-separated):" << endl;
    vector<int> key(block_size);
    for (int i = 0; i < block_size; ++i) {
        cin >> key[i];
    }
    
    string ciphertext = encrypt(plaintext, key);
    string recovered = decrypt(ciphertext, key);
    
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Plaintext: " << recovered << endl;
    
    return 0;
}
