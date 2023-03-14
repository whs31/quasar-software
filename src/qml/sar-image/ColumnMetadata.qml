import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15
import Theme 1.0

ColumnLayout {
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }

    spacing: 1;
    Text {
        id: text_d_infoLabel;
        color: Theme.color("light1");
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
        color: Theme.color("light1");
        text: "Имя файла: " + m_filename;
        font.pixelSize: 12;
        font.bold: true;
        font.family: fontMedium.name;
    }
    Text {
        id: text_c_creationTime;
        color: Theme.color("light1");
        text: "Время съемки: " + m_datetime;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_latitude
        color: Theme.color("light1");
        text: "Широта: " + m_latitude;
        font.pixelSize: 12
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_longitude;
        color: Theme.color("light1");
        text: "Долгота: " + m_longitude;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true
    }
    Text {
        id: text_c_hashMatch;
        color: Theme.color("light1");
        text: "Совпадение хэша: " + m_checksumMatch;
        font.pixelSize: 12;
        font.family: fontMedium.name;
        font.bold: true;
    }
    Text {
        id: text_c_lx;
        color: Theme.color("light1");
        text: "Протяженность кадра по <i>OX</i>: " + m_lx;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_x0;
        color: Theme.color("light1");
        text: "Ближняя граница: " + m_x0;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_ly;
        color: Theme.color("light1");
        text: "Протяженность кадра по <i>OY</i>: " + m_ly; //
        font.pixelSize: 10
        font.family: fontMedium.name;
        font.bold: false
    }
    Text {
        id: text_c_y0;
        color: Theme.color("light1");
        text: "y0 (не используется): " + m_y0; //
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_dx;
        color: Theme.color("light1");
        text: "Попиксельный шаг по <i>OX</i>: " + m_dx;
        font.pixelSize: 10
        font.family: fontMedium.name;
        font.bold: false
    }
    Text {
        id: text_c_dy
        color: Theme.color("light1");
        text: "Попиксельный шаг по <i>OY</i>: " + m_dy;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_angle;
        color: Theme.color("light1");
        text: "Азимут: " + m_angle;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_driftAngle;
        color: Theme.color("light1");
        text: "Угол сноса: " + m_driftAngle;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_div;
        color: Theme.color("light1");
        text: "Ширина диаграммы направленности: " + m_azimuth;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_14;
        color: Theme.color("light1");
        text: "Навигационная скорость: " + m_velocity;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_15;
        color: Theme.color("light1");
        text: "Навигационная высота: " + m_elevation;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_16;
        color: Theme.color("light1");
        text: "Время синтезирования: " + m_ts;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_17;
        color: Theme.color("light1");
        text: "Смещение по времени: " + m_timeshift;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_18;
        color: Theme.color("light1");
        text: "Режим: " + m_mode;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_19;
        color: Theme.color("light1");
        text: "Коэффициент ЧИ: " + m_kr;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
    Text {
        id: text_c_hash;
        color: Theme.color("light1");
        text: "Хэш файла: " + m_hash;
        font.pixelSize: 10;
        font.family: fontMedium.name;
        font.bold: false;
    }
}
