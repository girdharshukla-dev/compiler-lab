#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    START,
    INT,
    DOT,
    FRAC,
    DEAD
} State;

State transition(State s, char c) {
    switch (s) {

        case START:
            if (isdigit(c)) return INT;
            return DEAD;

        case INT:
            if (isdigit(c)) return INT;
            if (c == '.')   return DOT;
            return DEAD;

        case DOT:
            if (isdigit(c)) return FRAC;
            return DEAD;

        case FRAC:
            if (isdigit(c)) return FRAC;
            return DEAD;

        default:
            return DEAD;
    }
}

void check_number(char *str) {
    State state = START;

    for (int i = 0; str[i] != '\0'; i++) {
        state = transition(state, str[i]);
        if (state == DEAD)
            break;
    }

    if (state == INT)
        printf("Valid Integer\n");
    else if (state == FRAC)
        printf("Valid Floating Number\n");
    else
        printf("Invalid Number\n");
}

int main() {
    char input[100];

    while (1) {
        printf("Enter number (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        check_number(input);
    }

    return 0;
}
