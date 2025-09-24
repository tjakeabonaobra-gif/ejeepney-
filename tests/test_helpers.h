#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "../ejeep_route_manager.h"

int assert_equals(int expected, int actual, const char *test_name);
int assert_string_equals(const char *expected, const char *actual, const char *test_name);
int assert_pointers_equal(const void *expected, const void *actual, const char *test_name);
int assert_is_null(const void *ptr, const char *test_name);

Jeepney *setup_test_environment(const char *stops[], int num_stops);
void teardown_test_environment(Jeepney *jeep);

#endif // TEST_HELPERS_H