import numpy as np

def mod_inverse(a, m):
    a = a % m
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return -1

def determinant(matrix, mod):
    det = int(np.round(np.linalg.det(matrix))) % mod
    return det

def inverse_matrix(matrix, mod):
    det = determinant(matrix, mod)
    inv_det = mod_inverse(det, mod)
    if inv_det == -1:
        raise ValueError("Matrix is not invertible under mod 26.")
    adjugate_matrix = np.round(np.linalg.inv(matrix) * np.linalg.det(matrix)).astype(int) % mod
    inv_matrix = (inv_det * adjugate_matrix) % mod
    return inv_matrix

def text_to_numbers(text):
    return [ord(char) - ord('A') for char in text]

def numbers_to_text(numbers):
    return ''.join([chr((num % 26) + ord('A')) for num in numbers])

def pad_text(text, matrix_size):
    while len(text) % matrix_size != 0:
        text += 'Z'
    return text

def hill_cipher_encrypt(plaintext, key_matrix):
    matrix_size = len(key_matrix)
    plaintext = pad_text(plaintext.upper(), matrix_size)
    plaintext_nums = text_to_numbers(plaintext)
    ciphertext = []
    for i in range(0, len(plaintext_nums), matrix_size):
        vector = np.array(plaintext_nums[i:i + matrix_size])
        encrypted_vector = np.dot(key_matrix, vector) % 26
        ciphertext.extend(encrypted_vector)
    return numbers_to_text(ciphertext)

def hill_cipher_decrypt(ciphertext, key_matrix):
    matrix_size = len(key_matrix)
    ciphertext_nums = text_to_numbers(ciphertext)
    try:
        inv_key_matrix = inverse_matrix(key_matrix, 26)
    except ValueError as e:
        print(e)
        return None
    plaintext = []
    for i in range(0, len(ciphertext_nums), matrix_size):
        vector = np.array(ciphertext_nums[i:i + matrix_size])
        decrypted_vector = np.dot(inv_key_matrix, vector) % 26
        plaintext.extend(decrypted_vector)
    return numbers_to_text(plaintext)

def main():
    plaintext = input("Enter plaintext (uppercase letters only): ").upper()
    key_matrix = np.array([[6, 24, 1], [13, 16, 10], [20, 17, 15]])
    print("Original Plaintext:", plaintext)
    ciphertext = hill_cipher_encrypt(plaintext, key_matrix)
    print("Ciphertext:", ciphertext)
    decrypted_text = hill_cipher_decrypt(ciphertext, key_matrix)
    if decrypted_text:
        print("Decrypted Plaintext:", decrypted_text)

if __name__ == "__main__":
    main()
