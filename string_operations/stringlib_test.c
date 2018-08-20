#include "string_operations.h"
#include <stdio.h>

int main(int argc, char** argv) {
    printf("%s - length %d\n",argv[1],str_len(argv[1]));
    printf("compare %d\n",str_cmp(argv[1], argv[2]));
    printf("compare %d\n",str_cmp(argv[2], argv[1]));
    printf("spn: %d\n",str_spn(argv[1], argv[2]));
}
