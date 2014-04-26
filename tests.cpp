// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() 
{
  Messineria<int> messi;

  ASSERT_EQ(messi.esVacia(), true);

  ASSERT_EQ(messi.tamanio(), 0);
}

void check_agrega_un_elemento_correctamente()
{
	Messineria<int> messi;
	int adepto = 5;
	messi.golDeMessi(adepto);

	ASSERT_EQ(messi.esVacia(), false);

	ASSERT_EQ(messi.tamanio(), 1);

	int alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 5);
}

void check_agrega_dos_elementos_correctamente()
{
	Messineria<int> messi;
	int adepto1 = 5, adepto2 = 8;
	
	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);

	ASSERT_EQ(messi.esVacia(), false);

	ASSERT_EQ(messi.tamanio(), 2);

	ASSERT_EQ(messi.adeptoAlabando(), 5);
}

void check_alabar_a_messi_tres_elementos()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;
	
	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	ASSERT_EQ(messi.adeptoAlabando(), 1);

	messi.alabarMessi();
	ASSERT_EQ(messi.adeptoAlabando(), 2);

	messi.alabarMessi();
	ASSERT_EQ(messi.adeptoAlabando(), 3);

	messi.alabarMessi();
	ASSERT_EQ(messi.adeptoAlabando(), 1);	
}

void check_elimina_adepto_no_alabador()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;
	
	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	ASSERT_EQ(messi.tamanio(), 3);

	messi.golDeCristiano(adepto2);

	ASSERT_EQ(messi.tamanio(), 2);

	messi.alabarMessi();
	ASSERT_EQ(messi.adeptoAlabando(), 3);
}

void check_elimina_adepto_alabador()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;
	
	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	ASSERT_EQ(messi.tamanio(), 3);

	messi.golDeCristiano(adepto1);

	ASSERT_EQ(messi.tamanio(), 2);

	ASSERT_EQ(messi.adeptoAlabando(), 2);

	messi.alabarMessi();
	ASSERT_EQ(messi.adeptoAlabando(), 3);
}

void check_olvide_alabarlo_un_poco_mas()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	messi.alabarMessi();

	ASSERT_EQ(messi.adeptoAlabando(), 2);

	messi.olvideAlabarloUnPocoMas();

	ASSERT_EQ(messi.adeptoAlabando(), 1);	
}

void check_escoger_elegido()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	ASSERT_EQ(messi.hayElegido(), false);

	messi.escogerElegido();

	ASSERT_EQ(messi.hayElegido(), true);	
}

void check_dame_elegido()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	messi.escogerElegido();

	ASSERT_EQ(messi.dameElegido(), 1);

	messi.alabarMessi();
	messi.escogerElegido();
	ASSERT_EQ(messi.dameElegido(), 2);

	messi.alabarMessi();
	messi.escogerElegido();
	ASSERT_EQ(messi.dameElegido(), 3);	
}

void check_traidor()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	messi.escogerElegido();
	messi.traidor();

	ASSERT_EQ(messi.tamanio(), 2);
	ASSERT_EQ(messi.hayElegido(), false);
	ASSERT_EQ(messi.adeptoAlabando(), 2);
}

void check_interrumpir_turno()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	messi.alabarMessi(); // alabando = 2
	messi.escogerElegido(); // elegido = 2
	messi.alabarMessi(); // alabando = 3
	messi.interrumpirTurno();

	ASSERT_EQ(messi.adeptoAlabando(), 2);
}

void check_mostrar_messineria()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);
		
	cout << messi << endl;
	
	messi.escogerElegido();
	
	cout << messi << endl;
	
	messi.alabarMessi();
	
	cout << messi << endl;
}

void check_constructor_por_copia()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3, adepto4 = 4;

	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);
	messi.golDeMessi(adepto4);
	messi.escogerElegido();
	
	Messineria<int> messiCopiado (messi);
	
	cout << messi << endl;
	cout << messiCopiado << endl;
}

void check_messineria_de_messinerias()
{
	cout << endl;
	
	Messineria<int> messi1;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3, adepto4 = 4;
	messi1.golDeMessi(adepto1);
	messi1.golDeMessi(adepto2);	
	messi1.golDeMessi(adepto3);
	messi1.golDeMessi(adepto4);
	messi1.escogerElegido();
	
	cout << "messi1 " <<  messi1 << endl;
	
	Messineria<int> messi2;
	adepto1 = 5;
	messi2.golDeMessi(adepto1);
	messi2.golDeMessi(adepto2);
	messi2.golDeMessi(adepto3);
	messi2.golDeMessi(adepto4);
	messi2.alabarMessi();
	messi2.escogerElegido();
	
	cout << "messi2 " << messi2 << endl;
	
	Messineria<int> messi3;
	adepto1 = 8;
	messi3.golDeMessi(adepto1);
	messi3.golDeMessi(adepto2);
	messi3.golDeMessi(adepto3);
	messi3.golDeMessi(adepto4);	
	
	cout << "messi3 " << messi3 << endl;
	
	Messineria<Messineria<int> > messiDeMessis;		
	messiDeMessis.golDeMessi(messi1);	
	messiDeMessis.golDeMessi(messi2);
	messiDeMessis.golDeMessi(messi3);	
	messiDeMessis.escogerElegido();
	
	cout << "messiDeMessis " << messiDeMessis << endl;
	
	// Messineria<Messineria<int> > messiDeMessis2 (messiDeMessis);
	
	// cout << "messiDeMessis2 " << messiDeMessis2 << endl;
	
	// messiDeMessis2.golDeCristiano(messi1);
	Messineria<int> messi4;
	// messiDeMessis2.golDeMessi(messi4);
	
	// cout << messiDeMessis2 << endl;
	cout << messiDeMessis << endl;
}

void check_operator_igual_igual ()
{
	Messineria<int> messi1;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3, adepto4 = 4;
	messi1.golDeMessi(adepto1);
	messi1.golDeMessi(adepto2);	
	messi1.golDeMessi(adepto3);
	messi1.golDeMessi(adepto4);
	messi1.escogerElegido();
	
	cout << "messi1 " <<  messi1 << endl;
	
	Messineria<int> messi2;
	messi2.golDeMessi(adepto1);
	messi2.golDeMessi(adepto2);
	messi2.golDeMessi(adepto3);
	messi2.golDeMessi(adepto4);
	messi2.alabarMessi();
	messi2.escogerElegido();
	messi2.alabarMessi();
	messi2.alabarMessi();
	messi2.alabarMessi();
	
	cout << "messi2 " << messi2 << endl;
	
	bool sonIguales = (messi1 == messi2);	
	cout << "Son iguales: " << sonIguales << endl;
}

void check_operator_igual_igual_interrumpir()
{
	Messineria<int> messi1;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3, adepto4 = 4;
	messi1.golDeMessi(adepto1);
	messi1.golDeMessi(adepto2);	
	messi1.golDeMessi(adepto3);
	messi1.golDeMessi(adepto4);
	messi1.escogerElegido();
	
	cout << "messi1 " <<  messi1 << endl;
	
	Messineria<int> messi2;
	messi2.golDeMessi(adepto1);
	messi2.golDeMessi(adepto2);
	messi2.golDeMessi(adepto3);
	messi2.golDeMessi(adepto4);
	messi2.escogerElegido();
	messi2.alabarMessi();
	messi2.interrumpirTurno();
	
	cout << "messi2 " << messi2 << endl;
	
	bool sonIguales = (messi1 == messi2);	
	cout << "Son iguales: " << sonIguales << endl;
}

int main() {	
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_agrega_un_elemento_correctamente);  
  RUN_TEST(check_agrega_dos_elementos_correctamente);
  RUN_TEST(check_alabar_a_messi_tres_elementos);
  RUN_TEST(check_elimina_adepto_no_alabador);
  RUN_TEST(check_elimina_adepto_alabador);
  RUN_TEST(check_olvide_alabarlo_un_poco_mas);
  RUN_TEST(check_escoger_elegido);
  RUN_TEST(check_dame_elegido);
  RUN_TEST(check_traidor);
  RUN_TEST(check_interrumpir_turno);
  RUN_TEST(check_mostrar_messineria);
  RUN_TEST(check_constructor_por_copia);
  RUN_TEST(check_messineria_de_messinerias);
  RUN_TEST(check_operator_igual_igual);
  RUN_TEST(check_operator_igual_igual_interrumpir);

  return 0;
}
