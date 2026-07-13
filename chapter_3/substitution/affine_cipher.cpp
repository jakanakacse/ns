#include <iostream>
#include <string>
using namespace std;

int gcd(int a, int b, int &x, int &y) 
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

int modinv(int a, int m) 
{
    int x, y;
    int g = gcd(a, m, x, y);
    if (g != 1) {
        cout << "No modular inverse for key found" << endl;
        exit(1);
    }
    return (x % m + m) % m;
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
    int inv = modinv(a, 26);
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
