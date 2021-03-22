#include "voitto.h"
#include "ui_voitto.h"

Voitto::Voitto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voitto)
{
    ui->setupUi(this);
}

Voitto::~Voitto()
{
    delete ui;
}

void Voitto::on_pushButton_clicked()
{
    this->close();
}
