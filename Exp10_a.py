def gronsfeld_encrypt(plaintext, key):
    filler = min(plaintext.lower())
    encrypted_text = ""
    key_length = len(key)

    for i, char in enumerate(plaintext):
        shift = int(key[i % key_length])
        new_char = chr(((ord(char.upper()) - 65 + shift) % 26) + 65)
        encrypted_text += new_char

    return encrypted_text

def main():
    plaintext = "GRONSFELD"
    key = "1234"

    encrypted_text = gronsfeld_encrypt(plaintext, key)
    print("Encrypted text:", encrypted_text)

if __name__ == "__main__":
    main()
