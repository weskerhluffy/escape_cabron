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

#define GRAFO_no_ORIGEN 0
#define GRAFO_no_DESTINO 1
#define GRAFO_dis_ENTRE_noS 2

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bo;

#define GAN(no_apuntador,criterio_busqueda,discriminar_principal) \
		no_apuntador = (no_apuntador)->siguiente;

#define AAAA(no) \
	(no)->altura = ((no)->hijo_izq || (no)->hijo_der)? \
			caca_int_max(AAOA((no)->hijo_izq), AAOA((no)->hijo_der)) + 1: \
			0;

#define AAOA(no) \
	((no)?(no)->altura:0)

#define AAOV(no) \
	((no)?(no)->valor:ARBOL_AVL_VALOR_INVALIDO)

#define AAAP(no,nuevo_padre) \
	((no)?(no)->padre=(nuevo_padre):((void)0))

#define AAOP(no) \
	((no)?(no)->padre:NULL)

#define AAOI(no) \
	((no)?(no)->indice:ARBOL_AVL_INDICE_INVALIDO)

#define ABAI(no,nuevo_hijo) \
	((no)?(no)->hijo_izq=(nuevo_hijo):((void)0))

#define ABAD(no,nuevo_hijo) \
	((no)?(no)->hijo_der=(nuevo_hijo):((void)0))

#define CPAI(no,nuevo_indice) \
	(no)->indice=nuevo_indice

#define CPAV(no,nuevo_valor) \
	(no)->indice=nuevo_valor

typedef struct no {
	td valor;
	td indice;
	td dis;
	struct no *siguiente;
	struct no *anterior;
} no;

typedef struct no_arbol_binario {
	td indice;
	td valor;
	unsigned int altura;

	struct no_arbol_binario *hijo_izq;
	struct no_arbol_binario *hijo_der;
	struct no_arbol_binario *padre;
} nab;

typedef struct grifo_contexto {
	int localidades_usadas;
	no *inicio;
	no *final;
	no nos_disponibles[MXN];
	td matrix_diss[MXCN][MXFN];
	no *referencias_nos_por_indice[MXFN];
} gc;

typedef struct arbol_binario_contexto {
	bo no_indices_repetidos;
	int localidades_usadas;
	nab *rz;
	nab nos_disponibles[MXN];
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
td *datos, int num_datos, nab **arreglo_referencias_nos);

#define AAAI -1
#define AAAD 1
#define AAAB 0

static inline int aada(nab *no, int tolerancia,
		bo considerar_balanceado_cargado_der);

static inline nab *aba(ac *ctx, int localidades_solicitadas);

void arbol_avl_insertar(nab **rz, nab *no_a_insertar,
		bo no_indices_repetidos);

static inline int aacn(nab *no1, nab *no2);

static inline int caca_int_max(int a, int b);

static inline void abri(nab **no);
static inline void abrd(nab **no);

void arbol_binario_borrar_no(nab **rz,
td valor_a_borrar);

void arbol_avl_borrar(nab **rz, td valor_a_borrar);

void arbol_avl_borrar_referencia_directa(nab **rz, nab *no_a_borrar);

void cola_prioridad_modificar_valor_no(cc *cpctx,
td indice, td nuevo_valor);

void dijkstra_relaxar_no(gc *gctx, cc *cpctx,
td ind_no_origen, td ind_no_destino,
td *antecesores);

void cola_prioridad_init(cc *ctx, nc *nos, td *valores, td *indices,
		int num_nos, ac *actx, nab **referencias_directas);

nc *cola_prioridad_pop(cc *ctx);

bo cola_prioridad_es_vacia(cc *ctx);

void dijkstra_main(void *matrix_diss, int num_filas,
td ind_no_origen, td ind_no_destino, gc *gctx,
td *diss_minimas,
td *antecesores);

static inline void grafo_copia_no(const no *no_origen, no *no_destino);

static inline bo caca_arreglo_contiene(td *arreglo, int tam_arreglo,
td valor_buscado);

void grafo_copia_profunda(const gc *ctx_origen, gc *ctx_destino,
		td *indices_a_ignorar, int tam_indices_a_ignorar);

static inline void caca_inutiliza_no_cola_prioridad(nc *nos, int num_nos);

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva);

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nos_viables(void *matrix_vertices, int num_filas,
		gc *grafo_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *dis_posicion_incomoda_a_inicial);

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
	int contador_nos = 0;
	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td dis_actual = 0;
	td *matrix_int = NULL;
	td *matrix_diss = NULL;
	no *nuevo_no = NULL;
	td nos_registrados[MXN] = { falso };

	memset(ctx, 0, sizeof(gc));

	matrix_int = matrix;
	matrix_diss = ctx->matrix_diss;
	memset(matrix_diss, GRAFO_VALOR_INVALIDO,
			sizeof(ctx->matrix_diss));
	for (int i = 0; i < num_filas; i++) {
		indice_origen_actual = *(matrix_int + i * 3 + GRAFO_no_ORIGEN);
		indice_destino_actual = *(matrix_int + i * 3 + GRAFO_no_DESTINO);
		dis_actual = *(matrix_int + i * 3 + GRAFO_dis_ENTRE_noS);

		*(matrix_diss + indice_origen_actual * MXCN
				+ indice_destino_actual) = dis_actual;
		if (relaciones_bidireccionales) {
			*(matrix_diss + indice_destino_actual * MXCN
					+ indice_origen_actual) = dis_actual;
		}
		if (!*(nos_registrados + indice_origen_actual)) {
			nuevo_no = gna(ctx, 1);
			nuevo_no->indice = indice_origen_actual;
			if (ctx->inicio) {
				ctx->final->siguiente = nuevo_no;
			} else {
				ctx->inicio = nuevo_no;
			}
			ctx->final = nuevo_no;
			*(nos_registrados + indice_origen_actual) = verdadero;
			contador_nos++;
		}
		if (!*(nos_registrados + indice_destino_actual)) {
			nuevo_no = gna(ctx, 1);
			nuevo_no->indice = indice_destino_actual;
			ctx->final->siguiente = nuevo_no;
			ctx->final = nuevo_no;
			*(nos_registrados + indice_destino_actual) = verdadero;
			contador_nos++;
		}
	}
	return contador_nos;
}

no *gna(gc *ctx, int localidades_solicitadas) {
	no *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nos_disponibles
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
td *datos, int num_datos, nab **arreglo_referencias_nos) {
	int i = 0;
	td dato_actual = 0;
	nab *no_actual = NULL;

	memset((void *) ctx, 0, sizeof(ac));
	memset((void *) ctx->nos_disponibles, 0, sizeof(ctx->nos_disponibles));

	for (i = 0; i < num_datos; i++) {
		if (indices && *(indices + i) == ARBOL_AVL_INDICE_INVALIDO) {
			continue;
		}

		if (!ctx->rz) {
			ctx->rz = aba(ctx, 1);
			if (indices) {
				ctx->rz->indice = *(indices + i);
			} else {
				ctx->rz->indice = 1;
			}
			if (arreglo_referencias_nos) {
				if (indices) {
					*(arreglo_referencias_nos + *(indices + i)) = ctx->rz;

				} else {
					*(arreglo_referencias_nos + 1) = ctx->rz;
				}
			}
			ctx->rz->valor = *(datos + i);
			continue;
		}

		dato_actual = *(datos + i);
		no_actual = aba(ctx, 1);

		no_actual->valor = dato_actual;
		if (indices) {
			no_actual->indice = *(indices + i);
		} else {
			no_actual->indice = i + 1;
		}

		arbol_avl_insertar(&ctx->rz, no_actual, ctx->no_indices_repetidos);
		if (arreglo_referencias_nos) {
			if (indices) {
				*(arreglo_referencias_nos + *(indices + i)) = no_actual;

			} else {
				*(arreglo_referencias_nos + i + 1) = no_actual;
			}
		}
	}
}

void arbol_avl_insertar(nab **rz, nab *no_a_insertar,
		bo no_indices_repetidos) {
	nab *rz_int = NULL;

	rz_int = *rz;

	if (!rz_int) {
		*rz = no_a_insertar;
		return;
	}

	switch (aacn(rz_int, no_a_insertar)) {
	case CACA_COMPARACION_IZQ_MENOR:
		if (rz_int->hijo_der) {
			arbol_avl_insertar(&rz_int->hijo_der, no_a_insertar,
					no_indices_repetidos);
		} else {
			rz_int->hijo_der = no_a_insertar;
			AAAP(no_a_insertar, rz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_MAYOR:
		if (rz_int->hijo_izq) {
			arbol_avl_insertar(&rz_int->hijo_izq, no_a_insertar,
					no_indices_repetidos);
		} else {
			rz_int->hijo_izq = no_a_insertar;
			AAAP(no_a_insertar, rz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_IGUAL:
		if (no_indices_repetidos) {
			perror("NO mames, una llave repetida, ahhhhh !");
			exit(1);
		} else {
			if (rz_int->hijo_der) {
				arbol_avl_insertar(&rz_int->hijo_der, no_a_insertar,
						no_indices_repetidos);
			} else {
				rz_int->hijo_der = no_a_insertar;
				AAAP(no_a_insertar, rz_int);
			}
		}
		break;
	default:
		perror("NO mames, resultado increible en arbol_avl_insertar!");
		exit(1);
		break;
	}

	AAAA(rz_int);

	switch (aada(rz_int, 1, verdadero)) {
	case AAAI:
		if (AAOV(
				rz_int->hijo_izq) < AAOV(no_a_insertar)) {
			abri(&rz_int->hijo_izq);
		}
		abrd(rz);
		break;
	case AAAD:
		if (AAOV(
				rz_int->hijo_der) > AAOV(no_a_insertar)) {
			abrd(&rz_int->hijo_der);
		}
		abri(rz);
		break;
	case AAAB:
		break;
	default:
		perror("error en altura indeterminada, verga");
		exit(1);
		break;
	}

}

static inline int aacn(nab *no1, nab *no2) {
	if (no1->valor < no2->valor) {
		return CACA_COMPARACION_IZQ_MENOR;
	} else {
		if (no1->valor > no2->valor) {
			return CACA_COMPARACION_IZQ_MAYOR;
		} else {
			return CACA_COMPARACION_IZQ_IGUAL;
		}
	}
}

static inline int caca_int_max(int a, int b) {
	return (a > b) ? a : b;
}

static inline int aada(nab *no, int tolerancia,
		bo considerar_balanceado_cargado_der) {
	int diferencia_alturas = 0;
	diferencia_alturas = AAOA(
			no->hijo_izq) - AAOA(no->hijo_der);
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

static inline void abri(nab **no) {
	nab *no_int = NULL;
	nab *hijo_der = NULL;
	nab *hijo_der_subarbol_izq = NULL;

	no_int = *no;
	hijo_der = no_int->hijo_der;
	hijo_der_subarbol_izq = hijo_der->hijo_izq;

	no_int->hijo_der = hijo_der_subarbol_izq;
	hijo_der->hijo_izq = no_int;

	AAAP(hijo_der, AAOP(no_int));
	AAAP(hijo_der_subarbol_izq, no_int);
	AAAP(no_int, hijo_der);

	AAAA(no_int);
	AAAA(hijo_der);

	*no = hijo_der;

}

static inline void abrd(nab **no) {
	nab *no_int = NULL;
	nab *hijo_izq = NULL;
	nab *hijo_izq_subarbol_der = NULL;

	no_int = *no;
	hijo_izq = no_int->hijo_izq;
	hijo_izq_subarbol_der = hijo_izq->hijo_der;

	no_int->hijo_izq = hijo_izq_subarbol_der;
	hijo_izq->hijo_der = no_int;

	AAAP(hijo_izq, AAOP(no_int));
	AAAP(hijo_izq_subarbol_der, no_int);
	AAAP(no_int, hijo_izq);

	AAAA(no_int);
	AAAA(hijo_izq);

	*no = hijo_izq;

}

static inline nab *aba(ac *ctx, int localidades_solicitadas) {
	nab *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

static inline nab *arbol_binario_get_no_minimo_valor(nab *rz) {
	nab *no_actual = NULL;
	no_actual = rz;
	while (no_actual->hijo_izq) {
		no_actual = no_actual->hijo_izq;
	}
	return no_actual;
}

void arbol_binario_borrar_no(nab **rz,
td valor_a_borrar) {
	nab *rz_int = NULL;
	nab *no_min = NULL;

	rz_int = *rz;

	if (!rz_int) {
		return;
	}
	if (rz_int->valor > valor_a_borrar) {
		arbol_binario_borrar_no(&rz_int->hijo_izq, valor_a_borrar);
	} else {
		if (rz_int->valor < valor_a_borrar) {
			arbol_binario_borrar_no(&rz_int->hijo_der, valor_a_borrar);
		} else {
			if (!rz_int->hijo_izq) {
				*rz = rz_int->hijo_der;
			} else {
				if (!rz_int->hijo_der) {
					*rz = rz_int->hijo_izq;
				} else {
					no_min = arbol_binario_get_no_minimo_valor(
							rz_int->hijo_der);
					rz_int->valor = no_min->valor;
					arbol_binario_borrar_no(&rz_int->hijo_der,
							rz_int->valor);
				}
			}
		}
	}

}


void arbol_avl_borrar(nab **rz, td valor_a_borrar) {

	nab *rz_int = NULL;
	nab *no_min = NULL;

	rz_int = *rz;

	if (!rz_int) {
		return;
	}
	if (rz_int->valor > valor_a_borrar) {
		arbol_avl_borrar(&rz_int->hijo_izq, valor_a_borrar);
	} else {
		if (rz_int->valor < valor_a_borrar) {
			arbol_avl_borrar(&rz_int->hijo_der, valor_a_borrar);
		} else {
			if (!rz_int->hijo_izq) {
				*rz = rz_int->hijo_der;
			} else {
				if (!rz_int->hijo_der) {
					*rz = rz_int->hijo_izq;
				} else {
					no_min = arbol_binario_get_no_minimo_valor(
							rz_int->hijo_der);
					rz_int->valor = no_min->valor;
					arbol_avl_borrar(&rz_int->hijo_der, rz_int->valor);

					ABAI(no_min, rz_int->hijo_izq);
					ABAD(no_min, rz_int->hijo_der);
					AAAP(no_min, rz_int->padre);
					no_min->altura = AAOA(rz_int);
					AAAP(rz_int->hijo_izq, no_min);
					AAAP(rz_int->hijo_der, no_min);
					*rz = no_min;
				}
			}
		}
	}

	if (!*rz) {
		return;
	}

	AAAA(rz_int);

	switch (aada(rz_int, 1, verdadero)) {
	case AAAI:
		if (aada(rz_int->hijo_izq, 0, falso) == AAAD) {
			abri(&rz_int->hijo_izq);
		}
		abrd(rz);
		break;
	case AAAD:
		if (aada(rz_int->hijo_der, 0, verdadero) == AAAI) {
			abrd(&rz_int->hijo_der);
		}
		abri(rz);
		break;
	case AAAB:
		break;
	default:
		break;
	}

}

void arbol_avl_borrar_referencia_directa(nab **rz, nab *no_a_borrar) {

	nab *ancestro_actual = NULL;
	nab *no_a_borrar_padre = NULL;
	nab *no_min = NULL;

	nab **ancestro_actual_apuntador = NULL;
	nab **no_a_borrar_ref = NULL;

	if (!no_a_borrar) {
		abort();
	}

	if (!(no_a_borrar_padre = AAOP(no_a_borrar))) {
		no_a_borrar_padre = NULL;
		no_a_borrar_ref = rz;
	} else {

		no_a_borrar_ref =
				no_a_borrar->valor < (no_a_borrar_padre)->valor ?
						&no_a_borrar_padre->hijo_izq :
				no_a_borrar->valor > (no_a_borrar_padre)->valor ?
						&no_a_borrar_padre->hijo_der :
				no_a_borrar->indice == AAOI(no_a_borrar_padre->hijo_izq) ?
						&no_a_borrar_padre->hijo_izq :
						&no_a_borrar_padre->hijo_der;

	}

	ancestro_actual = no_a_borrar->padre;
	ancestro_actual_apuntador = &no_a_borrar->padre;

	if (!no_a_borrar->hijo_izq) {
		AAAP(no_a_borrar->hijo_der, ancestro_actual);
		*no_a_borrar_ref = no_a_borrar->hijo_der;
	} else {
		if (!no_a_borrar->hijo_der) {
			AAAP(no_a_borrar->hijo_izq, ancestro_actual);
			*no_a_borrar_ref = no_a_borrar->hijo_izq;
		} else {
			no_min = arbol_binario_get_no_minimo_valor(
					no_a_borrar->hijo_der);

			arbol_avl_borrar_referencia_directa(rz, no_min);
			ABAI(no_min, no_a_borrar->hijo_izq);
			ABAD(no_min, no_a_borrar->hijo_der);
			AAAP(no_min, no_a_borrar->padre);
			no_min->altura = AAOA(no_a_borrar);

			AAAP(no_a_borrar->hijo_izq, no_min);
			AAAP(no_a_borrar->hijo_der, no_min);

			*no_a_borrar_ref = no_min;
		}
	}

	do {
		if (!AAOP(no_a_borrar)) {
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
			ancestro_actual_apuntador = rz;
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

void cola_prioridad_modificar_valor_no(cc *cpctx,
td indice, td nuevo_valor) {
	nab *referencia_directa = NULL;
	nab *nuevo_no = NULL;
	nab **referencias_directas = NULL;
	nab **rz = NULL;

	referencias_directas = cpctx->referencias_directas_por_indice;
	rz = &cpctx->actx->rz;

	referencia_directa = *(referencias_directas + indice);


	arbol_avl_borrar_referencia_directa(&cpctx->actx->rz, referencia_directa);


	nuevo_no = aba(cpctx->actx, 1);
	memset(nuevo_no, 0, sizeof(nab));
	nuevo_no->indice = indice;
	nuevo_no->valor = nuevo_valor;

	arbol_avl_insertar(rz, nuevo_no, falso);

	*(referencias_directas + indice) = nuevo_no;
}

void dijkstra_relaxar_no(gc *gctx, cc *cpctx,
td ind_no_origen, td ind_no_destino,
td *antecesores) {
	td dist_origen_dest = 0;

	td *matrix_diss = NULL;

	nab *dis_min_origen = NULL;
	nab *dis_min_destino = NULL;
	nab **diss_minimas = NULL;

	matrix_diss = gctx->matrix_diss;
	dist_origen_dest = *(matrix_diss + ind_no_origen * MXCN
			+ ind_no_destino);

	diss_minimas = cpctx->referencias_directas_por_indice;

	dis_min_origen = *(diss_minimas + ind_no_origen);
	dis_min_destino = *(diss_minimas + ind_no_destino);

	if (dis_min_destino->valor
			> dis_min_origen->valor + dist_origen_dest) {
		cola_prioridad_modificar_valor_no(cpctx, ind_no_destino,
				dis_min_origen->valor + dist_origen_dest);
		if (antecesores) {
			*(antecesores + ind_no_destino) = ind_no_origen;
		}
	}
}

void dijkstra_main(void *matrix_diss, int num_filas,
td ind_no_origen, td ind_no_destino, gc *gctx,
td *diss_minimas,
td *antecesores) {

	int contador = 0;
	int num_nos = 0;

	td indice_origen_actual = 0;
	td indice_destino_actual = 0;
	td dis_actual = 0;
	td max_indice = 0;
	td *matrix_diss_int = NULL;

	gc gctx_mem;
	gc *gctx_int;
	cc cpctx;

	no *no_origen_actual = NULL;
	no *no_destino_actual = NULL;
	nc *no_mas_cercas = NULL;

	bo nos_diss_minimas_calculadas[MXN] = { falso };
	nc diss_minimas_nos[MXN];

	caca_inutiliza_no_cola_prioridad(diss_minimas_nos, MXN);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_grafo(matrix_diss, num_filas, gctx_int, falso, verdadero);
	}
	matrix_diss_int = gctx_int->matrix_diss;

	no_origen_actual = gctx_int->inicio;

	while (no_origen_actual) {
		if (no_origen_actual->indice == ind_no_origen) {
			(diss_minimas_nos + no_origen_actual->indice)->valor = 0;
		} else {
			(diss_minimas_nos + no_origen_actual->indice)->valor =
			MAX_VALOR;
		}
		if (no_origen_actual->indice > max_indice) {
			max_indice = no_origen_actual->indice;
			if (max_indice > MXN) {
				perror(
						"El indice maximo supera el maximo de nos permitidos, a la mierda todo");
				abort();
			}
		}
		(diss_minimas_nos + no_origen_actual->indice)->indice =
				no_origen_actual->indice;
		GAN(no_origen_actual, GRAFO_PRINCIPAL, falso);
		contador++;
	}
	num_nos = contador;

	cola_prioridad_init(&cpctx, diss_minimas_nos, NULL, NULL,
			max_indice + 1, NULL, NULL);

	contador = 0;
	while (!cola_prioridad_es_vacia(&cpctx)) {
		no_mas_cercas = cola_prioridad_pop(&cpctx);
		nos_diss_minimas_calculadas[no_mas_cercas->indice] =
				verdadero;

		indice_origen_actual = no_mas_cercas->indice;

		for (int j = 0; j < MXCN; j++) {
			dis_actual = (td) *(matrix_diss_int
					+ indice_origen_actual * MXFN + j);
			indice_destino_actual = j;
			if (dis_actual != GRAFO_VALOR_INVALIDO
					&& !(*(nos_diss_minimas_calculadas
							+ indice_destino_actual))) {
				dijkstra_relaxar_no(gctx_int, &cpctx, indice_origen_actual,
						indice_destino_actual, antecesores);
			}
		}

		contador++;
	}
	*(antecesores + ind_no_origen) = 0;
	for (int i = 0; i < max_indice + 1; i++) {
		*(diss_minimas + i) =
				i == ind_no_origen ? 0 :
				caca_apuntador_valido(
						(*(cpctx.referencias_directas_por_indice + i))) ?
						(*(cpctx.referencias_directas_por_indice + i))->valor :
						COLA_PRIORIDAD_VALOR_INVALIDO;
	}

}

void cola_prioridad_init(cc *ctx, nc *nos, td *valores, td *indices,
		int num_nos, ac *actx, nab **referencias_directas) {
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
		for (int i = 0; i < num_nos; i++) {
			if (nos) {
				if ((nos + i)->indice == COLA_PRIORIDAD_VALOR_INVALIDO) {
					continue;
				}
				*(indices_int + i) = (nos + i)->indice;
				*(datos + i) = (nos + i)->valor;
			} else {
				if (!valores) {
					perror("no se proporcionaron nos ni valores");
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

		arbol_avl_init(ctx->actx, indices_int, datos, num_nos,
				ctx->referencias_directas_por_indice);
	}

}

nc *cola_prioridad_pop(cc *ctx) {
	nab *no_actual = NULL;
	nab *no_anterior = NULL;

	no_actual = ctx->actx->rz;

	while (no_actual) {
		no_anterior = no_actual;
		no_actual = no_actual->hijo_izq;
	}

	arbol_avl_borrar_referencia_directa(&ctx->actx->rz, no_anterior);

	return no_anterior;
}

bo cola_prioridad_es_vacia(cc *ctx) {
	return !ctx->actx->rz;
}

void grafo_copia_profunda(const gc *ctx_origen, gc *ctx_destino,
		td *indices_a_ignorar, int tam_indices_a_ignorar) {
	td indice_no_origen_actual = 0;

	td *matrix_origen = NULL;
	td *matrix_destino = NULL;

	no *no_origen_principal_actual = NULL;
	no *no_destino_principal_actual = NULL;
	no *no_destino_principal_previo = NULL;

	matrix_origen = ctx_origen->matrix_diss;
	matrix_destino = ctx_destino->matrix_diss;
	memcpy(matrix_destino, matrix_origen,
			sizeof(ctx_origen->matrix_diss));

	no_origen_principal_actual = ctx_origen->inicio;
	while (no_origen_principal_actual) {
		indice_no_origen_actual = no_origen_principal_actual->indice;
		if (indices_a_ignorar
				&& caca_arreglo_contiene(indices_a_ignorar,
						tam_indices_a_ignorar, indice_no_origen_actual)) {

			for (int i = 0; i < MXFN; i++) {
				*(matrix_destino + i * MXCN + indice_no_origen_actual) =
						GRAFO_VALOR_INVALIDO;
			}
			for (int j = 0; j < MXCN; j++) {
				*(matrix_destino + indice_no_origen_actual * MXCN + j) =
				GRAFO_VALOR_INVALIDO;
			}
			GAN(no_origen_principal_actual, 0, 0);
			continue;
		}
		no_destino_principal_actual = gna(ctx_destino, 1);
		memset(no_destino_principal_actual, 0, sizeof(no));
		grafo_copia_no(no_origen_principal_actual,
				no_destino_principal_actual);
		if (no_destino_principal_previo) {
			no_destino_principal_previo->siguiente =
					no_destino_principal_actual;
			no_destino_principal_actual->anterior =
					no_destino_principal_previo;
		} else {
			ctx_destino->inicio = no_destino_principal_actual;
		}
		no_destino_principal_previo = no_destino_principal_actual;

		GAN(no_origen_principal_actual, 0, 0);
	}

}

#define GRAFO_COPIA_PROPIEDAD(propiedad) no_destino->propiedad = no_origen->propiedad
static inline void grafo_copia_no(const no *no_origen, no *no_destino) {
	GRAFO_COPIA_PROPIEDAD(dis);
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

static inline void caca_inutiliza_no_cola_prioridad(nc *nos, int num_nos) {
	for (int i = 0; i < num_nos; i++) {
		CPAI((nos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
		CPAV((nos + i), COLA_PRIORIDAD_VALOR_INVALIDO);
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

int escape_cabron_determina_nos_viables(void *matrix_aristas, int num_filas,
		gc *grafo_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *dis_posicion_incomoda_a_inicial) {

	int num_nos = 0;
	int contador_nos_ruta_maldita = 0;
	int contador_nos_recorridos = 0;
	td ancestro_actual = 0;
	gc grafo_inicial_ctx;

	td *diss_minimas = NULL, *antecesores = NULL;
	td *ruta_maldita;

	num_nos = init_grafo(matrix_aristas, num_filas, &grafo_inicial_ctx, falso,
			verdadero);

	diss_minimas = calloc(num_nos + 1, sizeof(td));
	if (!diss_minimas) {
		perror("no se consigio memoria para diss");
		exit(-1);
	}
	antecesores = calloc(num_nos + 1, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		exit(-1);
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO, (num_nos + 1) * sizeof(td));
	ruta_maldita = calloc(num_nos + 1, sizeof(td));
	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(-1);
	}

	dijkstra_main(NULL, 0, posicion_incomoda, posicion_inicial,
			&grafo_inicial_ctx, diss_minimas, antecesores);

	*(ruta_maldita + contador_nos_ruta_maldita++) = posicion_inicial;

	while (*(ruta_maldita + contador_nos_ruta_maldita) != posicion_incomoda
			&& contador_nos_recorridos < num_nos + 1) {
		ancestro_actual = *(antecesores
				+ *(ruta_maldita + contador_nos_ruta_maldita - 1));
		if (ancestro_actual != 0) {
			*(ruta_maldita + contador_nos_ruta_maldita) = ancestro_actual;
			contador_nos_ruta_maldita++;
		} else {
			break;
		}
		contador_nos_recorridos++;
	}

	if (contador_nos_ruta_maldita < 2) {
		perror("no c encontraron nos prohibidos, no mames!");
		abort();
	}

	grafo_copia_profunda(&grafo_inicial_ctx, grafo_viable_ctx, ruta_maldita + 1,
			contador_nos_ruta_maldita - 1);

	if (dis_posicion_incomoda_a_inicial) {
		*dis_posicion_incomoda_a_inicial = *(diss_minimas
				+ posicion_inicial);
	}
	return num_nos - contador_nos_ruta_maldita + 1;
}

float escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
td posicion_polis, td posicion_ratas,
td *salidas_carretera, int num_salidas_carretera) {
	int num_nos_viables = 0;
	int num_salidas_viables = 0;
	float maxima_velocidad = 0;
	float tiempo_polis = 0;
	td salida_carretera_actual = 0;
	td dis_salida_carretera_actual = 0;
	td dis_polis_a_ratas = 0;
	td dis_recorrida_polis = 0;
	nc *no_salida_mas_cercana = NULL;
	gc *grafo_viable_ctx = NULL;
	cc *cola_salidas_carretera = NULL;
	td *diss_minimas = NULL;
	td *antecesores = NULL;
	td *diss_salidas_carretera = NULL;
	td *salidas_carretera_viables = NULL;

	grafo_viable_ctx = calloc(1, sizeof(gc));
	if (!grafo_viable_ctx) {
		perror("no se consigio memoria para grafo viable");
		abort();
	}

	num_nos_viables = escape_cabron_determina_nos_viables(matrix_aristas,
			num_filas, grafo_viable_ctx, posicion_polis, posicion_ratas,
			&dis_polis_a_ratas);

	if (num_nos_viables < 2) {
		return maxima_velocidad;
	}

	diss_minimas = malloc((num_nos_viables + 1) * sizeof(td));
	if (!diss_minimas) {
		perror("no se consigio memoria para diss");
		abort();
	}
	antecesores = malloc((num_nos_viables + 1) * sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		abort();
	}
	diss_salidas_carretera = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para diss de salidas a carretera");
		abort();
	}
	salidas_carretera_viables = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para salidas a carretera viables");
		abort();
	}
	memset(antecesores, DIJKSTRA_VALOR_INVALIDO,
			(num_nos_viables + 1) * sizeof(td));
	memset(diss_minimas, DIJKSTRA_VALOR_INVALIDO,
			(num_nos_viables + 1) * sizeof(td));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, grafo_viable_ctx,
			diss_minimas, antecesores);

	for (int i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if ((dis_salida_carretera_actual = *(diss_minimas
				+ salida_carretera_actual)) == MAX_VALOR) {
			continue;
		}
		*(diss_salidas_carretera + num_salidas_viables) =
				dis_salida_carretera_actual;
		*(salidas_carretera_viables + num_salidas_viables) =
				salida_carretera_actual;
		num_salidas_viables++;
	}

	if (!num_salidas_viables) {
		return maxima_velocidad;
	}

	cola_salidas_carretera = calloc(1, sizeof(cc));
	if (!antecesores) {
		perror("no se consigio memoria para cola de diss a salidas");
		abort();
	}

	cola_prioridad_init(cola_salidas_carretera, NULL, salidas_carretera_viables,
			diss_salidas_carretera, num_salidas_carretera, NULL, NULL);

	if (cola_prioridad_es_vacia(cola_salidas_carretera)) {
		return maxima_velocidad;
	}

	no_salida_mas_cercana = cola_prioridad_pop(cola_salidas_carretera);

	dis_recorrida_polis = no_salida_mas_cercana->indice
			+ dis_polis_a_ratas;

	tiempo_polis = (float) dis_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) no_salida_mas_cercana->indice / tiempo_polis;

	return maxima_velocidad;
}

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	td num_nos = 0, num_salidas = 0;
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

	num_nos = *datos_escape;
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
