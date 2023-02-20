import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import UX 1.0

ColumnLayout {
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }

    spacing: 1;
    Text {
        id: text_d_infoLabel;
        color: UX.textWhite;
        text: "ИНФОРМАЦИЯ ОБ ИЗОБРАЖЕНИИ №" + Number(index + 1);
        font.pixelSize: 14;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignTop;
        bottomPadding: 5;
        font.underline: true;
        font.bold: true;
        font.family: fontMedium.name;
    }
    Text {
        id: text_c_filename;
        color: UX.textWhite;
        text: "Имя файла: " + m_filename;
        font.pixelSize: 12;
        font.bold: true;
        font.family: fontMedium.name;
    }
    Text {
        id: text_c_creationTime;
        color: UX.textWhite;
        text: "Время съемки: " + m_datetime;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_latitude
        color: UX.textWhite;
        text: "Широта: " + m_latitude;
        font.pixelSize: 12
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_longitude;
        color: UX.textWhite;
        text: "Долгота: " + m_longitude;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true
    }
    Text {
        id: text_c_hashMatch;
        color: UX.textWhite;
        text: "Совпадение хэша: " + m_checksumMatch;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_lx;
        color: UX.textWhite;
        text: "Протяженность кадра по <i>OX</i>: " + m_lx;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_x0;
        color: UX.textWhite;
        text: "Ближняя граница: " + m_x0;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_ly;
        color: UX.textWhite;
        text: "Протяженность кадра по <i>OY</i>: " + m_ly; //
        font.pixelSize: 10
        font.family: fontMedium.name;
        font.bold: false
    }
    Text {
        id: text_c_y0;
        color: UX.textWhite;
        text: "y0 (не используется): " + m_y0; //
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_dx;
        color: UX.textWhite;
        text: "Попиксельный шаг по <i>OX</i>: " + m_dx;
        font.pixelSize: 10
        font.family: fontMedium.name;
        font.bold: false
    }
    Text {
        id: text_c_dy
        color: UX.textWhite;
        text: "Попиксельный шаг по <i>OY</i>: " + m_dy;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_angle;
        color: UX.textWhite;
        text: "Азимут: " + m_angle;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_driftAngle;
        color: UX.textWhite;
        text: "Угол сноса: " + m_driftAngle;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_div;
        color: UX.textWhite;
        text: "Ширина диаграммы направленности: " + m_azimuth;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_hash;
        color: UX.textWhite;
        text: "Хэш файла: " + m_hash;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
}
