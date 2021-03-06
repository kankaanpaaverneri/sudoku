

#include "sudoku.h"
#include "Grid.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Init sudoku values to grid object
    srand(time(nullptr));
    Grid grid;
    while(!grid.init_sudoku())
           grid.reset_grid();
    //grid.display_grid();

    if(grid.check_sudoku() == false)
    {
        std::cout << "VIRHEELLINEN SUDOKU" << std::endl;
    }

    grid.erase_random_values_from_grid();

    //Init sudoku GUI
    Sudoku w(nullptr, grid);
    w.resize(1000, 800);
    w.show();
    return a.exec();
}
