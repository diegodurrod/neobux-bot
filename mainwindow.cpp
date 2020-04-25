#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    accionesBotones();

    //disparador = new QTimer(this);
    webView = new QWebView(this);

    ui->Tabs->removeTab(1);
    ui->Tabs->removeTab(0);

    // Creación de semilla para la generación de números aleatorios
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    // Fin de la creación

    iniciarHerramientas();

    putUrlVerAnuncios(QUrl(""));

    putAutomatico(true);
    if(getAutomatico())
        iniciarSistema();

}

void MainWindow::comodin()
{
    qDebug() << "[INFO] Aplicando comodín...";

    finalizarSistema();

}

void MainWindow::iniciarSistema()
{
    if(!url.getIdentificado())
    {
        qDebug() << "[INFO] Iniciando sistema... " << url.getUrlBase();

        putPaginaLogin();

        qDebug() << "[INFO] Identificando...";
        QTimer::singleShot(tiempo.getClickLogin(), this, SLOT(putIdentificacion())); //Identifica en 15 segundos
        //connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(putIdentificacion()));

        url.putIdentificado(true);

        //Ver Anuncios -- Sólamente cuando se haya identificado luego se irá a dicha página dando a "volver"
        QTimer::singleShot(tiempo.getClickVerAds(), this, SLOT(putPaginaPtc1()));

    }

    //Tiempo para iniciar el PTC
    QTimer::singleShot(tiempo.getClickLogin()+1, this, SLOT(iniciarPTC()));

}

void MainWindow::iniciarPTC()
{
    if(getHayAnuncios())
    {
        //Limpia la memoria de basura
        webView->settings()->clearMemoryCaches();
        webView->settings()->clearIconDatabase();

        dispClickAd = new QTimer(this);
        dispClickPuntoRojo = new QTimer(this);
        dispMostrarUrl = new QTimer(this);
        dispEliminarObject = new QTimer(this);
        dispEliminarJavascript = new QTimer(this);
        dispVolverPtc = new QTimer(this);
        dispIniciarPTC = new QTimer(this);
        dispClickProfile = new QTimer(this);
        dispClickSuPago = new QTimer(this);
        dispClickPayPal = new QTimer(this);
        dispClickAceptar = new QTimer(this);
        dispComprobarDeNuevo = new QTimer(this);

        dispClickAd->setInterval(tiempo.getClickAd());
        dispClickPuntoRojo->setInterval(tiempo.getClickPuntoRojo());
        dispMostrarUrl->setInterval(tiempo.getClickPuntoRojo()+2000);
        dispEliminarObject->setInterval(tiempo.getClickPuntoRojo()+5000);
        dispEliminarJavascript->setInterval(tiempo.getClickVolver()-1000);
        dispVolverPtc->setInterval(tiempo.getClickVolver());
        dispIniciarPTC->setInterval(tiempo.getBucle());
        dispClickProfile->setInterval(tiempo.getIrPerfil());
        dispClickSuPago->setInterval(tiempo.getIrSupago());
        dispClickPayPal->setInterval(tiempo.getIrPaypal());
        dispClickAceptar->setInterval(tiempo.getIrAceptar());
        dispComprobarDeNuevo->setInterval(tiempo.getChkNuevosAnuncios());

        dispClickAd->setSingleShot(true);
        dispClickPuntoRojo->setSingleShot(true);
        dispMostrarUrl->setSingleShot(true);
        dispEliminarObject->setSingleShot(true);
        dispEliminarJavascript->setSingleShot(true);
        dispVolverPtc->setSingleShot(true);
        dispIniciarPTC->setSingleShot(true);
        dispClickProfile->setSingleShot(true);
        dispClickSuPago->setSingleShot(true);
        dispClickPayPal->setSingleShot(true);
        dispClickAceptar->setSingleShot(true);
        dispComprobarDeNuevo->setSingleShot(true);

        qDebug() << "[INFO] Let's go...";

        //Dar click a un anuncio
        connect(dispClickAd, SIGNAL(timeout()), SLOT(putClickPtc()));
        dispClickAd->start();

        //Dar click al punto rojo
        connect(dispClickPuntoRojo, SIGNAL(timeout()), SLOT(putClickPuntoRojo()));
        dispClickPuntoRojo->start();

        //Dar click al punto rojo
        connect(dispMostrarUrl, SIGNAL(timeout()), SLOT(mostrarUrl()));
        dispMostrarUrl->start();

        //Elimina todos los objetos del iframe
        connect(dispEliminarObject, SIGNAL(timeout()), SLOT(eliminarObject()));
        dispEliminarObject->start();

        //Elimina los scripts
        connect(dispEliminarJavascript, SIGNAL(timeout()), SLOT(eliminarJavascript()));
        dispEliminarJavascript->start();

        //Vuelve a la página de ver anuncios
        connect(dispVolverPtc, SIGNAL(timeout()), SLOT(volverPtc()));
        dispVolverPtc->start();

        //Vuelve a realizarse el proceso
        connect(dispIniciarPTC, SIGNAL(timeout()), SLOT(iniciarPTC()));
        dispIniciarPTC->start();

    }

    else
    {
        if(getCobrar())
        {
            //Dar click para ir al perfil del usuario
            connect(dispClickProfile, SIGNAL(timeout()), SLOT(putClickProfile()));
            dispClickProfile->start();

            //Dar click en el botón para realizar el pago
            connect(dispClickSuPago, SIGNAL(timeout()), SLOT(putClickSuPago()));
            dispClickSuPago->start();

            //Dar click al botón PayPal para elegir la opción de pago
            connect(dispClickPayPal, SIGNAL(timeout()), SLOT(putClickPayPal()));
            dispClickPayPal->start();

            //Dar click al botón Sí para proceder definitivamente al pago
            connect(dispClickAceptar, SIGNAL(timeout()), SLOT(putClickAceptar()));
            dispClickAceptar->start();

            putCobrar(false);

        }

        //Vuelve a recargar por si existiese anuncios nuevos
        connect(dispComprobarDeNuevo, SIGNAL(timeout()), SLOT(comprobarDeNuevo()));
        dispComprobarDeNuevo->start();

        //Rejuvenece webview para eliminar basura - 9 horas
        //QTimer::singleShot(32400000, this, SLOT(renovarWebKit()));

    }

}

void MainWindow::iniciarHerramientas()
{
    //Por defecto dirá que hay anuncios y lo comprobará
    putHayAnuncios(true);
    //Por defecto no se indicará el cobro
    putCobrar(false);

    //Clase para evitar los mensajes de javascript
    mipagina = new MyWebPage;
    webView->setPage(mipagina);

    //Historial de navegación
    QWebHistory *history = webView->page()->history();
    history->setMaximumItemCount(0);

    //Comportamiento visual de la ventana
    setCentralWidget(ui->Tabs);

    ui->Tabs->addTab(webView, "NeoBux");

    //Necesario para inspeccionar elementos DOM
    webView->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    //Para ahorrar ancho de banda
    webView->page()->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    webView->page()->settings()->setAttribute(QWebSettings::JavaEnabled, false);
    webView->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    webView->page()->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);

    //Para ahorrar memoria una vez arrancado
    webView->page()->settings()->setMaximumPagesInCache(0);
    webView->page()->settings()->setObjectCacheCapacities(0, 0, 0);
    webView->page()->settings()->setOfflineStorageDefaultQuota(0);
    webView->page()->settings()->setOfflineWebApplicationCacheQuota(0);
    webView->page()->settings()->setIconDatabasePath("");

    QWebInspector inspector;
    inspector.setPage(webView->page());
    inspector.setVisible(true);

}

void MainWindow::putAutomatico(const bool &automatico_)
{
    automatico = automatico_;

}

void MainWindow::putHayAnuncios(const bool &hayAnuncios_)
{
    hayAnuncio = hayAnuncios_;

}

void MainWindow::putUrlVerAnuncios(const QUrl &url_)
{
    urlVerAnuncios = url_;

}

void MainWindow::putCobrar(const bool cobrar_)
{
    cobrar = cobrar_;

}

bool MainWindow::getAutomatico() const
{
    return automatico;

}

bool MainWindow::getHayAnuncios() const
{
    return hayAnuncio;

}

QUrl MainWindow::getUrlVerAnuncios() const
{
    return urlVerAnuncios;

}

bool MainWindow::getCobrar() const
{
    return cobrar;

}

// Método que imprime en pantalla la dirección real del anuncio (con vl)
void MainWindow::mostrarUrl()
{
    qDebug() << "[INFO] La dirección del anuncio es " << webView->url().toString() << "...";

}

//Método que obtiene la variable sVL para poder después hacer un tratamiento de la misma
QString MainWindow::getVL() const
{
    int i;
    int cont = 0;
    QString sVL;
    QWebFrame *frame = webView->page()->mainFrame();
    QWebElementCollection scripts = frame->findAllElements("script"); //Etiquetas <script></script>

    qDebug() << "[INFO] Mostrando los scripts...";

    for(i=0;i<scripts.count();i++)
    {
        if(scripts.at(i).toOuterXml().indexOf("sVL=") != -1)
        {
            //qDebug() << "[DONE] Cadena sVL capturada: " << scripts.at(i).toOuterXml() << "...";
            sVL = scripts.at(i).toOuterXml().left(212);

            i = scripts.count();

        }

        //else
            //qDebug() << scripts.at(i).toOuterXml();
    }

    //qDebug() << "[INFO] Cadena sVL pre-tratada: " << sVL << "...";

    for(i=sVL.count();i>0;i--)
    {
        if(sVL.at(i) != '\'')
            cont++;
        else
            i = 0;

    }

    sVL = sVL.right(cont-1);

    //qDebug() << "[INFO] Este es el resultado después de tratar la cadena: " << sVL << "...";

    return sVL;

}

//Método que imprime en pantalla la variable sVL
void MainWindow::mostrarVL()
{
    qDebug() << "[INFO] Este es el resultado después de tratar la cadena: " << getVL() << "...";

}

int MainWindow::generarNum(const int &min, const int &max) const
{
    return qrand() % ((max + 1) - min) + min;

}


/////////////////////////////////////////
///    Aquí empiezan otras configs    ///
/////////////////////////////////////////

bool MainWindow::compararDirecciones(const QString &direccion1,
                                     const QString &direccion2,
                                     const int &longitud)
{
    bool correcto = true;

    qDebug() << "[INFO] Dirección sin comprobar: " << direccion1 << " " << direccion2;

    for(int i=0;i<longitud;i++)
    {
        if(direccion1.at(i) != direccion2.at(i))
        {
            correcto = false;
            i = longitud;

        }
    }

    if(!correcto)
        qDebug() << "[WARN] Dirección no idéntica:   " << direccion1 << " " << direccion2;
    else
        qDebug() << "[INFO] Dirección correcta:      " << direccion2;


    return correcto;

}

void MainWindow::eliminarJavascript()
{
    if(getHayAnuncios())
    {
        //int i;

        QWebFrame *frame = webView->page()->mainFrame();
        //QWebElementCollection scripts = frame->findAllElements("script"); //Etiquetas <script></script>
        QWebElement html = frame->findFirstElement("html"); //Etiquetas <html></html>

        html.setInnerXml("");
        html.setOuterXml("");
        html.removeAllChildren();
        html.removeFromDocument();

        frame->setHtml("<html><body><h1>(: Eliminado todo :)</h1></body></html>");

        /*for(i=0;i<scripts.count();i++)
        {
            qDebug() << "[INFO] Anulando " << scripts.at(i).toOuterXml();
            scripts.at(i).parent().removeAllChildren();
            scripts.at(i).setAttribute("src", "");
            scripts.at(i).setInnerXml("");
            scripts.at(i).setOuterXml("");
            scripts.at(i).removeFromDocument();

            if(scripts.at(i).toOuterXml() == "")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << scripts.at(i).toOuterXml();

        }*/
    }
}

void MainWindow::renovarWebKit()
{
    //if(!getHayAnuncios() && !getCobrar())
    //{
        qDebug() << "[INFO] Renovando WebKit...";

        //Desconexión de todos los singleShot
        dispClickAd->stop();
        dispClickPuntoRojo->stop();
        dispMostrarUrl->stop();
        dispEliminarObject->stop();
        dispEliminarJavascript->stop();
        dispVolverPtc->stop();
        dispIniciarPTC->stop();
        dispClickProfile->stop();
        dispClickSuPago->stop();
        dispClickPayPal->stop();
        dispClickAceptar->stop();
        dispComprobarDeNuevo->stop();

        //Renovación de webview
        //webView->page()->mainFrame()->deleteLater();
        //webView->page()->deleteLater();
        webView->page()->deleteLater();
        webView->deleteLater();
        webView = new QWebView(this);

        url.putIdentificado(false);

        iniciarHerramientas();
        iniciarSistema();

    //}
}

//Métodos contadores
void MainWindow::putContUrlActual(const int &contUrlActual_)
{
    contUrlActual = contUrlActual_;

}

void MainWindow::putContUrlTotal(const int &contUrlTotal_)
{
    contUrlTotal = contUrlTotal_;

}

int MainWindow::getContUrlActual() const
{
    return contUrlActual;

}

int MainWindow::getContUrlTotal() const
{
    return contUrlTotal;

}

//Métodos bandera para el Ptc
void MainWindow::putBanderaPtc(const bool &banderaPtc_)
{
    banderaPtc = banderaPtc_;

}

bool MainWindow::getBanderaPtc() const
{
    return banderaPtc;

}

//Métodos booleanos Captcha
void MainWindow::putCaptchaSaltado(const bool &captchaSaltado_)
{
    captchaSaltado = captchaSaltado_;

}

bool MainWindow::getCaptchaSaltado() const
{
    return captchaSaltado;

}

//Métodos para cargar Urls
void MainWindow::putPaginaBase()
{
    webView->load(QUrl(url.getUrlBase()));

}

void MainWindow::putPaginaLogin()
{
    webView->load(QUrl(url.getUrlLogin()));

}

void MainWindow::putPaginaEarnings()
{
    webView->load(QUrl(url.getUrlEarnings()));

}

void MainWindow::putPaginaInbox()
{
    webView->load(QUrl(url.getUrlInbox()));

}

void MainWindow::putPaginaPtc1()
{
    //webView->load(QUrl(url.getUrlPtc1()));

    QWebFrame *frame = webView->page()->mainFrame();
    QWebElement verAnuncios = frame->findFirstElement("a[class='button green']");

    verAnuncios.evaluateJavaScript("this.click()");

    qDebug() << "[DONE] Pasando a la página -Ver anuncios-...";

}

void MainWindow::putPaginaPtc2()
{
    webView->load(QUrl(url.getUrlPtc2()));

}

void MainWindow::putPaginaPtc3()
{
    webView->load(QUrl(url.getUrlPtc3()));

}

void MainWindow::putPaginaReeden()
{
    webView->load(QUrl(url.getUrlRedeen()));

}

void MainWindow::putIdentificacion()
{
    QWebFrame *frame = webView->page()->mainFrame();

    QWebElement user = frame->findFirstElement("input[id='Kf1']");
    QWebElement passwd = frame->findFirstElement("input[id='Kf2']");
    QWebElement submit = frame->findFirstElement("a[id='botao_login']");

    user.setAttribute("value", "*****YOUR_USERNAME*****");
    passwd.setAttribute("value", "*****YOUR_PASSWORD*****");

    submit.evaluateJavaScript("this.click()");

    qDebug() << "[DONE] Identificado...";

    //Medida temporal: probar haber si funciona
    //url.putIdentificado(true);

}

///////////////////////////////////////////////
///     Aquí empiezan las desconexiones     ///
///////////////////////////////////////////////

void MainWindow::descLogin()
{
    disconnect(webView, SIGNAL(loadFinished(bool)), this, SLOT(putIdentificacion()));

}

void MainWindow::descClickPtc()
{
    disconnect(webView, SIGNAL(loadFinished(bool)), this, SLOT(putClickPtc()));

}

/////////////////////////////////////////////////
///     Aquí empieza el mecanismo de pago     ///
/////////////////////////////////////////////////

void MainWindow::putClickProfile()
{
    qDebug() << "[INFO] Haciendo click en el perfil...";
    webView->page()->mainFrame()->findFirstElement("a[id=\"t_conta\"]").evaluateJavaScript("this.click()");

}

void MainWindow::putClickSuPago()
{
    qDebug() << "[INFO] Haciendo click en el botón \"Su Pago\"...";
    webView->page()->mainFrame()->findFirstElement("a[id=\"t_pgt1\"]").evaluateJavaScript("this.click()");

}

void MainWindow::putClickPayPal()
{
    qDebug() << "[INFO] Hacineod click en el botón \"PayPal\"...";
    webView->page()->mainFrame()->findFirstElement("a[onclick=\"tr(1)\"]").evaluateJavaScript("this.click()");

}

void MainWindow::putClickAceptar()
{
    qDebug() << "[INFO] Hacineod click en el botón \"Sí\"...";
    webView->page()->mainFrame()->findFirstElement("a[class=\"button medium green\"]").evaluateJavaScript("this.click()");

}

/////////////////////////////////////////
///     Aquí empieza la parte PTC     ///
/////////////////////////////////////////

//Aquí no hace click en los anuncios
void MainWindow::putClickPtc()
{
    QWebFrame *frame = webView->page()->mainFrame();
    QWebElementCollection collectionAzules = frame->findAllElements("div[class=\"ad15\"]"); //Anuncios azules
    QWebElementCollection collection = frame->findAllElements("div[class=\"adfu\"]"); //Anuncios violetas
    QWebElementCollection collectionVerdes = frame->findAllElements("div[class=\"ad30\"]"); //Anuncios verdes
    QWebElementCollection collectionNaranjas = frame->findAllElements("div[class=\"adf\"]"); //Anuncios naranjas
    QWebElement adPrize = frame->findFirstElement("a[id=\"ap_h\"]");
    QWebElement ganancias = frame->findFirstElement("span[style=\"font-family:verdana;font-size:13px;color:#fff\"]");
    QWebElement gananciasCobro = frame->findFirstElement("span[style=\"font-family:verdana;font-size:13px;color:#8aee3c\"]");
    QWebElement botonCerrar = frame->findFirstElement("a[class=\"button small2 orange\"]");
    //QWebElement aux;

    QString onmouseover;
    QString numAleatorio = QString(generarNum(250, 1000));
    QString entero;
    QString centesimas;
    QString milesimas;
    QString gananciasCantidad;

    qDebug() << "[INFO] Recogiendo todos los anuncios...";

    qDebug() << "[INFO] Existen " << collectionAzules.count() << " anuncios azules disponibles...";
    qDebug() << "[INFO] Existen " << collection.count() << " anuncios violetas disponibles...";
    qDebug() << "[INFO] Existen " << collectionVerdes.count() << " anuncios verdes disponibles...";
    qDebug() << "[INFO] Existen " << collectionNaranjas.count() << " anuncios naranjas disponibles...";
    qDebug() << "[INFO] Existen " << adPrize.toInnerXml().toInt() << " oportunidades en AdPrize para llevarse un premio...";

    centesimas = frame->findFirstElement("span[style=\"font-size:11px;\"]").toInnerXml();
    milesimas = frame->findFirstElement("span[style=\"font-size:9px;\"]").toInnerXml();
    gananciasCantidad = entero+centesimas+milesimas;

    if(adPrize.toInnerXml() == "X" || adPrize.toInnerXml() == "x")
        comprobarDeNuevo();
    else
    {
        if(gananciasCantidad == "")
        {
            qDebug() << "[INFO] Parece que la sesión ha expirado, volviendo a reinicializar el sistema...";
            renovarWebKit();
        }

        if(gananciasCobro.toInnerXml() != "")
        {
            putCobrar(true);

            if(gananciasCobro.toInnerXml().left(8).right(1) == "<")
                entero = gananciasCobro.toInnerXml().left(7).right(3);
            else
                entero = gananciasCobro.toInnerXml().left(8).right(2);

            centesimas = frame->findFirstElement("span[style=\"font-size:11px;\"]").toInnerXml();
            milesimas = frame->findFirstElement("span[style=\"font-size:9px;\"]").toInnerXml();

            gananciasCantidad = entero+centesimas+milesimas;

            ui->Tabs->setTabText(0, "NeoBux: "+gananciasCantidad+" PENDIENTE DE COBRO");

            qDebug() << "[INFO] Su saldo actual es de " << gananciasCantidad;
            qDebug() << "[DONE] ¡PREPARADO PARA COBRAR!...";

        }

        else
        {
            if(ganancias.toInnerXml().left(8).right(1) == "<")
                entero = ganancias.toInnerXml().left(7).right(3);
            else
                entero = ganancias.toInnerXml().left(8).right(2);

            centesimas = frame->findFirstElement("span[style=\"font-size:11px;\"]").toInnerXml();
            milesimas = frame->findFirstElement("span[style=\"font-size:9px;\"]").toInnerXml();

            gananciasCantidad = entero+centesimas+milesimas;

            ui->Tabs->setTabText(0, "NeoBux: "+gananciasCantidad);

            qDebug() << "[INFO] Su saldo actual es de " << gananciasCantidad;

        }

        if(getUrlVerAnuncios().toString() == "")
        {
            qDebug() << "[INFO] Establecida la Dirección de vuelta: " << webView->url().toString();
            putUrlVerAnuncios(webView->url());

        }

        if(collectionAzules.count() > 0)
        {
            qDebug() << "[INFO] Dando click sobre el anuncio azul... " << collectionAzules.first().firstChild().toInnerXml();

            collectionAzules.first().parent().parent().parent().parent().parent().parent().setAttribute("class", "mbxm adbs");
            collectionAzules.first().parent().parent().parent().parent().parent().parent().setAttribute("style", "padding: 1px; float: left; width: 196px; height: 97px; border: 1px solid rgb(102, 102, 102); margin-right: 16px; margin-bottom: 16px; background-color: rgb(250, 250, 250);");

            onmouseover = collectionAzules.first().parent().parent().parent().parent().parent().attribute("onmouseover");

            collectionAzules.first().parent().parent().parent().parent().parent().evaluateJavaScript(onmouseover);
            collectionAzules.first().parent().parent().parent().parent().parent().evaluateJavaScript("ul = "+ numAleatorio +";");
            collectionAzules.first().evaluateJavaScript("this.click()");

        }

        else
        {
            if(collection.count() > 0)
            {
                qDebug() << "[INFO] Dando click sobre el anuncio verde... " << collection.first().firstChild().toInnerXml();

                collection.first().parent().parent().parent().parent().parent().parent().setAttribute("class", "mbxm adbs");
                collection.first().parent().parent().parent().parent().parent().parent().setAttribute("style", "padding: 1px; float: left; width: 196px; height: 97px; border: 1px solid rgb(102, 102, 102); margin-right: 16px; margin-bottom: 16px; background-color: rgb(250, 250, 250);");

                onmouseover = collection.first().parent().parent().parent().parent().parent().attribute("onmouseover");

                collection.first().parent().parent().parent().parent().parent().evaluateJavaScript(onmouseover);
                collection.first().parent().parent().parent().parent().parent().evaluateJavaScript("ul = "+ numAleatorio +";");
                collection.first().evaluateJavaScript("this.click()");

            }

            else
            {
                qDebug() << "[WARN] No existen anuncios violetas...";

                if(collectionVerdes.count() > 0)
                {
                    qDebug() << "[INFO] Dando click sobre el anuncio... " << collectionVerdes.first().firstChild().toInnerXml();

                    collectionVerdes.first().parent().parent().parent().parent().parent().parent().setAttribute("class", "mbxm adbs");
                    collectionVerdes.first().parent().parent().parent().parent().parent().parent().setAttribute("style", "padding: 1px; float: left; width: 196px; height: 97px; border: 1px solid rgb(102, 102, 102); margin-right: 16px; margin-bottom: 16px; background-color: rgb(250, 250, 250);");

                    onmouseover = collectionVerdes.first().parent().parent().parent().parent().parent().attribute("onmouseover");

                    collectionVerdes.first().parent().parent().parent().parent().parent().evaluateJavaScript(onmouseover);
                    collectionVerdes.first().parent().parent().parent().parent().parent().evaluateJavaScript("ul = "+ numAleatorio +";");
                    collectionVerdes.first().evaluateJavaScript("this.click()");

                }

                else
                {
                    qDebug() << "[WARN] No existen anuncios verdes...";

                    if(collectionNaranjas.count() > 0)
                    {
                        qDebug() << "[INFO] Dando click sobre el anuncio... " << collectionNaranjas.first().firstChild().toInnerXml();

                        collectionNaranjas.first().parent().parent().parent().parent().parent().parent().setAttribute("class", "mbxm adbs");
                        collectionNaranjas.first().parent().parent().parent().parent().parent().parent().setAttribute("style", "padding: 1px; float: left; width: 196px; height: 97px; border: 1px solid rgb(102, 102, 102); margin-right: 16px; margin-bottom: 16px; background-color: rgb(250, 250, 250);");

                        onmouseover = collectionNaranjas.first().parent().parent().parent().parent().parent().attribute("onmouseover");

                        collectionNaranjas.first().parent().parent().parent().parent().parent().evaluateJavaScript(onmouseover);
                        collectionNaranjas.first().parent().parent().parent().parent().parent().evaluateJavaScript("ul += "+ numAleatorio +";");
                        collectionNaranjas.first().evaluateJavaScript("this.click()");

                    }

                    else
                    {
                        qDebug() << "[WARN] No existen anuncios naranjas...";

                        if(adPrize.toInnerXml().toInt() != 0)
                        {
                            qDebug() << "[INFO] Intentando suerte en AdPrize... ";
                            adPrize.setAttribute("target", "_self");
                            adPrize.evaluateJavaScript("this.click()");

                        }

                        else
                        {
                            if(botonCerrar.attribute("href") == "#")
                            {
                                qDebug() << "[WARN] Error al volver a -Ver Anuncios-...";
                                qDebug() << "[INFO] Reintentando volver...";
                                //QTimer::singleShot(0, webView, SLOT(back()));
                                //webView->page()->triggerAction(QWebPage::Back);
                                //botonCerrar.setAttribute("onclick", "window.history.back()");
                                //botonCerrar.setAttribute("onclick", "window.top.history.back()");
                                //botonCerrar.removeAttribute("href");
                                qDebug() << "[INFO] Dirección de vuelta: " << webView->page()->history()->backItem().url().toString();
                                webView->load(webView->page()->history()->backItem().url());

                                //botonCerrar.evaluateJavaScript("this.click()");
                                //qDebug() << "[INFO] Resultado de la modificación:" << botonCerrar.toOuterXml();

                            }

                            else
                            {
                                qDebug() << "[WARN] No existen oportunidades en AdPrize...";
                                qDebug() << "[INFO] Toca esperar un tiempo...";

                                putHayAnuncios(false);
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::putClickPuntoRojo()
{
    if(getHayAnuncios())
    {
        QString idA = "";
        QString idC = "";
        QWebFrame *frame = webView->page()->mainFrame();
        QWebElementCollection collection = frame->findAllElements("div[class=\"ad15\"]"); //Anuncios azules
        //QWebElementCollection collection = frame->findAllElements("div[class=\"adfu\"]"); //Anuncios violetas
        QWebElement elementoIdA;
        bool hayBanners = true;

        if(collection.count() > 0)
            elementoIdA = collection.first(); //Localiza el punto rojo

        else
        {
            collection = frame->findAllElements("div[class=\"adfu\"]"); //Localiza los banners violetas

            if(collection.count() > 0)
                elementoIdA = collection.first(); //Localiza el punto rojo

            else
            {
                collection = frame->findAllElements("div[class=\"ad30\"]"); //Localiza los banners verdes

                if(collection.count() > 0)
                    elementoIdA = collection.first(); //Localiza el punto rojo

                else
                {
                    collection = frame->findAllElements("div[class=\"adf\"]"); //Localiza los banners naranjas

                    if(collection.count() > 0)
                        elementoIdA = collection.first(); //Localiza el punto rojo

                    else
                        hayBanners = false;

                }
            }
        }

        if(hayBanners)
        {
            qDebug() << "[INFO] Haciendo click sobre el punto rojo...";

            idA = elementoIdA.parent().attribute("id");

            if(idA.size() == 4)
                idC = idA.left(3)+"c";
            else
                idC = idA.left(4)+"c";

            QWebElement elementoIdC = frame->findFirstElement("span[id="+idC+"]");
            QWebElement puntoRojo = elementoIdC.firstChild();
            /*int *x = new(int);
            int *y = new(int);
            int *ancho = new(int);
            int *alto = new(int);
            int correccionX = 5;
            int correccionY = 60;
            int xFinal;
            int yFinal;

            puntoRojo.geometry().getRect(x, y, ancho, alto);

            xFinal = *x + correccionX;
            yFinal = *y + correccionY;

            QCursor::setPos(mapToGlobal(webView->pos()+=QPoint(xFinal, yFinal)));

            qDebug() << "[INFO] Las coordenadas x e y son " << xFinal << "," << yFinal << " respectivamente...";

            puntoRojo.setAttribute("target", "_self");
            puntoRojo.evaluateJavaScript("var evObj = document.createEvent('MouseEvents');evObj.initEvent( 'click', true, true );this.dispatchEvent(evObj);");

            //QCursor::setPos(mapToGlobal(pos()+=QPoint(*x, *y)));

            //QTimer::singleShot(5000, this, SLOT(clickIzq()));
            */

            puntoRojo.setAttribute("target", "_self");

            qDebug() << "[INFO] El elemento A es " << idA;
            qDebug() << "[INFO] El elemento C es " << elementoIdC.attribute("id");

            if(elementoIdC.firstChild().attribute("href").indexOf("&vl=") != -1)
            {
                //elementoIdC.firstChild().evaluateJavaScript("this.click()");
                webView->load(elementoIdC.firstChild().attribute("href"));
                qDebug() << "[INFO] Haciendo click en " << elementoIdC.firstChild().attribute("href");

            }

            else
            {
                webView->load(elementoIdC.firstChild().attribute("href") + "&vl=" + getVL());
                qDebug() << "[INFO] Haciendo click en " << elementoIdC.firstChild().attribute("href") + "&vl=" + getVL();

            }

            //qDebug() << "[INFO] Haciendo click en " << elementoIdC.firstChild().attribute("href") + "&vl=" + getVL();
            //qDebug() << "[INFO] El atributo style de divIdC es " << elementoIdC.attribute("style");

        }

        else
            qDebug() << "[WARN] No existen más banners...";

        //connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(eliminarObject()));
    }

}

void MainWindow::siguienteAnuncio()
{
    QWebFrame *frame = webView->page()->mainFrame();
    QWebElement botonSiguiente = frame->findFirstElement("a[id=\"nxt_bt_a\"]");
    QWebElement botonCerrar = frame->findFirstElement("a[class=\"button small2 orange\"]");

    if(botonSiguiente.attribute("href") != "")
    {
        qDebug() << "[INFO] Pulsando sobre el botón siguiente...";
        qDebug() << "[INFO] Dirección: " << "http://www.neobux.com"+botonSiguiente.attribute("href");
        webView->load("http://www.neobux.com"+botonSiguiente.attribute("href"));
        //botonSiguiente.evaluateJavaScript("this.click()");

    }

    else
        if(botonCerrar.attribute("href") == "#")
        {
            qDebug() << "[DONE] Se han terminado los anuncios de AdPrize...";
            qDebug() << "[INFO] Volviendo a la página principal... ";
            putPaginaBase();

        }

    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(eliminarObject()));

}

void MainWindow::eliminarObject()
{
    if(getHayAnuncios())
    {
        //int i;
        //QString code;
        QWebFrame *frame = webView->page()->mainFrame();
        //QWebElementCollection scripts = frame->findAllElements("script"); //Etiquetas <script></script>
        //QWebElementCollection objects = frame->findAllElements("object"); //Etiquetas <object></object>
        //QWebElementCollection embed = frame->findAllElements("embed"); //Etiquetas <embed>
        //QWebElementCollection video = frame->findAllElements("video"); //Etiquetas <video></video>
        //QWebElementCollection sound = frame->findAllElements("sound"); //Etiquetas <sound></sound>
        //QWebElementCollection audio = frame->findAllElements("audio"); //Etiquetas <audio></audio>
        //QWebElementCollection iframe = frame->findAllElements("iframe"); //Etiquetas <iframe></iframe>
        QWebElement iF = frame->findFirstElement("iframe[id=\"iF\"]");

        //code = "$('script').remove()";
        //code = "content.replace(/(<script>|<\\/script>)/g, \"\")";
        //frame->evaluateJavaScript(code);
        /*
    for(i=0;i<scripts.count();i++)
    {
        qDebug() << "[INFO] Anulando " << scripts.at(i).toOuterXml();
        scripts.at(i).parent().removeAllChildren();
        scripts.at(i).setAttribute("src", "");
        scripts.at(i).setInnerXml("");
        scripts.at(i).setOuterXml("");
        scripts.at(i).removeFromDocument();

        if(scripts.at(i).toOuterXml() == "")
            qDebug() << "[DONE] Anulado...";
        else
            qDebug() << "[WARN] No se ha podido anular el elemento" << scripts.at(i).toOuterXml();

    }
     */
/*
        for(i=0;i<scripts.count();i++)
        {
            scripts.at(i).removeFromDocument();
            scripts.at(i).parent().removeAllChildren();
*/
            /*if(scripts.at(i).toOuterXml() == "")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << scripts.at(i).toOuterXml();*/

        /*}

        code = "$('object').remove()";
        frame->evaluateJavaScript(code);
        for(i=0;i<objects.count();i++)
        {*/
            /*if(objects.at(i).toOuterXml() == "")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << objects.at(i).toOuterXml();*/

        /*}

        code = "$('embed').remove()";
        frame->evaluateJavaScript(code);
        for(i=0;i<embed.count();i++)
        {*/
            /*if(embed.at(i).toOuterXml() == "")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << embed.at(i).toOuterXml();*/

        /*}

        for(i=0;i<video.count();i++)
        {
            qDebug() << "[INFO] Anulando " << video.at(i).toOuterXml();
            video.at(i).parent().removeAllChildren();
            //video.at(i).removeFromDocument();
*/
            /*if(video.at(i).toOuterXml() == "")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << video.at(i).toOuterXml();*/

        /*}

        for(i=0;i<sound.count();i++)
        {
            qDebug() << "[INFO] Anulando " << sound.at(i).toOuterXml();
            sound.at(i).parent().removeAllChildren();
            //sound.at(i).removeFromDocument();

        }

        for(i=0;i<audio.count();i++)
        {
            qDebug() << "[INFO] Anulando " << audio.at(i).toOuterXml();
            audio.at(i).parent().removeAllChildren();
            //audio.at(i).removeFromDocument();

        }*/

        /*for(i=0;i<iframe.count();i++)
        {
            qDebug() << "[INFO] Anulando " << iframe.at(i).toOuterXml();
            iframe.at(i).setAttribute("src", "about:blank");
*/
            /*if(iframe.at(i).attribute("src") == "about:blank")
                qDebug() << "[DONE] Anulado...";
            else
                qDebug() << "[WARN] No se ha podido anular el elemento" << iframe.at(i).toOuterXml();*/

        /*}*/

        qDebug() << "[INFO] Anulando " << iF.toOuterXml();
        iF.setAttribute("src", "about:blank");

        //disconnect(webView, SIGNAL(loadFinished(bool)), this, SLOT(eliminarObject()));
    }
}

void MainWindow::comprobarDeNuevo()
{
    if(!getHayAnuncios())
    {
        putPaginaPtc1();
        putHayAnuncios(true);
        iniciarPTC();

    }
}

void MainWindow::volverPtc()
{
    if(getHayAnuncios())
    {
        qDebug() << "[INFO] Volviendo...";

        webView->load(getUrlVerAnuncios());

    }
}

void MainWindow::finalizarPTC()
{
    bool ptcFinalizado = false;

    //Esto es necesario cambiarlo si se quiere transladar a un vector
    if(url.getUrlPtc1() == url.getUrlPtc2())
        url.putUrlPtc1(url.getUrlPtc3());

    else if(url.getUrlPtc1() == url.getUrlPtc3())
        url.putUrlPtc1(url.getUrlPtc4());

    else if(url.getUrlPtc1() == url.getUrlPtc4())
    {
        ptcFinalizado = true;
        finalizarSistema();

    }
    else
        url.putUrlPtc1(url.getUrlPtc2());

    if(url.getUrlPtc1() == "" || url.getUrlPtc1() == "no")
    {
        ptcFinalizado = true;
        finalizarSistema();
    }

    if(!ptcFinalizado)
        iniciarPTC();

}

void MainWindow::finalizarSistema()
{
    url.putPtcFinalizado(true);
    putContUrlActual(getContUrlActual()+1);

    //Limpia todos los elementos que están en la caché
    //QWebSettings::clearIconDatabase();
    //QWebSettings::clearMemoryCaches();
    webView->page()->settings()->clearIconDatabase();
    webView->page()->settings()->clearMemoryCaches();
    webView->history()->clear();
    
    //Vuelve a cargar el siguiente PTR
    //QTimer::singleShot(tiempo.getClickCorreo(), this, SLOT(cargarConfig()));

}

void MainWindow::accionesBotones()
{
    connect(ui->actionIdentificar, SIGNAL(triggered()), this, SLOT(putIdentificacion()));
    connect(ui->actionVer_Anuncios, SIGNAL(triggered()), this, SLOT(putPaginaPtc1()));
    connect(ui->actionHacer_Click_a_los_anuncios, SIGNAL(triggered()), this, SLOT(putClickPtc()));
    connect(ui->actionHacer_Click_Punto_Rojo, SIGNAL(triggered()), this, SLOT(putClickPuntoRojo()));
    connect(ui->actionSiguiente_AdPrize, SIGNAL(triggered()), this, SLOT(siguienteAnuncio()));
    connect(ui->actionVer_variable_sVL, SIGNAL(triggered()), this, SLOT(mostrarVL()));
    //connect(ui->actionVolver, SIGNAL(triggered()), webView, SLOT(back()));
    //connect(ui->actionRenovar_WebView, SIGNAL(triggered()), this, SLOT(renovarWebKit()));
    connect(ui->actionRenovar_WebView, SIGNAL(triggered()), this, SLOT(comprobarDeNuevo()));

    connect(ui->actionCargar, SIGNAL(triggered()), this, SLOT(putPaginaLogin()));
    connect(ui->actionComod_n, SIGNAL(triggered()), this, SLOT(comodin()));

    connect(ui->actionBase, SIGNAL(triggered()), this, SLOT(putPaginaBase()));
    connect(ui->actionLogin, SIGNAL(triggered()), this, SLOT(putPaginaLogin()));
    connect(ui->actionEarnings, SIGNAL(triggered()), this, SLOT(putPaginaEarnings()));
    connect(ui->actionInbox, SIGNAL(triggered()), this, SLOT(putPaginaInbox()));
    connect(ui->actionPtc1, SIGNAL(triggered()), this, SLOT(putPaginaPtc1()));
    connect(ui->actionPtc2, SIGNAL(triggered()), this, SLOT(putPaginaPtc2()));
    connect(ui->actionPtc3, SIGNAL(triggered()), this, SLOT(putPaginaPtc3()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
