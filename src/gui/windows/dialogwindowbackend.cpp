#include "dialogwindowbackend.h"

DialogWindowBackend* DialogWindowBackend::pointer = nullptr;
DialogWindowBackend* DialogWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new DialogWindowBackend(parent);
    return pointer;
}
DialogWindowBackend::DialogWindowBackend(QObject *parent)
    : QObject{parent}
{

}

void DialogWindowBackend::show(void)
{
     setReturnCode(0);
     setShown(true);
}

QString DialogWindowBackend::getHeader() const { return m_header; }
void DialogWindowBackend::setHeader(const QString &newHeader)
{
    if (m_header == newHeader) return;
    m_header = newHeader;
    emit headerChanged();
}
QString DialogWindowBackend::getIcon() const { return m_icon; }
void DialogWindowBackend::setIcon(const QString &newIcon)
{
    if (m_icon == newIcon) return;
    m_icon = newIcon;
    emit iconChanged();
}
QString DialogWindowBackend::getText() const { return m_text; }
void DialogWindowBackend::setText(const QString &newText)
{
    if (m_text == newText) return;
    m_text = newText;
    emit textChanged();
}
bool DialogWindowBackend::getShown() const { return m_shown; }
void DialogWindowBackend::setShown(bool newShown)
{
    if (m_shown == newShown) return;
    m_shown = newShown;
    emit shownChanged();
}
int DialogWindowBackend::getReturnCode() const { return m_returnCode; }
void DialogWindowBackend::setReturnCode(int newReturnCode)
{
    if (m_returnCode == newReturnCode) return;
    m_returnCode = newReturnCode;
    emit returnCodeChanged();
}
