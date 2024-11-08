def gronsfeld_encrypt(plaintext, key):
    encrypted_text = ""
    key_length = len(key)

    key_index = 0  # Separate index for the key to skip spaces in the plaintext
    for char in plaintext:
        if char == " ":  # Preserve spaces in the output
            encrypted_text += " "
            continue
        shift = int(key[key_index % key_length])  # Determine the shift based on the key
        new_char = chr(((ord(char.upper()) - 65 + shift) % 26) + 65)
        encrypted_text += new_char
        key_index += 1  # Increment key_index only if the character is not a space

    return encrypted_text

def main():
    plaintext = "RAG BABY"
    key = "1234"

    encrypted_text = gronsfeld_encrypt(plaintext, key)
    print("Encrypted text:", encrypted_text)

if __name__ == "__main__":
    main()
