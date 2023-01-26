#include "colorpicker.h"

#include <QColorDialog>

ColorPicker::ColorPicker( QWidget* parent )
    : QPushButton(parent)
{
    connect( this, SIGNAL(clicked()), this, SLOT(changeColor()) );
}

void ColorPicker::updateColor()
{
    setStyleSheet( "background-color: " + color.name() );
}

void ColorPicker::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if ( newColor != color )
    {
        setColor( newColor );
    }
}

void ColorPicker::setColor( const QColor& color )
{
    this->color = color;
    updateColor();
}

const QColor& ColorPicker::getColor() const
{
    return color;
}
