#include "ejeep_route_manager.h"
#include <stdio.h>

int main() {
    // Define stop names for the route
    const char *stop_names[] = {"City Hall", "Market", "University"};
    int num_stops = 3;

    // Create a new jeepney
    Jeepney *jeep = create_jeepney();
    if (!jeep) {
        printf("Failed to create jeepney.\n");
        return 1;
    }

    // Build the route and assign it to the jeepney
    jeep->current_stop = create_route(stop_names, num_stops);
    if (!jeep->current_stop) {
        printf("Failed to create route.\n");
        free(jeep);
        return 1;
    }

    // Simulate boarding passengers
    jeep->current_stop->passengers_waiting = 10;
    board_passengers(jeep, 5);
    printf("Boarded passengers. Total now: %d\n", jeep->total_passengers);

    // Move to the next stop
    move_next(jeep);
    printf("Moved to next stop: %s\n", jeep->current_stop->name);

    // Add a new stop after the current one
    add_stop_after(jeep->current_stop, "Mall");
    printf("Added new stop after current: Mall\n");

    // Remove the current stop
    remove_current_stop(jeep);
    if (jeep->current_stop) {
        printf("Removed current stop. Now at: %s\n", jeep->current_stop->name);
    } else {
        printf("Route is now empty.\n");
    }

    // Clean up memory
    destroy_route(jeep->current_stop);
    free(jeep);

    return 0;
}
