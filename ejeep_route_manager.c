#include "ejeep_route_manager.h"
#include <stdlib.h>
#include <string.h>

/**
 * @file ejeep_route_manager.c
 * @brief Your implementation file for the e-jeepney route management system.
 */

void move_next(Jeepney *jeep)
{
    if (jeep && jeep->current_stop){
        jeep->current_stop = jeep->current_stop->next;
    }
}

void move_prev(Jeepney *jeep)
{
    if (jeep && jeep->current_stop){
        jeep->current_stop = jeep->current_stop->prev;
    }
}

void board_passengers(Jeepney *jeep, int passengers_to_board)
{
    if (jeep && jeep->current_stop && passengers_to_board > 0){
        int actual_boarding = passengers_to_board;
        if (actual_boarding > jeep->current_stop->passengers_waiting)
        {
            actual_boarding = jeep->current_stop->passengers_waiting;
        }

        jeep->current_stop->passengers_waiting -= actual_boarding;
        jeep->total_passengers += actual_boarding;
    }
}

void add_stop_after(RouteStop *current_stop, const char *new_stop_name)
{
    if (current_stop && new_stop_name){
        RouteStop *new_stop = (RouteStop *)malloc(sizeof(RouteStop));
        if (!new_stop) return;

        strncpy(new_stop->name, new_stop_name, sizeof(new_stop->name) - 1);
        new_stop->name[sizeof(new_stop->name) - 1] = '\0';
        new_stop->passengers_waiting = 0;

        RouteStop *stop_after = current_stop->next;

        current_stop->next = new_stop;
        new_stop->prev = current_stop;
        new_stop->next = stop_after;
        stop_after->prev = new_stop;
    }
}

void remove_current_stop(Jeepney *jeep)
{
    if (jeep && jeep->current_stop){
        RouteStop *stop_to_remove = jeep->current_stop;

        if (stop_to_remove->next == stop_to_remove)
        {
            free(stop_to_remove);
            jeep->current_stop = NULL;
        }
        else
        {
            RouteStop *prev = stop_to_remove->prev;
            RouteStop *next = stop_to_remove->next;

            prev->next = next;
            next->prev = prev;

            jeep->current_stop = next;
            free(stop_to_remove);
        }
    }
}
