#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <cacacomun.h>
#include "../src/escapecabron.h"

START_TEST( test_determina_nodos_viables)
	{
		const tipo_dato POSICION_INICIAL_BANDIDOS_DE_AMORES = 3;
		const tipo_dato POSICION_INICIAL_POLICIAS = 2;
		const tipo_dato VERTICES[2][3] = { { 1, 2, 7 }, { 2, 3, 8 } };
		const tipo_dato RESULTADO_ESPERADO[] = { 1, 1, 3, 3 };

		bool resultado = falso;
		int nodos_viables_calculados = 0;
		tipo_dato resultado_real[4] = { 0 };

		grafo_contexto grafo_viable_ctx;

		caca_log_debug("me corto las pelotas");

		/*
		 while (mierda) {
		 caca_log_debug("FFFFUUUUCCKKK");
		 }
		 */
//			sleep(10);
//		mierda=0;
		nodos_viables_calculados = escape_cabron_determina_nodos_viables(
				(void *) VERTICES, 2, &grafo_viable_ctx,
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES);

		grafo_get_representacion_en_matriz_ordenada(&grafo_viable_ctx,
				resultado_real, 1);

		resultado = (nodos_viables_calculados == 2)
				&& !memcmp(RESULTADO_ESPERADO, resultado_real, 4*(sizeof(tipo_dato)));

		ck_assert_msg(resultado, "verga, la matrix es %d", resultado_real);
	}END_TEST

Suite *
escapecabron_suite(void) {
	Suite *s = suite_create("Unos locos");

	/* Core test case */
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_determina_nodos_viables);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s = escapecabron_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
