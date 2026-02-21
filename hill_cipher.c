#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Function to read the encryption key matrix from a file
void loadEncryptionKey(char* keyFile, int** keyMatrix, int* size) {
FILE* file = fopen(keyFile, "r");
if (file == NULL) {
perror("Error opening key file");
exit(1);
}
fscanf(file, "%d", size);
*keyMatrix = (int*)malloc(*size * *size * sizeof(int));
if (*keyMatrix == NULL) {
perror("Memory allocation failed");
fclose(file);
exit(1);
}
for (int i = 0; i < *size; i++) {
for (int j = 0; j < *size; j++) {
fscanf(file, "%d", &(*keyMatrix)[i * *size + j]);
}
}
fclose(file);
}
// Function to read the plaintext from a file and store only lowercase letters
void loadPlaintext(char* plaintextFile, char* text) {
FILE* file = fopen(plaintextFile, "r");
if (file == NULL) {
perror("Error opening plaintext file");
exit(1);
}
int index = 0;
char character;
while ((character = fgetc(file)) != EOF && index < 10000) {
if (isalpha(character)) {
text[index++] = tolower(character);
}
}
// Pad with 'x' if needed
while (index % 4 != 0) {
text[index++] = 'x';
}
text[index] = '\0';
fclose(file);
}
// Function to encrypt the plaintext using the Hill cipher
void performEncryption(char* text, int* keyMatrix, int size, char* encryptedText) {
int textLength = strlen(text);
for (int i = 0; i < textLength; i += size) {
for (int j = 0; j < size; j++) {
int sum = 0;
for (int k = 0; k < size; k++) {
sum += (keyMatrix[j * size + k] * (text[i + k] - 'a'));
}
encryptedText[i + j] = (sum % 26) + 'a';
}
}
}
int main(int argumentsCount, char* arguments[]) {
if (argumentsCount != 3) {
printf("Usage: %s <key_file> <plaintext_file>\n", arguments[0]);
return 1;
}
char* keyFile = arguments[1];
char* plaintextFile = arguments[2];
int size; // Matrix size
int* keyMatrix; // Encryption key matrix
char plaintext[10000]; // Plaintext array
char ciphertext[10000]; // Ciphertext array
// Read the encryption key matrix from the key file
loadEncryptionKey(keyFile, &keyMatrix, &size);
// Read the plaintext from the plaintext file
loadPlaintext(plaintextFile, plaintext);
// Encrypt the plaintext using the Hill cipher
performEncryption(plaintext, keyMatrix, size, ciphertext);
// Output the key matrix
printf("Key matrix:\n");
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
printf("%d ", keyMatrix[i * size + j]);
}
printf("\n");
}
// Output the plaintext
printf("Plaintext:\n%s\n", plaintext);
// Output the ciphertext
printf("Ciphertext:\n");
// Print ciphertext in rows of 80 characters
int ciphertextLength = strlen(ciphertext);
for (int i = 0; i < ciphertextLength; i++) {
putchar(ciphertext[i]);
if ((i + 1) % 80 == 0) {
printf("\n");
}
}
printf("\n");
// Free dynamically allocated memory
free(keyMatrix);
return 0;
}
