#include "attack.h"
#include "bb.h"
#include "defs.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        run_tests();
        exit(EXIT_SUCCESS);
    }

    init_attacks();
    exit(EXIT_SUCCESS);
}