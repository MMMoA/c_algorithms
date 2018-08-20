#include "string_operations.h"
#define dp(X,Y) *(_dp_table + (((X)) * (l_str2+1) + ((Y))))

/**
 * Compares two strings, returns -1 if the first one is smaller, 0 if they are equal and 1 if the
 * second string is smaller.
 */
int str_cmp(char* str1, char* str2) {
    int _str1_length = str_len(str1);
    int _str2_length = str_len(str2);
    int l = _str1_length <= _str2_length ? _str1_length : _str2_length;
    for (int i = 0; i < l; i++) {
        if(*(str1 + i) < *(str2 + i)) {
            return -1;
        } else if (*(str1 + i) > *(str2 + i)) {
            return 1;
        }
    }
    if (_str1_length < _str2_length) {
        return -1;
    } else if (_str1_length == _str2_length) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Implementation of longest common string using dynamic programming.
 * See Informatik 2 2018-vl12-kap6-2
 */
int str_spn(char* str1, char* str2) {
    int l_str1 = str_len(str1);
    int l_str2 = str_len(str2);
    int* _dp_table = (int*) malloc((l_str1 + 1) * (l_str2 + 1) * sizeof(int));
    int lc_seq = 0;

    // Initialize table - first row and first column are zero.
    for (int i = 0; i <= l_str1; i++) {
        dp(i,0) = 0;
    }
    for (int j = 0; j <= l_str2; j++) {
        dp(0,j) = 0;
    }

    for (int i = 1; i <= l_str1; i++) { // Prefixes of str1.
        for (int j = 1; j <= l_str2; j++) { // Prefixes of str2.

            // Apply recursive definition of longest commen string.
            if ( *(str1 + i - 1) != *(str2 + j - 1) ) {
                dp(i,j) = dp(i,j-1) > dp(i-1,j) ? dp(i,j-1) : dp(i-1,j);
            } else {
                dp(i,j) = dp(i-1,j-1) + 1;
            }

            // Get the largest value
            lc_seq = (lc_seq < dp(i,j) ? dp(i,j) : lc_seq);
        }
    }
    /*    for (int i = 0; i <= l_str1; i++) {
        printf("|");
        for (int j = 0; j <= l_str2; j++) {
            printf(" %-3d",dp(i,j));
        }
        printf("|\n");
    }*/

    free(_dp_table);
    return lc_seq;
}

/**
 * Returns the length of a string.
 */
int str_len(char* str1) {
    int i = 0;
    while (str1[i] != '\0') {
        i++;
    }
    return i;
}

int firstIndexOf(char* str1, char c) {
    int index = 0;
    int l = str_len(str1);
    while (index < l) {
        if (*(str1 + index) == c) {
            return index;
        }
        index++;
    }
    return -1;
}

int lastIndexOf(char* str1, char c) {
    int f_index = -1;
    for (int i = 0; i < str_len(str1); i++) {
        if (*(str1 + i) == c) {
            f_index = i;
        }
    }
    return f_index;
}
