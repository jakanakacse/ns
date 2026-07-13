#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> playfair_matrix = {
    {'L', 'I', 'S', 'T', 'E'},
    {'R', 'A', 'B', 'C', 'D'},
    {'F', 'G', 'H', 'K', 'M'},
    {'N', 'O', 'P', 'Q', 'U'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

string prepare_text(string text) 
{
    string result = "";
    for (size_t i = 0; i < text.size(); ) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            if (ch == 'J') ch = 'I';
            result += ch;
            if (i+1 < text.size() && toupper(text[i+1]) == toupper(text[i])) {
                result += 'X';
            }
            ++i;
        } else {
            ++i;
        }
    }
    if (result.size() % 2 != 0) result += 'X';
    return result;
}

pair<int, int> find_position(char c) 
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (playfair_matrix[i][j] == c) return {i, j};
        }
    }
    return {-1, -1};
}

string encrypt(string plaintext) 
{
    string text = prepare_text(plaintext);
    string result = "";
    for (size_t i = 0; i < text.size(); i += 2) {
        char a = text[i], b = text[i+1];
        int row1, col1, row2, col2;
        tie(row1, col1) = find_position(a);
        tie(row2, col2) = find_position(b);
        if (row1 == row2) {
            result += playfair_matrix[row1][(col1+1)%5];
            result += playfair_matrix[row2][(col2+1)%5];
        } else if (col1 == col2) {
            result += playfair_matrix[(row1+1)%5][col1];
            result += playfair_matrix[(row2+1)%5][col2];
        } else {
            result += playfair_matrix[row1][col2];
            result += playfair_matrix[row2][col1];
        }
    }
    return result;
}

string decrypt(string ciphertext) 
{
    string result = "";
    for (size_t i = 0; i < ciphertext.size(); i += 2) {
        char a = toupper(ciphertext[i]), b = toupper(ciphertext[i+1]);
        int row1, col1, row2, col2;
        tie(row1, col1) = find_position(a);
        tie(row2, col2) = find_position(b);
        if (row1 == row2) {
            result += playfair_matrix[row1][(col1+4)%5];
            result += playfair_matrix[row2][(col2+4)%5];
        } else if (col1 == col2) {
            result += playfair_matrix[(row1+4)%5][col1];
            result += playfair_matrix[(row2+4)%5][col2];
        } else {
            result += playfair_matrix[row1][col2];
            result += playfair_matrix[row2][col1];
        }
    }
    return result;
}

void print_matrix() 
{
    cout << "Playfair Matrix:" << endl;
    for (auto& row : playfair_matrix) {
        for (char c : row) cout << c << ' ';
        cout << endl;
    }
}

int main() {
    print_matrix();
    string plain;
    cout << "Enter plaintext:" << endl;
    getline(cin, plain);
    string cipher = encrypt(plain);
    cout << "Encrypted: " << cipher << endl;
    cout << "Plaintext: " << decrypt(cipher) << endl;
    return 0;
}
