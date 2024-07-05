#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha256_hash(const char *input, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0'; // Null-terminate the output string
}

int main() {
    char password[100];
    char hashed_password[65];

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    sha256_hash(password, hashed_password);

    printf("Original Password: %s\n", password);
    printf("Hashed Password (SHA-256): %s\n", hashed_password);

    return 0;
}

