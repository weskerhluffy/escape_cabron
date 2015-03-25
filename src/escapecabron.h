/*
 * escapecabron.h
 *
 *  Created on: 16/01/2015
 *      Author: ernesto
 */

#include<config.h>
#include<cacacomun.h>

#ifndef ESCAPECABRON_H_
#define ESCAPECABRON_H_

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nodos_viables(void *matrix_vertices, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial);

double escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera);

double escape_cabron_main();

void dijkstra_calcula_ruta(tipo_dato *antecesores,int tam_antecesores, tipo_dato posicion_inicial,
		tipo_dato posicion_destino, tipo_dato *ruta, int *tam_ruta);

#endif /* ESCAPECABRON_H_ */
