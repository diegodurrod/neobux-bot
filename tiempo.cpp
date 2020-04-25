#include "tiempo.h"

Tiempo::Tiempo()
{
    clickLogin = 15000;
    login = 30000;
    clickVerAds = 25000;
    clickAd = 30000;
    clickPuntoRojo = 31000;
    clickVolver = 80000;
    bucle = 81000;
    chkNuevosAnuncios = 8100000; // 2 horas 15 minutos

    irPerfil = 35000;
    irSupago = irPerfil+10000;
    irPaypal = irSupago+10000;
    irAceptar = irPaypal+10000;

}

void Tiempo::putClickLogin(const int &clickLogin_)
{
    clickLogin = clickLogin_;

}

void Tiempo::putLogin(const int &login_)
{
    login = login_;

}

void Tiempo::putClickVerAds(const int &clickVerAds_)
{
    clickVerAds = clickVerAds_;

}

void Tiempo::putClickAd(const int &clickAd_)
{
    clickAd = clickAd_;

}

void Tiempo::putClickPuntoRojo(const int &clickPuntoRojo_)
{
    clickPuntoRojo = clickPuntoRojo_;

}

void Tiempo::putClickVolver(const int &clickVolver_)
{
    clickVolver = clickVolver_;

}

void Tiempo::putBucle(const int &bucle_)
{
    bucle = bucle_;

}

void Tiempo::putChkNuevosAnuncios(const int &chkNuevosAnuncios_)
{
    chkNuevosAnuncios = chkNuevosAnuncios_;

}

void Tiempo::putIrPerfil(const int &irPerfil_)
{
    irPerfil = irPerfil_;

}

void Tiempo::putIrSupago(const int &irSupago_)
{
    irSupago = irSupago_;

}

void Tiempo::putIrPaypal(const int &irPaypal_)
{
    irPaypal = irPaypal_;

}

void Tiempo::putIrAceptar(const int &irAceptar_)
{
    irAceptar = irAceptar_;

}

int Tiempo::getClickLogin() const
{
    return clickLogin;

}

int Tiempo::getLogin() const
{
    return login;

}

int Tiempo::getClickVerAds() const
{
    return clickVerAds;

}

int Tiempo::getClickAd() const
{
    return clickAd;

}

int Tiempo::getClickPuntoRojo() const
{
    return clickPuntoRojo;

}

int Tiempo::getClickVolver() const
{
    return clickVolver;

}

int Tiempo::getBucle() const
{
    return bucle;

}

long int Tiempo::getChkNuevosAnuncios() const
{
    return chkNuevosAnuncios;

}

int Tiempo::getIrPerfil() const
{
    return irPerfil;

}

int Tiempo::getIrSupago() const
{
    return irSupago;

}

int Tiempo::getIrPaypal() const
{
    return irPaypal;

}

int Tiempo::getIrAceptar() const
{
    return irAceptar;

}

Tiempo::~Tiempo()
{

}
