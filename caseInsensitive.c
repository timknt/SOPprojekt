#include "caseInsensitive.h"

void caseInsensitive(char *string ) {
    if (string == NULL) {
        return;
    }
    while (*string != '\0') {
        *string = tolower((unsigned char)*string);
        string++;
    }
}

void testCaseInsensitive() {
    char *string = malloc(10);
    strcpy(string, "HeLlo WOrLd");
    caseInsensitive(string);
    printf("%s\n", string);
}
