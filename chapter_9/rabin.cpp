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

void extended_gcd(ll p, ll q, ll &a, ll &b) 
{
    if (q == 0) {
        a = 1;
        b = 0;
        return;
    }
    ll a1, b1;
    extended_gcd(q, p % q, a1, b1);
    a = b1;
    b = a1 - (p / q) * b1;
}

ll encrypt(ll text, ll n) 
{
    return power(text, 2, n);
}

vector<ll> decrypt(ll C, ll p, ll q) 
{
    ll n = p * q;
    ll mp = power(C, (p + 1) / 4, p);
    ll mq = power(C, (q + 1) / 4, q);
    
    ll a, b;
    extended_gcd(p, q, a, b);
    
    ll r1 = (a * p * mq + b * q * mp) % n;
    if (r1 < 0) r1 += n;
    
    ll r2 = n - r1;
    
    ll r3 = (a * p * mq - b * q * mp) % n;
    if (r3 < 0) r3 += n;
    
    ll r4 = n - r3;
    
    return {r1, r2, r3, r4};
}

int main() 
{
    ll p, q;
    cout << "Enter a prime p (p == 3 mod 4): ";
    cin >> p;
    cout << "Enter a prime q (q == 3 mod 4): ";
    cin >> q;
    
    if (p % 4 != 3 || q % 4 != 3) {
        cout << "Error: Both primes must be 3 mod 4!" << endl;
        return 1;
    }
    
    ll n = p * q;
    cout << "\nGenerated Keys:" << endl;
    cout << "Public Key (n) = " << n << endl;
    cout << "Private Keys (p, q) = (" << p << ", " << q << ")" << endl;
    
    ll text;
    cout << "\nEnter plaintext (integer < " << n << "): ";
    cin >> text;
    
    if (text >= n) {
        cout << "Error: Plaintext M must be less than n!" << endl;
        return 1;
    }
    
    ll cipher = encrypt(text, n);
    cout << "Ciphertext: " << cipher << endl;
    
    vector<ll> plaintexts = decrypt(cipher, p, q);
    
    cout << "The four possible plaintexts are:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << plaintexts[i] << endl;
    }
}
