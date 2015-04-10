/*
 ============================================================================
 Name        : escape_cabron.c
 Author      : ernesto
 Version     :
 Copyright   : Your copyright notice
 Description : Era un bandido tan pervertido...
 ============================================================================
 */

#include<config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#ifdef HAVE_EXECINFO_H
#	include <execinfo.h>
#endif
#include <cacacomun.h>
#include "escapecabron.h"

int escape_cabron_determina_nodos_viables(void *matrix_aristas, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial) {

	int num_nodos = 0;
	int contador_nodos_ruta_maldita = 0;
	int contador_nodos_recorridos = 0;
	tipo_dato ancestro_actual = 0;
	grafo_contexto grafo_inicial_ctx;

	char *buffer = NULL;
	tipo_dato *distancias_minimas = NULL, *antecesores = NULL;
	tipo_dato *ruta_maldita;

	buffer = malloc(MAX_TAM_CADENA * sizeof(char));

	num_nodos = init_grafo(matrix_aristas, num_filas, &grafo_inicial_ctx, falso,
			verdadero);

	distancias_minimas = calloc(num_nodos + 1, sizeof(tipo_dato));
	if (!distancias_minimas) {
		perror("no se consigio memoria para distancias");
		exit(EXIT_FAILURE);
	}
	antecesores = calloc(num_nodos + 1, sizeof(tipo_dato));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		exit(EXIT_FAILURE);
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos + 1) * sizeof(tipo_dato));
	ruta_maldita = calloc(num_nodos + 1, sizeof(tipo_dato));
	caca_log_debug("lo q c regreso para ruta_maldita %p", ruta_maldita);
	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(EXIT_FAILURE);
	}

	caca_log_debug("llamando a dijkstra");
	dijkstra_main(NULL, 0, posicion_incomoda, posicion_inicial,
			&grafo_inicial_ctx, distancias_minimas, antecesores);

	caca_log_debug("las distancias minimas son: %s",
			caca_arreglo_a_cadena(distancias_minimas, num_nodos + 1, buffer));

	caca_log_debug("los antecesores son: %s",
			caca_arreglo_a_cadena(antecesores, num_nodos + 1, buffer));

	caca_log_debug("sacando la ruta maldita");
	*(ruta_maldita + contador_nodos_ruta_maldita++) = posicion_inicial;

	while (*(ruta_maldita + contador_nodos_ruta_maldita) != posicion_incomoda
			&& contador_nodos_recorridos < num_nodos + 1) {
		ancestro_actual = *(antecesores
				+ *(ruta_maldita + contador_nodos_ruta_maldita - 1));
		caca_log_debug("ancestro actual %ld en %d", ancestro_actual,
				contador_nodos_ruta_maldita);
		if (ancestro_actual != 0) {
			*(ruta_maldita + contador_nodos_ruta_maldita) = ancestro_actual;
			contador_nodos_ruta_maldita++;
		} else {
			break;
		}
		contador_nodos_recorridos++;
	}

	if (contador_nodos_ruta_maldita < 2) {
		perror("no c encontraron nodos prohibidos, no mames!");
		abort();
	}

	caca_log_debug("la ruta maldita kedo %s",
			caca_arreglo_a_cadena(ruta_maldita, contador_nodos_ruta_maldita,
					buffer));

	grafo_copia_profunda(&grafo_inicial_ctx, grafo_viable_ctx, ruta_maldita + 1,
			contador_nodos_ruta_maldita - 1);

	if (distancia_posicion_incomoda_a_inicial) {
		*distancia_posicion_incomoda_a_inicial = *(distancias_minimas
				+ posicion_inicial);
	}
	return num_nodos - contador_nodos_ruta_maldita + 1;
}

double escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera) {
	int i, j;
	int num_nodos = 0;
	int tam_ruta_a_salida_actual = 0;
	double maxima_velocidad = 0;
	double tiempo_polis = 0;
	double velocidad_minima = (double) MAX_VALOR;
	tipo_dato salida_carretera_actual = 0;
	tipo_dato distancia_salida_carretera_actual = 0;
	tipo_dato distancia_polis_a_ratas = 0;
	tipo_dato distancia_recorrida_polis = 0;
	tipo_dato min_distancia_salida = MAX_VALOR;
	tipo_dato ind_min_distancia_salida = 0;
	tipo_dato ind_nodo_actual = 0;
	tipo_dato distancia_poli_a_nodo_actual;
	tipo_dato distancia_min_poli_a_nodo_actual = MAX_VALOR;
	tipo_dato ind_distancia_min_poli_a_nodo_actual = MAX_VALOR;
	char *buffer = NULL;
	tipo_dato *distancias_minimas_bandido = NULL;
	tipo_dato *antecesores_bandido = NULL;
	tipo_dato *distancias_minimas_polis = NULL;
	tipo_dato *antecesores_polis = NULL;
	nodo_cola_prioridad *nodo_salida_mas_cercana = NULL;
	grafo_contexto *grafo_bandido_ctx = NULL;
	grafo_contexto *grafo_poli_ctx = NULL;
	tipo_dato *ruta_a_salida_actual = NULL;

	if (caca_arreglo_contiene(salidas_carretera, num_salidas_carretera,
			posicion_polis)) {
		caca_log_debug("Se empieza en una salida, asi que todo esta hecho");
		return 0;
	}

	if (posicion_polis == posicion_ratas) {
		caca_log_debug(
				"VERGA, la posicion de las ratas y de los polis es la misma");
		return velocidad_minima;
	}

	buffer = calloc(1000, sizeof(char));

	caca_log_debug("el num d filas %d", num_filas);
	caca_log_debug("los polis %ld", posicion_polis);
	caca_log_debug("las ratas %ld", posicion_ratas);
	caca_log_debug("num de salidas a carretera %ld", num_salidas_carretera);
	caca_log_debug("las salidas a carretera %s",
			caca_arreglo_a_cadena(salidas_carretera, num_salidas_carretera,
					buffer));
	caca_log_debug("la matrix de adjacencia:");
	caca_imprime_matrix(matrix_aristas, num_filas, NULL, 3);

	grafo_poli_ctx = calloc(1, sizeof(grafo_contexto));
	if (!grafo_poli_ctx) {
		perror("no se consigio memoria para grafo poli");
		abort();
	}

	grafo_bandido_ctx = calloc(1, sizeof(grafo_contexto));
	if (!grafo_bandido_ctx) {
		perror("no se consigio memoria para grafo bandido");
		abort();
	}

	num_nodos = init_grafo(matrix_aristas, num_filas, grafo_poli_ctx, falso,
			verdadero);

	distancias_minimas_bandido = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!distancias_minimas_bandido) {
		perror("no se consigio memoria para distancias bandido");
		abort();
	}
	antecesores_bandido = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!antecesores_bandido) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	distancias_minimas_polis = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!distancias_minimas_polis) {
		perror("no se consigio memoria para distancias poli");
		abort();
	}
	antecesores_polis = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!antecesores_polis) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	ruta_a_salida_actual = calloc(num_nodos + 1, sizeof(tipo_dato));
	if (!ruta_a_salida_actual) {
		perror("no se consigio memoria para ruta_salida_actual");
		abort();
	}

	caca_log_debug("l num de nodos poli %d", num_nodos);

	grafo_copia_profunda(grafo_poli_ctx, grafo_bandido_ctx, &posicion_polis, 1);

	dijkstra_main(NULL, 0, posicion_polis, 0, grafo_poli_ctx,
			distancias_minimas_polis, antecesores_polis);

	caca_log_debug("las distancias minimas de poli %ld %s", posicion_polis,
			caca_arreglo_a_cadena(distancias_minimas_polis, num_nodos + 1,
					buffer));
	caca_log_debug("los antecesores de los polis %s",
			caca_arreglo_a_cadena(antecesores_polis, num_nodos + 1, buffer));

	dijkstra_main(NULL, 0, posicion_ratas, 0, grafo_bandido_ctx,
			distancias_minimas_bandido, antecesores_bandido);

	caca_log_debug("las distancias minimas de bandidos %ld %s", posicion_ratas,
			caca_arreglo_a_cadena(distancias_minimas_bandido, num_nodos + 1,
					buffer));
	caca_log_debug("los antecesores de los bandidos %s",
			caca_arreglo_a_cadena(antecesores_bandido, num_nodos + 1, buffer));

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if (salida_carretera_actual == posicion_polis) {
			caca_log_debug("No mames la salida es donde estan los polis %ld",
					salida_carretera_actual);
			continue;
		}
		if (*(distancias_minimas_bandido + salida_carretera_actual)
				== COLA_PRIORIDAD_VALOR_INVALIDO) {
			caca_log_debug("VERGA, la salida a %ld es inalcanzable",
					salida_carretera_actual);
			continue;
		}

		dijkstra_calcula_ruta(antecesores_bandido, num_nodos + 1,
				posicion_ratas, salida_carretera_actual, ruta_a_salida_actual,
				&tam_ruta_a_salida_actual);
		caca_log_debug("la ruta maldita a %ld es %s, de tam %d",
				salida_carretera_actual,
				caca_arreglo_a_cadena(ruta_a_salida_actual,
						tam_ruta_a_salida_actual, buffer),
				tam_ruta_a_salida_actual);

		distancia_min_poli_a_nodo_actual = MAX_VALOR;
		ind_distancia_min_poli_a_nodo_actual = MAX_VALOR;
		for (j = 0; j < tam_ruta_a_salida_actual - 1; j++) {
			ind_nodo_actual = *(ruta_a_salida_actual + j);
			distancia_poli_a_nodo_actual = *(distancias_minimas_polis
					+ ind_nodo_actual);
			caca_log_debug("distancia de policia a %ld es %ld", ind_nodo_actual,
					distancia_poli_a_nodo_actual);
			if (distancia_poli_a_nodo_actual
					< distancia_min_poli_a_nodo_actual) {
				distancia_min_poli_a_nodo_actual = distancia_poli_a_nodo_actual;
				ind_distancia_min_poli_a_nodo_actual = ind_nodo_actual;
			}
		}
		assert(distancia_min_poli_a_nodo_actual <= MAX_VALOR);
		assert(ind_distancia_min_poli_a_nodo_actual <= MAX_VALOR);

		distancia_recorrida_polis = distancia_min_poli_a_nodo_actual;

		tiempo_polis = (double) (distancia_recorrida_polis)
				/ (double) (MAX_VEL_POLIS);
		caca_log_debug(
				"la distancia recorrida x los polis %ld y su max vel %ld, x tanto su tiempo %f",
				distancia_recorrida_polis, MAX_VEL_POLIS, tiempo_polis);

		maxima_velocidad = (double) (*(distancias_minimas_bandido
				+ ind_distancia_min_poli_a_nodo_actual)) / (tiempo_polis);
		caca_log_debug(
				"nodo donde ambos c encuentran %ld, distancia de ratas a ese nodo %ld",
				ind_distancia_min_poli_a_nodo_actual,
				*(distancias_minimas_bandido
						+ ind_distancia_min_poli_a_nodo_actual));
		caca_log_debug(
				"la distancia a la salida mas cercana para los amantes bandidos %ld, la max velocidad %.10f",
				*(distancias_minimas_bandido + salida_carretera_actual),
				maxima_velocidad);

		// TODO: Caso especial si la max vel es MAX vel de polis?
		if (maxima_velocidad < (double) MAX_VEL_POLIS) {
			caca_log_debug("sere tu heroe de amor");
			distancia_recorrida_polis = *(distancias_minimas_polis
					+ salida_carretera_actual);
			tiempo_polis = (double) (distancia_recorrida_polis)
					/ (double) (MAX_VEL_POLIS);
			maxima_velocidad = (double) (*(distancias_minimas_bandido
					+ salida_carretera_actual)) / (tiempo_polis);
			/*
			 caca_log_debug(
			 "la velocidad era demasiado poca, entonces la distancia del poli a la salida era mayor, por lo que se usa esa distancia para calcular la velocidad %f",
			 maxima_velocidad);
			 */
			caca_log_debug("sere tu amante bastardo, digo bandido %f",
					maxima_velocidad);
		}

		if (maxima_velocidad < velocidad_minima) {
			velocidad_minima = maxima_velocidad;
		}

	}

	/* ???
	 if (velocidad_minima == (double) MAX_VALOR) {
	 return 0;
	 }
	 */
	caca_log_debug("la velocidad minima encontrada es %.10f", velocidad_minima);

	return velocidad_minima;
}

double escape_cabron_main() {
	double maxima_velocidad = 0;

	int num_aristas = 0;

	tipo_dato num_nodos = 0, num_salidas = 0;
	tipo_dato posicion_ratas = 0, posicion_polis = 0;

	tipo_dato *datos_escape_mem = NULL;

	tipo_dato *datos_escape = (tipo_dato *) datos_escape_mem;
	tipo_dato *inicio_aristas = NULL;
	tipo_dato *salidas = NULL;

	datos_escape_mem = calloc(
			ESCAPE_CABRON_MAX_FILAS_INPUT * ESCAPE_CABRON_MAX_COLS_INPUT,
			sizeof(tipo_dato));
	if (!datos_escape_mem) {
		perror("no se obtubo memoria para los datos del escape");
		abort();
	}
	datos_escape = datos_escape_mem;

	lee_matrix_long_stdin((tipo_dato *) datos_escape, &num_aristas, NULL,
			ESCAPE_CABRON_MAX_FILAS_INPUT, ESCAPE_CABRON_MAX_COLS_INPUT);
	caca_log_debug("la matrix leida,num de aristas %ld", num_aristas);
	caca_imprime_matrix(datos_escape_mem, num_aristas, NULL,
			ESCAPE_CABRON_MAX_COLS_INPUT);

	if (!num_aristas) {
		perror("vale verga, no c leyo nada");
		abort();
	}

	num_nodos = *datos_escape;
	num_aristas = *(datos_escape + 1);
	num_salidas = *(datos_escape + 2);

	inicio_aristas = datos_escape + ESCAPE_CABRON_MAX_COLS_INPUT;
	salidas = inicio_aristas + num_aristas * ESCAPE_CABRON_MAX_COLS_INPUT;
	posicion_ratas = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT);
	posicion_polis = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT + 1);

	caca_realinea_array(inicio_aristas, num_aristas,
			ESCAPE_CABRON_MAX_COLS_INPUT, 3);

	maxima_velocidad = escape_cabron_encuentra_escape(inicio_aristas,
			num_aristas, posicion_polis, posicion_ratas, salidas, num_salidas);

	caca_log_debug("la maxima velocida calculada %f", maxima_velocidad);
	return maxima_velocidad;
}

void dijkstra_calcula_ruta(tipo_dato *antecesores, int tam_antecesores,
		tipo_dato posicion_inicial, tipo_dato posicion_destino,
		tipo_dato *ruta_maldita, int *tam_ruta) {
	int contador_nodos_recorridos = 0;
	int contador_nodos_ruta_maldita = 0;
	tipo_dato ancestro_actual = 0;

	caca_log_debug("sacando la ruta maldita de %ld a %ld", posicion_inicial,
			posicion_destino);
	*(ruta_maldita + contador_nodos_ruta_maldita++) = posicion_destino;
	caca_log_debug("nodo destino %ld", posicion_destino);
	while (*(ruta_maldita + contador_nodos_ruta_maldita - 1) != posicion_inicial
			&& contador_nodos_recorridos < tam_antecesores) {
		ancestro_actual = *(antecesores
				+ *(ruta_maldita + contador_nodos_ruta_maldita - 1));
		caca_log_debug("ancestro actual %ld en %d", ancestro_actual,
				contador_nodos_ruta_maldita);
		if (ancestro_actual != 0) {
			*(ruta_maldita + contador_nodos_ruta_maldita) = ancestro_actual;
			contador_nodos_ruta_maldita++;
		} else {
			break;
		}
		contador_nodos_recorridos++;
	}
	*tam_ruta = contador_nodos_recorridos + 1;
	caca_log_debug("el tamaño de la ruta queda %d", *tam_ruta);
}
