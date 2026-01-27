#include <stdio.h>
#include <string.h>

typedef enum {
    START,

    I1, I2, I3,          // int path
    L1, L2, L3, L4,      // long path
    D1, D2, D3, D4, D5, D6,  // double path

    DEAD
} State;

State transition(State s, char c) {
    switch (s) {
        // ---- START BRANCH ----
        case START:
            if (c == 'i') return I1;
            if (c == 'l') return L1;
            if (c == 'd') return D1;
            return DEAD;

        // ---- int ----
        case I1: return (c == 'n') ? I2 : DEAD;
        case I2: return (c == 't') ? I3 : DEAD;

        // ---- long ----
        case L1: return (c == 'o') ? L2 : DEAD;
        case L2: return (c == 'n') ? L3 : DEAD;
        case L3: return (c == 'g') ? L4 : DEAD;

        // ---- double ----
        case D1: return (c == 'o') ? D2 : DEAD;
        case D2: return (c == 'u') ? D3 : DEAD;
        case D3: return (c == 'b') ? D4 : DEAD;
        case D4: return (c == 'l') ? D5 : DEAD;
        case D5: return (c == 'e') ? D6 : DEAD;

        default:
            return DEAD;
    }
}

void identify(char *str) {
    State state = START;

    for (int i = 0; str[i] != '\0'; i++) {
        state = transition(state, str[i]);
        if (state == DEAD) break;
    }

    if (state == I3 && strlen(str) == 3)
        printf("Keyword: INT\n");
    else if (state == L4 && strlen(str) == 4)
        printf("Keyword: LONG\n");
    else if (state == D6 && strlen(str) == 6)
        printf("Keyword: DOUBLE\n");
    else
        printf("Not a valid keyword\n");
}

int main() {
    char input[50];

    while (1) {
        printf("Enter string (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        identify(input);
    }

    return 0;
}
