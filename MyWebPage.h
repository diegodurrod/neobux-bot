#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QWebPage>

// Reimplementación de la clase QWebPage para evitar diálogos JavaScript
class MyWebPage : public QWebPage
{
    protected:
        virtual bool javaScriptPrompt(QWebFrame *, const QString&, const QString&, QString*) { return true; }
        virtual void javaScriptConsoleMessage(const QString&, int, const QString&) {}
        virtual void javaScriptAlert(QWebFrame*, const QString &) {}
        virtual bool javaScriptConfirm(QWebFrame*, const QString &) { return true; }

};


#endif // MYWEBPAGE_H
