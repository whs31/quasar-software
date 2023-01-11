import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15

ColumnLayout {
    spacing: 1;
    Text {
        id: text_d_infoLabel;
        color: "#dae1e5";
        text: "Информация об изображении №" + Number(index + 1);
        font.pixelSize: 11
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignTop;
        bottomPadding: 5
        font.underline: true;
        font.bold: true;
    }
    Text {
        id: text_c_filename
        color: "#dae1e5"
        text: "Имя файла: " + m_filename;
        font.pixelSize: 9
        font.bold: true
        font.family: "Verdana"
    }
    Text {
        id: text_c_creationTime
        color: "#dae1e5"
        text: "Время съемки: " + m_datetime;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: true
    }
    Text {
        id: text_c_latitude
        color: "#dae1e5"
        text: "Широта: " + m_latitude;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: true
    }
    Text {
        id: text_c_longitude
        color: "#dae1e5"
        text: "Долгота: " + m_longitude;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: true
    }
    Text {
        id: text_c_hashMatch
        color: "#dae1e5"
        text: "Совпадение хэша: " + m_checksumMatch;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: true
    }
    Text {
        id: text_c_lx
        color: "#dae1e5"
        text: "Протяженность кадра по <i>OX</i>: " + m_lx;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_x0
        color: "#dae1e5"
        text: "Ближняя граница: " + m_x0;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_ly
        color: "#dae1e5"
        text: "Протяженность кадра по <i>OY</i>: " + m_ly; //
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_y0
        color: "#dae1e5"
        text: "y0 (не используется): " + m_y0; //
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_dx
        color: "#dae1e5"
        text: "Попиксельный шаг по <i>OX</i>: " + m_dx;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_dy
        color: "#dae1e5"
        text: "Попиксельный шаг по <i>OY</i>: " + m_dy;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_angle
        color: "#dae1e5"
        text: "Азимут: " + m_angle;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_driftAngle
        color: "#dae1e5"
        text: "Угол сноса: " + m_driftAngle;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_div
        color: "#dae1e5"
        text: "Ширина диаграммы направленности: " + m_azimuth;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
    Text {
        id: text_c_hash
        color: "#dae1e5"
        text: "Хэш файла: " + m_hash;
        font.pixelSize: 9
        font.family: "Verdana"
        font.bold: false
    }
}
