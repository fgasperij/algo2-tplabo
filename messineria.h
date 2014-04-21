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
	};

	/**
	 * Buscar un adepto en la messineria
	 */ 
	nodoAdepto* buscarAdepto(const T&);	 

	bool bElegido;
	nodoAdepto* ptrElegido;
	nodoAdepto* ptrAlabando;



};

template<class T>
ostream& operator<<(ostream& out, const Messineria<T>& a) {
	return a.mostrarMessineria(out);
}

/*
 * Crea una secta nueva sin adeptos.
 */	
template<class T>
Messineria<T>::Messineria() {
	ptrAlabando = NULL;
	bElegido = false;
	ptrElegido = NULL;
}

/*
 * Una vez copiada, ambas Messinerias deben ser independientes, 
 * es decir, cuando se borre una no debe borrar la otra.
 */	
template<class T>
Messineria<T>::Messineria(const Messineria<T>&) {

}
	
/*
 * Acordarse de liberar toda la memoria!
 */	 
template<class T>
Messineria<T>::~Messineria() {
}

/*
 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido 
 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso 
 * contrario, se arrodillará a la izquierda del que está alabando.
 */
template<class T>
void Messineria<T>::golDeMessi(const T& tNuevoAdepto)
{
	nodoAdepto* ptrNuevoAdepto = new (nodoAdepto);
	ptrNuevoAdepto->tAdepto = T (tNuevoAdepto);
	nodoAdepto* ptrAgregarAtras = NULL;
	
	// if there's no follower
	if (ptrAlabando == NULL) {
		ptrAlabando = ptrNuevoAdepto;
		ptrNuevoAdepto->ptrProximo = ptrNuevoAdepto;
		ptrNuevoAdepto->ptrAnterior = ptrNuevoAdepto;
		return;
	}

	if (bElegido) {
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
	while (ptrAdeptoActual->tAdepto != tSale) {
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
	ptrAlabando = ptrAlabando->ptrProximo;

	return ptrAlabando->tAdepto;
}

/*
 * Cambia el turno de alabar al inmediato anterior.
 * 
 */
template<class T>
void Messineria<T>::olvideAlabarloUnPocoMas() 
{
	ptrAlabando = ptrAlabando->ptrAnterior;
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
* Elimina de la secta al Elegido. 
*
* PRE: hay Elegido en la Messinería.
*/
template<class T>
void Messineria<T>::traidor() 
{

}

/*
* El Elegido interrumpe el tuno y pasa a ser el que está alabando
*
* PRE: hay Elegido en la Messinería.
*/
template<class T>
void Messineria<T>::interrumpirTurno() {

}

/*
 * Devuelve al Elegido. 
 *
 * PRE: Hay Elegido en la Messineria.
 */
template<class T>
const T& Messineria<T>::dameElegido() const
{

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
	nodoAdepto* ptrAdeptoActual = new (nodoAdepto);	
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
bool Messineria<T>::operator==(const Messineria<T>&) const
{

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
ostream& Messineria<T>::mostrarMessineria(ostream&) const
{

}




#endif //MESSINERIA_H_
