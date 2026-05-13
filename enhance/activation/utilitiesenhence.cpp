#include "utilitiesenhence.h"

UtilitiesEnhence::UtilitiesEnhence() {}


#include <QMessageBox>


void showCustomCriticalMessageBox(QWidget *parent, const QString &title, const QString &text) {
    QMessageBox msgBox(QMessageBox::Critical, title, text, QMessageBox::Ok, parent);

    // 设置自定义样式
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #f5f5f5;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        QLabel {
            color: #333;
            font-size: 14px;
            min-width: 200px;
        }
        QPushButton {
            background-color: #e74c3c;
            color: white;
            border: none;
            border-radius: 3px;
            padding: 8px 16px;
            font-size: 14px;
            margin: 5px;
        }
        QPushButton:hover {
            background-color: #c0392b;
        }
        QPushButton:pressed {
            background-color: #a93226;
        }
    )");

    msgBox.exec();
}



#if  0
void showCustomInfoMessageBox(QWidget *parent, const QString &title, const QString &text) {
    QMessageBox msgBox(QMessageBox::Information, title, text, QMessageBox::Ok, parent);

    // 设置自定义样式（蓝色主题）
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #f8fafc;
            border: 1px solid #cbd5e1;
            border-radius: 6px;
            padding: 2px;  /* 减小整体内边距 */
        }
        QLabel {
            color: #334155;
            font-size: 14px;
            min-width: 200px;
        }
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 16px;
            font-size: 14px;
            margin: 1px;
        }
        QPushButton:hover {
            background-color: #2563eb;
        }
        QPushButton:pressed {
            background-color: #1d4ed8;
        }
        QMessageBox QLabel#qt_msgbox_icon_label {
            margin-left: 1px;
        }
    )");

    msgBox.exec();
}
#endif

void showCustomInfoMessageBox(QWidget *parent, const QString &title, const QString &text) {
    QMessageBox msgBox(QMessageBox::Information, title, text, QMessageBox::Ok, parent);

    // 设置自定义样式（蓝色主题）
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #f8fafc;
            border: 1px solid #cbd5e1;
            border-radius: 6px;
            padding: 0px;
        }
        QLabel {
            color: #334155;
            font-size: 14px;
            min-width: 320px;
            text-align: left;
            margin: 0;
            padding: 0;
        }
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 16px;
            font-size: 14px;
            min-width: 80px;
            margin: 8px;
        }
        QPushButton:hover {
            background-color: #2563eb;
        }
        QPushButton:pressed {
            background-color: #1d4ed8;
        }
        QMessageBox QLabel#qt_msgbox_label {
            margin-left: 12px;
            margin-right: 12px;
        }
        QMessageBox QLabel#qt_msgbox_icon_label {
            margin-left: 12px;
            margin-right: 12px;
        }
    )");

    msgBox.exec();
}
