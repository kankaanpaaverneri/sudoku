#include "sudoku.h"
#include "ui_sudoku.h"
#include "voitto.h"

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);
}

Sudoku::Sudoku(QWidget *parent, Grid &grid)
    : QMainWindow(parent), ui(new Ui::Sudoku)
{
    ui->setupUi(this);
    init_gui_sudoku_values(grid);
}

Sudoku::~Sudoku()
{
    delete ui;
}

void Sudoku::reset_checked_buttons()
{
    for(size_t i = 0; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            if(buttons.at(i).at(j)->text() == " ")
            {
                buttons.at(i).at(j)->setChecked(false);
            }
        }
    }
}

void Sudoku::reset_color_values(Grid &grid)
{
    for(size_t i = 0; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            if(buttons.at(i).at(j)->styleSheet() == TEXT_COLOR_RED)
            {
                const int number = buttons.at(i).at(j)->text().toInt();
                const Coor coordinates = grid.init_coordinates(j, i);
                if(grid.check_if_value_exists(number, coordinates) != NOT_FOUND)
                {
                    buttons.at(i).at(j)->setStyleSheet(TEXT_COLOR_RED);
                }
            }
        }
    }
}

void Sudoku::init_gui_sudoku_values(Grid &grid)
{
    buttons = init_pushButton_array();
    QString str;

    for(unsigned int i = 0; i < GRID_SIZE; i++)
    {
        for(unsigned int j = 0; j < GRID_SIZE; j++)
        {
            Coor coordinates = grid.init_coordinates(j, i);
            str.push_back(grid.get_grid_value(coordinates));
        }
    }
    size_t i {0}, k {0};
    for(i = 0; i < GRID_SIZE; i++)
    {
        std::array<QPushButton*, GRID_SIZE> row;
        row = buttons.at(i);
        for(auto &button: row)
        {
            button->setText(str.at(k));
            k++;
        }
    }
    for(i = 0; i < GRID_SIZE; i++)
    {
        std::array<QPushButton*, GRID_SIZE> row;
        row = buttons.at(i);
        for(auto &button: row)
        {
            if(button->text() != ' ')
            {
                button->setStyleSheet("background-color: rgb(136, 138, 133);color: rgb(255, 255, 255);");
            }
            else
            {
                button->setCheckable(true);
            }
        }
    }
}

void Sudoku::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_1 || event->key() == Qt::Key_2
            || event->key() == Qt::Key_3 || event->key() == Qt::Key_4
            || event->key() == Qt::Key_5 || event->key() == Qt::Key_6
            || event->key() == Qt::Key_7 || event->key() == Qt::Key_8
            || event->key() == Qt::Key_9 || event->key() == Qt::Key_Backspace)
    {
        enter_value_to_grid(event->key());
    }
}

bool Sudoku::enter_value_to_grid(const int number)
{
    Grid grid;
    grid.copy_values_to_grid(buttons);
    Sudoku::reset_color_values(grid);
    for(size_t i {0}; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            if(buttons.at(i).at(j)->isChecked())
            {
                Coor coordinates = grid.init_coordinates(j, i);

                if(grid.check_if_value_exists(number, coordinates) == Status::NOT_FOUND)
                {
                    buttons.at(i).at(j)->setStyleSheet(TEXT_COLOR_BLACK);
                }
                else
                {
                    buttons.at(i).at(j)->setStyleSheet(TEXT_COLOR_RED);
                }

                if(number == Qt::Key_Backspace)
                    buttons.at(i).at(j)->setText(" ");
                else
                    buttons.at(i).at(j)->setText(QString(number));

                buttons.at(i).at(j)->setChecked(false);
                Sudoku::reset_checked_buttons();

                grid.set_grid_value(coordinates, number);

                if(winning_condition())
                {
                     Voitto v;
                     v.setModal(true);
                     v.exec();
                     QApplication::quit();
                }
                return true;
            }
        }
    }
    return false;
}

std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> Sudoku::init_pushButton_array()
{
    std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> pushButtons
    {{
        {ui->pushButton, ui->pushButton_2, ui->pushButton_3,
        ui->pushButton_4, ui->pushButton_5, ui->pushButton_6,
        ui->pushButton_7, ui->pushButton_8, ui->pushButton_9},
        {ui->pushButton_10, ui->pushButton_11, ui->pushButton_12,
        ui->pushButton_13, ui->pushButton_14, ui->pushButton_15,
        ui->pushButton_16, ui->pushButton_17, ui->pushButton_18},
        {ui->pushButton_19, ui->pushButton_20, ui->pushButton_21,
        ui->pushButton_22, ui->pushButton_23, ui->pushButton_24,
        ui->pushButton_25, ui->pushButton_26, ui->pushButton_27},
        {ui->pushButton_28, ui->pushButton_29, ui->pushButton_30,
        ui->pushButton_31, ui->pushButton_32, ui->pushButton_33,
        ui->pushButton_34, ui->pushButton_35, ui->pushButton_36},
        {ui->pushButton_37, ui->pushButton_38, ui->pushButton_39,
        ui->pushButton_40, ui->pushButton_41, ui->pushButton_42,
        ui->pushButton_43, ui->pushButton_44, ui->pushButton_45},
        {ui->pushButton_46, ui->pushButton_47, ui->pushButton_48,
        ui->pushButton_49, ui->pushButton_50, ui->pushButton_51,
        ui->pushButton_52, ui->pushButton_53, ui->pushButton_54},
        {ui->pushButton_55, ui->pushButton_56, ui->pushButton_57,
        ui->pushButton_58, ui->pushButton_59, ui->pushButton_60,
        ui->pushButton_61, ui->pushButton_62, ui->pushButton_63},
        {ui->pushButton_64, ui->pushButton_65, ui->pushButton_66,
        ui->pushButton_67, ui->pushButton_68, ui->pushButton_69,
        ui->pushButton_70, ui->pushButton_71, ui->pushButton_72},
        {ui->pushButton_73, ui->pushButton_74, ui->pushButton_75,
        ui->pushButton_76, ui->pushButton_77, ui->pushButton_78,
        ui->pushButton_79, ui->pushButton_80, ui->pushButton_81}
    }};

    return pushButtons;
}

bool Sudoku::winning_condition()
{
    for(size_t i = 0; i < GRID_SIZE; i++)
    {
        for(size_t j = 0; j < GRID_SIZE; j++)
        {
            if(buttons.at(i).at(j)->text() == " " || buttons.at(i).at(j)->styleSheet() == TEXT_COLOR_RED)
            {
                return false;
            }
        }
    }
    return true;
}
