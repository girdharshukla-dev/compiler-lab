#include <stdio.h>
#include <string.h>

int simulate_nfa(char *str) {
    int in_q0 = 1;  // start
    int in_q1 = 0;
    int in_q2 = 0;  // accept

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        int next_q0 = 0, next_q1 = 0, next_q2 = 0;

        // From q0
        if (in_q0) {
            if (c == '0') {
                next_q0 = 1;   // stay in q0
                next_q1 = 1;   // guess start of "01"
            }
            else if (c == '1') {
                next_q0 = 1;   // stay in q0
            }
        }

        // From q1
        if (in_q1) {
            if (c == '1') {
                next_q2 = 1;   // completed "01"
            }
        }

        // q2 has no outgoing transitions

        in_q0 = next_q0;
        in_q1 = next_q1;
        in_q2 = next_q2;
    }

    return in_q2;
}

int main() {
    char input[100];

    while (1) {
        printf("Enter binary string (q to quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            break;

        if (simulate_nfa(input))
            printf("ACCEPTED (ends with 01)\n");
        else
            printf("REJECTED\n");
    }

    return 0;
}
