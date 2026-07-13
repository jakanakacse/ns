#include <iostream>
#include <string>
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

string encrypt(string plaintext, int a, int b) 
{
    string result = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                char c = ((a * (ch - 'A') + b) % 26) + 'A';
                result += c;
            } else {
                char c = ((a * (ch - 'a') + b) % 26) + 'a';
                result += c;
            }
        } else {
            result += ch;
        }
    }
    return result;
}

string decrypt(string ciphertext, int a, int b) 
{
    string result = "";
    int inv = modInverse(a, 26);
    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                char p = (inv * ((ch - 'A') - b + 26)) % 26 + 'A';
                result += p;
            } else {
                char p = (inv * ((ch - 'a') - b + 26)) % 26 + 'a';
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
    int a, b;
    cout << "Enter plaintext:" << endl;
    getline(cin, plain);
    cout << "Enter key a:" << endl;
    cin >> a;
    cout << "Enter key b:" << endl;
    cin >> b;
    string cipher = encrypt(plain, a, b);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, a, b) << endl;
    return 0;
}
