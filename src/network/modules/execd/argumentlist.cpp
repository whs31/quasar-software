#include "argumentlist.h"

ArgumentList *ArgumentList::_instance = nullptr;
ArgumentList *ArgumentList::get(QObject *parent) { if (_instance != NULL) return _instance;
    _instance = new ArgumentList(parent); return _instance; }
ArgumentList::ArgumentList(QObject *parent)
    : QObject{parent}
{
    Debug::Log("?[EXECD REMOTE] Assigned execd ARGUMENT LIST");
}

QString ArgumentList::makeFormArguments(void)
{
    QString returnString = "(";
    // это ужасно)
    if(filename->isChanged())
        returnString.append(" " + filename->key + " " + filename->getValue());
    if(mode->isChanged())
        returnString.append(" " + mode->key + " " + mode->getValue());
    if(timeshift->isChanged())
        returnString.append(" " + timeshift->key + " " + timeshift->getValue());
    if(brightness->isChanged())
        returnString.append(" " + brightness->key + " " + brightness->getValue());
    if(sealevel->isChanged())
        returnString.append(" " + sealevel->key + " " + sealevel->getValue());
    if(windowfunction->isChanged())
        returnString.append(" " + windowfunction->key + " " + windowfunction->getValue());
    if(interpolation->isChanged())
        returnString.append(" " + interpolation->key + " " + interpolation->getValue());
    if(time->isChanged())
        returnString.append(" " + time->key + " " + time->getValue());
    if(striptime->isChanged())
        returnString.append(" " + striptime->key + " " + striptime->getValue());
    if(freqinterp_x->isChanged())
        returnString.append(" " + freqinterp_x->key + " " + freqinterp_x->getValue());
    if(freqintep_y->isChanged())
        returnString.append(" " + freqintep_y->key + " " + freqintep_y->getValue());
    if(jpegcompression->isChanged())
        returnString.append(" " + jpegcompression->key + " " + jpegcompression->getValue());
    if(dx->isChanged())
        returnString.append(" " + dx->key + " " + dx->getValue());
    if(dy->isChanged())
        returnString.append(" " + dy->key + " " + dy->getValue());
    if(x0->isChanged())
        returnString.append(" " + x0->key + " " + x0->getValue());
    if(y0->isChanged())
        returnString.append(" " + y0->key + " " + y0->getValue());
    if(lx->isChanged())
        returnString.append(" " + lx->key + " " + lx->getValue());
    if(ly->isChanged())
        returnString.append(" " + ly->key + " " + ly->getValue());
    if(ip->isChanged())
        returnString.append(" " + ip->key + " " + ip->getValue());
    if(im->isChanged())
        returnString.append(" " + im->key + " " + im->getValue());
    if(tshift2->isChanged())
        returnString.append(" " + tshift2->key + " " + tshift2->getValue());
    if(remote->isChanged())
        returnString.append(" " + remote->key + " " + remote->getValue());

    returnString.append(" )");
    return returnString;
}
