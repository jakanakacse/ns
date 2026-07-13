#include <bits/stdc++.h>
using namespace std;

string pad_text(string text, int cols) {
    string padded = text;
    while (padded.size() % cols != 0) {
        padded += ' ';
    }
    return padded;
}

vector<string> permute_columns(vector<string> table, vector<int> key) {
    int cols = table[0].size();
    int rows = table.size();
    vector<string> result(rows, "");
    
    for (int i = 0; i < cols; ++i) {
        for (int row = 0; row < rows; ++row) {
            result[row] += table[row][key[i] - 1];
        }
    }
    return result;
}

vector<string> inverse_permute_columns(vector<string> table, vector<int> key) {
    int cols = table[0].size();
    int rows = table.size();
    vector<string> result(rows, string(cols, ' '));
    
    for (int i = 0; i < cols; ++i) {
        for (int row = 0; row < rows; ++row) {
            result[row][key[i] - 1] = table[row][i];
        }
    }
    return result;
}

string encrypt(string plaintext, vector<int> key) {
    int cols = key.size();
    string padded = pad_text(plaintext, cols);
    int rows = padded.size() / cols;
    
    vector<string> table(rows, "");
    for (int i = 0; i < padded.size(); ++i) {
        table[i / cols] += padded[i];
    }
    
    vector<string> permuted = permute_columns(table, key);
    
    string ciphertext = "";
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            ciphertext += permuted[row][col];
        }
    }
    return ciphertext;
}

string decrypt(string ciphertext, vector<int> key) {
    int cols = key.size();
    int rows = ciphertext.size() / cols;
    
    vector<string> table(rows, "");
    int idx = 0;
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            table[row] += ciphertext[idx++];
        }
    }
    
    vector<string> depermuted = inverse_permute_columns(table, key);
    
    string plaintext = "";
    for (int row = 0; row < rows; ++row) {
        plaintext += depermuted[row];
    }
    return plaintext;
}

int main() {
    string plaintext;
    int cols;
    
    cout << "Enter plaintext:" << endl;
    getline(cin, plaintext);
    
    cout << "Enter number of columns:" << endl;
    cin >> cols;
    
    cout << "Enter permutation key (space-separated):" << endl;
    vector<int> key(cols);
    for (int i = 0; i < cols; ++i) {
        cin >> key[i];
    }
    
    string ciphertext = encrypt(plaintext, key);
    string recovered = decrypt(ciphertext, key);
    
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Plaintext: " << recovered << endl;
    
    return 0;
}
