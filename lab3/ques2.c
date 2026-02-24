// # is epsilon

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 50

int n;
char prod[MAX][MAX];
char first[26][MAX];
char follow[26][MAX];

/* ---------- Utility ---------- */
int has(char *set, char c) {
  for (int i = 0; set[i]; i++)
    if (set[i] == c)
      return 1;
  return 0;
}

void add(char *set, char c) {
  if (!has(set, c)) {
    int l = strlen(set);
    set[l] = c;
    set[l + 1] = '\0';
  }
}

char get_fresh_nonterminal() {
  int used[26] = {0};

  for (int i = 0; i < n; i++)
    used[prod[i][0] - 'A'] = 1;

  for (char c = 'A'; c <= 'Z'; c++)
    if (!used[c - 'A'])
      return c;

  return '?'; // should never happen in lab grammars
}


/* ---------- LEFT FACTORING ---------- */
void left_factoring() {
  char new_prod[MAX][MAX];
  int new_n = 0;

  for (int i = 0; i < n;) {
    char A = prod[i][0];
    char prefix = prod[i][2];
    int count = 0;

    int j = i;
    while (j < n && prod[j][0] == A && prod[j][2] == prefix) {
      count++;
      j++;
    }

    if (count > 1) {
      char Aprime = get_fresh_nonterminal();
      sprintf(new_prod[new_n++], "%c=%c%c", A, prefix, Aprime);

      for (int k = i; k < j; k++) {
        if (prod[k][3])
          sprintf(new_prod[new_n++], "%c=%s", Aprime, prod[k] + 3);
        else
          sprintf(new_prod[new_n++], "%c=#", Aprime);
      }
    } else {
      strcpy(new_prod[new_n++], prod[i]);
    }

    i = j;
  }

  n = new_n;
  for (int i = 0; i < n; i++)
    strcpy(prod[i], new_prod[i]);
}

/* ---------- FIRST ---------- */
void compute_first() {
  int changed = 1;

  while (changed) {
    changed = 0;
    for (int i = 0; i < n; i++) {
      char A = prod[i][0];
      char *rhs = prod[i] + 2;

      for (int j = 0; rhs[j]; j++) {
        if (!isupper(rhs[j])) {
          if (!has(first[A - 'A'], rhs[j])) {
            add(first[A - 'A'], rhs[j]);
            changed = 1;
          }
          break;
        } else {
          char B = rhs[j];
          for (int k = 0; first[B - 'A'][k]; k++) {
            if (first[B - 'A'][k] != '#' &&
                !has(first[A - 'A'], first[B - 'A'][k])) {
              add(first[A - 'A'], first[B - 'A'][k]);
              changed = 1;
            }
          }
          if (!has(first[B - 'A'], '#'))
            break;
        }
      }
    }
  }
}

/* ---------- FOLLOW ---------- */
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
              if (!has(follow[B - 'A'], rhs[k])) {
                add(follow[B - 'A'], rhs[k]);
                changed = 1;
              }
              break;
            } else {
              char C = rhs[k];
              for (int x = 0; first[C - 'A'][x]; x++) {
                if (first[C - 'A'][x] != '#' &&
                    !has(follow[B - 'A'], first[C - 'A'][x])) {
                  add(follow[B - 'A'], first[C - 'A'][x]);
                  changed = 1;
                }
              }
              if (!has(first[C - 'A'], '#'))
                break;
              nullable = 1;
            }
          }

          if (j == strlen(rhs) - 1 || nullable) {
            for (int x = 0; follow[A - 'A'][x]; x++) {
              if (!has(follow[B - 'A'], follow[A - 'A'][x])) {
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

/* ---------- MAIN ---------- */
int main() {
  printf("Enter number of productions: ");
  scanf("%d", &n);

  printf("Enter productions (A=aB form, # for epsilon):\n");
  for (int i = 0; i < n; i++)
    scanf("%s", prod[i]);

  left_factoring();

  printf("\nGrammar after left factoring:\n");
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