import QtQuick 2.12
import SignalLinker 1.0
import DiskManager 1.0
import ImageManager 1.0
import DialogWindowBackend 1.0

import UX 1.0
import RuntimeData 1.0
import DynamicResolution 1.0
import SAR 1.0
import FormParameters 1.0

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/input" as Input
import "qrc:/qml/ui/checkboxes" as Checkboxes
import "qrc:/qml/ui/widgets" as CustomWidgets


Rectangle {
    id: base;
    height: 70 * DynamicResolution.kh;
    color: UX.primaryDark;
    
    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }

    Buttons.ClassicButton
    {
        id: formImageButton;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 14 * DynamicResolution.kh;
        anchors.left: parent.left;
        anchors.leftMargin: 8 * DynamicResolution.kw;

        display_mode: Buttons.ClassicButton.Mode.LabelOnly;
        fixed_width: 188 * DynamicResolution.kw;
        fixed_height: 28 * DynamicResolution.kh;
        label_text: FormParameters.formingQueueMode === 0 ? "ФОРМИРОВАНИЕ РЛИ" : FormParameters.formingContinuous ? "ОСТАНОВКА" : "ЗАПУСК ОЧЕРЕДИ";
        label_color: FormParameters.formingQueueMode === 1 ? UX.primaryDarker : UX.textWhite;
        label_text_size: 17 * DynamicResolution.kh;
        label_text_family: fontBold.name;   label_text_bold: true;
        background_color: FormParameters.formingQueueMode === 0 ? UX.infoLight : FormParameters.formingContinuous ? UX.textWhite : UX.accentLighter;
		background_secondary_color: Qt.lighter(background_color, 1.1);
        background_radius: 2 * DynamicResolution.kw;
        tooltip_text: "Запуск формирования";
        tooltip_enabled: true;
        onClicked: 
        { 
            if(!FormParameters.formingContinuous) { 
                SignalLinker.formSingleImage(); 
                if(FormParameters.formingQueueMode === 1)
                {
                    FormParameters.formingContinuous = true; 
                }
            }
            else { FormParameters.formingContinuous = false; }
        }
    }
    Labels.FramedLabel
    {
        id: formModeLabel;
        anchors.bottom: formImageButton.top;
        anchors.bottomMargin: 4 * DynamicResolution.kh;
        anchors.left: formImageButton.left;

        fixed_width: 51 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        label_text: "РЕЖИМ";
        label_color: UX.textWhite;          label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 1;
    }
    Dropdowns.Dropdown
    {
        id: formModeDropDown;
        anchors.left: formModeLabel.right;
        anchors.leftMargin: 1 * DynamicResolution.kw;
        anchors.top: formModeLabel.top;
        
        fixed_width: 136 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        fixed_drop: 17*2 * DynamicResolution.kh;
        label_text: FormParameters.formingQueueMode === 0 ? "ОДИНОЧНОЕ" : "НЕПРЕРЫВНОЕ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        highlight_color: UX.infoLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 1;
        enabled: FormParameters.formingContinuous ? false : true;
        container: Item {
            Buttons.LightButton
            {
                id: selectSingle;
                fixed_width: 136 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ОДИНОЧНОЕ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                highlight_color: UX.textFaded;
                frame_radius: 0;                frame_width: 1;
                frame_enabled: false;
                onClicked: {
                    formModeDropDown.shown = false;
                    FormParameters.formingQueueMode = 0;
                }
            }
            Buttons.LightButton
            {
                id: selectContinuous;
                anchors.top: selectSingle.bottom;
                fixed_width: 136 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "НЕПРЕРЫВНОЕ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                highlight_color: UX.textFaded;
                frame_radius: 0;                frame_width: 1;
                frame_enabled: false;
                onClicked: {
                    formModeDropDown.shown = false;
                    FormParameters.formingQueueMode = 1;
                }
            }
        }
    }
    Buttons.LightToolButton
    {
        id: panImageButton;
        anchors.top: formModeDropDown.top;
        anchors.left: formModeDropDown.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.infoLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/image.png";
        tooltip_text: "Центрировать карту на последнем изображении";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: { panImage(); RuntimeData.followPlane = false; }
    }
    Buttons.LightToolButton
    {
        id: panPlaneButton;
        anchors.top: panImageButton.top;
        anchors.left: panImageButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.infoLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/gps.png";
        tooltip_text: "Центрировать карту на БПЛА";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: { panGPS(); }
    }
    Buttons.LightToolButton
    {
        id: refreshCatalogueButton;
        anchors.top: panPlaneButton.top;
        anchors.left: panPlaneButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.successLighter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/refresh.png";
        tooltip_text: "Обновить каталог с изображениями";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: { DiskManager.fetchDirectory(); }
    }
    Buttons.LightToolButton
    {
        id: changeCatalogueButton;
        enabled: !RuntimeData.windowLock;
        anchors.top: refreshCatalogueButton.top;
        anchors.left: refreshCatalogueButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.warningLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/folder.png";
        tooltip_text: "Изменить каталог изображений для просмотра";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: { ioHandler.changeDirectory(); }
    }
    Buttons.LightToolButton
    {
		property bool waitingForDialogResponse: false;

        id: clearMapButton;
        enabled: !RuntimeData.windowLock;
        anchors.top: changeCatalogueButton.top;
        anchors.left: changeCatalogueButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 22 * DynamicResolution.kw;
        fixed_height: 16 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 12 * DynamicResolution.kw;
        icon_source: "qrc:/icons/eraser.png";
        tooltip_text: "Очистить карту";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
			RuntimeData.windowLock = true;
			DialogWindowBackend.header = "ОЧИСТКА КАРТЫ";
			DialogWindowBackend.icon = "qrc:/icons/dialog/warning.png";
			DialogWindowBackend.text = "Вы уверены, что хотите очистить карту от всех изображений?";
			DialogWindowBackend.show();
			waitingForDialogResponse = true;
        }
		function handleResponse()
		{
			if(waitingForDialogResponse === true)
			{
				if(DialogWindowBackend.returnCode === 1)
				{
					imageModel.clear();
					imageUIModel.clear();
					ImageManager.clearAll();
					waitingForDialogResponse = false;
				}
			}
		}
		Component.onCompleted: {
			DialogWindowBackend.returnCodeChanged.connect(handleResponse)
		}
    }
    Buttons.LightToolButton
    {
		property bool waitingForDialogResponse: false;

        id: clearLocalCacheButton;
        enabled: !RuntimeData.windowLock;
        anchors.bottom: changeCatalogueButton.bottom;
        anchors.left: changeCatalogueButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 22 * DynamicResolution.kw;
        fixed_height: 16 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 12 * DynamicResolution.kw;
        icon_source: "qrc:/icons/trashbin.png";
        tooltip_text: "Очистить кэш приложения";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
			RuntimeData.windowLock = true;
			DialogWindowBackend.header = "ОЧИСТКА КЭША";
			DialogWindowBackend.icon = "qrc:/icons/dialog/warning.png";
			DialogWindowBackend.text = "Вы уверены, что хотите очистить кэш программы? Все полученные в ходе полёта изображения исчезнут из памяти компьютера.";
			DialogWindowBackend.show();
			waitingForDialogResponse = true;
		}
		function handleResponse()
		{
			if(waitingForDialogResponse === true)
			{
				if(DialogWindowBackend.returnCode === 1)
				{
					DiskManager.clearCache();
					waitingForDialogResponse = false;
				}
			}
		}
		Component.onCompleted: {
			DialogWindowBackend.returnCodeChanged.connect(handleResponse)
		}
    }
    Dropdowns.Dropdown
    {
        id: formParametersDropDown;
        anchors.left: panImageButton.left;
        anchors.bottom: separator1.bottom;

        fixed_width: 186 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        fixed_drop: 17*8  * DynamicResolution.kh;
        label_text: "ПАРАМЕТРЫ ФОРМИРОВАНИЯ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        highlight_color: UX.infoLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 1;
        clip: false;
        container: Item {
                        Dropdowns.SideDropdown
                        {
                            clip: false;
                            id: formParametersModeDropdown;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            fixed_drop_width: 64 * DynamicResolution.kw;
                            fixed_drop_height: 17*4 * DynamicResolution.kh;
                            label_uppercase: true;
                            label_text: "РЕЖИМ : " + FormParameters.formMode;
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            drop_color: UX.textWhite;
                            label_text_family: fontMedium.name;     label_text_bold: true;
                            label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textFaded;
                            frame_radius: 0;                    frame_width: 0;
                            container: Item {
                                Buttons.LightButton
                                {
                                    id: m1Button;
                                    fixed_width: 64 * DynamicResolution.kw;
                                    fixed_height: 17 * DynamicResolution.kh;
                                    label_text: "M1";
                                    label_color: UX.primaryDarker;
                                    label_text_size: 12 * DynamicResolution.kh;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        FormParameters.formMode = "m1";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m2Button;
                                    anchors.top: m1Button.bottom;
                                    fixed_width: 64 * DynamicResolution.kw;
                                    fixed_height: 17 * DynamicResolution.kh;
                                    label_text: "M2";
                                    label_color: UX.primaryDarker;
                                    label_text_size: 12 * DynamicResolution.kh;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        FormParameters.formMode = "m2";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m3Button;
                                    anchors.top: m2Button.bottom;
                                    fixed_width: 64 * DynamicResolution.kw;
                                    fixed_height: 17 * DynamicResolution.kh;
                                    label_text: "M3";
                                    label_color: UX.primaryDarker;
                                    label_text_size: 12 * DynamicResolution.kh;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        FormParameters.formMode = "m3";
                                    }
                                }
                                Buttons.LightButton
                                {
                                    id: m4Button;
                                    anchors.top: m3Button.bottom;
                                    fixed_width: 64 * DynamicResolution.kw;
                                    fixed_height: 17 * DynamicResolution.kh;
                                    label_text: "M4";
                                    label_color: UX.primaryDarker;
                                    label_text_size: 12 * DynamicResolution.kh;
                                    label_text_family: fontMedium.name;
                                    label_text_bold: true;         label_textAlignment: Text.AlignRight;
                                    highlight_color: UX.textFaded;
                                    frame_enabled: false;
                                    onClicked: {
                                        formParametersModeDropdown.shown = false;
                                        FormParameters.formMode = "m4";
                                    }
                                }
                            }
                        }
                        Input.LineEdit
                        {
                            id: x0Input;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: formParametersModeDropdown.bottom;
                            label_text: "БЛИЖНЯЯ ГРАНИЦА : ";
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formLowerBound);
                            input_text_postfix: " м";
                            lower_bound: 50; upper_bound: 2000; decimal_precision: 0;
                            onTxtChanged: {
                                FormParameters.formLowerBound = parseInt(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: lxInput;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: x0Input.bottom;
                            label_text: "ДАЛЬНЯЯ ГРАНИЦА : ";
                            label_color: UX.primaryDarker;  label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formUpperBound);
                            input_text_postfix: " м";
                            lower_bound: 500; upper_bound: 10000; decimal_precision: 0;
                            onTxtChanged: {
                                FormParameters.formUpperBound = parseInt(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: dxInput;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: lxInput.bottom;
                            label_text: "ПОПИКСЕЛЬНЫЙ ШАГ : ";
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formStep);
                            input_text_postfix: "";
                            lower_bound: 0.1; upper_bound: 10; decimal_precision: 2;
                            onTxtChanged: {
                                FormParameters.formStep = parseFloat(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: tsInput;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: dxInput.bottom;
                            label_text: "ВРЕМЯ ФОРМИРОВАНИЯ : ";
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formTime);
                            input_text_postfix: "  с";
                            lower_bound: 0.1; upper_bound: 10; decimal_precision: 2;
                            onTxtChanged: {
                                FormParameters.formTime = parseFloat(input_text);
                            }
                        }
                        Checkboxes.LightCheckbox
                        {
                            id: manualGPSCheckbox;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: tsInput.bottom;
                            label_text: "КОРРЕКТИРОВКА GPS";
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            contrast_color: UX.textWhite;
                            highlight_color: UX.infoLight;
                            checked: false;
                            onCheckedChanged: {
                                if(checked) { FormParameters.formOverrideGPSData = 1; } else { FormParameters.formOverrideGPSData = 0; }
                            }
                        }
                        Input.LineEdit
                        {
                            id: heightInput;
                            enabled: manualGPSCheckbox.checked;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: manualGPSCheckbox.bottom;
                            anchors.topMargin: DynamicResolution.kh;
                            label_text: "ВЫСОТА : ";
                            label_color: UX.primaryDarker;
                            label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formGPSHeight);
                            input_text_postfix: " м";
                            lower_bound: 0.1; upper_bound: 30000.0; decimal_precision: 1;
                            onTxtChanged: {
                                FormParameters.formGPSHeight = parseFloat(input_text);
                            }
                        }
                        Input.LineEdit
                        {
                            id: velocityInput;
                            enabled: manualGPSCheckbox.checked;
                            fixed_width: 186 * DynamicResolution.kw;
                            fixed_height: 17 * DynamicResolution.kh;
                            anchors.top: heightInput.bottom;
                            label_text: "СКОРОСТЬ : ";
                            label_color: UX.primaryDarker;  label_text_size: 12 * DynamicResolution.kh;
                            label_text_family: fontMedium.name;
                            label_text_bold: true;         label_textAlignment: Text.AlignRight;
                            highlight_color: UX.textWhite;
                            frame_radius: 0;                frame_width: 1;
                            frame_enabled: false;
                            selection_color: UX.infoDark;
                            input_text: Number(FormParameters.formGPSVelocity);
                            input_text_postfix: " км/ч";
                            lower_bound: 0.05; upper_bound: 3000.0; decimal_precision: 2;
                            onTxtChanged: {
                                FormParameters.formGPSVelocity = parseFloat(input_text);
                            }
                        }
        }
    }
    Layouts.Separator
    {
        id: separator1;
        fixed_height: 56 * DynamicResolution.kh;
        line_color: UX.textWhite;
        anchors.left: clearMapButton.right;  anchors.leftMargin: 6 * DynamicResolution.kw;
        anchors.top: clearMapButton.top;
    }
    CustomWidgets.StorageStatusIndicator
    {
        id: storageStatusIndicator;
        anchors.left: separator1.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;
        anchors.top: separator1.top;
        percentage: Number.isNaN(100 * (1 - SAR.freeDiskSpace / SAR.totalDiskSpace)) ?
                        5 :
                        100 * (1 - SAR.freeDiskSpace / SAR.totalDiskSpace);
    }
    Layouts.Separator
    {
        id: separator2;
        fixed_height: 56 * DynamicResolution.kh;
        line_color: UX.textWhite;
        anchors.left: storageStatusIndicator.right;  anchors.leftMargin: 6 * DynamicResolution.kw;
        anchors.top: clearMapButton.top;
    }
    Labels.FramedLabel
    {
        id: mapToolsLabel;
        anchors.top: separator2.top;
        anchors.left: separator2.right; anchors.leftMargin: 63 * DynamicResolution.kw;

        fixed_width: 176 * DynamicResolution.kw;
        fixed_height: 13 * DynamicResolution.kh;
        label_text: "ИНСТРУМЕНТЫ КАРТЫ";
        label_color: UX.textWhite;          label_text_size: 14 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Dropdowns.Dropdown
    {
        id: mapParametersDropDown;
        anchors.left: separator2.left;
        anchors.top: parent.bottom; anchors.topMargin: -2 * DynamicResolution.kh;

        fixed_width: 220 * DynamicResolution.kw;
        fixed_height: 17 * DynamicResolution.kh;
        fixed_drop: 17*8 * DynamicResolution.kh;
        label_text: "ПАРАМЕТРЫ КАРТЫ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        highlight_color: UX.primaryLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
        frame_fill_color: UX.primaryDark;   frame_filled: true;
        container: Item {
            Checkboxes.LightCheckbox
            {
                id: followPlaneCheckbox;
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                //anchors.top: tsInput.bottom;
                label_text: "СЛЕДИТЬ ЗА БОРТОМ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: RuntimeData.followPlane;
                onCheckedChanged: { RuntimeData.followPlane = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: drawGridCheckbox;
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                anchors.top: followPlaneCheckbox.bottom;
                label_text: "ОТОБРАЖАТЬ СЕТКУ НА КАРТЕ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: false;
                onCheckedChanged: { RuntimeData.drawGrid = checked; }
            }
            Checkboxes.LightCheckbox
            {
                id: cursorCoordsCheckbox;
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                anchors.top: drawGridCheckbox.bottom;
                label_text: "КООРДИНАТЫ КУРСОРА";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
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
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                anchors.top: cursorCoordsCheckbox.bottom;
                anchors.topMargin: 17 * DynamicResolution.kh;
                label_text: "ОТОБРАЖАТЬ ТРЕК ПОЛЁТА";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
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
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                anchors.top: drawRouteCheckbox.bottom;
                label_text: "ОТОБРАЖАТЬ ВЕКТОР СКОРОСТИ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
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
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                anchors.top: drawVectorCheckbox.bottom;
                label_text: "ДИАГРАММА НАПРАВЛЕННОСТИ";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignRight;
                contrast_color: UX.textWhite;
                highlight_color: UX.infoLight;
                checked: true;
                onCheckedChanged: { RuntimeData.drawDiagram = checked; }
            }
            Buttons.LightButton
            {
				property bool waitingForDialogResponse: false;

                id: clearTrackButton;
                enabled: !RuntimeData.windowLock;
                anchors.top: drawDiagramCheckbox.bottom;
                fixed_width: 220 * DynamicResolution.kw;
                fixed_height: 17 * DynamicResolution.kh;
                label_text: "ОЧИСТИТЬ ТРЕК";
                label_color: UX.primaryDarker;
                label_text_size: 12 * DynamicResolution.kh;
                label_text_family: fontMedium.name;
                label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
				highlight_color: UX.errorDark;
				frame_radius: 0;                frame_width: 1;
				frame_enabled: false;
				onClicked: {
					RuntimeData.windowLock = true;
					DialogWindowBackend.header = "ОЧИСТКА ТРЕКА";
					DialogWindowBackend.icon = "qrc:/icons/dialog/info.png";
					DialogWindowBackend.text = "Вы уверены, что хотите полностью очистить трек?";
					DialogWindowBackend.show();
					waitingForDialogResponse = true;
				}
				function handleResponse()
				{
					if(waitingForDialogResponse === true)
					{
						if(DialogWindowBackend.returnCode === 1)
						{
							clearRoute();
							waitingForDialogResponse = false;
						}
					}
				}
				Component.onCompleted: {
					DialogWindowBackend.returnCodeChanged.connect(handleResponse)
				}
            }
        }
    }
    Buttons.LightToolButton
    {
        id: rulerButton;
        anchors.bottom: separator2.bottom;
        anchors.left: separator2.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/ruler.png";
        tooltip_text: "Линейка";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
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
        anchors.left: rulerButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/protractor.png";
        tooltip_text: "Угломер";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
        }
    }
    Labels.FramedLabel
    {
        id: zoomLabel;
        anchors.top: protractorButton.top;
        anchors.left: protractorButton.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 55 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: "МАСШТАБ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name;
        label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Buttons.LightToolButton
    {
        id: zoomOutButton;
        anchors.top: zoomLabel.bottom;
        anchors.topMargin: 3 * DynamicResolution.kh;
        anchors.left: zoomLabel.left;

        fixed_width: 18 * DynamicResolution.kw;
        fixed_height: 18 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 12 * DynamicResolution.kw;
        icon_source: "qrc:/icons/minus.png";
        tooltip_text: "Уменьшить масштаб карты";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
            if(mapView.zoomLevel > 2) { mapView.zoomLevel -= 0.5; }
        }
    }
    Input.FramedSlider
    {
        id: zoomSlider;
        anchors.top: zoomOutButton.top;
        anchors.left: zoomOutButton.right;
        anchors.leftMargin: 2 * DynamicResolution.kw;
        fixed_width: 167 * DynamicResolution.kw;
        fixed_height: 18 * DynamicResolution.kh;
        fill_color: UX.textWhite;
        highlight_color: UX.textWhite;
        frame_radius: 2 * DynamicResolution.kw;
        slider_fromvalue: 2;
        slider_tovalue: 18;
        slider_horizontal: true;
        slider_value: RuntimeData.currentZoomLevel;
        onMoved: { mapView.zoomLevel = slider_value; }
    }
    Buttons.LightToolButton
    {
        id: zoomInButton;
        anchors.top: zoomLabel.bottom;
        anchors.topMargin: 3 * DynamicResolution.kh;
        anchors.left: zoomSlider.right;
        anchors.leftMargin: 2 * DynamicResolution.kw;

        fixed_width: 18 * DynamicResolution.kw;
        fixed_height: 18 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.accentLight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 12 * DynamicResolution.kw;
        icon_source: "qrc:/icons/plus.png";
        tooltip_text: "Увеличить масштаб карты";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
            if(mapView.zoomLevel < 18) { mapView.zoomLevel += 0.5; }
        }
    }

    Layouts.Separator
    {
        id: separator3;
        fixed_height: 56 * DynamicResolution.kh;
        line_color: UX.textWhite;
        anchors.left: mapToolsLabel.right;
        anchors.leftMargin: 63 * DynamicResolution.kw;
        anchors.top: clearMapButton.top;
    }
    Labels.FramedLabel
    {
        id: mapUnitsLabel;
        anchors.top: separator3.top;
        anchors.left: separator3.right;
        anchors.leftMargin: 63 * DynamicResolution.kw;

        fixed_width: 176 * DynamicResolution.kw;
        fixed_height: 13 * DynamicResolution.kh;
        label_text: "ОБЪЕКТЫ КАРТЫ";
        label_color: UX.textWhite;
        label_text_size: 14 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name;
        label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Buttons.LightToolButton
    {
        id: markerButton;
        enabled: !RuntimeData.windowLock;
        anchors.bottom: separator3.bottom;
        anchors.left: separator3.right;
        anchors.leftMargin: 6 * DynamicResolution.kw;

        fixed_width: 35 * DynamicResolution.kw;
        fixed_height: 35 * DynamicResolution.kh;
        frame_color: UX.textWhite;
        highlight_color: UX.primaryLighter;
        frame_radius: 2 * DynamicResolution.kw;
        frame_enabled: true;
        icon_px_size: 23 * DynamicResolution.kw;
        icon_source: "qrc:/icons/marker.png";
        tooltip_text: "Установить геометку";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
			RuntimeData.mouseState = 1;
        }
    }

    Labels.FramedLabel
    {
        id: totalImagesCountTooltip;
        anchors.top: parent.top;
        anchors.topMargin: 26 * DynamicResolution.kh;
        anchors.right: separator4.left;
        anchors.rightMargin: 50 * DynamicResolution.kw;

        fixed_width: 170 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: "РАДИОЛОКАЦИОННЫЕ СНИМКИ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name; label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: autocaptureTargetsTooltip;
        anchors.top: totalImagesCountTooltip.bottom;
        anchors.topMargin: -1 * DynamicResolution.kh;
        anchors.right: separator4.left;
        anchors.rightMargin: 50 * DynamicResolution.kw;

        fixed_width: 170 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: "ЦЕЛИ АВТОЗАХВАТА";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name; label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: autocaptureClosestEncounterTooltip;
        anchors.top: autocaptureTargetsTooltip.bottom;
        anchors.topMargin: -1 * DynamicResolution.kh;
        anchors.right: separator4.left;
        anchors.rightMargin: 50 * DynamicResolution.kw;

        fixed_width: 170 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: "РАССТОЯНИЕ ДО БЛИЖАЙШЕЙ";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontSemiBold.name; label_text_bold: false;
        label_textAlignment: Text.AlignLeft;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: totalImagesCountIndicator;
        anchors.top: parent.top;
        anchors.topMargin: 24 * DynamicResolution.kh;
        anchors.right: separator4.left;
        anchors.rightMargin: 4 * DynamicResolution.kw;

        fixed_width: 42 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: RuntimeData.totalImageCount;
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: autocaptureTargetsIndicator;
        anchors.top: totalImagesCountIndicator.bottom;
        anchors.right: separator4.left;
        anchors.rightMargin: 4 * DynamicResolution.kw;

        fixed_width: 42 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: RuntimeData.totalAutocapCount;
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Labels.FramedLabel
    {
        id: autocaptureClosestEncounterIndicator;
        anchors.top: autocaptureTargetsIndicator.bottom;
        anchors.right: separator4.left;
        anchors.rightMargin: 4 * DynamicResolution.kw;

        fixed_width: 42 * DynamicResolution.kw;
        fixed_height: 14 * DynamicResolution.kh;
        label_text: Number(RuntimeData.autocaptureDistance).toFixed(0) + " М";
        label_color: UX.textWhite;
        label_text_size: 12 * DynamicResolution.kh;
        label_text_family: fontExtraBold.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        frame_radius: 2 * DynamicResolution.kw;
        frame_width: 0;
    }
    Layouts.Separator
    {
        id: separator4;
        fixed_height: 56 * DynamicResolution.kh;
        line_color: UX.textWhite;
        anchors.left: mapUnitsLabel.right;
        anchors.leftMargin: 65 * DynamicResolution.kw;
        anchors.top: clearMapButton.top;
    }
}
