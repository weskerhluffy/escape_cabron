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

float escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera) {
	int i;
	int num_nodos_viables = 0;
	int num_salidas_viables = 0;
	float maxima_velocidad = 0;
	float tiempo_polis = 0;
	tipo_dato salida_carretera_actual = 0;
	tipo_dato distancia_salida_carretera_actual = 0;
	tipo_dato distancia_polis_a_ratas = 0;
	tipo_dato distancia_recorrida_polis = 0;
	tipo_dato min_distancia_salida = MAX_VALOR;
	tipo_dato ind_min_distancia_salida = 0;
	char *buffer = NULL;
	nodo_cola_prioridad *nodo_salida_mas_cercana = NULL;
	grafo_contexto *grafo_viable_ctx = NULL;
	tipo_dato *distancias_minimas = NULL;
	tipo_dato *antecesores = NULL;
	tipo_dato *distancias_salidas_carretera = NULL;
	tipo_dato *salidas_carretera_viables = NULL;

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

	grafo_viable_ctx = calloc(1, sizeof(grafo_contexto));
	if (!grafo_viable_ctx) {
		perror("no se consigio memoria para grafo viable");
		abort();
	}

	num_nodos_viables = escape_cabron_determina_nodos_viables(matrix_aristas,
			num_filas, grafo_viable_ctx, posicion_polis, posicion_ratas,
			&distancia_polis_a_ratas);

	caca_log_debug("l num de nodos viables %d", num_nodos_viables);

	if (num_nodos_viables < 2) {
		return maxima_velocidad;
	}

	distancias_minimas = malloc((num_nodos_viables + 1) * sizeof(tipo_dato));
	if (!distancias_minimas) {
		perror("no se consigio memoria para distancias");
		abort();
	}
	antecesores = malloc((num_nodos_viables + 1) * sizeof(tipo_dato));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		abort();
	}
	distancias_salidas_carretera = calloc(num_salidas_carretera,
			sizeof(tipo_dato));
	if (!antecesores) {
		perror("no se consigio memoria para distancias de salidas a carretera");
		abort();
	}
	salidas_carretera_viables = calloc(num_salidas_carretera,
			sizeof(tipo_dato));
	if (!antecesores) {
		perror("no se consigio memoria para salidas a carretera viables");
		abort();
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables+ 1) * sizeof(tipo_dato));
	memset(distancias_minimas, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables+ 1) * sizeof(tipo_dato));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, grafo_viable_ctx,
			distancias_minimas, antecesores);

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if (salida_carretera_actual == posicion_polis) {
			caca_log_debug("No mames la salida es donde estan los polis %ld",
					salida_carretera_actual);
			continue;
		}
		if ((distancia_salida_carretera_actual = *(distancias_minimas
				+ salida_carretera_actual)) == MAX_VALOR
				|| distancia_salida_carretera_actual
						== COLA_PRIORIDAD_VALOR_INVALIDO) {
			caca_log_debug("Mierda, la salida %ld es inalcanzable",
					salida_carretera_actual);
			continue;
		}
		caca_log_debug("Salida a carretera %ld es viable con %ld",
				salida_carretera_actual, distancia_salida_carretera_actual);
		*(distancias_salidas_carretera + num_salidas_viables) =
				distancia_salida_carretera_actual;
		*(salidas_carretera_viables + num_salidas_viables) =
				salida_carretera_actual;
		num_salidas_viables++;
	}

	caca_log_debug("las distancias a las salidas de la carretera son %s",
			caca_arreglo_a_cadena(distancias_salidas_carretera,
					num_salidas_viables, buffer));
	caca_log_debug("las salidas de la carretera viables son %s",
			caca_arreglo_a_cadena(salidas_carretera_viables,
					num_salidas_viables, buffer));

	if (!num_salidas_viables) {
		return maxima_velocidad;
	}

	for (i = 0; i < num_salidas_viables; i++) {
		distancia_salida_carretera_actual = *(distancias_salidas_carretera + i);
		if (distancia_salida_carretera_actual < min_distancia_salida) {
			min_distancia_salida = distancia_salida_carretera_actual;
			ind_min_distancia_salida = *(salidas_carretera_viables + i);
		}
	}

	caca_log_debug("la salida mas cercana %ld a %ld km",
			ind_min_distancia_salida, min_distancia_salida);

	nodo_salida_mas_cercana = calloc(1, sizeof(nodo_cola_prioridad));
	COLA_PRIORIDAD_ASIGNA_VALOR(nodo_salida_mas_cercana,
			ind_min_distancia_salida);
	COLA_PRIORIDAD_ASIGNA_INDICE(nodo_salida_mas_cercana, min_distancia_salida);

	caca_log_debug("La salida mas cercana es %ld, con distancia %ld",
			nodo_salida_mas_cercana->valor, nodo_salida_mas_cercana->indice);

	distancia_recorrida_polis = nodo_salida_mas_cercana->indice
			+ distancia_polis_a_ratas;

	tiempo_polis = (float) distancia_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) nodo_salida_mas_cercana->indice / tiempo_polis;

	return maxima_velocidad;
}

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	tipo_dato num_nodos = 0, num_salidas = 0;
	tipo_dato posicion_ratas = 0, posicion_polis = 0;

	tipo_dato datos_escape_mem[ESCAPE_CABRON_MAX_FILAS_INPUT][ESCAPE_CABRON_MAX_COLS_INPUT] =
			{ { 0 } };
	/* 	tipo_dato *datos_escape_mem = NULL; */

	tipo_dato *datos_escape = (tipo_dato *) datos_escape_mem;
	tipo_dato *inicio_aristas = NULL;
	tipo_dato *salidas = NULL;

	/*
	 datos_escape_mem = calloc(
	 ESCAPE_CABRON_MAX_FILAS_INPUT * ESCAPE_CABRON_MAX_COLS_INPUT,
	 sizeof(tipo_dato));
	 if (!datos_escape_mem) {
	 perror("no se obtubo memoria para los datos del escape");
	 abort();
	 }
	 datos_escape = datos_escape_mem;
	 */

	lee_matrix_long_stdin((tipo_dato *) datos_escape_mem, &num_aristas, NULL,
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
