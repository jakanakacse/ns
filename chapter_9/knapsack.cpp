#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int m) 
{
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

vector<int> permute(vector<int> t, vector<int> p) 
{
    vector<int> a(t.size());
    for (int i = 0; i < t.size(); ++i) {
        a[i] = t[p[i] - 1];
    }
    return a;
}

int knapsackSum(vector<int> a, vector<int> x) 
{
    int s = 0;
    for (int i = 0; i < a.size(); ++i) {
        s += a[i] * x[i];
    }
    return s;
}

vector<int> inv_knapsackSum(int s, vector<int> b) 
{
    int k = b.size();
    vector<int> x_prime(k, 0);
    for (int i = k - 1; i >= 0; --i) {
        if (s >= b[i]) {
            x_prime[i] = 1;
            s -= b[i];
        }
    }
    return x_prime;
}

int encrypt(vector<int> x, vector<int> a) 
{
    return knapsackSum(a, x);
}

vector<int> decrypt(int s, int n, int r, vector<int> b, vector<int> p) 
{
    int r_inv = modInverse(r, n);
    int s_prime = (s * r_inv) % n;
    vector<int> x_prime = inv_knapsackSum(s_prime, b);
    return permute(x_prime, p);
}

int main() 
{
    vector<int> b = {7, 11, 19, 39, 79, 157, 313};
    int n = 900;
    int r = 37;
    vector<int> p = {4, 2, 5, 3, 1, 7, 6};
    
    vector<int> t(b.size());
    for (int i = 0; i < b.size(); ++i) {
        t[i] = (r * b[i]) % n;
    }
    vector<int> a = permute(t, p);
    
    cout << "Public Key a = ";
    for (int val : a) cout << val << " ";
    cout << endl;
    
    vector<int> x = {1, 1, 0, 0, 1, 1, 1}; 
    cout << "\nPlaintext x = ";
    for (int val : x) cout << val << " ";
    cout << " (character 'g')" << endl;
    
    int s = encrypt(x, a);
    cout << "Ciphertext s = " << s << endl;
    
    vector<int> plain = decrypt(s, n, r, b, p);
    
    cout << "\nDecrypted plaintext x = ";
    for (int val : plain) cout << val << " ";
    cout << endl;
    
    return 0;
}
