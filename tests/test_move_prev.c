#include "../ejeep_route_manager.h"
#include "./test_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int test_standard_move()
{
    const char *stops[] = {"Lignon Hill", "Daraga Church", "Cagsawa Ruins"};
    Jeepney *jeep = setup_test_environment(stops, 3); // Starts at Lignon Hill

    move_prev(jeep); // Should move to Cagsawa Ruins

    int pass = assert_string_equals("Cagsawa Ruins", jeep->current_stop->name, "Standard Move Test");

    teardown_test_environment(jeep);
    return pass;
}

int test_circular_traversal()
{
    const char *stops[] = {"Embarcadero", "SM City Legazpi", "Ayala Malls"};
    Jeepney *jeep = setup_test_environment(stops, 3);

    move_prev(jeep); // Now at Ayala Malls
    move_prev(jeep); // Now at SM City Legazpi
    move_prev(jeep); // Should be back at Embarcadero

    int pass = assert_string_equals("Embarcadero", jeep->current_stop->name, "Circular Traversal Test");

    teardown_test_environment(jeep);
    return pass;
}

int test_empty_route()
{
    Jeepney *jeep = create_jeepney(); // current_stop is NULL

    move_prev(jeep); // Should not crash or change state

    int pass = assert_is_null(jeep->current_stop, "Empty Route Test");

    free(jeep);
    return pass;
}

int main()
{
    printf("--- Running Move Prev Tests ---\n");
    int passed = 1;
    passed &= test_standard_move();
    passed &= test_circular_traversal();
    passed &= test_empty_route();
    printf("--- Move Prev Tests Complete ---\n");

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