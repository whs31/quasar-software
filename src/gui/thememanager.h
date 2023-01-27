#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QColor>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <qqml.h>

#include "themes/dark.h"
#include "themes/swampgreen.h"
#include "misc/debug.h"

enum CurrentTheme : short
{
    SwampTheme,
    DarkTheme
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
        
    QML_ELEMENT

public:
    static ThemeManager* get(QObject* parent = nullptr, short themeInitializer = 0);
    static void setStyleSheet(void);


        QColor getPrimaryDarkest();             void setPrimaryDarkest(QColor color);
        QColor getPrimaryDarker();              void setPrimaryDarker(QColor color);
        QColor getPrimaryDark();                void setPrimaryDark(QColor color);
        QColor getPrimaryLight();               void setPrimaryLight(QColor color);
        QColor getPrimaryLighter();             void setPrimaryLighter(QColor color);
        QColor getPrimaryLightest();            void setPrimaryLightest(QColor color);
        QColor getTextFaded();                  void setTextFaded(QColor color);
        QColor getTextColored();                void setTextColored(QColor color);
        QColor getTextWhite();                  void setTextWhite(QColor color);
        QColor getWarningDarkest();             void setWarningDarkest(QColor color);
        QColor getWarningDarker();              void setWarningDarker(QColor color);
        QColor getWarningDark();                void setWarningDark(QColor color);
        QColor getWarningLight();               void setWarningLight(QColor color);
        QColor getWarningLighter();             void setWarningLighter(QColor color);          
        QColor getWarningLightest();            void setWarningLightest(QColor color);
        QColor getAccentDarkest();              void setAccentDarkest(QColor color);
        QColor getAccentDarker();               void setAccentDarker(QColor color);
        QColor getAccentDark();                 void setAccentDark(QColor color);
        QColor getAccentLight();                void setAccentLight(QColor color);
        QColor getAccentLighter();              void setAccentLighter(QColor color);
        QColor getAccentLightest();             void setAccentLightest(QColor color);
        QColor getInfoDarkest();                void setInfoDarkest(QColor color);
        QColor getInfoDarker();                 void setInfoDarker(QColor color);
        QColor getInfoDark();                   void setInfoDark(QColor color);
        QColor getInfoLight();                  void setInfoLight(QColor color);
        QColor getInfoLighter();                void setInfoLighter(QColor color);
        QColor getInfoLightest();               void setInfoLightest(QColor color);
        QColor getErrorDarkest();               void setErrorDarkest(QColor color);
        QColor getErrorDarker();                void setErrorDarker(QColor color);
        QColor getErrorDark();                  void setErrorDark(QColor color);
        QColor getErrorLight();                 void setErrorLight(QColor color);
        QColor getErrorLighter();               void setErrorLighter(QColor color);
        QColor getErrorLightest();              void setErrorLightest(QColor color);
        QColor getSuccessDarkest();             void setSuccessDarkest(QColor color);
        QColor getSuccessDarker();              void setSuccessDarker(QColor color);
        QColor getSuccessDark();                void setSuccessDark(QColor color);
        QColor getSuccessLight();               void setSuccessLight(QColor color);
        QColor getSuccessLighter();             void setSuccessLighter(QColor color);
        QColor getSuccessLightest();            void setSuccessLightest(QColor color);
        
    CurrentTheme currentTheme = CurrentTheme::SwampTheme;

signals:
        void primaryDarkestChanged();   void primaryDarkerChanged();   void primaryDarkChanged();
        void primaryLightChanged();     void primaryLighterChanged();  void primaryLightestChanged();
        void textFadedChanged();        void textColoredChanged();     void textWhiteChanged();
        void warningDarkestChanged();   void warningDarkerChanged();   void warningDarkChanged();
        void warningLightChanged();     void warningLighterChanged();  void warningLightestChanged();
        void accentDarkestChanged();    void accentDarkerChanged();    void accentDarkChanged();
        void accentLightChanged();      void accentLighterChanged();   void accentLightestChanged();
        void infoDarkestChanged();      void infoDarkerChanged();      void infoDarkChanged();
        void infoLightChanged();        void infoLighterChanged();     void infoLightestChanged();
        void errorDarkestChanged();     void errorDarkerChanged();     void errorDarkChanged();
        void errorLightChanged();       void errorLighterChanged();    void errorLightestChanged();
        void successDarkestChanged();   void successDarkerChanged();   void successDarkChanged();
        void successLightChanged();     void successLighterChanged();  void successLightestChanged();

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
        QColor msc_brown; //refactor this into array

};

#endif // THEMEMANAGER_H
