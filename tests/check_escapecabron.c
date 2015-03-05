#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <cacacomun.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <util.h>
#include <math.h>
#include "../src/escapecabron.h"

#define ERROR_MAXIMO 1E-6

static int *resultado_assestment = NULL;

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

		ck_assert_msg(resultado &&resultado-RESULTADO_ESPERADO< ERROR_MAXIMO,
				"verga, la velocidad max es %f", resultado);
	}END_TEST

#define NUM_FILAS  4
START_TEST( test_encuentra_escape_ultimo_exemplo)
	{
		const tipo_dato POSICION_INICIAL_BANDIDOS_DE_AMORES = 3;
		const tipo_dato POSICION_INICIAL_POLICIAS = 4;
		const tipo_dato VERTICES[NUM_FILAS][3] = {

		{ 1, 4, 1 },

		{ 1, 3, 4 },

		{ 3, 4, 10 },

		{ 2, 3, 30 }

		};
		const tipo_dato SALIDAS_A_CARRETERA[] = { 1, 2 };
		const float RESULTADO_ESPERADO = 137.142857143;

		float resultado = 0;

		caca_log_debug("video kill the radio star");

		/*
		 while (mierda) {
		 caca_log_debug("FFFFUUUUCCKKK");
		 }
		 */
		//			sleep(10);
		//		mierda=0;
		resultado = escape_cabron_encuentra_escape((void *) VERTICES, NUM_FILAS,
				POSICION_INICIAL_POLICIAS, POSICION_INICIAL_BANDIDOS_DE_AMORES,
				(tipo_dato *) SALIDAS_A_CARRETERA,
				sizeof(SALIDAS_A_CARRETERA) / sizeof(tipo_dato));
		caca_log_debug("velocidad maxima %f", resultado);

		ck_assert_msg(resultado && resultado-RESULTADO_ESPERADO< ERROR_MAXIMO,
				"verga, la velocidad max es %f", resultado);
	}END_TEST

#undef NUM_FILAS
#define NUM_FILAS  7
START_TEST(test_video_kill)
	{

		const char EOT[] = { 4, '\0' };
		const float VALOR_ESPERADO = 137.142857143;
		const char VALORES_ENTRADA[NUM_FILAS][10] = {

		{ "4 4 2\n" },

		{ "1 4 1\n" },

		{ "1 3 4\n" },

		{ "3 4 10\n" },

		{ "2 3 30\n" },

		{ "1 2\n" },

		{ "3 4\n" }

		};

		int ptyfd = 0;
		int pid = 0;

		float resultado_real = 0;

		printf("you were the last one \n");

		resultado_assestment = mmap(NULL, sizeof *resultado_assestment,
				PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

		printf("antes de forkear\n");
		pid = forkpty(&ptyfd, 0, 0, 0);
		if (pid < 0) {
			perror("forkpty no c pudo acer"), abort();
		}

		*resultado_assestment = -1;

		if (!pid) {
			resultado_real = escape_cabron_main();

			*resultado_assestment = fabsf(
					VALOR_ESPERADO - resultado_real) < ERROR_MAXIMO;

		} else {
			for (int i = 0; i < NUM_FILAS; i++) {
				printf("escribiendo esta mierda %s", *(VALORES_ENTRADA + i));
				write(ptyfd, *(VALORES_ENTRADA + i),
						strlen(*(VALORES_ENTRADA + i)));
			}
			write(ptyfd, EOT, 1);
		}

		if (pid) {
			while (*resultado_assestment < 0) {
				sleep(5);
			}
			printf("cerrando todo\n");
			close(ptyfd);
			ck_assert_msg(*resultado_assestment > 0, "Las matrices no son =s");
		} else {

		}
	}END_TEST

#undef NUM_FILAS
#define NUM_FILAS  33
START_TEST(test_radio_star)
	{

		const char EOT[] = { 4, '\0' };
		const float VALOR_ESPERADO = 0;
		const char VALORES_ENTRADA[NUM_FILAS][14] = {

		{ "30 30 5\n" },

		{ "1 2 1\n" },

		{ "2 3 1\n" },

		{ "3 25 100\n" },

		{ "4 3 1\n" },

		{ "5 3 1\n" },

		{ "6 3 1\n" },

		{ "7 3 1\n" },

		{ "8 3 1\n" },

		{ "9 3 1\n" },

		{ "10 3 452\n" },

		{ "11 3 1\n" },

		{ "12 3 1\n" },

		{ "13 3 1\n" },

		{ "14 3 1\n" },

		{ "15 3 1\n" },

		{ "16 3 1\n" },

		{ "17 3 1\n" },

		{ "18 3 1\n" },

		{ "19 3 5\n" },

		{ "20 3 1\n" },

		{ "21 3 1\n" },

		{ "22 3 1\n" },

		{ "23 3 1\n" },

		{ "24 3 1\n" },

		{ "25 4 1\n" },

		{ "26 3 1\n" },

		{ "27 3 1\n" },

		{ "28 3 1\n" },

		{ "29 3 1\n" },

		{ "30 3 100\n" },

		{ "3 6 9 12 15 \n" },

		{ "27 18\n" }

		};

		int ptyfd = 0;
		int pid = 0;

		float resultado_real = 0;

		printf("you were the last one \n");

		resultado_assestment = mmap(NULL, sizeof *resultado_assestment,
				PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

		printf("antes de forkear\n");
		pid = forkpty(&ptyfd, 0, 0, 0);
		printf("ya forkeo\n");
		if (pid < 0) {
			perror("forkpty no c pudo acer"), abort();
		}
		printf("si se izo pid\n");

		*resultado_assestment = -1;

		if (!pid) {
			printf("q pedo\n");
			resultado_real = escape_cabron_main();

			*resultado_assestment = fabsf(
					VALOR_ESPERADO - resultado_real) < ERROR_MAXIMO;

		} else {
			printf("me corto las pelotas\n");
			for (int i = 0; i < NUM_FILAS; i++) {
				printf("escribiendo esta mierda %s", *(VALORES_ENTRADA + i));
				write(ptyfd, *(VALORES_ENTRADA + i),
						strlen(*(VALORES_ENTRADA + i)));
			}
			write(ptyfd, EOT, 1);
		}

		if (pid) {
			while (*resultado_assestment < 0) {
				sleep(5);
			}
			printf("cerrando todo\n");
			close(ptyfd);
			ck_assert_msg(*resultado_assestment > 0, "Las matrices no son =s");
		} else {

		}
	}END_TEST

#undef NUM_FILAS
#define NUM_FILAS  33
START_TEST(test_stresar_salidas)
	{

		const char EOT[] = { 4, '\0' };
		const float VALOR_ESPERADO = 0;
		const char VALORES_ENTRADA[NUM_FILAS][29] = {

		{ "30 30 10\n" },

		{ "1 2 1\n" },

		{ "2 3 1\n" },

		{ "3 25 100\n" },

		{ "4 3 1\n" },

		{ "5 3 1\n" },

		{ "6 3 1\n" },

		{ "7 3 1\n" },

		{ "8 3 1\n" },

		{ "9 3 1\n" },

		{ "10 3 452\n" },

		{ "11 3 1\n" },

		{ "12 3 1\n" },

		{ "13 3 1\n" },

		{ "14 3 1\n" },

		{ "15 3 1\n" },

		{ "16 3 1\n" },

		{ "17 3 1\n" },

		{ "18 3 1\n" },

		{ "19 3 5\n" },

		{ "20 3 1\n" },

		{ "21 3 1\n" },

		{ "22 3 1\n" },

		{ "23 3 1\n" },

		{ "24 3 1\n" },

		{ "25 4 1\n" },

		{ "26 3 1\n" },

		{ "27 3 1\n" },

		{ "28 3 1\n" },

		{ "29 3 1\n" },

		{ "30 3 100\n" },

		{ "3 6 9 12 15 22 17 26 14 29\n" },

		{ "27 18\n" }

		};

		int ptyfd = 0;
		int pid = 0;

		float resultado_real = 0;

		printf("you were the last one \n");

		resultado_assestment = mmap(NULL, sizeof *resultado_assestment,
				PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

		printf("antes de forkear\n");
		pid = forkpty(&ptyfd, 0, 0, 0);
		printf("ya forkeo\n");
		if (pid < 0) {
			perror("forkpty no c pudo acer"), abort();
		}
		printf("si se izo pid\n");

		*resultado_assestment = -1;

		if (!pid) {
			printf("q pedo\n");
			resultado_real = escape_cabron_main();

			*resultado_assestment = fabsf(
					VALOR_ESPERADO - resultado_real) < ERROR_MAXIMO;

		} else {
			printf("me corto las pelotas\n");
			for (int i = 0; i < NUM_FILAS; i++) {
				printf("escribiendo esta mierda %s", *(VALORES_ENTRADA + i));
				write(ptyfd, *(VALORES_ENTRADA + i),
						strlen(*(VALORES_ENTRADA + i)));
			}
			write(ptyfd, EOT, 1);
		}

		if (pid) {
			while (*resultado_assestment < 0) {
				sleep(5);
			}
			printf("cerrando todo\n");
			close(ptyfd);
			ck_assert_msg(*resultado_assestment > 0, "Las matrices no son =s");
		} else {

		}
	}END_TEST

#undef NUM_FILAS
#define NUM_FILAS  35
START_TEST(test_stresar_salidas_viable)
	{

		const char EOT[] = { 4, '\0' };
		const float VALOR_ESPERADO = 150.857147;
		const char VALORES_ENTRADA[NUM_FILAS][29] = {

		{ "30 32 10\n" },

		{ "1 2 1\n" },

		{ "2 3 1\n" },

		{ "3 25 100\n" },

		{ "4 3 1\n" },

		{ "4 22 140\n" },

		{ "5 3 1\n" },

		{ "6 3 1\n" },

		{ "7 3 1\n" },

		{ "8 3 1\n" },

		{ "9 3 1\n" },

		{ "10 3 452\n" },

		{ "11 3 1\n" },

		{ "12 3 1\n" },

		{ "13 3 1\n" },

		{ "14 3 1\n" },

		{ "15 3 1\n" },

		{ "16 3 1\n" },

		{ "17 3 1\n" },

		{ "18 3 1\n" },

		{ "19 3 5\n" },

		{ "20 3 1\n" },

		{ "21 3 1\n" },

		{ "22 3 1\n" },

		{ "23 3 1\n" },

		{ "24 3 1\n" },

		{ "25 4 1\n" },

		{ "26 3 1\n" },

		{ "27 3 1\n" },

		{ "27 22 33\n" },

		{ "28 3 1\n" },

		{ "29 3 1\n" },

		{ "30 3 100\n" },

		{ "3 6 9 12 15 22 17 26 14 29\n" },

		{ "27 18\n" }

		};

		int ptyfd = 0;
		int pid = 0;

		float resultado_real = 0;

		printf("you were the last one \n");

		resultado_assestment = mmap(NULL, sizeof *resultado_assestment,
				PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

		printf("antes de forkear\n");
		pid = forkpty(&ptyfd, 0, 0, 0);
		printf("ya forkeo\n");
		if (pid < 0) {
			perror("forkpty no c pudo acer"), abort();
		}
		printf("si se izo pid\n");

		*resultado_assestment = -1;

		if (!pid) {
			printf("q pedo\n");
			resultado_real = escape_cabron_main();

			*resultado_assestment = fabsf(
					VALOR_ESPERADO - resultado_real) < ERROR_MAXIMO;

		} else {
			printf("me corto las pelotas\n");
			for (int i = 0; i < NUM_FILAS; i++) {
				printf("escribiendo esta mierda %s", *(VALORES_ENTRADA + i));
				write(ptyfd, *(VALORES_ENTRADA + i),
						strlen(*(VALORES_ENTRADA + i)));
			}
			write(ptyfd, EOT, 1);
		}

		if (pid) {
			while (*resultado_assestment < 0) {
				sleep(5);
			}
			printf("cerrando todo\n");
			close(ptyfd);
			ck_assert_msg(*resultado_assestment > 0, "Las matrices no son =s");
		} else {

		}
	}END_TEST

Suite *
escapecabron_suite(void) {
	Suite *s = suite_create("Escape de mierda");

	/* Core test case */
	TCase *tc_core = tcase_create("Core");
	tcase_set_timeout(tc_core, 600);
	tcase_add_test(tc_core, test_determina_nodos_viables);
	tcase_add_test(tc_core, test_determina_nodos_viables_caso_posible);
	tcase_add_test(tc_core, test_encuentra_escape_imposible);
	tcase_add_test(tc_core, test_encuentra_escape_posible);
	tcase_add_test(tc_core, test_encuentra_escape_ultimo_exemplo);
	tcase_add_test(tc_core, test_video_kill);
	/*
	*/
	tcase_add_test(tc_core, test_radio_star);
	tcase_add_test(tc_core, test_stresar_salidas);
	tcase_add_test(tc_core, test_stresar_salidas_viable);
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
