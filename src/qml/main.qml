import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 1280
    height: 1024
    title: qsTr("FinParse")
    color: "#fff"

    header: Rectangle {
        height: 50
        width: parent.width
        color: "#888"
        ToolBar {
            anchors.fill: parent
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    text: qsTr("Load")
                    onClicked: fileDialog.visible = true
                }
                ToolButton {
                    text: qsTr("Quit")
                    onClicked: Qt.quit();
                }
            }
        }
    }
    Item {
        focus: true
        Keys.onPressed: {
            if (event.text == "d") {
                list.viewMode = !list.viewMode;
            }
        }
    }

    Page {
        anchors.fill: parent
        background: Rectangle {
            color: "#fff"
        }

        ListView {
            id: list
            property bool viewMode: false
            anchors.fill: parent
            ScrollBar.vertical: ScrollBar {}
            model: PdfDocument

            delegate: Rectangle {
                width: image.width
                height: image.height

                Image {
                    id: image
                    width: list.width
                    height: width * sourceSize.height/sourceSize.width
                    source: url
                    visible: !list.viewMode
                }
                Text {
                    width: image.width
                    height: image.height
                    font.pixelSize: 16
                    text: raw
                    visible: list.viewMode
                    clip: true
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Choose file")

        onAccepted: {
            console.log(fileDialog.fileUrls)
            System.loadFiles(fileDialog.fileUrls);
        }
    }
}
