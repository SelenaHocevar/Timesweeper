#include "Headers/Options.h"
#include "ui_Options.h"

Options::Options(QWidget *parent) : QMainWindow(parent), ui(new Ui::Options)
{
    ui->setupUi(this);
    setFixedSize(800,500);
    setWindowTitle("timesweeper");
}

Options::~Options()
{
    delete ui;
}