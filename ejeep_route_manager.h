#ifndef EJEEP_ROUTE_MANAGER_H
#define EJEEP_ROUTE_MANAGER_H

/**
 * @file ejeep_route_manager.h
 * @brief A module for managing a Legazpi City e-jeepney route.
 *
 * This module uses a circular doubly linked list to simulate the route of an
 * e-jeepney. It provides functions for navigation, passenger management,
 * and dynamic route modifications like adding or removing stops.
 */

/**
 * @brief Represents a single stop on the e-jeepney route.
 *
 * Each stop is a node in a circular doubly linked list, containing its name,
 * the number of passengers currently waiting, and pointers to the next and
 * previous stops in the loop.
 */
typedef struct RouteStop
{
    char name[50];
    int passengers_waiting;
    struct RouteStop *next;
    struct RouteStop *prev;
} RouteStop;

/**
 * @brief Represents the state of a single e-jeepney.
 *
 * This structure tracks the total number of passengers currently on board and
 * maintains a pointer to the jeepney's current location (stop) within the route.
 */
typedef struct Jeepney
{
    int total_passengers;
    RouteStop *current_stop;
} Jeepney;

/* --- Pre-defined Helper Functions --- */

/**
 * @brief Creates and initializes a new Jeepney object.
 *
 * @return A pointer to the newly allocated Jeepney struct.
 */
Jeepney *create_jeepney();

/**
 * @brief Constructs a complete circular route from an array of stop names.
 *
 * @param stops An array of strings, where each string is the name of a stop.
 * @param num_stops The number of stops in the array.
 * @return A pointer to the first stop in the newly created circular route.
 */
RouteStop *create_route(const char *stops[], int num_stops);

/**
 * @brief Deallocates all memory for the route to prevent leaks.
 *
 * @param stop A pointer to any stop within the route to begin deallocation.
 */
void destroy_route(RouteStop *stop);

/* --- Functions You Will Implement --- */

/**
 * @brief Moves the jeepney to the next stop in its circular route.
 *
 * @param jeep A pointer to the Jeepney object to be moved.
 */
void move_next(Jeepney *jeep);

/**
 * @brief Moves the jeepney to the previous stop in its circular route.
 *
 * @param jeep A pointer to the Jeepney object to be moved.
 */
void move_prev(Jeepney *jeep);

/**
 * @brief Simulates passengers boarding the jeepney at its current stop.
 *
 * This function updates the passenger counts on both the jeepney and the stop.
 * The number of passengers waiting at the stop decreases, and the total
 * passengers on the jeepney increases.
 *
 * @param jeep A pointer to the Jeepney whose passenger count will be updated.
 * @param passengers_to_board The number of passengers attempting to board.
 */
void board_passengers(Jeepney *jeep, int passengers_to_board);

/**
 * @brief Inserts a new stop into the route immediately after a specified stop.
 *
 * @param current_stop A pointer to the stop after which the new stop will be added.
 * @param new_stop_name The name for the new RouteStop to be created.
 */
void add_stop_after(RouteStop *current_stop, const char *new_stop_name);

/**
 * @brief Removes the jeepney's current stop from the route.
 *
 * After removal, the jeepney's current stop is updated to be the stop that
 * was previously next in the route. The memory for the removed stop is freed.
 *
 * @param jeep A pointer to the Jeepney whose current stop will be removed.
 */
void remove_current_stop(Jeepney *jeep);

#endif // EJEEP_ROUTE_MANAGER_H