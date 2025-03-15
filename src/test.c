#include "test.h"

#include <string.h>

const char COLOR_GREEN[] = "\033[0;32m";
const char COLOR_RED[] = "\033[0;31m";
const char COLOR_RESET[] = "\033[0m";

const int TEST_SUCCESS = 0;
const int TEST_FAILURE = 1;

void test_passed(const char *test_name)
{
    printf("%s%s [PASSED]%s\n", COLOR_GREEN, test_name, COLOR_RESET);
}

void test_failed(const char *test_name)
{
    printf("%s%s [FAILED]%s\n", COLOR_RED, test_name, COLOR_RESET);
}

const char *default_message(const char *message, const char *default_msg)
{
    return (message == NULL || message[0] == '\0') ? default_msg : message;
}

int assertEquals(int expected, int actual, const char *message)
{
    message = default_message(message, "assertEquals failed");
    if (expected != actual)
    {
        test_failed(message);
        printf("  Expected: %d, Got: %d\n", expected, actual);
        return TEST_FAILURE;
    }
    test_passed(message);
    return TEST_SUCCESS;
}

int assertNotEquals(int expected, int actual, const char *message)
{
    message = default_message(message, "assertNotEquals failed");
    if (expected == actual)
    {
        test_failed(message);
        printf("  Values should be different but got: %d\n", expected);
        return TEST_FAILURE;
    }
    test_passed(message);
    return TEST_SUCCESS;
}

int assertStringEquals(const char *expected, const char *actual, const char *message)
{
    message = default_message(message, "assertStringEquals failed");
    if (strcmp(expected, actual) != 0)
    {
        test_failed(message);
        printf("  Expected: \"%s\", Got: \"%s\"\n", expected, actual);
        return TEST_FAILURE;
    }
    test_passed(message);
    return TEST_SUCCESS;
}

int assertNotNull(void *ptr, const char *message)
{
    message = default_message(message, "assertNotNull failed");
    if (ptr == NULL)
    {
        test_failed(message);
        printf("  Expected non-null pointer\n");
        return TEST_FAILURE;
    }
    test_passed(message);
    return TEST_SUCCESS;
}

int assertNull(void *ptr, const char *message)
{
    message = default_message(message, "assertNull failed");
    if (ptr != NULL)
    {
        test_failed(message);
        printf("  Expected NULL pointer\n");
        return TEST_FAILURE;
    }
    test_passed(message);
    return TEST_SUCCESS;
}

void run_test(const char *test_name, int (*test_func)(void))
{
    printf("\nRunning test: %s\n", test_name);
    int failures = test_func();

    if (failures == 0)
    {
        test_passed(test_name);
    }
    else
    {
        test_failed(test_name);
        printf("  %d assertion(s) failed\n", failures);
    }
}
