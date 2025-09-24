#include "test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int assert_equals(int expected, int actual, const char *test_name)
{
    if (expected != actual)
    {
        printf("FAILED: %s. Expected %d, got %d\n", test_name, expected, actual);
        return 0;
    }
    printf("PASSED: %s\n", test_name);
    return 1;
}

int assert_string_equals(const char *expected, const char *actual, const char *test_name)
{
    if (strcmp(expected, actual) != 0)
    {
        printf("FAILED: %s. Expected \"%s\", got \"%s\"\n", test_name, expected, actual);
        return 0;
    }
    printf("PASSED: %s\n", test_name);
    return 1;
}

int assert_pointers_equal(const void *expected, const void *actual, const char *test_name)
{
    if (expected != actual)
    {
        printf("FAILED: %s. Pointers do not match.\n", test_name);
        return 0;
    }
    printf("PASSED: %s\n", test_name);
    return 1;
}

int assert_is_null(const void *ptr, const char *test_name)
{
    if (ptr != NULL)
    {
        printf("FAILED: %s. Pointer was not NULL.\n", test_name);
        return 0;
    }
    printf("PASSED: %s\n", test_name);
    return 1;
}

Jeepney *setup_test_environment(const char *stops[], int num_stops)
{
    RouteStop *route = create_route(stops, num_stops);
    if (!route)
    {
        return NULL;
    }

    Jeepney *jeep = create_jeepney();
    if (!jeep)
    {
        destroy_route(route);
        return NULL;
    }

    jeep->current_stop = route;
    return jeep;
}

void teardown_test_environment(Jeepney *jeep)
{
    if (!jeep)
    {
        return;
    }

    if (jeep->current_stop)
    {
        destroy_route(jeep->current_stop);
    }

    free(jeep);
}