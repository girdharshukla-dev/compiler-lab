#include <stdio.h>
#include <string.h>

typedef enum {
    S0,   // Start
    S1,   // Last char was 'a'
    S2    // Ends with "ab" (accept)
} State;

// DFA transition function
State transition(State s, char c) {
    switch (s) {
        case S0:
            if (c == 'a') return S1;
            if (c == 'b') return S0;
            break;

        case S1:
            if (c == 'a') return S1;
            if (c == 'b') return S2;
            break;

        case S2:
            if (c == 'a') return S1;
            if (c == 'b') return S0;
            break;
    }
    return S0;  // default safe fallback
}

void check_string(char *str) {
    State state = S0;

    for (int i = 0; str[i] != '\0'; i++) {
        state = transition(state, str[i]);
    }

    if (state == S2)
        printf("String Accepted (ends with 'ab')\n");
    else
        printf("String Rejected\n");
}

int main() {
    char input[100];

    while (1) {
        printf("Enter string over {a,b} (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        check_string(input);
    }

    return 0;
}

//ends with ab