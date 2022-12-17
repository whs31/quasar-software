#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent, QString password) :
    QDialog(parent),
    _password(password),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_passwordField_textChanged(const QString &arg1)
{
    if(arg1 == _password)
    {
        passwordCheck = true;
    } else {
        passwordCheck = false;
    }
}

