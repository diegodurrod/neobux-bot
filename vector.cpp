#include "vector.h"

Vector::Vector()
{
    numElementos = 0;
    puntero = 0;
    estaVacio = true;
    estaLleno = false;

}

void Vector::putNumElementos(const int &numElementos_)
{
    numElementos = numElementos_;

}

void Vector::putPuntero(const int &puntero_)
{
    puntero = puntero_;

}

void Vector::putEstaLleno(const bool &estaLleno_)
{
    estaLleno = estaLleno_;

}

void Vector::putEstaVacio(const bool &estaVacio_)
{
    estaVacio = estaVacio_;

}

int Vector::getNumElementos() const
{
    return numElementos;

}

int Vector::getPuntero() const
{
    return puntero;

}

bool Vector::getEstaLleno() const
{
    bool lleno = false;

    if(numElementos == MAX_ELEMENTOS-1)
        lleno = true;

    return lleno;

}

bool Vector::getEstaVacio() const
{
    bool vacio = false;

    if(numElementos == 0)
        vacio = true;

    return vacio;

}

bool Vector::insertarElemento(const QString &elemento)
{
    bool insertado = false;

    if(numElementos != MAX_ELEMENTOS-1)
    {
        vectorElementos[numElementos] = elemento;
        numElementos = numElementos + 1;

        insertado = true;

    }

    return insertado;

}

//Faltaría por implementar este método...
bool Vector::borrarElemento(const QString &elemento)
{
    QString aux;
    bool borrado = false;
    int i = 0;
    int j = 0;

    for(i=0;i<=numElementos;i++)
    {
        if(vectorElementos[i] == elemento)
        {
            borrado = true;
            for(j=i;j<numElementos;j++)
                vectorElementos[j]=vectorElementos[j+1];

        }
    }

    return borrado;

}

QString Vector::primero() const
{
    QString salida = "Vector vacío";

    if(numElementos != 0)
        salida = vectorElementos[0];

    return salida;

}

QString Vector::ultimo() const
{
    QString salida = "Vector vacío";

    if(numElementos != 0)
        salida = vectorElementos[numElementos];

    return salida;

}

QString Vector::elemento(const int &posicion) const
{
    QString salida = "Vector vacío";

    if(numElementos != 0)
        if(posicion >= 0 && posicion <= numElementos)
            salida = vectorElementos[posicion];

    return salida;

}

Vector::~Vector()
{

}
