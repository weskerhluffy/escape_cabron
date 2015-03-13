#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define td unsigned long

#define MN 101
#define TML 1024
#define MFN 1000
#define MCN 1000
#define cc_COMPARACION_IZQ_MENOR -1
#define cc_COMPARACION_IZQ_IGUAL 0
#define cc_COMPARACION_IZQ_MAYOR 1
#define MTC 200
#define AAII -1
#define AAVI -1
#define CPVI -1
#define DVI -1
#define GVI -1

#define MV (td) (2<<28)

#define gf_no_ORIGEN 0
#define gf_no_ds 1
#define gf_di_ENTRE_noS 2

#define CAGADA printf("mierda"), exit(0);

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bo;

#define GAN(no_apuntador,criterio_busqueda,discriminar_principal) \
		no_apuntador = (no_apuntador)->sg;

#define gf_COPIA_no_DATOS(no_origen,no_ds) \
		no_ds->vl=no_ds->vl; \
		no_ds->di=no_ds->di; \
		no_ds->id=no_ds->id;

#define AAAA(no) \
	(no)->altura = ((no)->hijo_izq || (no)->hijo_der)? \
			cc_int_max(AAGA((no)->hijo_izq), AAGA((no)->hijo_der)) + 1: \
			0;

#define AAGA(no) \
	((no)?(no)->altura:0)

#define AAGV(no) \
	((no)?(no)->vl:AAVI)

#define ARBOL_BINARIO_acIZAR_PADRE(no,nuevo_padre) \
	((no)?(no)->padre=(nuevo_padre):((void)0))

#define aa_GET_PADRE(no) \
	((no)?(no)->padre:NULL)

#define aa_GET_id(no) \
	((no)?(no)->id:AAII)

#define ARBOL_BINARIO_acIZAR_HIJO_IZQ(no,nuevo_hijo) \
	((no)?(no)->hijo_izq=(nuevo_hijo):((void)0))

#define ARBOL_BINARIO_acIZAR_HIJO_DER(no,nuevo_hijo) \
	((no)?(no)->hijo_der=(nuevo_hijo):((void)0))

#define cp_ASIGNA_id(no,nuevo_id) \
	(no)->id=nuevo_id

#define cp_ASIGNA_vl(no,nuevo_vl) \
	(no)->id=nuevo_vl

typedef struct no {
	td vl;
	td id;
	td di;
	struct no *sg;
	struct no *an;
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
	no *inicio;
	no *final;
	no nos_disponibles[MN];
	td matrix_dis[MCN][MFN];
} gc;

typedef struct arbol_binario_contexto {
	bo no_ids_repetidos;
	int localidades_usadas;
	nab *rz;
	nab nos_disponibles[MN];
} abc;

typedef struct cp_contexto {
	abc actx_mem;
	abc *actx;
	nab *rdp_id_mem[MN];
	nab **rdp_id;
} cpc;

typedef nab ncp;

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int init_gf(void *matrix, int num_filas, gc *ctx, bo usar_hashes,
		bo relaciones_bidireccionales);

no *gf_no_alloc(gc *ctx, int localidades_solicitadas);

int cav(void *p);

bo from_stack(void *ptr);

void aa_init(abc *ctx, td *ids, td *datos, int num_datos,
		nab **arreglo_referencias_nos);

#define aa_ALTURA_CARGADA_IZQ -1
#define aa_ALTURA_CARGADA_DER 1
#define aa_ALTURA_BALANCEADA 0

nab *abna(abc *ctx, int localidades_solicitadas);

void aain(nab **rz, nab *no_a_insertar, bo no_ids_repetidos);

int aacn(nab *no1, nab *no2);

int cc_int_max(int a, int b);

void abri(nab **no);
void abrd(nab **no);

void arbol_binario_borrar_no(nab **rz, td vl_a_borrar);

void aa_borrar(nab **rz, td vl_a_borrar);

void aabrd(nab **rz, nab *no_a_borrar, nab *tope);

void cp_modificar_vl_no(cpc *cpctx, td id, td nuevo_vl);

void dijkstra_relaxar_no(gc *gctx, cpc *cpctx, td ind_no_origen, td ind_no_ds,
		td *antecesores);

void cp_init(cpc *ctx, ncp *nos, td *vles, td *ids, int num_nos, abc *actx,
		nab **referencias_directas);

ncp *cp_pop(cpc *ctx);

bo cp_es_vacia(cpc *ctx);

void dijkstra_main(void *matrix_dis, int num_filas, td ind_no_origen,
		td ind_no_ds, gc *gctx, td *dis_minimas, td *antecesores);

void gf_copia_no(const no *no_origen, no *no_ds);

bo cc_arreglo_contiene(td *arreglo, int tam_arreglo, td vl_buscado);

void gf_copia_profunda(const gc *ctx_origen, gc *ctx_ds, td *ids_a_ignorar,
		int tam_ids_a_ignorar);

void cc_inutiliza_no_cp(ncp *nos, int num_nos);

void cc_realinea_array(td *arreglo, int num_filas, int alineacion_ac,
		int alineacion_nueva);

int aa_diferencia_alturas_subarboles(nab *no, int tolerancia,
		bo considerar_balanceado_cargado_der);

int lee_matrix_long_stdin(td *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int id_filas = 0;
	int id_columnas = 0;
	long numero = 0;
	char *sg_cadena_numero = NULL;
	char *cadena_numero_ac = NULL;
	char linea[TML];

	while (fgets(linea, TML, stdin)) {
		id_columnas = 0;
		cadena_numero_ac = linea;
		for (sg_cadena_numero = linea;; sg_cadena_numero = cadena_numero_ac) {
			numero = strtol(sg_cadena_numero, &cadena_numero_ac, 10);
			if (cadena_numero_ac == sg_cadena_numero) {
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
	td id_origen_ac = 0;
	td id_ds_ac = 0;
	td di_ac = 0;
	td *matrix_int = NULL;
	td *matrix_dis = NULL;
	no *nuevo_no = NULL;
	td nos_registrados[MN] = { falso };
	int i;

	memset(ctx, 0, sizeof(gc));

	matrix_int = matrix;
	matrix_dis = (td *) ctx->matrix_dis;
	memset(matrix_dis, GVI, sizeof(ctx->matrix_dis));
	for (i = 0; i < num_filas; i++) {
		id_origen_ac = *(matrix_int + i * 3 + gf_no_ORIGEN);
		id_ds_ac = *(matrix_int + i * 3 + gf_no_ds);
		di_ac = *(matrix_int + i * 3 + gf_di_ENTRE_noS);

		*(matrix_dis + id_origen_ac * MCN + id_ds_ac) = di_ac;

		if (relaciones_bidireccionales) {
			*(matrix_dis + id_ds_ac * MCN + id_origen_ac) = di_ac;
		}
		if (!*(nos_registrados + id_origen_ac)) {
			nuevo_no = gf_no_alloc(ctx, 1);
			nuevo_no->id = id_origen_ac;
			if (ctx->inicio) {
				ctx->final->sg = nuevo_no;
			} else {
				ctx->inicio = nuevo_no;
			}
			ctx->final = nuevo_no;
			*(nos_registrados + id_origen_ac) = verdadero;
			contador_nos++;
		}
		if (!*(nos_registrados + id_ds_ac)) {
			nuevo_no = gf_no_alloc(ctx, 1);
			nuevo_no->id = id_ds_ac;
			ctx->final->sg = nuevo_no;
			ctx->final = nuevo_no;
			*(nos_registrados + id_ds_ac) = verdadero;
			contador_nos++;
		}
	}
	return contador_nos;
}

no *gf_no_alloc(gc *ctx, int localidades_solicitadas) {
	no *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

int cav(void *p) {
	return (p != NULL );
}

void aa_init(abc *ctx, td *ids, td *datos, int num_datos,
		nab **arreglo_referencias_nos) {
	int i = 0;
	td dato_ac = 0;
	nab *no_ac = NULL;

	memset((void * ) ctx, 0, sizeof(abc));
	memset((void * ) ctx->nos_disponibles, 0, sizeof(ctx->nos_disponibles));

	for (i = 0; i < num_datos; i++) {
		if (ids && *(ids + i) == AAII) {
			continue;
		}

		if (!ctx->rz) {
			ctx->rz = abna(ctx, 1);
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

		dato_ac = *(datos + i);
		no_ac = abna(ctx, 1);

		no_ac->vl = dato_ac;
		if (ids) {
			no_ac->id = *(ids + i);
		} else {
			no_ac->id = i + 1;
		}

		aain(&ctx->rz, no_ac, ctx->no_ids_repetidos);
		if (arreglo_referencias_nos) {
			if (ids) {
				*(arreglo_referencias_nos + *(ids + i)) = no_ac;

			} else {
				*(arreglo_referencias_nos + i + 1) = no_ac;
			}
		}
	}
}

void aain(nab **rz, nab *no_a_insertar, bo no_ids_repetidos) {
	nab *rz_int = NULL;

	rz_int = *rz;

	if (!rz_int) {
		*rz = no_a_insertar;

		return;
	}

	switch (aacn(rz_int, no_a_insertar)) {
	case cc_COMPARACION_IZQ_MENOR:
		if (rz_int->hijo_der) {
			aain(&rz_int->hijo_der, no_a_insertar, no_ids_repetidos);
		} else {
			rz_int->hijo_der = no_a_insertar;
			ARBOL_BINARIO_acIZAR_PADRE(no_a_insertar, rz_int);
		}
		break;
	case cc_COMPARACION_IZQ_MAYOR:
		if (rz_int->hijo_izq) {
			aain(&rz_int->hijo_izq, no_a_insertar, no_ids_repetidos);
		} else {
			rz_int->hijo_izq = no_a_insertar;
			ARBOL_BINARIO_acIZAR_PADRE(no_a_insertar, rz_int);
		}
		break;
	case cc_COMPARACION_IZQ_IGUAL:
		if (no_ids_repetidos) {
			perror("NO mames, una llave repetida, ahhhhh !");
			exit(1);
		} else {
			if (rz_int->hijo_der) {
				aain(&rz_int->hijo_der, no_a_insertar, no_ids_repetidos);
			} else {
				rz_int->hijo_der = no_a_insertar;
				ARBOL_BINARIO_acIZAR_PADRE(no_a_insertar, rz_int);
			}
		}
		break;
	default:
		perror("NO mames, resultado increible en aa_insertar!");
		exit(1);
		break;
	}

	AAAA(rz_int);

	switch (aa_diferencia_alturas_subarboles(rz_int, 1, verdadero)) {
	case aa_ALTURA_CARGADA_IZQ:
		if (AAGV(
				rz_int->hijo_izq) < AAGV(no_a_insertar)) {
			abri(&rz_int->hijo_izq);
		}
		abrd(rz);
		break;
	case aa_ALTURA_CARGADA_DER:
		if (AAGV(
				rz_int->hijo_der) > AAGV(no_a_insertar)) {
			abrd(&rz_int->hijo_der);
		}
		abri(rz);
		break;
	case aa_ALTURA_BALANCEADA:
		break;
	default:
		perror("error en altura indeterminada, verga");
		exit(1);
		break;
	}

}

int aacn(nab *no1, nab *no2) {
	if (no1->vl < no2->vl) {
		return cc_COMPARACION_IZQ_MENOR;
	} else {
		if (no1->vl > no2->vl) {
			return cc_COMPARACION_IZQ_MAYOR;
		} else {
			return cc_COMPARACION_IZQ_IGUAL;
		}
	}
}

int cc_int_max(int a, int b) {
	return (a > b) ? a : b;
}

void abri(nab **no) {
	nab *no_int = NULL;
	nab *hijo_der = NULL;
	nab *hijo_der_subarbol_izq = NULL;

	no_int = *no;

	hijo_der = no_int->hijo_der;

	hijo_der_subarbol_izq = hijo_der->hijo_izq;

	no_int->hijo_der = hijo_der_subarbol_izq;
	hijo_der->hijo_izq = no_int;

	ARBOL_BINARIO_acIZAR_PADRE(hijo_der, aa_GET_PADRE(no_int));
	ARBOL_BINARIO_acIZAR_PADRE(hijo_der_subarbol_izq, no_int);
	ARBOL_BINARIO_acIZAR_PADRE(no_int, hijo_der);

	AAAA(no_int);
	AAAA(hijo_der);

	*no = hijo_der;

}

nab *abna(abc *ctx, int localidades_solicitadas) {
	nab *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

nab *arbol_binario_get_no_minimo_vl(nab *rz) {
	nab *no_ac = NULL;
	no_ac = rz;
	while (no_ac->hijo_izq) {
		no_ac = no_ac->hijo_izq;
	}
	return no_ac;
}

void arbol_binario_borrar_no(nab **rz, td vl_a_borrar) {
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

void aa_borrar(nab **rz, td vl_a_borrar) {

	nab *rz_int = NULL;
	nab *no_min = NULL;

	rz_int = *rz;

	if (!rz_int) {
		return;
	}
	if (rz_int->vl > vl_a_borrar) {
		aa_borrar(&rz_int->hijo_izq, vl_a_borrar);
	} else {
		if (rz_int->vl < vl_a_borrar) {
			aa_borrar(&rz_int->hijo_der, vl_a_borrar);
		} else {
			if (!rz_int->hijo_izq) {
				*rz = rz_int->hijo_der;
			} else {
				if (!rz_int->hijo_der) {
					*rz = rz_int->hijo_izq;
				} else {
					no_min = arbol_binario_get_no_minimo_vl(rz_int->hijo_der);
					rz_int->vl = no_min->vl;
					aa_borrar(&rz_int->hijo_der, rz_int->vl);

					ARBOL_BINARIO_acIZAR_HIJO_IZQ(no_min, rz_int->hijo_izq);
					ARBOL_BINARIO_acIZAR_HIJO_DER(no_min, rz_int->hijo_der);
					ARBOL_BINARIO_acIZAR_PADRE(no_min, rz_int->padre);
					no_min->altura = AAGA(rz_int);
					ARBOL_BINARIO_acIZAR_PADRE(rz_int->hijo_izq, no_min);
					ARBOL_BINARIO_acIZAR_PADRE(rz_int->hijo_der, no_min);
					*rz = no_min;
				}
			}
		}
	}

	if (!*rz) {
		return;
	}

	AAAA(rz_int);

	switch (aa_diferencia_alturas_subarboles(rz_int, 1, verdadero)) {
	case aa_ALTURA_CARGADA_IZQ:
		if (aa_diferencia_alturas_subarboles(rz_int->hijo_izq, 0,
				falso) == aa_ALTURA_CARGADA_DER) {
			abri(&rz_int->hijo_izq);
		}
		abrd(rz);
		break;
	case aa_ALTURA_CARGADA_DER:
		if (aa_diferencia_alturas_subarboles(rz_int->hijo_der, 0,
				verdadero) == aa_ALTURA_CARGADA_IZQ) {
			abrd(&rz_int->hijo_der);
		}
		abri(rz);
		break;
	case aa_ALTURA_BALANCEADA:
		break;
	default:
		break;
	}

}

void aabrd(nab **rz, nab *no_a_borrar, nab *tope) {

	nab *ancestro_ac = NULL;
	nab *ancestro_ac_tmp = NULL;
	nab *no_a_borrar_padre = NULL;
	nab *no_min = NULL;

	nab **ancestro_ac_apuntador = NULL;
	nab **no_a_borrar_ref = NULL;

	if (!no_a_borrar) {
		abort();
	}

	if (!(no_a_borrar_padre = aa_GET_PADRE(no_a_borrar))) {
		no_a_borrar_padre = NULL;
		no_a_borrar_ref = rz;

	} else {

		no_a_borrar_ref =
				no_a_borrar->vl < (no_a_borrar_padre)->vl ?
						&no_a_borrar_padre->hijo_izq :
				no_a_borrar->vl > (no_a_borrar_padre)->vl ?
						&no_a_borrar_padre->hijo_der :
				no_a_borrar->id == aa_GET_id(no_a_borrar_padre->hijo_izq) ?
						&no_a_borrar_padre->hijo_izq :
						&no_a_borrar_padre->hijo_der;

	}

	ancestro_ac = no_a_borrar->padre;
	ancestro_ac_apuntador = &no_a_borrar->padre;

	if (!no_a_borrar->hijo_izq) {

		ARBOL_BINARIO_acIZAR_PADRE(no_a_borrar->hijo_der, ancestro_ac);
		*no_a_borrar_ref = no_a_borrar->hijo_der;
	} else {
		if (!no_a_borrar->hijo_der) {

			ARBOL_BINARIO_acIZAR_PADRE(no_a_borrar->hijo_izq, ancestro_ac);
			*no_a_borrar_ref = no_a_borrar->hijo_izq;
		} else {
			no_min = arbol_binario_get_no_minimo_vl(no_a_borrar->hijo_der);

			aabrd(rz, no_min, no_a_borrar);
			ARBOL_BINARIO_acIZAR_HIJO_IZQ(no_min, no_a_borrar->hijo_izq);
			ARBOL_BINARIO_acIZAR_HIJO_DER(no_min, no_a_borrar->hijo_der);
			ARBOL_BINARIO_acIZAR_PADRE(no_min, no_a_borrar->padre);
			no_min->altura = AAGA(no_a_borrar);

			ARBOL_BINARIO_acIZAR_PADRE(no_a_borrar->hijo_izq, no_min);
			ARBOL_BINARIO_acIZAR_PADRE(no_a_borrar->hijo_der, no_min);

			*no_a_borrar_ref = no_min;
			ancestro_ac = no_min;
		}
	}

	do {
		if (!aa_GET_PADRE(no_a_borrar)) {

			break;
		}

		if (tope && ancestro_ac == tope) {

			return;
		}
		ancestro_ac_tmp = ancestro_ac->padre;

		if (aa_GET_PADRE(ancestro_ac)) {
			if (AAGV(
					ancestro_ac) <= AAGV(ancestro_ac->padre)) {
				ancestro_ac_apuntador = &ancestro_ac->padre->hijo_izq;

			} else {
				ancestro_ac_apuntador = &ancestro_ac->padre->hijo_der;

			}
		} else {

			ancestro_ac_apuntador = rz;
		};

		AAAA(ancestro_ac);

		switch (aa_diferencia_alturas_subarboles(ancestro_ac, 1, verdadero)) {
		case aa_ALTURA_CARGADA_IZQ:

			if (aa_diferencia_alturas_subarboles(ancestro_ac->hijo_izq, 0,
					falso) == aa_ALTURA_CARGADA_DER) {

				abri(&ancestro_ac->hijo_izq);
			}
			abrd(ancestro_ac_apuntador);
			break;
		case aa_ALTURA_CARGADA_DER:

			if (aa_diferencia_alturas_subarboles(ancestro_ac->hijo_der, 0,
					verdadero) == aa_ALTURA_CARGADA_IZQ) {

				abrd(&ancestro_ac->hijo_der);
			}
			abri(ancestro_ac_apuntador);
			break;
		case aa_ALTURA_BALANCEADA:

			break;
		default:
			break;
		}

		ancestro_ac = ancestro_ac_tmp;
	} while (ancestro_ac);

}

void cp_modificar_vl_no(cpc *cpctx, td id, td nuevo_vl) {
	nab *referencia_directa = NULL;
	nab *nuevo_no = NULL;
	nab **referencias_directas = NULL;
	nab **rz = NULL;

	referencias_directas = cpctx->rdp_id;
	rz = &cpctx->actx->rz;

	referencia_directa = *(referencias_directas + id);

	aabrd(&cpctx->actx->rz, referencia_directa, NULL );

	nuevo_no = abna(cpctx->actx, 1);
	memset(nuevo_no, 0, sizeof(nab));
	nuevo_no->id = id;
	nuevo_no->vl = nuevo_vl;

	aain(rz, nuevo_no, falso);

	*(referencias_directas + id) = nuevo_no;
}

void dijkstra_relaxar_no(gc *gctx, cpc *cpctx, td ind_no_origen, td ind_no_ds,
		td *antecesores) {
	td dist_origen_dest = 0;

	td *matrix_dis = NULL;

	nab *di_min_origen = NULL;
	nab *di_min_ds = NULL;
	nab **dis_minimas = NULL;

	matrix_dis = (td*) gctx->matrix_dis;
	dist_origen_dest = *(matrix_dis + ind_no_origen * MCN + ind_no_ds);

	dis_minimas = cpctx->rdp_id;

	di_min_origen = *(dis_minimas + ind_no_origen);
	di_min_ds = *(dis_minimas + ind_no_ds);

	if (di_min_ds->vl > di_min_origen->vl + dist_origen_dest) {

		cp_modificar_vl_no(cpctx, ind_no_ds,
				di_min_origen->vl + dist_origen_dest);
		if (antecesores) {
			*(antecesores + ind_no_ds) = ind_no_origen;
		}
	}
}
void dijkstra_main(void *matrix_dis, int num_filas, td ind_no_origen,
		td ind_no_ds, gc *gctx, td *dis_minimas, td *antecesores) {
	int i, j;
	int contador = 0;
	int num_nos = 0;

	td id_origen_ac = 0;
	td id_ds_ac = 0;
	td di_ac = 0;
	td max_id = 0;
	td *matrix_dis_int = NULL;

	gc gctx_mem;
	gc *gctx_int;
	cpc cpctx;

	no *no_origen_ac = NULL;
	ncp *no_mas_cercas = NULL;

	bo nos_dis_minimas_calculadas[MN] = { falso };
	ncp dis_minimas_nos[MN];

	cc_inutiliza_no_cp(dis_minimas_nos, MN);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_gf(matrix_dis, num_filas, gctx_int, falso, verdadero);
	}
	matrix_dis_int = (td *) gctx_int->matrix_dis;

	no_origen_ac = gctx_int->inicio;

	while (no_origen_ac) {
		if (no_origen_ac->id == ind_no_origen) {
			(dis_minimas_nos + no_origen_ac->id)->vl = 0;
		} else {
			(dis_minimas_nos + no_origen_ac->id)->vl = MV;
		}
		if (no_origen_ac->id > max_id) {
			max_id = no_origen_ac->id;
			if (max_id > MN) {
				perror(
						"El id maximo supera el maximo de nos permitidos, a la mierda todo");
				abort();
			}
		}
		(dis_minimas_nos + no_origen_ac->id)->id = no_origen_ac->id;
		GAN(no_origen_ac, gf_PRINCIPAL, falso);
		contador++;
	}
	num_nos = contador;

	cp_init(&cpctx, dis_minimas_nos, NULL, NULL, max_id + 1, NULL, NULL );

	contador = 0;
	while (!cp_es_vacia(&cpctx)) {
		no_mas_cercas = cp_pop(&cpctx);
		nos_dis_minimas_calculadas[no_mas_cercas->id] = verdadero;

		id_origen_ac = no_mas_cercas->id;

		for (j = 0; j < MCN; j++) {
			di_ac = (td) *(matrix_dis_int + id_origen_ac * MFN + j);
			id_ds_ac = j;
			if (di_ac != GVI && !(*(nos_dis_minimas_calculadas + id_ds_ac))) {
				/*
				if (j > 50) {
					CAGADA
				}
				*/

				dijkstra_relaxar_no(gctx_int, &cpctx, id_origen_ac, id_ds_ac,
						antecesores);
			}
		}

		contador++;
	}

	*(antecesores + ind_no_origen) = 0;
	for (i = 0; i < max_id + 1; i++) {
		*(dis_minimas + i) =
				i == ind_no_origen ? 0 :
				cav((*(cpctx.rdp_id + i))) ? (*(cpctx.rdp_id + i))->vl : CPVI;
	}

}

void cp_init(cpc *ctx, ncp *nos, td *vles, td *ids, int num_nos, abc *actx,
		nab **referencias_directas) {
	int i;
	td ids_int[MN] = { AAII };
	td datos[MN] = { AAII };

	memset(ctx, 0, sizeof(cpc));
	memset(ctx->rdp_id_mem, 0, sizeof(ctx->rdp_id_mem));
	memset(ids_int, CPVI, sizeof(ids_int));
	memset(datos, CPVI, sizeof(datos));

	if (actx) {
		if (!referencias_directas) {
			perror("se paso un contexto de arbol sin referencias directas");
			exit(1);
		}
		ctx->actx = actx;
		ctx->rdp_id = referencias_directas;
	} else {
		for (i = 0; i < num_nos; i++) {
			if (nos) {
				if ((nos + i)->id == CPVI) {
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
		ctx->rdp_id = ctx->rdp_id_mem;

		aa_init(ctx->actx, ids_int, datos, num_nos, ctx->rdp_id);
	}

}

ncp *cp_pop(cpc *ctx) {
	nab *no_ac = NULL;
	nab *no_an = NULL;

	no_ac = ctx->actx->rz;

	while (no_ac) {
		no_an = no_ac;
		no_ac = no_ac->hijo_izq;
	}

	aabrd(&ctx->actx->rz, no_an, NULL );

	return no_an;
}

bo cp_es_vacia(cpc *ctx) {
	return !ctx->actx->rz;
}

void gf_copia_profunda(const gc *ctx_origen, gc *ctx_ds, td *ids_a_ignorar,
		int tam_ids_a_ignorar) {
	int i, j;
	td id_no_origen_ac = 0;

	td *matrix_origen = NULL;
	td *matrix_ds = NULL;

	no *no_origen_principal_ac = NULL;
	no *no_ds_principal_ac = NULL;
	no *no_ds_principal_previo = NULL;

	matrix_origen = (td*) ctx_origen->matrix_dis;
	matrix_ds = (td *) ctx_ds->matrix_dis;
	memcpy(matrix_ds, matrix_origen, sizeof(ctx_origen->matrix_dis));

	no_origen_principal_ac = ctx_origen->inicio;

	while (no_origen_principal_ac) {
		id_no_origen_ac = no_origen_principal_ac->id;

		if (ids_a_ignorar
				&& cc_arreglo_contiene(ids_a_ignorar, tam_ids_a_ignorar,
						id_no_origen_ac)) {

			for (i = 0; i < MFN; i++) {
				*(matrix_ds + i * MCN + id_no_origen_ac) = GVI;
			}
			for (j = 0; j < MCN; j++) {
				*(matrix_ds + id_no_origen_ac * MCN + j) = GVI;
			}
			GAN(no_origen_principal_ac, 0, 0);

			continue;
		}

		no_ds_principal_ac = gf_no_alloc(ctx_ds, 1);
		memset(no_ds_principal_ac, 0, sizeof(no));
		gf_copia_no(no_origen_principal_ac, no_ds_principal_ac);
		if (no_ds_principal_previo) {
			no_ds_principal_previo->sg = no_ds_principal_ac;
			no_ds_principal_ac->an = no_ds_principal_previo;
		} else {
			ctx_ds->inicio = no_ds_principal_ac;
		}
		no_ds_principal_previo = no_ds_principal_ac;

		GAN(no_origen_principal_ac, 0, 0);
	}

}

#define gf_COPIA_PROPIEDAD(propiedad) no_ds->propiedad = no_origen->propiedad
void gf_copia_no(const no *no_origen, no *no_ds) {
	gf_COPIA_PROPIEDAD(di);
	gf_COPIA_PROPIEDAD(id);
	gf_COPIA_PROPIEDAD(vl);
}

bo cc_arreglo_contiene(td *arreglo, int tam_arreglo, td vl_buscado) {
	int i;
	for (i = 0; i < tam_arreglo; i++) {

		if (*(arreglo + i) == vl_buscado) {
			return verdadero;
		}
	}
	return falso;
}

void cc_inutiliza_no_cp(ncp *nos, int num_nos) {
	int i, j;
	for (i = 0; i < num_nos; i++) {
		cp_ASIGNA_id((nos + i), CPVI);
		cp_ASIGNA_vl((nos + i), CPVI);
	}
}

void cc_realinea_array(td *arreglo, int num_filas, int alineacion_ac,
		int alineacion_nueva) {
	int i, j;
	for (i = 0; i < num_filas; i++) {
		for (j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_ac + j);
		}

	}
}

int aa_diferencia_alturas_subarboles(nab *no, int tolerancia,
		bo considerar_balanceado_cargado_der) {
	int diferencia_alturas = 0;
	diferencia_alturas = AAGA(
			no->hijo_izq) - AAGA(no->hijo_der);
	if (considerar_balanceado_cargado_der) {
		return diferencia_alturas < 0 - tolerancia ? aa_ALTURA_CARGADA_DER :
				diferencia_alturas > tolerancia ?
						aa_ALTURA_CARGADA_IZQ : aa_ALTURA_BALANCEADA;
	} else {
		return diferencia_alturas < 0 - tolerancia ? aa_ALTURA_CARGADA_DER :
				diferencia_alturas > tolerancia ?
						aa_ALTURA_CARGADA_IZQ : aa_ALTURA_BALANCEADA;
	}
}

void abrd(nab **no) {
	nab *no_int = NULL;
	nab *hijo_izq = NULL;
	nab *hijo_izq_subarbol_der = NULL;

	no_int = *no;

	hijo_izq = no_int->hijo_izq;

	hijo_izq_subarbol_der = hijo_izq->hijo_der;

	no_int->hijo_izq = hijo_izq_subarbol_der;
	hijo_izq->hijo_der = no_int;

	ARBOL_BINARIO_acIZAR_PADRE(hijo_izq, aa_GET_PADRE(no_int));
	ARBOL_BINARIO_acIZAR_PADRE(hijo_izq_subarbol_der, no_int);
	ARBOL_BINARIO_acIZAR_PADRE(no_int, hijo_izq);

	AAAA(no_int);
	AAAA(hijo_izq);

	*no = hijo_izq;

}

bo from_stack(void *ptr) {
	return verdadero;
}

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_FILAS_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nos_viables(void *matrix_vertices, int num_filas,
		gc *gf_viable_ctx, td posicion_incomoda, td posicion_inicial,
		td *di_posicion_incomoda_a_inicial);

float escape_cabron_encuentra_escape(void *matrix_vertices, int num_filas,
		td posicion_polis, td posicion_ratas, td *salidas_carretera,
		int num_salidas_carretera);

float escape_cabron_main();

int escape_cabron_determina_nos_viables(void *matrix_aristas, int num_filas,
		gc *gf_viable_ctx, td posicion_incomoda, td posicion_inicial,
		td *di_posicion_incomoda_a_inicial) {

	int num_nos = 0;
	int contador_nos_ruta_maldita = 0;
	int contador_nos_recorridos = 0;
	td ancestro_ac = 0;
	gc gf_inicial_ctx;

	char *buffer = NULL;
	td *dis_minimas = NULL, *antecesores = NULL;
	td *ruta_maldita;

	buffer = malloc(MTC * sizeof(char));

	num_nos = init_gf(matrix_aristas, num_filas, &gf_inicial_ctx, falso,
			verdadero);

	dis_minimas = calloc(num_nos + 1, sizeof(td));
	if (!dis_minimas) {
		perror("no se consigio memoria para dis");
		exit(EXIT_FAILURE);
	}
	antecesores = calloc(num_nos + 1, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		exit(EXIT_FAILURE);
	}
	memset(antecesores, DVI, (num_nos + 1) * sizeof(td));
	ruta_maldita = calloc(num_nos + 1, sizeof(td));

	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(EXIT_FAILURE);
	}

	dijkstra_main(NULL, 0, posicion_incomoda, posicion_inicial, &gf_inicial_ctx,
			dis_minimas, antecesores);

	*(ruta_maldita + contador_nos_ruta_maldita++) = posicion_inicial;

	while (*(ruta_maldita + contador_nos_ruta_maldita) != posicion_incomoda
			&& contador_nos_recorridos < num_nos + 1) {
		ancestro_ac = *(antecesores
				+ *(ruta_maldita + contador_nos_ruta_maldita - 1));

		if (ancestro_ac != 0) {
			*(ruta_maldita + contador_nos_ruta_maldita) = ancestro_ac;
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

	if (di_posicion_incomoda_a_inicial) {
		*di_posicion_incomoda_a_inicial = *(dis_minimas + posicion_inicial);
	}
	return num_nos - contador_nos_ruta_maldita + 1;
}

float escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
		td posicion_polis, td posicion_ratas, td *salidas_carretera,
		int num_salidas_carretera) {
	int i;
	int num_nos_viables = 0;
	int num_salidas_viables = 0;
	float maxima_velocidad = 0;
	float tiempo_polis = 0;
	td salida_carretera_ac = 0;
	td di_salida_carretera_ac = 0;
	td di_polis_a_ratas = 0;
	td di_recorrida_polis = 0;
	char *buffer = NULL;
	ncp *no_salida_mas_cercana = NULL;
	gc *gf_viable_ctx = NULL;
	cpc *cola_salidas_carretera = NULL;
	td *dis_minimas = NULL;
	td *antecesores = NULL;
	td *dis_salidas_carretera = NULL;
	td *salidas_carretera_viables = NULL;

	buffer = calloc(1000, sizeof(char));

	gf_viable_ctx = calloc(1, sizeof(gc));
	if (!gf_viable_ctx) {
		perror("no se consigio memoria para gf viable");
		abort();
	}

	num_nos_viables = escape_cabron_determina_nos_viables(matrix_aristas,
			num_filas, gf_viable_ctx, posicion_polis, posicion_ratas,
			&di_polis_a_ratas);

	if (num_nos_viables < 2) {
		return maxima_velocidad;
	}

	dis_minimas = malloc((num_nos_viables + 1) * sizeof(td));
	if (!dis_minimas) {
		perror("no se consigio memoria para dis");
		abort();
	}
	antecesores = malloc((num_nos_viables + 1) * sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para antecesores");
		abort();
	}
	dis_salidas_carretera = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para dis de salidas a carretera");
		abort();
	}
	salidas_carretera_viables = calloc(num_salidas_carretera, sizeof(td));
	if (!antecesores) {
		perror("no se consigio memoria para salidas a carretera viables");
		abort();
	}
	memset(antecesores, DVI, (num_nos_viables + 1) * sizeof(td));
	memset(dis_minimas, DVI, (num_nos_viables + 1) * sizeof(td));

	dijkstra_main(NULL, 0, posicion_ratas, posicion_polis, gf_viable_ctx,
			dis_minimas, antecesores);

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_ac = *(salidas_carretera + i);
		if (salida_carretera_ac == posicion_polis) {

			continue;
		}
		if ((di_salida_carretera_ac = *(dis_minimas + salida_carretera_ac))
				== MV || di_salida_carretera_ac == CPVI) {

			continue;
		}

		*(dis_salidas_carretera + num_salidas_viables) = di_salida_carretera_ac;
		*(salidas_carretera_viables + num_salidas_viables) =
				salida_carretera_ac;
		num_salidas_viables++;
	}

	if (!num_salidas_viables) {
		return maxima_velocidad;
	}

	cola_salidas_carretera = calloc(1, sizeof(cpc));
	if (!antecesores) {
		perror("no se consigio memoria para cola de dis a salidas");
		abort();
	}

	cp_init(cola_salidas_carretera, NULL, salidas_carretera_viables,
			dis_salidas_carretera, num_salidas_viables, NULL, NULL );

	if (cp_es_vacia(cola_salidas_carretera)) {
		return maxima_velocidad;
	}

	no_salida_mas_cercana = cp_pop(cola_salidas_carretera);

	di_recorrida_polis = no_salida_mas_cercana->id + di_polis_a_ratas;

	tiempo_polis = (float) di_recorrida_polis / MAX_VEL_POLIS;

	maxima_velocidad = (float) no_salida_mas_cercana->id / tiempo_polis;

	return maxima_velocidad;
}

float escape_cabron_main() {
	float maxima_velocidad = 0;

	int num_aristas = 0;

	td num_nos = 0, num_salidas = 0;
	td posicion_ratas = 0, posicion_polis = 0;

	/*	tipo_dato datos_escape_mem[ESCAPE_CABRON_MAX_FILAS_INPUT][ESCAPE_CABRON_MAX_COLS_INPUT] =
	 { { 0 } };
	 */

	td *datos_escape = NULL;
	td *inicio_aristas = NULL;
	td *salidas = NULL;

	datos_escape = calloc(
			ESCAPE_CABRON_MAX_COLS_INPUT * ESCAPE_CABRON_MAX_FILAS_INPUT,
			sizeof(td));
	if (!datos_escape) {
		perror("no se pudo obtener memoria para datos_Escape");
		abort();
	}

	lee_matrix_long_stdin((td *) datos_escape, &num_aristas, NULL,
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

	cc_realinea_array(inicio_aristas, num_aristas, ESCAPE_CABRON_MAX_COLS_INPUT,
			3);

	maxima_velocidad = escape_cabron_encuentra_escape(inicio_aristas,
			num_aristas, posicion_polis, posicion_ratas, salidas, num_salidas);

	return maxima_velocidad;
}

int main(int argc, char *argv[]) {
	float resultado = 0;

	resultado = escape_cabron_main();
	if (resultado) {
		printf("%.10f\n", resultado);
	} else {
		printf("IMPOSSIBLE\n");
	}

	return 0;
}
