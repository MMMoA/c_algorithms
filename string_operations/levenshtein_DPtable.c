#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *data;
    int size;
} str_t;

typedef struct {
    int *table;
    int rows;
    int columns;
    str_t s;
    str_t t;
    int *edit_distance;
} table_t;

void _print_table(table_t *table);
table_t _init_table(int rows, int columns);
table_t calulate_levenshtein_distance(char *s, char *t);
void _fill_table(table_t *t);
void print_backtracking(table_t *t);
int* _min_backtracking(int *p_left, int *p_above, int *p_leftabove);

/**
 * Horrendous print loops to prettily print the table to the terminal.
 */
void _print_table(table_t *table) {
    short _cw = table->t.size / 10 + 3;

    for (int i = -1; i < table->rows; i++) {
        for (int j = -1; j < table->columns; j++) {
            if(i == -1) { // Print the top line
                if (j == -1) {
                    printf("%*s", _cw, " ");
                } else if(j == 0) {
                    printf("%*s", _cw, "-");
                } else if(j > 0) {
                    printf("%*c", _cw, table->t.data[j-1]);
                }
            } else if (i > -1) { // All following lines
                if (j == -1) { // Special case for first column to print the downward string here
                    if (i == 0) {
                        printf("%*s", _cw, "-");
                    } else {
                        printf("%*c", _cw, table->s.data[i-1]);
                    }
                } else { // Finally just do the array
                    printf("%*d", _cw, *(table->table + i * table->columns + j));
                }
            }

        }
        printf("\n");
    }
}

/**
 * Initializes the base values of the table.
 */
table_t _init_table(int rows, int columns) {
    table_t set;
    set.table = (int*) malloc(rows * columns * sizeof(int)); // Allocate memory for the table.
    set.columns = columns;
    set.rows = rows;
    // Fill the array with initial values
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0) {
                *(set.table + i * columns +j) = j; // Top row
            } else if (j == 0) {
                *(set.table + i * columns +j) = i; // first column
            } else {
                *(set.table + i * columns +j) = 0;
            }
        }
    }
    return set;
}

/**
 * Fills the table according to the recursive definition of editing distance.
 */
void _fill_table(table_t *t) {
    for (int i = 1; i < t->rows; i++) {
        for (int j = 1; j < t->columns; j++) {
            int min;
            // First check left above, if the values are equal, just take that value, otherwise add 1.
            min = *(t->table + (i-1) * t->columns + (j-1)) + (t->s.data[i-1] != t->t.data[j-1] ? 1 : 0);

            // Next look to the left for a possibly smaller value
            int tmp = *(t->table + (i-1) * t->columns + j) + 1;
            min = (min <= tmp ? min : tmp);

            // Now look above for the same.
            tmp = *(t->table + i * t->columns + (j-1)) + 1;
            min = (min <= tmp ? min : tmp);

            *(t->table + i * t->columns + j) = min; // Put the value
        }
    }
}

table_t calulate_levenshtein_distance(char *s, char *t) {
    str_t ss;
    str_t tt;
    ss.data = s;
    ss.size = strlen(s);
    tt.data = t;
    tt.size = strlen(t);

    // Create the table,
    table_t dp_table = _init_table(ss.size+1, tt.size+1);
    dp_table.s = ss;
    dp_table.t = tt;
    _fill_table(&dp_table);

    dp_table.edit_distance = (dp_table.table + (dp_table.rows - 1) * dp_table.columns + (dp_table.columns - 1)); //Edit distance can be found in the bottom right of the array;
    printf("Distance: %d\n", *dp_table.edit_distance);
    _print_table(&dp_table);
    return dp_table;
}

void print_backtracking(table_t *tb) {
    int *table_index = tb->edit_distance; //tb->table + (tb->rows - 1) * tb->columns + (tb->columns - 1);
    int t_index = tb->t.size - 1;
    int s_index = tb->s.size - 1;
    int _op_cntr = *tb->edit_distance;
    //printf("--- %d ---\n", *(tb->table + 0 * tb->columns));
    while (table_index != tb->table + 0 * tb->columns) { // End if im at the top left index.
        int *p_left = table_index - 1;
        int *p_above = table_index - tb->columns;
        int *p_leftabove = table_index - 1 - tb->columns;
        int *min = _min_backtracking(p_left, p_above, p_leftabove);
        printf("s = %d, t = %d\n", s_index, t_index);
        if (min == p_left) {
            // We found it to the left, meaning we need to insert
            printf("%d: [Insert %c]\n", _op_cntr--, tb->t.data[t_index]);
            t_index--;
        } else if (min == p_above) {
            // We found it above, this means we need to remove a char.
            printf("%d: [Remove %c]\n", _op_cntr--, tb->s.data[s_index]);
            s_index--;

        } else if (min == p_leftabove) {
            if (*table_index != *min) {
                // If the values aren't equal, we need to replace, if they are equal, then we don't have to do anything.
                printf("%d: [Replace %c with %c]\n", _op_cntr--, tb->s.data[s_index], tb->t.data[t_index]);
            }
            // Decrease all indices accordingly
            t_index--;
            s_index--;
        } else {
            exit(-1);
        }
        table_index = min;
    }
}

int* _min_backtracking(int *p_left, int *p_above, int *p_leftabove) {
    int *min = p_leftabove;

    min = (*p_above < *min ? p_above : min);
    min = (*p_left < *min ? p_left : min);
    return min;
}

int main(int argc, char **argv) {
    if (argc < 3){
        printf("Usage: ./levenshtein <string1> <string2>\n");
        return EXIT_FAILURE;
    }

    // Run computations.
    table_t dp_table;
    dp_table = calulate_levenshtein_distance(argv[1], argv[2]);
    print_backtracking(&dp_table);
    free(dp_table.table);
    return EXIT_SUCCESS;
}
