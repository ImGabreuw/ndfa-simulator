#include "test.h"

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"

int test_read_first_line_to_get_automaton_alphabet_symbols(void)
{
    const char input_file[] = "in-test.txt";

    FILE *file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return EXIT_FAILURE;
    }

    char alphabet_symbols[MAX_LINE_SIZE];
    read_line(file, 1, alphabet_symbols);

    int failures = 0;
    failures += assertStringEquals("ab", alphabet_symbols, NULL);
    return failures;
}

int main(void)
{
    run_test(
        "Should read first line to get the automaton alphabet symbols",
        &test_read_first_line_to_get_automaton_alphabet_symbols);

    return EXIT_SUCCESS;
}
