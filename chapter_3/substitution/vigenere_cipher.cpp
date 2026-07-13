#include <bits/stdc++.h>
using namespace std;

string generate_key(string text, string key) 
{
    if (key.empty()) {
        cout << "Error: Key must not be empty." << endl;
        exit(1);
    }
    string key_full = key;
    size_t i = 0;
    while (key_full.size() < text.size()) {
        key_full += key_full[i % key_full.size()];
        ++i;
    }
    return key_full;
}

string encrypt(string plaintext, string key) 
{
    string result = "";
    string key_full = generate_key(plaintext, key);
    for (size_t i = 0; i < plaintext.size(); ++i) {
        char p = plaintext[i];
        char k = key_full[i];
        if (isalpha(p)) {
            int k_val = toupper(k) - 'A';
            char c = ((toupper(p) - 'A' + k_val) % 26) + 'A';
            result += isupper(p) ? c : tolower(c);
        } else {
            result += p;
        }
    }
    return result;
}

string decrypt(string ciphertext, string key) 
{
    string result = "";
    string key_full = generate_key(ciphertext, key);
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        char c = ciphertext[i];
        char k = key_full[i];
        if (isalpha(c)) {
            int k_val = toupper(k) - 'A';
            char p = ((toupper(c) - 'A' - k_val + 26) % 26) + 'A';
            result += isupper(c) ? p : tolower(p);
        } else {
            result += c;
        }
    }
    return result;
}

int main() 
{
    string plain, key;
    cout << "Enter plaintext:" << endl;
    getline(cin, plain);
    cout << "Enter key:" << endl;
    getline(cin, key);
    string cipher = encrypt(plain, key);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    return 0;
}
