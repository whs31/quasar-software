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
        QString prm_darker = "#121617";
        QString prm_dark = "#293133";
        QString prm_light = "#3e4c4f";
        QString prm_lighter = "#6d848a";
        QString prm_lightest;
        QString txt_faded = "#b2b9bb";
        QString txt_colored = "#b4b4dc";
        QString txt_white = "#dae1e5";
        QString wrn_darkest = "#372b07";
        QString wrn_darker = "#886911";
        QString wrn_dark = "#bc9117";
        QString wrn_light = "#c7a750";
        QString wrn_lighter = "#c4bb4b";
        QString wrn_lightest;
        QString acc_darkest;
        QString acc_darker = "#27183d";
        QString acc_dark = "#4b2e75";
        QString acc_light = "#a385cf";
        QString acc_lighter = "#b8a1da";
        QString acc_lightest;
        QString inf_darkest;
        QString inf_darker = "#173846";
        QString inf_dark = "#2B6781";
        QString inf_light = "#3681A2";
        QString inf_lighter = "#43a1ca";
        QString inf_lightest;
        QString err_darkest;
        QString err_darker = "#701828";
        QString err_dark = "#b16573";
        QString err_light;
        QString err_lighter = "#de3857";
        QString err_lightest;
        QString scs_darkest;
        QString scs_darker;
        QString scs_dark;
        QString scs_light;
        QString scs_lighter = "#73c924";
        QString scs_lightest;
        QString msc_brown = "#7D5233";
    

signals:

};

#endif // DARK_H
