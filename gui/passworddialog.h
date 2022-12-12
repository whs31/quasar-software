#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr, QString password = "123");
    ~PasswordDialog();

    bool passwordCheck = false;

private slots:
    void on_passwordField_textChanged(const QString &arg1);

private:
    Ui::PasswordDialog *ui;
    QString _password;
};

#endif // PASSWORDDIALOG_H
