// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() {
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

int main() {	
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_agrega_un_elemento_correctamente);
  RUN_TEST(check_agrega_dos_elementos_correctamente);
  return 0;
}

