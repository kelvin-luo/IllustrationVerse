#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>

// 自定义许可证密钥对话框。这个对话框的唯一的作用就是复制激活码。
class LicenseKeyDialog : public QDialog {
    Q_OBJECT

public:
    LicenseKeyDialog(const QString& key, QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("License Key");
        setMinimumWidth(400);

        // 创建主布局
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        // 添加说明标签
        QLabel* infoLabel = new QLabel("Your generated license key is:", this);
        mainLayout->addWidget(infoLabel);

        // 添加文本编辑框显示密钥（只读）
        keyEdit = new QTextEdit(key, this);
        keyEdit->setReadOnly(true);
        keyEdit->setMinimumHeight(100);
        mainLayout->addWidget(keyEdit);

        // 创建按钮布局
        QHBoxLayout* buttonLayout = new QHBoxLayout;

        // 添加复制按钮
        QPushButton* copyButton = new QPushButton("Copy to Clipboard", this);
        connect(copyButton, &QPushButton::clicked, this, &LicenseKeyDialog::copyToClipboard);
        buttonLayout->addWidget(copyButton);

        // 添加确定按钮
        QPushButton* okButton = new QPushButton("OK", this);
        connect(okButton, &QPushButton::clicked, this, &LicenseKeyDialog::accept);
        buttonLayout->addWidget(okButton);

        mainLayout->addLayout(buttonLayout);
    }

private slots:
    void copyToClipboard() {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(keyEdit->toPlainText());
    }

private:
    QTextEdit* keyEdit;
};

// 在需要显示许可证密钥的地方使用这个对话框
// LicenseKeyDialog dialog(generatedKey, this);
// dialog.exec();

#endif // MYDIALOG_H
