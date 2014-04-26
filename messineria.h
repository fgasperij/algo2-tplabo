#ifndef MESSINERIA_H_
#define MESSINERIA_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class Messineria {

  public:

	/*
	 * Crea una secta nueva sin adeptos.
	 */	
	Messineria();

	/*
	 * Una vez copiada, ambas Messinerias deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	Messineria(const Messineria<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~Messineria();

	/*
	 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido 
	 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso 
	 * contrario, se arrodillará a la izquierda del que está alabando.
	 */
	void golDeMessi(const T&);
	
	/*
	 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
	 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
	 */
	void golDeCristiano(const T&);
	
	/*
	 * Devuelve el adepto que está albando.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& adeptoAlabando() const;
	
    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función
	 * retornan distintos valores.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& alabarMessi();
	
	/*
	 * Cambia el turno de alabar al inmediato anterior.
	 * 
	 */
	void olvideAlabarloUnPocoMas();
	
	/*
	 * Selecciona al adepto que está alabando como el Elegido.
	 *
	 * PRE: Hay adeptos en la Messineria y no hay Elegido.
	 */
	void escogerElegido();
	
    /*
	 * Indica si esta presente el Elegido entre los adeptos.
	 */
	bool hayElegido() const;
	
	/*
	* Elimina de la secta al Elegido. 
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void traidor();
	
	/*
	* El Elegido interrumpe el tuno y pasa a ser el que está alabando
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void interrumpirTurno();
	
	/*
	 * Devuelve al Elegido. 
	 *
	 * PRE: Hay Elegido en la Messineria.
	 */
	const T& dameElegido() const;	

	/*
	 * Dice si la Messineria tiene o no adeptos.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de adeptos a la Messineria.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las Messinerias son iguales.
	 */
	bool operator==(const Messineria<T>&) const;	
	
	/*
	 * Debe mostrar la ronda por el ostream (y retornar el mismo).
	 * Messineria vacio: []
	 * Messineria con 2 elementos (e1 es el actual): [e1, e2]
	 * Messineria con 2 elementos (e2 es el actual y e1 es el Elegido): [e2, e1*]
	 * Messineria con 3 elementos (e1 es el actual, e2 fue agregado antes que e3, 
	 * e1 fue agregado antes que e2): [e1, e2, e3]
	 */
	ostream& mostrarMessineria(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Messineria<T>& operator=(const Messineria<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del adepto.
	 */
	struct nodoAdepto {		
		T tAdepto;
		nodoAdepto* ptrProximo;
		nodoAdepto* ptrAnterior;
		
		nodoAdepto(const T& adepto) : tAdepto (adepto), ptrProximo (NULL), ptrAnterior (NULL)
		{}
	};

	bool bElegido;
	nodoAdepto* ptrElegido;
	nodoAdepto* ptrAlabando;
	bool bInterrumpido;
	nodoAdepto* ptrInterrumpido;

	/**
	 * Buscar un adepto en la messineria
	 */ 
	nodoAdepto* buscarAdepto(const T&);

	void reset();

	bool hayInterrumpido() const;

};

template<class T>
ostream& operator<<(ostream& out, const Messineria<T>& a) {
	return a.mostrarMessineria(out);
}

template<class T>
void Messineria<T>::reset()
{
	bElegido = false;
	bInterrumpido = false;
	ptrInterrumpido = NULL;
	ptrElegido = NULL;
	ptrAlabando = NULL;
}

/*
 * Crea una secta nueva sin adeptos.
 */	
template<class T>
Messineria<T>::Messineria() 
{
	reset();
}

/*
 * Una vez copiada, ambas Messinerias deben ser independientes, 
 * es decir, cuando se borre una no debe borrar la otra.
 */	
template<class T>
Messineria<T>::Messineria(const Messineria<T>& other) 
{
	if (other.esVacia()) {
		reset();
		return;
	}

	ptrAlabando = new nodoAdepto (other.adeptoAlabando());

	if (other.tamanio() == 1) {
		ptrAlabando->ptrProximo = ptrAlabando;
		ptrAlabando->ptrAnterior = ptrAlabando;	

		if (other.hayElegido()) {
			bElegido = true;
			ptrElegido = ptrAlabando;
		}

		if (other.hayInterrumpido()) {
			bInterrumpido = true;
			ptrInterrumpido = ptrAlabando;
		}			

		return;
	}

	if (other.hayElegido()) {
		bElegido = true; 
	} else {
		bElegido = false;
	}

	if (other.hayInterrumpido()) {
		bInterrumpido = true; 
	} else {
		bInterrumpido = false;
	}

	nodoAdepto* ptrActualThis;
	nodoAdepto* ptrAnteriorThis = ptrAlabando;
	nodoAdepto* ptrActualOther = other.ptrAlabando->ptrProximo;

	while (ptrActualOther != other.ptrAlabando) {
	    ptrActualThis = new nodoAdepto (ptrActualOther->tAdepto);
	    ptrActualThis->ptrAnterior = ptrAnteriorThis;

	    ptrAnteriorThis->ptrProximo = ptrActualThis;

	    if (other.hayElegido() && other.ptrElegido == ptrActualOther)
	    	ptrElegido = ptrActualThis;

	    if (other.hayInterrumpido() && other.ptrInterrumpido == ptrActualOther)
	    	ptrInterrumpido = ptrActualThis;

	    ptrAnteriorThis = ptrActualThis;
	    ptrActualOther = ptrActualOther->ptrProximo;
	}

	ptrActualThis->ptrProximo = ptrAlabando;
	ptrAlabando->ptrAnterior = ptrActualThis;

	if (other.hayElegido() && other.ptrElegido == other.ptrAlabando)
	    	ptrElegido = ptrAlabando;

    if (other.hayInterrumpido() && other.ptrInterrumpido == ptrAlabando)
    	ptrInterrumpido = ptrAlabando;
}
	
/*
 * Acordarse de liberar toda la memoria!
 */	 
template<class T>
Messineria<T>::~Messineria() 
{
	if (this->esVacia())
		return;

	nodoAdepto* ptrNodoActual = ptrAlabando;
	nodoAdepto* ptrTemporario;
	
	if (tamanio() == 1) {
		delete ptrAlabando;
		return;
	}
	
	ptrNodoActual = ptrAlabando->ptrProximo;
	delete ptrAlabando;

	while (ptrNodoActual != ptrAlabando) {
		ptrTemporario = ptrNodoActual->ptrProximo;
		delete ptrNodoActual;
		ptrNodoActual = ptrTemporario;
	}
}

/*
 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido 
 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso 
 * contrario, se arrodillará a la izquierda del que está alabando.
 */
template<class T>
void Messineria<T>::golDeMessi(const T& tNuevoAdepto)
{
	nodoAdepto* ptrNuevoAdepto = new nodoAdepto (tNuevoAdepto);	
	
	// if there's no follower
	if (esVacia()) {
		ptrAlabando = ptrNuevoAdepto;
		ptrNuevoAdepto->ptrProximo = ptrNuevoAdepto;
		ptrNuevoAdepto->ptrAnterior = ptrNuevoAdepto;
		return;
	}
	
	nodoAdepto* ptrAgregarAtras = NULL;
	if (hayElegido()) {
		ptrAgregarAtras = ptrElegido;
	} else {	
		ptrAgregarAtras = ptrAlabando;
	}
	 
	nodoAdepto* ptrAnteriorAgregarAtras = ptrAgregarAtras->ptrAnterior;
	// new follower			
	ptrNuevoAdepto->ptrProximo = ptrAgregarAtras;
	ptrNuevoAdepto->ptrAnterior = ptrAgregarAtras->ptrAnterior;			
	// previous current worshipper
	ptrAnteriorAgregarAtras->ptrProximo = ptrNuevoAdepto;
	// current worshipper
	ptrAgregarAtras->ptrAnterior = ptrNuevoAdepto;
}
	
/*
 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
 */
template<class T>
void Messineria<T>::golDeCristiano(const T& tSale) 
{
	nodoAdepto* ptrSale = buscarAdepto(tSale);

	if (this->tamanio() == 1) {
		delete ptrSale;
		ptrAlabando = NULL;
		bElegido = false;
		ptrElegido = NULL;

		return;
	}

	if (ptrAlabando == ptrSale) {
		this->alabarMessi();
	}

	if (ptrElegido == ptrSale) {
		bElegido = false;
		ptrElegido = NULL;
	}
	
	if (ptrInterrumpido == ptrSale) {
		bInterrumpido = false;
		ptrInterrumpido = NULL;
	}
	
	nodoAdepto* ptrAnteriorSale = ptrSale->ptrAnterior;
	nodoAdepto* ptrProximoSale = ptrSale->ptrProximo;	
	
	ptrAnteriorSale->ptrProximo = ptrSale->ptrProximo;
	ptrProximoSale->ptrAnterior = ptrSale->ptrAnterior;

	delete ptrSale; 
}

template<class T>
typename Messineria<T>::nodoAdepto* Messineria<T>::buscarAdepto(const T& tSale)
{
	nodoAdepto* ptrAdeptoActual = ptrAlabando;	
	while (!(ptrAdeptoActual->tAdepto == tSale)) {
		ptrAdeptoActual = ptrAdeptoActual->ptrProximo;
	}

	return ptrAdeptoActual;
}
	
/*
 * Devuelve el adepto que está albando.
 *
 * PRE: Hay adeptos en la Messineria.
 */
template<class T>
const T& Messineria<T>::adeptoAlabando() const
{
	return ptrAlabando->tAdepto;
}
	
/*
 * Devuelve el próximo elemento según el orden dado.
 * Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función
 * retornan distintos valores.
 *
 * PRE: Hay adeptos en la Messineria.
 */
template<class T>
const T& Messineria<T>::alabarMessi() 
{
	if (bInterrumpido) {
		ptrAlabando = ptrInterrumpido;
		bInterrumpido = false;
		ptrInterrumpido = NULL;
	} else {
		ptrAlabando = ptrAlabando->ptrProximo;
	}		

	return ptrAlabando->tAdepto;
}

/*
 * Cambia el turno de alabar al inmediato anterior.
 * 
 */
template<class T>
void Messineria<T>::olvideAlabarloUnPocoMas() 
{
	if (bInterrumpido) {
		ptrAlabando = ptrInterrumpido;
		bInterrumpido = false;
		ptrInterrumpido = NULL;
	} else {
		ptrAlabando = ptrAlabando->ptrAnterior;
	}
	
}

/*
 * Selecciona al adepto que está alabando como el Elegido.
 *
 * PRE: Hay adeptos en la Messineria y no hay Elegido.
 */
template<class T>
void Messineria<T>::escogerElegido() 
{
	bElegido = true;
	ptrElegido = ptrAlabando;
}

/*
 * Indica si esta presente el Elegido entre los adeptos.
 */
template<class T>
bool Messineria<T>::hayElegido() const
{
	return bElegido;
}

/*
 * Indica si esta presente el Interrumpido entre los adeptos.
 */
template<class T>
bool Messineria<T>::hayInterrumpido() const
{
	return bInterrumpido;
}

/*
* Elimina de la secta al Elegido. 
*
* PRE: hay Elegido en la Messinería.
*/
template<class T>
void Messineria<T>::traidor() 
{
	golDeCristiano(ptrElegido->tAdepto);
}

/*
* El Elegido interrumpe el turno y pasa a ser el que está alabando
*
* PRE: hay Elegido en la Messinería.
*/
template<class T>
void Messineria<T>::interrumpirTurno() 
{
	assert(bElegido);

	ptrInterrumpido = ptrAlabando;
	bInterrumpido = true;
	ptrAlabando = ptrElegido;
}

/*
 * Devuelve al Elegido. 
 *
 * PRE: Hay Elegido en la Messineria.
 */
template<class T>
const T& Messineria<T>::dameElegido() const
{
	return ptrElegido->tAdepto;
}	

/*
 * Dice si la Messineria tiene o no adeptos.
 */
template<class T>
bool Messineria<T>::esVacia() const
{
		return this->tamanio() == 0;
}

/*
 * Devuelve la cantidad de adeptos a la Messineria.
 */
template<class T>
int Messineria<T>::tamanio() const
{
	// there's always a follower worshipping
	if (this->ptrAlabando == NULL)
		return 0;

	// there's at least the one that is worshipping at the moment
	int tamanio = 1;
	nodoAdepto* ptrAdeptoActual;	
	ptrAdeptoActual = this->ptrAlabando;
	
	while (ptrAdeptoActual->ptrProximo != this->ptrAlabando) {
		tamanio++;
		ptrAdeptoActual = ptrAdeptoActual->ptrProximo;
	}

	return tamanio;
}

/*
 * Devuelve true si las Messinerias son iguales.
 */
template<class T>
bool Messineria<T>::operator==(const Messineria<T>& other) const
{
	if ( other.esVacia() != esVacia() || 
		 other.hayElegido() != hayElegido() ||
		 other.tamanio() != tamanio() ||
		 other.bInterrumpido != bInterrumpido )
		return false;

	if (esVacia())
		return true;

	nodoAdepto* ptrNodoActual = ptrAlabando->ptrProximo;
	nodoAdepto* ptrOtherNodoActual = other.ptrAlabando;
	ptrOtherNodoActual = ptrOtherNodoActual->ptrProximo;
	
	if (hayElegido()) {
		if ( !(ptrElegido->tAdepto == other.ptrElegido->tAdepto) ) return false;
	}
	
	if (bInterrumpido) {	
		if ( !(ptrInterrumpido->tAdepto == other.ptrInterrumpido->tAdepto) ) {
			return false;
		}
	}	

	while (ptrNodoActual != ptrAlabando) {
		if (ptrNodoActual->tAdepto != ptrOtherNodoActual->tAdepto)
			return false;

		ptrNodoActual = ptrNodoActual->ptrProximo;
		ptrOtherNodoActual = ptrOtherNodoActual->ptrProximo;
	}

	if (ptrAlabando->tAdepto == other.ptrAlabando->tAdepto)
		return true;
}	

/*
 * Debe mostrar la ronda por el ostream (y retornar el mismo).
 * Messineria vacio: []
 * Messineria con 2 elementos (e1 es el actual): [e1, e2]
 * Messineria con 2 elementos (e2 es el actual y e1 es el Elegido): [e2, e1*]
 * Messineria con 3 elementos (e1 es el actual, e2 fue agregado antes que e3, 
 * e1 fue agregado antes que e2): [e1, e2, e3]
 */
template<class T>
ostream& Messineria<T>::mostrarMessineria(ostream& outStream) const
{
	nodoAdepto* ptrNodoActual = ptrAlabando;
		
	outStream << "[";
	for(int i = 0; i < this->tamanio(); i++) {
		outStream << ptrNodoActual->tAdepto;
		
		if (bElegido && ptrNodoActual == ptrElegido) outStream << "*";
		
		if ( i != (this->tamanio() - 1) ) outStream << ", ";
		
		ptrNodoActual = ptrNodoActual->ptrProximo;
	}
	outStream << "]";

	return outStream;
}




#endif //MESSINERIA_H_
