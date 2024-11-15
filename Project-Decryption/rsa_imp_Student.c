#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to calculate greatest common divisor (GCD) of two numbers
unsigned long gcd(unsigned long a, unsigned long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate modulo inverse using extended Euclidean algorithm
unsigned long modInverse(unsigned long a, unsigned long m) {
    long t = 0;
    long newT = 1;
    long r = m;
    long newR = a;
    long quotient, temp;

    while (newR != 0) {
        quotient = r / newR;

        temp = t;
        t = newT;
        newT = temp - quotient * newT;

        temp = r;
        r = newR;
        newR = temp - quotient * newR;
    }

    if (r > 1) {
        return -1; 
    if (t < 0) {
        t = t + m;
    }
    return t;
}

// Function to generate keys for RSA encryption
void generateKeys(unsigned long p, unsigned long q, unsigned long *n, unsigned long *e, unsigned long *d) {
    *n = p * q;
    unsigned long phi = (p - 1) * (q - 1); // f(n) = (p-1) * (q-1)

    // Seed random number gen
    srand(time(NULL));  

    // random e that is 1 < e < f(n) and gcd(e, f(n)) = 1
    do {
        *e = rand() % (phi - 2) + 2;  //picking e
    } while (gcd(*e, phi) != 1);  // Keep trying until gcd(e, f(n)) = 1

    // Calculate d = e * d = 1 (mod f(n))
    *d = modInverse(*e, phi);
}

// Function to encrypt plaintext using RSA
unsigned long encrypt(unsigned long plaintext, unsigned long e, unsigned long n) {
    unsigned long result = 1;
    unsigned long i;
    for (i = 0; i < e; i++) {
        result = (result * plaintext) % n;
    }
    return result;
}

// Function to decrypt ciphertext using RSA
unsigned long decrypt(unsigned long ciphertext, unsigned long d, unsigned long n) {
    unsigned long result = 1;
    unsigned long i;
    for (i = 0; i < d; i++) {
        result = (result * ciphertext) % n;
    }
    return result;
}

int main() {
    unsigned long p, q;
    unsigned long n, e, d;

    printf("Enter p and q: ");
    scanf("%lu %lu", &p, &q);

    // Generate RSA keys
    generateKeys(p, q, &n, &e, &d);
    printf("Public key (e, n): (%lu, %lu)\n", e, n);
    printf("Private key (d, n): (%lu, %lu)\n\n", d, n);

    // Encrypt and decrypt a sample plaintext
    unsigned long plaintext;
    printf("Enter an integer between 0 and n-1 as plain text to be encrypted: ");
    scanf("%lu", &plaintext);
    printf("Original plaintext: %lu\n", plaintext);

    unsigned long ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lu\n", ciphertext);

    unsigned long decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lu\n\n", decrypted);

    return 0;
}
