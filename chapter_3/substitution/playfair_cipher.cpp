#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> mat = {
    {'L', 'I', 'S', 'T', 'E'},
    {'R', 'A', 'B', 'C', 'D'},
    {'F', 'G', 'H', 'K', 'M'},
    {'N', 'O', 'P', 'Q', 'U'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

string prepare_text(string text) 
{
    string result = "";
    for (int i = 0; i < text.size(); ++i) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            if (ch == 'J') ch = 'I';
            result += ch;
            if (i+1 < text.size() && toupper(text[i+1]) == toupper(text[i])) {
                result += 'X';
            }
        }
    }
    if (result.size() % 2 != 0) result += 'X';
    return result;
}

pair<int, int> find_position(char c) 
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (mat[i][j] == c) return {i, j};
        }
    }
}

string encrypt(string plaintext) 
{
    string text = prepare_text(plaintext);
    string result = "";
    for (int i = 0; i < text.size(); i += 2) {
        auto a = find_position(text[i]);
        auto b = find_position(text[i + 1]);
        if (a.first == b.first) {
            result += mat[a.first][(a.second+1)%5];
            result += mat[b.first][(b.second+1)%5];
        } else if (a.second == b.second) {
            result += mat[(a.first+1)%5][a.second];
            result += mat[(b.first+1)%5][b.second];
        } else {
            result += mat[a.first][b.second];
            result += mat[b.first][a.second];
        }
    }
    return result;
}

string decrypt(string ciphertext) 
{
    string result = "";
    for (int i = 0; i < ciphertext.size(); i += 2) {
        auto a = find_position(toupper(ciphertext[i]));
        auto b = find_position(toupper(ciphertext[i + 1]));
        if (a.first == b.first) {
            result += mat[a.first][(a.second + 4) % 5];
            result += mat[b.first][(b.second + 4) % 5];
        } else if (a.second == b.second) {
            result += mat[(a.first + 4) % 5][a.second];
            result += mat[(b.first + 4) % 5][b.second];
        } else {
            result += mat[a.first][b.second];
            result += mat[b.first][a.second];
        }
    }
    return result;
}

void print_matrix() 
{
    cout << "Playfair Matrix:" << endl;
    for (auto& row : mat) {
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
