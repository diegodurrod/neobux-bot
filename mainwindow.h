#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QWebView>
#include <QWebElement>
#include <QWebElementCollection>
#include <QWebFrame>
#include <QWebPage>
#include <QWebHistory>

#include <QTimer>

#include <QDebug>
#include <QWebInspector> //Para depurar el código HTML
#include <QList>
#include <QListIterator>

#include <QCursor>
#include <QMouseEvent>
#include <QPoint>
#include <QSignalMapper>

#include <qglobal.h>
#include <QTime>

#include "url.h"
#include "tiempo.h"
//#include "vector.h"
#include "MyWebPage.h"

namespace Ui
{
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Url url;
    QUrl urlVerAnuncios;
    Tiempo tiempo;
    MyWebPage *mipagina;
    QWebView *webView;
    //QList<QString> vectorCaptcha;
    //QListIterator<QString> posicionCaptcha;

    //Vector vectorCaptcha; //Añadido aquí como medida de prueba

    //Disparadores  -->  futura clase, modificar
    QTimer *dispClickAd;
    QTimer *dispClickPuntoRojo;
    QTimer *dispMostrarUrl;
    QTimer *dispEliminarObject;
    QTimer *dispEliminarJavascript;
    QTimer *dispVolverPtc;
    QTimer *dispIniciarPTC;

    QTimer *dispClickProfile;
    QTimer *dispClickSuPago;
    QTimer *dispClickPayPal;
    QTimer *dispClickAceptar;

    QTimer *dispComprobarDeNuevo;

    bool captchaSaltado;
    bool banderaPtc; //Para que desconecte solo cuando haya un loadFinished
    bool automatico;
    bool hayAnuncio;
    bool cobrar;
    int x;
    int y;

    //Contadores de URLs para cargar configuraciones
    int contUrlActual; //Indica por qué número está actualmente
    int contUrlTotal; //Indica la cantidad total de ellos

    //Métodos setters y getters para contadores
    void putContUrlActual(const int &contUrlActual_);
    void putContUrlTotal(const int &contUrlTotal_);
    int getContUrlActual() const;
    int getContUrlTotal() const;

    //Indica la página de -Ver Anuncios-
    void putUrlVerAnuncios(const QUrl &url_);
    QUrl getUrlVerAnuncios() const;

    //Indica si el captcha está saltado
    void putCaptchaSaltado(const bool &captchaSaltado_);
    bool getCaptchaSaltado() const;

    //Establece si el proceso es automático o no
    void putAutomatico(const bool &automatico_);
    bool getAutomatico() const;

    //Finaliza una página PTC y pasa a la siguiente si la hubiese
    void finalizarPTC();

    //Finaliza un el sistema y pasa a la configuración del siguiente
    void finalizarSistema();

    //Inicia todas las herramientas para depurar entre otras cosas
    void iniciarHerramientas();

    //Devuelve true si los primeros (longitud) caracteres de las dos
    //direcciones son iguales, de lo contrario, devuelve false
    bool compararDirecciones(const QString &direccion1,
                             const QString &direccion2,
                             const int &longitud);

    //Define las banderas para la desconexión del PTC
    void putBanderaPtc(const bool &banderaPtc_);
    bool getBanderaPtc() const;

    //Establece si hay anuncios
    void putHayAnuncios(const bool &hayAnuncios_);
    bool getHayAnuncios() const;

    //Establece si se está listo para cobrar
    void putCobrar(const bool cobrar_);
    bool getCobrar() const;

    //Obtiene la variable sVL
    QString getVL() const;

    //Genera un número aleatorio entre un valor mínimo y otro máximo
    int generarNum(const int &min, const int &max) const;

    Ui::MainWindow *ui;


public slots:
    //Estos métodos sirven para cargar configs de la web
    //void cargarConfig();
    //void cargarContTotal();
    //void cargarPagConf();
    //void cargarConfs();

    //Salta al siguiente PTR manualmente
    void comodin();

    //Inicia el sistema PTR, PTC...
    void iniciarSistema();

    //Inicia el proceso automático de los PTC
    void iniciarPTC();

    //Desconexiones de métodos
    void descLogin();
    void descClickPtc();

    //Carga de enlaces
    void putPaginaBase();
    void putPaginaLogin();
    void putPaginaEarnings();
    void putPaginaInbox();
    void putPaginaPtc1();
    void putPaginaPtc2();
    void putPaginaPtc3();
    void putPaginaReeden();

    void putIdentificacion();

    void putClickProfile(); // Click a la página del perfil
    void putClickSuPago(); // Click al botón verde de "Su pago"
    void putClickPayPal(); // Click al botón verde de "PayPal"
    void putClickAceptar(); // Click al botón verde de "Sí"

    //void refrescar();

    void putClickPtc(); // Click en banners PTC
    void putClickPuntoRojo(); // Da click en el punto rojo
    void siguienteAnuncio(); // En AdPrize, da click a "siguiente"
    void eliminarObject(); // Elimina todos los objects, videos, sounds y audios
    void eliminarJavascript(); // Elimina todas las etiquetas <script></script>
    void comprobarDeNuevo(); // Comprueba si existen de nuevo anuncios
    void volverPtc(); // Vuelve a la página de los PTC

    void mostrarUrl(); // Imprime en pantalla la dirección real del anuncio
    void mostrarVL(); // Muestra la variable sVL

    void renovarWebKit(); // Destruye y vuelve a crear webkit como si se arrancase de nuevo

    //Este método hace las siguientes tareas:
    //- Vuelve al Inbox una vez que ha sido recompensado por el anuncio
    //- Vuelve y elimina el anuncio visitado
    //- Vuelve y elimina un anuncio que sale del PTR



public:
    explicit MainWindow(QWidget *parent = 0);

    void accionesBotones();



    ~MainWindow();
    

};

#endif // MAINWINDOW_H
