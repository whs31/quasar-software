#ifndef QTCOLORPICKER_H
#define QTCOLORPICKER_H
#include <QPushButton>
#include <QColor>

class ColorPicker : public QPushButton
{
    Q_OBJECT
public:
    ColorPicker( QWidget* parent );

    void setColor( const QColor& color );
    const QColor& getColor() const;

public slots:
    void updateColor();
    void changeColor();

private:
    QColor color;
};
#endif
