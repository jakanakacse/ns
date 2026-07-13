#include <bits/stdc++.h>
using namespace std;

string encrypt(string plaintext, int key) 
{
    string result = "";
    int curr = key;
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            int p = toupper(ch) - 'A';
            char c = ((p + curr) % 26) + 'A';
            result += isupper(ch) ? c : tolower(c);
            curr = p;
        } else {
            result += ch;
        }
    }
    return result;
}

string decrypt(string ciphertext, int key) 
{
    string result = "";
    int curr = key;
    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            int c = toupper(ch) - 'A';
            int p = (c - curr + 26) % 26 + 'A';
            result += isupper(ch) ? p : tolower(p);
            curr = p - 'A';
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
    cout << "Enter plaintext: ";
    getline(cin, plain);
    cout << "Enter key (integer): ";
    cin >> key;
    
    string cipher = encrypt(plain, key);
    cout << "Ciphertext: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    return 0;
}
