/* only main should be in this file, to make all other functions in
 the prograble testable by Check.  in order to test main(), use a
 whole program testing framework like Autotest.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <math.h>

#ifndef CACACOMUN_H_
#define CACACOMUN_H_

//XXX: http://gnupdf.org/manuals/gnupdf-hg-manual/html_node/Using-gdb-to-debug-check-tests.html

#define tipo_dato unsigned long

#define MAX_NODOS 101
#define TAM_MAX_LINEA 1024
#define TAM_MAX_NUMERO 128
#define MAX_FILAS_INPUT 5010
#define MAX_COLUMNAS_INPUT 256
#define MAX_FILAS_NODOS 1000
#define MAX_COLUMNAS_NODOS 1000
#define CACA_COMPARACION_IZQ_MENOR -1
#define CACA_COMPARACION_IZQ_IGUAL 0
#define CACA_COMPARACION_IZQ_MAYOR 1
#define MAX_TAM_CADENA 200
#define ARBOL_AVL_INDICE_INVALIDO -1
#define ARBOL_AVL_VALOR_INVALIDO -1
#define COLA_PRIORIDAD_VALOR_INVALIDO -1
#define DIJKSTRA_VALOR_INVALIDO -1

#define MAX_VALOR (tipo_dato) (2<<28)

#define GRAFO_NODO_ORIGEN 0
#define GRAFO_NODO_DESTINO 1
#define GRAFO_DISTANCIA_ENTRE_NODOS 2

#define GRAFO_LIMITE_ORDENACION_LINEAL 2

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;


#define GRAFO_AVANZAR_NODO(nodo_apuntador,criterio_busqueda,discriminar_principal) \
		switch (criterio_busqueda) { \
	 	case GRAFO_VALOR: \
			nodo_apuntador = (nodo_apuntador)->siguiente_valor; \
			break; \
		case GRAFO_DISTANCIA: \
			nodo_apuntador = (nodo_apuntador)->siguiente_distancia; \
			break; \
		case GRAFO_INDICE: \
			nodo_apuntador = (nodo_apuntador)->siguiente_indice; \
			break; \
		case GRAFO_PRINCIPAL: \
			if(!discriminar_principal) { \
				nodo_apuntador = (nodo_apuntador)->siguiente; \
			} \
			break; \
		default: \
			perror("en GRAFO_AVANZAR_NODO  hubo un error culero al buscar"); \
			break; \
		}

#define GRAFO_COPIA_NODO_DATOS(nodo_origen,nodo_destino) \
		nodo_destino->valor=nodo_destino->valor; \
		nodo_destino->distancia=nodo_destino->distancia; \
		nodo_destino->indice=nodo_destino->indice;

#define GRAFO_NODO_SIG_ANT(nodo_anterior,nodo_siguiente,nodo_actual,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GRAFO_VALOR: \
			nodo_siguiente= (nodo_actual)->siguiente_valor; \
			nodo_anterior= (nodo_actual)->anterior_valor; \
			break; \
		case GRAFO_DISTANCIA: \
			nodo_siguiente= (nodo_actual)->siguiente_distancia; \
			nodo_anterior= (nodo_actual)->anterior_distancia; \
			break; \
		case GRAFO_INDICE: \
			nodo_siguiente= (nodo_actual)->siguiente_indice; \
			nodo_anterior= (nodo_actual)->anterior_indice; \
			break; \
		case GRAFO_PRINCIPAL: \
			nodo_siguiente= (nodo_actual)->siguiente; \
			nodo_anterior= (nodo_actual)->anterior; \
			break; \
		default: \
			perror("en GRAFO_AVANZAR_NODO  hubo un error culero al buscar"); \
			break; \
		}

#define GRAFO_ASIGNAR_SIGUIENTE_ANTERIOR(nodo_anterior,nodo_siguiente,nodo_actual,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GRAFO_VALOR: \
			(nodo_actual)->siguiente_valor=nodo_siguiente; \
			(nodo_actual)->anterior_valor=nodo_anterior; \
			break; \
		case GRAFO_DISTANCIA: \
			(nodo_actual)->siguiente_distancia=nodo_siguiente; \
			(nodo_actual)->anterior_distancia=nodo_anterior; \
			break; \
		case GRAFO_INDICE: \
			(nodo_actual)->siguiente_indice=nodo_siguiente; \
			(nodo_actual)->anterior_indice=nodo_anterior; \
			break; \
		case GRAFO_PRINCIPAL: \
			(nodo_actual)->siguiente=nodo_siguiente; \
			(nodo_actual)->anterior=nodo_anterior; \
			break; \
		default: \
			perror("en GRAFO_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define GRAFO_ASIGNAR_SIGUIENTE(nodo_siguiente,nodo_actual,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GRAFO_VALOR: \
			(nodo_actual)->siguiente_valor=nodo_siguiente; \
			break; \
		case GRAFO_DISTANCIA: \
			(nodo_actual)->siguiente_distancia=nodo_siguiente; \
			break; \
		case GRAFO_INDICE: \
			(nodo_actual)->siguiente_indice=nodo_siguiente; \
			break; \
		case GRAFO_PRINCIPAL: \
			(nodo_actual)->siguiente=nodo_siguiente; \
			break; \
		default: \
			perror("en GRAFO_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define GRAFO_ASIGNAR_ANTERIOR(nodo_anterior,nodo_actual,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GRAFO_VALOR: \
			(nodo_actual)->anterior_valor=nodo_anterior; \
			break; \
		case GRAFO_DISTANCIA: \
			(nodo_actual)->anterior_distancia=nodo_anterior; \
			break; \
		case GRAFO_INDICE: \
			(nodo_actual)->anterior_indice=nodo_anterior; \
			break; \
		case GRAFO_PRINCIPAL: \
			(nodo_actual)->anterior=nodo_anterior; \
			break; \
		default: \
			perror("en GRAFO_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define caca_log_debug(formato, args...) \
		do \
		{ \
			((void)0); \
		} \
		while(0);

/*
 #define caca_log_debug(formato, args...) (void) 0
 */

#define ARBOL_AVL_ACTUALIZAR_ALTURA(nodo) \
	(nodo)->altura = ((nodo)->hijo_izq || (nodo)->hijo_der)? \
			caca_int_max(ARBOL_AVL_GET_ALTURA((nodo)->hijo_izq), ARBOL_AVL_GET_ALTURA((nodo)->hijo_der)) + 1: \
			0;

#define ARBOL_AVL_GET_ALTURA(nodo) \
	((nodo)?(nodo)->altura:0)

#define ARBOL_AVL_GET_VALOR(nodo) \
	((nodo)?(nodo)->valor:ARBOL_AVL_VALOR_INVALIDO)

#define ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo,nuevo_padre) \
	((nodo)?(nodo)->padre=(nuevo_padre):((void)0))

#define ARBOL_AVL_GET_PADRE(nodo) \
	((nodo)?(nodo)->padre:NULL)

#define ARBOL_AVL_GET_INDICE(nodo) \
	((nodo)?(nodo)->indice:ARBOL_AVL_INDICE_INVALIDO)

#define ARBOL_BINARIO_ACTUALIZAR_HIJO_IZQ(nodo,nuevo_hijo) \
	((nodo)?(nodo)->hijo_izq=(nuevo_hijo):((void)0))

#define ARBOL_BINARIO_ACTUALIZAR_HIJO_DER(nodo,nuevo_hijo) \
	((nodo)?(nodo)->hijo_der=(nuevo_hijo):((void)0))

#define COLA_PRIORIDAD_ASIGNA_INDICE(nodo,nuevo_indice) \
	(nodo)->indice=nuevo_indice

#define COLA_PRIORIDAD_ASIGNA_VALOR(nodo,nuevo_valor) \
	(nodo)->indice=nuevo_valor

// XXX: http://www.programiz.com/c-programming/c-enumeration
#undef  ADDITEM
#define ADDITEM( criterio_ordenacion, comentario) criterio_ordenacion
typedef enum GRAFO_CRITERIOS_ORDENACION {
	ADDITEM(GRAFO_INDICE,"Ordenacion por indice"),
	ADDITEM(GRAFO_VALOR,"Ordenacion por valor"),
	ADDITEM(GRAFO_DISTANCIA,"Ordenacion por distancia"),
	ADDITEM(GRAFO_PRINCIPAL,"Ordenacion por indice, pero para el grafo principal")
} GRAFO_CRITERIOS_ORDENACION;
#undef  ADDITEM

typedef enum GRAFO_TIPO_RESULTADO_BUSQUEDA {
	GRAFO_NADA_ENCONTRADO,
	GRAFO_NODO_ENCONTRADO,
	GRAFO_NODOS_PRE_POST_ENCONTRADOS
} GRAFO_TIPO_RESULTADO_BUSQUEDA;

typedef struct nodo {
	tipo_dato valor;
	tipo_dato indice;
	tipo_dato distancia;
	int num_nodos_asociados;
	int num_nodos_asociados_indice;
	int num_nodos_asociados_valor;
	int num_nodos_asociados_distancia;
	struct nodo *siguiente;
	struct nodo *anterior;
	struct nodo *siguiente_indice;
	struct nodo *anterior_indice;
	struct nodo *siguiente_valor;
	struct nodo *anterior_valor;
	struct nodo *siguiente_distancia;
	struct nodo *anterior_distancia;
} nodo;

typedef struct nodo_arbol_binario {
	tipo_dato indice;
	tipo_dato valor;
	unsigned int altura;

	struct nodo_arbol_binario *hijo_izq;
	struct nodo_arbol_binario *hijo_der;
	struct nodo_arbol_binario *padre;
} nodo_arbol_binario;

typedef struct grifo_contexto {
	int localidades_usadas;
	nodo *inicio;
	nodo nodos_disponibles[MAX_NODOS];
	tipo_dato matrix_distancias[MAX_COLUMNAS_NODOS][MAX_FILAS_NODOS];
	nodo *referencias_nodos_por_indice[MAX_FILAS_NODOS];
} grafo_contexto;

typedef struct arbol_binario_contexto {
	bool no_indices_repetidos;
	int localidades_usadas;
	nodo_arbol_binario *raiz;
	nodo_arbol_binario nodos_disponibles[MAX_NODOS];
} arbol_binario_contexto;

typedef struct cola_prioridad_contexto {
	arbol_binario_contexto actx_mem;
	arbol_binario_contexto *actx;
	nodo_arbol_binario *referencias_directas_por_indice_mem[MAX_NODOS];
	nodo_arbol_binario **referencias_directas_por_indice;
} cola_prioridad_contexto;

typedef nodo_arbol_binario nodo_cola_prioridad;


#undef ADDITEM
#define ADDITEM( criterio_ordenacion, comentario) [criterio_ordenacion]=comentario
const char* GRAFO_NOMBRES_CRITERIOS_ORDENACION[GRAFO_PRINCIPAL + 1] =
		{ ADDITEM(GRAFO_INDICE,"Ordenacion por indice"),
				ADDITEM(GRAFO_VALOR,"Ordenacion por valor"),
				ADDITEM(GRAFO_DISTANCIA,"Ordenacion por distancia"),
				ADDITEM(GRAFO_PRINCIPAL,"Ordenacion por indice, pero para el grafo principal") };
#undef ADDITEM
int lee_matriz_int_archivo(const char * nombre_archivo,
		tipo_dato matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT], int *filas);

int lee_matriz_long_stdin(tipo_dato matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT],
		int *filas);

// XXX: http://stackoverflow.com/questions/5724171/passing-an-array-by-reference
/**
 *
 * @param matrix
 * @param num_filas Regresa el num de filas .Debe ser inicializado externo.
 * @param num_columnas Regresa de cada fila el num de columnas. Debe ser inicializado externo. Debe ser al menos de tama�o ::MAX_FILAS_INPUT.
 * @return
 */
int lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int caca_imprime_matrix(void *matrix, int num_filas, int *num_columnas,
		int num_columnas_fijo);

int init_grafo(void *matrix, int num_filas, grafo_contexto *ctx,
		bool usar_hashes, bool relaciones_bidireccionales);

nodo *grafo_nodo_alloc(grafo_contexto *ctx, int localidades_solicitadas);

// XXX: http://stackoverflow.com/questions/742699/returning-an-enum-from-a-function-in-c
GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_lineal(nodo *inicio, nodo *nodo_a_buscar,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda, void *nodos_encontrados,
		int limite_nodos_busqueda);

GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_binaria(nodo *inicio,
		nodo *nodo_a_buscar, GRAFO_CRITERIOS_ORDENACION criterio_busqueda,
		void *nodos_encontrados);

GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_binaria_recursiva(nodo *inicio,
		nodo **arreglo_nodos, nodo *nodo_a_buscar,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda, void *nodos_encontrados,
		int indice_inicial, int indice_final);


static inline char *grafo_nodo_a_cadena(nodo *node, char *cadena_buffer,
		int *characteres_escritos);

static inline int grafo_comparar_nodos(nodo *nodo1, nodo *nodo2,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda);

void caca_log_debug_func(const char *format, ...);

// XXX: https://www.securecoding.cert.org/confluence/display/seccode/MEM10-C.+Define+and+use+a+pointer+validation+function
int caca_apuntador_valido(void *p);

// XXX: http://www.quora.com/Given-a-variable-how-can-you-find-whether-it-was-allocated-from-stack-or-from-heap-memory

void grafo_insertar_nodo(nodo *nodo_anterior, nodo *nodo_siguiente,
		nodo *nodo_a_insertar, GRAFO_CRITERIOS_ORDENACION criterio_busqueda);

void grafo_anadir_nodo(nodo *nodo_inicial, nodo *nodo_a_anadir,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda);

void imprimir_lista_adjacencia(nodo *nodo_inicial);

static inline int *grafo_apuntador_num_nodos_asociados(nodo *nodo,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda);

void arbol_avl_init(arbol_binario_contexto *ctx, tipo_dato *indices,
		tipo_dato *datos, int num_datos,
		nodo_arbol_binario **arreglo_referencias_nodos);

#define ARBOL_AVL_ALTURA_CARGADA_IZQ -1
#define ARBOL_AVL_ALTURA_CARGADA_DER 1
#define ARBOL_AVL_ALTURA_BALANCEADA 0

static inline int arbol_avl_diferencia_alturas_subarboles(
		nodo_arbol_binario *nodo, int tolerancia,
		bool considerar_balanceado_cargado_der);

static inline char *arbol_binario_nodo_a_cadena(nodo_arbol_binario *node,
		char *cadena_buffer, int *characteres_escritos);

static inline nodo_arbol_binario *arbol_binario_nodo_allocar(
		arbol_binario_contexto *ctx, int localidades_solicitadas);

void arbol_binario_recorrido_preoder(nodo_arbol_binario *raiz);

void arbol_binario_colectar_datos_recorrido_preoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados);

void arbol_avl_insertar(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_insertar, bool no_indices_repetidos);

static inline int arbol_avl_compara_nodos(nodo_arbol_binario *nodo1,
		nodo_arbol_binario *nodo2);

static inline int caca_int_max(int a, int b);

static inline void arbol_binario_rotar_izq(nodo_arbol_binario **nodo);
static inline void arbol_binario_rotar_der(nodo_arbol_binario **nodo);

void arbol_binario_borrar_nodo(nodo_arbol_binario **raiz,
		tipo_dato valor_a_borrar);

void arbol_binario_colectar_datos_recorrido_inoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados);

void arbol_binario_recorrido_inoder(nodo_arbol_binario *raiz);

void arbol_avl_borrar(nodo_arbol_binario **raiz, tipo_dato valor_a_borrar);

void arbol_avl_borrar_referencia_directa(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_borrar);

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		tipo_dato indice, tipo_dato nuevo_valor);

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		tipo_dato *antecesores);

void cola_prioridad_init(cola_prioridad_contexto *ctx,
		nodo_cola_prioridad *nodos, tipo_dato *valores, tipo_dato *indices,
		int num_nodos, arbol_binario_contexto *actx,
		nodo_arbol_binario **referencias_directas);

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx,
		tipo_dato *valores, int *num_valores);

nodo_cola_prioridad *cola_prioridad_pop(cola_prioridad_contexto *ctx);

bool cola_prioridad_es_vacia(cola_prioridad_contexto *ctx);

nodo *grafo_get_nodo_origen_por_indice(grafo_contexto *ctx, tipo_dato indice);

nodo *grafo_get_nodo_destino_por_indice(grafo_contexto *ctx, nodo *nodo_origen,
		tipo_dato indice);

tipo_dato grafo_get_distancia_entre_nodos_por_indice(grafo_contexto *ctx,
		tipo_dato indice_origen, tipo_dato indice_destino);

void dijkstra_main(void *matrix_distancias, int num_filas,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		grafo_contexto *gctx, tipo_dato *distancias_minimas,
		tipo_dato *antecesores);

char *caca_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo, char *buffer);

void timestamp_caca(char *stime);

void current_utc_time(struct timespec *ts);

static inline void grafo_copia_nodo(const nodo *nodo_origen, nodo *nodo_destino);

static inline bool caca_arreglo_contiene(tipo_dato *arreglo, int tam_arreglo,
		tipo_dato valor_buscado);

void grafo_get_representacion_en_matriz_ordenada(grafo_contexto *ctx,
		void *matrix, int num_columnas);

void grafo_copia_profunda(const grafo_contexto *ctx_origen,
		grafo_contexto *ctx_destino, tipo_dato *indices_a_ignorar,
		int tam_indices_a_ignorar);

static inline void caca_inutiliza_nodo_cola_prioridad(
		nodo_cola_prioridad *nodos, int num_nodos);

char *caca_arreglo_a_cadena_float(float *arreglo, int tam_arreglo, char *buffer);

void caca_realinea_array(tipo_dato *arreglo, int num_filas,
		int alineacion_actual, int alineacion_nueva);

#endif /* CACACOMUN_H_ */

/*
 * escapecabron.h
 *
 *  Created on: 16/01/2015
 *      Author: ernesto
 */

#ifndef ESCAPECABRON_H_
#define ESCAPECABRON_H_

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nodos_viables(void *matrix_vertices, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial);

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera);

float escape_cabron_main();

#endif /* ESCAPECABRON_H_ */

/*

 * cacacomun.c
 *
 *  Created on: 07/02/2014
 *      Author: ernesto
 */

int lee_matriz_int_archivo(const char * nombre_archivo,
		tipo_dato matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT], int *filas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	long numero = 0;
	char *inicio_cadena_num = NULL;
	char linea[TAM_MAX_LINEA];
	FILE *fp;

	fp = fopen(nombre_archivo, "r");
	if (fp == NULL ) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	while (fgets(linea, TAM_MAX_LINEA, fp) != NULL ) {
		/* writing content to stdout */
		//puts(str);
		inicio_cadena_num = strtok(linea, " ");
		indice_columnas = 0;
		while (inicio_cadena_num != NULL ) {
			numero = strtol(inicio_cadena_num, NULL, 10);
			matrix[indice_columnas][indice_filas] = (tipo_dato) numero;
			inicio_cadena_num = strtok(NULL, " ");
			indice_columnas++;
		}
		indice_filas++;
	}
	*filas = indice_filas;
	fclose(fp);
	return 0;
}

int lee_matriz_long_stdin(tipo_dato matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT],
		int *filas) {
	int indice_filas = 0;
	char linea[TAM_MAX_LINEA];

	fgets(linea, TAM_MAX_LINEA, stdin);
	sscanf(linea, "%ld %ld", &matrix[0][indice_filas],
			&matrix[1][indice_filas]);
	indice_filas++;
	while (fgets(linea, TAM_MAX_LINEA, stdin)
			&& sscanf(linea, "%ld %ld", &matrix[0][indice_filas],
					&matrix[1][indice_filas]) == 2) {
		indice_filas++;
	}

	*filas = indice_filas;
	return 0;
}

// XXX: http://www.eclipse.org/forums/index.php/t/26571/
// XXX: http://stackoverflow.com/questions/3537542/a-doxygen-eclipse-plugin-with-automatic-code-completion
int lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	long numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char linea[TAM_MAX_LINEA];

	caca_log_debug("DDDDDDDDDDDentro de leer mierda");
// XXX: http://stackoverflow.com/questions/2195823/reading-unknown-number-of-integers-from-stdin-c
	while (fgets(linea, TAM_MAX_LINEA, stdin)) {
		caca_log_debug("escaneando linea");
		indice_columnas = 0;
		caca_log_debug("transformando linea '%s'", linea);
		cadena_numero_actual = linea;
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			caca_log_debug("la cadena restante '%s'", cadena_numero_actual);
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			caca_log_debug("el num actual %ld", numero);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				caca_log_debug("se llego al final de la cadena");
				break;
			}
			caca_log_debug("guardando el numero %ld en fil %d, col %d", numero,
					indice_filas, indice_columnas);
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
			if (indice_columnas >= num_max_columnas) {
				perror("se leyeron demasiadas columnas, a la verga");
				abort();
			}
		}
		caca_log_debug("salio del ciclo de linea");
//		*(*num_columnas + indice_filas) = indice_columnas;
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		caca_log_debug("c asigno el numero de columnas");
		indice_filas++;
		caca_log_debug("terminada de procesar linea '%s'", linea);
		if (indice_filas >= num_max_filas) {
			perror("se leyeron demasiadas filas, a la verga");
			abort();
		}
	}

	*num_filas = indice_filas;
	caca_log_debug("termino de recibir mierda");
	return 0;
}

int caca_imprime_matrix(void *matrix, int num_filas, int *num_columnas,
		int num_columnas_fijo) {
	bool es_array = falso;
	int i = 0, j = 0;
	int num_columnas_actual = 0;
	tipo_dato numero_actual = 0;
	tipo_dato *matrix_array = NULL;
	tipo_dato **matrix_pointer = NULL;

	matrix_array = matrix;
	matrix_pointer = matrix;

	caca_log_debug("Me corto los webos");

	es_array = verdadero;

	caca_log_debug("determinado q es array %d", es_array);

	if (!num_columnas && !num_columnas_fijo) {
		caca_log_debug("No mames no ay nada con q trabajar");
	}

	num_columnas_actual = num_columnas_fijo ? num_columnas_fijo : 0;

	for (i = 0; i < num_filas; i++) {
		caca_log_debug("En la fila %d de %d", i, num_filas);
		if (num_columnas) {
			num_columnas_actual = *(num_columnas + i);
		}
		if (num_columnas_fijo) {
			num_columnas_actual = num_columnas_fijo;
		}
//		caca_log_debug("el num d cols actual %d", num_columnas_actual);
		for (j = 0; j < num_columnas_actual; j++) {
			//		caca_log_debug("En la columna %d de %d", j, num_columnas_actual);
			if (es_array) {
//				caca_log_debug("copiando array");
				numero_actual = *(matrix_array + i * num_columnas_actual + j);
			} else {
				caca_log_debug("copiando apuntadores bidimensional");
				numero_actual = *(*(matrix_pointer + i) + j);
			}
//			caca_log_debug("copiado numero");
			if (numero_actual) {
				caca_log_debug("en %d %d el num %ld", i, j, numero_actual);
			}
		}
	}

	caca_log_debug("El # de filas %d", num_filas);
	if (num_columnas) {
		for (i = 0; i < num_filas; i++) {
			caca_log_debug("en fila %d, columnas %d", i, *(num_columnas + i));
		}
	} else {
		caca_log_debug("num  d columnas para todas las filas %d",
				num_columnas_fijo);
	}

	return 0;
}

/*int init_grafo(tipo_dato[3][MAX_FILAS_INPUT], grafo_contexto *ctx,
 int num_filas, bool
 usar_hashes) */
int init_grafo(void *matrix, int num_filas, grafo_contexto *ctx,
		bool usar_hashes, bool relaciones_bidireccionales) {
	int i = 0;
	int contador_nodos = 0;
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado = GRAFO_NADA_ENCONTRADO;
	tipo_dato distancia_actual = 0, indice_nodo_origen_actual = 0,
			indice_nodo_destino_actual = 0;
// XXX: http://stackoverflow.com/questions/11454376/cast-void-pointer-to-integer-array
	tipo_dato (*matrix_int)[3] = NULL;
	nodo nodo_tmp;
	nodo *nodo_origen_actual = NULL;
	nodo *nodo_destino_actual = NULL;
	nodo *nodos_encontrados[2] = { NULL };

	matrix_int = (tipo_dato (*)[3]) matrix;
	caca_log_debug("despues de acer el cacast");

	memset((void * ) ctx, 0, sizeof(grafo_contexto));
	caca_log_debug("despues de acer el set de ceros");
	memset((void * ) ctx->matrix_distancias, MAX_VALOR,
			sizeof(ctx->matrix_distancias));

	memset((void * ) &nodo_tmp, 0, sizeof(nodo));

	caca_log_debug("despues de inicializar contexto %s", "mierdadsdsadsa");

	caca_imprime_matrix(matrix, num_filas, NULL, 3);

	for (i = 0; i < num_filas; i++) {
		indice_nodo_origen_actual = *(*(matrix_int + i) + GRAFO_NODO_ORIGEN);
		indice_nodo_destino_actual = *(*(matrix_int + i) + GRAFO_NODO_DESTINO);
		distancia_actual = *(*(matrix_int + i) + GRAFO_DISTANCIA_ENTRE_NODOS);

		caca_log_debug("En fila %d, origen %ld, destino %ld, distancia %ld", i,
				indice_nodo_origen_actual, indice_nodo_destino_actual,
				distancia_actual);

		nodo_tmp.indice = indice_nodo_origen_actual;

		tipo_resultado = busqueda_binaria(ctx->inicio, &nodo_tmp,
				GRAFO_PRINCIPAL, (void *) &nodos_encontrados);

		switch (tipo_resultado) {
		case GRAFO_NODO_ENCONTRADO:
			nodo_origen_actual = *nodos_encontrados;
			break;
		case GRAFO_NODOS_PRE_POST_ENCONTRADOS:
			nodo_origen_actual = grafo_nodo_alloc(ctx, 1);
			nodo_origen_actual->indice = indice_nodo_origen_actual;
			caca_log_debug("anadiendo %p a lista principal, entre %p y %p",
					nodo_origen_actual, *nodos_encontrados,
					*(nodos_encontrados + 1))
			;
			grafo_insertar_nodo(*nodos_encontrados, *(nodos_encontrados + 1),
					nodo_origen_actual, GRAFO_PRINCIPAL);
//			if (*(nodos_encontrados + 1) == ctx->inicio) {
			if (!*nodos_encontrados) {
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_PRINCIPAL) = *grafo_apuntador_num_nodos_asociados(
						ctx->inicio, GRAFO_PRINCIPAL) + 1;
				ctx->inicio = nodo_origen_actual;
			} else {
				(*grafo_apuntador_num_nodos_asociados(ctx->inicio,
						GRAFO_PRINCIPAL))++;
			}
			*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
					GRAFO_INDICE) = -1;
			*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
					GRAFO_DISTANCIA) = -1;
			contador_nodos++;
			break;
		case GRAFO_NADA_ENCONTRADO:
			nodo_origen_actual = grafo_nodo_alloc(ctx, 1);
			nodo_origen_actual->indice = indice_nodo_origen_actual;
			ctx->inicio = nodo_origen_actual;
			*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
					GRAFO_PRINCIPAL) = 0;
			*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
					GRAFO_INDICE) = -1;
			*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
					GRAFO_DISTANCIA) = -1;
			caca_log_debug("Se inicia la lista de nodos en ctx")
			;
			contador_nodos++;
			break;
		default:
			perror("no se pudo configurar ctx d graph");
			exit(1);
			break;
		}

		nodo_destino_actual = grafo_nodo_alloc(ctx, 1);
		nodo_destino_actual->distancia = distancia_actual;
		nodo_destino_actual->indice = indice_nodo_destino_actual;

		caca_log_debug("insertando nodo %p en lista de indices de %p",
				nodo_destino_actual, nodo_origen_actual);
		grafo_anadir_nodo(nodo_origen_actual, nodo_destino_actual,
				GRAFO_INDICE);
		caca_log_debug("insertando nodo %p en lista de distancias de %p",
				nodo_destino_actual, nodo_origen_actual);
		grafo_anadir_nodo(nodo_origen_actual, nodo_destino_actual,
				GRAFO_DISTANCIA);

		if (usar_hashes) {
			ctx->matrix_distancias[indice_nodo_origen_actual][indice_nodo_destino_actual] =
					distancia_actual;
			*(ctx->referencias_nodos_por_indice + indice_nodo_origen_actual) =
					nodo_origen_actual;
		}

		if (relaciones_bidireccionales) {
			caca_log_debug("Dando de alta relacion espejo-pendejoº");

			nodo_tmp.indice = indice_nodo_destino_actual;

			tipo_resultado = busqueda_binaria(ctx->inicio, &nodo_tmp,
					GRAFO_PRINCIPAL, (void *) &nodos_encontrados);

			switch (tipo_resultado) {
			case GRAFO_NODO_ENCONTRADO:
				nodo_origen_actual = *nodos_encontrados;
				break;
			case GRAFO_NODOS_PRE_POST_ENCONTRADOS:
				nodo_origen_actual = grafo_nodo_alloc(ctx, 1);
				nodo_origen_actual->indice = indice_nodo_destino_actual;
				caca_log_debug("anadiendo %p a lista principal, entre %p y %p",
						nodo_origen_actual, *nodos_encontrados,
						*(nodos_encontrados + 1))
				;
				grafo_insertar_nodo(*nodos_encontrados,
						*(nodos_encontrados + 1), nodo_origen_actual,
						GRAFO_PRINCIPAL);
				if (!*nodos_encontrados) {
					*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
							GRAFO_PRINCIPAL) =
							*grafo_apuntador_num_nodos_asociados(ctx->inicio,
									GRAFO_PRINCIPAL) + 1;
					ctx->inicio = nodo_origen_actual;
				} else {
					(*grafo_apuntador_num_nodos_asociados(ctx->inicio,
							GRAFO_PRINCIPAL))++;
				}
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_INDICE) = -1;
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_DISTANCIA) = -1;
				contador_nodos++;
				break;
			case GRAFO_NADA_ENCONTRADO:
				nodo_origen_actual = grafo_nodo_alloc(ctx, 1);
				nodo_origen_actual->indice = indice_nodo_destino_actual;
				ctx->inicio = nodo_origen_actual;
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_PRINCIPAL) = 0;
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_INDICE) = -1;
				*grafo_apuntador_num_nodos_asociados(nodo_origen_actual,
						GRAFO_DISTANCIA) = -1;
				caca_log_debug("Se inicia la lista de nodos en ctx")
				;
				contador_nodos++;
				break;
			default:
				perror("no se pudo configurar ctx d graph");
				exit(1);
				break;
			}

			nodo_destino_actual = grafo_nodo_alloc(ctx, 1);
			nodo_destino_actual->distancia = distancia_actual;
			nodo_destino_actual->indice = indice_nodo_origen_actual;

			caca_log_debug("insertando nodo %p en lista de indices de %p",
					nodo_destino_actual, nodo_origen_actual);
			grafo_anadir_nodo(nodo_origen_actual, nodo_destino_actual,
					GRAFO_INDICE);
			caca_log_debug("insertando nodo %p en lista de distancias de %p",
					nodo_destino_actual, nodo_origen_actual);
			grafo_anadir_nodo(nodo_origen_actual, nodo_destino_actual,
					GRAFO_DISTANCIA);

			if (usar_hashes) {
				ctx->matrix_distancias[indice_nodo_destino_actual][indice_nodo_origen_actual] =
						distancia_actual;
				*(ctx->referencias_nodos_por_indice + indice_nodo_destino_actual) =
						nodo_origen_actual;
			}

		}

	}

	return (contador_nodos);
}

nodo *grafo_nodo_alloc(grafo_contexto *ctx, int localidades_solicitadas) {
	nodo *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
#ifdef GRAFO_DEBUG_ALLOC
		caca_log_debug("el inicio actual es %p",
				ctx->nodos_disponibles + ctx->localidades_usadas);
#endif
	}
#ifdef GRAFO_DEBUG_ALLOC
	caca_log_debug(
			"las localidades usadas son %d, la direccion regresada es %p, cuyo inicio es %p",
			ctx->localidades_usadas, inicio_localidades_allocadas,
			ctx->nodos_disponibles);
#endif
	return inicio_localidades_allocadas;
}

GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_lineal(nodo *inicio, nodo *nodo_a_buscar,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda, void *nodos_encontrados,
		int limite_nodos_busqueda) {
	int num_nodos_recorridos = 0;
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado = GRAFO_NADA_ENCONTRADO;
	char buffer[MAX_TAM_CADENA] = { '\0' };
	char buffer1[MAX_TAM_CADENA] = { '\0' };
	nodo *nodo_actual = NULL;
	nodo *nodo_anterior = NULL;
	nodo **nodos_encontrados_int = NULL;

	nodos_encontrados_int = ((nodo **) nodos_encontrados);

	nodo_actual = inicio;
//	GRAFO_AVANZAR_NODO(nodo_actual, criterio_busqueda, verdadero);

	caca_log_debug("nodo inicial %p, nodo a buscar %p, limite de buskeda %d",
			inicio, nodo_a_buscar, limite_nodos_busqueda);

	while (nodo_actual && num_nodos_recorridos <= limite_nodos_busqueda
			&& tipo_resultado == GRAFO_NADA_ENCONTRADO) {
		caca_log_debug(
				"Comparando actual %s con el q c busca %s con criterio %s",
				grafo_nodo_a_cadena(nodo_actual,buffer,NULL),
				grafo_nodo_a_cadena(nodo_a_buscar,buffer1,NULL),
				GRAFO_NOMBRES_CRITERIOS_ORDENACION[criterio_busqueda]);
		switch (criterio_busqueda) {
		case GRAFO_VALOR:
			nodo_anterior = nodo_actual;
			if (nodo_actual->valor == nodo_a_buscar->valor) {
				tipo_resultado = GRAFO_NODO_ENCONTRADO;
				continue;
			}
			if (nodo_actual->valor > nodo_a_buscar->valor) {
				tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
				continue;
			}
			nodo_actual = nodo_actual->siguiente_valor;
			break;
		case GRAFO_DISTANCIA:
			nodo_anterior = nodo_actual;
			caca_log_debug("Se asigno nodo anterior en distancia")
			;
			if (nodo_actual->distancia == nodo_a_buscar->distancia) {
				tipo_resultado = GRAFO_NODO_ENCONTRADO;
				continue;
			}
			if (nodo_actual->distancia > nodo_a_buscar->distancia) {
				tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
				continue;
			}
			nodo_actual = nodo_actual->siguiente_distancia;
			caca_log_debug("Avanzado en distancia con tipo resultado %d",
					tipo_resultado)
			;
			break;
		case GRAFO_INDICE:
			nodo_anterior = nodo_actual;
			caca_log_debug(
					"comparando indices nodo actual %ld con nodo a buscar %ld",
					nodo_actual->indice, nodo_a_buscar->indice)
			;
			if (nodo_actual->indice == nodo_a_buscar->indice) {
				tipo_resultado = GRAFO_NODO_ENCONTRADO;
				continue;
			}
			if (nodo_actual->indice > nodo_a_buscar->indice) {
				tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
				continue;
			}
			nodo_actual = nodo_actual->siguiente_indice;
			caca_log_debug("Avanzado en indice con tipo resultado %d",
					tipo_resultado)
			;
			break;
		case GRAFO_PRINCIPAL:
			nodo_anterior = nodo_actual;
			if (nodo_actual->indice == nodo_a_buscar->indice) {
				tipo_resultado = GRAFO_NODO_ENCONTRADO;
				continue;
			}
			if (nodo_actual->indice > nodo_a_buscar->indice) {
				tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
				continue;
			}
			nodo_actual = nodo_actual->siguiente;
			break;
		default:
			perror("en busqueda lineal hubo un error culero al buscar");
			exit(1);
			break;
		}
		caca_log_debug("Salio del case con %d", tipo_resultado);
		num_nodos_recorridos++;
	}

	/*
	 if (tipo_resultado != GRAFO_NADA_ENCONTRADO) {
	 num_nodos_recorridos++;
	 } else {
	 if (nodo_actual) {
	 tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
	 }
	 }
	 */
	if (tipo_resultado == GRAFO_NADA_ENCONTRADO && nodo_actual) {
		tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
	}

	if (nodo_actual && num_nodos_recorridos <= limite_nodos_busqueda) {
		if (tipo_resultado == GRAFO_NODO_ENCONTRADO) {
			*nodos_encontrados_int = nodo_actual;
		}
		if (tipo_resultado == GRAFO_NODOS_PRE_POST_ENCONTRADOS) {
			switch (criterio_busqueda) {
			case GRAFO_VALOR:
				*nodos_encontrados_int = nodo_actual->anterior_valor;
				*(nodos_encontrados_int + 1) = nodo_actual;
				break;
			case GRAFO_DISTANCIA:
				*nodos_encontrados_int = nodo_actual->anterior_distancia;
				*(nodos_encontrados_int + 1) = nodo_actual;
				break;
			case GRAFO_INDICE:
				*nodos_encontrados_int = nodo_actual->anterior_indice;
				*(nodos_encontrados_int + 1) = nodo_actual;
				break;
			case GRAFO_PRINCIPAL:
				*nodos_encontrados_int = nodo_actual->anterior;
				*(nodos_encontrados_int + 1) = nodo_actual;
				break;
			default:
				perror(
						"en busqueda lineal hubo un error culero al asignar resultados");
				exit(EXIT_FAILURE);
				break;
			}
		}
	} else {
		caca_log_debug("Se reccorrio toda la lista sin encontrar");
		if (nodo_anterior) {
			caca_log_debug(
					"HAy un nodo anterior, lo q significa que al menos c recorrio un nodo");
			tipo_resultado = GRAFO_NODOS_PRE_POST_ENCONTRADOS;
			switch (criterio_busqueda) {
			case GRAFO_VALOR:
				*nodos_encontrados_int = nodo_anterior;
				*(nodos_encontrados_int + 1) = nodo_anterior->siguiente_valor;
				break;
			case GRAFO_DISTANCIA:
				*nodos_encontrados_int = nodo_anterior;
				*(nodos_encontrados_int + 1) =
						nodo_anterior->siguiente_distancia;
				break;
			case GRAFO_INDICE:
				*nodos_encontrados_int = nodo_anterior;
				*(nodos_encontrados_int + 1) = nodo_anterior->siguiente_indice;
				break;
			case GRAFO_PRINCIPAL:
				*nodos_encontrados_int = nodo_anterior;
				*(nodos_encontrados_int + 1) = nodo_anterior->siguiente;
				caca_log_debug("El nodo anterior %p, el nodo siguiente %p",
						*nodos_encontrados_int, *(nodos_encontrados_int + 1))
				;
				break;
			default:
				perror(
						"en busqueda lineal hubo un error culero al asignar resultados sin nodo actual");
				exit(EXIT_FAILURE);
				break;
			}
		}
	}
	return tipo_resultado;
}

GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_binaria(nodo *inicio,
		nodo *nodo_a_buscar, GRAFO_CRITERIOS_ORDENACION criterio_busqueda,
		void *nodos_encontrados) {
	int i = 0;
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado = GRAFO_NADA_ENCONTRADO;
	char buffer[MAX_TAM_CADENA];
	nodo *nodo_actual = NULL;
	nodo *arreglo_nodos_tmp[MAX_NODOS] = { NULL };

	nodo_actual = inicio;

	caca_log_debug("El nodo inicial %p", inicio);

	if (!nodo_actual) {
		return tipo_resultado;
	}

	caca_log_debug("Antes de creaer el arreglo temporal");
	do {
		caca_log_debug("En iteracion %d", i);
		*(arreglo_nodos_tmp + i) = nodo_actual;
		caca_log_debug("Nodo actual %p", nodo_actual);
		caca_log_debug("en la iteracion %d  el nodo es %s", i,
				grafo_nodo_a_cadena(nodo_actual,buffer,NULL));
		GRAFO_AVANZAR_NODO(nodo_actual, criterio_busqueda, falso);
		i++;
	} while (nodo_actual);

	caca_log_debug("Despues de creaer el arreglo temporal");

	tipo_resultado = busqueda_binaria_recursiva(inicio, arreglo_nodos_tmp,
			nodo_a_buscar, criterio_busqueda, nodos_encontrados, 0,
			*grafo_apuntador_num_nodos_asociados(inicio, criterio_busqueda));

	caca_log_debug("Al salir %d", tipo_resultado);

	return tipo_resultado;
}

GRAFO_TIPO_RESULTADO_BUSQUEDA busqueda_binaria_recursiva(nodo *inicio,
		nodo **arreglo_nodos, nodo *nodo_a_buscar,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda, void *nodos_encontrados,
		int indice_inicial, int indice_final) {
	int resultado_comparacion = 0;
	int indice_medio = 0;
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado = GRAFO_NADA_ENCONTRADO;
	char cadena1[MAX_TAM_CADENA] = { '\0' };
	char cadena2[MAX_TAM_CADENA] = { '\0' };
	nodo **nodos_encontrados_int = NULL;
	nodos_encontrados_int = ((nodo **) nodos_encontrados);

	caca_log_debug("entrando con inicio %d y fin %d", indice_inicial,
			indice_final);
	caca_log_debug("nodo inicial %p, nodo a buscar %p", inicio, nodo_a_buscar);

	if ((indice_final - indice_inicial) <= GRAFO_LIMITE_ORDENACION_LINEAL) {
		caca_log_debug("buscando linealmento, ventana menor a %d",
				GRAFO_LIMITE_ORDENACION_LINEAL);
		tipo_resultado = busqueda_lineal(*(arreglo_nodos + indice_inicial),
				nodo_a_buscar, criterio_busqueda, nodos_encontrados,
				indice_final - indice_inicial + 1);
	} else {
		indice_medio = (indice_inicial + indice_final) / 2;
		caca_log_debug("el indice medio pendejo es %d", indice_medio);
		resultado_comparacion = grafo_comparar_nodos(nodo_a_buscar,
				*(arreglo_nodos + indice_medio), criterio_busqueda);
		caca_log_debug("la comparacion se hizo");
		caca_log_debug("comparando nodo %s con %s (posicion %d), resultado %d",
				grafo_nodo_a_cadena(nodo_a_buscar, cadena1,NULL),
				grafo_nodo_a_cadena(*(arreglo_nodos + indice_medio), cadena2,NULL),
				indice_medio, resultado_comparacion);
		if (resultado_comparacion == CACA_COMPARACION_IZQ_IGUAL) {
			tipo_resultado = GRAFO_NODO_ENCONTRADO;
			*nodos_encontrados_int = *(arreglo_nodos + indice_medio);
		} else {
			if (resultado_comparacion == CACA_COMPARACION_IZQ_MENOR) {
				indice_final = indice_medio - 1;
			} else {
				if (resultado_comparacion == CACA_COMPARACION_IZQ_MAYOR) {
					indice_inicial = indice_medio + 1;
				} else {
					perror("What the fuck?? busqueda_binaria_recursiva");
					exit(1);
				}
			}
			caca_log_debug(
					"recursividad arreglo_nodos %d final %d, el medio es %d",
					indice_inicial, indice_final, indice_medio);
			tipo_resultado = busqueda_binaria_recursiva(inicio, arreglo_nodos,
					nodo_a_buscar, criterio_busqueda, nodos_encontrados,
					indice_inicial, indice_final);
			caca_log_debug("recursividad resultado %d ", tipo_resultado);
		}
	}

	caca_log_debug("al salir d la funcion %d", tipo_resultado);

	return tipo_resultado;
}

// XXX: http://stackoverflow.com/questions/2679182/have-macro-return-a-value
static inline int grafo_comparar_nodos(nodo *nodo1, nodo *nodo2,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda) {
	tipo_dato val1 = 0, val2 = 0;
	int resultado_comparacion;
	char cadena1[MAX_TAM_CADENA];
	char cadena2[MAX_TAM_CADENA];

	caca_log_debug("entro a grafo_comparar_nodos");

	caca_log_debug("comparando %s con %s",
			grafo_nodo_a_cadena(nodo1, cadena1,NULL),
			grafo_nodo_a_cadena(nodo2, cadena2,NULL));

	switch (criterio_busqueda) {
	case GRAFO_VALOR:
		val1 = nodo1->valor;
		val2 = nodo2->valor;
		break;
	case GRAFO_DISTANCIA:
		val1 = nodo1->distancia;
		val2 = nodo2->distancia;
		break;
	case GRAFO_INDICE:
	case GRAFO_PRINCIPAL:
		val1 = nodo1->indice;
		val2 = nodo2->indice;
		break;
	default:
		perror("en GRAFO_COMPARAR_NODOS %s un error culero al buscar");
		exit(EXIT_FAILURE);
		break;
	}
	if (val1 < val2) {
		resultado_comparacion = CACA_COMPARACION_IZQ_MENOR;
	} else {
		if (val1 > val2) {
			resultado_comparacion = CACA_COMPARACION_IZQ_MAYOR;
		} else {
			resultado_comparacion = CACA_COMPARACION_IZQ_IGUAL;
		}
	}
	caca_log_debug("resultado de comparacion %s con %s %d",
			grafo_nodo_a_cadena(nodo1, cadena1,NULL),
			grafo_nodo_a_cadena(nodo2, cadena2,NULL), resultado_comparacion);
	return resultado_comparacion;
}


static inline char *grafo_nodo_a_cadena(nodo *node, char *cadena_buffer,
		int *characteres_escritos) {

	if (!node) {
		perror("q pedo, pasaron un nodo vacio!");
		abort();
	}

	if (characteres_escritos) {
//		caca_log_debug("Se regresaran los characteres escribtos");
		*characteres_escritos = sprintf(cadena_buffer,
				"{valor:%ld,indice:%ld,distancia:%ld} (%p) ", node->valor,
				node->indice, node->distancia, node);
	} else {

		//	caca_log_debug("No se regresaran los characteres escribtos %p", node);
		sprintf(cadena_buffer, "{valor:%ld,indice:%ld,distancia:%ld} (%p) ",
				node->valor, node->indice, node->distancia, node);
	}

//	caca_log_debug("Termina conversion");
	return cadena_buffer;
}

int caca_apuntador_valido(void *p) {
//	extern char _etext;
//	return (p != NULL ) && ((char*) p > &_etext);
	return (p != NULL );
}

void grafo_insertar_nodo(nodo *nodo_anterior, nodo *nodo_siguiente,
		nodo *nodo_a_insertar, GRAFO_CRITERIOS_ORDENACION criterio_busqueda) {
	nodo **apuntador_nodo_anterior = NULL;
	nodo **apuntador_nodo_siguiente = NULL;
	nodo **nodo_a_insertar_siguente = NULL;
	nodo **nodo_a_insertar_anterior = NULL;

	if (!nodo_anterior && !nodo_siguiente) {
		perror("grafo_insertar_nodo no puede continuar");
		exit(1);
	}

	switch (criterio_busqueda) {
	case GRAFO_VALOR:
		apuntador_nodo_anterior =
				nodo_anterior ? &nodo_anterior->siguiente_valor : NULL;
		apuntador_nodo_siguiente =
				nodo_siguiente ? &nodo_siguiente->anterior_valor : NULL;
		nodo_a_insertar_siguente = &nodo_a_insertar->siguiente_valor;
		nodo_a_insertar_anterior = &nodo_a_insertar->anterior_valor;
		break;
	case GRAFO_DISTANCIA:
		apuntador_nodo_anterior =
				nodo_anterior ? &nodo_anterior->siguiente_distancia : NULL;
		apuntador_nodo_siguiente =
				nodo_siguiente ? &nodo_siguiente->anterior_distancia : NULL;
		nodo_a_insertar_siguente = &nodo_a_insertar->siguiente_distancia;
		nodo_a_insertar_anterior = &nodo_a_insertar->anterior_distancia;
		break;
	case GRAFO_INDICE:
		apuntador_nodo_anterior =
				nodo_anterior ? &nodo_anterior->siguiente_indice : NULL;
		apuntador_nodo_siguiente =
				nodo_siguiente ? &nodo_siguiente->anterior_indice : NULL;
		nodo_a_insertar_siguente = &nodo_a_insertar->siguiente_indice;
		nodo_a_insertar_anterior = &nodo_a_insertar->anterior_indice;
		break;
	case GRAFO_PRINCIPAL:
		apuntador_nodo_anterior =
				nodo_anterior ? &nodo_anterior->siguiente : NULL;
		apuntador_nodo_siguiente =
				nodo_siguiente ? &nodo_siguiente->anterior : NULL;
		nodo_a_insertar_siguente = &nodo_a_insertar->siguiente;
		nodo_a_insertar_anterior = &nodo_a_insertar->anterior;
		caca_log_debug(
				"insertando %p, nodo a insrtar anterior %p, cuyo valor es %p, nodo a insertar siguiente %p, cuyo valor es %p",
				nodo_a_insertar, nodo_a_insertar_anterior,
				*nodo_a_insertar_anterior, nodo_a_insertar_siguente,
				*nodo_a_insertar_siguente)
		;
		break;
	default:
		perror("fallo en grafo_insertar_nodo");
		exit(EXIT_FAILURE);
		break;
	}
	if (apuntador_nodo_anterior) {
		*apuntador_nodo_anterior = nodo_a_insertar;
	}
	if (apuntador_nodo_siguiente) {
		*apuntador_nodo_siguiente = nodo_a_insertar;
	}
	*nodo_a_insertar_siguente = nodo_siguiente;
	*nodo_a_insertar_anterior = nodo_anterior;
	caca_log_debug("nodo %p entre %p y %p", nodo_a_insertar, nodo_anterior,
			nodo_siguiente);
}

void grafo_anadir_nodo(nodo *nodo_inicial, nodo *nodo_a_anadir,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda) {
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado;
	nodo *nodo_anterior = NULL;
	nodo *nodo_siguiente = NULL;
	nodo *nodo_inicial_tmp = NULL;
	nodo *nodos_encontrados[2] = { NULL };

	caca_log_debug(
			"Anadiendo nodo %ld (%p) a lista %ld (%p) de %s, num de nodos asociados %d",
			nodo_a_anadir->indice, nodo_a_anadir, nodo_inicial->indice,
			nodo_inicial, GRAFO_NOMBRES_CRITERIOS_ORDENACION[criterio_busqueda],
			*grafo_apuntador_num_nodos_asociados(nodo_inicial, criterio_busqueda));

	nodo_inicial_tmp = nodo_inicial;

	if (criterio_busqueda != GRAFO_PRINCIPAL) {
		GRAFO_AVANZAR_NODO(nodo_inicial_tmp, criterio_busqueda, verdadero);
		if (nodo_inicial_tmp) {
			*grafo_apuntador_num_nodos_asociados(nodo_inicial_tmp,
					criterio_busqueda) = *grafo_apuntador_num_nodos_asociados(
					nodo_inicial, criterio_busqueda);
		}
	}

	tipo_resultado = busqueda_binaria(nodo_inicial_tmp, nodo_a_anadir,
			criterio_busqueda, (void *) &nodos_encontrados);

	switch (tipo_resultado) {
	case GRAFO_NODOS_PRE_POST_ENCONTRADOS:
		nodo_anterior = *(nodos_encontrados);
		nodo_siguiente = *(nodos_encontrados + 1);
		break;
	case GRAFO_NODO_ENCONTRADO:
		GRAFO_NODO_SIG_ANT(nodo_anterior, nodo_siguiente, *nodos_encontrados,
				criterio_busqueda)
		;
		break;
	case GRAFO_NADA_ENCONTRADO:
		nodo_anterior = nodo_inicial;
		nodo_siguiente = NULL;
		break;
	default:
		perror("init_grafo error");
		exit(1);
		break;
	}

	grafo_insertar_nodo(nodo_anterior, nodo_siguiente, nodo_a_anadir,
			criterio_busqueda);
	(*grafo_apuntador_num_nodos_asociados(nodo_inicial, criterio_busqueda))++;
	caca_log_debug(
			"al terminar de añadir el # de nodos asociados en principal %d",
			*grafo_apuntador_num_nodos_asociados(nodo_inicial, criterio_busqueda));

	nodo_inicial_tmp = nodo_inicial;

	GRAFO_AVANZAR_NODO(nodo_inicial_tmp, criterio_busqueda, verdadero);
	if (nodo_inicial_tmp) {
		*grafo_apuntador_num_nodos_asociados(nodo_inicial_tmp,
				criterio_busqueda) = *grafo_apuntador_num_nodos_asociados(
				nodo_inicial, criterio_busqueda);
		(*grafo_apuntador_num_nodos_asociados(nodo_inicial_tmp,
				criterio_busqueda))++;
		caca_log_debug(
				"al terminar de añadir el # de nodos asociados en 1ero a buscar %d",
				*grafo_apuntador_num_nodos_asociados(nodo_inicial_tmp, criterio_busqueda));
	}
}

void imprimir_lista_adjacencia(nodo *nodo_inicial) {
	const char *FORMATO_CONCAT_NODO = " --> ";
	int caracteres_escritos = 0;
	char *ap_cadena = NULL;
	char *buffer = NULL;
	nodo *nodo_actual = NULL;
	nodo *nodo_adjacente_actual = NULL;

	nodo_actual = nodo_inicial;

	caca_log_debug("La matrix de adjacencia es:");

	buffer = calloc(1000, sizeof(char));

	while (nodo_actual) {
		nodo_adjacente_actual = nodo_actual;
		ap_cadena = buffer;

		caca_log_debug("Conexiones de nodo %s.",
				grafo_nodo_a_cadena(nodo_adjacente_actual, ap_cadena, &caracteres_escritos));

		strcpy(ap_cadena, GRAFO_NOMBRES_CRITERIOS_ORDENACION[GRAFO_DISTANCIA]);
		ap_cadena += strlen(
				GRAFO_NOMBRES_CRITERIOS_ORDENACION[GRAFO_DISTANCIA]);

		nodo_adjacente_actual = nodo_actual->siguiente_distancia;
		while (nodo_adjacente_actual) {

//			caca_log_debug("Direccion nodo adjacente %p", nodo_adjacente_actual);
			strcpy(ap_cadena, FORMATO_CONCAT_NODO);
			ap_cadena += strlen(FORMATO_CONCAT_NODO);
			grafo_nodo_a_cadena(nodo_adjacente_actual, ap_cadena,
					&caracteres_escritos);
			ap_cadena += caracteres_escritos;

			nodo_adjacente_actual = nodo_adjacente_actual->siguiente_distancia;
		}

		caca_log_debug("%s", buffer);

		ap_cadena = buffer;

		strcpy(ap_cadena, GRAFO_NOMBRES_CRITERIOS_ORDENACION[GRAFO_INDICE]);
		ap_cadena += strlen(GRAFO_NOMBRES_CRITERIOS_ORDENACION[GRAFO_INDICE]);

		nodo_adjacente_actual = nodo_actual->siguiente_indice;
		while (nodo_adjacente_actual) {

//			caca_log_debug("Direccion nodo adjacente %p", nodo_adjacente_actual);
			strcpy(ap_cadena, FORMATO_CONCAT_NODO);
			ap_cadena += strlen(FORMATO_CONCAT_NODO);
			grafo_nodo_a_cadena(nodo_adjacente_actual, ap_cadena,
					&caracteres_escritos);
			ap_cadena += caracteres_escritos;

			nodo_adjacente_actual = nodo_adjacente_actual->siguiente_indice;

		}

		caca_log_debug("%s", buffer);

		nodo_actual = nodo_actual->siguiente;

	}
}

static inline int *grafo_apuntador_num_nodos_asociados(nodo *nodo,
		GRAFO_CRITERIOS_ORDENACION criterio_busqueda) {
	int *num_nodos = NULL;
	switch (criterio_busqueda) {
	case GRAFO_VALOR:
		num_nodos = &(nodo)->num_nodos_asociados_valor;
		break;
	case GRAFO_DISTANCIA:
		num_nodos = &(nodo)->num_nodos_asociados_distancia;
		break;
	case GRAFO_INDICE:
		num_nodos = &(nodo)->num_nodos_asociados_indice;
		break;
	case GRAFO_PRINCIPAL:
		num_nodos = &(nodo)->num_nodos_asociados;
		break;
	default:
		perror("en GRAFO_NUM_NODOS_ASOCIADOS hubo un error culero al buscar");
		exit(EXIT_FAILURE);
		break;
	}
	return num_nodos;
}

void arbol_avl_init(arbol_binario_contexto *ctx, tipo_dato *indices,
		tipo_dato *datos, int num_datos,
		nodo_arbol_binario **arreglo_referencias_nodos) {
	int i = 0;
	tipo_dato dato_actual = 0;
	nodo_arbol_binario *nodo_actual = NULL;

	memset((void * ) ctx, 0, sizeof(arbol_binario_contexto));
	memset((void * ) ctx->nodos_disponibles, 0, sizeof(ctx->nodos_disponibles));
	caca_log_debug("initializando con num de datos %d", num_datos);

	for (i = 0; i < num_datos; i++) {
		caca_log_debug("en contador %d indice %ld", i,
				indices ? *(indices + i) : i + 1);
		if (indices && *(indices + i) == ARBOL_AVL_INDICE_INVALIDO) {
			caca_log_debug(
					"Ignorando indice %d, %ld, contienen indice invalido", i,
					*(indices + i));
			continue;
		}

		if (!ctx->raiz) {
			ctx->raiz = arbol_binario_nodo_allocar(ctx, 1);
			if (indices) {
				ctx->raiz->indice = *(indices + i);
			} else {
				ctx->raiz->indice = 1;
			}
			if (arreglo_referencias_nodos) {
				if (indices) {
					*(arreglo_referencias_nodos + *(indices + i)) = ctx->raiz;

				} else {
					*(arreglo_referencias_nodos + 1) = ctx->raiz;
				}
			}
			ctx->raiz->valor = *(datos + i);
			caca_log_debug("dada de alta raiz %d,%ld,%ld", i, ctx->raiz->indice,
					ctx->raiz->valor);
			continue;
		}

		dato_actual = *(datos + i);
		nodo_actual = arbol_binario_nodo_allocar(ctx, 1);

		nodo_actual->valor = dato_actual;
		if (indices) {
			nodo_actual->indice = *(indices + i);
		} else {
			nodo_actual->indice = i + 1;
		}

		arbol_avl_insertar(&ctx->raiz, nodo_actual, ctx->no_indices_repetidos);
		if (arreglo_referencias_nodos) {
			if (indices) {
				*(arreglo_referencias_nodos + *(indices + i)) = nodo_actual;

			} else {
				*(arreglo_referencias_nodos + i + 1) = nodo_actual;
			}
		}
		caca_log_debug("Raiz actual %ld", ctx->raiz->valor);
	}
}

void arbol_avl_insertar(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_insertar, bool no_indices_repetidos) {
	nodo_arbol_binario *raiz_int = NULL;

	raiz_int = *raiz;
	char *buffer = NULL;
	char *buffer1 = NULL;

	buffer = calloc(1000, sizeof(char));
	buffer1 = calloc(1000, sizeof(char));

	caca_log_debug("Insertando nodo %s, ancestro actual %s",
			arbol_binario_nodo_a_cadena(nodo_a_insertar,buffer,NULL),
			raiz_int? arbol_binario_nodo_a_cadena(raiz_int,buffer1,NULL):"No hay nada en raiz");

	if (!raiz_int) {
		*raiz = nodo_a_insertar;
		return;
	}

	switch (arbol_avl_compara_nodos(raiz_int, nodo_a_insertar)) {
	case CACA_COMPARACION_IZQ_MENOR:
		caca_log_debug("Insercion BST a la der")
		;
		if (raiz_int->hijo_der) {
			caca_log_debug("Recursiva");
			arbol_avl_insertar(&raiz_int->hijo_der, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			raiz_int->hijo_der = nodo_a_insertar;
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_MAYOR:
		caca_log_debug("Insercion BST a la izq")
		;
		if (raiz_int->hijo_izq) {
			caca_log_debug("Recursiva %p", &raiz_int->hijo_izq);
			arbol_avl_insertar(&raiz_int->hijo_izq, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			caca_log_debug("Directa");
			raiz_int->hijo_izq = nodo_a_insertar;
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_IGUAL:
		if (no_indices_repetidos) {
			perror("NO mames, una llave repetida, ahhhhh !");
			exit(1);
		} else {
			caca_log_debug("Insercion BST a la der aunke las llaves son =s");
			if (raiz_int->hijo_der) {
				caca_log_debug("Recursiva");
				arbol_avl_insertar(&raiz_int->hijo_der, nodo_a_insertar,
						no_indices_repetidos);
			} else {
				raiz_int->hijo_der = nodo_a_insertar;
				ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
			}
		}
		break;
	default:
		perror("NO mames, resultado increible en arbol_avl_insertar!");
		exit(1);
		break;
	}

	caca_log_debug("Echa la insercion BST de %ld en ancestro %ld",
			ARBOL_AVL_GET_VALOR(nodo_a_insertar), ARBOL_AVL_GET_VALOR(raiz_int));
	ARBOL_AVL_ACTUALIZAR_ALTURA(raiz_int);
	caca_log_debug("algura es %d", raiz_int->altura);
	caca_log_debug("hijo der %ld %p %p", ARBOL_AVL_GET_VALOR((*raiz)->hijo_izq),
			(*raiz)->hijo_izq, &(*raiz)->hijo_izq);

	switch (arbol_avl_diferencia_alturas_subarboles(raiz_int, 1, verdadero)) {
	case ARBOL_AVL_ALTURA_CARGADA_IZQ:
		caca_log_debug("Arbol cagado a la izq en %ld", raiz_int->valor)
		;
		if (ARBOL_AVL_GET_VALOR(
				raiz_int->hijo_izq) < ARBOL_AVL_GET_VALOR(nodo_a_insertar)) {
			caca_log_debug("con hijo a la der");
			arbol_binario_rotar_izq(&raiz_int->hijo_izq);
		}
		arbol_binario_rotar_der(raiz);
		caca_log_debug("Ahora la raiz %p %ld, izq %ld, der %ld", raiz,
				ARBOL_AVL_GET_VALOR(*raiz),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_izq),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_der))
		;
		break;
	case ARBOL_AVL_ALTURA_CARGADA_DER:
		caca_log_debug("Arbol cagado a la der en %ld", raiz_int->valor)
		;
		if (ARBOL_AVL_GET_VALOR(
				raiz_int->hijo_der) > ARBOL_AVL_GET_VALOR(nodo_a_insertar)) {
			caca_log_debug("con hijo a la izq");
			arbol_binario_rotar_der(&raiz_int->hijo_der);
		}
		arbol_binario_rotar_izq(raiz);
		caca_log_debug("Ahora la raiz %p %ld, izq %ld, der %ld", raiz,
				ARBOL_AVL_GET_VALOR(*raiz),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_izq),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_der))
		;
		break;
	case ARBOL_AVL_ALTURA_BALANCEADA:
		caca_log_debug("Excelente, en nodo %s, altura balancelada",
				arbol_binario_nodo_a_cadena(raiz_int,buffer,NULL))
		;
		break;
	default:
		perror("error en altura indeterminada, verga");
		exit(1);
		break;
	}

	caca_log_debug("termino con valor %ld, raiz %p y ap raiz %p",
			ARBOL_AVL_GET_VALOR(*raiz), *raiz, raiz);
	arbol_binario_recorrido_preoder(*raiz);
}

static inline int arbol_avl_compara_nodos(nodo_arbol_binario *nodo1,
		nodo_arbol_binario *nodo2) {
	caca_log_debug("Comparando %ld con %ld", nodo1->valor, nodo2->valor);
	if (nodo1->valor < nodo2->valor) {
		return CACA_COMPARACION_IZQ_MENOR;
	} else {
		if (nodo1->valor > nodo2->valor) {
			return CACA_COMPARACION_IZQ_MAYOR;
		} else {
			return CACA_COMPARACION_IZQ_IGUAL;
		}
	}
}

static inline int caca_int_max(int a, int b) {
	return (a > b) ? a : b;
}

static inline int arbol_avl_diferencia_alturas_subarboles(
		nodo_arbol_binario *nodo, int tolerancia,
		bool considerar_balanceado_cargado_der) {
	int diferencia_alturas = 0;
	diferencia_alturas = ARBOL_AVL_GET_ALTURA(
			nodo->hijo_izq) - ARBOL_AVL_GET_ALTURA(nodo->hijo_der);
	caca_log_debug("La diferecnai entre %ld de %ld y %ld de %ld es resultao %d",
			ARBOL_AVL_GET_ALTURA(nodo->hijo_izq),
			ARBOL_AVL_GET_INDICE(nodo->hijo_izq),
			ARBOL_AVL_GET_ALTURA(nodo->hijo_der),
			ARBOL_AVL_GET_INDICE(nodo->hijo_der), diferencia_alturas);
	if (considerar_balanceado_cargado_der) {
		return diferencia_alturas < 0 - tolerancia ?
				ARBOL_AVL_ALTURA_CARGADA_DER :
				diferencia_alturas > tolerancia ?
						ARBOL_AVL_ALTURA_CARGADA_IZQ :
						ARBOL_AVL_ALTURA_BALANCEADA;
	} else {
		return diferencia_alturas < 0 - tolerancia ?
				ARBOL_AVL_ALTURA_CARGADA_DER :
				diferencia_alturas > tolerancia ?
						ARBOL_AVL_ALTURA_CARGADA_IZQ :
						ARBOL_AVL_ALTURA_BALANCEADA;
	}
}

static inline void arbol_binario_rotar_izq(nodo_arbol_binario **nodo) {
	nodo_arbol_binario *nodo_int = NULL;
	nodo_arbol_binario *hijo_der = NULL;
	nodo_arbol_binario *hijo_der_subarbol_izq = NULL;

	caca_log_debug("rotando %ld", ARBOL_AVL_GET_VALOR(*nodo));

	nodo_int = *nodo;
	hijo_der = nodo_int->hijo_der;
	caca_log_debug("Asignado hijo der %ld", ARBOL_AVL_GET_VALOR(hijo_der));
	hijo_der_subarbol_izq = hijo_der->hijo_izq;
	caca_log_debug("Asignado subarbol izq hijo der %ld",
			ARBOL_AVL_GET_VALOR(hijo_der_subarbol_izq));

	caca_log_debug("Antes de la rotacion");

	nodo_int->hijo_der = hijo_der_subarbol_izq;
	hijo_der->hijo_izq = nodo_int;

	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_der, ARBOL_AVL_GET_PADRE(nodo_int));
	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_der_subarbol_izq, nodo_int);
	ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_int, hijo_der);

	caca_log_debug("Rotados los nodos");
	ARBOL_AVL_ACTUALIZAR_ALTURA(nodo_int);
	ARBOL_AVL_ACTUALIZAR_ALTURA(hijo_der);
	caca_log_debug("Alturas actualizadas");

	*nodo = hijo_der;

}

static inline void arbol_binario_rotar_der(nodo_arbol_binario **nodo) {
	nodo_arbol_binario *nodo_int = NULL;
	nodo_arbol_binario *hijo_izq = NULL;
	nodo_arbol_binario *hijo_izq_subarbol_der = NULL;

	caca_log_debug("rotando %ld hijo izq %ld hijo der %ld",
			ARBOL_AVL_GET_VALOR(*nodo), ARBOL_AVL_GET_VALOR((*nodo)->hijo_izq),
			ARBOL_AVL_GET_VALOR((*nodo)->hijo_der));

	nodo_int = *nodo;
	hijo_izq = nodo_int->hijo_izq;
	caca_log_debug("Asignado hijo izq %ld", ARBOL_AVL_GET_VALOR(hijo_izq));
	hijo_izq_subarbol_der = hijo_izq->hijo_der;
	caca_log_debug("Asignado subarbol der hijo izq %ld",
			ARBOL_AVL_GET_VALOR(hijo_izq_subarbol_der));

	caca_log_debug("Antes de la rotacion");

	nodo_int->hijo_izq = hijo_izq_subarbol_der;
	hijo_izq->hijo_der = nodo_int;

	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_izq, ARBOL_AVL_GET_PADRE(nodo_int));
	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_izq_subarbol_der, nodo_int);
	ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_int, hijo_izq);

	caca_log_debug("Rotados los nodos");
	ARBOL_AVL_ACTUALIZAR_ALTURA(nodo_int);
	ARBOL_AVL_ACTUALIZAR_ALTURA(hijo_izq);
	caca_log_debug("Alturas actualizadas");

	*nodo = hijo_izq;

}

static inline char *arbol_binario_nodo_a_cadena(nodo_arbol_binario *node,
		char *cadena_buffer, int *characteres_escritos) {

	int characteres_escritos_int = 0;

	characteres_escritos_int =
			sprintf(cadena_buffer,
					"{indice:%ld, valor:%ld, altura %d, direccion %p, hijo izq:%ld (%p), hijo der:%ld (%p), padre:%ld (%p)}  ",
					node->indice, node->valor, ARBOL_AVL_GET_ALTURA(node), node,
					ARBOL_AVL_GET_VALOR(node->hijo_izq), node->hijo_izq,
					ARBOL_AVL_GET_VALOR(node->hijo_der), node->hijo_der,
					ARBOL_AVL_GET_VALOR(node->padre), node->padre);

	if (characteres_escritos) {
		*characteres_escritos = characteres_escritos_int;
	}
	return cadena_buffer;
}

static inline nodo_arbol_binario *arbol_binario_nodo_allocar(
		arbol_binario_contexto *ctx, int localidades_solicitadas) {
	nodo_arbol_binario *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

void arbol_binario_recorrido_preoder(nodo_arbol_binario *raiz) {
	char buffer[MAX_TAM_CADENA];
	if (!raiz) {
		return;
	}
	caca_log_debug("%s ", arbol_binario_nodo_a_cadena(raiz,buffer,NULL));
	arbol_binario_recorrido_preoder(raiz->hijo_izq);
	arbol_binario_recorrido_preoder(raiz->hijo_der);
}

void arbol_binario_colectar_datos_recorrido_preoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados) {
	if (!raiz) {
		return;
	}
	*(datos_ordenados + (*num_datos_colectados)++) = raiz->valor;
	arbol_binario_colectar_datos_recorrido_preoder(raiz->hijo_izq,
			datos_ordenados, num_datos_colectados);
	arbol_binario_colectar_datos_recorrido_preoder(raiz->hijo_der,
			datos_ordenados, num_datos_colectados);
}

static inline nodo_arbol_binario *arbol_binario_get_nodo_minimo_valor(
		nodo_arbol_binario *raiz) {
	nodo_arbol_binario *nodo_actual = NULL;
	nodo_actual = raiz;
	while (nodo_actual->hijo_izq) {
		nodo_actual = nodo_actual->hijo_izq;
	}
	return nodo_actual;
}

void arbol_binario_borrar_nodo(nodo_arbol_binario **raiz,
		tipo_dato valor_a_borrar) {
	nodo_arbol_binario *raiz_int = NULL;
	nodo_arbol_binario *nodo_min = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
		caca_log_debug("Raiz nula, pq la mandan?");
		return;
	}
	if (raiz_int->valor > valor_a_borrar) {
		arbol_binario_borrar_nodo(&raiz_int->hijo_izq, valor_a_borrar);
	} else {
		if (raiz_int->valor < valor_a_borrar) {
			arbol_binario_borrar_nodo(&raiz_int->hijo_der, valor_a_borrar);
		} else {
			if (!raiz_int->hijo_izq) {
				*raiz = raiz_int->hijo_der;
			} else {
				if (!raiz_int->hijo_der) {
					*raiz = raiz_int->hijo_izq;
				} else {
					nodo_min = arbol_binario_get_nodo_minimo_valor(
							raiz_int->hijo_der);
					raiz_int->valor = nodo_min->valor;
					arbol_binario_borrar_nodo(&raiz_int->hijo_der,
							raiz_int->valor);
				}
			}
		}
	}

}

void arbol_binario_recorrido_inoder(nodo_arbol_binario *raiz) {
	char buffer[MAX_TAM_CADENA];
	if (!raiz) {
		return;
	}
	arbol_binario_recorrido_inoder(raiz->hijo_izq);
	caca_log_debug("%s ", arbol_binario_nodo_a_cadena(raiz,buffer,NULL));
	arbol_binario_recorrido_inoder(raiz->hijo_der);
}

void arbol_binario_colectar_datos_recorrido_inoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados) {
	if (!raiz) {
		return;
	}
	arbol_binario_colectar_datos_recorrido_inoder(raiz->hijo_izq,
			datos_ordenados, num_datos_colectados);
	*(datos_ordenados + (*num_datos_colectados)++) = raiz->valor;
	arbol_binario_colectar_datos_recorrido_inoder(raiz->hijo_der,
			datos_ordenados, num_datos_colectados);
}

void arbol_avl_borrar(nodo_arbol_binario **raiz, tipo_dato valor_a_borrar) {

	nodo_arbol_binario *raiz_int = NULL;
	nodo_arbol_binario *nodo_min = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
		caca_log_debug("Raiz nula, pq la mandan?");
		return;
	}
	if (raiz_int->valor > valor_a_borrar) {
		arbol_avl_borrar(&raiz_int->hijo_izq, valor_a_borrar);
	} else {
		if (raiz_int->valor < valor_a_borrar) {
			arbol_avl_borrar(&raiz_int->hijo_der, valor_a_borrar);
		} else {
			if (!raiz_int->hijo_izq) {
				*raiz = raiz_int->hijo_der;
			} else {
				if (!raiz_int->hijo_der) {
					*raiz = raiz_int->hijo_izq;
				} else {
					nodo_min = arbol_binario_get_nodo_minimo_valor(
							raiz_int->hijo_der);
					raiz_int->valor = nodo_min->valor;
					arbol_avl_borrar(&raiz_int->hijo_der, raiz_int->valor);

					ARBOL_BINARIO_ACTUALIZAR_HIJO_IZQ(nodo_min,
							raiz_int->hijo_izq);
					ARBOL_BINARIO_ACTUALIZAR_HIJO_DER(nodo_min,
							raiz_int->hijo_der);
					ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_min, raiz_int->padre);
					nodo_min->altura = ARBOL_AVL_GET_ALTURA(raiz_int);
					ARBOL_BINARIO_ACTUALIZAR_PADRE(raiz_int->hijo_izq,
							nodo_min);
					ARBOL_BINARIO_ACTUALIZAR_PADRE(raiz_int->hijo_der,
							nodo_min);
					*raiz = nodo_min;
				}
			}
		}
	}

	caca_log_debug("Terminado borrado BST");

	if (!*raiz) {
		caca_log_debug("Se borro el ultimo nodo");
		return;
	}

	ARBOL_AVL_ACTUALIZAR_ALTURA(raiz_int);

	switch (arbol_avl_diferencia_alturas_subarboles(raiz_int, 1, verdadero)) {
	case ARBOL_AVL_ALTURA_CARGADA_IZQ:
		caca_log_debug("Arbol cagado a la izq")
		;
		if (arbol_avl_diferencia_alturas_subarboles(raiz_int->hijo_izq, 0,
				falso) == ARBOL_AVL_ALTURA_CARGADA_DER) {
			caca_log_debug("Con ijo cagado a la derecha");
			arbol_binario_rotar_izq(&raiz_int->hijo_izq);
		}
		caca_log_debug("Rotando nodo raiz")
		;
		arbol_binario_rotar_der(raiz);
		caca_log_debug("Ahora la raiz %ld, izq %ld, der %ld",
				ARBOL_AVL_GET_VALOR(*raiz),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_izq),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_der))
		;
		break;
	case ARBOL_AVL_ALTURA_CARGADA_DER:
		caca_log_debug("Arbol cagado a la der")
		;
		if (arbol_avl_diferencia_alturas_subarboles(raiz_int->hijo_der, 0,
				verdadero) == ARBOL_AVL_ALTURA_CARGADA_IZQ) {
			caca_log_debug("Con ijo cagado a la izq");
			arbol_binario_rotar_der(&raiz_int->hijo_der);
		}
		caca_log_debug("Rotando nodo raiz")
		;
		arbol_binario_rotar_izq(raiz);
		caca_log_debug("Ahora la raiz %ld, izq %ld, der %ld",
				ARBOL_AVL_GET_VALOR(*raiz),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_izq),
				ARBOL_AVL_GET_VALOR((*raiz)->hijo_der))
		;
		break;
	case ARBOL_AVL_ALTURA_BALANCEADA:
		caca_log_debug("Arbol balanceado")
		;
		break;
	default:
		caca_log_debug("Mother of fuck arbol_avl_borrar")
		;
		break;
	}

}

void arbol_avl_borrar_referencia_directa(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_borrar) {

	nodo_arbol_binario *ancestro_actual = NULL;
	nodo_arbol_binario *nodo_a_borrar_padre = NULL;
	nodo_arbol_binario *nodo_min = NULL;

	nodo_arbol_binario **ancestro_actual_apuntador = NULL;
	nodo_arbol_binario **nodo_a_borrar_ref = NULL;

	if (!nodo_a_borrar) {
		caca_log_debug("Nodo a borrar nula, pq la mandan?");
		abort();
	}

	if (!(nodo_a_borrar_padre = ARBOL_AVL_GET_PADRE(nodo_a_borrar))) {
		nodo_a_borrar_padre = NULL;
		nodo_a_borrar_ref = raiz;
	} else {
		caca_log_debug("Borrando nodo no raiz");

		caca_log_debug("Calculando referencia en arbolazo, padre %p",
				nodo_a_borrar_padre);

		nodo_a_borrar_ref =
				nodo_a_borrar->valor < (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_izq :
				nodo_a_borrar->valor > (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_der :
				nodo_a_borrar->indice
						== ARBOL_AVL_GET_INDICE(nodo_a_borrar_padre->hijo_izq) ?
						&nodo_a_borrar_padre->hijo_izq :
						&nodo_a_borrar_padre->hijo_der;

		caca_log_debug(
				"la referencia del nodo a borrar %p, referencia de ijo izq %p, de ijo der %p",
				nodo_a_borrar_ref, &nodo_a_borrar_padre->hijo_izq,
				&nodo_a_borrar_padre->hijo_der);

		caca_log_debug("borrando nodo %ld, indice %ld", nodo_a_borrar->valor,
				nodo_a_borrar->indice);

	}

	ancestro_actual = nodo_a_borrar->padre;
	ancestro_actual_apuntador = &nodo_a_borrar->padre;

	caca_log_debug(
			"ancestro actual de nodo a borrar %p, su apuntador %p, lo que apunta %p",
			ancestro_actual, ancestro_actual_apuntador,
			*ancestro_actual_apuntador);

	if (nodo_a_borrar_padre) {
		caca_log_debug("estado original de padre %p hijod izq %p hiijos der %p",
				nodo_a_borrar_padre, nodo_a_borrar_padre->hijo_izq,
				nodo_a_borrar_padre->hijo_der);
	}

	if (!nodo_a_borrar->hijo_izq) {
		caca_log_debug("Borrando directamente sin hijo izq");
		ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_der,
				ancestro_actual);
		*nodo_a_borrar_ref = nodo_a_borrar->hijo_der;
		if (nodo_a_borrar_padre) {
			caca_log_debug("asi kedo el ancestro %p hijod izq %p hiijos der %p",
					nodo_a_borrar_padre, nodo_a_borrar_padre->hijo_izq,
					nodo_a_borrar_padre->hijo_der);
		}
	} else {
		if (!nodo_a_borrar->hijo_der) {
			caca_log_debug("Borrando directamente sin hijo der");
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_izq,
					ancestro_actual);
			*nodo_a_borrar_ref = nodo_a_borrar->hijo_izq;
		} else {
			caca_log_debug("Borrando nodo intermedio");
			nodo_min = arbol_binario_get_nodo_minimo_valor(
					nodo_a_borrar->hijo_der);

			arbol_avl_borrar_referencia_directa(raiz, nodo_min);
			ARBOL_BINARIO_ACTUALIZAR_HIJO_IZQ(nodo_min,
					nodo_a_borrar->hijo_izq);
			ARBOL_BINARIO_ACTUALIZAR_HIJO_DER(nodo_min,
					nodo_a_borrar->hijo_der);
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_min, nodo_a_borrar->padre);
			nodo_min->altura = ARBOL_AVL_GET_ALTURA(nodo_a_borrar);

			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_izq, nodo_min);
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_der, nodo_min);

			*nodo_a_borrar_ref = nodo_min;
		}
	}

	caca_log_debug("Terminado borrado BST con ancestro %p",
			*ancestro_actual_apuntador);

	do {
		if (!ARBOL_AVL_GET_PADRE(nodo_a_borrar)) {
			caca_log_debug("el q c intenta borrar es la raiz");
			break;
		}

		caca_log_debug("En el ancestro %ld %p",
				ARBOL_AVL_GET_INDICE(ancestro_actual), ancestro_actual);

		if (ARBOL_AVL_GET_PADRE(ancestro_actual)) {
			if (ARBOL_AVL_GET_VALOR(ancestro_actual)
					<= ARBOL_AVL_GET_VALOR(ancestro_actual->padre)) {
				ancestro_actual_apuntador = &ancestro_actual->padre->hijo_izq;
			} else {
				ancestro_actual_apuntador = &ancestro_actual->padre->hijo_der;
			}
		} else {
			ancestro_actual_apuntador = raiz;
		};

		ARBOL_AVL_ACTUALIZAR_ALTURA(ancestro_actual);

		switch (arbol_avl_diferencia_alturas_subarboles(ancestro_actual, 1,
				verdadero)) {
		case ARBOL_AVL_ALTURA_CARGADA_IZQ:
			caca_log_debug("Arbol cagado a la izq")
			;

			if (arbol_avl_diferencia_alturas_subarboles(
					ancestro_actual->hijo_izq, 0,
					falso) == ARBOL_AVL_ALTURA_CARGADA_DER) {
				caca_log_debug("Con ijo cagado a la derecha");
				arbol_binario_rotar_izq(&ancestro_actual->hijo_izq);
			}
			caca_log_debug(
					"Rotando nodo ancestro_actual_apuntador %p, contenido %p, %p",
					ancestro_actual_apuntador, *ancestro_actual_apuntador,
					ancestro_actual)
			;
			arbol_binario_rotar_der(ancestro_actual_apuntador);
			caca_log_debug(
					"Ahora la ancestro_actual_apuntador %ld, izq %ld, der %ld",
					ARBOL_AVL_GET_VALOR(*ancestro_actual_apuntador),
					ARBOL_AVL_GET_VALOR((*ancestro_actual_apuntador)->hijo_izq),
					ARBOL_AVL_GET_VALOR((*ancestro_actual_apuntador)->hijo_der))
			;
			break;
		case ARBOL_AVL_ALTURA_CARGADA_DER:
			caca_log_debug("Arbol cagado a la der")
			;
			if (arbol_avl_diferencia_alturas_subarboles(
					ancestro_actual->hijo_der, 0,
					verdadero) == ARBOL_AVL_ALTURA_CARGADA_IZQ) {
				caca_log_debug("Con ijo cagado a la izq");
				arbol_binario_rotar_der(&ancestro_actual->hijo_der);
			}
			caca_log_debug("Rotando nodo ancestro_actual_apuntador")
			;
			arbol_binario_rotar_izq(ancestro_actual_apuntador);
			caca_log_debug(
					"Ahora la ancestro_actual_apuntador %ld, izq %ld, der %ld",
					ARBOL_AVL_GET_VALOR(*ancestro_actual_apuntador),
					ARBOL_AVL_GET_VALOR((*ancestro_actual_apuntador)->hijo_izq),
					ARBOL_AVL_GET_VALOR((*ancestro_actual_apuntador)->hijo_der))
			;
			break;
		case ARBOL_AVL_ALTURA_BALANCEADA:
			caca_log_debug("Arbol balanceado %ld", ancestro_actual->valor)
			;
			break;
		default:
			caca_log_debug("Mother of fuck arbol_avl_borrar")
			;
			break;
		}

		ancestro_actual = ancestro_actual->padre;
	} while (ancestro_actual);
	caca_log_debug("termino borrado x ref de %p", nodo_a_borrar);
}

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		tipo_dato indice, tipo_dato nuevo_valor) {
	char buffer[MAX_TAM_CADENA] = { '\0' };
	nodo_arbol_binario *referencia_directa = NULL;
	nodo_arbol_binario *nuevo_nodo = NULL;
	nodo_arbol_binario **referencias_directas = NULL;
	nodo_arbol_binario **raiz = NULL;

	referencias_directas = cpctx->referencias_directas_por_indice;
	raiz = &cpctx->actx->raiz;

	referencia_directa = *(referencias_directas + indice);

	caca_log_debug("Modificando valor de %s",
			arbol_binario_nodo_a_cadena(referencia_directa,buffer,NULL));

	caca_log_debug("antes de borrar");
	arbol_binario_recorrido_inoder(cpctx->actx->raiz);

	arbol_avl_borrar_referencia_directa(&cpctx->actx->raiz, referencia_directa);

	caca_log_debug("tras borrar quedo");
	arbol_binario_recorrido_inoder(cpctx->actx->raiz);

	nuevo_nodo = arbol_binario_nodo_allocar(cpctx->actx, 1);
//	nuevo_nodo = referencia_directa;
	memset(nuevo_nodo, 0, sizeof(nodo_arbol_binario));
	nuevo_nodo->indice = indice;
	nuevo_nodo->valor = nuevo_valor;

	caca_log_debug("Re-insertando %s",
			arbol_binario_nodo_a_cadena(nuevo_nodo,buffer,NULL));

	arbol_avl_insertar(raiz, nuevo_nodo, falso);

	*(referencias_directas + indice) = nuevo_nodo;
}

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		tipo_dato *antecesores) {

	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado;

	tipo_dato dist_origen_dest = 0;

	nodo nodo_tmp;

	nodo_arbol_binario *distancia_min_origen = NULL;
	nodo_arbol_binario *distancia_min_destino = NULL;
	nodo_arbol_binario **distancias_minimas = NULL;
	nodo *nodos_encontrados[2] = { NULL };

	nodo_tmp.indice = ind_nodo_origen;
	caca_log_debug("buscando nodo origen en grafo principal %ld",
			ind_nodo_origen);
	tipo_resultado = busqueda_binaria(gctx->inicio, &nodo_tmp, GRAFO_PRINCIPAL,
			(void *) nodos_encontrados);

	if (tipo_resultado != GRAFO_NODO_ENCONTRADO) {
		perror("El nodo origen no fue en contrado n l grafo");
		exit(EXIT_FAILURE);
	}

	nodo_tmp.indice = ind_nodo_destino;
	caca_log_debug("buscando nodo destino %ld en grafo de %ld",
			ind_nodo_destino, ind_nodo_origen);
	tipo_resultado = busqueda_binaria((*nodos_encontrados)->siguiente_indice,
			&nodo_tmp, GRAFO_INDICE, (void *) nodos_encontrados);
	caca_log_debug("resultado de la busqueda de nodo destino %d",
			tipo_resultado);

	if (tipo_resultado != GRAFO_NODO_ENCONTRADO) {
		perror("El nodo destino no fue encontrado aunke el oringen si");
		exit(EXIT_FAILURE);
	}

	dist_origen_dest = (*nodos_encontrados)->distancia;

	distancias_minimas = cpctx->referencias_directas_por_indice;

	distancia_min_origen = *(distancias_minimas + ind_nodo_origen);
	distancia_min_destino = *(distancias_minimas + ind_nodo_destino);

	caca_log_debug("distancia de %ld a %ld: %ld", distancia_min_origen->indice,
			distancia_min_destino->indice, dist_origen_dest);

	if (distancia_min_destino->valor
			> distancia_min_origen->valor + dist_origen_dest) {
		cola_prioridad_modificar_valor_nodo(cpctx, ind_nodo_destino,
				distancia_min_origen->valor + dist_origen_dest);
		if (antecesores) {
			*(antecesores + ind_nodo_destino) = ind_nodo_origen;
		}
	}
}

void dijkstra_main(void *matrix_distancias, int num_filas,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		grafo_contexto *gctx, tipo_dato *distancias_minimas,
		tipo_dato *antecesores) {

	int contador = 0;
	int num_nodos = 0;

	tipo_dato indice_origen_actual = 0;
	tipo_dato indice_destino_actual = 0;
	tipo_dato max_indice = 0;

	grafo_contexto gctx_mem;
	grafo_contexto *gctx_int;
	cola_prioridad_contexto cpctx;

	nodo *nodo_origen_actual = NULL;
	nodo *nodo_destino_actual = NULL;
	nodo_cola_prioridad *nodo_mas_cercas = NULL;

	bool nodos_distancias_minimas_calculadas[MAX_NODOS] = { falso };
	char buffer[MAX_TAM_CADENA] = { '\0' };
	nodo_cola_prioridad distancias_minimas_nodos[MAX_NODOS];

	caca_log_debug("INitiado dikstra con nodo origen %ld", ind_nodo_origen);

	caca_inutiliza_nodo_cola_prioridad(distancias_minimas_nodos, MAX_NODOS);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_grafo(matrix_distancias, num_filas, gctx_int, falso, verdadero);
	}

	caca_log_debug("INitiado grafo");

	imprimir_lista_adjacencia(gctx_int->inicio);

	nodo_origen_actual = gctx_int->inicio;

	while (nodo_origen_actual) {
		caca_log_debug("initializando nodo de cola d prioridad de %s",
				grafo_nodo_a_cadena(nodo_origen_actual,buffer,NULL));
		if (nodo_origen_actual->indice == ind_nodo_origen) {
			caca_log_debug("Initializado nodo origen %ld", ind_nodo_origen);
			(distancias_minimas_nodos + nodo_origen_actual->indice)->valor = 0;
		} else {
			caca_log_debug("Initializado nodo no origen %ld",
					nodo_origen_actual->indice);
			(distancias_minimas_nodos + nodo_origen_actual->indice)->valor =
					MAX_VALOR;
		}
		if (nodo_origen_actual->indice > max_indice) {
			max_indice = nodo_origen_actual->indice;
			if (max_indice > MAX_NODOS) {
				perror(
						"El indice maximo supera el maximo de nodos permitidos, a la mierda todo");
				abort();
			}
		}
		(distancias_minimas_nodos + nodo_origen_actual->indice)->indice =
				nodo_origen_actual->indice;
		GRAFO_AVANZAR_NODO(nodo_origen_actual, GRAFO_PRINCIPAL, falso);
		contador++;
	}
	num_nodos = contador;

	caca_log_debug("initializando cola de prioridad con indice maximo %ld",
			max_indice);

	cola_prioridad_init(&cpctx, distancias_minimas_nodos, NULL, NULL,
			max_indice + 1, NULL, NULL );

	caca_log_debug("a punto de relaxar todos los nodos");

	contador = 0;
	while (!cola_prioridad_es_vacia(&cpctx)) {
		nodo_mas_cercas = cola_prioridad_pop(&cpctx);
		nodos_distancias_minimas_calculadas[nodo_mas_cercas->indice] =
				verdadero;
		caca_log_debug("revisando vecinos de %s",
				arbol_binario_nodo_a_cadena(nodo_mas_cercas,buffer,NULL));

		indice_origen_actual = nodo_mas_cercas->indice;
		nodo_origen_actual = grafo_get_nodo_origen_por_indice(gctx_int,
				indice_origen_actual);

		caca_log_debug("masajeando nodos de %s",
				grafo_nodo_a_cadena(nodo_origen_actual,buffer,NULL));

		nodo_destino_actual = nodo_origen_actual;

		while ((nodo_destino_actual = nodo_destino_actual->siguiente_distancia)) {
			indice_destino_actual = nodo_destino_actual->indice;
			if (!(*(nodos_distancias_minimas_calculadas + indice_destino_actual))) {
				dijkstra_relaxar_nodo(gctx_int, &cpctx, indice_origen_actual,
						indice_destino_actual, antecesores);
				caca_log_debug("Relaxado nodo %s,distancia minima actual %ld",
						grafo_nodo_a_cadena(nodo_destino_actual,buffer,NULL),
						(*(cpctx.referencias_directas_por_indice + indice_destino_actual))->valor);
			}
		}
		/*
		 if (contador > 40) {
		 exit(EXIT_FAILURE);
		 }
		 */
		contador++;
	}
	*(antecesores + ind_nodo_origen) = 0;
	for (int i = 0; i < max_indice + 1; i++) {
		caca_log_debug("llenando distancia minima de %d", i);
		*(distancias_minimas + i) =
				i == ind_nodo_origen ? 0 :
				caca_apuntador_valido(
						(*(cpctx.referencias_directas_por_indice + i))) ?
						(*(cpctx.referencias_directas_por_indice + i))->valor :
						COLA_PRIORIDAD_VALOR_INVALIDO;
	}

}

void cola_prioridad_init(cola_prioridad_contexto *ctx,
		nodo_cola_prioridad *nodos, tipo_dato *valores, tipo_dato *indices,
		int num_nodos, arbol_binario_contexto *actx,
		nodo_arbol_binario **referencias_directas) {
	tipo_dato indices_int[MAX_NODOS] = { ARBOL_AVL_INDICE_INVALIDO };
	tipo_dato datos[MAX_NODOS] = { ARBOL_AVL_INDICE_INVALIDO };

	memset(ctx, 0, sizeof(cola_prioridad_contexto));
	memset(ctx->referencias_directas_por_indice_mem, 0,
			sizeof(ctx->referencias_directas_por_indice_mem));
	memset(indices_int, COLA_PRIORIDAD_VALOR_INVALIDO, sizeof(indices_int));
	memset(datos, COLA_PRIORIDAD_VALOR_INVALIDO, sizeof(datos));

	if (actx) {
		if (!referencias_directas) {
			perror("se paso un contexto de arbol sin referencias directas");
			exit(1);
		}
		ctx->actx = actx;
		ctx->referencias_directas_por_indice = referencias_directas;
	} else {
		for (int i = 0; i < num_nodos; i++) {
			if (nodos) {
				if ((nodos + i)->indice == COLA_PRIORIDAD_VALOR_INVALIDO) {
					continue;
				}
				*(indices_int + i) = (nodos + i)->indice;
				*(datos + i) = (nodos + i)->valor;
			} else {
				if (!valores) {
					perror("no se proporcionaron nodos ni valores");
					exit(1);
				}
				if (indices) {
					*(indices_int + i) = *(indices + i);
				} else {
					*(indices_int + i) = i + 1;
				}
				*(datos + i) = *(valores + i);
			}
			caca_log_debug("en indice %ld, valor %ld", *(indices_int + i),
					*(datos + i));
		}

		ctx->actx = &ctx->actx_mem;
		ctx->referencias_directas_por_indice =
				ctx->referencias_directas_por_indice_mem;

		arbol_avl_init(ctx->actx, indices_int, datos, num_nodos,
				ctx->referencias_directas_por_indice);
	}

}

nodo_cola_prioridad *cola_prioridad_pop(cola_prioridad_contexto *ctx) {
	nodo_arbol_binario *nodo_actual = NULL;
	nodo_arbol_binario *nodo_anterior = NULL;

	caca_log_debug("popeando la cola de prioridad");

	nodo_actual = ctx->actx->raiz;

	while (nodo_actual) {
		nodo_anterior = nodo_actual;
		nodo_actual = nodo_actual->hijo_izq;
	}

	arbol_avl_borrar_referencia_directa(&ctx->actx->raiz, nodo_anterior);

	return nodo_anterior;
}

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx,
		tipo_dato *valores, int *num_valores) {
	arbol_binario_colectar_datos_recorrido_inoder(ctx->actx->raiz, valores,
			num_valores);
}

bool cola_prioridad_es_vacia(cola_prioridad_contexto *ctx) {
	return !ctx->actx->raiz;
}

nodo *grafo_get_nodo_origen_por_indice(grafo_contexto *ctx, tipo_dato indice) {
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado;

	nodo nodo_tmp;
	nodo *nodo_encontrado = NULL;
	nodo *nodos_encontrados[2] = { NULL };

	nodo_tmp.indice = indice;

	tipo_resultado = busqueda_binaria(ctx->inicio, &nodo_tmp, GRAFO_PRINCIPAL,
			(void *) nodos_encontrados);

	if (tipo_resultado == GRAFO_NODO_ENCONTRADO) {
		nodo_encontrado = *nodos_encontrados;
	}
	return nodo_encontrado;
}

nodo *grafo_get_nodo_destino_por_indice(grafo_contexto *ctx, nodo *nodo_origen,
		tipo_dato indice) {
	GRAFO_TIPO_RESULTADO_BUSQUEDA tipo_resultado;

	nodo nodo_tmp;
	nodo *nodo_encontrado = NULL;
	nodo *nodos_encontrados[2] = { NULL };

	nodo_tmp.indice = indice;

	tipo_resultado = busqueda_binaria(nodo_origen, &nodo_tmp, GRAFO_INDICE,
			(void *) nodos_encontrados);

	if (tipo_resultado == GRAFO_NODO_ENCONTRADO) {
		nodo_encontrado = *nodos_encontrados;
	}
	return nodo_encontrado;
}

tipo_dato grafo_get_distancia_entre_nodos_por_indice(grafo_contexto *ctx,
		tipo_dato indice_origen, tipo_dato indice_destino) {

	tipo_dato distancia = 0;

	nodo *nodo_origen = NULL;
	nodo *nodo_destino = NULL;

	nodo_origen = grafo_get_nodo_origen_por_indice(ctx, indice_origen);
	nodo_destino = grafo_get_nodo_destino_por_indice(ctx, nodo_origen,
			indice_destino);

	distancia = nodo_destino->distancia;

	return distancia;
}

char *caca_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo, char *buffer) {
	char *ap_buffer = NULL;
	int characteres_escritos = 0;

	ap_buffer = buffer;

	for (int i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%ld",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	return ap_buffer;
}

//XXX: http://stackoverflow.com/questions/9596945/how-to-get-appropriate-timestamp-in-c-for-logs
//XXX: http://stackoverflow.com/questions/3756323/getting-the-current-time-in-milliseconds
//XXX: http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
void timestamp_caca(char *stime) {
	time_t ltime;
	struct tm result;
	long ms; // Milliseconds
	struct timespec spec;
	char parte_milisecundos[50];

	ltime = time(NULL );

	localtime_r(&ltime, &result);
	asctime_r(&result, stime);

	*(stime + strlen(stime) - 1) = ' ';

	current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3); // Convert nanoseconds to milliseconds
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}

void grafo_copia_profunda(const grafo_contexto *ctx_origen,
		grafo_contexto *ctx_destino, tipo_dato *indices_a_ignorar,
		int tam_indices_a_ignorar) {

	nodo *nodo_origen_principal_actual = NULL;
	nodo *nodo_origen_ordenado_actual = NULL;
	nodo *nodo_destino_principal_actual = NULL;
	nodo *nodo_destino_principal_previo = NULL;
	nodo *nodo_destino_ordenado_actual = NULL;
	nodo *nodo_destino_ordenado_previo = NULL;

	nodo_origen_principal_actual = ctx_origen->inicio;
	while (nodo_origen_principal_actual) {
		caca_log_debug("lopp de principales");
		caca_log_debug("procesando %ld", nodo_origen_principal_actual->indice);
		if (indices_a_ignorar
				&& caca_arreglo_contiene(indices_a_ignorar,
						tam_indices_a_ignorar,
						nodo_origen_principal_actual->indice)) {
			caca_log_debug("ignorando algo en principales");
			caca_log_debug("ignorando prinipal %ld x esta n lista de ignorar",
					nodo_origen_principal_actual->indice);
			nodo_origen_principal_actual =
					nodo_origen_principal_actual->siguiente;
			continue;
		}
		nodo_destino_principal_actual = grafo_nodo_alloc(ctx_destino, 1);
		memset(nodo_destino_principal_actual, 0, sizeof(nodo));
		memset(nodo_destino_principal_actual, sizeof(nodo), 0);
		grafo_copia_nodo(nodo_origen_principal_actual,
				nodo_destino_principal_actual);
		if (nodo_destino_principal_previo) {
			nodo_destino_principal_previo->siguiente =
					nodo_destino_principal_actual;
			nodo_destino_principal_actual->anterior =
					nodo_destino_principal_previo;
		} else {
			ctx_destino->inicio = nodo_destino_principal_actual;
		}
		nodo_destino_principal_previo = nodo_destino_principal_actual;

		caca_log_debug("copiado nodo principal %ld %ld",
				nodo_destino_principal_actual->indice,
				nodo_destino_principal_actual->distancia);

		for (GRAFO_CRITERIOS_ORDENACION i = GRAFO_INDICE; i < GRAFO_PRINCIPAL;
				i++) {
			caca_log_debug("copiando nodos ordenados por %s",
					GRAFO_NOMBRES_CRITERIOS_ORDENACION[i]);
			nodo_destino_ordenado_previo = NULL;
			nodo_origen_ordenado_actual = nodo_origen_principal_actual;
			GRAFO_AVANZAR_NODO(nodo_origen_ordenado_actual, i, verdadero);
			while (nodo_origen_ordenado_actual) {
				caca_log_debug("lopp de adjacentes");
				caca_log_debug("procesando %ld",
						nodo_origen_ordenado_actual->indice);
				if (indices_a_ignorar
						&& caca_arreglo_contiene(indices_a_ignorar,
								tam_indices_a_ignorar,
								nodo_origen_ordenado_actual->indice)) {
					caca_log_debug(
							"ignorando adjacente %ld x esta n lista de ignorar",
							nodo_origen_ordenado_actual->indice);
					GRAFO_AVANZAR_NODO(nodo_origen_ordenado_actual, i,
							verdadero);
					continue;
				}
				nodo_destino_ordenado_actual = grafo_nodo_alloc(ctx_destino, 1);
				memset(nodo_destino_ordenado_actual, 0, sizeof(nodo));
				memset(nodo_destino_ordenado_actual, sizeof(nodo), 0);
				grafo_copia_nodo(nodo_origen_ordenado_actual,
						nodo_destino_ordenado_actual);
				if (nodo_destino_ordenado_previo) {
					GRAFO_ASIGNAR_ANTERIOR(nodo_destino_ordenado_previo,
							nodo_destino_ordenado_actual, i);
					GRAFO_ASIGNAR_SIGUIENTE(nodo_destino_ordenado_actual,
							nodo_destino_ordenado_previo, i);
				} else {
					GRAFO_ASIGNAR_SIGUIENTE(nodo_destino_ordenado_actual,
							nodo_destino_principal_actual, i);
					GRAFO_ASIGNAR_ANTERIOR(nodo_destino_principal_actual,
							nodo_destino_ordenado_actual, i);
					caca_log_debug("asignando 1ero de lista ordenada");
				}
				caca_log_debug("copiado nodo adjacente  %ld %ld",
						nodo_destino_ordenado_actual->indice,
						nodo_destino_ordenado_actual->distancia);
				caca_log_debug("de original %ld %ld",
						nodo_origen_ordenado_actual->indice,
						nodo_origen_ordenado_actual->distancia);

				GRAFO_AVANZAR_NODO(nodo_origen_ordenado_actual, i, verdadero);
				nodo_destino_ordenado_previo = nodo_destino_ordenado_actual;
			}
		}

		nodo_origen_principal_actual = nodo_origen_principal_actual->siguiente;
	}

}

#define GRAFO_COPIA_PROPIEDAD(propiedad) nodo_destino->propiedad = nodo_origen->propiedad
static inline void grafo_copia_nodo(const nodo *nodo_origen, nodo *nodo_destino) {
	GRAFO_COPIA_PROPIEDAD(distancia);
	GRAFO_COPIA_PROPIEDAD(indice);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_distancia);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_indice);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_valor);
	GRAFO_COPIA_PROPIEDAD(valor);
}

static inline bool caca_arreglo_contiene(tipo_dato *arreglo, int tam_arreglo,
		tipo_dato valor_buscado) {
	for (int i = 0; i < tam_arreglo; i++) {
		caca_log_debug("estoy en %d", i);
		if (*(arreglo + i) == valor_buscado) {
			return verdadero;
		}
	}
	return falso;
}

#define GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_destino,posicion_filas,posicion_columnas) \
			if (es_array) { \
				apuntador_destino= (matrix_array + posicion_filas * num_columnas + posicion_columnas); \
			} else { \
				apuntador_destino= (*(matrix_pointer + posicion_filas) + posicion_columnas); \
			}
void grafo_get_representacion_en_matriz_ordenada(grafo_contexto *ctx,
		void *matrix, int num_columnas) {
	bool es_array = falso;
	int contador_filas = 0;
	int contador_columnas = 0;
	void **apuntador_matrix = NULL;
	tipo_dato *matrix_array = NULL;
	tipo_dato **matrix_pointer = NULL;
	tipo_dato *apuntador_a_posicion_en_matrix = NULL;
	nodo *nodo_actual = NULL;
	nodo *nodo_adjacente_actual = NULL;

	nodo_actual = ctx->inicio;
	apuntador_matrix = matrix;
	matrix_array = (tipo_dato *) apuntador_matrix;
	matrix_pointer = (tipo_dato **) apuntador_matrix;

	es_array = verdadero;

	caca_log_debug("Transformando listas en matrix:");

	while (nodo_actual) {
		nodo_adjacente_actual = nodo_actual;
		GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_INDICE, verdadero);
		contador_columnas = 0;

		GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
				contador_filas, contador_columnas);

		caca_log_debug(
				"el apuntador destino del nodo principal %p en %d %d, cuyo valor es %ld",
				apuntador_a_posicion_en_matrix, contador_filas,
				contador_columnas, nodo_actual->indice);

		*apuntador_a_posicion_en_matrix = nodo_actual->indice;

		contador_columnas++;

		while (nodo_adjacente_actual) {

			GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
					contador_filas, contador_columnas);

			caca_log_debug("en adjacente indice %d %d", contador_filas,
					contador_columnas);
			*apuntador_a_posicion_en_matrix = nodo_adjacente_actual->indice;

			GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_INDICE, verdadero);
			contador_columnas++;
		}

		contador_filas++;
		contador_columnas = 0;

		GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
				contador_filas, contador_columnas);
		*apuntador_a_posicion_en_matrix = nodo_actual->indice;

		contador_columnas++;

		nodo_adjacente_actual = nodo_actual;
		GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_DISTANCIA, verdadero);
		while (nodo_adjacente_actual) {
			GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
					contador_filas, contador_columnas);

			caca_log_debug("en adjacente distancia %d %d", contador_filas,
					contador_columnas);
			*apuntador_a_posicion_en_matrix = nodo_adjacente_actual->indice;

			GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_DISTANCIA,
					verdadero);
			contador_columnas++;
		}

		nodo_actual = nodo_actual->siguiente;

		contador_filas++;
	}
	caca_log_debug("termino representacion en matrix");
}

static inline void caca_inutiliza_nodo_cola_prioridad(
		nodo_cola_prioridad *nodos, int num_nodos) {
	for (int i = 0; i < num_nodos; i++) {
		COLA_PRIORIDAD_ASIGNA_INDICE((nodos + i),
				COLA_PRIORIDAD_VALOR_INVALIDO);
		COLA_PRIORIDAD_ASIGNA_VALOR((nodos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
	}
}

char *caca_arreglo_a_cadena_float(float *arreglo, int tam_arreglo, char *buffer) {
	char *ap_buffer = NULL;
	int characteres_escritos = 0;

	ap_buffer = buffer;

	for (int i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%f",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	return ap_buffer;
}

void caca_realinea_array(tipo_dato *arreglo, int num_filas,
		int alineacion_actual, int alineacion_nueva) {
	for (int i = 0; i < num_filas; i++) {
		for (int j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_actual + j);
		}

	}
}

int escape_cabron_determina_nodos_viables(void *matrix_aristas, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial) {

	int num_nodos = 0;
	int contador_nodos_ruta_maldita = 0;
	int contador_nodos_recorridos = 0;
	tipo_dato ancestro_actual = 0;
	grafo_contexto grafo_inicial_ctx;

	char buffer[MAX_TAM_CADENA] = { '\0' };
//	char *buffer = NULL;
	tipo_dato *distancias_minimas = NULL, *antecesores = NULL;
	tipo_dato *ruta_maldita;

//	buffer = malloc(MAX_TAM_CADENA * sizeof(char));

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
			caca_arreglo_a_cadena(ruta_maldita, contador_nodos_ruta_maldita, buffer));

	caca_log_debug("el grafo initial antes de ser copiado");
	imprimir_lista_adjacencia(grafo_inicial_ctx.inicio);

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
	int num_nodos_viables = 0;
	int num_salidas_viables = 0;
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
	tipo_dato *salidas_carretera_viables = NULL;

	buffer = calloc(1000, sizeof(char));

	caca_log_debug("el num d filas %d", num_filas);
	caca_log_debug("los polis %ld", posicion_polis);
	caca_log_debug("las ratas %ld", posicion_ratas);
	caca_log_debug("num de salidas a carretera %ld", num_salidas_carretera);
	caca_log_debug("las salidas a carretera %s",
			caca_arreglo_a_cadena(salidas_carretera, num_salidas_carretera, buffer));
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

	for (int i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if ((distancia_salida_carretera_actual = *(distancias_minimas
				+ salida_carretera_actual)) == MAX_VALOR) {
			caca_log_debug("Mierda, la salida %ld es inalcanzable",
					salida_carretera_actual);
			continue;
		}
		*(distancias_salidas_carretera + num_salidas_viables) =
				distancia_salida_carretera_actual;
		*(salidas_carretera_viables + num_salidas_viables) =
				salida_carretera_actual;
		num_salidas_viables++;
	}

	caca_log_debug("las distancias a las salidas de la carretera son %s",
			caca_arreglo_a_cadena(distancias_salidas_carretera, num_salidas_viables, buffer));
	caca_log_debug("las salidas de la carretera viables son %s",
			caca_arreglo_a_cadena(salidas_carretera_viables, num_salidas_viables, buffer));

	if (!num_salidas_viables) {
		return maxima_velocidad;
	}

	cola_salidas_carretera = calloc(1, sizeof(cola_prioridad_contexto));
	if (!antecesores) {
		perror("no se consigio memoria para cola de distancias a salidas");
		abort();
	}

	cola_prioridad_init(cola_salidas_carretera, NULL, salidas_carretera_viables,
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

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	tipo_dato num_nodos = 0, num_salidas = 0;
	tipo_dato posicion_ratas = 0, posicion_polis = 0;

	tipo_dato datos_escape_mem[ESCAPE_CABRON_MAX_FILAS_INPUT][ESCAPE_CABRON_MAX_COLS_INPUT] =
			{ { 0 } };
//	tipo_dato *datos_escape_mem = NULL;

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

int main(int argc, char *argv[]) {

	float speed = 0;

	caca_log_debug("CACA");

	speed = escape_cabron_main();

	if (speed) {
		printf("%.10f\n", speed);
	} else {
		printf("IMPOSSIBLE\n");
	}

	return 0;
}
