#pragma once

#include <stdio.h>

extern const char COLOR_GREEN[];
extern const char COLOR_RED[];
extern const char COLOR_RESET[];

extern const int TEST_SUCCESS;
extern const int TEST_FAILURE;

void test_passed(const char *test_name);
void test_failed(const char *test_name);

int assertEquals(int expected, int actual, const char *message);
int assertNotEquals(int expected, int actual, const char *message);
int assertStringEquals(const char *expected, const char *actual, const char *message);
int assertNotNull(void *ptr, const char *message);
int assertNull(void *ptr, const char *message);

void run_test(const char *test_name, int (*test_func)(void));
