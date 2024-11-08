import random
from sympy import isprime, primerange

def generate_prime():
    prime_candidate = random.choice(list(primerange(50, 100)))
    return prime_candidate

def find_primitive_root(p):
    for g in range(2, p):
        if pow(g, (p - 1) // 2, p) != 1:
            return g
    return None

def alice_generate_keys(p, g):
    a = random.randint(1, p - 1)
    A = pow(g, a, p)
    return a, A

def bob_generate_keys(p, g):
    b = random.randint(1, p - 1)
    B = pow(g, b, p)
    return b, B

def alice_compute_shared_secret(a, B, p):
    shared_secret_A = pow(B, a, p)
    return shared_secret_A

def bob_compute_shared_secret(b, A, p):
    shared_secret_B = pow(A, b, p)
    return shared_secret_B

p = generate_prime()
g = find_primitive_root(p)

print(f"Generated Prime (p): {p}")
print(f"Primitive Root (g): {g}")

a, A = alice_generate_keys(p, g)
print(f"Alice's Public Key: {A}")

b, B = bob_generate_keys(p, g)
print(f"Bob's Public Key: {B}")

shared_secret_A = alice_compute_shared_secret(a, B, p)
shared_secret_B = bob_compute_shared_secret(b, A, p)

print(f"Alice's Shared Secret: {shared_secret_A}")
print(f"Bob's Shared Secret: {shared_secret_B}")
if shared_secret_A == shared_secret_B:
    print("The shared secret is successfully established!")
else:
    print("Something went wrong with the key exchange.")

