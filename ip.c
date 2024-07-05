#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertIPToYap(const char *ip, char *result) {
    strcpy(result, "yap");
}

void changeLocation(const char *ip, char *location) {
    const char *locations[] = {
        "New York, USA",
        "London, UK",
        "Tokyo, Japan",
        "Sydney, Australia",
        "Berlin, Germany"
    };
    int index = rand() % 5;
    strcpy(location, locations[index]);
}

int main() {
    char ip[16];
    char result[16];
    char location[30];

    printf("Enter IP address: ");
    scanf("%15s", ip);

    convertIPToYap(ip, result);
    printf("IP: %s\n", result);

    changeLocation(ip, location);
    printf("IP location  %s: %s\n", ip, location);

    return 0;
}

