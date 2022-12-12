#include "smath.h"

SMath::SMath(QObject *parent)
    : QObject{parent}
{

}

qreal SMath::degreesToKilometers(qreal degrees)          { return ( degrees * 111.111 );         }
qreal SMath::degreesToMeters(qreal degrees)              { return ( degrees * 111.111 * 1000 );  }
qreal SMath::metersToDegrees(qreal meters)               { return ( meters / (111.111 * 1000) ); }
qreal SMath::mercatorZoomLevel(qreal dx, qreal latitude) { if(dx == 0) { return log(2, 156543.03392 * qCos(latitude * M_PI / 180)); } return log(2, 156543.03392 * qCos(latitude * M_PI / 180) / dx); }
qreal SMath::log(qreal base, qreal exponent)             { return ( qLn(exponent) / qLn(base) );      }
qreal SMath::degreesToRadians(qreal degrees)             { return ( qDegreesToRadians(degrees) );     }
qreal SMath::radiansToDegrees(qreal radians)             { return ( qRadiansToDegrees(radians) );     }
