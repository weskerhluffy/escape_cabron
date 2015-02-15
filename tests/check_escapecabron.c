#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <cacacomun.h>
#include "../src/escapecabron.h"

#define ERROR_MAXIMO 1E-6

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
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES,
				NULL );

		grafo_get_representacion_en_matriz_ordenada(&grafo_viable_ctx,
				resultado_real, 1);

		resultado = (nodos_viables_calculados == 2)
				&& !memcmp(RESULTADO_ESPERADO, resultado_real,
						4 * (sizeof(tipo_dato)));

		ck_assert_msg(resultado, "verga, la matrix es %d", resultado_real);
	}END_TEST

START_TEST( test_determina_nodos_viables_caso_posible)
	{
		const tipo_dato POSICION_INICIAL_BANDIDOS_DE_AMORES = 2;
		const tipo_dato POSICION_INICIAL_POLICIAS = 3;
		const tipo_dato VERTICES[2][3] = { { 1, 2, 7 }, { 2, 3, 8 } };
		const tipo_dato RESULTADO_ESPERADO[] = { 1, 1, 2, 2 };

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
		//		mierda=0;
		nodos_viables_calculados = escape_cabron_determina_nodos_viables(
				(void *) VERTICES, 2, &grafo_viable_ctx,
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES,
				NULL );

		grafo_get_representacion_en_matriz_ordenada(&grafo_viable_ctx,
				resultado_real, 1);

		resultado = (nodos_viables_calculados == 2)
				&& !memcmp(RESULTADO_ESPERADO, resultado_real,
						4 * (sizeof(tipo_dato)));

		ck_assert_msg(resultado, "verga, la matrix es %d", resultado_real);
	}END_TEST

START_TEST( test_encuentra_escape_imposible)
	{
		const tipo_dato POSICION_INICIAL_BANDIDOS_DE_AMORES = 3;
		const tipo_dato POSICION_INICIAL_POLICIAS = 2;
		const tipo_dato VERTICES[2][3] = { { 1, 2, 7 }, { 2, 3, 8 } };
		const tipo_dato SALIDAS_A_CARRETERA[] = { 1 };

		float resultado = 0;

		caca_log_debug("me kiero cortar los webos");

		/*
		 while (mierda) {
		 caca_log_debug("FFFFUUUUCCKKK");
		 }
		 */
		//			sleep(10);
		//		mierda=0;
		resultado = escape_cabron_encuentra_escape((void *) VERTICES, 2,
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES,
				(tipo_dato *) SALIDAS_A_CARRETERA, 1);

		ck_assert_msg(!resultado, "verga, la velocidad max es %f", resultado);
	}END_TEST

START_TEST( test_encuentra_escape_posible)
	{
		const tipo_dato POSICION_INICIAL_BANDIDOS_DE_AMORES = 2;
		const tipo_dato POSICION_INICIAL_POLICIAS = 3;
		const tipo_dato VERTICES[2][3] = { { 1, 2, 7 }, { 2, 3, 8 } };
		const tipo_dato SALIDAS_A_CARRETERA[] = { 1 };
		const float RESULTADO_ESPERADO = 74.6666666667;

		float resultado = 0;

		caca_log_debug("me kiero cortar los webos");

		/*
		 while (mierda) {
		 caca_log_debug("FFFFUUUUCCKKK");
		 }
		 */
		//			sleep(10);
		//		mierda=0;
		resultado = escape_cabron_encuentra_escape((void *) VERTICES, 2,
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES,
				(tipo_dato *) SALIDAS_A_CARRETERA, 1);
		caca_log_debug("velocidad maxima %f", resultado);

		ck_assert_msg(resultado-RESULTADO_ESPERADO< ERROR_MAXIMO,
				"verga, la velocidad max es %f", resultado);
	}END_TEST

Suite *
escapecabron_suite(void) {
	Suite *s = suite_create("Unos locos");

	/* Core test case */
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_determina_nodos_viables);
	tcase_add_test(tc_core, test_determina_nodos_viables_caso_posible);
	/*
	 */
	tcase_add_test(tc_core, test_encuentra_escape_imposible);
	tcase_add_test(tc_core, test_encuentra_escape_posible);
	/*
	 */

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
