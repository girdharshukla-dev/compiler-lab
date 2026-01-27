#include <stdio.h>
#include <string.h>

int simulate_nfa(char *str) {
    // current active states
    int in_q0 = 1;  // start state
    int in_q1 = 0;  // accept state

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        int next_q0 = 0;
        int next_q1 = 0;

        // From q0
        if (in_q0) {
            if (c == '0') {
                next_q0 = 1;
            }
            else if (c == '1') {
                next_q0 = 1;  // stay in q0
                next_q1 = 1;  // guess this is last 1
            }
        }

        // From q1 → no outgoing transitions

        in_q0 = next_q0;
        in_q1 = next_q1;
    }

    return in_q1;  // accept if q1 is active
}

int main() {
    char input[100];

    while (1) {
        printf("Enter binary string (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        if (simulate_nfa(input))
            printf("ACCEPTED (ends with 1)\n");
        else
            printf("REJECTED\n");
    }

    return 0;
}
