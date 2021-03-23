#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <string>

#include "ui_sudoku.h"

#define EMPTY ' '
#define GRID_SIZE 9

enum Status : int
{
    ZERO = 0,
    ROW = 1,
    COLUMN = 2,
    SECTION = 3,
    NOT_FOUND = 4
};

#define MAX_TRACK_NUMBER_CALLS 2000

typedef struct coordinates {
    int x, y;
}Coor;

class Grid {
    private:
        std::array<std::array<char, GRID_SIZE>, GRID_SIZE> grid;
        static int track_number_counter;
    public:
        Grid();
        ~Grid() = default;

        bool check_sudoku();

        //GETTERS AND SETTERS
        static int get_track_number_counter() {return track_number_counter;}
        char get_grid_value(const Coor &coordinates) const;
        void set_grid_value(const Coor &coordinates, const char value);

        //Initializers
        bool init_sudoku();
        Coor init_coordinates(const int x, const int y);
        void init_from_one_to_nine(std::array<char, GRID_SIZE> &temp_array);

        //Reset functions
        void reset_grid();
        void reset_row_array_values(std::array<char, GRID_SIZE> &number_array);
        bool reset_row_index(size_t &index);

        void erase_random_values_from_grid();
        void copy_values_to_grid(std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> &src);

        int check_if_value_exists(const char number, Coor current_location);
        bool scan_row(const char number, Coor current_location);
        bool scan_column(const char number, Coor current_location);
        bool scan_section(const char number, const Coor section_begin, const Coor current_location);

        Coor find_section(const Coor current_location);
        bool replace_values(char number, Coor current_location);
        bool swap_values_from_current_row(char number, Coor current_location);

        void add_number_to_grid(char &number, const Coor current_location);
        
        void shuffle(std::array<char, GRID_SIZE> &row);
        bool loop_through_until_not_zero(size_t &cur_index, const std::array<char, GRID_SIZE> &row);


        template<typename T>
        void swap(T &i, T &j);

        void display_grid() const;

        //Track number functions
        void track_number(char &number, Coor &current_location);
        bool track_column(char &number, Coor &current_location);
        bool track_row(char &number, Coor &current_location);
        bool track_section(char &number, const Coor &section_begin, Coor &current_location);
};

#endif

