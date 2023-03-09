#ifndef DARK_H
#define DARK_H

#include <QObject>
#include <QString>

class Dark : public QObject
{
    Q_OBJECT
public:
    explicit Dark(QObject *parent = nullptr);
        QString prm_darkest;
        QString prm_darker = "#2E3440";
        QString prm_dark = "#3B4252";
        QString prm_light = "#434C5E";
        QString prm_lighter = "#4C566A";
        QString prm_lightest;
        QString txt_faded = "#D8DEE9";
        QString txt_colored = "#B48EAD";
        QString txt_white = "#ECEFF4";
        QString wrn_darkest = "#D08770";
        QString wrn_darker = "#D08770";
        QString wrn_dark = "#D08770";
        QString wrn_light = "#EBCB8B";
        QString wrn_lighter = "#EBCB8B";
        QString wrn_lightest;
        QString acc_darkest;
        QString acc_darker = "#B48EAD";
        QString acc_dark = "#B48EAD";
        QString acc_light = "#B48EAD";
        QString acc_lighter = "#B48EAD";
        QString acc_lightest;
        QString inf_darkest;
        QString inf_darker = "#5E81AC";
        QString inf_dark = "#81A1C1";
        QString inf_light = "#88C0D0";
        QString inf_lighter = "#8FBCBB";
        QString inf_lightest;
        QString err_darkest;
        QString err_darker = "#BF616A";
        QString err_dark = "#BF616A";
        QString err_light;
        QString err_lighter = "#BF616A";
        QString err_lightest;
        QString scs_darkest;
        QString scs_darker;
        QString scs_dark;
        QString scs_light;
        QString scs_lighter = "#A3BE8C";
        QString scs_lightest;
        QString msc_brown = "#7D5233";
    

signals:

};

#endif // DARK_H
