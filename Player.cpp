/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Jamey Carpenter, Divyanga Bajoria
 * jameyc, bajoriad
 *
 * Project 4: Battleship
 *
 * Description:
 * This cpp file has the player information, such as name, number of ships,
 * their grid, and it attacks the other ship based on the player's move. When
 * a ship is sunk, it announces the sunk ship.
 */

#include <fstream>

#include "Player.h"

// default constructor
Player::Player()
{
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

// non-default constructor setting player name to user entered name
Player::Player(string name_val)
{
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

// filling all positions of grid and guess grid with the EMPTY_LETTER character
void Player::init_grid()
{
    for (int i = 0; i < MAX_GRID_SIZE; i++)
    {
        for (int j = 0; j < MAX_GRID_SIZE; j++)
        {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
}

// getter function for player's name
string Player::get_name()
{
    return name;
}

// getter fucntion for number of ships of the player
int Player::get_num_ships()
{
    return num_ships;
}

// getter function for remaining number of ships of the player
int Player::get_remaining_ships()
{
    return remaining_ships;
}

// getter function for grid, return element at user entered position
char Player::get_grid_at(int row, int col)
{
    char grid_element;
    grid_element = grid[row][col];
    return grid_element;
}

// getter function for guess grid, return element at user entered position
char Player::get_guess_grid_at(int row, int col)
{
    char guess_element;
    guess_element = guess_grid[row][col];
    return guess_element;
}

// adds ships to the player's grid
void Player::add_ship(Ship ship)
{
    // if player's grid has MAX_NUM_SHIPS it does not add any more ships
    if (num_ships == MAX_NUM_SHIPS)
    {
        return;
    }
    if (ship.is_horizontal())
    {
        // when column element of start position is less than end position
        if (ship.get_start().get_col() <= ship.get_end().get_col())
        {
            // adding ship to the player's grid
            for (int i = ship.get_start().get_col();
                i <= ship.get_end().get_col(); i++)
            {
                grid[ship.get_start().get_row()][i] = SHIP_LETTER;
            }
        }
        // when column element of start position is bigger than end position
        else if (ship.get_start().get_col() >= ship.get_end().get_col())
        {
            for (int i = ship.get_end().get_col();
                i <= ship.get_start().get_col(); i++)
            {
                grid[ship.get_start().get_row()][i] = SHIP_LETTER;
            }
        }
    }
    // checking when ship is vertical
    else
    {
        // when row element of start position is less than end position
        if (ship.get_start().get_row() <= ship.get_end().get_row())
        {
            for (int i = ship.get_start().get_row();
                i <= ship.get_end().get_row(); i++)
            {
                grid[i][ship.get_start().get_col()] = SHIP_LETTER;
            }
        }
        // when row element of start position is bigger than end position
        else if (ship.get_start().get_row() >= ship.get_end().get_row())
        {
            for (int i = ship.get_end().get_row();
                i <= ship.get_start().get_row(); i++)
            {
                grid[i][ship.get_start().get_col()] = SHIP_LETTER;
            }
        }
    }
    // adding ship the player's array of ships at the valid index
    ships[num_ships] = ship;
    num_ships++;
    remaining_ships++;
}

void Player::attack(Player &opponent, Position pos)
{
    int ship_pos = 0;
    // checking which player's ship falls on the user entered position
    for (int i = 0; i < opponent.num_ships; i++)
    {
        if (opponent.ships[i].has_position(pos))
        {
            // stores the index of the valid ship in the player's ships array
            ship_pos = i;
        }
    }
    // when entered position is on the valid ship and not been hit previously
    if ((opponent.ships[ship_pos].has_position(pos)) &&
        (opponent.grid[pos.get_row()][pos.get_col()] == SHIP_LETTER))
    {
        opponent.ships[ship_pos].hit();
        opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        cout << name << " " <<  pos << " " << "hit" << endl;
        // when hitting the ship causes the player' ship to sink
        if (opponent.ships[ship_pos].has_sunk())
        {
            opponent.remaining_ships--;
            announce_ship_sunk(opponent.ships[ship_pos].get_size());
            cout << endl;
        }
    }
    // when entered is not on the valid ship or has been hit previously
    else
    {
        opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        cout << name << " " <<  pos << " " << "miss" << endl;
    }
}

// printing type of opponent's ship sunk by player based on size of ship
void Player::announce_ship_sunk(int size)
{
    if (size == 2)
    {
        cout << "Congratulations " << name << "! You sunk a destroyer";
    }
    else if (size == 3)
    {
        cout << "Congratulations " << name << "! You sunk a Submarine";
    }
    else if (size == 4)
    {
        cout << "Congratulations " << name << "! You sunk a Battleship";
    }
    else if (size == 5)
    {
        cout << "Congratulations " << name << "! You sunk a Carrier";
    }
}

// reading start and end positions of ships from a file
bool Player::load_grid_file(string filename)
{
    ifstream fin_read;
    Position start_pos;
    Position end_pos;
    Ship valid_ship;
    fin_read.open(filename);
    // checking is the file opened or not
    if (fin_read.is_open())
    {
        /* continue to read start and end positions of ships until all on the
           file are read */
        while (fin_read >> start_pos >> end_pos)
        {
            valid_ship = Ship(start_pos, end_pos);
            add_ship(valid_ship);
            Position();
            Position();
          }
        return true;
    }
    else
    {
        return false;
    }
}

// returns true when player's ship has got destroyed, otherwise false
bool Player::destroyed()
{
    if (remaining_ships == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
