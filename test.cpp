/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    return;
}

void test_position()
{
    // test of default constructor
    Position p1;
    cout << "Row:" << p1.get_row() << "  Col:" << p1.get_col() << endl;
    // test of the other constructor
    Position p2(3, 9);
    cout << "Row:" << p2.get_row() << "  Col:" << p2.get_col() << endl;
    Position pos1(1, 3);
    cout << "Row:" << pos1.get_row() << "  Col:" << pos1.get_col() << endl;
    pos1.set_row(0);
    pos1.set_col(10);
    cout << "Row:" << pos1.get_row() << "  Col:" << pos1.get_col() << endl;
    pos1.set_row(-3);
    pos1.set_col(6);
    cout << "Row:" << pos1.get_row() << "  Col:" << pos1.get_col() << endl;
        
    // test of other non-default constructor
    Position pos2('1', 'c');
    cout << "Row:" << pos2.get_row() << "  Col:" << pos2.get_col() << endl;
    Position pos3('8', 'A');
    cout << "Row:" << pos3.get_row() << "  Col:" << pos3.get_col() << endl;
    Position pos4('5', 'H');
    cout << "Row:" << pos4.get_row() << "  Col:" << pos4.get_col() << endl;
        
        
    // test of member function: set_row(int row_in)
    p1.set_row(5);
    // test of member function: set_col(int col_in)
    p1.set_col(3);
        
    // test of member fucntions get_row() and get_col()
    cout << "(" << p1.get_row() << ", " << p1.get_col() << ")" << endl;
        
    p1.set_row(2);
    p1.set_col(1);
    cout << "(" << p1.get_row() << ", " << p1.get_col() << ")" << endl;
        
    // you can also do cin >> p1;
    cout << "P1 Coordinate: ";
    p1.read(cin);
    cout << p1 << endl;
        
    ifstream fin;
    fin.open("grid2.txt");
    p1.read(fin);
    cout << "Expected: (3,F), Actual: " << p1 << endl;
    p1.read(fin);
    p1.read(fin);
    cout << "Expected: (1,A), Actual: " << p1 << endl;
    fin.close();
        
    fin.open("grid1.txt");
    p1.read(fin);
    cout << "Expected: (8,B), Actual: " << p1 << endl;
    p1.read(fin);
    p1.read(fin);
    cout << "Expected: (6,H), Actual: " << p1 << endl;
    fin.close();
    return;
}

void test_ship()
{
    cout << "Now testing ship.cpp: " << endl;
    // test of default constructor
    Ship s1;
    cout << "Start:" << s1.get_start() << "  End:" << s1.get_end()
         << "  Size:" << s1.get_size() << endl;
        
    // test non-default constructor
    Position start_ship(1, 3);
    Position end_ship(1, 6);
    Ship s2(start_ship, end_ship);
        
    // test is_horizontal()
    cout << endl << "Testing is_horizontal()" << endl;
    cout << "Expected: 1, Actual: " << s2.is_horizontal() << endl;
        
    // test get_size()
    cout << endl << "Testing get_size()" << endl;
    cout << "Expected: 4, Actual: " << s2.get_size() << endl;
        
    cout << "Start:" << s2.get_start() << "  End:" << s2.get_end() << "  Size:"
         << s2.get_size() << endl;
        
    Position start_ship2(1, 4);
    Position end_ship2(5, 4);
    Ship s3(start_ship2, end_ship2);
        
    Position start_ship3(2, 8);
    Position end_ship3(2, 4);
    Ship s4(start_ship3, end_ship3);
        
    Position start_ship4(5, 6);
    Position end_ship4(5, 2);
    Ship s5(start_ship4, end_ship4);
        
    // test has_position()
    cout << endl << "Testing has_position()" << endl;
    Position pos(1, 4);
    cout << "Expected: 1, Actual: " << s2.has_position(pos) << endl;
    pos.set_row(2);
    pos.set_col(6);
    cout << "Expected: 1, Actual: " << s4.has_position(pos) << endl;
    pos.set_row(2);
    pos.set_col(2);
    cout << "Expected: 0, Actual: " << s4.has_position(pos) << endl;
    Position pos2(2, 5);
    cout << "Expected: 0, Actual: " << s2.has_position(pos2) << endl;
    Position pos3(0, 0);
    cout << "Expected: 0, Actual: " << s2.has_position(pos3) << endl;
    Position pos4(3, 4);
    cout << "Expected: 1, Actual: " << s3.has_position(pos4) << endl;
    Position pos5(1, 3);
    cout << "Expected: 1, Actual: " << s2.has_position(pos5) << endl;
    pos5.set_row(1);
    pos5.set_col(6);
    cout << "Expected: 1, Actual: " << s2.has_position(pos5) << endl;
    pos5.set_row(5);
    pos5.set_col(4);
    cout << "Expected: 1, Actual: " << s5.has_position(pos5) << endl;
    pos5.set_row(5);
    pos5.set_col(1);
    cout << "Expected: 0, Actual: " << s5.has_position(pos5) << endl;
        
        
    // test hit()
    cout << endl << "Testing hit()" << endl;
    s3.hit();
    cout << "Expected: 0, Actual: " << s3.has_sunk() << endl;
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    cout << "Expected: 1, Actual: " << s3.has_sunk() << endl;
        
    Position start_ship6(1, 2);
    Position end_ship6(1, 2);
    Ship ship1(start_ship6, end_ship6);
    ship1.hit();
    cout << "Expected: 1, Actual: " << ship1.has_sunk() << endl;
        
    s2.hit();
    cout << "Expected: 0, Actual: " << s2.has_sunk() << endl;
    s2.hit();
    s2.hit();
    s2.hit();
    cout << "Expected: 1, Actual: " << s2.has_sunk() << endl;
        
    s4.hit();
    s4.hit();
    cout << "Expected: 0, Actual: " << s4.has_sunk() << endl;
    s4.hit();
    s4.hit();
    s4.hit();
    cout << "Expected: 1, Actual: " << s4.has_sunk() << endl;
    return;
}

void test_player()
{
    //test of defaultor function
    cout << "Testing for default constructor" << endl;
    Player p1;
    p1.init_grid();
    cout << p1.get_name() << " " << p1.get_num_ships() << " "
    << p1.get_remaining_ships() << " " << endl;
    p1.print_grid();
    
    //test of 1st default constructor
    cout << "Testing for first non-default constructor" << endl;
    Player p2("Thomas");
    p2.init_grid();
    cout << p2.get_name() << " " << p2.get_num_ships() << " "
    << p2.get_remaining_ships() << " " << endl;
    p2.print_grid();
    
    //testing for add_ship
    Player p3;
    Position start1('1','c');
    Position start2('1','f');
    Ship s2(start1, start2);
    p3.add_ship(s2);
    cout << p3.get_num_ships() << " " << p3.get_remaining_ships() << " " << endl;
    p3.print_grid();
    Position start3('1','f');
    Position start4('1','c');
    Ship s3(start3, start4);
    p3.add_ship(s3);
    p3.print_grid();
    Position start5('3','F');
    Position start6('7','F');
    Ship s4(start5, start6);
    p3.add_ship(s4);
    p3.print_grid();
    Position start7('7','g');
    Position start8('3','G');
    Ship s5(start7, start8);
    p3.add_ship(s5);
    p3.print_grid();
    
    Player p4;
    Position start9('2','G');
    Position start10('5','G');
    Ship s6(start9, start10);
    p4.add_ship(s6);
    p4.print_grid();
    Position start11('1','H');
    Position start12('8','H');
    Ship s61(start11, start12);
    p4.add_ship(s61);
    p4.print_grid();
    Position start13('8','H');
    Position start14('1','H');
    Ship s62(start13, start14);
    p4.add_ship(s62);
    p4.print_grid();
    
    Player p41;
    Position start15('1','A');
    Position start16('8','A');
    Ship s63(start15, start16);
    p41.add_ship(s63);
    p41.print_grid();
    Position start17('8','A');
    Position start18('1','A');
    Ship s64(start17, start18);
    p41.add_ship(s64);
    p41.print_grid();
    
    Player p42;
    Position start19('1','A');
    Position start20('1','H');
    Ship s65(start19, start20);
    p42.add_ship(s65);
    p42.print_grid();
    Position start21('1','H');
    Position start22('1','A');
    Ship s66(start21, start22);
    p42.add_ship(s66);
    p42.print_grid();
    
    Player p43;
    Position start23('8','A');
    Position start24('8','H');
    Ship s67(start23, start24);
    p43.add_ship(s67);
    p43.print_grid();
    Position start25('8','H');
    Position start26('8','A');
    Ship s68(start25, start26);
    p43.add_ship(s68);
    p43.print_grid();
    
    //testing attack function
    Player p5;
    Player p6;
    Position a1('1','A');
    Position a2('1','C');
    Position b1('3','D');
    Position b2('3','F');
    Ship s7(a1, a2);
    Ship s8(b1, b2);
    p5.add_ship(s7);
    p6.add_ship(s8);
    p5.attack(p6, Position('3','E'));
    p5.attack(p6, Position('1','A'));
    p6.attack(p5, Position('1','A'));
    p6.attack(p5, Position('1','H'));
    p5.attack(p6, Position('3','E'));
    
    Player p7;
    Player p8;
    Position a3('1','G');
    Position a4('5','G');
    Position b3('4','D');
    Position b4('7','D');
    Ship s71(a3, a4);
    Ship s72(b3, b4);
    p7.add_ship(s71);
    p8.add_ship(s72);
    p7.attack(p8, Position('5','D'));
    p7.attack(p8, Position('8','D'));
    p8.attack(p7, Position('4','G'));
    p8.attack(p7, Position('6','g'));
    p7.attack(p8, Position('5','D'));
    
    Player p51;
    Player p61;
    Position a11('1','A');
    Position a22('1','C');
    Position b11('3','D');
    Position b22('3','F');
    Ship s73(a22, a11);
    Ship s74(b22, b11);
    p51.add_ship(s73);
    p61.add_ship(s74);
    p51.attack(p61, Position('3','E'));
    p51.attack(p61, Position('1','A'));
    p61.attack(p51, Position('1','a'));
    p61.attack(p51, Position('1','H'));
    p51.attack(p61, Position('3','e'));
    
    Player p71;
    Player p81;
    Position a31('1','G');
    Position a44('5','G');
    Position b31('4','D');
    Position b44('7','D');
    Ship s75(a44, a31);
    Ship s76(b44, b31);
    p71.add_ship(s75);
    p81.add_ship(s76);
    p71.attack(p81, Position('5','d'));
    p71.attack(p81, Position('8','D'));
    p81.attack(p71, Position('4','g'));
    p81.attack(p71, Position('6','G'));
    p71.attack(p81, Position('5','D'));
    
    Player p82;
    Player p83;
    Position c1('5','H');
    Position c2('8','H');
    Position c3('3','D');
    Position c4('3','G');
    Ship s78(c1, c2);
    Ship s79(c3, c4);
    p82.add_ship(s78);
    p83.add_ship(s79);
    p82.attack(p83, Position('6','H'));
    p82.attack(p83, Position('3','h'));
    p83.attack(p82, Position('3','D'));
    p83.attack(p82, Position('3','c'));
    p82.attack(p83, Position('6','h'));
    
    Player p85;
    Player p86;
    Position d1('1','B');
    Position d2('1','G');
    Position d3('3','C');
    Position d4('3','F');
    Ship s80(d1, d2);
    Ship s81(d3, d4);
    p85.add_ship(s80);
    p86.add_ship(s81);
    p85.attack(p86, Position('3','C'));
    p85.attack(p86, Position('3','D'));
    p85.attack(p86, Position('3','E'));
    p85.attack(p86, Position('3','F'));
    p85.attack(p86, Position('4','F'));
    p86.attack(p85, Position('1','B'));
    p86.attack(p85, Position('1','A'));
    p86.attack(p85, Position('1','B'));
    
    Player p87;
    Player p88;
    Position d5('1','B');
    Position d6('5','B');
    Position d7('4','C');
    Position d8('7','C');
    Ship s82(d5, d6);
    Ship s83(d7, d8);
    p87.add_ship(s82);
    p88.add_ship(s83);
    p87.attack(p88, Position('4','C'));
    p87.attack(p88, Position('5','c'));
    p87.attack(p88, Position('6','c'));
    p87.attack(p88, Position('7','C'));
    p87.attack(p88, Position('4','F'));
    p88.attack(p87, Position('1','B'));
    p88.attack(p87, Position('6','B'));
    p88.attack(p87, Position('1','B'));
    
    
    //testing
    Player p9;
    p9.load_grid_file("grid1.txt");
    p9.print_grid();
    Player p91;
    p91.load_grid_file("grid3.txt");
    p91.print_grid();
    Player p10;
    p10.load_grid_file("grid2.txt");
    p10.print_grid();
    p10.load_grid_file("grid3.txt");
    p10.print_grid();
    Player p11;
    p11.load_grid_file("grid1.txt");
    p11.print_grid();
    p11.load_grid_file("grid2.txt");
    p11.print_grid();
    p11.load_grid_file("grid3.txt");
    p11.print_grid();
    return;
}

void test_game()
{
   //test of default constructor
    Game g1;
    g1.get_p1().init_grid();
    g1.get_p2().init_grid();
    cout << g1.get_p1().get_name() << " " << g1.get_p1().get_num_ships() << " "
         << g1.get_p1().get_remaining_ships() << " " << g1.get_p2().get_name() <<
         " " << g1.get_p2().get_num_ships() << " " << g1.get_p2().get_remaining_ships() <<
    endl;
    g1.get_p1().print_grid();
    g1.get_p2().print_grid();
    
    //testing for getters
    Game a1;
    a1.get_p1().init_grid();
    a1.get_p2().init_grid();
    cout << a1.get_p1().get_name() << " " << a1.get_p1().get_num_ships() << " "
    << a1.get_p1().get_remaining_ships() << " " << a1.get_p2().get_name() <<
    " " << a1.get_p2().get_num_ships() << " " << a1.get_p2().get_remaining_ships() <<
    " " << a1.get_move("SAM") << " " << a1.get_move("Henry") << endl;
    a1.get_p1().print_grid();
    a1.get_p2().print_grid();
    
    Player c1;
    Player c2;
    Game a2(c1,"grid1.txt", c2,"grid2.txt");
    a2.get_p1().init_grid();
    a2.get_p2().init_grid();
    a2.get_p1().print_grid();
    a2.get_p2().print_grid();
    a2.get_p1().get_grid_at(1, 5);
    a2.get_p2().get_grid_at(5, 8);
    a2.get_p1().print_grid();
    a2.get_p2().print_grid();
    a2.get_p1().get_guess_grid_at(4, 5);
    a2.get_p2().get_grid_at(7, 5);
    a2.get_p1().print_grid();
    a2.get_p2().print_grid();
    a2.get_move(c1.get_name());
    cout << endl;
    a2.get_move(c2.get_name());
    cout << endl;
    a2.get_move("Henry");
    cout << endl;
    a2.get_move("Sam");
    cout << endl;
    cout << a2.get_p1().get_name() << " " << a2.get_p1().get_num_ships() << " "
         << a2.get_p1().get_remaining_ships() << " " << a2.get_p2().get_name() <<
         " " << a2.get_p2().get_num_ships() << " " << a2.get_p2().get_remaining_ships() <<
    endl;
    
    Player c3;
    Player c4;
    Game a3(c3,"grid3.txt", c4,"grid4.txt");
    a3.get_p1().init_grid();
    a3.get_p2().init_grid();
    a3.get_p1().print_grid();
    a3.get_p2().print_grid();
    a3.get_p1().get_grid_at(1, 5);
    a3.get_p2().get_grid_at(5, 8);
    a3.get_p1().print_grid();
    a3.get_p2().print_grid();
    a3.get_p1().get_guess_grid_at(4, 5);
    a3.get_p2().get_grid_at(7, 5);
    a3.get_p1().print_grid();
    a3.get_p2().print_grid();
    a3.get_move(c3.get_name());
    cout << endl;
    a3.get_move(c4.get_name());
    cout << endl;
    a3.get_move("Henry");
    cout << endl;
    a3.get_move("Sam");
    cout << endl;
    cout << a3.get_p1().get_name() << " " << a3.get_p1().get_num_ships() << " "
         << a3.get_p1().get_remaining_ships() << " " << a3.get_p2().get_name() <<
         " " << a3.get_p2().get_num_ships() << " " << a3.get_p2().get_remaining_ships() <<
    endl;
    
    Player c5("Harry");
    Player c6("Potter");
    Game a4(c5,"grid1.txt", c6,"grid3.txt");
    a4.get_p1().init_grid();
    a4.get_p2().init_grid();
    a4.get_p1().print_grid();
    a4.get_p2().print_grid();
    a4.get_p1().get_grid_at(4, 5);
    a4.get_p2().get_grid_at(5, 7);
    a4.get_p1().print_grid();
    a4.get_p2().print_grid();
    a4.get_p1().get_guess_grid_at(3, 5);
    a4.get_p2().get_grid_at(6, 5);
    a4.get_p1().print_grid();
    a4.get_p2().print_grid();
    a4.get_move(c5.get_name());
    cout << endl;
    a4.get_move(c6.get_name());
    cout << endl;
    a4.get_move("Henry");
    cout << endl;
    a4.get_move("Sam");
    cout << endl;
    cout << a4.get_p1().get_name() << " " << a4.get_p1().get_num_ships() << " "
         << a4.get_p1().get_remaining_ships() << " " << a4.get_p2().get_name() <<
         " " << a4.get_p2().get_num_ships() << " " << a4.get_p2().get_remaining_ships() <<
    endl;
    
    Player c7("Tom");
    Player c8("Ford");
    Game a5(c7,"grid4.txt", c8,"grid2.txt");
    a5.get_p1().init_grid();
    a5.get_p2().init_grid();
    a5.get_p1().print_grid();
    a5.get_p2().print_grid();
    a5.get_p1().get_grid_at(4, 5);
    a5.get_p2().get_grid_at(5, 7);
    a5.get_p1().print_grid();
    a5.get_p2().print_grid();
    a5.get_p1().get_guess_grid_at(3, 5);
    a5.get_p2().get_grid_at(6, 5);
    a5.get_p1().print_grid();
    a5.get_p2().print_grid();
    a5.get_move(c7.get_name());
    cout << endl;
    a5.get_move(c8.get_name());
    cout << endl;
    a5.get_move("Henry");
    cout << endl;
    a5.get_move("Sam");
    cout << endl;
    cout << a5.get_p1().get_name() << " " << a5.get_p1().get_num_ships() << " "
         << a5.get_p1().get_remaining_ships() << " " << a5.get_p2().get_name() <<
         " " << a5.get_p2().get_num_ships() << " " << a5.get_p2().get_remaining_ships() <<
    endl;
    
    //test for non-default constructor
    Player p3("Thomas");
    Player p4("Charles");
    Game g2(p3, "", p4, "hello");
    p3.print_grid();
    p4.print_grid();
    
    Player p5("Thames");
    Player p6("Nate");
    Game g3(p5, "HELLO", p6, "");
    p5.print_grid();
    p6.print_grid();
    
    Player p7("Sam");
    Player p8("Roster");
    Game g4(p7, "", p8, "");
    p7.print_grid();
    p8.print_grid();
    
    //testing for valid move
    string move1 = "-1A";
    string move2 = "3b";
    string move3 = "AGDH";
    string move4 = "9c";
    string move5 = "8J";
    string move6 = "9J";
    string move7 = "1G";
    Game g5;
    Game g6;
    g5.check_valid_move(move1);
    g6.check_valid_move(move2);
    g5.check_valid_move(move3);
    g5.check_valid_move(move4);
    g5.check_valid_move(move5);
    g5.check_valid_move(move6);
    g5.check_valid_move(move7);
    return;
}

