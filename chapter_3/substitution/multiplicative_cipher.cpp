#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int m) 
{
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    cout << "No modular multiplicative inverse found" << endl;
    exit(-1);
}

string encrypt(string plaintext, int key) 
{
    string result = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                char c = ((ch - 'A') * key) % 26 + 'A';
                result += c;
            } else {
                char c = ((ch - 'a') * key) % 26 + 'a';
                result += c;
            }
        } else {
            result += ch;
        }
    }
    return result;
}

string decrypt(string ciphertext, int key) 
{
    string result = "";
    int inv = modinv(key, 26);
    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                char p = ((ch - 'A') * inv) % 26 + 'A';
                result += p;
            } else {
                char p = ((ch - 'a') * inv) % 26 + 'a';
                result += p;
            }
        } else {
            result += ch;
        }
    }
    return result;
}

int main() 
{
    string plain;
    int key;
    cout << "Enter plaintext:" << endl;
    getline(cin, plain);
    cout << "Enter key:" << endl;
    cin >> key;
    string cipher = encrypt(plain, key);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    return 0;
}
