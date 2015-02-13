/*
 ============================================================================
 Name        : escape_cabron.c
 Author      : ernesto
 Version     :
 Copyright   : Your copyright notice
 Description : Era un bandido tan pervertido...
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cacacomun.h>
#include "escapecabron.h"

int escape_cabron_determina_nodos_viables(void *matrix_vertices, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial) {

	int num_nodos = 0;
	int contador_nodos_ruta_maldita = 0;
	int contador_nodos_recorridos = 0;
	tipo_dato ancestro_actual = 0;
	grafo_contexto grafo_inicial_ctx;

	char buffer[MAX_TAM_CADENA] = { '\0' };
	tipo_dato *distancias_minimas = NULL, *antecesores = NULL;
	tipo_dato *ruta_maldita;

	num_nodos = init_grafo(matrix_vertices, num_filas, &grafo_inicial_ctx,
			falso, verdadero);

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
	dijkstra_main(matrix_vertices, num_filas, posicion_incomoda,
			posicion_inicial, NULL, distancias_minimas, antecesores);

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

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera) {
	int num_nodos_viables = 0;
	float maxima_velocidad = 0;
	float tiempo_polis = 0;
	tipo_dato salida_carretera_actual = 0;
	tipo_dato distancia_salida_carretera_actual = 0;
	tipo_dato distancia_polis_a_ratas = 0;
	tipo_dato distancia_recorrida_polis = 0;
	char *buffer = NULL;
	nodo_cola_prioridad *nodo_salida_mas_cercana = NULL;
	grafo_contexto *grafo_viable_ctx = NULL;
	cola_prioridad_contexto *cola_salidas_carretera = NULL;
	tipo_dato *distancias_minimas = NULL;
	tipo_dato *antecesores = NULL;
	tipo_dato *distancias_salidas_carretera = NULL;

	buffer = calloc(1000, sizeof(char));

	grafo_viable_ctx = calloc(1, sizeof(grafo_contexto));
	if (!grafo_viable_ctx) {
		perror("no se consigio memoria para grafo viable");
		abort();
	}

	num_nodos_viables = escape_cabron_determina_nodos_viables(matrix_vertices,
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
	distancias_salidas_carretera = malloc(
			num_salidas_carretera * sizeof(tipo_dato));
	if (!antecesores) {
		perror("no se consigio memoria para distancias de salidas a carretera");
		abort();
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables+ 1) * sizeof(tipo_dato));
	memset(distancias_minimas, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables+ 1) * sizeof(tipo_dato));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, grafo_viable_ctx,
			distancias_minimas, antecesores);

	for (int i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		distancia_salida_carretera_actual = *(distancias_minimas
				+ salida_carretera_actual);
		*(distancias_salidas_carretera + i) = distancia_salida_carretera_actual;
	}

	caca_log_debug("las distancias a las salidas de la carretera son %s",
			caca_arreglo_a_cadena(distancias_salidas_carretera,
					num_salidas_carretera, buffer));

	cola_salidas_carretera = calloc(1, sizeof(cola_prioridad_contexto));
	if (!antecesores) {
		perror("no se consigio memoria para cola de distancias a salidas");
		abort();
	}

	cola_prioridad_init(cola_salidas_carretera, NULL, salidas_carretera,
			distancias_salidas_carretera, num_salidas_carretera, NULL, NULL );

	if (cola_prioridad_es_vacia(cola_salidas_carretera)) {
		return maxima_velocidad;
	}

	nodo_salida_mas_cercana = cola_prioridad_pop(cola_salidas_carretera);
	caca_log_debug("La salida mas cercana es %ld, con distancia %ld",
			nodo_salida_mas_cercana->valor, nodo_salida_mas_cercana->indice);

	distancia_recorrida_polis = nodo_salida_mas_cercana->indice
			+ distancia_polis_a_ratas;

	tiempo_polis = (float) distancia_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) nodo_salida_mas_cercana->indice / tiempo_polis;

	return maxima_velocidad;
}
