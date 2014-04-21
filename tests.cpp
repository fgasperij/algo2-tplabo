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

	int alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 5);
}

void check_alabar_a_messi_tres_elementos()
{
	Messineria<int> messi;
	int adepto1 = 1, adepto2 = 2, adepto3 = 3;
	
	messi.golDeMessi(adepto1);
	messi.golDeMessi(adepto2);
	messi.golDeMessi(adepto3);

	int alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 1);

	messi.alabarMessi();
	alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 2);

	messi.alabarMessi();
	alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 3);

	messi.alabarMessi();
	alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 1);	
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
	int alabando = messi.adeptoAlabando();
	ASSERT_EQ(alabando, 3);
}

int main() {	
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_agrega_un_elemento_correctamente);
  RUN_TEST(check_agrega_dos_elementos_correctamente);
  RUN_TEST(check_alabar_a_messi_tres_elementos);
  RUN_TEST(check_elimina_adepto_no_alabador);
  return 0;
}

