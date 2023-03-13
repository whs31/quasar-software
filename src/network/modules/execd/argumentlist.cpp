#include "argumentlist.h"
#include "config/sconfig.h"
#include <QDebug>

ArgumentList *ArgumentList::_instance = nullptr;
ArgumentList *ArgumentList::get(QObject *parent) { if (_instance != NULL) return _instance;
    _instance = new ArgumentList(parent); return _instance; }
ArgumentList::ArgumentList(QObject *parent)
    : QObject{parent}
{
    qInfo() << "[ARGUMENTLIST] Assigned execd ARGUMENT LIST";

    args.append(filename);
    args.append(mode);
    args.append(timeshift);
    args.append(brightness);
    args.append(sealevel);
    args.append(elevation);
    args.append(velocity);
    args.append(windowfunction);
    args.append(interpolation);
    args.append(time);
    args.append(striptime);
    args.append(freqinterp_x);
    args.append(freqinterp_y);
    args.append(jpegcompression);
    args.append(dx);
    args.append(dy);
    args.append(lx);
    args.append(ly);
    args.append(x0);
    args.append(y0);
    args.append(ip);
    args.append(im);
    args.append(tshift2);
    args.append(remote);
    args.append(timedur);

    focus_args.append(filename);
    focus_args.append(velocity);
    focus_args.append(focus_time);
    focus_args.append(rect_x);
    focus_args.append(rect_y);
    focus_args.append(rect_edge);
    focus_args.append(focus_vel_max);
    focus_args.append(focus_vel_min);
    focus_args.append(drift_angle);
    focus_args.append(focus_img_cnt);
}

QString ArgumentList::makeFormArguments(void)
{
    QString returnString = "(";
    bool noSpaceFlag = false;
    for(size_t arg = 0; arg < args.length(); arg++)
    {
        if(args[arg]->isChanged() && !noSpaceFlag)
        {
            returnString.append(args[arg]->key + " " + args[arg]->getValue());
            noSpaceFlag = true;
            continue;
        }
        if(args[arg]->isChanged())
            returnString.append(" " + args[arg]->key + " " + args[arg]->getValue());
    }
    returnString.append(")");
    return returnString;
}

QString ArgumentList::makeFocusArguments(void)
{
    QString returnString = "(";
    bool noSpaceFlag = false;
    for(size_t arg = 0; arg < focus_args.length(); arg++)
    {
        if(focus_args[arg]->isChanged() and not noSpaceFlag)
        {
            returnString.append(focus_args[arg]->key + " " + focus_args[arg]->getValue());
            noSpaceFlag = true;
            continue;
        }
        if(focus_args[arg]->isChanged())
            returnString.append(" " + focus_args[arg]->key + " " + focus_args[arg]->getValue());
    }
    //QString remoteAddress = " --remote " + SConfig::get()->getComputerIP() + ":" + SConfig::get()->getLoaderPort();
    //returnString.append(remoteAddress);
    //qWarning() << "[ARGUMENT] Assigned remote: " << remoteAddress;
    returnString.append(")");
    return returnString;
}
