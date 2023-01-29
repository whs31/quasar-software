#include "argumentlist.h"

ArgumentList *ArgumentList::_instance = nullptr;
ArgumentList *ArgumentList::get(QObject *parent) { if (_instance != NULL) return _instance;
    _instance = new ArgumentList(parent); return _instance; }
ArgumentList::ArgumentList(QObject *parent)
    : QObject{parent}
{
    Debug::Log("?[EXECD REMOTE] Assigned execd ARGUMENT LIST");
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
    args.append(freqintep_y);
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
