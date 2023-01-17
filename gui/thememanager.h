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
    Q_PROPERTY(QColor primaryDarkest   READ getPrimaryDarkest       WRITE setPrimaryDarkest         NOTIFY primaryDarkestChanged) 
    Q_PROPERTY(QColor primaryDarker    READ getPrimaryDarker        WRITE setPrimaryDarker          NOTIFY primaryDarkerChanged)
    Q_PROPERTY(QColor primaryDark      READ getPrimaryDark          WRITE setPrimaryDark            NOTIFY primaryDarkChanged)
    Q_PROPERTY(QColor primaryLight     READ getPrimaryLight         WRITE setPrimaryLight           NOTIFY primaryLightChanged)
    Q_PROPERTY(QColor primaryLighter   READ getPrimaryLighter       WRITE setPrimaryLighter         NOTIFY primaryLighterChanged)
    Q_PROPERTY(QColor primaryLightest  READ getPrimaryLightest      WRITE setPrimaryLightest        NOTIFY primaryLightestChanged)
    
    Q_PROPERTY(QColor textFaded        READ getTextFaded            WRITE setTextFaded              NOTIFY textFadedChanged)
    Q_PROPERTY(QColor textColored      READ getTextColored          WRITE setTextColored            NOTIFY textColoredChanged)
    Q_PROPERTY(QColor textWhite        READ getTextWhite            WRITE setTextWhite              NOTIFY textWhiteChanged)

    Q_PROPERTY(QColor warningDarkest   READ getWarningDarkest       WRITE setWarningDarkest         NOTIFY warningDarkestChanged)
    Q_PROPERTY(QColor warningDarker    READ getWarningDarker        WRITE setWarningDarker          NOTIFY warningDarkerChanged)
    Q_PROPERTY(QColor warningDark      READ getWarningDark          WRITE setWarningDark            NOTIFY warningDarkChanged)
    Q_PROPERTY(QColor warningLight     READ getWarningLight         WRITE setWarningLight           NOTIFY warningLightChanged)
    Q_PROPERTY(QColor warningLighter   READ getWarningLighter       WRITE setWarningLighter         NOTIFY warningLighterChanged)
    Q_PROPERTY(QColor warningLightest  READ getWarningLightest      WRITE setWarningLightest        NOTIFY warningLightestChanged)
        
    Q_PROPERTY(QColor accentDarkest    READ getAccentDarkest        WRITE setAccentDarkest          NOTIFY accentDarkestChanged)
    Q_PROPERTY(QColor accentDarker     READ getAccentDarker         WRITE setAccentDarker           NOTIFY accentDarkerChanged)
    Q_PROPERTY(QColor accentDark       READ getAccentDark           WRITE setAccentDark             NOTIFY accentDarkChanged)
    Q_PROPERTY(QColor accentLight      READ getAccentLight          WRITE setAccentLight            NOTIFY accentLightChanged)
    Q_PROPERTY(QColor accentLighter    READ getAccentLighter        WRITE setAccentLighter          NOTIFY accentLighterChanged)
    Q_PROPERTY(QColor accentLightest   READ getAccentLightest       WRITE setAccentLightest         NOTIFY accentLightestChanged)
    
    Q_PROPERTY(QColor infoDarkest      READ getInfoDarkest          WRITE setInfoDarkest            NOTIFY infoDarkestChanged)
    Q_PROPERTY(QColor infoDarker       READ getInfoDarker           WRITE setInfoDarker             NOTIFY infoDarkerChanged)
    Q_PROPERTY(QColor infoDark         READ getInfoDark             WRITE setInfoDark               NOTIFY infoDarkChanged)
    Q_PROPERTY(QColor infoLight        READ getInfoLight            WRITE setInfoLight              NOTIFY infoLightChanged)
    Q_PROPERTY(QColor infoLighter      READ getInfoLighter          WRITE setInfoLighter            NOTIFY infoLighterChanged)
    Q_PROPERTY(QColor infoLightest     READ getInfoLightest         WRITE setInfoLightest           NOTIFY infoLightestChanged)
    
    Q_PROPERTY(QColor errorDarkest     READ getErrorDarkest         WRITE setErrorDarkest           NOTIFY errorDarkestChanged)
    Q_PROPERTY(QColor errorDarker      READ getErrorDarker          WRITE setErrorDarker            NOTIFY errorDarkerChanged)
    Q_PROPERTY(QColor errorDark        READ getErrorDark            WRITE setErrorDark              NOTIFY errorDarkChanged)
    Q_PROPERTY(QColor errorLight       READ getErrorLight           WRITE setErrorLight             NOTIFY errorLightChanged)
    Q_PROPERTY(QColor errorLighter     READ getErrorLighter         WRITE setErrorLighter           NOTIFY errorLighterChanged)
    Q_PROPERTY(QColor errorLightest    READ getErrorLightest        WRITE setErrorLightest          NOTIFY errorLightestChanged)
        
    Q_PROPERTY(QColor successDarkest   READ getSuccessDarkest       WRITE setSuccessDarkest         NOTIFY successDarkestChanged)
    Q_PROPERTY(QColor successDarker    READ getSuccessDarker        WRITE setSuccessDarker          NOTIFY successDarkerChanged)
    Q_PROPERTY(QColor successDark      READ getSuccessDark          WRITE setSuccessDark            NOTIFY successDarkChanged)
    Q_PROPERTY(QColor successLight     READ getSuccessLight         WRITE setSuccessLight           NOTIFY successLightChanged)
    Q_PROPERTY(QColor successLighter   READ getSuccessLighter       WRITE setSuccessLighter         NOTIFY successLighterChanged)
    Q_PROPERTY(QColor successLightest  READ getSuccessLightest      WRITE setSuccessLightest        NOTIFY successLightestChanged)
        
    Q_PROPERTY(QColor miscBrown        READ getMiscBrown            WRITE setMiscBrown              NOTIFY miscBrownChanged)
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



        void setPrimaryDarkest(QColor color);
        void setPrimaryDarker(QColor color);
        void setPrimaryDark(QColor color);
        void setPrimaryLight(QColor color);
        void setPrimaryLighter(QColor color);
        void setPrimaryLightest(QColor color);
        void setTextFaded(QColor color);
        void setTextColored(QColor color);
        void setTextWhite(QColor color);
        void setWarningDarkest(QColor color);
        void setWarningDarker(QColor color);
        void setWarningDark(QColor color);
        void setWarningLight(QColor color);
        void setWarningLighter(QColor color);
        void setWarningLightest(QColor color);
        void setAccentDarkest(QColor color);
        void setAccentDarker(QColor color);
        void setAccentDark(QColor color);
        void setAccentLight(QColor color);
        void setAccentLighter(QColor color);
        void setAccentLightest(QColor color);
        void setInfoDarkest(QColor color);
        void setInfoDarker(QColor color);
        void setInfoDark(QColor color);
        void setInfoLight(QColor color);
        void setInfoLighter(QColor color);
        void setInfoLightest(QColor color);
        void setErrorDarkest(QColor color);
        void setErrorDarker(QColor color);
        void setErrorDark(QColor color);
        void setErrorLight(QColor color);
        void setErrorLighter(QColor color);
        void setErrorLightest(QColor color);
        void setSuccessDarkest(QColor color);
        void setSuccessDarker(QColor color);
        void setSuccessDark(QColor color);
        void setSuccessLight(QColor color);
        void setSuccessLighter(QColor color);
        void setSuccessLightest(QColor color);
        void setMiscBrown(QColor color);

    CurrentTheme currentTheme = CurrentTheme::Swamp;

signals:
        void primaryDarkestChanged();
        void primaryDarkerChanged();
        void primaryDarkChanged();
        void primaryLightChanged();
        void primaryLighterChanged();
        void primaryLightestChanged();
        void textFadedChanged();
        void textColoredChanged();
        void textWhiteChanged();
        void warningDarkestChanged();
        void warningDarkerChanged();
        void warningDarkChanged();
        void warningLightChanged();
        void warningLighterChanged();
        void warningLightestChanged();
        void accentDarkestChanged();
        void accentDarkerChanged();
        void accentDarkChanged();
        void accentLightChanged();
        void accentLighterChanged();
        void accentLightestChanged();
        void infoDarkestChanged();
        void infoDarkerChanged();
        void infoDarkChanged();
        void infoLightChanged();
        void infoLighterChanged();
        void infoLightestChanged();
        void errorDarkestChanged();
        void errorDarkerChanged();
        void errorDarkChanged();
        void errorLightChanged();
        void errorLighterChanged();
        void errorLightestChanged();
        void successDarkestChanged();
        void successDarkerChanged();
        void successDarkChanged();
        void successLightChanged();
        void successLighterChanged();
        void successLightestChanged();
        void miscBrownChanged();



private:
    static ThemeManager* _instance;
    explicit ThemeManager(QObject *parent = nullptr, short themeInitializer = 0);

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

};

#endif // THEMEMANAGER_H
