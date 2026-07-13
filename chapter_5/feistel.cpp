#include <bits/stdc++.h>
using namespace std;

string round_function(string R, int key) 
{
    string temp = R;
    for (int i = 0; i < 4; ++i) {
        temp[i] = (temp[i] ^ key) % 256;
    }
    return temp;
}

string xor_strings(string A, string B) 
{
    string result = "";
    for (int i = 0; i < 4; ++i) {
        result += (char)(A[i] ^ B[i]);
    }
    return result;
}

string encrypt(string plaintext, vector<int> round_keys) 
{
    string L = plaintext.substr(0, 4);
    string R = plaintext.substr(4, 4);
    
    for (int round = 0; round < 4; ++round) {
        int key = round_keys[round];
        string next_L = R;
        string f_result = round_function(R, key);
        string next_R = xor_strings(L, f_result);
        
        L = next_L;
        R = next_R;
    }
    return R + L;
}

string decrypt(string ciphertext, vector<int> round_keys) 
{
    string L = ciphertext.substr(0, 4);
    string R = ciphertext.substr(4, 4);
    
    for (int round = 0; round < 4; ++round) {
        int key = round_keys[3 - round];
        string next_L = R;
        string f_result = round_function(R, key);
        string next_R = xor_strings(L, f_result);
        
        L = next_L;
        R = next_R;
    }
    return R + L;
}

int main() 
{
    string text;
    int key;
    
    cout << "Enter an 8-character plaintext: ";
    getline(cin, text);
    
    if (text.length() < 8) {
        text.append(8 - text.length(), ' ');
    } else if (text.length() > 8) {
        text = text.substr(0, 8);
    }
    
    cout << "Enter key: ";
    cin >> key;
    
    vector<int> round_keys(4);
    for (int i = 0; i < 4; ++i) {
        round_keys[i] = (key + (i + 1) * 7) % 256;
    }
    
    string ciphertext = encrypt(text, round_keys);
    cout << "Ciphertext: ";
    for (char c : ciphertext) {
        cout << hex << setw(2) << setfill('0') << (int)(unsigned char)c << " ";
    }
    cout << dec << endl;
    
    string decrypted = decrypt(ciphertext, round_keys);
    cout << "Plaintext: \"" << decrypted << "\"" << endl;
    
    return 0;
}
