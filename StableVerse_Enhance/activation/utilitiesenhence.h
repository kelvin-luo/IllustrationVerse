#ifndef UTILITIESENHENCE_H
#define UTILITIESENHENCE_H
#include <QMessageBox>
#include <QPushButton>
class UtilitiesEnhence
{
public:
    UtilitiesEnhence();
};

void showCustomCriticalMessageBox(QWidget *parent, const QString &title, const QString &text) ;



void showCustomInfoMessageBox(QWidget *parent, const QString &title, const QString &text) ;


#endif // UTILITIESENHENCE_H
