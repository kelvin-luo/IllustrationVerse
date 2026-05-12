
#include <QApplication>

#pragma encoding("UTF-8")
#pragma execution_character_set("utf-8")

#include <QLocale>
#include <QTranslator>
#include <QTextCodec>
#include <QDebug>
#include <QWidget>
int main(int argc, char *argv[]) {
    // QTextCodec *codec = QTextCodec::codecForName("UTF8"); // 例如，对于GBK编码的文本
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    QByteArray encodedStr = codec->fromUnicode(QString::fromUtf8("你的UTF-8文本"));
    QString decodedStr = codec->toUnicode(encodedStr);

    // 设置应用程序的编码为UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    QWidget w;
    w.show();
    return a.exec();
}    
