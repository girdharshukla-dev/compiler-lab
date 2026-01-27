#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    START,
    ID,
    DEAD
} State;

// Transition function δ(q, a)
State transition(State s, char c) {
    switch (s) {
        case START:
            if (isalpha(c) || c == '_')
                return ID;
            else
                return DEAD;

        case ID:
            if (isalnum(c) || c == '_')
                return ID;
            else
                return DEAD;

        default:
            return DEAD;
    }
}

void check_identifier(char *str) {
    State state = START;

    for (int i = 0; str[i] != '\0'; i++) {
        state = transition(state, str[i]);
        if (state == DEAD)
            break;
    }

    if (state == ID)
        printf("Valid Identifier\n");
    else
        printf("Invalid Identifier\n");
}

int main() {
    char input[100];

    while (1) {
        printf("Enter string (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        check_identifier(input);
    }

    return 0;
}

