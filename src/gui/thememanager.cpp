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
    SwampGreen theme_s;
    Dark theme_d;
    if (currentTheme == CurrentTheme::SwampTheme)
    {
        prm_darkest = theme_s.prm_darkest;
        prm_darker = theme_s.prm_darker;
        prm_dark = theme_s.prm_dark;
        prm_light = theme_s.prm_light;
        prm_lighter = theme_s.prm_lighter;
        prm_lightest = theme_s.prm_lightest;
        txt_faded = theme_s.txt_faded;
        txt_colored = theme_s.txt_colored;
        txt_white = theme_s.txt_white;
        wrn_darkest = theme_s.wrn_darkest;
        wrn_darker = theme_s.wrn_darker;
        wrn_dark = theme_s.wrn_dark;
        wrn_light = theme_s.wrn_light;
        wrn_lighter = theme_s.wrn_lighter;
        wrn_lightest = theme_s.wrn_lightest;
        acc_darkest = theme_s.acc_darkest;
        acc_darker = theme_s.acc_darker;
        acc_dark = theme_s.acc_dark;
        acc_light = theme_s.acc_light;
        acc_lighter = theme_s.acc_lighter;
        acc_lightest = theme_s.acc_lightest;
        inf_darkest = theme_s.inf_darkest;
        inf_darker = theme_s.inf_darker;
        inf_dark = theme_s.inf_dark;
        inf_light = theme_s.inf_light;
        inf_lighter = theme_s.inf_lighter;
        inf_lightest = theme_s.inf_lightest;
        err_darkest = theme_s.err_darkest;
        err_darker = theme_s.err_darker;
        err_dark = theme_s.err_dark;
        err_light = theme_s.err_light;
        err_lighter = theme_s.err_lighter;
        err_lightest = theme_s.err_lightest;
        scs_darkest = theme_s.scs_darkest;
        scs_darker = theme_s.scs_darker;
        scs_dark = theme_s.scs_dark;
        scs_light = theme_s.scs_light;
        scs_lighter = theme_s.scs_lighter;
        scs_lightest = theme_s.scs_lightest;
    }
    else if (currentTheme == CurrentTheme::DarkTheme)
    {
        prm_darkest = theme_d.prm_darkest;
        prm_darker = theme_d.prm_darker;
        prm_dark = theme_d.prm_dark;
        prm_light = theme_d.prm_light;
        prm_lighter = theme_d.prm_lighter;
        prm_lightest = theme_d.prm_lightest;
        txt_faded = theme_d.txt_faded;
        txt_colored = theme_d.txt_colored;
        txt_white = theme_d.txt_white;
        wrn_darkest = theme_d.wrn_darkest;
        wrn_darker = theme_d.wrn_darker;
        wrn_dark = theme_d.wrn_dark;
        wrn_light = theme_d.wrn_light;
        wrn_lighter = theme_d.wrn_lighter;
        wrn_lightest = theme_d.wrn_lightest;
        acc_darkest = theme_d.acc_darkest;
        acc_darker = theme_d.acc_darker;
        acc_dark = theme_d.acc_dark;
        acc_light = theme_d.acc_light;
        acc_lighter = theme_d.acc_lighter;
        acc_lightest = theme_d.acc_lightest;
        inf_darkest = theme_d.inf_darkest;
        inf_darker = theme_d.inf_darker;
        inf_dark = theme_d.inf_dark;
        inf_light = theme_d.inf_light;
        inf_lighter = theme_d.inf_lighter;
        inf_lightest = theme_d.inf_lightest;
        err_darkest = theme_d.err_darkest;
        err_darker = theme_d.err_darker;
        err_dark = theme_d.err_dark;
        err_light = theme_d.err_light;
        err_lighter = theme_d.err_lighter;
        err_lightest = theme_d.err_lightest;
        scs_darkest = theme_d.scs_darkest;
        scs_darker = theme_d.scs_darker;
        scs_dark = theme_d.scs_dark;
        scs_light = theme_d.scs_light;
        scs_lighter = theme_d.scs_lighter;
        scs_lightest = theme_d.scs_lightest;
    }
}

void ThemeManager::setStyleSheet(void)
{
    QFile qss(":/stylesheet/lightstyle.qss");
    if (!qss.exists())
    {
        Debug::Log("!![QSS] Unable to set test stylesheet, file not found\n");
    }
    else
    {
        qss.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qss);
        qApp->setStyleSheet(ts.readAll());
    }
}

QColor ThemeManager::getPrimaryDarkest() { return prm_darkest; }
void ThemeManager::setPrimaryDarkest(QColor color)
{
    if (color == prm_darkest)
        return;
    prm_darkest = color;
    emit primaryDarkestChanged();
}
QColor ThemeManager::getPrimaryDarker() { return prm_darker; }
void ThemeManager::setPrimaryDarker(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit primaryDarkerChanged();
}
QColor ThemeManager::getPrimaryDark() { return prm_dark; }
void ThemeManager::setPrimaryDark(QColor color)
{
    if (color == prm_dark)
        return;
    prm_dark = color;
    emit primaryDarkChanged();
}
QColor ThemeManager::getPrimaryLight() { return prm_light; }
void ThemeManager::setPrimaryLight(QColor color)
{
    if (color == prm_light)
        return;
    prm_light = color;
    emit primaryLightChanged();
}
QColor ThemeManager::getPrimaryLighter() { return prm_lighter; }
void ThemeManager::setPrimaryLighter(QColor color)
{
    if (color == prm_lighter)
        return;
    prm_lighter = color;
    emit primaryLighterChanged();
}
QColor ThemeManager::getPrimaryLightest()
{
    return prm_lightest;
}
void ThemeManager::setPrimaryLightest(QColor color)
{
    if (color == prm_lightest)
        return;
    prm_lightest = color;
    emit primaryLightestChanged();
}
QColor
ThemeManager::getTextFaded() { return txt_faded; }
void ThemeManager::setTextFaded(QColor color)
{
    if (color == txt_faded)
        return;
    txt_faded = color;
    emit textFadedChanged();
}
QColor ThemeManager::getTextColored() { return txt_colored; }
void ThemeManager::setTextColored(QColor color)
{
    if (color == txt_colored)
        return;
    txt_colored = color;
    emit
    textColoredChanged();
}
QColor ThemeManager::getTextWhite() { return txt_white; }
void ThemeManager::setTextWhite(QColor color)
{
    if (color == txt_white)
        return;
    txt_white = color;
    emit textWhiteChanged();
}
QColor ThemeManager::getWarningDarkest() { return wrn_darkest; }
void ThemeManager::setWarningDarkest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningDarkestChanged();
}
QColor ThemeManager::getWarningDarker() { return wrn_darker; }
void ThemeManager::setWarningDarker(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningDarkerChanged();
}
QColor ThemeManager::getWarningDark() { return wrn_dark; }
void ThemeManager::setWarningDark(
    QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningDarkChanged();
}
QColor ThemeManager::getWarningLight() { return wrn_light; }
void ThemeManager::
    setWarningLight(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningLightChanged();
}
QColor ThemeManager::getWarningLighter() { return wrn_lighter; }
void ThemeManager::setWarningLighter(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningLighterChanged();
}
QColor ThemeManager::getWarningLightest()
{
    return wrn_lightest;
}
void ThemeManager::setWarningLightest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit warningLightestChanged();
}
QColor
ThemeManager::getAccentDarkest() { return acc_darkest; }
void ThemeManager::setAccentDarkest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit
    accentDarkestChanged();
}
QColor ThemeManager::getAccentDarker() { return acc_darker; }
void ThemeManager::setAccentDarker(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit accentDarkerChanged();
}
QColor ThemeManager::getAccentDark() { return acc_dark; }
void ThemeManager::setAccentDark(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit accentDarkChanged();
}
QColor ThemeManager::getAccentLight() { return acc_light; }
void ThemeManager::setAccentLight(QColor color)
{
    if (color ==
        prm_darker)
        return;
    prm_darker = color;
    emit accentLightChanged();
}
QColor ThemeManager::getAccentLighter() { return acc_lighter; }
void ThemeManager::setAccentLighter(QColor
                                        color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit accentLighterChanged();
}
QColor ThemeManager::getAccentLightest() { return acc_lightest; }
void ThemeManager::
    setAccentLightest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit accentLightestChanged();
}
QColor ThemeManager::getInfoDarkest() { return inf_darkest; }
void ThemeManager::setInfoDarkest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit infoDarkestChanged();
}
QColor ThemeManager::getInfoDarker() { return inf_darker; }
void ThemeManager::setInfoDarker(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit infoDarkerChanged();
}
QColor ThemeManager::getInfoDark()
{
    return inf_dark;
}
void ThemeManager::setInfoDark(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit infoDarkChanged();
}
QColor ThemeManager::getInfoLight()
{
    return inf_light;
}
void ThemeManager::setInfoLight(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit infoLightChanged();
}
QColor ThemeManager::
    getInfoLighter() { return inf_lighter; }
void ThemeManager::setInfoLighter(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit infoLighterChanged();
}
QColor
ThemeManager::getInfoLightest() { return inf_lightest; }
void ThemeManager::setInfoLightest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit
    infoLightestChanged();
}
QColor ThemeManager::getErrorDarkest() { return err_darkest; }
void ThemeManager::setErrorDarkest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit errorDarkestChanged();
}
QColor ThemeManager::getErrorDarker() { return err_darker; }
void ThemeManager::setErrorDarker(QColor color)
{
    if (color ==
        prm_darker)
        return;
    prm_darker = color;
    emit errorDarkerChanged();
}
QColor ThemeManager::getErrorDark() { return err_dark; }
void ThemeManager::setErrorDark(QColor color)
{
    if (
        color == prm_darker)
        return;
    prm_darker = color;
    emit errorDarkChanged();
}
QColor ThemeManager::getErrorLight() { return err_light; }
void ThemeManager::setErrorLight(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit errorLightChanged();
}
QColor ThemeManager::getErrorLighter() { return err_lighter; }
void ThemeManager::setErrorLighter(
    QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit errorLighterChanged();
}
QColor ThemeManager::getErrorLightest() { return err_lightest; }
void ThemeManager::
    setErrorLightest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit errorLightestChanged();
}
QColor ThemeManager::getSuccessDarkest() { return scs_darkest; }
void ThemeManager::setSuccessDarkest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successDarkestChanged();
}
QColor ThemeManager::getSuccessDarker()
{
    return scs_darker;
}
void ThemeManager::setSuccessDarker(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successDarkerChanged();
}
QColor ThemeManager::
    getSuccessDark() { return scs_dark; }
void ThemeManager::setSuccessDark(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successDarkChanged();
}
QColor
ThemeManager::getSuccessLight() { return scs_light; }
void ThemeManager::setSuccessLight(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successLightChanged();
}
QColor ThemeManager::getSuccessLighter() { return scs_lighter; }
void ThemeManager::setSuccessLighter(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successLighterChanged();
}
QColor ThemeManager::getSuccessLightest() { return scs_lightest; }
void ThemeManager::setSuccessLightest(QColor color)
{
    if (color == prm_darker)
        return;
    prm_darker = color;
    emit successLightestChanged();
}
