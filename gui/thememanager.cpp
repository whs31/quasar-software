#include "thememanager.h"

ThemeManager *ThemeManager::_instance = nullptr;
ThemeManager *ThemeManager::get(QObject *parent, short themeInitializer)
{
    if (_instance != NULL)
        return _instance;
    _instance = new ThemeManager(parent, themeInitializer);
    return _instance;
}

ThemeManager::ThemeManager(QObject *parent, short themeInitializer) : QObject{parent}
{
    currentTheme = (CurrentTheme)themeInitializer;
    if(currentTheme == CurrentTheme::Swamp)
    {
        SwampGreen theme;
        prm_darkest         = theme.prm_darkest;
        prm_darker          = theme.prm_darker;
        prm_dark            = theme.prm_dark;
        prm_light           = theme.prm_light;
        prm_lighter         = theme.prm_lighter;
        prm_lightest        = theme.prm_lightest;

        txt_faded           = theme.txt_faded;
        txt_colored         = theme.txt_colored;
        txt_white           = theme.txt_white;
        
        wrn_darkest         = theme.wrn_darkest;
        wrn_darker          = theme.wrn_darker;
        wrn_dark            = theme.wrn_dark;
        wrn_light           = theme.wrn_light;
        wrn_lighter         = theme.wrn_lighter;
        wrn_lightest        = theme.wrn_lightest;

        acc_darkest         = theme.acc_darkest;
        acc_darker          = theme.acc_darker;
        acc_dark            = theme.acc_dark;
        acc_light           = theme.acc_light;
        acc_lighter         = theme.acc_lighter;
        acc_lightest        = theme.acc_lightest;
        
        inf_darkest         = theme.inf_darkest;
        inf_darker          = theme.inf_darker;
        inf_dark            = theme.inf_dark;
        inf_light           = theme.inf_light;
        inf_lighter         = theme.inf_lighter;
        inf_lightest        = theme.inf_lightest;

        err_darkest         = theme.err_darkest;
        err_darker          = theme.err_darker;
        err_dark            = theme.err_dark;
        err_light           = theme.err_light;
        err_lighter         = theme.err_lighter;
        err_lightest        = theme.err_lightest;

        scs_darkest         = theme.scs_darkest;
        scs_darker          = theme.scs_darker;
        scs_dark            = theme.scs_dark;
        scs_light           = theme.scs_light;
        scs_lighter         = theme.scs_lighter;
        scs_lightest        = theme.scs_lightest;

        msc_brown           = theme.msc_brown;
    }
}

QColor ThemeManager::getPrimaryDarkest(){return prm_darkest;}void ThemeManager::setPrimaryDarkest(QColor color){if(color==prm_darkest)return;prm_darkest=color;
emit primaryDarkestChanged();}QColor ThemeManager::getPrimaryDarker(){return prm_darker;}void ThemeManager::setPrimaryDarker(QColor color){if(color==prm_darker)
return;prm_darker=color;emit primaryDarkerChanged();}QColor ThemeManager::getPrimaryDark(){return prm_dark;}void ThemeManager::setPrimaryDark(QColor color){if 
(color==prm_dark)return;prm_dark=color;emit primaryDarkChanged();}QColor ThemeManager::getPrimaryLight(){return prm_light;}void ThemeManager::setPrimaryLight
(QColor color){if(color==prm_light)return;prm_light=color;emit primaryLightChanged();}QColor ThemeManager::getPrimaryLighter(){return prm_lighter;}void 
ThemeManager::setPrimaryLighter(QColor color){if(color==prm_lighter)return;prm_lighter=color;emit primaryLighterChanged();}QColor ThemeManager::getPrimaryLightest()
{return prm_lightest;}void ThemeManager::setPrimaryLightest(QColor color){if(color==prm_lightest)return;prm_lightest=color;emit primaryLightestChanged();}QColor 
ThemeManager::getTextFaded(){return txt_faded;}void ThemeManager::setTextFaded(QColor color){if(color==txt_faded)return;txt_faded=color;emit textFadedChanged();}
QColor ThemeManager::getTextColored(){return txt_colored;}void ThemeManager::setTextColored(QColor color){if(color==txt_colored)return;txt_colored=color;emit 
textColoredChanged();}QColor ThemeManager::getTextWhite(){return txt_white;}void ThemeManager::setTextWhite(QColor color){if(color==txt_white)return;txt_white=color;
emit textWhiteChanged();}QColor ThemeManager::getWarningDarkest(){return wrn_darkest;}void ThemeManager::setWarningDarkest(QColor color){if(color==prm_darker)return;
prm_darker=color;emit warningDarkestChanged();}QColor ThemeManager::getWarningDarker(){return wrn_darker;}void ThemeManager::setWarningDarker(QColor color){if
(color==prm_darker)return;prm_darker=color;emit warningDarkerChanged();}QColor ThemeManager::getWarningDark(){return wrn_dark;}void ThemeManager::setWarningDark(
QColor color){if(color==prm_darker)return;prm_darker=color;emit warningDarkChanged();}QColor ThemeManager::getWarningLight(){return wrn_light;}void ThemeManager::
setWarningLight(QColor color){if(color==prm_darker)return;prm_darker=color;emit warningLightChanged();}QColor ThemeManager::getWarningLighter(){return wrn_lighter;}
void ThemeManager::setWarningLighter(QColor color){if(color==prm_darker)return;prm_darker=color;emit warningLighterChanged();}QColor ThemeManager::getWarningLightest()
{return wrn_lightest;}void ThemeManager::setWarningLightest(QColor color){if(color==prm_darker)return;prm_darker=color;emit warningLightestChanged();}QColor 
ThemeManager::getAccentDarkest(){return acc_darkest;}void ThemeManager::setAccentDarkest(QColor color){if(color==prm_darker)return;prm_darker=color;emit 
accentDarkestChanged();}QColor ThemeManager::getAccentDarker(){return acc_darker;}void ThemeManager::setAccentDarker(QColor color){if(color==prm_darker)return;
prm_darker=color;emit accentDarkerChanged();}QColor ThemeManager::getAccentDark(){return acc_dark;}void ThemeManager::setAccentDark(QColor color){if(color==prm_darker)
return;prm_darker=color;emit accentDarkChanged();}QColor ThemeManager::getAccentLight(){return acc_light;}void ThemeManager::setAccentLight(QColor color){if(color==
prm_darker)return;prm_darker=color;emit accentLightChanged();}QColor ThemeManager::getAccentLighter(){return acc_lighter;}void ThemeManager::setAccentLighter(QColor 
color){if(color==prm_darker)return;prm_darker=color;emit accentLighterChanged();}QColor ThemeManager::getAccentLightest(){return acc_lightest;}void ThemeManager::
setAccentLightest(QColor color){if(color==prm_darker)return;prm_darker=color;emit accentLightestChanged();}QColor ThemeManager::getInfoDarkest(){return inf_darkest;}
void ThemeManager::setInfoDarkest(QColor color){if(color==prm_darker)return;prm_darker=color;emit infoDarkestChanged();}QColor ThemeManager::getInfoDarker(){return 
inf_darker;}void ThemeManager::setInfoDarker(QColor color){if(color==prm_darker)return;prm_darker=color;emit infoDarkerChanged();}QColor ThemeManager::getInfoDark()
{return inf_dark;}void ThemeManager::setInfoDark(QColor color){if(color==prm_darker)return;prm_darker=color;emit infoDarkChanged();}QColor ThemeManager::getInfoLight()
{return inf_light;}void ThemeManager::setInfoLight(QColor color){if(color==prm_darker)return;prm_darker=color;emit infoLightChanged();}QColor ThemeManager::
getInfoLighter(){return inf_lighter; } void ThemeManager::setInfoLighter(QColor color){if(color==prm_darker)return;prm_darker=color;emit infoLighterChanged();}QColor 
ThemeManager::getInfoLightest(){return inf_lightest; } void ThemeManager::setInfoLightest(QColor color){if(color==prm_darker)return;prm_darker=color;emit 
infoLightestChanged();}QColor ThemeManager::getErrorDarkest(){return err_darkest;}void ThemeManager::setErrorDarkest(QColor color){if(color==prm_darker)return;
prm_darker=color;emit errorDarkestChanged();}QColor ThemeManager::getErrorDarker(){return err_darker;}void ThemeManager::setErrorDarker(QColor color){if(color==
prm_darker)return;prm_darker=color;emit errorDarkerChanged();}QColor ThemeManager::getErrorDark(){return err_dark;}void ThemeManager::setErrorDark(QColor color){if(
color==prm_darker)return;prm_darker=color;emit errorDarkChanged();}QColor ThemeManager::getErrorLight(){return err_light;}void ThemeManager::setErrorLight(QColor color)
{if(color==prm_darker)return;prm_darker=color;emit errorLightChanged();}QColor ThemeManager::getErrorLighter(){return err_lighter;}void ThemeManager::setErrorLighter(
QColor color){if(color==prm_darker)return;prm_darker=color;emit errorLighterChanged();}QColor ThemeManager::getErrorLightest(){return err_lightest;}void ThemeManager::
setErrorLightest(QColor color){if(color==prm_darker)return;prm_darker=color;emit errorLightestChanged();}QColor ThemeManager::getSuccessDarkest(){return scs_darkest;} 
void ThemeManager::setSuccessDarkest(QColor color){if(color==prm_darker)return;prm_darker=color;emit successDarkestChanged();}QColor ThemeManager::getSuccessDarker()
{return scs_darker;}void ThemeManager::setSuccessDarker(QColor color){if(color==prm_darker)return;prm_darker=color;emit successDarkerChanged();}QColor ThemeManager::
getSuccessDark(){return scs_dark;}void ThemeManager::setSuccessDark(QColor color){if(color==prm_darker)return;prm_darker=color;emit successDarkChanged();}QColor 
ThemeManager::getSuccessLight(){return scs_light;}void ThemeManager::setSuccessLight(QColor color){if(color==prm_darker)return;prm_darker=color;emit successLightChanged
();}QColor ThemeManager::getSuccessLighter(){return scs_lighter;}void ThemeManager::setSuccessLighter(QColor color){if(color==prm_darker)return;prm_darker=color;emit 
successLighterChanged();}QColor ThemeManager::getSuccessLightest(){return scs_lightest;}void ThemeManager::setSuccessLightest(QColor color){if(color==prm_darker)return;
prm_darker=color;emit successLightestChanged();}QColor ThemeManager::getMiscBrown(){return msc_brown;}void ThemeManager::setMiscBrown(QColor color){if(color==msc_brown)
return;msc_brown=color;emit miscBrownChanged();}