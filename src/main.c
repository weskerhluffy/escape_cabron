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

#define GF_vl_INVALIDO -1
#define ARBOL_AVL_id_INVALIDO -1
#define ARBOL_AVL_vl_INVALIDO -1
#define CP_vl_INVALIDO GF_vl_INVALIDO
#define DIJKSTRA_vl_INVALIDO -1

#define MAX_vl (td) (2<<28)

#define GF_no_or 0
#define GF_no_ds 1
#define GF_dis_ENTRE_noS 2

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
	((no)?(no)->vl:ARBOL_AVL_vl_INVALIDO)

#define AAAP(no,nuevo_padre) \
	((no)?(no)->padre=(nuevo_padre):((void)0))

#define AAOP(no) \
	((no)?(no)->padre:NULL)

#define AAOI(no) \
	((no)?(no)->id:ARBOL_AVL_id_INVALIDO)

#define ABAI(no,nuevo_hijo) \
	((no)?(no)->hijo_izq=(nuevo_hijo):((void)0))

#define ABAD(no,nuevo_hijo) \
	((no)?(no)->hijo_der=(nuevo_hijo):((void)0))

#define CPAI(no,nuevo_id) \
	(no)->id=nuevo_id

#define CPAV(no,nuevo_vl) \
	(no)->id=nuevo_vl

typedef struct no {
	td vl;
	td id;
	td dis;
	struct no *siguiente;
	struct no *anterior;
} no;

typedef struct no_arbol_binario {
	td id;
	td vl;
	unsigned int altura;

	struct no_arbol_binario *hijo_izq;
	struct no_arbol_binario *hijo_der;
	struct no_arbol_binario *padre;
} nab;

typedef struct grifo_contexto {
	int localidades_usadas;
	no *ini;
	no *final;
	no nos_disponibles[MXN];
	td matrix_diss[MXCN][MXFN];
	no *referencias_nos_por_id[MXFN];
} gc;

typedef struct arbol_binario_contexto {
	bo no_ids_repetidos;
	int localidades_usadas;
	nab *rz;
	nab nos_disponibles[MXN];
} ac;

typedef struct cola_prioridad_contexto {
	ac actx_mem;
	ac *actx;
	nab *referencias_directas_por_id_mem[MXN];
	nab **referencias_directas_por_id;
} cc;

typedef nab nc;

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int init_gf(void *matrix, int num_filas, gc *ctx, bo usar_hashes,
		bo relaciones_bidireccionales);

int caca_apuntador_valido(void *p);

void arbol_avl_init(ac *ctx, td *ids,
td *datos, int num_datos, nab **arreglo_referencias_nos);

#define AAAI -1
#define AAAD 1
#define AAAB 0

static int aada(nab *no, int tolerancia, bo considerar_balanceado_cargado_der);

static nab *aba(ac *ctx, int localidades_solicitadas);

void arbol_avl_insertar(nab **rz, nab *no_a_insertar, bo no_ids_repetidos);

static int aacn(nab *no1, nab *no2);

static int caca_int_max(int a, int b);

static void abri(nab **no);
static void abrd(nab **no);

void arbol_binario_borrar_no(nab **rz,
td vl_a_borrar);

void arbol_avl_borrar(nab **rz, td vl_a_borrar);

void arbol_avl_borrar_referencia_directa(nab **rz, nab *no_a_borrar);

void cola_prioridad_modificar_vl_no(cc *cpctx,
td id, td nuevo_vl);

void dijkstra_relaxar_no(gc *gctx, cc *cpctx,
td ind_no_or, td ind_no_ds,
td *antecesores);

void cola_prioridad_init(cc *ctx, nc *nos, td *vles, td *ids, int num_nos,
		ac *actx, nab **referencias_directas);

nc *cola_prioridad_pop(cc *ctx);

bo cola_prioridad_es_vacia(cc *ctx);

void dijkstra_main(void *matrix_diss, int num_filas,
td ind_no_or, td ind_no_ds, gc *gctx,
td *diss_minimas,
td *antecesores);

static void gf_copia_no(const no *no_or, no *no_ds);

static bo caca_arreglo_contiene(td *arreglo, int tam_arreglo,
td vl_buscado);

void gf_copia_profunda(const gc *ctx_or, gc *ctx_ds,
td *ids_a_ignorar, int tam_ids_a_ignorar);

static void caca_inutiliza_no_cola_prioridad(nc *nos, int num_nos);

void caca_realinea_array(td *arreglo, int num_filas, int alineacion_actual,
		int alineacion_nueva);

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nos_viables(void *matrix_vertices, int num_filas,
		gc *gf_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *dis_posicion_incomoda_a_inicial);

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
td posicion_polis, td posicion_ratas,
td *salidas_carretera, int num_salidas_carretera);

float escape_cabron_main();

no *gna(gc *ctx, int localidades_solicitadas);

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int id_filas = 0;
	int id_columnas = 0;
	long numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char linea[MXL];

	while (fgets(linea, MXL, stdin)) {
		id_columnas = 0;
		cadena_numero_actual = linea;
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + id_filas * num_max_columnas + id_columnas) = numero;
			id_columnas++;
			if (id_columnas >= num_max_columnas) {
				perror("se leyeron demasiadas columnas, a la verga");
				abort();
			}
		}
		if (num_columnas) {
			num_columnas[id_filas] = id_columnas;
		}
		id_filas++;
		if (id_filas >= num_max_filas) {
			perror("se leyeron demasiadas filas, a la verga");
			abort();
		}
	}

	*num_filas = id_filas;
	return 0;
}

int init_gf(void *matrix, int num_filas, gc *ctx, bo usar_hashes,
		bo relaciones_bidireccionales) {
	int contador_nos = 0;
	td id_or_actual = 0;
	td id_ds_actual = 0;
	td dis_actual = 0;
	td *matrix_int = NULL;
	td *matrix_diss = NULL;
	no *nuevo_no = NULL;
	td nos_registrados[MXN] = { falso };
	int i = 0;

	memset(ctx, 0, sizeof(gc));

	matrix_int = (td *)matrix;
	matrix_diss = (td *) ctx->matrix_diss;
	memset(matrix_diss, GF_vl_INVALIDO, sizeof(ctx->matrix_diss));
	for (i = 0; i < num_filas; i++) {
		id_or_actual = *(matrix_int + i * 3 + GF_no_or);
		id_ds_actual = *(matrix_int + i * 3 + GF_no_ds);
		dis_actual = *(matrix_int + i * 3 + GF_dis_ENTRE_noS);

		*(matrix_diss + id_or_actual * MXCN + id_ds_actual) = dis_actual;
		if (relaciones_bidireccionales) {
			*(matrix_diss + id_ds_actual * MXCN + id_or_actual) = dis_actual;
		}
		if (!*(nos_registrados + id_or_actual)) {
			nuevo_no = gna(ctx, 1);
			nuevo_no->id = id_or_actual;
			if (ctx->ini) {
				ctx->final->siguiente = nuevo_no;
			} else {
				ctx->ini = nuevo_no;
			}
			ctx->final = nuevo_no;
			*(nos_registrados + id_or_actual) = verdadero;
			contador_nos++;
		}
		if (!*(nos_registrados + id_ds_actual)) {
			nuevo_no = gna(ctx, 1);
			nuevo_no->id = id_ds_actual;
			ctx->final->siguiente = nuevo_no;
			ctx->final = nuevo_no;
			*(nos_registrados + id_ds_actual) = verdadero;
			contador_nos++;
		}
	}
	return contador_nos;
}

no *gna(gc *ctx, int localidades_solicitadas) {
	no *ini_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		ini_localidades_allocadas = ctx->nos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return ini_localidades_allocadas;
}

int caca_apuntador_valido(void *p) {
	return (p != NULL);
}

void arbol_avl_init(ac *ctx, td *ids,
td *datos, int num_datos, nab **arreglo_referencias_nos) {
	int i = 0;
	td dato_actual = 0;
	nab *no_actual = NULL;

	memset((void *) ctx, 0, sizeof(ac));
	memset((void *) ctx->nos_disponibles, 0, sizeof(ctx->nos_disponibles));

	for (i = 0; i < num_datos; i++) {
		if (ids && *(ids + i) == (td)ARBOL_AVL_id_INVALIDO) {
			continue;
		}

		if (!ctx->rz) {
			ctx->rz = aba(ctx, 1);
			if (ids) {
				ctx->rz->id = *(ids + i);
			} else {
				ctx->rz->id = 1;
			}
			if (arreglo_referencias_nos) {
				if (ids) {
					*(arreglo_referencias_nos + *(ids + i)) = ctx->rz;

				} else {
					*(arreglo_referencias_nos + 1) = ctx->rz;
				}
			}
			ctx->rz->vl = *(datos + i);
			continue;
		}

		dato_actual = *(datos + i);
		no_actual = aba(ctx, 1);

		no_actual->vl = dato_actual;
		if (ids) {
			no_actual->id = *(ids + i);
		} else {
			no_actual->id = i + 1;
		}

		arbol_avl_insertar(&ctx->rz, no_actual, ctx->no_ids_repetidos);
		if (arreglo_referencias_nos) {
			if (ids) {
				*(arreglo_referencias_nos + *(ids + i)) = no_actual;

			} else {
				*(arreglo_referencias_nos + i + 1) = no_actual;
			}
		}
	}
}

void arbol_avl_insertar(nab **rz, nab *no_a_insertar, bo no_ids_repetidos) {
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
					no_ids_repetidos);
		} else {
			rz_int->hijo_der = no_a_insertar;
			AAAP(no_a_insertar, rz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_MAYOR:
		if (rz_int->hijo_izq) {
			arbol_avl_insertar(&rz_int->hijo_izq, no_a_insertar,
					no_ids_repetidos);
		} else {
			rz_int->hijo_izq = no_a_insertar;
			AAAP(no_a_insertar, rz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_IGUAL:
		if (no_ids_repetidos) {
			perror("NO mames, una llave repetida, ahhhhh !");
			exit(1);
		} else {
			if (rz_int->hijo_der) {
				arbol_avl_insertar(&rz_int->hijo_der, no_a_insertar,
						no_ids_repetidos);
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

static int aacn(nab *no1, nab *no2) {
	if (no1->vl < no2->vl) {
		return CACA_COMPARACION_IZQ_MENOR;
	} else {
		if (no1->vl > no2->vl) {
			return CACA_COMPARACION_IZQ_MAYOR;
		} else {
			return CACA_COMPARACION_IZQ_IGUAL;
		}
	}
}

static int caca_int_max(int a, int b) {
	return (a > b) ? a : b;
}

static int aada(nab *no, int tolerancia, bo considerar_balanceado_cargado_der) {
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

static void abri(nab **no) {
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

static void abrd(nab **no) {
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

static nab *aba(ac *ctx, int localidades_solicitadas) {
	nab *ini_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		ini_localidades_allocadas = ctx->nos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return ini_localidades_allocadas;
}

static nab *arbol_binario_get_no_minimo_vl(nab *rz) {
	nab *no_actual = NULL;
	no_actual = rz;
	while (no_actual->hijo_izq) {
		no_actual = no_actual->hijo_izq;
	}
	return no_actual;
}

void arbol_binario_borrar_no(nab **rz,
td vl_a_borrar) {
	nab *rz_int = NULL;
	nab *no_min = NULL;

	rz_int = *rz;

	if (!rz_int) {
		return;
	}
	if (rz_int->vl > vl_a_borrar) {
		arbol_binario_borrar_no(&rz_int->hijo_izq, vl_a_borrar);
	} else {
		if (rz_int->vl < vl_a_borrar) {
			arbol_binario_borrar_no(&rz_int->hijo_der, vl_a_borrar);
		} else {
			if (!rz_int->hijo_izq) {
				*rz = rz_int->hijo_der;
			} else {
				if (!rz_int->hijo_der) {
					*rz = rz_int->hijo_izq;
				} else {
					no_min = arbol_binario_get_no_minimo_vl(rz_int->hijo_der);
					rz_int->vl = no_min->vl;
					arbol_binario_borrar_no(&rz_int->hijo_der, rz_int->vl);
				}
			}
		}
	}

}

void arbol_avl_borrar(nab **rz, td vl_a_borrar) {

	nab *rz_int = NULL;
	nab *no_min = NULL;

	rz_int = *rz;

	if (!rz_int) {
		return;
	}
	if (rz_int->vl > vl_a_borrar) {
		arbol_avl_borrar(&rz_int->hijo_izq, vl_a_borrar);
	} else {
		if (rz_int->vl < vl_a_borrar) {
			arbol_avl_borrar(&rz_int->hijo_der, vl_a_borrar);
		} else {
			if (!rz_int->hijo_izq) {
				*rz = rz_int->hijo_der;
			} else {
				if (!rz_int->hijo_der) {
					*rz = rz_int->hijo_izq;
				} else {
					no_min = arbol_binario_get_no_minimo_vl(rz_int->hijo_der);
					rz_int->vl = no_min->vl;
					arbol_avl_borrar(&rz_int->hijo_der, rz_int->vl);

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
				no_a_borrar->vl < (no_a_borrar_padre)->vl ?
						&no_a_borrar_padre->hijo_izq :
				no_a_borrar->vl > (no_a_borrar_padre)->vl ?
						&no_a_borrar_padre->hijo_der :
				no_a_borrar->id == AAOI(no_a_borrar_padre->hijo_izq) ?
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
			no_min = arbol_binario_get_no_minimo_vl(no_a_borrar->hijo_der);

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

void cola_prioridad_modificar_vl_no(cc *cpctx,
td id, td nuevo_vl) {
	nab *referencia_directa = NULL;
	nab *nuevo_no = NULL;
	nab **referencias_directas = NULL;
	nab **rz = NULL;

	referencias_directas = cpctx->referencias_directas_por_id;
	rz = &cpctx->actx->rz;

	referencia_directa = *(referencias_directas + id);

	arbol_avl_borrar_referencia_directa(&cpctx->actx->rz, referencia_directa);

	nuevo_no = aba(cpctx->actx, 1);
	memset(nuevo_no, 0, sizeof(nab));
	nuevo_no->id = id;
	nuevo_no->vl = nuevo_vl;

	arbol_avl_insertar(rz, nuevo_no, falso);

	*(referencias_directas + id) = nuevo_no;
}

void dijkstra_relaxar_no(gc *gctx, cc *cpctx,
td ind_no_or, td ind_no_ds,
td *antecesores) {
	td dist_or_dest = 0;

	td *matrix_diss = NULL;

	nab *dis_min_or = NULL;
	nab *dis_min_ds = NULL;
	nab **diss_minimas = NULL;

	matrix_diss = (td *) gctx->matrix_diss;
	dist_or_dest = *(matrix_diss + ind_no_or * MXCN + ind_no_ds);

	diss_minimas = cpctx->referencias_directas_por_id;

	dis_min_or = *(diss_minimas + ind_no_or);
	dis_min_ds = *(diss_minimas + ind_no_ds);

	if (dis_min_ds->vl > dis_min_or->vl + dist_or_dest) {
		cola_prioridad_modificar_vl_no(cpctx, ind_no_ds,
				dis_min_or->vl + dist_or_dest);
		if (antecesores) {
			*(antecesores + ind_no_ds) = ind_no_or;
		}
	}
}

void dijkstra_main(void *matrix_diss, int num_filas,
td ind_no_or, td ind_no_ds, gc *gctx,
td *diss_minimas,
td *antecesores) {

	int contador = 0;

	td id_or_actual = 0;
	td id_ds_actual = 0;
	td dis_actual = 0;
	td max_id = 0;
	td *matrix_diss_int = NULL;

	gc gctx_mem;
	gc *gctx_int;
	cc cpctx;

	no *no_or_actual = NULL;
	nc *no_mas_cercas = NULL;

	bo nos_diss_minimas_calculadas[MXN] = { falso };
	nc diss_minimas_nos[MXN];

	int i, j;

	caca_inutiliza_no_cola_prioridad(diss_minimas_nos, MXN);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_gf(matrix_diss, num_filas, gctx_int, falso, verdadero);
	}
	matrix_diss_int = (td *) gctx_int->matrix_diss;

	no_or_actual = gctx_int->ini;

	while (no_or_actual) {
		if (no_or_actual->id == ind_no_or) {
			(diss_minimas_nos + no_or_actual->id)->vl = 0;
		} else {
			(diss_minimas_nos + no_or_actual->id)->vl =
			MAX_vl;
		}
		if (no_or_actual->id > max_id) {
			max_id = no_or_actual->id;
			if (max_id > MXN) {
				perror(
						"El id maximo supera el maximo de nos permitidos, a la mierda todo");
				abort();
			}
		}
		(diss_minimas_nos + no_or_actual->id)->id = no_or_actual->id;
		GAN(no_or_actual, GF_PRINCIPAL, falso);
		contador++;
	}

	cola_prioridad_init(&cpctx, diss_minimas_nos, NULL, NULL, max_id + 1, NULL,
			NULL);

	contador = 0;
	while (!cola_prioridad_es_vacia(&cpctx)) {
		no_mas_cercas = cola_prioridad_pop(&cpctx);
		nos_diss_minimas_calculadas[no_mas_cercas->id] = verdadero;

		id_or_actual = no_mas_cercas->id;

		for (j = 0; j < MXCN; j++) {
			dis_actual = (td) *(matrix_diss_int + id_or_actual * MXFN + j);
			id_ds_actual = j;
			if (dis_actual != (td)GF_vl_INVALIDO
					&& !(*(nos_diss_minimas_calculadas + id_ds_actual))) {
				dijkstra_relaxar_no(gctx_int, &cpctx, id_or_actual,
						id_ds_actual, antecesores);
			}
		}

		contador++;
	}
	*(antecesores + ind_no_or) = 0;
	for (i = 0; (td)i < max_id + 1; i++) {
		*(diss_minimas + i) =
				(td)i == ind_no_or ? 0 :
				caca_apuntador_valido(
						(*(cpctx.referencias_directas_por_id + i))) ?
						(*(cpctx.referencias_directas_por_id + i))->vl :
						CP_vl_INVALIDO;
	}

}

void cola_prioridad_init(cc *ctx, nc *nos, td *vles, td *ids, int num_nos,
		ac *actx, nab **referencias_directas) {
	td ids_int[MXN] = { ARBOL_AVL_id_INVALIDO };
	td datos[MXN] = { ARBOL_AVL_id_INVALIDO };
	int i;

	memset(ctx, 0, sizeof(cc));
	memset(ctx->referencias_directas_por_id_mem, 0,
			sizeof(ctx->referencias_directas_por_id_mem));
	memset(ids_int, CP_vl_INVALIDO, sizeof(ids_int));
	memset(datos, CP_vl_INVALIDO, sizeof(datos));

	if (actx) {
		if (!referencias_directas) {
			perror("se paso un contexto de arbol sin referencias directas");
			exit(1);
		}
		ctx->actx = actx;
		ctx->referencias_directas_por_id = referencias_directas;
	} else {
		for (i = 0; i < num_nos; i++) {
			if (nos) {
				if ((nos + i)->id == CP_vl_INVALIDO) {
					continue;
				}
				*(ids_int + i) = (nos + i)->id;
				*(datos + i) = (nos + i)->vl;
			} else {
				if (!vles) {
					perror("no se proporcionaron nos ni vles");
					exit(1);
				}
				if (ids) {
					*(ids_int + i) = *(ids + i);
				} else {
					*(ids_int + i) = i + 1;
				}
				*(datos + i) = *(vles + i);
			}
		}
		ctx->actx = &ctx->actx_mem;
		ctx->referencias_directas_por_id = ctx->referencias_directas_por_id_mem;

		arbol_avl_init(ctx->actx, ids_int, datos, num_nos,
				ctx->referencias_directas_por_id);
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

void gf_copia_profunda(const gc *ctx_or, gc *ctx_ds,
td *ids_a_ignorar, int tam_ids_a_ignorar) {
	td id_no_or_actual = 0;

	td *matrix_or = NULL;
	td *matrix_ds = NULL;

	no *no_or_principal_actual = NULL;
	no *no_ds_principal_actual = NULL;
	no *no_ds_principal_previo = NULL;
	int i, j;

	matrix_or = (td *) ctx_or->matrix_diss;
	matrix_ds = (td *) ctx_ds->matrix_diss;
	memcpy(matrix_ds, matrix_or, sizeof(ctx_or->matrix_diss));

	no_or_principal_actual = ctx_or->ini;
	while (no_or_principal_actual) {
		id_no_or_actual = no_or_principal_actual->id;
		if (ids_a_ignorar
				&& caca_arreglo_contiene(ids_a_ignorar, tam_ids_a_ignorar,
						id_no_or_actual)) {

			for (i = 0; i < MXFN; i++) {
				*(matrix_ds + i * MXCN + id_no_or_actual) =
				GF_vl_INVALIDO;
			}
			for (j = 0; j < MXCN; j++) {
				*(matrix_ds + id_no_or_actual * MXCN + j) =
				GF_vl_INVALIDO;
			}
			GAN(no_or_principal_actual, 0, 0);
			continue;
		}

		no_ds_principal_actual = gna(ctx_ds, 1);
		memset(no_ds_principal_actual, 0, sizeof(no));
		gf_copia_no(no_or_principal_actual, no_ds_principal_actual);
		if (no_ds_principal_previo) {
			no_ds_principal_previo->siguiente = no_ds_principal_actual;
			no_ds_principal_actual->anterior = no_ds_principal_previo;
		} else {
			ctx_ds->ini = no_ds_principal_actual;
		}
		no_ds_principal_previo = no_ds_principal_actual;

		GAN(no_or_principal_actual, 0, 0);
	}

}

#define GF_COPIA_PROPIEDAD(propiedad) no_ds->propiedad = no_or->propiedad
static void gf_copia_no(const no *no_or, no *no_ds) {
	GF_COPIA_PROPIEDAD(dis);
	GF_COPIA_PROPIEDAD(id);
	GF_COPIA_PROPIEDAD(vl);
}

static bo caca_arreglo_contiene(td *arreglo, int tam_arreglo,
td vl_buscado) {
	int i;
	for (i = 0; i < tam_arreglo; i++) {
		if (*(arreglo + i) == vl_buscado) {
			return verdadero;
		}
	}
	return falso;
}

static void caca_inutiliza_no_cola_prioridad(nc *nos, int num_nos) {
	int i;
	for (i = 0; i < num_nos; i++) {
		CPAI((nos + i), CP_vl_INVALIDO);
		CPAV((nos + i), CP_vl_INVALIDO);
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

int escape_cabron_determina_nos_viables(void *matrix_aristas, int num_filas,
		gc *gf_viable_ctx, td posicion_incomoda,
		td posicion_inicial,
		td *dis_posicion_incomoda_a_inicial) {

	int num_nos = 0;
	int contador_nos_ruta_maldita = 0;
	int contador_nos_recorridos = 0;
	td ancestro_actual = 0;
	gc gf_inicial_ctx;

	td *diss_minimas = NULL, *antecesores = NULL;
	td *ruta_maldita;

	num_nos = init_gf(matrix_aristas, num_filas, &gf_inicial_ctx, falso,
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
	memset(antecesores, DIJKSTRA_vl_INVALIDO, (num_nos + 1) * sizeof(td));
	ruta_maldita = calloc(num_nos + 1, sizeof(td));
	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(-1);
	}

	dijkstra_main(NULL, 0, posicion_incomoda, posicion_inicial, &gf_inicial_ctx,
			diss_minimas, antecesores);

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

	gf_copia_profunda(&gf_inicial_ctx, gf_viable_ctx, ruta_maldita + 1,
			contador_nos_ruta_maldita - 1);

	if (dis_posicion_incomoda_a_inicial) {
		*dis_posicion_incomoda_a_inicial = *(diss_minimas + posicion_inicial);
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
	gc *gf_viable_ctx = NULL;
	cc *cola_salidas_carretera = NULL;
	td *diss_minimas = NULL;
	td *antecesores = NULL;
	td *diss_salidas_carretera = NULL;
	td *salidas_carretera_viables = NULL;
	int i;

	gf_viable_ctx = calloc(1, sizeof(gc));
	if (!gf_viable_ctx) {
		perror("no se consigio memoria para gf viable");
		abort();
	}

	num_nos_viables = escape_cabron_determina_nos_viables(matrix_aristas,
			num_filas, gf_viable_ctx, posicion_polis, posicion_ratas,
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
	memset(antecesores, DIJKSTRA_vl_INVALIDO,
			(num_nos_viables + 1) * sizeof(td));
	memset(diss_minimas, DIJKSTRA_vl_INVALIDO,
			(num_nos_viables + 1) * sizeof(td));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, gf_viable_ctx,
			diss_minimas, antecesores);

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_actual = *(salidas_carretera + i);
		if ((dis_salida_carretera_actual = *(diss_minimas
				+ salida_carretera_actual)) == MAX_vl) {
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

	dis_recorrida_polis = no_salida_mas_cercana->id + dis_polis_a_ratas;

	tiempo_polis = (float) dis_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) no_salida_mas_cercana->id / tiempo_polis;

	return maxima_velocidad;
}

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	td num_salidas = 0;
	td posicion_ratas = 0, posicion_polis = 0;

	td datos_escape_mem[ESCAPE_CABRON_MAX_FILAS_INPUT][ESCAPE_CABRON_MAX_COLS_INPUT] =
			{ { 0 } };

	td *datos_escape = (td *) datos_escape_mem;
	td *ini_aristas = NULL;
	td *salidas = NULL;

	lee_matrix_long_stdin((td *) datos_escape_mem, &num_aristas, NULL,
	ESCAPE_CABRON_MAX_FILAS_INPUT, ESCAPE_CABRON_MAX_COLS_INPUT);

	if (!num_aristas) {
		perror("vale verga, no c leyo nada");
		abort();
	}


	num_aristas = *(datos_escape + 1);
	num_salidas = *(datos_escape + 2);

	ini_aristas = datos_escape + ESCAPE_CABRON_MAX_COLS_INPUT;
	salidas = ini_aristas + num_aristas * ESCAPE_CABRON_MAX_COLS_INPUT;
	posicion_ratas = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT);
	posicion_polis = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT + 1);

	caca_realinea_array(ini_aristas, num_aristas,
	ESCAPE_CABRON_MAX_COLS_INPUT, 3);

	maxima_velocidad = escape_cabron_encuentra_escape(ini_aristas, num_aristas,
			posicion_polis, posicion_ratas, salidas, num_salidas);

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
