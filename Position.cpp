/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Jamey Carpenter, Divyanga Bajoria
 * jameyc, bajoriad
 *
 * Project 4: Battleship
 *
 * Description:
 * This returns the row and column of a position on the batteship board. It
 * can convert from an int or a char.
 */

#include "Position.h"
#include "utility.h"

// default constructor: set row and col to 0
Position::Position()
{
    row = 0;
    col = 0;
}

// non-default constructor: set row and col to the int passed
Position::Position(int row_in, int col_in)
{
    set_row(row_in);
    set_col(col_in);
}

// non-default constructor: convert chars passed into ints and set row and col
Position::Position(char row_in, char col_in)
{
    row = int(row_in) - '1';
    col = int(col_in);
    col = toupper(char(col));
    col = col - 'A';
    set_row(row);
    set_col(col);
}

// getter function for row
int Position::get_row()
{
    return row;
}

// setter function for row
void Position::set_row(int row_in)
{
    row = check_range(row_in);
    return;
}

// getter function for col
int Position::get_col()
{
    return col;
}

// setter function for col
void Position::set_col(int col_in)
{
    col = check_range(col_in);
    return;
}

void Position::read(istream &is)
{
    // junk_input is for reading parenthesis and commas
    char junk_input;
    // column_input is an alpha char
    char column_input;
    
    // read in if it is in the format '6A'
    is >> row >> column_input;
    
    // if that is not the format, read in the format '(6,A)'
    if (!(is.good()))
    {
        is.clear();
        is >> junk_input >> row >> junk_input >> column_input >> junk_input;
    }
    col = int(column_input);
    col = toupper(char(col));
    // convert to corresponding col # (i.e. 'A' = '1')
    col = col - '@';
    row = check_range(row - 1);
    col = check_range(col - 1);
            
    return;
}

// writing the position in the form of (row,col)
void Position::write(ostream &os)
{
    os << "(" << row + 1 << ",";
    os << char(col + 'A') << ")";
    return;
}

int Position::check_range(int val)
{
    // if the val is in the correct range, return val
    if (val >= 0 && val < MAX_GRID_SIZE)
    {
            return val;
    }
    // return closest in-range val if not
    else
    {
        if (val < 0)
        {
            val = 0;
        }
        else if (val >= MAX_GRID_SIZE)
        {
            val = MAX_GRID_SIZE - 1;
        }
    }
    return val;
}


// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

