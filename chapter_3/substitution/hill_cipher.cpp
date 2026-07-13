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

vector<vector<int>> matrix_inverse(vector<vector<int>> mat) 
{
    int det = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0] + 26) % 26;
    int det_inv = modInverse(det, 26);
    
    vector<vector<int>> inv = {
        {mat[1][1], -mat[0][1]},
        {-mat[1][0], mat[0][0]}
    };
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            inv[i][j] = ((inv[i][j] * det_inv) % 26 + 26) % 26;
        }
    }
    return inv;
}

vector<int> multiply(vector<vector<int>> mat, vector<int> vec) 
{
    vector<int> res(2);
    for (int i = 0; i < 2; ++i) {
        res[i] = (mat[i][0] * vec[0] + mat[i][1] * vec[1]) % 26;
    }
    return res;
}

string preprocess(string text) 
{
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            result += tolower(c);
        }
    }
    if (result.size() % 2 != 0) { 
        result += 'z';
    }    
    return result;
}

string encrypt(string plaintext, vector<vector<int>> key) 
{
    string pt = preprocess(plaintext);
    string ct = "";
    for (int i = 0; i < pt.size(); i += 2) {
        vector<int> block = {pt[i] - 'a', pt[i + 1] - 'a'};
        vector<int> enc = multiply(key, block);
        ct += (char)(enc[0] + 'A');
        ct += (char)(enc[1] + 'A');
    }
    return ct;
}

string decrypt(string ciphertext, vector<vector<int>> key) 
{
    vector<vector<int>> inv_key = matrix_inverse(key);
    string pt = "";
    for (int i = 0; i < ciphertext.size(); i += 2) {
        vector<int> block = {toupper(ciphertext[i]) - 'A', toupper(ciphertext[i + 1]) - 'A'};
        vector<int> dec = multiply(inv_key, block);
        pt += (char)(dec[0] + 'a');
        pt += (char)(dec[1] + 'a');
    }
    return pt;
}

int main() 
{
    vector<vector<int>> key = {{3, 3}, {2, 5}};
    string plain;
    
    cout << "Enter plaintext: ";
    getline(cin, plain);
    
    string cipher = encrypt(plain, key);
    cout << "Ciphertext: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    
    return 0;
}
