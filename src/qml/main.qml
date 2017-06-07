import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 1024
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

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page {
            background: Rectangle {
                color: "#fff"
            }

            ListView {
                id: list
                anchors.fill: parent
                ScrollBar.vertical: ScrollBar {}

                model: PdfDocument

                delegate: Image {
                    width: list.width
                    height: width * sourceSize.height/sourceSize.width
                    source: url
                }

            }
        }
        Page {
            Label {
                text: qsTr("Parsed")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Document")
        }
        TabButton {
            text: qsTr("Parsed")
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
