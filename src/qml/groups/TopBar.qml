import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import DiskManager 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/input" as Input
import "qrc:/qml/ui/checkboxes" as Checkboxes
import "qrc:/qml/ui/widgets" as CustomWidgets

Rectangle {
    id: base;
    height: 70;
    color: UX.primaryDark;
    
    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }

    Buttons.ClassicButton
    {
        id: formImageButton;
        anchors.bottom: parent.bottom;              anchors.bottomMargin: 14;
        anchors.left: parent.left;                  anchors.leftMargin: 8;

        display_mode: Buttons.ClassicButton.Mode.LabelOnly;
        fixed_width: 188;                           fixed_height: 28;
        label_text: RuntimeData.formingQueueMode === 0 ? "ФОРМИРОВАНИЕ РЛИ" : RuntimeData.formingContinuous ? "ОСТАНОВКА" : "ЗАПУСК ОЧЕРЕДИ";
        label_color: RuntimeData.formingQueueMode === 1 ? UX.primaryDarker : UX.textWhite;          label_text_size: 17;
        label_text_family: fontBold.name;   label_text_bold: true;
        background_color: RuntimeData.formingQueueMode === 0 ? UX.infoLight : RuntimeData.formingContinuous ? UX.textWhite : UX.accentLighter;
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: 
        { 
            if(!RuntimeData.formingContinuous) { 
                SignalLinker.formSingleImage(); 
                if(RuntimeData.formingQueueMode === 1)
                {
                    RuntimeData.formingContinuous = true; 
                }
            }
            else { RuntimeData.formingContinuous = false; }
        }
    }
    Labels.FramedLabel
    {
        id: formModeLabel;
        anchors.bottom: formImageButton.top;    anchors.bottomMargin: 4;
        anchors.left: formImageButton.left;

        fixed_width: 51;    fixed_height: 17;
        label_text: "РЕЖИМ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                    frame_width: 1;
    }
    Dropdowns.Dropdown
    {
        id: formModeDropDown;
        anchors.left: formModeLabel.right;  anchors.leftMargin: 1;
        anchors.top: formModeLabel.top;
        
        fixed_width: 136;       fixed_height: 17;           fixed_drop: 17*2;
        label_text: RuntimeData.formingQueueMode === 0 ? "ОДИНОЧНОЕ" : "НЕПРЕРЫВНОЕ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        highlight_color: UX.infoLight;
        frame_radius: 2;                    frame_width: 1;
        enabled: RuntimeData.formingContinuous ? false : true;
        container: Item {
            Buttons.LightButton
            {
                id: selectSingle;
                fixed_width: 136;               fixed_height: 17;
                label_text: "ОДИНОЧНОЕ";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                highlight_color: UX.textFaded;
                frame_radius: 0;                frame_width: 1;
                frame_enabled: false;
                onClicked: {
                    formModeDropDown.shown = false;
                    RuntimeData.formingQueueMode = 0;
                }
            }
            Buttons.LightButton
            {
                id: selectContinuous;
                anchors.top: selectSingle.bottom;
                fixed_width: 136;               fixed_height: 17;
                label_text: "НЕПРЕРЫВНОЕ";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                highlight_color: UX.textFaded;
                frame_radius: 0;                frame_width: 1;
                frame_enabled: false;
                onClicked: {
                    formModeDropDown.shown = false;
                    RuntimeData.formingQueueMode = 1;
                }
            }
        }
    }
    Buttons.LightToolButton
    {
        id: panImageButton;
        anchors.top: formModeDropDown.top;
        anchors.left: formModeDropDown.right;     anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.infoLight;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/image.png";
        onClicked: { panImage(); RuntimeData.followPlane = false; }
    }
    Buttons.LightToolButton
    {
        id: panPlaneButton;
        anchors.top: panImageButton.top;
        anchors.left: panImageButton.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.infoLight;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/gps.png";
        onClicked: { panGPS(); }
    }
    Buttons.LightToolButton
    {
        id: refreshCatalogueButton;
        anchors.top: panPlaneButton.top;
        anchors.left: panPlaneButton.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.successLighter;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/refresh.png";
        onClicked: { DiskManager.fetchDirectory(); }
    }
    Buttons.LightToolButton
    {
        id: changeCatalogueButton;
        anchors.top: refreshCatalogueButton.top;
        anchors.left: refreshCatalogueButton.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.warningLight;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/folder.png";
        onClicked: { ioHandler.changeDirectory(); }
    }
    Buttons.LightToolButton
    {
        id: clearMapButton;
        anchors.top: changeCatalogueButton.top;
        anchors.left: changeCatalogueButton.right;    anchors.leftMargin: 6;

        fixed_width: 22;      fixed_height: 16;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 12;
        icon_source: "qrc:/icons/eraser.png";
        onClicked: {
            var verify = ioHandler.clearMap();
            if(verify) {
                imageModel.clear();
                imageUIModel.clear();
                ImageManager.clearAll();
            }
        }
    }
    Buttons.LightToolButton
    {
        id: clearLocalCacheButton;
        anchors.bottom: changeCatalogueButton.bottom;
        anchors.left: changeCatalogueButton.right;    anchors.leftMargin: 6;

        fixed_width: 22;      fixed_height: 16;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 12;
        icon_source: "qrc:/icons/trashbin.png";
        onClicked: {
            var verify = ioHandler.clearCache();
            if(verify) { DiskManager.clearCache(); }
        }
    }
    Dropdowns.Dropdown
    {
        id: formParametersDropDown;
        anchors.left: panImageButton.left;
        anchors.bottom: separator1.bottom;

        fixed_width: 186;       fixed_height: 17;           fixed_drop: 17*8;
        label_text: "ПАРАМЕТРЫ ФОРМИРОВАНИЯ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        highlight_color: UX.infoLight;
        frame_radius: 2;                    frame_width: 1;
        clip: false;
        //enabled: RuntimeData.formingContinuous ? false : true;
        container: Item {
                        Dropdowns.SideDropdown
                        {
                            clip: false;
                            id: formParametersModeDropdown;
                            fixed_width: 186;       fixed_height: 17;      fixed_drop_width: 64;        fixed_drop_height: 17*4;
                            label_uppercase: true;
                            label_text: "РЕЖИМ : " + RuntimeData.formMode;
                            label_color: UX.primaryDarker;          label_text_size: 12;                drop_color: UX.textWhite;
                            label_text_family: fontMedium.name;     label_text_bold: true;
                            label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                    frame_width: 0;
                            container: Item {
                                Buttons.LightButton
                                {
                                    id: m1Button;
                                    fixed_width: 64;             fixed_height: 17;
                                    label_text: "M1";
                                    label_color: UX.primaryDarker;  label_text_size: 12;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        RuntimeData.formMode = "m1";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m2Button;
                                    anchors.top: m1Button.bottom;
                                    fixed_width: 64;               fixed_height: 17;
                                    label_text: "M2";
                                    label_color: UX.primaryDarker;  label_text_size: 12;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        RuntimeData.formMode = "m2";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m3Button;
                                    anchors.top: m2Button.bottom;
                                    fixed_width: 64;               fixed_height: 17;
                                    label_text: "M3";
                                    label_color: UX.primaryDarker;  label_text_size: 12;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        RuntimeData.formMode = "m3";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m4Button;
                                    anchors.top: m3Button.bottom;
                                    fixed_width: 64;               fixed_height: 17;
                                    label_text: "M4";
                                    label_color: UX.primaryDarker;  label_text_size: 12;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        RuntimeData.formMode = "m4";
                                    }
                                }
                            }
                        }
                        Input.LineEdit
                        {
                            id: x0Input;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: formParametersModeDropdown.bottom;
                            label_text: "БЛИЖНЯЯ ГРАНИЦА : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formLowerBound);
                            input_text_postfix: " M";
                            lower_bound: 50; upper_bound: 2000; decimal_precision: 0;
                            onTxtChanged: {
                                RuntimeData.formLowerBound = parseInt(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: lxInput;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: x0Input.bottom;
                            label_text: "ДАЛЬНЯЯ ГРАНИЦА : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formUpperBound);
                            input_text_postfix: " M";
                            lower_bound: 500; upper_bound: 10000; decimal_precision: 0;
                            onTxtChanged: {
                                RuntimeData.formUpperBound = parseInt(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: dxInput;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: lxInput.bottom;
                            label_text: "ПОПИКСЕЛЬНЫЙ ШАГ : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formStep);
                            input_text_postfix: "";
                            lower_bound: 0.1; upper_bound: 10; decimal_precision: 2;
                            onTxtChanged: {
                                RuntimeData.formStep = parseFloat(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: tsInput;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: dxInput.bottom;
                            label_text: "ВРЕМЯ ФОРМИРОВАНИЯ : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formTime);
                            input_text_postfix: "  С";
                            lower_bound: 0.1; upper_bound: 10; decimal_precision: 2;
                            onTxtChanged: {
                                RuntimeData.formTime = parseFloat(input_text);
                            }
                        }
                        Checkboxes.LightCheckbox
                        {
                            id: manualGPSCheckbox;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: tsInput.bottom;
                            label_text: "КОРРЕКТИРОВКА GPS";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            contrast_color: UX.textWhite;
                            highlight_color: UX.infoLight;
                            checked: false;
                            onCheckedChanged: {
                                if(checked) { RuntimeData.formOverrideGPSData = 1; } else { RuntimeData.formOverrideGPSData = 0; }
                            }
                        }
                        Input.LineEdit
                        {
                            id: heightInput;
                            enabled: manualGPSCheckbox.checked;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: manualGPSCheckbox.bottom;
                            label_text: "ВЫСОТА : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formGPSHeight);
                            input_text_postfix: " М";
                            lower_bound: 0.1; upper_bound: 30000.0; decimal_precision: 1;
                            onTxtChanged: {
                                RuntimeData.formGPSHeight = parseFloat(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: velocityInput;
                            enabled: manualGPSCheckbox.checked;
                            fixed_width: 186;               fixed_height: 17;
                            anchors.top: heightInput.bottom;
                            label_text: "СКОРОСТЬ : ";
                            label_color: UX.primaryDarker;  label_text_size: 12;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoLight;
                            input_text: Number(RuntimeData.formGPSVelocity);
                            input_text_postfix: " км/ч";
                            lower_bound: 0.05; upper_bound: 3000.0; decimal_precision: 2;
                            onTxtChanged: {
                                RuntimeData.formGPSVelocity = parseFloat(input_text);
                            }
                        }
        }
    }
    Layouts.Separator
    {
        id: separator1;
        fixed_height: 56;
        line_color: UX.textWhite;
        anchors.left: clearMapButton.right;  anchors.leftMargin: 6;
        anchors.top: clearMapButton.top;
    }
    CustomWidgets.StorageStatusIndicator
    {
        id: storageStatusIndicator;
        anchors.left: separator1.right;     anchors.leftMargin: 6;
        anchors.top: separator1.top;
        percentage: Number.isNaN(100 * (1 - RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace)) ?
                        5 :
                        100 * (1 - RuntimeData.freeDiskSpace / RuntimeData.totalDiskSpace);
    }
    Layouts.Separator
    {
        id: separator2;
        fixed_height: 56;
        line_color: UX.textWhite;
        anchors.left: storageStatusIndicator.right;  anchors.leftMargin: 6;
        anchors.top: clearMapButton.top;
    }
    Labels.FramedLabel
    {
        id: mapToolsLabel;
        anchors.top: separator2.top;
        anchors.left: separator2.right; anchors.leftMargin: 63;

        fixed_width: 176;    fixed_height: 13;
        label_text: "ИНСТРУМЕНТЫ КАРТЫ";
        label_color: UX.textWhite;          label_text_size: 14;
        label_text_family: fontSemiBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                    frame_width: 0;
    }
    Dropdowns.Dropdown
    {
        id: mapParametersDropDown;
        anchors.left: rulerButton.left;
        anchors.top: parent.bottom; anchors.topMargin: -2;

        fixed_width: 220;       fixed_height: 17;           fixed_drop: 17*7;
        label_text: "ПАРАМЕТРЫ КАРТЫ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.primaryLight;
        frame_radius: 2;                    frame_width: 0;
        frame_fill_color: UX.primaryDark;   frame_filled: true;
        container: Item {
            Checkboxes.LightCheckbox
            {
                id: followPlaneCheckbox;
                fixed_width: 220;               fixed_height: 17;
                //anchors.top: tsInput.bottom;
                label_text: "СЛЕДИТЬ ЗА БОРТОМ";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: false;
                onCheckedChanged: { RuntimeData.followPlane = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: cursorCoordsCheckbox;
                fixed_width: 220;               fixed_height: 17;
                anchors.top: followPlaneCheckbox.bottom;
                label_text: "КООРДИНАТЫ КУРСОРА";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: true;
                onCheckedChanged: { RuntimeData.drawTooltip = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: drawRouteCheckbox;
                fixed_width: 220;               fixed_height: 17;
                anchors.top: cursorCoordsCheckbox.bottom; anchors.topMargin: 17;
                label_text: "ОТОБРАЖАТЬ ТРЕК ПОЛЁТА";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: true;
                onCheckedChanged: { RuntimeData.drawRoute = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: drawVectorCheckbox;
                fixed_width: 220;               fixed_height: 17;
                anchors.top: drawRouteCheckbox.bottom;
                label_text: "ОТОБРАЖАТЬ ВЕКТОР СКОРОСТИ";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: true;
                onCheckedChanged: { RuntimeData.drawPredict = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: drawDiagramCheckbox;
                fixed_width: 220;               fixed_height: 17;
                anchors.top: drawVectorCheckbox.bottom;
                label_text: "ДИАГРАММА НАПРАВЛЕННОСТИ";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: true;
                onCheckedChanged: { RuntimeData.drawDiagram = checked; }
            }
            Buttons.LightButton
            {
                id: clearTrackButton;
                anchors.top: drawDiagramCheckbox.bottom;
                fixed_width: 220;               fixed_height: 17;
                label_text: "ОЧИСТИТЬ ТРЕК";
                label_color: UX.primaryDarker;  label_text_size: 12;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
                highlight_color: UX.textFaded;
                frame_radius: 0;                frame_width: 1;
                frame_enabled: false;
                onClicked: {
                    ioHandler.clearTrack();
                }
            }
        }
    }
    Buttons.LightToolButton
    {
        id: rulerButton;
        anchors.bottom: separator2.bottom;
        anchors.left: separator2.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/ruler.png";
        onClicked: {
            if(r_currentstate !== 0) { r_currentstate = 1;
                clearRuler(); } else {
                r_currentstate = 1;
            }
        }
    }
    Buttons.LightToolButton
    {
        id: protractorButton;
        anchors.bottom: rulerButton.bottom;
        anchors.left: rulerButton.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/protractor.png";
        onClicked: {
        }
    }
    Layouts.Separator
    {
        id: separator3;
        fixed_height: 56;
        line_color: UX.textWhite;
        anchors.left: mapToolsLabel.right;  anchors.leftMargin: 63;
        anchors.top: clearMapButton.top;
    }
    Labels.FramedLabel
    {
        id: mapUnitsLabel;
        anchors.top: separator3.top;
        anchors.left: separator3.right; anchors.leftMargin: 63;

        fixed_width: 176;    fixed_height: 13;
        label_text: "ОБЪЕКТЫ КАРТЫ";
        label_color: UX.textWhite;          label_text_size: 14;
        label_text_family: fontSemiBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                    frame_width: 0;
    }
    Buttons.LightToolButton
    {
        id: markerButton;
        anchors.bottom: separator3.bottom;
        anchors.left: separator3.right;    anchors.leftMargin: 6;

        fixed_width: 35;      fixed_height: 35;
        frame_color: UX.textWhite;
        highlight_color: UX.primaryLighter;
        frame_radius: 2; frame_enabled: true;
        icon_px_size: 23;
        icon_source: "qrc:/icons/marker.png";
        onClicked: {
            ioHandler.placeMarker();
        }
    }
    Layouts.Separator
    {
        id: separator4;
        fixed_height: 56;
        line_color: UX.textWhite;
        anchors.left: mapUnitsLabel.right;  anchors.leftMargin: 65;
        anchors.top: clearMapButton.top;
    }
}
