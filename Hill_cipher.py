import numpy as np

class HillCipher:
    def get_key_matrix(self):
        key = input("Enter key matrix: ")
        sq = len(key) ** 0.5
        if sq != int(sq):
            raise ValueError("Cannot form a square matrix")
        length = int(sq)
        key_matrix = np.zeros((length, length), dtype=int)
        
        k = 0
        for i in range(length):
            for j in range(length):
                key_matrix[i][j] = ord(key[k]) - 97
                k += 1
        return key_matrix

    def is_valid_matrix(self, key_matrix):
        det = key_matrix[0][0] * key_matrix[1][1] - key_matrix[0][1] * key_matrix[1][0]
        if det == 0:
            raise ValueError("Det equals to zero, invalid key matrix!")

    def is_valid_reverse_matrix(self, key_matrix, reverse_matrix):
        product = np.dot(key_matrix, reverse_matrix) % 26
        if not np.array_equal(product, np.array([[1, 0], [0, 1]])):
            raise ValueError("Invalid reverse matrix found!")

    def reverse_matrix(self, key_matrix):
        detmod26 = (key_matrix[0][0] * key_matrix[1][1] - key_matrix[0][1] * key_matrix[1][0]) % 26
        factor = 0
        for factor in range(1, 26):
            if (detmod26 * factor) % 26 == 1:
                break
        reverse_matrix = np.zeros((2, 2), dtype=int)
        reverse_matrix[0][0] = key_matrix[1][1] * factor % 26
        reverse_matrix[0][1] = (26 - key_matrix[0][1]) * factor % 26
        reverse_matrix[1][0] = (26 - key_matrix[1][0]) * factor % 26
        reverse_matrix[1][1] = key_matrix[0][0] * factor % 26
        return reverse_matrix

    def echo_result(self, label, adder, phrase):
        print(label, end="")
        for i in range(0, len(phrase), 2):
            print(chr(phrase[i] + (64 + adder)), end="")
            print(chr(phrase[i + 1] + (64 + adder)), end="")
            if i + 2 < len(phrase):
                print("-", end="")
        print()

    def encrypt(self, phrase, alpha_zero):
        adder = 1 if alpha_zero else 0
        key_matrix = self.get_key_matrix()
        self.is_valid_matrix(key_matrix)
        
        phrase = ''.join(filter(str.isalpha, phrase)).upper()
        if len(phrase) % 2 == 1:
            phrase += "Q"

        phrase_to_num = [ord(char) - (64 + adder) for char in phrase]
        phrase_encoded = []

        for i in range(0, len(phrase_to_num), 2):
            x = (key_matrix[0][0] * phrase_to_num[i] + key_matrix[0][1] * phrase_to_num[i + 1]) % 26
            y = (key_matrix[1][0] * phrase_to_num[i] + key_matrix[1][1] * phrase_to_num[i + 1]) % 26
            phrase_encoded.append(x if alpha_zero else (x if x != 0 else 26))
            phrase_encoded.append(y if alpha_zero else (y if y != 0 else 26))

        self.echo_result("Encoded phrase: ", adder, phrase_encoded)

    def decrypt(self, phrase, alpha_zero):
        adder = 1 if alpha_zero else 0
        key_matrix = self.get_key_matrix()
        self.is_valid_matrix(key_matrix)

        phrase = ''.join(filter(str.isalpha, phrase)).upper()
        phrase_to_num = [ord(char) - (64 + adder) for char in phrase]

        rev_key_matrix = self.reverse_matrix(key_matrix)
        self.is_valid_reverse_matrix(key_matrix, rev_key_matrix)

        phrase_decoded = []
        for i in range(0, len(phrase_to_num), 2):
            phrase_decoded.append((rev_key_matrix[0][0] * phrase_to_num[i] + rev_key_matrix[0][1] * phrase_to_num[i + 1]) % 26)
            phrase_decoded.append((rev_key_matrix[1][0] * phrase_to_num[i] + rev_key_matrix[1][1] * phrase_to_num[i + 1]) % 26)

        self.echo_result("Decoded phrase: ", adder, phrase_decoded)

if __name__ == "__main__":
    cipher = HillCipher()
    print("Hill Cipher Implementation (2x2)")
    print("-------------------------")
    print("1. Encrypt text (A=0,B=1,...Z=25)")
    print("2. Decrypt text (A=0,B=1,...Z=25)")
    print("3. Encrypt text (A=1,B=2,...Z=26)")
    print("4. Decrypt text (A=1,B=2,...Z=26)")
    print()
    print("Type any other character to exit")
    print()

    while True:
        opt = input("Select your choice: ")
        if opt not in ["1", "2", "3", "4"]:
            break

        phrase = input("Enter phrase: ")
        if opt == "1":
            cipher.encrypt(phrase, True)
        elif opt == "2":
            cipher.decrypt(phrase, True)
        elif opt == "3":
            cipher.encrypt(phrase, False)
        elif opt == "4":
            cipher.decrypt(phrase, False)
