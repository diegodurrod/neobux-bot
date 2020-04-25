#ifndef VECTOR_H
#define VECTOR_H

#include <QString>

const int MAX_ELEMENTOS = 100;

class Vector
{
private:
    QString vectorElementos[MAX_ELEMENTOS];
    int numElementos;
    int puntero;
    bool estaVacio;
    bool estaLleno;

public:
    Vector();
    ~Vector();

    void putNumElementos(const int &numElementos_);
    void putPuntero(const int &puntero_);
    void putEstaLleno(const bool &estaLleno_);
    void putEstaVacio(const bool &estaVacio_);
    int getNumElementos() const;
    int getPuntero() const;
    bool getEstaLleno() const;
    bool getEstaVacio() const;

    bool insertarElemento(const QString &elemento);
    bool borrarElemento(const QString &elemento);
    QString primero() const;
    QString ultimo() const;
    QString elemento(const int &posicion) const;

};

#endif // VECTOR_H
