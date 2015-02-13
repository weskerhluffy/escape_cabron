/*
 * escapecabron.h
 *
 *  Created on: 16/01/2015
 *      Author: ernesto
 */

#include<cacacomun.h>

#ifndef ESCAPECABRON_H_
#define ESCAPECABRON_H_

#define MAX_VEL_POLIS 160

int escape_cabron_determina_nodos_viables(void *matrix_vertices, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial);

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera);

#endif /* ESCAPECABRON_H_ */
