#include <bits/stdc++.h>
using namespace std;

string rail_fence_encrypt(const string& plaintext) {
    string row1 = "", row2 = "";
    for (int i = 0; i < plaintext.size(); ++i) {
        if (i % 2 == 0) {
            row1 += plaintext[i];
        } else {
            row2 += plaintext[i];
        }
    }
    return row1 + row2;
}

string rail_fence_decrypt(const string& ciphertext) {
    int n = ciphertext.size();
    int row1_len = (n + 1) / 2;
    int row2_len = n / 2;
    
    string row1 = ciphertext.substr(0, row1_len);
    string row2 = ciphertext.substr(row1_len);
    
    string plaintext = "";
    for (int i = 0; i < row2_len; ++i) {
        plaintext += row1[i];
        plaintext += row2[i];
    }
    if (row1_len > row2_len) {
        plaintext += row1[row1_len - 1];
    }
    return plaintext;
}

int main() {
    string plaintext;
    cout << "Enter plaintext:" << endl;
    getline(cin, plaintext);
    
    string ciphertext = rail_fence_encrypt(plaintext);
    string recovered = rail_fence_decrypt(ciphertext);
    
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Plaintext: " << recovered << endl;
}
