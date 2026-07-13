#include <bits/stdc++.h>
using namespace std;

string pad_text(string text, int cols) {
    string padded = text;
    while (padded.size() % cols != 0) {
        padded += ' ';
    }
    return padded;
}

string encrypt(string plaintext, int cols) {
    string padded = pad_text(plaintext, cols);
    int rows = padded.size() / cols;
    
    string ciphertext = "";
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            ciphertext += padded[row * cols + col];
        }
    }
    return ciphertext;
}

string decrypt(string ciphertext, int cols) {
    int rows = ciphertext.size() / cols;
    string plaintext = "";
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            plaintext += ciphertext[col * rows + row];
        }
    }
    return plaintext;
}

int main() {
    string plaintext;
    int cols;
    
    cout << "Enter plaintext:" << endl;
    getline(cin, plaintext);
    
    cout << "Enter number of columns:" << endl;
    cin >> cols;
    
    string ciphertext = encrypt(plaintext, cols);
    string recovered = decrypt(ciphertext, cols);
    
    cout << "Encrypted: " << ciphertext << endl;
    cout << "Plaintext: " << recovered << endl;
    
    return 0;
}
