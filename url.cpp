#include "url.h"

Url::Url()
{
    urlBase = "http://www.neobux.com/";
    urlLogin = "https://www.neobux.com/m/l/";
    urlEarnings = "http://www.neobux.com/c/";
    urlInbox = ""; //No existe en neobux
    urlPtc1 = "";
    urlPtc2 = "";
    urlPtc3 = "";
    urlPtc4 = "";
    urlRedeen = "";
    urlWithDraw = "";

    urlTrampa1 = "no";
    urlTrampa2 = "no";
    urlTrampa3 = "no";
    urlTrampa4 = "no";
    urlTrampa5 = "no";
    urlTrampa6 = "no";
    urlTrampa7 = "no";
    urlTrampa8 = "no";
    urlTrampa9 = "no";

    ptrFinalizado = false;
    ptcFinalizado = false;
    ptc1Finalizado = false;
    ptc2Finalizado = false;
    ptc3Finalizado = false;
    ptc4Finalizado = false;

    ptrFinalizado = false;
    ptcFinalizado = false;
    ptc1Finalizado = false;
    ptc2Finalizado = false;
    ptc3Finalizado = false;
    ptc4Finalizado = false;

    todoFinalizado = false;
    identificado = false;

}

void Url::putUrlBase(const QString &urlBase_)
{
    urlBase = urlBase_;

    //Introducimos las direcciones por defecto
    urlLogin = urlBase+"pages/enter.php";
    urlEarnings = urlBase+"pages/earnings.php";
    urlInbox = urlBase+"pages/inbox.php";
    urlPtc1 = urlBase+"pages/ptc.php";
    urlPtc2 = "";
    urlPtc3 = "";
    urlRedeen = urlBase+"pages/redeem.php";
    urlWithDraw = urlBase+"pages/cashout.php";

}

void Url::putUrlLogin(const QString &urlLogin_)
{
    urlLogin = urlLogin_;

}

void Url::putUrlEarnings(const QString &urlEarnings_)
{
    urlEarnings = urlEarnings_;

}

void Url::putUrlInbox(const QString &urlInbox_)
{
    urlInbox = urlInbox_;

}

void Url::putUrlPtc1(const QString &urlPtc1_)
{
    urlPtc1 = urlPtc1_;

}

void Url::putUrlPtc2(const QString &urlPtc2_)
{
    urlPtc2 = urlPtc2_;

}

void Url::putUrlPtc3(const QString &urlPtc3_)
{
    urlPtc3 = urlPtc3_;

}

void Url::putUrlPtc4(const QString &urlPtc4_)
{
    urlPtc4 = urlPtc4_;

}

void Url::putPtcTrampa1(const QString &urlTrampa1_)
{
    urlTrampa1 = urlTrampa1_;

}

void Url::putPtcTrampa2(const QString &urlTrampa2_)
{
    urlTrampa2 = urlTrampa2_;

}

void Url::putPtcTrampa3(const QString &urlTrampa3_)
{
    urlTrampa3 = urlTrampa3_;

}

void Url::putPtcTrampa4(const QString &urlTrampa4_)
{
    urlTrampa4 = urlTrampa4_;

}

void Url::putPtcTrampa5(const QString &urlTrampa5_)
{
    urlTrampa5 = urlTrampa5_;

}

void Url::putPtcTrampa6(const QString &urlTrampa6_)
{
    urlTrampa6 = urlTrampa6_;

}

void Url::putPtcTrampa7(const QString &urlTrampa7_)
{
    urlTrampa7 = urlTrampa7_;

}

void Url::putPtcTrampa8(const QString &urlTrampa8_)
{
    urlTrampa8 = urlTrampa8_;

}

void Url::putPtcTrampa9(const QString &urlTrampa9_)
{
    urlTrampa9 = urlTrampa9_;

}

void Url::putUrlRedeen(const QString &urlRedeen_)
{
    urlRedeen = urlRedeen_;

}

void Url::putUrlWithDraw(const QString &urlWithDraw_)
{
    urlWithDraw = urlWithDraw_;

}

void Url::putIdentificado(const bool &identificado_)
{
    identificado = identificado_;

}

void Url::putPtrFinalizado(const bool &ptrFinalizado_)
{
    ptrFinalizado = ptrFinalizado_;

}

void Url::putPtcFinalizado(const bool &ptcFinalizado_)
{
    ptcFinalizado = ptcFinalizado_;

}

void Url::putPtc1Finalizado(const bool &ptc1Finalizado_)
{
    ptc1Finalizado = ptc1Finalizado_;

}

void Url::putPtc2Finalizado(const bool &ptc2Finalizado_)
{
    ptc2Finalizado = ptc2Finalizado_;

}

void Url::putPtc3Finalizado(const bool &ptc3Finalizado_)
{
    ptc3Finalizado = ptc3Finalizado_;

}

void Url::putPtc4Finalizado(const bool &ptc4Finalizado_)
{
    ptc4Finalizado = ptc4Finalizado_;

}

void Url::putTodoFinalizado(const bool &todoFinalizado_)
{
    todoFinalizado = todoFinalizado_;

}

QString Url::getUrlBase() const
{
    return urlBase;

}

QString Url::getUrlLogin() const
{
    return urlLogin;

}

QString Url::getUrlEarnings() const
{
    return urlEarnings;

}

QString Url::getUrlInbox() const
{
    return urlInbox;

}

QString Url::getUrlPtc1() const
{
    return urlPtc1;

}

QString Url::getUrlPtc2() const
{
    return urlPtc2;

}

QString Url::getUrlPtc3() const
{
    return urlPtc3;

}

QString Url::getUrlPtc4() const
{
    return urlPtc4;

}

QString Url::getPtcTrampa1() const
{
    return urlTrampa1;

}

QString Url::getPtcTrampa2() const
{
    return urlTrampa2;

}

QString Url::getPtcTrampa3() const
{
    return urlTrampa3;

}

QString Url::getPtcTrampa4() const
{
    return urlTrampa4;

}

QString Url::getPtcTrampa5() const
{
    return urlTrampa5;

}

QString Url::getPtcTrampa6() const
{
    return urlTrampa6;

}

QString Url::getPtcTrampa7() const
{
    return urlTrampa7;

}

QString Url::getPtcTrampa8() const
{
    return urlTrampa8;

}

QString Url::getPtcTrampa9() const
{
    return urlTrampa9;

}

QString Url::getUrlRedeen() const
{
    return urlRedeen;

}

QString Url::getUrlWithDraw() const
{
    return urlWithDraw;

}

bool Url::getIdentificado() const
{
    return identificado;

}

bool Url::getPtrFinalizado() const
{
    return ptrFinalizado;

}

bool Url::getPtcFinalizado() const
{
    return ptcFinalizado;

}

bool Url::getPtc1Finalizado() const
{
    return ptc1Finalizado;

}

bool Url::getPtc2Finalizado() const
{
    return ptc2Finalizado;

}

bool Url::getPtc3Finalizado() const
{
    return ptc3Finalizado;

}

bool Url::getPtc4Finalizado() const
{
    return ptc4Finalizado;
}

bool Url::getTodoFinalizado() const
{
    return todoFinalizado;

}


Url::~Url()
{

}
