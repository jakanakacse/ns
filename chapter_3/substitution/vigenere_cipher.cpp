#include <bits/stdc++.h>
using namespace std;

string generate_key(string text, string key) 
{
    string key_full = "";
    for (int i = 0; i < text.size(); ++i) {
        key_full += key[i % key.size()];
    }
    return key_full;
}

string encrypt(string plaintext, string key) 
{
    string result = "";
    for (int i = 0; i < plaintext.size(); ++i) {
        char p = plaintext[i];
        char k = key[i];
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
    for (int i = 0; i < ciphertext.size(); ++i) {
        char c = ciphertext[i];
        char k = key[i];
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
    cout << "Enter plaintext: ";
    getline(cin, plain);
    cout << "Enter key: ";
    getline(cin, key);

    key = generate_key(plain, key);
    string cipher = encrypt(plain, key);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    return 0;
}
