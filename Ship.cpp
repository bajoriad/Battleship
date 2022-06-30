/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Jamey Carpenter, Divyanga Bajoria
 * jameyc, bajoriad
 *
 * Project 4: Battleship
 *
 * Description:
 * This determines the size, positions of the start and end of the ship,
 * and whether or not a ship has sunk due to the number of hits.
 */

#include <cmath>

#include "Ship.h"

// default constructor sets start, end, size, and num_hits to 0
Ship::Ship()
{
    Position();
    size = 0;
    num_hits = 0;
}

// non-default constructor
Ship::Ship(Position start_in, Position end_in)
{
    start = start_in;
    end = end_in;
    num_hits = 0;
    if (is_horizontal())
    {
        size = abs(start.get_col() - end.get_col()) + 1;
    }
    else
    {
        size = abs(start.get_row() - end.get_row()) + 1;
    }
}

// getter function for start position
Position Ship::get_start()
{
    return start;
}

// getter function for end position
Position Ship::get_end()
{
    return end;
}

// getter function for size
int Ship::get_size()
{
    return size;
}

// returns true if the ship is horizontal, false if vertical
bool Ship::is_horizontal()
{
    if (start.get_row() == end.get_row())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Ship::has_position(Position pos)
{
    if (is_horizontal())
    {
        // if the position is in the same row, continue checking
        if (pos.get_row() == start.get_row())
        {
            // if the position is between the start and end, return true
            if ((start.get_col() <= end.get_col()) && pos.get_col() >=
            start.get_col() && pos.get_col() <= end.get_col())
            {
                return true;
            }
            // if end is less than the start, it can also return true
            else if ((start.get_col() >= end.get_col()) && pos.get_col()
                    <= start.get_col() && pos.get_col() >= end.get_col())
            {
                return true;
            }
            // same row, not in col range = false
            else
            {
               return false;
            }
        }
        // not the same row = false
        else
        {
            return false;
        }
    }
    // if the ship is vertical, still check
    else if (pos.get_col() == start.get_col())
    {
        // start < end: check to see if position is in range
        if ((start.get_row() <= end.get_row()) && pos.get_row() >=
            start.get_row() && pos.get_row() <= end.get_row())
            {
                return true;
            }
            // start > end: still check to see if position is in range
            else if ((start.get_row() >= end.get_row()) && pos.get_row() <=
                     start.get_row() && pos.get_row() >= end.get_row())
            {
                return true;
            }
            else
            {
                return false;
            }
    }
    else
    {
        return false;
    }
}

// increment num_hits
void Ship::hit()
{
    if (num_hits < size)
    {
        num_hits++;
    }
    return;
}

bool Ship::has_sunk()
{
    // ship has sunk when num_hits hits size
    if (num_hits == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
