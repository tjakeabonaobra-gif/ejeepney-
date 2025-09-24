#include "../ejeep_route_manager.h"
#include "./test_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int test_standard_removal()
{
    const char *stops[] = {"Lignon Hill", "Daraga Church", "Cagsawa Ruins"};
    Jeepney *jeep = setup_test_environment(stops, 3);
    jeep->current_stop = jeep->current_stop->next; // Start at Daraga Church

    RouteStop *lignon = jeep->current_stop->prev;
    RouteStop *cagsawa = jeep->current_stop->next;

    remove_current_stop(jeep); // Remove Daraga Church

    int pass1 =
        assert_string_equals("Cagsawa Ruins", jeep->current_stop->name, "Standard Removal Test (Jeep Position)");
    int pass2 = assert_pointers_equal(cagsawa, lignon->next, "Standard Removal Test (Lignon->next)");
    int pass3 = assert_pointers_equal(lignon, cagsawa->prev, "Standard Removal Test (Cagsawa->prev)");

    teardown_test_environment(jeep);
    return pass1 && pass2 && pass3;
}

int test_last_stop_removal()
{
    const char *stops[] = {"Embarcadero"};
    Jeepney *jeep = setup_test_environment(stops, 1);

    remove_current_stop(jeep); // Remove the only stop

    int pass = assert_is_null(jeep->current_stop, "Last Stop Removal Test");

    teardown_test_environment(jeep);
    return pass;
}

int main()
{
    printf("--- Running Remove Current Stop Tests ---\n");
    int passed = 1;
    passed &= test_standard_removal();
    passed &= test_last_stop_removal();
    printf("--- Remove Current Stop Tests Complete ---\n");

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