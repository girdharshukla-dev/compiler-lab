#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int n;
char prod[MAX][MAX];

char first[26][MAX];
char follow[26][MAX];

int used[26];  // track used non-terminals

/* ---------------- Utility ---------------- */

int contains(char *set, char c) {
    for (int i = 0; set[i]; i++)
        if (set[i] == c) return 1;
    return 0;
}

void add(char *set, char c) {
    if (!contains(set, c)) {
        int l = strlen(set);
        set[l] = c;
        set[l + 1] = '\0';
    }
}

char get_fresh_nonterminal() {
    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            used[i] = 1;
            return 'A' + i;
        }
    }
    return '?';  // should never happen in lab grammars
}

/* ---------------- Left Recursion ---------------- */

void remove_left_recursion() {
    char new_prod[MAX][MAX];
    int new_n = 0;

    for (int i = 0; i < n;) {

        char A = prod[i][0];
        char alpha[MAX][MAX], beta[MAX][MAX];
        int ac = 0, bc = 0;

        int j = i;
        while (j < n && prod[j][0] == A) {
            if (prod[j][2] == A)
                strcpy(alpha[ac++], prod[j] + 3);
            else
                strcpy(beta[bc++], prod[j] + 2);
            j++;
        }

        if (ac > 0) {
            char Aprime = get_fresh_nonterminal();

            for (int k = 0; k < bc; k++)
                sprintf(new_prod[new_n++], "%c=%s%c", A, beta[k], Aprime);

            for (int k = 0; k < ac; k++)
                sprintf(new_prod[new_n++], "%c=%s%c", Aprime, alpha[k], Aprime);

            sprintf(new_prod[new_n++], "%c=#", Aprime);

        } else {
            for (int k = i; k < j; k++)
                strcpy(new_prod[new_n++], prod[k]);
        }

        i = j;
    }

    n = new_n;
    for (int i = 0; i < n; i++)
        strcpy(prod[i], new_prod[i]);
}

/* ---------------- FIRST ---------------- */

void compute_first() {
    int changed = 1;

    while (changed) {
        changed = 0;

        for (int i = 0; i < n; i++) {
            char A = prod[i][0];
            char *rhs = prod[i] + 2;

            for (int j = 0; rhs[j]; j++) {

                if (!isupper(rhs[j])) {
                    if (!contains(first[A - 'A'], rhs[j])) {
                        add(first[A - 'A'], rhs[j]);
                        changed = 1;
                    }
                    break;
                }

                char B = rhs[j];

                for (int k = 0; first[B - 'A'][k]; k++) {
                    char c = first[B - 'A'][k];
                    if (c != '#' && !contains(first[A - 'A'], c)) {
                        add(first[A - 'A'], c);
                        changed = 1;
                    }
                }

                if (!contains(first[B - 'A'], '#'))
                    break;

                if (rhs[j + 1] == '\0') {
                    if (!contains(first[A - 'A'], '#')) {
                        add(first[A - 'A'], '#');
                        changed = 1;
                    }
                }
            }
        }
    }
}

/* ---------------- FOLLOW ---------------- */

void compute_follow() {
    add(follow[prod[0][0] - 'A'], '$');

    int changed = 1;

    while (changed) {
        changed = 0;

        for (int i = 0; i < n; i++) {

            char A = prod[i][0];
            char *rhs = prod[i] + 2;

            for (int j = 0; rhs[j]; j++) {

                if (isupper(rhs[j])) {

                    char B = rhs[j];
                    int nullable = 1;

                    for (int k = j + 1; rhs[k]; k++) {
                        nullable = 0;

                        if (!isupper(rhs[k])) {
                            if (!contains(follow[B - 'A'], rhs[k])) {
                                add(follow[B - 'A'], rhs[k]);
                                changed = 1;
                            }
                            break;
                        }

                        char C = rhs[k];

                        for (int x = 0; first[C - 'A'][x]; x++) {
                            char c = first[C - 'A'][x];
                            if (c != '#' && !contains(follow[B - 'A'], c)) {
                                add(follow[B - 'A'], c);
                                changed = 1;
                            }
                        }

                        if (!contains(first[C - 'A'], '#'))
                            break;

                        nullable = 1;
                    }

                    if (rhs[j + 1] == '\0' || nullable) {
                        for (int x = 0; follow[A - 'A'][x]; x++) {
                            if (!contains(follow[B - 'A'], follow[A - 'A'][x])) {
                                add(follow[B - 'A'], follow[A - 'A'][x]);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

/* ---------------- MAIN ---------------- */

int main() {

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (A=aB form, # for epsilon):\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        used[prod[i][0] - 'A'] = 1;
    }

    remove_left_recursion();

    printf("\nGrammar after removing left recursion:\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", prod[i]);

    compute_first();
    compute_follow();

    printf("\nFIRST sets:\n");
    for (int i = 0; i < 26; i++)
        if (first[i][0])
            printf("FIRST(%c) = { %s }\n", i + 'A', first[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < 26; i++)
        if (follow[i][0])
            printf("FOLLOW(%c) = { %s }\n", i + 'A', follow[i]);

    return 0;
}