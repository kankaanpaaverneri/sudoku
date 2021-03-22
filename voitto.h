#ifndef VOITTO_H
#define VOITTO_H

#include <QDialog>

namespace Ui {
class Voitto;
}

class Voitto : public QDialog
{
    Q_OBJECT

public:
    explicit Voitto(QWidget *parent = nullptr);
    ~Voitto();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Voitto *ui;
};

#endif // VOITTO_H
