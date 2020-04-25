#ifndef TIEMPO_H
#define TIEMPO_H

class Tiempo
{
private:
    int clickLogin;
    int login;
    int clickVerAds;
    int clickAd;
    int clickPuntoRojo;
    int clickVolver;
    int bucle;
    long int chkNuevosAnuncios;

    int irPerfil;
    int irSupago;
    int irPaypal;
    int irAceptar;

public:
    Tiempo();
    ~Tiempo();

    //Inicio de los métodos put
    void putClickLogin(const int &clickLogin_);
    void putLogin(const int &login_);
    void putClickVerAds(const int &clickClickVerAds_);
    void putClickAd(const int &clickAd_);
    void putClickPuntoRojo(const int &clickPuntoRojo_);
    void putClickVolver(const int &clickVolver_);
    void putBucle(const int &bucle_);
    void putChkNuevosAnuncios(const int &chkNuevosAnuncios_);

    void putIrPerfil(const int &irPerfil_);
    void putIrSupago(const int &irSupago_);
    void putIrPaypal(const int &irPaypal_);
    void putIrAceptar(const int &irAceptar_);

    //Inicio de los métodos get
    int getClickLogin() const;
    int getLogin() const;
    int getClickVerAds() const;
    int getClickAd() const;
    int getClickPuntoRojo() const;
    int getClickVolver() const;
    int getBucle() const;
    long int getChkNuevosAnuncios() const;

    int getIrPerfil() const;
    int getIrSupago() const;
    int getIrPaypal() const;
    int getIrAceptar() const;

};

#endif // TIEMPO_H
