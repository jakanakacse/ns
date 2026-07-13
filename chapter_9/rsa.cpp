#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll power(ll base, ll exp, ll mod) 
{
    ll res = 1;
    base = base % mod;
    while (exp) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

vector<ll> encrypt(string message, ll e, ll n) 
{
    vector<ll> ciphertext;
    for (char c : message) {
        ciphertext.push_back(power(c, e, n));
    }
    return ciphertext;
}

string decrypt(vector<ll> ciphertext, ll d, ll n) 
{
    string plaintext = "";
    for (ll c : ciphertext) {
        plaintext += (char)power(c, d, n);
    }
    return plaintext;
}

int main() 
{
    ll p, q;
    cout << "Enter a prime number p: ";
    cin >> p;
    cout << "Enter another prime number q: ";
    cin >> q;
    
    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    ll e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    
    ll d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }
    
    cout << "\nGenerated Key Pairs:" << endl;
    cout << "n = p * q = " << n << endl;
    cout << "phi(n) = " << phi << endl;
    cout << "Public Key (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n) = (" << d << ", " << n << ")" << endl;
    
    cin.ignore();
    
    string message;
    cout << "\nEnter plaintext message: ";
    getline(cin, message);
    
    vector<ll> ciphertext = encrypt(message, e, n);
    cout << "Ciphertext: ";
    for (ll x : ciphertext) {
        cout << x << " ";
    }
    cout << endl;
    
    string decrypted = decrypt(ciphertext, d, n);
    cout << "Plaintext: " << decrypted << endl;
    
    return 0;
}
