#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QColor>
#include <QDebug>
#include "qqml.h"
#include "themes/dark.h"
#include "themes/swampgreen.h"

enum CurrentTheme : short
{
    Swamp,
    Dark
};

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor primaryDarkest   READ getPrimaryDarkest)
    Q_PROPERTY(QColor primaryDarker    READ getPrimaryDarker)
    Q_PROPERTY(QColor primaryDark      READ getPrimaryDark)
    Q_PROPERTY(QColor primaryLight     READ getPrimaryLight)
    Q_PROPERTY(QColor primaryLighter   READ getPrimaryLighter)
    Q_PROPERTY(QColor primaryLightest  READ getPrimaryLightest)

    Q_PROPERTY(QColor textFaded        READ getTextFaded)
    Q_PROPERTY(QColor textColored      READ getTextColored)
    Q_PROPERTY(QColor textWhite        READ getTextWhite)

    Q_PROPERTY(QColor warningDarkest   READ getWarningDarkest)
    Q_PROPERTY(QColor warningDarker    READ getWarningDarker)
    Q_PROPERTY(QColor warningDark      READ getWarningDark)
    Q_PROPERTY(QColor warningLight     READ getWarningLight)
    Q_PROPERTY(QColor warningLighter   READ getWarningLighter)
    Q_PROPERTY(QColor warningLightest  READ getWarningLightest)

    Q_PROPERTY(QColor accentDarkest    READ getAccentDarkest)
    Q_PROPERTY(QColor accentDarker     READ getAccentDarker)
    Q_PROPERTY(QColor accentDark       READ getAccentDark)
    Q_PROPERTY(QColor accentLight      READ getAccentLight)
    Q_PROPERTY(QColor accentLighter    READ getAccentLighter)
    Q_PROPERTY(QColor accentLightest   READ getAccentLightest)

    Q_PROPERTY(QColor infoDarkest      READ getInfoDarkest)
    Q_PROPERTY(QColor infoDarker       READ getInfoDarker)
    Q_PROPERTY(QColor infoDark         READ getInfoDark)
    Q_PROPERTY(QColor infoLight        READ getInfoLight)
    Q_PROPERTY(QColor infoLighter      READ getInfoLighter)
    Q_PROPERTY(QColor infoLightest     READ getInfoLightest)

    Q_PROPERTY(QColor errorDarkest     READ getErrorDarkest)
    Q_PROPERTY(QColor errorDarker      READ getErrorDarker)
    Q_PROPERTY(QColor errorDark        READ getErrorDark)
    Q_PROPERTY(QColor errorLight       READ getErrorLight)
    Q_PROPERTY(QColor errorLighter     READ getErrorLighter)
    Q_PROPERTY(QColor errorLightest    READ getErrorLightest)

    Q_PROPERTY(QColor successDarkest   READ getSuccessDarkest)
    Q_PROPERTY(QColor successDarker    READ getSuccessDarker)
    Q_PROPERTY(QColor successDark      READ getSuccessDark)
    Q_PROPERTY(QColor successLight     READ getSuccessLight)
    Q_PROPERTY(QColor successLighter   READ getSuccessLighter)
    Q_PROPERTY(QColor successLightest  READ getSuccessLightest)

    Q_PROPERTY(QColor miscBrown        READ getMiscBrown)
    QML_ELEMENT

public:
    static ThemeManager* get(QObject* parent = nullptr, short themeInitializer = 0);

        QColor getPrimaryDarkest();
        QColor getPrimaryDarker();
        QColor getPrimaryDark();
        QColor getPrimaryLight();
        QColor getPrimaryLighter();
        QColor getPrimaryLightest();

        QColor getTextFaded();
        QColor getTextColored();
        QColor getTextWhite();

        QColor getWarningDarkest();
        QColor getWarningDarker();
        QColor getWarningDark();
        QColor getWarningLight();
        QColor getWarningLighter();
        QColor getWarningLightest();

        QColor getAccentDarkest();
        QColor getAccentDarker();
        QColor getAccentDark();
        QColor getAccentLight();
        QColor getAccentLighter();
        QColor getAccentLightest();

        QColor getInfoDarkest();
        QColor getInfoDarker();
        QColor getInfoDark();
        QColor getInfoLight();
        QColor getInfoLighter();
        QColor getInfoLightest();

        QColor getErrorDarkest();
        QColor getErrorDarker();
        QColor getErrorDark();
        QColor getErrorLight();
        QColor getErrorLighter();
        QColor getErrorLightest();

        QColor getSuccessDarkest();
        QColor getSuccessDarker();
        QColor getSuccessDark();
        QColor getSuccessLight();
        QColor getSuccessLighter();
        QColor getSuccessLightest();

        QColor getMiscBrown();

        QColor prm_darkest;
        QColor prm_darker;
        QColor prm_dark;
        QColor prm_light;
        QColor prm_lighter;
        QColor prm_lightest;
        QColor txt_faded;
        QColor txt_colored;
        QColor txt_white;
        QColor wrn_darkest;
        QColor wrn_darker;
        QColor wrn_dark;
        QColor wrn_light;
        QColor wrn_lighter;
        QColor wrn_lightest;
        QColor acc_darkest;
        QColor acc_darker;
        QColor acc_dark;
        QColor acc_light;
        QColor acc_lighter;
        QColor acc_lightest;
        QColor inf_darkest;
        QColor inf_darker;
        QColor inf_dark;
        QColor inf_light;
        QColor inf_lighter;
        QColor inf_lightest;
        QColor err_darkest;
        QColor err_darker;
        QColor err_dark;
        QColor err_light;
        QColor err_lighter;
        QColor err_lightest;
        QColor scs_darkest;
        QColor scs_darker;
        QColor scs_dark;
        QColor scs_light;
        QColor scs_lighter;
        QColor scs_lightest;
        QColor msc_brown;

    CurrentTheme currentTheme = CurrentTheme::Swamp;

signals:

private:
    static ThemeManager* _instance;
    explicit ThemeManager(QObject *parent = nullptr, short themeInitializer = 0);

};

#endif // THEMEMANAGER_H
