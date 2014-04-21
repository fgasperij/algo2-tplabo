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

	/**
	 * Buscar un adepto en la messineria
	 */ 
	const T& buscarAdepto(const T&) const;	 

	/*
	 * Aca va la implementación del adepto.
	 */
	struct nodoAdepto {
		T tAdepto;
		nodoAdepto* nAdPtr_Proximo;
		nodoAdepto* nAdPtr_Anterior;	
	};

	bool bElegido;
	nodoAdepto* nAdPtr_Elegido;
	nodoAdepto* nAdPtr_Alabando;



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
	nAdPtr_Alabando = NULL;
	bElegido = false;
	nAdPtr_Elegido = NULL;
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
	nodoAdepto* nAdPtr_NuevoAdepto = new (nodoAdepto);
	nAdPtr_NuevoAdepto->tAdepto = T (tNuevoAdepto);
	nodoAdepto* nAdPtr_agregarAtras = NULL;
	
	// if there's no follower
	if (nAdPtr_Alabando == NULL) {
		nAdPtr_Alabando = nAdPtr_NuevoAdepto;
		nAdPtr_NuevoAdepto->nAdPtr_Proximo = nAdPtr_NuevoAdepto;
		nAdPtr_NuevoAdepto->nAdPtr_Anterior = nAdPtr_NuevoAdepto;
		return;
	}

	if (bElegido) {
		nAdPtr_agregarAtras = nAdPtr_Elegido;
	} else {	
		nAdPtr_agregarAtras = nAdPtr_Alabando;
	}
	 
	nodoAdepto* nAdPtrAnteriorAgregarAtras = nAdPtr_agregarAtras->nAdPtr_Anterior;
	// new follower			
	nAdPtr_NuevoAdepto->nAdPtr_Proximo = nAdPtr_agregarAtras;
	nAdPtr_NuevoAdepto->nAdPtr_Anterior = nAdPtr_agregarAtras->nAdPtr_Anterior;			
	// previous current worshipper
	nAdPtrAnteriorAgregarAtras->nAdPtr_Proximo = nAdPtr_NuevoAdepto;
	// current worshipper
	nAdPtr_agregarAtras->nAdPtr_Anterior = nAdPtr_NuevoAdepto;
}
	
/*
 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
 */
template<class T>
void Messineria<T>::golDeCristiano(const T& sale) 
{
	T* salgo = this->buscarAdepto(sale);
}
template<class T>
const T& Messineria<T>::buscarAdepto(const T& sale) const
{
	// T* adeptoActual = new (T);
	// T* adeptoActual = this->alabando;
	// while (adeptoActual->adepto != sale) {
	// 	adeptoActual = adeptoAcual->proximo;
	// }

	// return adeptoActual;
}
	
/*
 * Devuelve el adepto que está albando.
 *
 * PRE: Hay adeptos en la Messineria.
 */
template<class T>
const T& Messineria<T>::adeptoAlabando() const
{
	return nAdPtr_Alabando->tAdepto;
}
	
/*
 * Devuelve el próximo elemento según el orden dado.
 * Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función
 * retornan distintos valores.
 *
 * PRE: Hay adeptos en la Messineria.
 */
template<class T>
const T& Messineria<T>::alabarMessi() {

}

/*
 * Cambia el turno de alabar al inmediato anterior.
 * 
 */
template<class T>
void Messineria<T>::olvideAlabarloUnPocoMas() {

}

/*
 * Selecciona al adepto que está alabando como el Elegido.
 *
 * PRE: Hay adeptos en la Messineria y no hay Elegido.
 */
template<class T>
void Messineria<T>::escogerElegido() {

}

/*
 * Indica si esta presente el Elegido entre los adeptos.
 */
template<class T>
bool Messineria<T>::hayElegido() const
{

}

/*
* Elimina de la secta al Elegido. 
*
* PRE: hay Elegido en la Messinería.
*/
template<class T>
void Messineria<T>::traidor() {

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
	if (this->nAdPtr_Alabando == NULL)
		return 0;

	// there's at least the one that is worshipping at the moment
	int tamanio = 1;
	nodoAdepto* nAdPtr_AdeptoActual = new (nodoAdepto);	
	nAdPtr_AdeptoActual = this->nAdPtr_Alabando;
	
	while (nAdPtr_AdeptoActual->nAdPtr_Proximo != this->nAdPtr_Alabando) {
		tamanio++;
		nAdPtr_AdeptoActual = nAdPtr_AdeptoActual->nAdPtr_Proximo;
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
