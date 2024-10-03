#include <bits/stdc++.h>
using namespace std;

string encryption(string plainText, int key, vector<char> smallAlphabets, vector<char> capitalAlphabets)
{
    string encryptedString = "";
    int index;

    for (int i = 0; i < plainText.size(); i++)
    {
        char c = plainText[i];
        if (c == ' ')
        {
            encryptedString += ' ';
            continue;
        }

        if (islower(c))
        {
            for (int j = 0; j < smallAlphabets.size(); j++)
            {
                if (smallAlphabets[j] == c)
                {
                    index = j;
                    break;
                }
            }
            encryptedString += smallAlphabets[(key + index) % 26];
        }
        else if (isupper(c))
        {
            for (int j = 0; j < capitalAlphabets.size(); j++)
            {
                if (capitalAlphabets[j] == c)
                {
                    index = j;
                    break;
                }
            }
            encryptedString += capitalAlphabets[(key + index) % 26];
        }
    }

    return encryptedString;
}

string decryption(string encryptedText, int key, vector<char> smallAlphabets, vector<char> capitalAlphabets)
{
    string decryptedString = "";
    int index;

    for (int i = 0; i < encryptedText.size(); i++)
    {
        char c = encryptedText[i];
        if (c == ' ')
        {
            decryptedString += ' ';
            continue;
        }

        if (islower(c))
        {
            for (int j = 0; j < smallAlphabets.size(); j++)
            {
                if (smallAlphabets[j] == c)
                {
                    index = j;
                    break;
                }
            }

            int newIndex = (index - key) % 26;
            
            if (newIndex < 0)
            {
                newIndex += 26;
            }
            decryptedString += smallAlphabets[newIndex];
        }
        else if (isupper(c))
        {
            for (int j = 0; j < capitalAlphabets.size(); j++)
            {
                if (capitalAlphabets[j] == c)
                {
                    index = j;
                    break;
                }
            }

            int newIndex = (index - key) % 26;

            if (newIndex < 0)
            {
                newIndex += 26;
            }
            decryptedString += capitalAlphabets[newIndex];
        }
    }

    return decryptedString;
}

int main()
{
    string plainText;
    cout << "Enter plaintext: ";
    getline(cin, plainText);

    int key;
    cout << "Enter the key: ";
    cin >> key;

    vector<char> smallAlphabets = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector<char> capitalAlphabets = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    string encrypt = encryption(plainText, key, smallAlphabets, capitalAlphabets);
    cout << "Encrypted string is: " << encrypt << endl;
    string decrypt = decryption(encrypt, key, smallAlphabets, capitalAlphabets);
    cout << "Decrypted string is: " << decrypt << endl;

    return 0;
}
