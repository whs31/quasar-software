#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include "themes/dark.h"
#include "themes/swampgreen.h"

enum CurrentTheme : short
{
    Swamp,
    Dark
};

class ThemeManager : public QObject
{
    Q_GADGET
    Q_PROPERTY(QString primaryDarkest   MEMBER prm_darkest)
    Q_PROPERTY(QString primaryDarker    MEMBER prm_darker)
    Q_PROPERTY(QString primaryDark      MEMBER prm_dark)
    Q_PROPERTY(QString primaryLight     MEMBER prm_light)
    Q_PROPERTY(QString primaryLighter   MEMBER prm_lighter)
    Q_PROPERTY(QString primaryLightest  MEMBER prm_lightest)

    Q_PROPERTY(QString textFaded        MEMBER txt_faded)
    Q_PROPERTY(QString textColored      MEMBER txt_colored)
    Q_PROPERTY(QString textWhite        MEMBER txt_white)

    Q_PROPERTY(QString warningDarkest   MEMBER wrn_darkest)
    Q_PROPERTY(QString warningDarker    MEMBER wrn_darker)
    Q_PROPERTY(QString warningDark      MEMBER wrn_dark)
    Q_PROPERTY(QString warningLight     MEMBER wrn_light)
    Q_PROPERTY(QString warningLighter   MEMBER wrn_lighter)
    Q_PROPERTY(QString warningLightest  MEMBER wrn_lightest)

    Q_PROPERTY(QString accentDarkest    MEMBER acc_darkest)
    Q_PROPERTY(QString accentDarker     MEMBER acc_darker)
    Q_PROPERTY(QString accentDark       MEMBER acc_dark)
    Q_PROPERTY(QString accentLight      MEMBER acc_light)
    Q_PROPERTY(QString accentLighter    MEMBER acc_lighter)
    Q_PROPERTY(QString accentLightest   MEMBER acc_lightest)

    Q_PROPERTY(QString infoDarkest      MEMBER inf_darkest)
    Q_PROPERTY(QString infoDarker       MEMBER inf_darker)
    Q_PROPERTY(QString infoDark         MEMBER inf_dark)
    Q_PROPERTY(QString infoLight        MEMBER inf_light)
    Q_PROPERTY(QString infoLighter      MEMBER inf_lighter)
    Q_PROPERTY(QString infoLightest     MEMBER inf_lightest)

    Q_PROPERTY(QString errorDarkest     MEMBER err_darkest)
    Q_PROPERTY(QString errorDarker      MEMBER err_darker)
    Q_PROPERTY(QString errorDark        MEMBER err_dark)
    Q_PROPERTY(QString errorLight       MEMBER err_light)
    Q_PROPERTY(QString errorLighter     MEMBER err_lighter)
    Q_PROPERTY(QString errorLightest    MEMBER err_lightest)

    Q_PROPERTY(QString successDarkest   MEMBER scs_darkest)
    Q_PROPERTY(QString successDarker    MEMBER scs_darker)
    Q_PROPERTY(QString successDark      MEMBER scs_dark)
    Q_PROPERTY(QString successLight     MEMBER scs_light)
    Q_PROPERTY(QString successLighter   MEMBER scs_lighter)
    Q_PROPERTY(QString successLightest  MEMBER scs_lightest)

    Q_PROPERTY(QString miscBrown        MEMBER msc_brown)

public:
    static ThemeManager* get(QObject* parent = nullptr, short themeInitializer = 0);
        QString prm_darkest;
        QString prm_darker;
        QString prm_dark;
        QString prm_light;
        QString prm_lighter;
        QString prm_lightest;
        QString txt_faded;
        QString txt_colored;
        QString txt_white;
        QString wrn_darkest;
        QString wrn_darker;
        QString wrn_dark;
        QString wrn_light;
        QString wrn_lighter;
        QString wrn_lightest;
        QString acc_darkest;
        QString acc_darker;
        QString acc_dark;
        QString acc_light;
        QString acc_lighter;
        QString acc_lightest;
        QString inf_darkest;
        QString inf_darker;
        QString inf_dark;
        QString inf_light;
        QString inf_lighter;
        QString inf_lightest;
        QString err_darkest;
        QString err_darker;
        QString err_dark;
        QString err_light;
        QString err_lighter;
        QString err_lightest;
        QString scs_darkest;
        QString scs_darker;
        QString scs_dark;
        QString scs_light;
        QString scs_lighter;
        QString scs_lightest;
        QString msc_brown;

    CurrentTheme currentTheme = CurrentTheme::Swamp;

signals:

private:
    static ThemeManager* _instance;
    explicit ThemeManager(QObject *parent = nullptr, short themeInitializer = 0);

};

#endif // THEMEMANAGER_H
