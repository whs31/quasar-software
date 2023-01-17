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
        prm_darkest = theme.prm_darkest;
        prm_darker = theme.prm_darker;
        prm_dark = theme.prm_dark;
        prm_light = theme.prm_light;
        prm_lighter = theme.prm_lighter;
        prm_lightest = theme.prm_lightest;

        txt_faded = theme.txt_faded;
        txt_colored = theme.txt_colored;
        txt_white = theme.txt_white;
        
        wrn_darkest = theme.wrn_darkest;
        wrn_darker = theme.wrn_darker;
        wrn_dark = theme.wrn_dark;
        wrn_light = theme.wrn_light;
        wrn_lighter = theme.wrn_lighter;
        wrn_lightest = theme.wrn_lightest;

        acc_darkest = theme.acc_darkest;
        acc_darker = theme.acc_darker;
        acc_dark = theme.acc_dark;
        acc_light = theme.acc_light;
        acc_lighter = theme.acc_lighter;
        acc_lightest = theme.acc_lightest;
        
        inf_darkest = theme.inf_darkest;
        inf_darker = theme.inf_darker;
        inf_dark = theme.inf_dark;
        inf_light = theme.inf_light;
        inf_lighter = theme.inf_lighter;
        inf_lightest = theme.inf_lightest;

        err_darkest = theme.err_darkest;
        err_darker = theme.err_darker;
        err_dark = theme.err_dark;
        err_light = theme.err_light;
        err_lighter = theme.err_lighter;
        err_lightest = theme.err_lightest;

        scs_darkest = theme.scs_darkest;
        scs_darker = theme.scs_darker;
        scs_dark = theme.scs_dark;
        scs_light = theme.scs_light;
        scs_lighter = theme.scs_lighter;
        scs_lightest = theme.scs_lightest;

        msc_brown = theme.msc_brown;
    }
}
