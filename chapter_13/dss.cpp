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

ll sign_message(ll message, ll d, ll n) 
{
    return power(message, d, n);
}

bool verify_message(ll message, ll signature, ll e, ll n) 
{
    return power(signature, e, n) == message;
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
    cout << "n = " << n << endl;
    cout << "phi(n) = " << phi << endl;
    cout << "Public Key (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n) = (" << d << ", " << n << ")" << endl;
    
    ll message;
    cout << "\nEnter message to sign (integer): ";
    cin >> message;

    ll signature = sign_message(message, d, n);
    cout << "Signature: " << signature << endl;
    
    bool is_valid = verify_message(message, signature, e, n);
    cout << "Verification: " << (is_valid ? "Accept" : "Reject") << endl;
    
    return 0;
}
