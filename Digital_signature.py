def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(e, phi):
    d_old, d_new = 0, 1
    r_old, r_new = phi, e
    while r_new != 0:
        quotient = r_old // r_new
        r_old, r_new = r_new, r_old - quotient * r_new
        d_old, d_new = d_new, d_old - quotient * d_new
    return d_old % phi

def rsa_keygen(p, q):
    n = p * q
    phi = (p - 1) * (q - 1)
    e = 65537
    if gcd(e, phi) != 1:
        for i in range(2, phi):
            if gcd(i, phi) == 1:
                e = i
                break
    d = mod_inverse(e, phi)
    return (e, n), (d, n)

def rsa_encrypt_decrypt(message, key, n):
    return pow(message, key, n)

def hash_function(message):
    return sum([ord(c) for c in message]) % 256

def sign_message(message, private_key, n):
    hashed_msg = hash_function(message)
    signature = rsa_encrypt_decrypt(hashed_msg, private_key, n)
    return signature

def verify_signature(message, signature, public_key, n):
    hashed_msg = hash_function(message)
    decrypted_hash = rsa_encrypt_decrypt(signature, public_key, n)
    return hashed_msg == decrypted_hash

p = 61
q = 53
public_key, private_key = rsa_keygen(p, q)
message = " Sumeet Kapadia "
print("Message:", message)
signature = sign_message(message, private_key[0], private_key[1])
print("Signature:", signature)
verification = verify_signature(message, signature, public_key[0], public_key[1])
print("Verification successful:", verification)
