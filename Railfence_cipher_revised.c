#include <stdio.h>

void removeSpace(char str[], int length)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int stringLength(char str[])
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

void rail_fence_encrypt(char text[], int key, char result[])
{
    int length = stringLength(text);
    char rail[10][100]; // Assuming maximum key = 10 and text length = 100

    // Initialize the rail matrix with newline characters
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < length; j++)
        {
            rail[i][j] = '\n';
        }
    }

    int dir_down = 0, row = 0, col = 0;
    for (int i = 0; i < length; i++)
    {
        if (row == 0 || row == key - 1)
        {
            dir_down = !dir_down;
        }
        rail[row][col++] = text[i];
        if (dir_down)
        {
            row++;
        }
        else
        {
            row--;
        }
    }

    int k = 0;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (rail[i][j] != '\n')
            {
                result[k++] = rail[i][j];
            }
        }
    }
    result[k] = '\0'; // Null-terminate the result
}

void rail_fence_decrypt(char cipher[], int key, char result[])
{
    int length = stringLength(cipher);
    char rail[10][100]; // Assuming maximum key = 10 and text length = 100

    // Initialize the rail matrix with newline characters
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < length; j++)
        {
            rail[i][j] = '\n';
        }
    }

    int dir_down, row = 0, col = 0;
    for (int i = 0; i < length; i++)
    {
        if (row == 0)
        {
            dir_down = 1;
        }
        if (row == key - 1)
        {
            dir_down = 0;
        }
        rail[row][col++] = '*';
        if (dir_down)
        {
            row++;
        }
        else
        {
            row--;
        }
    }

    int index = 0;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (rail[i][j] == '*' && index < length)
            {
                rail[i][j] = cipher[index++];
            }
        }
    }

    row = 0, col = 0;
    for (int i = 0; i < length; i++)
    {
        if (row == 0)
        {
            dir_down = 1;
        }
        if (row == key - 1)
        {
            dir_down = 0;
        }
        if (rail[row][col] != '*')
        {
            result[i] = rail[row][col++];
        }
        if (dir_down)
        {
            row++;
        }
        else
        {
            row--;
        }
    }
    result[length] = '\0'; // Null-terminate the result
}

int main()
{
    char text[100], cipher_text_1[100], cipher_text_2[100], decrypted_text_1[100], decrypted_text_2[100];
    int key1, key2, i = 0, ch;

    printf("Enter the plain text: ");
    while ((ch = getchar()) != '\n' && i < 100)
    {
        text[i++] = ch;
    }
    text[i] = '\0'; // Null-terminate the input string

    printf("Enter the key for first Rail fence: ");
    scanf("%d", &key1);

    printf("Enter the key for second Rail fence: ");
    scanf("%d", &key2);

    removeSpace(text, i);

    rail_fence_encrypt(text, key1, cipher_text_1);
    rail_fence_encrypt(cipher_text_1, key2, cipher_text_2);
    printf("Encrypted text: %s\n", cipher_text_2);

    rail_fence_decrypt(cipher_text_2, key2, decrypted_text_1);
    rail_fence_decrypt(decrypted_text_1, key1, decrypted_text_2);
    printf("Decrypted text: %s\n", decrypted_text_2);

    return 0;
}
