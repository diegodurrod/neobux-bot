#ifndef URL_H
#define URL_H

#include <QString>

class Url
{
private:
    QString urlBase;
    QString urlLogin;
    QString urlEarnings;
    QString urlInbox;
    QString urlPtc1;
    QString urlPtc2;
    QString urlPtc3;
    QString urlPtc4;
    QString urlRedeen;
    QString urlWithDraw;

    QString urlTrampa1;
    QString urlTrampa2;
    QString urlTrampa3;
    QString urlTrampa4;
    QString urlTrampa5;
    QString urlTrampa6;
    QString urlTrampa7;
    QString urlTrampa8;
    QString urlTrampa9;

    bool identificado;
    bool ptrFinalizado;
    bool ptcFinalizado;
    bool ptc1Finalizado;
    bool ptc2Finalizado;
    bool ptc3Finalizado;
    bool ptc4Finalizado;
    bool todoFinalizado;

public:
    Url();
    ~Url();

    //Inicio de los métodos put
    void putUrlBase(const QString &urlBase_);
    void putUrlLogin(const QString &urlLogin_);
    void putUrlEarnings(const QString &urlEarnings_);
    void putUrlInbox(const QString &urlInbox_);
    void putUrlPtc1(const QString &urlPtc1_);
    void putUrlPtc2(const QString &urlPtc2_);
    void putUrlPtc3(const QString &urlPtc3_);
    void putUrlPtc4(const QString &urlPtc4_);
    void putPtcTrampa1(const QString &urlTrampa1_);
    void putPtcTrampa2(const QString &urlTrampa2_);
    void putPtcTrampa3(const QString &urlTrampa3_);
    void putPtcTrampa4(const QString &urlTrampa4_);
    void putPtcTrampa5(const QString &urlTrampa5_);
    void putPtcTrampa6(const QString &urlTrampa6_);
    void putPtcTrampa7(const QString &urlTrampa7_);
    void putPtcTrampa8(const QString &urlTrampa8_);
    void putPtcTrampa9(const QString &urlTrampa9_);
    void putUrlRedeen(const QString &urlReeden_);
    void putUrlWithDraw(const QString &urlWithDraw_);
    void putPtrFinalizado(const bool &ptrFinalizado_);
    void putPtcFinalizado(const bool &ptcFinalizado_);
    void putPtc1Finalizado(const bool &ptc1Finalizado_);
    void putPtc2Finalizado(const bool &ptc2Finalizado_);
    void putPtc3Finalizado(const bool &ptc3Finalizado_);
    void putPtc4Finalizado(const bool &ptc4Finalizado_);
    void putTodoFinalizado(const bool &todoFinalizado_);
    void putIdentificado(const bool &identificado_);

    //Inicio de los métodos get
    QString getUrlBase() const;
    QString getUrlLogin() const;
    QString getUrlEarnings() const;
    QString getUrlInbox() const;
    QString getUrlPtc1() const;
    QString getUrlPtc2() const;
    QString getUrlPtc3() const;
    QString getUrlPtc4() const;
    QString getPtcTrampa1() const;
    QString getPtcTrampa2() const;
    QString getPtcTrampa3() const;
    QString getPtcTrampa4() const;
    QString getPtcTrampa5() const;
    QString getPtcTrampa6() const;
    QString getPtcTrampa7() const;
    QString getPtcTrampa8() const;
    QString getPtcTrampa9() const;
    QString getUrlRedeen() const;
    QString getUrlWithDraw() const;
    bool getPtrFinalizado() const;
    bool getPtcFinalizado() const;
    bool getPtc1Finalizado() const;
    bool getPtc2Finalizado() const;
    bool getPtc3Finalizado() const;
    bool getPtc4Finalizado() const;
    bool getTodoFinalizado() const;
    bool getIdentificado() const;

};

#endif // URL_H
