#include "ejeep_route_manager.h"
#include <stdlib.h>
#include <string.h>

/**
 * @file helpers.c
 * @brief Implements the helper functions for the e-jeepney route management system.
 */

Jeepney *create_jeepney()
{
    Jeepney *new_jeep = (Jeepney *)malloc(sizeof(Jeepney));
    if (!new_jeep){
        return NULL;
    }

    new_jeep->total_passengers = 0;
    new_jeep->current_stop = NULL;

    return new_jeep;
}

RouteStop *create_route(const char *stops[], int num_stops)
{
    if (num_stops <= 0 || !stops){
        return NULL;
    }

    RouteStop *head = (RouteStop *)malloc(sizeof(RouteStop));
    if (!head){
        return NULL;
    }

    strcpy(head->name, stops[0]);
    head->passengers_waiting = 0;

    RouteStop *current = head;

    for (int i = 1; i < num_stops; ++i){
        RouteStop *new_stop = (RouteStop *)malloc(sizeof(RouteStop));
        if (!new_stop)
        {
            destroy_route(head);
            return NULL;
        }

        strcpy(new_stop->name, stops[i]);
        new_stop->passengers_waiting = 0;

        current->next = new_stop;
        new_stop->prev = current;

        current = new_stop;
    }

    current->next = head;
    head->prev = current;

    return head;
}

void destroy_route(RouteStop *stop)
{
    if (!stop){
        return;
    }

    stop->prev->next = NULL;

    RouteStop *current = stop;
    RouteStop *next_node;

    while (current != NULL){
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
