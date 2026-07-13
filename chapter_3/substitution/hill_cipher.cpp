#include <bits/stdc++.h>
using namespace std;

int determinant(vector<vector<int>> mat) 
{
    int n = mat.size();
    if (n == 2)
        return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
    if (n == 3)
        return (mat[0][0]*(mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1])
                - mat[0][1]*(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
                + mat[0][2]*(mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]));
    return 0;
}

int modinv(int a, int m) 
{
    a = (a % m + m) % m;
    for (int x = 1; x < m; ++x) {
        if ((a * x) % m == 1) return x;
    }
    cout << "No modular inverse for determinant!" << endl;
    exit(1);
}

vector<vector<int>> matrix_inverse(vector<vector<int>> mat) 
{
    int n = mat.size();
    int det = determinant(mat);
    int det_inv = modinv(det, 26);
    vector<vector<int>> inv(n, vector<int>(n));
    if (n == 2) {
        inv[0][0] =  mat[1][1];
        inv[0][1] = -mat[0][1];
        inv[1][0] = -mat[1][0];
        inv[1][1] =  mat[0][0];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                inv[i][j] = ((inv[i][j] * det_inv) % 26 + 26) % 26;
    }
    return inv;
}

vector<int> multiply(vector<vector<int>> mat, vector<int> vec) 
{
    int n = mat.size();
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = 0;
        for (int j = 0; j < n; ++j)
            res[i] = (res[i] + mat[i][j] * vec[j]) % 26;
    }
    return res;
}

string preprocess(string text, int block_size) 
{
    string result = "";
    for (char c : text) if (isalpha(c)) result += tolower(c);
    while (result.size() % block_size != 0) result += 'z';
    return result;
}

string encrypt(string plaintext, vector<vector<int>> key) 
{
    int n = key.size();
    string pt = preprocess(plaintext, n);
    string ct = "";
    for (size_t i = 0; i < pt.size(); i += n) {
        vector<int> block(n);
        for (int j = 0; j < n; ++j) block[j] = pt[i+j] - 'a';
        vector<int> enc = multiply(key, block);
        for (int v : enc) ct += (char)(v + 'A');
    }
    return ct;
}

string decrypt(string ciphertext, vector<vector<int>> key) 
{
    int n = key.size();
    vector<vector<int>> inv_key = matrix_inverse(key);
    string pt = "";
    for (size_t i = 0; i < ciphertext.size(); i += n) {
        vector<int> block(n);
        for (int j = 0; j < n; ++j) block[j] = toupper(ciphertext[i+j]) - 'A';
        vector<int> dec = multiply(inv_key, block);
        for (int v : dec) pt += (char)(v + 'a');
    }
    return pt;
}

int main() 
{
    vector<vector<int>> key = {{3, 3}, {2, 5}};
    cout << "Hill Cipher 2x2 Example" << endl;
    cout << "Key matrix:" << endl;
    for (auto& row : key) {
        for (int v : row) cout << v << ' ';
        cout << endl;
    }
    string plain;
    cout << "Enter plaintext:" << endl;
    getline(cin, plain);
    string cipher = encrypt(plain, key);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher, key) << endl;
    return 0;
}
