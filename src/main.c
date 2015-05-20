#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MIERDA printf("soldado del amor \n"),exit(0);

#define td unsigned long

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
#define COLA_PRIORIDAD_VALOR_INVALIDO -1
#define DIJKSTRA_VALOR_INVALIDO -1
#define GRAFO_VALOR_INVALIDO -1
#define ARBOL_AVL_INDICE_INVALIDO -1
#define ARBOL_AVL_VALOR_INVALIDO -1

#define MAX_VALOR (td) (2<<28)

#define GRAFO_NODO_ORIGEN 0
#define GRAFO_NODO_DESTINO 1
#define GRAFO_DISTANCIA_ENTRE_NODOS 2

#define GRAFO_LIMITE_ORDENACION_LINEAL 2

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

#define GRAFO_AVANZAR_NODO(nodo_apuntador,criterio_busqueda,discriminar_principal) \
		nodo_apuntador = (nodo_apuntador)->siguiente;

#define GRAFO_COPIA_NODO_DATOS(nodo_origen,nodo_destino) \
		nodo_destino->valor=nodo_destino->valor; \
		nodo_destino->distancia=nodo_destino->distancia; \
		nodo_destino->indice=nodo_destino->indice;

#define COLA_PRIORIDAD_ASIGNA_INDICE(nodo,nuevo_indice) \
	(nodo)->indice=nuevo_indice

#define COLA_PRIORIDAD_ASIGNA_VALOR(nodo,nuevo_valor) \
	(nodo)->valor=nuevo_valor

#define ARBOL_AVL_GET_VALOR(nodo) \
	((nodo)?(nodo)->valor:ARBOL_AVL_VALOR_INVALIDO)

#define ARBOL_AVL_GET_INDICE(nodo) \
	((nodo)?(nodo)->indice:ARBOL_AVL_INDICE_INVALIDO)

typedef struct nodo {
	td valor;
	td indice;
	td distancia;
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
	td indice;
	td valor;
	unsigned int altura;

	struct nodo_arbol_binario *hijo_izq;
	struct nodo_arbol_binario *hijo_der;
	struct nodo_arbol_binario *padre;
} nodo_arbol_binario;

typedef struct arbol_binario_contexto {
	bool no_indices_repetidos;
	int localidades_usadas;
	nodo_arbol_binario *raiz;
	nodo_arbol_binario nodos_disponibles[MAX_NODOS];
} arbol_binario_contexto;

typedef struct grifo_contexto {
	int localidades_usadas;
	nodo *inicio;
	nodo *final;
	nodo nodos_disponibles[MAX_NODOS];
	td matrix_distancias[MAX_COLUMNAS_NODOS][MAX_FILAS_NODOS];
	nodo *referencias_nodos_por_indice[MAX_FILAS_NODOS];
} grafo_contexto;

typedef struct cola_prioridad_contexto {
	int num_nodos;
	nodo_arbol_binario *referencias_directas_por_indice_mem[MAX_NODOS];
	nodo_arbol_binario **referencias_directas_por_indice;
} cola_prioridad_contexto;

typedef nodo_arbol_binario nodo_cola_prioridad;

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int init_grafo(void *matrix, int num_filas, grafo_contexto *ctx,
		bool usar_hashes, bool relaciones_bidireccionales);

nodo *grafo_nodo_alloc(grafo_contexto *ctx, int localidades_solicitadas);

/* XXX: : https://www.securecoding.cert.org/confluence/display/seccode/MEM10-C.+Define+and+use+a+pointer+validation+function */
int caca_apuntador_valido(void *p);

int caca_int_max(int a, int b);

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		td indice, td nuevo_valor);

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		td ind_nodo_origen, td ind_nodo_destino, td *antecesores,
		nodo_cola_prioridad *nodo_origen);

void cola_prioridad_init(cola_prioridad_contexto *ctx,
		nodo_cola_prioridad *nodos, td *valores, td *indices, int num_nodos,
		arbol_binario_contexto *actx, nodo_arbol_binario **referencias_directas);

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx, td *valores,
		int *num_valores);

nodo_cola_prioridad *cola_prioridad_pop(cola_prioridad_contexto *ctx);

bool cola_prioridad_es_vacia(cola_prioridad_contexto *ctx);

void dijkstra_main(void *matrix_distancias, int num_filas, td ind_nodo_origen,
		td ind_nodo_destino, grafo_contexto *gctx, td *distancias_minimas,
		td *antecesores);

void grafo_copia_nodo(const nodo *nodo_origen, nodo *nodo_destino);

bool caca_arreglo_contiene(td *arreglo, int tam_arreglo, td valor_buscado);

void grafo_copia_profunda(const grafo_contexto *ctx_origen,
		grafo_contexto *ctx_destino, td *indices_a_ignorar,
		int tam_indices_a_ignorar);

void caca_inutiliza_nodo_cola_prioridad(nodo_cola_prioridad *nodos,
		int num_nodos);

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva);

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	long numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char linea[TAM_MAX_LINEA];

	while (fgets(linea, TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
			if (indice_columnas >= num_max_columnas) {
				perror("se leyeron demasiadas columnas, a la verga");
				abort();
			}
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		if (indice_filas > num_max_filas) {
			perror("se leyeron demasiadas filas, a la verga");
			abort();
		}
	}

	*num_filas = indice_filas;
	return 0;
}

int init_grafo(void *matrix, int num_filas, grafo_contexto *ctx,
		bool usar_hashes, bool relaciones_bidireccionales) {
	int i;
	int contador_nodos = 0;
	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td distancia_actual = 0;
	td *matrix_int = NULL;
	td *matrix_distancias = NULL;
	nodo *nuevo_nodo = NULL;
	td nodos_registrados[MAX_NODOS] = { falso };

	memset(ctx, 0, sizeof(grafo_contexto));

	matrix_int = matrix;
	matrix_distancias = (td *) ctx->matrix_distancias;
	memset(matrix_distancias, GRAFO_VALOR_INVALIDO,
			sizeof(ctx->matrix_distancias));
	for (i = 0; i < num_filas; i++) {
		indice_origen_actual = *(matrix_int + i * 3 + GRAFO_NODO_ORIGEN);
		indice_destino_actual = *(matrix_int + i * 3 + GRAFO_NODO_DESTINO);
		distancia_actual = *(matrix_int + i * 3 + GRAFO_DISTANCIA_ENTRE_NODOS);

		*(matrix_distancias + indice_origen_actual * MAX_COLUMNAS_NODOS
				+ indice_destino_actual) = distancia_actual;

		if (relaciones_bidireccionales) {

			*(matrix_distancias + indice_destino_actual * MAX_COLUMNAS_NODOS
					+ indice_origen_actual) = distancia_actual;
		}
		if (!*(nodos_registrados + indice_origen_actual)) {
			nuevo_nodo = grafo_nodo_alloc(ctx, 1);
			nuevo_nodo->indice = indice_origen_actual;
			if (ctx->inicio) {
				ctx->final->siguiente = nuevo_nodo;
			} else {
				ctx->inicio = nuevo_nodo;
			}
			ctx->final = nuevo_nodo;
			*(nodos_registrados + indice_origen_actual) = verdadero;
			contador_nodos++;
		}
		if (!*(nodos_registrados + indice_destino_actual)) {
			nuevo_nodo = grafo_nodo_alloc(ctx, 1);
			nuevo_nodo->indice = indice_destino_actual;
			ctx->final->siguiente = nuevo_nodo;
			ctx->final = nuevo_nodo;
			*(nodos_registrados + indice_destino_actual) = verdadero;
			contador_nodos++;
		}
	}
	return contador_nodos;
}

nodo *grafo_nodo_alloc(grafo_contexto *ctx, int localidades_solicitadas) {
	nodo *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

int caca_apuntador_valido(void *p) {
	return (p != NULL );
}

int caca_int_max(int a, int b) {
	return (a > b) ? a : b;
}

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		td indice, td nuevo_valor) {
	nodo_arbol_binario *referencia_directa = NULL;
	nodo_arbol_binario **referencias_directas = NULL;

	referencias_directas = cpctx->referencias_directas_por_indice;

	referencia_directa = *(referencias_directas + indice);

	referencia_directa->valor = nuevo_valor;

}

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		td ind_nodo_origen, td ind_nodo_destino, td *antecesores,
		nodo_cola_prioridad *nodo_origen) {
	td dist_origen_dest = 0;

	td *matrix_distancias = NULL;

	nodo_arbol_binario *distancia_min_origen = NULL;
	nodo_arbol_binario *distancia_min_destino = NULL;
	nodo_arbol_binario **distancias_minimas = NULL;

	matrix_distancias = (td*) gctx->matrix_distancias;
	dist_origen_dest = *(matrix_distancias
			+ ind_nodo_origen * MAX_COLUMNAS_NODOS + ind_nodo_destino);

	distancias_minimas = cpctx->referencias_directas_por_indice;

	distancia_min_origen = *(distancias_minimas + ind_nodo_origen);
	if (nodo_origen) {
		distancia_min_origen = nodo_origen;
	}
	distancia_min_destino = *(distancias_minimas + ind_nodo_destino);

	if (distancia_min_destino->valor
			> distancia_min_origen->valor + dist_origen_dest) {

		cola_prioridad_modificar_valor_nodo(cpctx, ind_nodo_destino,
				distancia_min_origen->valor + dist_origen_dest);
		if (antecesores) {

			*(antecesores + ind_nodo_destino) = ind_nodo_origen;
		}
	}
}
void dijkstra_main(void *matrix_distancias, int num_filas, td ind_nodo_origen,
		td ind_nodo_destino, grafo_contexto *gctx, td *distancias_minimas,
		td *antecesores) {

	int i, j;

	int contador = 0;
	int num_nodos = 0;

	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td distancia_actual = 0;
	td max_indice = 0;
	td *matrix_distancias_int = NULL;

	grafo_contexto gctx_mem;
	grafo_contexto *gctx_int;
	cola_prioridad_contexto cpctx;

	nodo *nodo_origen_actual = NULL;
	nodo_cola_prioridad *nodo_mas_cercas = NULL;

	bool nodos_distancias_minimas_calculadas[MAX_NODOS] = { falso };
	/*
	 nodo_cola_prioridad distancias_minimas_nodos[MAX_NODOS];
	 nodo_cola_prioridad *distancias_minimas_nodos_calculadas[MAX_NODOS];
	 */
	nodo_cola_prioridad *distancias_minimas_nodos;
	nodo_cola_prioridad **distancias_minimas_nodos_calculadas;

	distancias_minimas_nodos = calloc(MAX_NODOS, sizeof(nodo_cola_prioridad));
	if (!distancias_minimas_nodos) {
		perror("no ay memm para distancias minimas nodos");
		abort();
	}
	distancias_minimas_nodos_calculadas = calloc(MAX_NODOS,
			sizeof(nodo_cola_prioridad*));
	if (!distancias_minimas_nodos_calculadas) {
		perror("no ay memm para distancias minimas nodos cacalculadas");
		abort();
	}

	caca_inutiliza_nodo_cola_prioridad(distancias_minimas_nodos, MAX_NODOS);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_grafo(matrix_distancias, num_filas, gctx_int, falso, verdadero);
	}
	matrix_distancias_int = (td *) gctx_int->matrix_distancias;

	nodo_origen_actual = gctx_int->inicio;

	while (nodo_origen_actual) {
		if (nodo_origen_actual->indice == ind_nodo_origen) {
			(distancias_minimas_nodos + nodo_origen_actual->indice)->valor = 0;
		} else {
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

	cola_prioridad_init(&cpctx, distancias_minimas_nodos, NULL, NULL,
			max_indice + 1, NULL, NULL );

	contador = 0;
	while (!cola_prioridad_es_vacia(&cpctx)) {
		nodo_mas_cercas = cola_prioridad_pop(&cpctx);
		nodos_distancias_minimas_calculadas[nodo_mas_cercas->indice] =
				verdadero;
		*(distancias_minimas_nodos_calculadas + nodo_mas_cercas->indice) =
				nodo_mas_cercas;

		indice_origen_actual = nodo_mas_cercas->indice;

		for (j = 0; j < MAX_COLUMNAS_NODOS; j++) {
			distancia_actual = (td) *(matrix_distancias_int
					+ indice_origen_actual * MAX_FILAS_NODOS + j);
			indice_destino_actual = j;
			if (distancia_actual != GRAFO_VALOR_INVALIDO
					&& !(*(nodos_distancias_minimas_calculadas
							+ indice_destino_actual))) {

				dijkstra_relaxar_nodo(gctx_int, &cpctx, indice_origen_actual,
						indice_destino_actual, antecesores, nodo_mas_cercas);
			}
		}

		contador++;
	}

	*(antecesores + ind_nodo_origen) = 0;
	for (i = 0; i < max_indice + 1; i++) {
		*(distancias_minimas + i) =
				i == ind_nodo_origen ? 0 :
				caca_apuntador_valido(
						(*(distancias_minimas_nodos_calculadas + i))) ?
						(*(distancias_minimas_nodos_calculadas + i))->valor
								== MAX_VALOR ?
								COLA_PRIORIDAD_VALOR_INVALIDO :
								(*(distancias_minimas_nodos_calculadas + i))->valor
						:COLA_PRIORIDAD_VALOR_INVALIDO;
	}

}

void cola_prioridad_init(cola_prioridad_contexto *ctx,
		nodo_cola_prioridad *nodos, td *valores, td *indices, int num_nodos,
		arbol_binario_contexto *actx, nodo_arbol_binario **referencias_directas) {
	int i;
	int num_nodos_int = 0;
	nodo_cola_prioridad **nodos_int = NULL;

	memset(ctx, 0, sizeof(cola_prioridad_contexto));
	memset(ctx->referencias_directas_por_indice_mem, 0,
			sizeof(ctx->referencias_directas_por_indice_mem));
	nodos_int =
			(nodo_cola_prioridad **) &ctx->referencias_directas_por_indice_mem;

	if (actx) {
		if (!referencias_directas) {
			perror("se paso un contexto de arbol sin referencias directas");
			exit(1);
		}
		ctx->referencias_directas_por_indice = referencias_directas;
		num_nodos_int = num_nodos;
	} else {
		for (i = 0; i < num_nodos; i++) {
			if (nodos) {
				if ((nodos + i)->indice == COLA_PRIORIDAD_VALOR_INVALIDO) {
					continue;
				}
				*(nodos_int + ARBOL_AVL_GET_INDICE((nodos + i))) = (nodos + i);

			} else {
				if (!valores) {
					perror("no se proporcionaron nodos ni valores");
					exit(1);
				}
				if (indices) {
					*(nodos_int + *(indices + i)) = calloc(1,
							sizeof(nodo_cola_prioridad));
					if (!*(nodos_int + *(indices + i))) {
						perror(
								"No se pudo obtener mem para nodo cp nuevo con indices");
					}
					COLA_PRIORIDAD_ASIGNA_VALOR(*(nodos_int + *(indices + i)),
							*(valores + i));
					COLA_PRIORIDAD_ASIGNA_INDICE(*(nodos_int + *(indices + i)),
							*(indices + i));

				} else {
					*(nodos_int + i + 1) = calloc(1,
							sizeof(nodo_cola_prioridad));
					if (!*(nodos_int + i + 1)) {
						perror(
								"No se pudo obtener mem para nodo cp nuevo sin indices");
					}
					COLA_PRIORIDAD_ASIGNA_VALOR(*(nodos_int + i + 1),
							*(valores + i));
					COLA_PRIORIDAD_ASIGNA_INDICE(*(nodos_int + i + 1), i + 1);

				}
			}
			num_nodos_int++;
		}

		ctx->referencias_directas_por_indice =
				ctx->referencias_directas_por_indice_mem;
		ctx->num_nodos = num_nodos_int;

	}

}

nodo_cola_prioridad *cola_prioridad_pop(cola_prioridad_contexto *ctx) {
	bool alguno_no_es_maximo = falso;
	int i = 0;
	td indice_min = 0;
	td valor_min = MAX_VALOR;
	nodo_cola_prioridad *nodo_encontrado = NULL;
	nodo_cola_prioridad *primer_nodo_no_vacio = NULL;

	for (i = 0; i < MAX_NODOS; i++) {
		nodo_encontrado = *(ctx->referencias_directas_por_indice + i);
		if (nodo_encontrado) {

			if (!primer_nodo_no_vacio) {
				primer_nodo_no_vacio = nodo_encontrado;
			}
			if (ARBOL_AVL_GET_VALOR(nodo_encontrado) < valor_min) {
				valor_min = ARBOL_AVL_GET_VALOR(nodo_encontrado);
				indice_min = ARBOL_AVL_GET_INDICE(nodo_encontrado);
				alguno_no_es_maximo = verdadero;
			}
		}
	}

	if (indice_min < MAX_NODOS && alguno_no_es_maximo) {

		nodo_encontrado = *(ctx->referencias_directas_por_indice + indice_min);
		*(ctx->referencias_directas_por_indice + indice_min) = NULL;
		ctx->num_nodos--;

	} else {
		if (primer_nodo_no_vacio) {

			nodo_encontrado = primer_nodo_no_vacio;
			*(ctx->referencias_directas_por_indice
					+ ARBOL_AVL_GET_INDICE(primer_nodo_no_vacio)) = NULL;
			ctx->num_nodos--;

		} else {

		}
	}

	return nodo_encontrado;
}

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx, td *valores,
		int *num_valores) {
	int i;
	int contador_nodos_validos = 0;
	nodo_cola_prioridad *nodo_actual = NULL;
	for (i = 0; i < MAX_NODOS; i++) {
		nodo_actual = *(ctx->referencias_directas_por_indice + i);
		if (nodo_actual) {

			*(valores + contador_nodos_validos) = nodo_actual->valor;
			contador_nodos_validos++;
		}
	}
	*num_valores = contador_nodos_validos;
}

bool cola_prioridad_es_vacia(cola_prioridad_contexto *ctx) {
	return !ctx->num_nodos;
}

void grafo_copia_profunda(const grafo_contexto *ctx_origen,
		grafo_contexto *ctx_destino, td *indices_a_ignorar,
		int tam_indices_a_ignorar) {
	int i, j;
	td indice_nodo_origen_actual = 0;

	td *matrix_origen = NULL;
	td *matrix_destino = NULL;

	nodo *nodo_origen_principal_actual = NULL;
	nodo *nodo_destino_principal_actual = NULL;
	nodo *nodo_destino_principal_previo = NULL;

	matrix_origen = (td*) ctx_origen->matrix_distancias;
	matrix_destino = (td *) ctx_destino->matrix_distancias;
	memcpy(matrix_destino, matrix_origen,
			sizeof(ctx_origen->matrix_distancias));

	nodo_origen_principal_actual = ctx_origen->inicio;

	while (nodo_origen_principal_actual) {
		indice_nodo_origen_actual = nodo_origen_principal_actual->indice;

		if (indices_a_ignorar
				&& caca_arreglo_contiene(indices_a_ignorar,
						tam_indices_a_ignorar, indice_nodo_origen_actual)) {

			for (i = 0; i < MAX_FILAS_NODOS; i++) {
				*(matrix_destino + i * MAX_COLUMNAS_NODOS
						+ indice_nodo_origen_actual) = GRAFO_VALOR_INVALIDO;
			}
			for (j = 0; j < MAX_COLUMNAS_NODOS; j++) {
				*(matrix_destino
						+ indice_nodo_origen_actual * MAX_COLUMNAS_NODOS + j) =
						GRAFO_VALOR_INVALIDO;
			}
			GRAFO_AVANZAR_NODO(nodo_origen_principal_actual, 0, 0);

			continue;
		}

		nodo_destino_principal_actual = grafo_nodo_alloc(ctx_destino, 1);
		memset(nodo_destino_principal_actual, 0, sizeof(nodo));
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

		GRAFO_AVANZAR_NODO(nodo_origen_principal_actual, 0, 0);
	}

}

#define GRAFO_COPIA_PROPIEDAD(propiedad) nodo_destino->propiedad = nodo_origen->propiedad
void grafo_copia_nodo(const nodo *nodo_origen, nodo *nodo_destino) {
	GRAFO_COPIA_PROPIEDAD(distancia);
	GRAFO_COPIA_PROPIEDAD(indice);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_distancia);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_indice);
	GRAFO_COPIA_PROPIEDAD(num_nodos_asociados_valor);
	GRAFO_COPIA_PROPIEDAD(valor);
}

bool caca_arreglo_contiene(td *arreglo, int tam_arreglo, td valor_buscado) {
	int i;
	for (i = 0; i < tam_arreglo; i++) {

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

void caca_inutiliza_nodo_cola_prioridad(nodo_cola_prioridad *nodos,
		int num_nodos) {
	int i;
	for (i = 0; i < num_nodos; i++) {
		COLA_PRIORIDAD_ASIGNA_INDICE((nodos + i),
				COLA_PRIORIDAD_VALOR_INVALIDO);
		COLA_PRIORIDAD_ASIGNA_VALOR((nodos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
	}
}

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva) {
	int i, j;
	for (i = 0; i < num_filas; i++) {
		for (j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_actual + j);
		}

	}
}

int lee_matriz_int_archivo(const char * nombre_archivo,
		td matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT], int *filas) {
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
		inicio_cadena_num = strtok(linea, " ");
		indice_columnas = 0;
		while (inicio_cadena_num != NULL ) {
			numero = strtol(inicio_cadena_num, NULL, 10);
			matrix[indice_columnas][indice_filas] = (td) numero;
			inicio_cadena_num = strtok(NULL, " ");
			indice_columnas++;
		}
		indice_filas++;
	}
	*filas = indice_filas;
	fclose(fp);
	return 0;
}

int lee_matriz_long_stdin(td matrix[MAX_COLUMNAS_INPUT][MAX_FILAS_INPUT],
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

bool from_stack(void *ptr) {
	return verdadero;
}

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

double escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		td posicion_polis, td posicion_ratas, td *salidas_carretera,
		int num_salidas_carretera);

double escape_cabron_main();

void dijkstra_calcula_ruta(td *antecesores, int tam_antecesores,
		td posicion_inicial, td posicion_destino, td *ruta, int *tam_ruta);

double escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
		td posicion_polis, td posicion_ratas, td *salidas_carretera,
		int num_salidas_carretera) {
	int i, j;
	int num_nodos = 0;
	int tam_ruta_a_salida_actual = 0;
	double maxima_velocidad = 0;
	double tiempo_polis = 0;
	double velocidad_minima = (double) MAX_VALOR;
	td salida_carretera_actual = 0;
	td distancia_salida_carretera_actual = 0;
	td distancia_polis_a_ratas = 0;
	td distancia_recorrida_polis = 0;
	td min_distancia_salida = MAX_VALOR;
	td ind_min_distancia_salida = 0;
	td ind_nodo_actual = 0;
	td distancia_poli_a_nodo_actual;
	td distancia_min_poli_a_nodo_actual = MAX_VALOR;
	td ind_distancia_min_poli_a_nodo_actual = MAX_VALOR;
	char *buffer = NULL;
	td *distancias_minimas_bandido = NULL;
	td *antecesores_bandido = NULL;
	td *distancias_minimas_polis = NULL;
	td *antecesores_polis = NULL;
	nodo_cola_prioridad *nodo_salida_mas_cercana = NULL;
	grafo_contexto *grafo_bandido_ctx = NULL;
	grafo_contexto *grafo_poli_ctx = NULL;
	td *ruta_a_salida_actual = NULL;

	buffer = calloc(1000, sizeof(char));

	if (caca_arreglo_contiene(salidas_carretera, num_salidas_carretera,
			posicion_ratas)) {
		return 0;
	}
	if (posicion_polis == posicion_ratas) {
		return MAX_VALOR ;
	}

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

	distancias_minimas_bandido = calloc((num_nodos + 1), sizeof(td));
	if (!distancias_minimas_bandido) {
		perror("no se consigio memoria para distancias bandido");
		abort();
	}
	antecesores_bandido = calloc((num_nodos + 1), sizeof(td));
	if (!antecesores_bandido) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	distancias_minimas_polis = calloc((num_nodos + 1), sizeof(td));
	if (!distancias_minimas_polis) {
		perror("no se consigio memoria para distancias poli");
		abort();
	}
	antecesores_polis = calloc((num_nodos + 1), sizeof(td));
	if (!antecesores_polis) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	ruta_a_salida_actual = calloc(num_nodos + 1, sizeof(td));
	if (!ruta_a_salida_actual) {
		perror("no se consigio memoria para ruta_salida_actual");
		abort();
	}

	grafo_copia_profunda(grafo_poli_ctx, grafo_bandido_ctx, &posicion_polis, 1);

	dijkstra_main(NULL, 0, posicion_polis, 0, grafo_poli_ctx,
			distancias_minimas_polis, antecesores_polis);

	dijkstra_main(NULL, 0, posicion_ratas, 0, grafo_bandido_ctx,
			distancias_minimas_bandido, antecesores_bandido);

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if (salida_carretera_actual == posicion_polis) {

			continue;
		}
		if (*(distancias_minimas_bandido + salida_carretera_actual)
				== COLA_PRIORIDAD_VALOR_INVALIDO) {

			continue;
		}
		dijkstra_calcula_ruta(antecesores_bandido, num_nodos + 1,
				posicion_ratas, salida_carretera_actual, ruta_a_salida_actual,
				&tam_ruta_a_salida_actual);

		distancia_min_poli_a_nodo_actual = MAX_VALOR;
		ind_distancia_min_poli_a_nodo_actual = MAX_VALOR;
		for (j = 0; j < tam_ruta_a_salida_actual - 1; j++) {
			ind_nodo_actual = *(ruta_a_salida_actual + j);
			distancia_poli_a_nodo_actual = *(distancias_minimas_polis
					+ ind_nodo_actual);

			if (distancia_poli_a_nodo_actual
					< distancia_min_poli_a_nodo_actual) {
				distancia_min_poli_a_nodo_actual = distancia_poli_a_nodo_actual;
				ind_distancia_min_poli_a_nodo_actual = ind_nodo_actual;
			}
		}

		distancia_recorrida_polis = distancia_min_poli_a_nodo_actual;

		tiempo_polis = (double) (distancia_recorrida_polis)
				/ (double) (MAX_VEL_POLIS);

		maxima_velocidad = (double) (*(distancias_minimas_bandido
				+ salida_carretera_actual)) / (tiempo_polis);

		if (maxima_velocidad < velocidad_minima) {
			velocidad_minima = maxima_velocidad;
		}

	}

	return velocidad_minima;
}

double escape_cabron_main() {
	double maxima_velocidad = 0;

	int num_aristas = 0;

	td num_nodos = 0, num_salidas = 0;
	td posicion_ratas = 0, posicion_polis = 0;

	td *datos_escape_mem = NULL;

	td *datos_escape = (td *) datos_escape_mem;
	td *inicio_aristas = NULL;
	td *salidas = NULL;

	datos_escape_mem = calloc(
			ESCAPE_CABRON_MAX_FILAS_INPUT * ESCAPE_CABRON_MAX_COLS_INPUT,
			sizeof(td));
	if (!datos_escape_mem) {
		perror("no se obtubo memoria para los datos del escape");
		abort();
	}
	datos_escape = datos_escape_mem;

	lee_matrix_long_stdin((td *) datos_escape, &num_aristas, NULL,
			ESCAPE_CABRON_MAX_FILAS_INPUT, ESCAPE_CABRON_MAX_COLS_INPUT);

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

	return maxima_velocidad;
}

void dijkstra_calcula_ruta(td *antecesores, int tam_antecesores,
		td posicion_inicial, td posicion_destino, td *ruta_maldita,
		int *tam_ruta) {
	int contador_nodos_recorridos = 0;
	int contador_nodos_ruta_maldita = 0;
	td ancestro_actual = 0;

	*(ruta_maldita + contador_nodos_ruta_maldita++) = posicion_destino;

	while (*(ruta_maldita + contador_nodos_ruta_maldita - 1) != posicion_inicial
			&& contador_nodos_recorridos < tam_antecesores) {
		ancestro_actual = *(antecesores
				+ *(ruta_maldita + contador_nodos_ruta_maldita - 1));

		if (ancestro_actual != 0) {
			*(ruta_maldita + contador_nodos_ruta_maldita) = ancestro_actual;
			contador_nodos_ruta_maldita++;
		} else {
			break;
		}
		contador_nodos_recorridos++;
	}
	*tam_ruta = contador_nodos_recorridos + 1;

}

int main(int argc, char *argv[]) {
	double resultado = 0;

	resultado = escape_cabron_main();
	if (resultado != MAX_VALOR) {
		printf("%.10f\n", resultado);
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
