#include <bits/stdc++.h>
using namespace std;

string encrypt(string plaintext, string key) 
{
    string result = "";
    string key_stream = key;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            int k = toupper(key_stream[i]) - 'A';
            char c = ((toupper(ch) - 'A' + k) % 26) + 'A';
            result += isupper(ch) ? c : tolower(c);
            key_stream += ch;
        } else {
            result += ch;
            key_stream += ch;
        }
    }
    return result;
}

string decrypt(string ciphertext, string key) 
{
    string result = "";
    string key_stream = key;
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            int k = toupper(key_stream[i]) - 'A';
            char p = ((toupper(ch) - 'A' - k + 26) % 26) + 'A';
            result += isupper(ch) ? p : tolower(p);
            key_stream += isupper(ch) ? p : tolower(p);
        } else {
            result += ch;
            key_stream += ch;
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
