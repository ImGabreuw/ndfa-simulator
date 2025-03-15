#pragma once

#include <stdio.h>

extern const int MAX_LINE_SIZE;

void read_line(FILE *file, int line_index, char line[MAX_LINE_SIZE]);