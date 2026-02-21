# Hill Cipher Encryption

A C program that encrypts plaintext using the Hill cipher, a polygraphic substitution cipher based on linear algebra and matrix multiplication.

## How It Works
- Reads an encryption key matrix from a file
- Reads plaintext from a file, strips non-alphabetic characters, and converts to lowercase
- Pads plaintext with 'x' as needed to align with matrix size
- Encrypts using matrix multiplication mod 26
- Outputs the key matrix, formatted plaintext, and ciphertext (80 characters per line)

## Usage
gcc hill_cipher.c -o hill_cipher
./hill_cipher <key_file> <plaintext_file>

## Input Format

**Key file:**
2
3 3
2 5

First line is the matrix size, followed by the matrix values.

**Plaintext file:**
Any text file — non-alphabetic characters are automatically filtered out.

## Concepts Used
- Hill cipher cryptographic algorithm
- Matrix multiplication mod 26
- Dynamic memory allocation with malloc
- File I/O with fscanf and fgetc
- Command-line argument handling
- String manipulation and character filtering

## Course
Security in Computing (CIS 3360) – University of Central Florida
