#include "../ejeep_route_manager.h"
#include "./test_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int test_standard_boarding()
{
    const char *stops[] = {"Pacific Mall"};
    Jeepney *jeep = setup_test_environment(stops, 1);
    jeep->current_stop->passengers_waiting = 10;

    board_passengers(jeep, 5);

    int pass1 = assert_equals(5, jeep->total_passengers, "Standard Boarding Test (Jeep Count)");
    int pass2 = assert_equals(5, jeep->current_stop->passengers_waiting, "Standard Boarding Test (Stop Count)");

    teardown_test_environment(jeep);
    return pass1 && pass2;
}

int test_over_boarding()
{
    const char *stops[] = {"Gaisano Mall"};
    Jeepney *jeep = setup_test_environment(stops, 1);
    jeep->current_stop->passengers_waiting = 5;

    board_passengers(jeep, 10);

    int pass1 = assert_equals(5, jeep->total_passengers, "Over-Boarding Test (Jeep Count)");
    int pass2 = assert_equals(0, jeep->current_stop->passengers_waiting, "Over-Boarding Test (Stop Count)");

    teardown_test_environment(jeep);
    return pass1 && pass2;
}

int test_zero_boarding()
{
    const char *stops[] = {"Old Albay Park"};
    Jeepney *jeep = setup_test_environment(stops, 1);
    jeep->current_stop->passengers_waiting = 10;

    board_passengers(jeep, 0);

    int pass1 = assert_equals(0, jeep->total_passengers, "Zero Boarding Test (Jeep Count)");
    int pass2 = assert_equals(10, jeep->current_stop->passengers_waiting, "Zero Boarding Test (Stop Count)");

    teardown_test_environment(jeep);
    return pass1 && pass2;
}

int main()
{
    printf("--- Running Board Passengers Tests ---\n");
    int passed = 1;
    passed &= test_standard_boarding();
    passed &= test_over_boarding();
    passed &= test_zero_boarding();
    printf("--- Board Passengers Tests Complete ---\n");

    if (passed)
    {
        printf("ALL TESTS PASSED\n");
    }
    else
    {
        printf("SOME TESTS FAILED\n");
    }

    return passed ? 0 : 1;
}