#include "reader.h"

#include <string.h>

const int MAX_LINE_SIZE = 100;

void read_line(FILE *file, int line_index, char line[MAX_LINE_SIZE])
{
    if (file == NULL)
    {
        printf("Erro ao ler o arquivo.\n");
        return;
    }

    char buffer[MAX_LINE_SIZE];
    int current_line = 1;

    while (fgets(buffer, MAX_LINE_SIZE, file))
    {
        if (current_line == line_index)
        {
            if (strlen(buffer) <= 0)
                break;

            buffer[strlen(buffer) - 1] = 0;
            strcpy(line, buffer);
            break;
        }
        current_line++;
    }

    if (current_line < line_index)
    {
        printf("O arquivo tem menos de %d linhas.\n", line_index);
    }
}