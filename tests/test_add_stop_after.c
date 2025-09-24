#include "../ejeep_route_manager.h"
#include "./test_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int test_standard_insertion()
{
    const char *stops[] = {"Lignon Hill", "Cagsawa Ruins"};
    Jeepney *jeep = setup_test_environment(stops, 2);
    RouteStop *lignon = jeep->current_stop;
    RouteStop *cagsawa = jeep->current_stop->next;

    add_stop_after(lignon, "Daraga Church");

    RouteStop *daraga = lignon->next;

    int pass1 = assert_string_equals("Daraga Church", daraga->name, "Standard Insertion Test (Name)");
    int pass2 = assert_pointers_equal(daraga, lignon->next, "Standard Insertion Test (Lignon->next)");
    int pass3 = assert_pointers_equal(lignon, daraga->prev, "Standard Insertion Test (Daraga->prev)");
    int pass4 = assert_pointers_equal(cagsawa, daraga->next, "Standard Insertion Test (Daraga->next)");
    int pass5 = assert_pointers_equal(daraga, cagsawa->prev, "Standard Insertion Test (Cagsawa->prev)");

    teardown_test_environment(jeep);
    return pass1 && pass2 && pass3 && pass4 && pass5;
}

int test_single_node_insertion()
{
    const char *stops[] = {"Embarcadero"};
    Jeepney *jeep = setup_test_environment(stops, 1);
    RouteStop *embarcadero = jeep->current_stop;

    add_stop_after(embarcadero, "SM City Legazpi");

    RouteStop *sm_city = embarcadero->next;

    int pass1 = assert_string_equals("SM City Legazpi", sm_city->name, "Single-Node Insertion Test (Name)");
    int pass2 = assert_pointers_equal(sm_city, embarcadero->next, "Single-Node Insertion Test (Embarcadero->next)");
    int pass3 = assert_pointers_equal(embarcadero, sm_city->prev, "Single-Node Insertion Test (SM->prev)");
    int pass4 = assert_pointers_equal(embarcadero, sm_city->next, "Single-Node Insertion Test (SM->next)");
    int pass5 = assert_pointers_equal(sm_city, embarcadero->prev, "Single-Node Insertion Test (Embarcadero->prev)");

    teardown_test_environment(jeep);
    return pass1 && pass2 && pass3 && pass4 && pass5;
}

int main()
{
    printf("--- Running Add Stop After Tests ---\n");
    int passed = 1;
    passed &= test_standard_insertion();
    passed &= test_single_node_insertion();
    printf("--- Add Stop After Tests Complete ---\n");

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