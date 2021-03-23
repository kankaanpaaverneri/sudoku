#include "Grid.h"

int Grid::track_number_counter = 0;

//Initialiaizes grid with empty values
Grid::Grid() {
    for(unsigned int i = 0; i < GRID_SIZE; i++) {
        for(unsigned int j = 0; j < GRID_SIZE; j++) {
            grid.at(i).at(j) = EMPTY;
        }
    }
}

bool Grid::check_sudoku()
{
    for(size_t i = 0; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            Coor cur_location = init_coordinates(j, i);
            if(check_if_value_exists(grid.at(i).at(j), cur_location) != Status::NOT_FOUND)
                return false;
        }
    }
    return true;
}

char Grid::get_grid_value(const Coor &coordinates) const
{
    return grid.at(coordinates.y).at(coordinates.x);
}

void Grid::set_grid_value(const Coor &coordinates, const char value)
{
    grid.at(coordinates.y).at(coordinates.x) = value;
}

//Generates random numbers to sudoku game
bool Grid::init_sudoku()
{
    std::array<char, GRID_SIZE> row;
    for(int i = 0; i < GRID_SIZE; i++)
    {
        reset_row_array_values(row); //Resets the row with random values from 1 to 9

        size_t row_index {0}, fail_counter {0};

        for(int j = 0; j < GRID_SIZE; j++)
        {
            Coor current_location = init_coordinates(j, i);
            if(check_if_value_exists(row.at(row_index), current_location) == Status::NOT_FOUND)
            {
                //Adds the value to the grid and replaces the corresponding value in the row to 0.
                grid.at(i).at(j) = row.at(row_index);
                row.at(row_index) = '0';
                //display_grid();
                fail_counter = 0;
            }
            else
            {
                j--;
                fail_counter++;
            }
            row_index++;
            reset_row_index(row_index);
            loop_through_until_not_zero(row_index, row);

            if(fail_counter >= GRID_SIZE) //If fail_counter reaches 9 we start to replace values
            {
                if(replace_values(row.at(row_index), current_location) == false)
                    return false;
                else
                    grid.at(current_location.y).at(current_location.x) = row.at(row_index);
            }
        }
    }
    return true;
}

Coor Grid::init_coordinates(const int x, const int y)
{
    Coor coordinates;
    coordinates.x = x;
    coordinates.y = y;
    return coordinates;
}

void Grid::init_from_one_to_nine(std::array<char, GRID_SIZE> &temp_array)
{
    for(size_t i {0}; i < temp_array.size(); i++)
    {
        temp_array.at(i) = static_cast<char>(i+1)+48;
    }
}

void Grid::reset_grid()
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        for(int j = 0; j < GRID_SIZE; j++)
        {
            grid.at(i).at(j) = EMPTY;
        }
    }
}

void Grid::reset_row_array_values(std::array<char, GRID_SIZE> &number_array)
{
    init_from_one_to_nine(number_array);
    shuffle(number_array);
}

//Resets the index that is pointing to the row_array
bool Grid::reset_row_index(size_t &index)
{
    if(index >= GRID_SIZE)
    {
        index = 0;
        return true;
    }
    return false;
}

void Grid::erase_random_values_from_grid()
{
    for(unsigned int i = 0; i < GRID_SIZE; i++)
    {
        for(unsigned int j = 0; j < GRID_SIZE; j++)
        {
            int x {0};
            x = rand()%GRID_SIZE;
            if(x > 3)
                grid.at(i).at(j) = ' ';
        }
    }
}

//Copys values from Qt PushButton text property to this objects array
void Grid::copy_values_to_grid(std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> &src)
{
    for(size_t i = 0; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            std::string temp = src.at(i).at(j)->text().toUtf8().constData();
            this->grid.at(i).at(j) = temp.at(0);
        }
    }
}

int Grid::check_if_value_exists(const char number, Coor current_location)
{
    if(number == '0')
        return Status::ZERO;

    if(scan_row(number, current_location))
        return Status::ROW;

    if(scan_column(number, current_location))
        return Status::COLUMN;

    Coor section_begin = find_section(current_location);
    if(scan_section(number, section_begin, current_location))
        return Status::SECTION;

    return Status::NOT_FOUND;
}

bool Grid::scan_row(const char number, Coor current_location)
{
    for(int j = 0; j < GRID_SIZE; j++)
    {
        if(grid.at(current_location.y).at(j) == number && j != current_location.x)
        {
            return true;
        }
    }
    return false;
}

bool Grid::scan_column(const char number, Coor current_location)
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        if(grid.at(i).at(current_location.x) == number && i != current_location.y)
        {
            return true;
        }
    }
    return false;
}

bool Grid::scan_section(const char number, const Coor section_begin, const Coor current_location)
{
    for(int i = section_begin.y; i < section_begin.y + Status::SECTION; i++)
    {
        for(int j = section_begin.x; j < section_begin.x + Status::SECTION; j++)
        {
            if(grid.at(i).at(j) == number)
            {
                if(i != current_location.y && j != current_location.x)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

Coor Grid::find_section(const Coor current_location)
{
    Coor section_begin = init_coordinates(0, 0);
    int i {0}, j {0};
    int cur_section {1};
    while(cur_section <= 9)
    {
        for(i = section_begin.y; i < section_begin.y + Status::SECTION; i++)
        {
            for(j = section_begin.x; j < section_begin.x + Status::SECTION; j++)
            {
                if(current_location.y == i && current_location.x == j)
                {
                    return section_begin;
                }
            }
        }
        if(cur_section == 3 || cur_section == 6)
        {
            section_begin = init_coordinates(0, i);
        } else
        {
            section_begin = init_coordinates(j, i-3);
        }
        cur_section++;
    }
    return section_begin;
}

bool Grid::replace_values(char number, Coor current_location)
{
    if(!swap_values_from_current_row(number, current_location))
    {
        //If we tried to replace every value in the current row.
        //We start to track the numbers one by one in the grid and replacing them recursively.
        track_number(number, current_location);
        if(get_track_number_counter() == MAX_TRACK_NUMBER_CALLS) {
            return false;
        }
    }
    return true;
}

bool Grid::swap_values_from_current_row(char number, Coor current_location) {

    for(int j {0}; j < current_location.x; j++)
    {
        Coor swap_location = init_coordinates(j, current_location.y);
        int match {0};
        char temp {grid.at(swap_location.y).at(j)};
        //check if swap_location is valid location for number
        if(check_if_value_exists(number, swap_location) == Status::NOT_FOUND)
        {
            match++;
            //temporary EMPTY will be placed here during comparison
            grid.at(swap_location.y).at(j) = EMPTY;
        }
        //check if current location is valid location for swap_location number
        if(check_if_value_exists(temp, current_location) == Status::NOT_FOUND)
        {
            match++;
        }
        grid.at(swap_location.y).at(j) = temp;
        if(match == 2)
        {
            swap<char>(grid.at(swap_location.y).at(j), number);
            return true;
        }
    }
    return false;
}

void Grid::shuffle(std::array<char, GRID_SIZE> &number_array)
{
    size_t i = 0;
    while(i < number_array.size())
    {
        size_t random_index = rand() % GRID_SIZE;
        swap<char>(number_array.at(i), number_array.at(random_index));
        i++;
    }
}

//Loops the whole array until it find zeros.
bool Grid::loop_through_until_not_zero(size_t &cur_index, const std::array<char, GRID_SIZE> &row)
{
    size_t loops {0};
    while(row.at(cur_index) == '0')
    {
        cur_index++;
        if(reset_row_index(cur_index) == true)
        {
            loops++;
        }

        if(loops >= 2)
        {
            //All of the elements are 0
            return true;
        }
    }
    return false;
}

template<typename T>
void Grid::swap(T &i, T &j)
{
    T temp = i;
    i = j;
    j = temp;
}

//DISPLAYS NUMBERS TO TERMINAL(CLI)
void Grid::display_grid() const
{
    int space {0}, new_line {0};
    for(size_t i = 0; i < grid.size(); i++)
    {
        for(size_t j = 0; j < grid.size(); j++)
        {
            space++;
            std::cout << grid.at(i).at(j) << " ";
            if(space == 3)
            {
                std::cout << " ";
                space = 0;
            }
        }
        std::cout << std::endl;
        new_line++;
        if(new_line == 3 && i != 8)
        {
            std::cout << std::endl;
            new_line = 0;
        }
    }
}

/*
Recursive loop that scans the section, column and the row and tries to find an equal number.
If equal number is found the it will replace the number and then function will be called again
for scaning the replaced number.
*/
void Grid::track_number(char &number, Coor &current_location) // Parameters are the value to look for and a location from to look for.
{
    //std::cout << "Track number called: " << get_track_number_counter() << std::endl;
    if(get_track_number_counter() >= MAX_TRACK_NUMBER_CALLS)
    {
        return;
    }
    track_number_counter++;
    if(check_if_value_exists(number, current_location) == Status::NOT_FOUND)
    {
        return;
    }
    else
    {
        grid.at(current_location.y).at(current_location.x) = number;

        Coor section_begin = find_section(current_location);
        if(scan_section(number, section_begin, current_location))
        {
            Coor left_of = current_location;
            track_section(number, section_begin, current_location);
            track_number(number, current_location);
            current_location = left_of;
            number = grid.at(current_location.y).at(current_location.x);
        }

        if(scan_column(number, current_location))
        {
            Coor left_of = current_location;
            track_column(number, current_location);
            track_number(number, current_location);
            current_location = left_of;
            number = grid.at(current_location.y).at(current_location.x);
        }

        if(scan_row(number, current_location))
        {
            Coor left_of = current_location;
            track_row(number, current_location);
            track_number(number, current_location);
            current_location = left_of;
            number = grid.at(current_location.y).at(current_location.x);
        }
    }
}

bool Grid::track_column(char &number, Coor &current_location)
{
    //initializes useable_values array
    std::array<char, GRID_SIZE> useable_values;
    init_from_one_to_nine(useable_values);
    for(int i {0}; i < GRID_SIZE; i++)
    {
        for(int j {0}; j < GRID_SIZE; j++)
        {
            if(grid.at(i).at(current_location.x) == useable_values.at(j))
            {
                useable_values.at(j) = '0';
            }
        }
    }

    //Changes the current_location coordinates
    for(int i {0}; i < GRID_SIZE; i++)
    {
        if(grid.at(i).at(current_location.x) == number && i != current_location.y)
        {
            current_location = init_coordinates(current_location.x, i);
            break;
        }
    }
    size_t index {0};
    loop_through_until_not_zero(index, useable_values);
    while(useable_values.at(index) == '0')
    {
        index = rand() % GRID_SIZE;
    }
    
    grid.at(current_location.y).at(current_location.x) = useable_values.at(index);
    number = grid.at(current_location.y).at(current_location.x);
    return true;
}

bool Grid::track_row(char &number, Coor &current_location)
{
    //intializes useable_values
    std::array<char, GRID_SIZE> useable_values;
    init_from_one_to_nine(useable_values);
    for(int j {0}; j < GRID_SIZE; j++)
    {
        for(int i {0}; i < GRID_SIZE; i++)
        {
            if(grid.at(current_location.y).at(j) == useable_values.at(i))
                useable_values.at(i) = '0';
        }
    }

    //Changes the current_location cordinates
    for(int j {0}; j < GRID_SIZE; j++)
    {
        if(grid.at(current_location.y).at(j) == number && j != current_location.x)
        {
            current_location = init_coordinates(j, current_location.y);
            break;
        }
    }
    size_t index {0};
    loop_through_until_not_zero(index, useable_values);

    while(useable_values.at(index) == '0')
    {
        index = rand() % GRID_SIZE;
    }

    grid.at(current_location.y).at(current_location.x) = useable_values.at(index);
    number = grid.at(current_location.y).at(current_location.x);
    return true;
}

bool Grid::track_section(char &number, const Coor &section_begin, Coor &current_location)
{
    //initializes useable_values array
    std::array<char, GRID_SIZE> useable_values;
    init_from_one_to_nine(useable_values);
    size_t index {0};
    for(int i {section_begin.y}; i < section_begin.y + Status::SECTION; i++)
    {
        for(int j {section_begin.x}; j < section_begin.x + Status::SECTION; j++)
        {
            index = 0;
            while(index < GRID_SIZE)
            {
                if(grid.at(i).at(j) == useable_values.at(index))
                {
                    useable_values.at(index) = '0';
                }
                index++;
            }
        }
    }

    //Changes the current_location cordinates
    for(int i {section_begin.y}; i < section_begin.y + Status::SECTION; i++)
    {
        bool exit_loop {false};
        for(int j {section_begin.x}; j < section_begin.x + Status::SECTION; j++)
        {
            if(grid.at(i).at(j) == number)
            {
                if(i != current_location.y && j != current_location.x)
                {
                    current_location = init_coordinates(j, i);
                    exit_loop = true;
                    break;
                }
            }
        }
        if(exit_loop)
            break;
    }
    index = 0;
    loop_through_until_not_zero(index, useable_values);

    while(useable_values.at(index) == '0')
    {
        index = rand() % GRID_SIZE;
    }

    grid.at(current_location.y).at(current_location.x) = useable_values.at(index);
    number = grid.at(current_location.y).at(current_location.x);
    return true;
}
