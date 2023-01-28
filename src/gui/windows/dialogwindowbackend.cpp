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
    : WindowBackend{parent}
{}

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
