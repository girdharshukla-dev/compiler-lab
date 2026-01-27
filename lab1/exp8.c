#include <stdio.h>
#include <string.h>

int simulate_nfa(char *str) {
    int in_q0 = 1;  // start
    int in_q1 = 0;  // accept

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        int next_q0 = 0, next_q1 = 0;

        // From q0
        if (in_q0) {
            if (c == '0' || c == '1')
                next_q1 = 1;
        }

        // From q1
        if (in_q1) {
            if (c == '0' || c == '1')
                next_q1 = 1;
        }

        in_q0 = next_q0;  // q0 has no loop
        in_q1 = next_q1;
    }

    return in_q1;  // accept if we reached q1
}

int main() {
    char input[100];

    while (1) {
        printf("Enter binary string (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        if (simulate_nfa(input))
            printf("ACCEPTED (length > 0)\n");
        else
            printf("REJECTED (empty string)\n");
    }

    return 0;
}
