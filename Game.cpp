/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Jamey Carpenter, Divyanga Bajoria
 * jameyc, bajoriad
 *
 * Project 4: Battleship
 *
 * Description:
 * This .cpp file runs the whole program - it generates the grids, gets
 * the players' moves and makes sure they are valid, and
 * announces the entire game winner.
 */

#include <fstream>

#include "Game.h"

// default constructor
Game::Game()
{
    p1 = Player();
    p2 = Player();
}

/* non-default constructor playing game with two user entered players and fills
   their respective grids based on the user entered grid1 and grid2 */
Game::Game(Player player1, string grid1, Player player2, string grid2)
{
    p1 = player1;
    p2 = player2;
    ifstream fin_read;
    fin_read.open("grid1.txt");
    // when grid1 is empty or grid file fails to open
    if ((!fin_read.is_open()) || (grid1.empty()))
    {
        cout << "Generating random grid for " << p1.get_name() << endl;
        generate_random_grid(p1);
    }
    // when grid1 is non-empty
    else
    {
        p1.load_grid_file(grid1);
    }
    fin_read.close();
    fin_read.open("grid2.txt");
    if ((!fin_read.is_open()) || (grid2.empty()))
    {
        cout << "Generating random grid for " << p2.get_name() << endl;
        generate_random_grid(p2);
    }
    else
    {
        p2.load_grid_file(grid2);
    }
    fin_read.close();
}

// getter function for player p1
Player Game::get_p1()
{
    return p1;
}

// getter function for player p2
Player Game::get_p2()
{
    return p2;
}

// getter function for player's move, asks user to enter a move in "1A" or "1a"
string Game::get_move(string player_name)
{
    string user_move = "";
    
    std::cout << player_name << " enter your move: ";
    cin >> user_move;
    cout << endl;
    
    return user_move;
}

// checks if user entered move is valid or not
bool Game::check_valid_move(string move)
{
    int move_row = 0;
    char move_col =  ' ';
    // checks for error 1 - if the size of the move is not equal to 2
    if (move.length() != 2)
    {
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    /* checks for error 2 - if the row or column element of the move is not
       within the valid input range */
    else
    {
        move_row = move.at(0) - '0';
        move_col = toupper(move.at(1));
        if (!(move_row >= 1 && move_row <= MAX_GRID_SIZE) || !(move_col >= 'A'
            && move_col <= 'H'))
        {
            cout << p1.get_name() << " you entered an invalid position" << endl;
            return false;
        }
        else
        {
            return true;
        }
    }
}
 
// playing the game in its entirety
void Game::start(char difficulty, int max_num_rounds)
{
    int round_no = 0;
    int p1_round = 0;
    int p2_round = 0;
    string p1_move = "";
    char move_row = ' ';
    char move_col = ' ';
    
    /* continues to play game until either of the players have destroyed their
       opponent's ships or the user enterd max rounds is not reached */
    while ((!p1.destroyed()) && (!p2.destroyed()) &&
           (round_no < max_num_rounds))
    {
        p1_move = get_move(p1.get_name());
        while (!check_valid_move(p1_move))
        {
            p1_move = get_move(p1.get_name());
        }
        // extracting the row and column element of p1's move
        move_row = p1_move.at(0);
        move_col = p1_move.at(1);
        p1.attack(p2, Position(move_row, move_col));
        p1_round++;
        if (!p2.destroyed())
        {
          // p2's move
          opponent_make_move(difficulty);
          p2_round++;
        }
        cout << "Your grid" << endl;
        p1.print_grid();
        cout << p2.get_name() << "'s grid" << endl;
        p1.print_guess_grid();
        round_no++;
    }
    // printing the final result of the game
    if (p2.destroyed())
    {
        cout << "Game over, winner is " << p1.get_name() << " in " << p1_round
                << " rounds";
    }
    else if (p1.destroyed())
    {
        cout << "Game over, winner is " << p2.get_name() << " in " << p2_round
                << " rounds";
    }
    else if ((!p1.destroyed()) || (!p2.destroyed()))
    {
        cout << "Game over, winner is no one in " << round_no << " rounds";
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

