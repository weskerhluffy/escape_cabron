#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <math.h>

#define td unsigned long

#define MXN 101
#define MXL 1024
#define MXNO 128
#define MXF 5010
#define MXCI 256
#define MXFN 100
#define MXCN 100
#define CACA_COMPARACION_IZQ_MENOR -1
#define CACA_COMPARACION_IZQ_IGUAL 0
#define CACA_COMPARACION_IZQ_MAYOR 1
#define MAX_TAM_CADENA 200

#define GRAFO_VALOR_INVALIDO -1
#define ARBOL_AVL_INDICE_INVALIDO -1
#define ARBOL_AVL_VALOR_INVALIDO -1
#define COLA_PRIORIDAD_VALOR_INVALIDO GRAFO_VALOR_INVALIDO
#define DIJKSTRA_VALOR_INVALIDO -1

#define MAX_VALOR (td) (2<<28)

#define GRAFO_NODO_ORIGEN 0
#define GRAFO_NODO_DESTINO 1
#define GRAFO_DISTANCIA_ENTRE_NODOS 2

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bo;

#define GAN(nodo_apuntador,criterio_busqueda,discriminar_principal) \
		nodo_apuntador = (nodo_apuntador)->siguiente;

#define AAAA(nodo) \
	(nodo)->altura = ((nodo)->hijo_izq || (nodo)->hijo_der)? \
			caca_int_max(AAOA((nodo)->hijo_izq), AAOA((nodo)->hijo_der)) + 1: \
			0;

#define AAOA(nodo) \
	((nodo)?(nodo)->altura:0)

#define AAOV(nodo) \
	((nodo)?(nodo)->valor:ARBOL_AVL_VALOR_INVALIDO)

#define AAAP(nodo,nuevo_padre) \
	((nodo)?(nodo)->padre=(nuevo_padre):((void)0))

#define AAOP(nodo) \
	((nodo)?(nodo)->padre:NULL)

#define AAOI(nodo) \
	((nodo)?(nodo)->indice:ARBOL_AVL_INDICE_INVALIDO)

#define ABAI(nodo,nuevo_hijo) \
	((nodo)?(nodo)->hijo_izq=(nuevo_hijo):((void)0))

#define ABAD(nodo,nuevo_hijo) \
	((nodo)?(nodo)->hijo_der=(nuevo_hijo):((void)0))

#define CPAI(nodo,nuevo_indice) \
	(nodo)->indice=nuevo_indice

#define CPAV(nodo,nuevo_valor) \
	(nodo)->indice=nuevo_valor

typedef struct nodo {
	td valor;
	td indice;
	td distancia;
	struct nodo *siguiente;
	struct nodo *anterior;
} no;

typedef struct nodo_arbol_binario {
	td indice;
	td valor;
	unsigned int altura;

	struct nodo_arbol_binario *hijo_izq;
	struct nodo_arbol_binario *hijo_der;
	struct nodo_arbol_binario *padre;
} nab;

typedef struct grifo_contexto {
	int localidades_usadas;
	no *inicio;
	no *final;
	no nodos_disponibles[MXN];
	td matrix_distancias[MXCN][MXFN];
	no *referencias_nodos_por_indice[MXFN];
} gc;

typedef struct arbol_binario_contexto {
	bo no_indices_repetidos;
	int localidades_usadas;
	nab *raiz;
	nab nodos_disponibles[MXN];
} ac;

typedef struct cola_prioridad_contexto {
	ac actx_mem;
	ac *actx;
	nab *referencias_directas_por_indice_mem[MXN];
	nab **referencias_directas_por_indice;
} cc;

typedef nab nc;

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int init_grafo(void *matrix, int num_filas, gc *ctx, bo usar_hashes,
		bo relaciones_bidireccionales);

int caca_apuntador_valido(void *p);

void arbol_avl_init(ac *ctx, td *indices,
td *datos, int num_datos, nab **arreglo_referencias_nodos);

#define AAAI -1
#define AAAD 1
#define AAAB 0

static inline int aada(nab *nodo, int tolerancia,
		bo considerar_balanceado_cargado_der);

static inline nab *aba(ac *ctx, int localidades_solicitadas);

void arbol_avl_insertar(nab **raiz, nab *nodo_a_insertar,
		bo no_indices_repetidos);

static inline int aacn(nab *nodo1, nab *nodo2);

static inline int caca_int_max(int a, int b);

static inline void abri(nab **nodo);
static inline void abrd(nab **nodo);

void arbol_binario_borrar_nodo(nab **raiz,
td valor_a_borrar);

void arbol_avl_borrar(nab **raiz, td valor_a_borrar);

void arbol_avl_borrar_referencia_directa(nab **raiz, nab *nodo_a_borrar);

void cola_prioridad_modificar_valor_nodo(cc *cpctx,
td indice, td nuevo_valor);

void dijkstra_relaxar_nodo(gc *gctx, cc *cpctx,
td ind_nodo_origen, td ind_nodo_destino,
td *antecesores);

void cola_prioridad_init(cc *ctx, nc *nodos, td *valores, td *indices,
		int num_nodos, ac *actx, nab **referencias_directas);

nc *cola_prioridad_pop(cc *ctx);

bo cola_prioridad_es_vacia(cc *ctx);

void dijkstra_main(void *matrix_distancias, int num_filas,
td ind_nodo_origen, td ind_nodo_destino, gc *gctx,
td *distancias_minimas,
td *antecesores);

static inline void grafo_copia_nodo(const no *nodo_origen, no *nodo_destino);

static inline bo caca_arreglo_contiene(td *arreglo, int tam_arreglo,
td valor_buscado);

void grafo_copia_profunda(const gc *ctx_origen, gc *ctx_destino,
		td *indices_a_ignorar, int tam_indices_a_ignorar);

static inline void caca_inutiliza_nodo_cola_prioridad(nc *nodos, int num_nodos);

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva);

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nodos_viables(void *matrix_vertices, int num_filas,
		gc *grafo_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *distancia_posicion_incomoda_a_inicial);

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
td posicion_polis, td posicion_ratas,
td *salidas_carretera, int num_salidas_carretera);

float escape_cabron_main();


no *gna(gc *ctx, int localidades_solicitadas);

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	long numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char linea[MXL];

	while (fgets(linea, MXL, stdin)) {
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
//		*(*num_columnas + indice_filas) = indice_columnas;
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		if (indice_filas >= num_max_filas) {
			perror("se leyeron demasiadas filas, a la verga");
			abort();
		}
	}

	*num_filas = indice_filas;
	return 0;
}

int init_grafo(void *matrix, int num_filas, gc *ctx, bo usar_hashes,
		bo relaciones_bidireccionales) {
	int contador_nodos = 0;
	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td distancia_actual = 0;
	td *matrix_int = NULL;
	td *matrix_distancias = NULL;
	no *nuevo_nodo = NULL;
	td nodos_registrados[MXN] = { falso };

	memset(ctx, 0, sizeof(gc));

	matrix_int = matrix;
	matrix_distancias = ctx->matrix_distancias;
	memset(matrix_distancias, GRAFO_VALOR_INVALIDO,
			sizeof(ctx->matrix_distancias));
	for (int i = 0; i < num_filas; i++) {
		indice_origen_actual = *(matrix_int + i * 3 + GRAFO_NODO_ORIGEN);
		indice_destino_actual = *(matrix_int + i * 3 + GRAFO_NODO_DESTINO);
		distancia_actual = *(matrix_int + i * 3 + GRAFO_DISTANCIA_ENTRE_NODOS);

		*(matrix_distancias + indice_origen_actual * MXCN
				+ indice_destino_actual) = distancia_actual;
		if (relaciones_bidireccionales) {
			*(matrix_distancias + indice_destino_actual * MXCN
					+ indice_origen_actual) = distancia_actual;
		}
		if (!*(nodos_registrados + indice_origen_actual)) {
			nuevo_nodo = gna(ctx, 1);
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
			nuevo_nodo = gna(ctx, 1);
			nuevo_nodo->indice = indice_destino_actual;
			ctx->final->siguiente = nuevo_nodo;
			ctx->final = nuevo_nodo;
			*(nodos_registrados + indice_destino_actual) = verdadero;
			contador_nodos++;
		}
	}
	return contador_nodos;
}

no *gna(gc *ctx, int localidades_solicitadas) {
	no *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

int caca_apuntador_valido(void *p) {
//	extern char _etext;
//	return (p != NULL ) && ((char*) p > &_etext);
	return (p != NULL);
}

void arbol_avl_init(ac *ctx, td *indices,
td *datos, int num_datos, nab **arreglo_referencias_nodos) {
	int i = 0;
	td dato_actual = 0;
	nab *nodo_actual = NULL;

	memset((void *) ctx, 0, sizeof(ac));
	memset((void *) ctx->nodos_disponibles, 0, sizeof(ctx->nodos_disponibles));

	for (i = 0; i < num_datos; i++) {
		if (indices && *(indices + i) == ARBOL_AVL_INDICE_INVALIDO) {
			continue;
		}

		if (!ctx->raiz) {
			ctx->raiz = aba(ctx, 1);
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
			continue;
		}

		dato_actual = *(datos + i);
		nodo_actual = aba(ctx, 1);

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
	}
}

void arbol_avl_insertar(nab **raiz, nab *nodo_a_insertar,
		bo no_indices_repetidos) {
	nab *raiz_int = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
		*raiz = nodo_a_insertar;
		return;
	}

	switch (aacn(raiz_int, nodo_a_insertar)) {
	case CACA_COMPARACION_IZQ_MENOR:
		if (raiz_int->hijo_der) {
			arbol_avl_insertar(&raiz_int->hijo_der, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			raiz_int->hijo_der = nodo_a_insertar;
			AAAP(nodo_a_insertar, raiz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_MAYOR:
		if (raiz_int->hijo_izq) {
			arbol_avl_insertar(&raiz_int->hijo_izq, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			raiz_int->hijo_izq = nodo_a_insertar;
			AAAP(nodo_a_insertar, raiz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_IGUAL:
		if (no_indices_repetidos) {
			perror("NO mames, una llave repetida, ahhhhh !");
			exit(1);
		} else {
			if (raiz_int->hijo_der) {
				arbol_avl_insertar(&raiz_int->hijo_der, nodo_a_insertar,
						no_indices_repetidos);
			} else {
				raiz_int->hijo_der = nodo_a_insertar;
				AAAP(nodo_a_insertar, raiz_int);
			}
		}
		break;
	default:
		perror("NO mames, resultado increible en arbol_avl_insertar!");
		exit(1);
		break;
	}

	AAAA(raiz_int);

	switch (aada(raiz_int, 1, verdadero)) {
	case AAAI:
		if (AAOV(
				raiz_int->hijo_izq) < AAOV(nodo_a_insertar)) {
			abri(&raiz_int->hijo_izq);
		}
		abrd(raiz);
		break;
	case AAAD:
		if (AAOV(
				raiz_int->hijo_der) > AAOV(nodo_a_insertar)) {
			abrd(&raiz_int->hijo_der);
		}
		abri(raiz);
		break;
	case AAAB:
		break;
	default:
		perror("error en altura indeterminada, verga");
		exit(1);
		break;
	}

}

static inline int aacn(nab *nodo1, nab *nodo2) {
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

static inline int aada(nab *nodo, int tolerancia,
		bo considerar_balanceado_cargado_der) {
	int diferencia_alturas = 0;
	diferencia_alturas = AAOA(
			nodo->hijo_izq) - AAOA(nodo->hijo_der);
	if (considerar_balanceado_cargado_der) {
		return diferencia_alturas < 0 - tolerancia ?
		AAAD :
				diferencia_alturas > tolerancia ?
				AAAI :
													AAAB;
	} else {
		return diferencia_alturas < 0 - tolerancia ?
		AAAD :
				diferencia_alturas > tolerancia ?
				AAAI :
													AAAB;
	}
}

static inline void abri(nab **nodo) {
	nab *nodo_int = NULL;
	nab *hijo_der = NULL;
	nab *hijo_der_subarbol_izq = NULL;

	nodo_int = *nodo;
	hijo_der = nodo_int->hijo_der;
	hijo_der_subarbol_izq = hijo_der->hijo_izq;

	nodo_int->hijo_der = hijo_der_subarbol_izq;
	hijo_der->hijo_izq = nodo_int;

	AAAP(hijo_der, AAOP(nodo_int));
	AAAP(hijo_der_subarbol_izq, nodo_int);
	AAAP(nodo_int, hijo_der);

	AAAA(nodo_int);
	AAAA(hijo_der);

	*nodo = hijo_der;

}

static inline void abrd(nab **nodo) {
	nab *nodo_int = NULL;
	nab *hijo_izq = NULL;
	nab *hijo_izq_subarbol_der = NULL;

	nodo_int = *nodo;
	hijo_izq = nodo_int->hijo_izq;
	hijo_izq_subarbol_der = hijo_izq->hijo_der;

	nodo_int->hijo_izq = hijo_izq_subarbol_der;
	hijo_izq->hijo_der = nodo_int;

	AAAP(hijo_izq, AAOP(nodo_int));
	AAAP(hijo_izq_subarbol_der, nodo_int);
	AAAP(nodo_int, hijo_izq);

	AAAA(nodo_int);
	AAAA(hijo_izq);

	*nodo = hijo_izq;

}

static inline nab *aba(ac *ctx, int localidades_solicitadas) {
	nab *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

static inline nab *arbol_binario_get_nodo_minimo_valor(nab *raiz) {
	nab *nodo_actual = NULL;
	nodo_actual = raiz;
	while (nodo_actual->hijo_izq) {
		nodo_actual = nodo_actual->hijo_izq;
	}
	return nodo_actual;
}

void arbol_binario_borrar_nodo(nab **raiz,
td valor_a_borrar) {
	nab *raiz_int = NULL;
	nab *nodo_min = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
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


void arbol_avl_borrar(nab **raiz, td valor_a_borrar) {

	nab *raiz_int = NULL;
	nab *nodo_min = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
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

					ABAI(nodo_min, raiz_int->hijo_izq);
					ABAD(nodo_min, raiz_int->hijo_der);
					AAAP(nodo_min, raiz_int->padre);
					nodo_min->altura = AAOA(raiz_int);
					AAAP(raiz_int->hijo_izq, nodo_min);
					AAAP(raiz_int->hijo_der, nodo_min);
					*raiz = nodo_min;
				}
			}
		}
	}

	if (!*raiz) {
		return;
	}

	AAAA(raiz_int);

	switch (aada(raiz_int, 1, verdadero)) {
	case AAAI:
		if (aada(raiz_int->hijo_izq, 0, falso) == AAAD) {
			abri(&raiz_int->hijo_izq);
		}
		abrd(raiz);
		break;
	case AAAD:
		if (aada(raiz_int->hijo_der, 0, verdadero) == AAAI) {
			abrd(&raiz_int->hijo_der);
		}
		abri(raiz);
		break;
	case AAAB:
		break;
	default:
		break;
	}

}

void arbol_avl_borrar_referencia_directa(nab **raiz, nab *nodo_a_borrar) {

	nab *ancestro_actual = NULL;
	nab *nodo_a_borrar_padre = NULL;
	nab *nodo_min = NULL;

	nab **ancestro_actual_apuntador = NULL;
	nab **nodo_a_borrar_ref = NULL;

	if (!nodo_a_borrar) {
		abort();
	}

	if (!(nodo_a_borrar_padre = AAOP(nodo_a_borrar))) {
		nodo_a_borrar_padre = NULL;
		nodo_a_borrar_ref = raiz;
	} else {

		nodo_a_borrar_ref =
				nodo_a_borrar->valor < (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_izq :
				nodo_a_borrar->valor > (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_der :
				nodo_a_borrar->indice == AAOI(nodo_a_borrar_padre->hijo_izq) ?
						&nodo_a_borrar_padre->hijo_izq :
						&nodo_a_borrar_padre->hijo_der;

	}

	ancestro_actual = nodo_a_borrar->padre;
	ancestro_actual_apuntador = &nodo_a_borrar->padre;

	if (!nodo_a_borrar->hijo_izq) {
		AAAP(nodo_a_borrar->hijo_der, ancestro_actual);
		*nodo_a_borrar_ref = nodo_a_borrar->hijo_der;
	} else {
		if (!nodo_a_borrar->hijo_der) {
			AAAP(nodo_a_borrar->hijo_izq, ancestro_actual);
			*nodo_a_borrar_ref = nodo_a_borrar->hijo_izq;
		} else {
			nodo_min = arbol_binario_get_nodo_minimo_valor(
					nodo_a_borrar->hijo_der);

			arbol_avl_borrar_referencia_directa(raiz, nodo_min);
			ABAI(nodo_min, nodo_a_borrar->hijo_izq);
			ABAD(nodo_min, nodo_a_borrar->hijo_der);
			AAAP(nodo_min, nodo_a_borrar->padre);
			nodo_min->altura = AAOA(nodo_a_borrar);

			AAAP(nodo_a_borrar->hijo_izq, nodo_min);
			AAAP(nodo_a_borrar->hijo_der, nodo_min);

			*nodo_a_borrar_ref = nodo_min;
		}
	}

	do {
		if (!AAOP(nodo_a_borrar)) {
			break;
		}

		if (AAOP(ancestro_actual)) {
			if (AAOV(
					ancestro_actual) <= AAOV(ancestro_actual->padre)) {
				ancestro_actual_apuntador = &ancestro_actual->padre->hijo_izq;
			} else {
				ancestro_actual_apuntador = &ancestro_actual->padre->hijo_der;
			}
		} else {
			ancestro_actual_apuntador = raiz;
		};

		AAAA(ancestro_actual);

		switch (aada(ancestro_actual, 1, verdadero)) {
		case AAAI:

			if (aada(ancestro_actual->hijo_izq, 0, falso) == AAAD) {
				abri(&ancestro_actual->hijo_izq);
			}
			abrd(ancestro_actual_apuntador);
			break;
		case AAAD:
			if (aada(ancestro_actual->hijo_der, 0, verdadero) == AAAI) {
				abrd(&ancestro_actual->hijo_der);
			}
			abri(ancestro_actual_apuntador);
			break;
		case AAAB:
			break;
		default:
			break;
		}

		ancestro_actual = ancestro_actual->padre;
	} while (ancestro_actual);
}

void cola_prioridad_modificar_valor_nodo(cc *cpctx,
td indice, td nuevo_valor) {
	nab *referencia_directa = NULL;
	nab *nuevo_nodo = NULL;
	nab **referencias_directas = NULL;
	nab **raiz = NULL;

	referencias_directas = cpctx->referencias_directas_por_indice;
	raiz = &cpctx->actx->raiz;

	referencia_directa = *(referencias_directas + indice);


	arbol_avl_borrar_referencia_directa(&cpctx->actx->raiz, referencia_directa);


	nuevo_nodo = aba(cpctx->actx, 1);
//	nuevo_nodo = referencia_directa;
	memset(nuevo_nodo, 0, sizeof(nab));
	nuevo_nodo->indice = indice;
	nuevo_nodo->valor = nuevo_valor;

	arbol_avl_insertar(raiz, nuevo_nodo, falso);

	*(referencias_directas + indice) = nuevo_nodo;
}

void dijkstra_relaxar_nodo(gc *gctx, cc *cpctx,
td ind_nodo_origen, td ind_nodo_destino,
td *antecesores) {
	td dist_origen_dest = 0;

	td *matrix_distancias = NULL;

	nab *distancia_min_origen = NULL;
	nab *distancia_min_destino = NULL;
	nab **distancias_minimas = NULL;

	matrix_distancias = gctx->matrix_distancias;
	dist_origen_dest = *(matrix_distancias + ind_nodo_origen * MXCN
			+ ind_nodo_destino);

	distancias_minimas = cpctx->referencias_directas_por_indice;

	distancia_min_origen = *(distancias_minimas + ind_nodo_origen);
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

void dijkstra_main(void *matrix_distancias, int num_filas,
td ind_nodo_origen, td ind_nodo_destino, gc *gctx,
td *distancias_minimas,
td *antecesores) {

	int contador = 0;
	int num_nodos = 0;

	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td distancia_actual = 0;
	td max_indice = 0;
	td *matrix_distancias_int = NULL;

	gc gctx_mem;
	gc *gctx_int;
	cc cpctx;

	no *nodo_origen_actual = NULL;
	no *nodo_destino_actual = NULL;
	nc *nodo_mas_cercas = NULL;

	bo nodos_distancias_minimas_calculadas[MXN] = { falso };
	nc distancias_minimas_nodos[MXN];

	caca_inutiliza_nodo_cola_prioridad(distancias_minimas_nodos, MXN);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_grafo(matrix_distancias, num_filas, gctx_int, falso, verdadero);
	}
	matrix_distancias_int = gctx_int->matrix_distancias;

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
			if (max_indice > MXN) {
				perror(
						"El indice maximo supera el maximo de nodos permitidos, a la mierda todo");
				abort();
			}
		}
		(distancias_minimas_nodos + nodo_origen_actual->indice)->indice =
				nodo_origen_actual->indice;
		GAN(nodo_origen_actual, GRAFO_PRINCIPAL, falso);
		contador++;
	}
	num_nodos = contador;

	cola_prioridad_init(&cpctx, distancias_minimas_nodos, NULL, NULL,
			max_indice + 1, NULL, NULL);

	contador = 0;
	while (!cola_prioridad_es_vacia(&cpctx)) {
		nodo_mas_cercas = cola_prioridad_pop(&cpctx);
		nodos_distancias_minimas_calculadas[nodo_mas_cercas->indice] =
				verdadero;

		indice_origen_actual = nodo_mas_cercas->indice;

		for (int j = 0; j < MXCN; j++) {
			distancia_actual = (td) *(matrix_distancias_int
					+ indice_origen_actual * MXFN + j);
			indice_destino_actual = j;
			if (distancia_actual != GRAFO_VALOR_INVALIDO
					&& !(*(nodos_distancias_minimas_calculadas
							+ indice_destino_actual))) {
				dijkstra_relaxar_nodo(gctx_int, &cpctx, indice_origen_actual,
						indice_destino_actual, antecesores);
			}
		}

		contador++;
	}
	*(antecesores + ind_nodo_origen) = 0;
	for (int i = 0; i < max_indice + 1; i++) {
		*(distancias_minimas + i) =
				i == ind_nodo_origen ? 0 :
				caca_apuntador_valido(
						(*(cpctx.referencias_directas_por_indice + i))) ?
						(*(cpctx.referencias_directas_por_indice + i))->valor :
						COLA_PRIORIDAD_VALOR_INVALIDO;
	}

}

void cola_prioridad_init(cc *ctx, nc *nodos, td *valores, td *indices,
		int num_nodos, ac *actx, nab **referencias_directas) {
	td indices_int[MXN] = { ARBOL_AVL_INDICE_INVALIDO };
	td datos[MXN] = { ARBOL_AVL_INDICE_INVALIDO };

	memset(ctx, 0, sizeof(cc));
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
		}

		ctx->actx = &ctx->actx_mem;
		ctx->referencias_directas_por_indice =
				ctx->referencias_directas_por_indice_mem;

		arbol_avl_init(ctx->actx, indices_int, datos, num_nodos,
				ctx->referencias_directas_por_indice);
	}

}

nc *cola_prioridad_pop(cc *ctx) {
	nab *nodo_actual = NULL;
	nab *nodo_anterior = NULL;

	nodo_actual = ctx->actx->raiz;

	while (nodo_actual) {
		nodo_anterior = nodo_actual;
		nodo_actual = nodo_actual->hijo_izq;
	}

	arbol_avl_borrar_referencia_directa(&ctx->actx->raiz, nodo_anterior);

	return nodo_anterior;
}

bo cola_prioridad_es_vacia(cc *ctx) {
	return !ctx->actx->raiz;
}

void grafo_copia_profunda(const gc *ctx_origen, gc *ctx_destino,
		td *indices_a_ignorar, int tam_indices_a_ignorar) {
	td indice_nodo_origen_actual = 0;

	td *matrix_origen = NULL;
	td *matrix_destino = NULL;

	no *nodo_origen_principal_actual = NULL;
	no *nodo_destino_principal_actual = NULL;
	no *nodo_destino_principal_previo = NULL;

	matrix_origen = ctx_origen->matrix_distancias;
	matrix_destino = ctx_destino->matrix_distancias;
	memcpy(matrix_destino, matrix_origen,
			sizeof(ctx_origen->matrix_distancias));

	nodo_origen_principal_actual = ctx_origen->inicio;
	while (nodo_origen_principal_actual) {
		indice_nodo_origen_actual = nodo_origen_principal_actual->indice;
		if (indices_a_ignorar
				&& caca_arreglo_contiene(indices_a_ignorar,
						tam_indices_a_ignorar, indice_nodo_origen_actual)) {

			for (int i = 0; i < MXFN; i++) {
				*(matrix_destino + i * MXCN + indice_nodo_origen_actual) =
						GRAFO_VALOR_INVALIDO;
			}
			for (int j = 0; j < MXCN; j++) {
				*(matrix_destino + indice_nodo_origen_actual * MXCN + j) =
				GRAFO_VALOR_INVALIDO;
			}
			GAN(nodo_origen_principal_actual, 0, 0);
			continue;
		}
		nodo_destino_principal_actual = gna(ctx_destino, 1);
		memset(nodo_destino_principal_actual, 0, sizeof(no));
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

		GAN(nodo_origen_principal_actual, 0, 0);
	}

}

#define GRAFO_COPIA_PROPIEDAD(propiedad) nodo_destino->propiedad = nodo_origen->propiedad
static inline void grafo_copia_nodo(const no *nodo_origen, no *nodo_destino) {
	GRAFO_COPIA_PROPIEDAD(distancia);
	GRAFO_COPIA_PROPIEDAD(indice);
	GRAFO_COPIA_PROPIEDAD(valor);
}

static inline bo caca_arreglo_contiene(td *arreglo, int tam_arreglo,
td valor_buscado) {
	for (int i = 0; i < tam_arreglo; i++) {
		if (*(arreglo + i) == valor_buscado) {
			return verdadero;
		}
	}
	return falso;
}

static inline void caca_inutiliza_nodo_cola_prioridad(nc *nodos, int num_nodos) {
	for (int i = 0; i < num_nodos; i++) {
		CPAI((nodos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
		CPAV((nodos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
	}
}

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva) {
	for (int i = 0; i < num_filas; i++) {
		for (int j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_actual + j);
		}

	}
}

int escape_cabron_determina_nodos_viables(void *matrix_aristas, int num_filas,
		gc *grafo_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *distancia_posicion_incomoda_a_inicial) {

	int num_nodos = 0;
	int contador_nodos_ruta_maldita = 0;
	int contador_nodos_recorridos = 0;
	td ancestro_actual = 0;
	gc grafo_inicial_ctx;

	td *distancias_minimas = NULL, *antecesores = NULL;
	td *ruta_maldita;

	num_nodos = init_grafo(matrix_aristas, num_filas, &grafo_inicial_ctx, falso,
			verdadero);

	distancias_minimas = calloc(num_nodos + 1, sizeof(td));
	if (!distancias_minimas) {
		perror("no se consigio memoria para distancias");
		exit(-1);
	}
	antecesores = calloc(num_nodos + 1, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		exit(-1);
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO, (num_nodos + 1) * sizeof(td));
	ruta_maldita = calloc(num_nodos + 1, sizeof(td));
	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(-1);
	}

	dijkstra_main(NULL, 0, posicion_incomoda, posicion_inicial,
			&grafo_inicial_ctx, distancias_minimas, antecesores);

	*(ruta_maldita + contador_nodos_ruta_maldita++) = posicion_inicial;

	while (*(ruta_maldita + contador_nodos_ruta_maldita) != posicion_incomoda
			&& contador_nodos_recorridos < num_nodos + 1) {
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

	if (contador_nodos_ruta_maldita < 2) {
		perror("no c encontraron nodos prohibidos, no mames!");
		abort();
	}

	grafo_copia_profunda(&grafo_inicial_ctx, grafo_viable_ctx, ruta_maldita + 1,
			contador_nodos_ruta_maldita - 1);

	if (distancia_posicion_incomoda_a_inicial) {
		*distancia_posicion_incomoda_a_inicial = *(distancias_minimas
				+ posicion_inicial);
	}
	return num_nodos - contador_nodos_ruta_maldita + 1;
}

float escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
td posicion_polis, td posicion_ratas,
td *salidas_carretera, int num_salidas_carretera) {
	int num_nodos_viables = 0;
	int num_salidas_viables = 0;
	float maxima_velocidad = 0;
	float tiempo_polis = 0;
	td salida_carretera_actual = 0;
	td distancia_salida_carretera_actual = 0;
	td distancia_polis_a_ratas = 0;
	td distancia_recorrida_polis = 0;
	nc *nodo_salida_mas_cercana = NULL;
	gc *grafo_viable_ctx = NULL;
	cc *cola_salidas_carretera = NULL;
	td *distancias_minimas = NULL;
	td *antecesores = NULL;
	td *distancias_salidas_carretera = NULL;
	td *salidas_carretera_viables = NULL;

	grafo_viable_ctx = calloc(1, sizeof(gc));
	if (!grafo_viable_ctx) {
		perror("no se consigio memoria para grafo viable");
		abort();
	}

	num_nodos_viables = escape_cabron_determina_nodos_viables(matrix_aristas,
			num_filas, grafo_viable_ctx, posicion_polis, posicion_ratas,
			&distancia_polis_a_ratas);

	if (num_nodos_viables < 2) {
		return maxima_velocidad;
	}

	distancias_minimas = malloc((num_nodos_viables + 1) * sizeof(td));
	if (!distancias_minimas) {
		perror("no se consigio memoria para distancias");
		abort();
	}
	antecesores = malloc((num_nodos_viables + 1) * sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		abort();
	}
	distancias_salidas_carretera = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para distancias de salidas a carretera");
		abort();
	}
	salidas_carretera_viables = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para salidas a carretera viables");
		abort();
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables + 1) * sizeof(td));
	memset(distancias_minimas, DIJKSTRA_VALOR_INVALIDO,
			(num_nodos_viables + 1) * sizeof(td));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, grafo_viable_ctx,
			distancias_minimas, antecesores);

	for (int i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if ((distancia_salida_carretera_actual = *(distancias_minimas
				+ salida_carretera_actual)) == MAX_VALOR) {
			continue;
		}
		*(distancias_salidas_carretera + num_salidas_viables) =
				distancia_salida_carretera_actual;
		*(salidas_carretera_viables + num_salidas_viables) =
				salida_carretera_actual;
		num_salidas_viables++;
	}

	if (!num_salidas_viables) {
		return maxima_velocidad;
	}

	cola_salidas_carretera = calloc(1, sizeof(cc));
	if (!antecesores) {
		perror("no se consigio memoria para cola de distancias a salidas");
		abort();
	}

	cola_prioridad_init(cola_salidas_carretera, NULL, salidas_carretera_viables,
			distancias_salidas_carretera, num_salidas_carretera, NULL, NULL);

	if (cola_prioridad_es_vacia(cola_salidas_carretera)) {
		return maxima_velocidad;
	}

	nodo_salida_mas_cercana = cola_prioridad_pop(cola_salidas_carretera);

	distancia_recorrida_polis = nodo_salida_mas_cercana->indice
			+ distancia_polis_a_ratas;

	tiempo_polis = (float) distancia_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) nodo_salida_mas_cercana->indice / tiempo_polis;

	return maxima_velocidad;
}

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	td num_nodos = 0, num_salidas = 0;
	td posicion_ratas = 0, posicion_polis = 0;

	td datos_escape_mem[ESCAPE_CABRON_MAX_FILAS_INPUT][ESCAPE_CABRON_MAX_COLS_INPUT] =
			{ { 0 } };

	td *datos_escape = (td *) datos_escape_mem;
	td *inicio_aristas = NULL;
	td *salidas = NULL;

	lee_matrix_long_stdin((td *) datos_escape_mem, &num_aristas, NULL,
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

int main(int argc, char *argv[]) {

	float speed = 0;

	speed = escape_cabron_main();

	if (speed) {
		printf("%.10f\n", speed);
	} else {
		printf("IMPOSSIBLE\n");
	}

	return 0;
}
