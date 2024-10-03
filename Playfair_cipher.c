#include <stdio.h>
void prepareKeyMatrix(char key[], char keyMatrix[5][5]) {
    int dict[26] = {0};
    int i, j, k = 0;

    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'j') key[i] = 'i';
        if (dict[key[i] - 'a'] == 0) {
            keyMatrix[k / 5][k % 5] = key[i];
            dict[key[i] - 'a'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i + 'a' == 'j') continue; 
        if (dict[i] == 0) {
            keyMatrix[k / 5][k % 5] = i + 'a';
            k++;
        }
    }
}

void displayKeyMatrix(char keyMatrix[5][5]) {
    int i, j;
    printf("5x5 Key Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void findPositionByValue(char ch, char keyMatrix[5][5], int positions[2]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyMatrix[i][j] == ch) {
                positions[0] = i;
                positions[1] = j;
                return;
            }
        }
    }
}

int isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

int stringLength(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void encryptPair(char ch1, char ch2, char keyMatrix[5][5], char encryptedPair[2]) {
    int pos1[2], pos2[2];

    findPositionByValue(ch1, keyMatrix, pos1);
    findPositionByValue(ch2, keyMatrix, pos2);

    if (pos1[0] == pos2[0]) { 
        encryptedPair[0] = keyMatrix[pos1[0]][(pos1[1] + 1) % 5];
        encryptedPair[1] = keyMatrix[pos2[0]][(pos2[1] + 1) % 5];
    } else if (pos1[1] == pos2[1]) {
        encryptedPair[0] = keyMatrix[(pos1[0] + 1) % 5][pos1[1]];
        encryptedPair[1] = keyMatrix[(pos2[0] + 1) % 5][pos2[1]];
    } else { 
        encryptedPair[0] = keyMatrix[pos1[0]][pos2[1]];
        encryptedPair[1] = keyMatrix[pos2[0]][pos1[1]];
    }
}

void prepareText(char text[], char preparedText[]) {
    int i, k = 0;
    int len = stringLength(text);

    for (i = 0; i < len; i++) {
        if (text[i] == 'j') text[i] = 'i'; 
        if (isAlpha(text[i])) {
            preparedText[k++] = toLower(text[i]);
            if (k > 1 && preparedText[k-1] == preparedText[k-2]) {
                preparedText[k++] = 'x'; 
            }
        }
    }
    if (k % 2 != 0) {
        preparedText[k++] = 'x';
    }
    preparedText[k] = '\0';
}

void encryptText(char text[], char keyMatrix[5][5]) {
    char encryptedPair[2];
    for (int i = 0; text[i] != '\0'; i += 2) {
        encryptPair(text[i], text[i + 1], keyMatrix, encryptedPair);
        text[i] = encryptedPair[0];
        text[i + 1] = encryptedPair[1];
    }
}

int main() {
    char key[100], text[100];
    char keyMatrix[5][5];
    char preparedText[100];

    printf("Enter key: ");
    scanf("%s", key);

    printf("Enter text: ");
    scanf("%s", text);

    prepareKeyMatrix(key, keyMatrix);
    displayKeyMatrix(keyMatrix); 
    prepareText(text, preparedText);
    encryptText(preparedText, keyMatrix);

    printf("Encrypted text: %s\n", preparedText);

    return 0;
}
