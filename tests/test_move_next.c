#include "../ejeep_route_manager.h"
#include "./test_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int test_standard_move()
{
    const char *stops[] = {"Lignon Hill", "Daraga Church", "Cagsawa Ruins"};
    Jeepney *jeep = setup_test_environment(stops, 3);

    move_next(jeep);

    int pass = assert_string_equals("Daraga Church", jeep->current_stop->name, "Standard Move Test");

    teardown_test_environment(jeep);
    return pass;
}

int test_circular_traversal()
{
    const char *stops[] = {"Embarcadero", "SM City Legazpi", "Ayala Malls"};
    Jeepney *jeep = setup_test_environment(stops, 3);

    move_next(jeep); // Now at SM City
    move_next(jeep); // Now at Ayala Malls
    move_next(jeep); // Should be back at Embarcadero

    int pass = assert_string_equals("Embarcadero", jeep->current_stop->name, "Circular Traversal Test");

    teardown_test_environment(jeep);
    return pass;
}

int test_empty_route()
{
    Jeepney *jeep = create_jeepney(); // current_stop is NULL by default

    move_next(jeep); // Should not crash

    int pass = assert_is_null(jeep->current_stop, "Empty Route Test");

    free(jeep);
    return pass;
}

int main()
{
    printf("--- Running Move Next Tests ---\n");
    int passed = 1;
    passed &= test_standard_move();
    passed &= test_circular_traversal();
    passed &= test_empty_route();
    printf("--- Move Next Tests Complete ---\n");

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