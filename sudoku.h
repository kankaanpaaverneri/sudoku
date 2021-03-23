#ifndef SUDOKU_H
#define SUDOKU_H

#include <QtWidgets/QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include "Grid.h"
#include "ui_sudoku.h"

#define PUSH_BUTTON_COUNT 81
#define ARRAY_LENGTH 9

#define TEXT_COLOR_RED "background-color: rgb(239, 41, 41);"
#define TEXT_COLOR_BLACK "color: rgb(0, 0, 0);"


QT_BEGIN_NAMESPACE
namespace Ui { class Sudoku; }
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    Sudoku(QWidget *parent, Grid &grid);
    ~Sudoku();

    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> buttons;
    Ui::Sudoku *ui;
    void init_gui_sudoku_values(Grid &grid);
    std::array<std::array<QPushButton*, GRID_SIZE>, GRID_SIZE> init_pushButton_array();
    bool enter_value_to_grid(const int number);
    void reset_checked_buttons();
    void reset_color_values(Grid &grid);
    bool winning_condition();
};
#endif // SUDOKU_H
