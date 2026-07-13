#include <bits/stdc++.h>
using namespace std;

bitset<4> f_key(const string& key) {
    int bit1 = key[0] - '0';
    int bit3 = key[2] - '0';
    int num = (bit1 << 1) | bit3;
    int squared = num * num;
    return bitset<4>(squared);
}

int main() {
    string plaintext_str, key_str;
    cout << "Enter plaintext (4-bit binary): ";
    cin >> plaintext_str;
    cout << "Enter key (3-bit binary): ";
    cin >> key_str;
    
    bitset<4> plaintext(plaintext_str);
    bitset<4> f_k = f_key(key_str);
    bitset<4> ciphertext = plaintext ^ f_k;
    bitset<4> recovered = ciphertext ^ f_k;
    
    cout << "Generated key: " << f_k << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Plaintext: " << recovered << endl;
    
    return 0;
}
