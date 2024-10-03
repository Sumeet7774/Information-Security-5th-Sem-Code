#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

void encrypt(const string &plaintext, string &ciphertext, int key, int size, const vector<char> &alpha, const vector<char> &Alpha)
{
    ciphertext.resize(size);

    for (int i = 0; i < size; i++)
    {
        if (plaintext[i] == ' ')
        {
            ciphertext[i] = ' ';
        }
        else
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == alpha[j])
                {
                    int k;
                    if (is_prime(j))
                    {
                        k = (j + key) % 26;
                    }
                    else
                    {
                        k = (j - key) % 26;
                        if (k < 0)
                        {
                            k += 26;
                        }
                    }
                    ciphertext[i] = alpha[k];
                    break;
                }
                else if (plaintext[i] == Alpha[j])
                {
                    int r;
                    if (is_prime(j))
                    {
                        r = (j + key) % 26;
                    }
                    else
                    {
                        r = (j - key) % 26;
                        if (r < 0)
                        {
                            r += 26;
                        }
                    }
                    ciphertext[i] = Alpha[r];
                    break;
                }
            }
        }
    }
    cout << "Encrypted Text: " << ciphertext << endl;
}

void decrypt(const string &ciphertext, string &decryptedtext, int key, int size, const vector<char> &alpha, const vector<char> &Alpha)
{
    decryptedtext.resize(size);

    for (int i = 0; i < size; i++)
    {
        if (ciphertext[i] == ' ')
        {
            decryptedtext[i] = ' ';
        }
        else
        {
            for (int j = 0; j < 26; j++)
            {
                if (ciphertext[i] == alpha[j])
                {
                    int k;
                    if (is_prime(j))
                    {
                        k = (j + key) % 26;
                    }
                    else
                    {
                        k = (j - key) % 26;
                        if (k < 0)
                        {
                            k += 26;
                        }
                    }
                    decryptedtext[i] = alpha[k];
                    break;
                }
                else if (ciphertext[i] == Alpha[j])
                {
                    int r;
                    if (is_prime(j))
                    {
                        r = (j + key) % 26;
                    }
                    else
                    {
                        r = (j - key) % 26;
                        if (r < 0)
                        {
                            r += 26;
                        }
                    }
                    decryptedtext[i] = Alpha[r];
                    break;
                }
            }
        }
    }
    cout << "Decrypted Text: " << decryptedtext << endl;
}

int main()
{
    string plaintext;    
    string ciphertext;   
    string decryptedtext; 
    int key = 1;

    vector<char> alphabets = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector<char> Alphabets = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    cout << "Enter Plain Text: ";
    getline(cin, plaintext);
    int size = plaintext.size();

    encrypt(plaintext, ciphertext, key, size, alphabets, Alphabets);
    decrypt(ciphertext, decryptedtext, key, size, alphabets, Alphabets);

    return 0;
}
