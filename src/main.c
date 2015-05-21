#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define td unsigned long

#define MAX_ndS 101
#define TAM_MAX_LINEA 1024
#define TAM_MAX_NUMERO 128
#define MAX_fils_INPUT 5010
#define MAX_COLS_INPUT 256
#define MAX_fils_ndS 1000
#define MAX_COLS_ndS 1000
#define CC_COMPARACION_IZQ_MENOR -1
#define CC_COMPARACION_IZQ_IGUAL 0
#define CC_COMPARACION_IZQ_MAYOR 1
#define MAX_TAM_CADENA 200
#define aa_id_INVALIDO -1
#define aa_VL_INVALIDO -1
#define cp_VL_INVALIDO -1
#define dij_VL_INVALIDO -1
#define GF_VL_INVALIDO -1

#define MAX_VL (td) (2<<28)

#define GF_nd_org 0
#define GF_nd_dst 1
#define GF_dis_ENTRE_ndS 2

#define GF_LIMITE_ORDENACION_LINEAL 2

typedef enum BOOLEANOS {
	falso = 0, tru
} bool;


#define GF_AVANZAR_nd(nd_apr,criterio_busqueda,discriminar_principal) \
		nd_apr = (nd_apr)->sig;

#define GF_COPIA_nd_dts(nd_org,nd_dst) \
		nd_dst->vl=nd_dst->vl; \
		nd_dst->dis=nd_dst->dis; \
		nd_dst->id=nd_dst->id;

#define GF_nd_SIG_ANT(nd_ant,nd_sig,nd_act,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GF_VL: \
			nd_sig= (nd_act)->sig_vl; \
			nd_ant= (nd_act)->ant_vl; \
			break; \
		case GF_dis: \
			nd_sig= (nd_act)->sig_dis; \
			nd_ant= (nd_act)->ant_dis; \
			break; \
		case GF_id: \
			nd_sig= (nd_act)->sig_id; \
			nd_ant= (nd_act)->ant_id; \
			break; \
		case GF_PRINCIPAL: \
			nd_sig= (nd_act)->sig; \
			nd_ant= (nd_act)->ant; \
			break; \
		default: \
			perror("en GF_AVANZAR_nd  hubo un error culero al buscar"); \
			break; \
		}

#define GF_ASIGNAR_SIG_ANT(nd_ant,nd_sig,nd_act,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GF_VL: \
			(nd_act)->sig_vl=nd_sig; \
			(nd_act)->ant_vl=nd_ant; \
			break; \
		case GF_dis: \
			(nd_act)->sig_dis=nd_sig; \
			(nd_act)->ant_dis=nd_ant; \
			break; \
		case GF_id: \
			(nd_act)->sig_id=nd_sig; \
			(nd_act)->ant_id=nd_ant; \
			break; \
		case GF_PRINCIPAL: \
			(nd_act)->sig=nd_sig; \
			(nd_act)->ant=nd_ant; \
			break; \
		default: \
			perror("en GF_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define GF_ASIGNAR_SIG(nd_sig,nd_act,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GF_VL: \
			(nd_act)->sig_vl=nd_sig; \
			break; \
		case GF_dis: \
			(nd_act)->sig_dis=nd_sig; \
			break; \
		case GF_id: \
			(nd_act)->sig_id=nd_sig; \
			break; \
		case GF_PRINCIPAL: \
			(nd_act)->sig=nd_sig; \
			break; \
		default: \
			perror("en GF_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define GF_ASIGNAR_ANT(nd_ant,nd_act,criterio_busqueda) \
		switch (criterio_busqueda) { \
	 	case GF_VL: \
			(nd_act)->ant_vl=nd_ant; \
			break; \
		case GF_dis: \
			(nd_act)->ant_dis=nd_ant; \
			break; \
		case GF_id: \
			(nd_act)->ant_id=nd_ant; \
			break; \
		case GF_PRINCIPAL: \
			(nd_act)->ant=nd_ant; \
			break; \
		default: \
			perror("en GF_ASIGNAR hubo un error culero al buscar"); \
			break; \
		}

#define aa_actIZAR_ALTURA(nd) \
	(nd)->altura = ((nd)->hijo_izq || (nd)->hijo_der)? \
			cc_int_max(aa_GET_ALTURA((nd)->hijo_izq), aa_GET_ALTURA((nd)->hijo_der)) + 1: \
			0;

#define aa_GET_ALTURA(nd) \
	((nd)?(nd)->altura:0)

#define aa_GET_VL(nd) \
	((nd)?(nd)->vl:aa_VL_INVALIDO)

#define ab_actIZAR_PADRE(nd,nuevo_padre) \
	((nd)?(nd)->padre=(nuevo_padre):((void)0))

#define aa_GET_PADRE(nd) \
	((nd)?(nd)->padre:NULL)

#define aa_GET_id(nd) \
	((nd)?(nd)->id:aa_id_INVALIDO)

#define ab_actIZAR_HIJO_IZQ(nd,nuevo_hijo) \
	((nd)?(nd)->hijo_izq=(nuevo_hijo):((void)0))

#define ab_actIZAR_HIJO_DER(nd,nuevo_hijo) \
	((nd)?(nd)->hijo_der=(nuevo_hijo):((void)0))

#define cp_ASIGNA_id(nd,nuevo_id) \
	(nd)->id=nuevo_id

#define cp_ASIGNA_VL(nd,nuevo_vl) \
	(nd)->vl=nuevo_vl

typedef enum GF_TIPO_RESULTADO_BUSQUEDA {
	GF_NADA_ENCONTRADO,
	GF_nd_ENCONTRADO,
	GF_ndS_PRE_POST_ENCONTRADOS
} GF_TIPO_RESULTADO_BUSQUEDA;

typedef struct nd {
	td vl;
	td id;
	td dis;
	int num_nds_asociados;
	int num_nds_asociados_id;
	int num_nds_asociados_vl;
	int num_nds_asociados_dis;
	struct nd *sig;
	struct nd *ant;
	struct nd *sig_id;
	struct nd *ant_id;
	struct nd *sig_vl;
	struct nd *ant_vl;
	struct nd *sig_dis;
	struct nd *ant_dis;
} nd;

typedef struct nd_ab {
	td id;
	td vl;
	unsigned int altura;

	struct nd_ab *hijo_izq;
	struct nd_ab *hijo_der;
	struct nd_ab *padre;
} nd_ab;

typedef struct grifo_ctx {
	int localidades_usadas;
	nd *inicio;
	nd *final;
	nd nds_disponibles[MAX_ndS];
	td mtx_diss[MAX_COLS_ndS][MAX_fils_ndS];
	nd *refs_nds_por_id[MAX_fils_ndS];
} gf_ctx;

typedef struct ab_ctx {
	bool no_ids_repetidos;
	int localidades_usadas;
	nd_ab *raiz;
	nd_ab nds_disponibles[MAX_ndS];
} ab_ctx;

typedef struct cp_ctx {
	int num_nds;
	ab_ctx actx_mem;
	ab_ctx *actx;
	nd_ab *refs_directas_por_id_mem[MAX_ndS];
	nd_ab **refs_directas_por_id;
} cp_ctx;

typedef nd_ab nd_cp;


int lee_mtx_long_stdin(td *mtx, int *num_fils, int *num_cols,
		int num_max_fils, int num_max_cols);


int init_gf(void *mtx, int num_fils, gf_ctx *ctx,
		bool usar_hashes, bool relaciones_bidireccionales);

nd *gf_nd_alloc(gf_ctx *ctx, int localidades_solicitadas);


int cc_apr_valido(void *p);


#define aa_ALTURA_CARGADA_IZQ -1
#define aa_ALTURA_CARGADA_DER 1
#define aa_ALTURA_BALANCEADA 0

void ab_recorrido_preoder(nd_ab *raiz);

void ab_colectar_dts_recorrido_preoder(nd_ab *raiz,
		td *dts_ordenados, int *num_dts_colectados);

int aa_compara_nds(nd_ab *nd1,
		nd_ab *nd2);

int cc_int_max(int a, int b);


void ab_colectar_dts_recorrido_inoder(nd_ab *raiz,
		td *dts_ordenados, int *num_dts_colectados);

void ab_recorrido_inoder(nd_ab *raiz);

void cp_modificar_vl_nd(cp_ctx *cpctx,
		td id, td nuevo_vl);

void dij_relaxar_nd(gf_ctx *gctx, cp_ctx *cpctx,
		td ind_nd_org, td ind_nd_dst,
		td *ances,nd_cp *nd_org);

void cp_init(cp_ctx *ctx,
		nd_cp *nds, td *vles, td *ids,
		int num_nds, ab_ctx *actx,
		nd_ab **refs_directas);

void cp_get_vles(cp_ctx *ctx,
		td *vles, int *num_vles);

nd_cp *cp_pop(cp_ctx *ctx);

bool cp_es_vacia(cp_ctx *ctx);

void dij_main(void *mtx_diss, int num_fils,
		td ind_nd_org, td ind_nd_dst,
		gf_ctx *gctx, td *diss_mims,
		td *ances);


void gf_copia_nd(const nd *nd_org, nd *nd_dst);

bool cc_arreglo_contiene(td *arreglo, int tam_arreglo,
		td vl_buscado);


void gf_copia_profunda(const gf_ctx *ctx_org,
		gf_ctx *ctx_dst, td *ids_a_ignorar,
		int tam_ids_a_ignorar);

void cc_inutiliza_nd_cp(nd_cp *nds,
		int num_nds);

void cc_realinea_array(td *arreglo, int num_fils,
		int alineacion_act, int alineacion_nueva);

int lee_mtx_long_stdin(td *mtx, int *num_fils, int *num_cols,
		int num_max_fils, int num_max_cols) {
	int id_fils = 0;
	int id_cols = 0;
	long numero = 0;
	char *sig_cadena_numero = NULL;
	char *cadena_numero_act = NULL;
	char linea[TAM_MAX_LINEA];

	while (fgets(linea, TAM_MAX_LINEA, stdin)) {
		id_cols = 0;
		cadena_numero_act = linea;
		for (sig_cadena_numero = linea;; sig_cadena_numero =
				cadena_numero_act) {
			numero = strtol(sig_cadena_numero, &cadena_numero_act, 10);
			if (cadena_numero_act == sig_cadena_numero) {
				break;
			}
			*(mtx + id_fils * num_max_cols + id_cols) =
					numero;
			id_cols++;
			if (id_cols >= num_max_cols) {
				perror("se leyeron demasiadas cols, a la verga");
				abort();
			}
		}
		if (num_cols) {
			num_cols[id_fils] = id_cols;
		}
		id_fils++;
		if (id_fils > num_max_fils) {
			perror("se leyeron demasiadas fils, a la verga");
			abort();
		}
	}

	*num_fils = id_fils;
	return 0;
}

int init_gf(void *mtx, int num_fils, gf_ctx *ctx,
		bool usar_hashes, bool relaciones_bidireccionales) {
	int i;
	int ctd_nds = 0;
	td id_org_act = 0;
	td id_dst_act = 0;
	td dis_act = 0;
	td *mtx_int = NULL;
	td *mtx_diss = NULL;
	nd *nuevo_nd = NULL;
	td nds_registrados[MAX_ndS] = { falso };

	memset(ctx, 0, sizeof(gf_ctx));

	mtx_int = mtx;
	mtx_diss = (td *) ctx->mtx_diss;
	memset(mtx_diss, GF_VL_INVALIDO,
			sizeof(ctx->mtx_diss));
	for (i = 0; i < num_fils; i++) {
		id_org_act = *(mtx_int + i * 3 + GF_nd_org);
		id_dst_act = *(mtx_int + i * 3 + GF_nd_dst);
		dis_act = *(mtx_int + i * 3 + GF_dis_ENTRE_ndS);

		*(mtx_diss + id_org_act * MAX_COLS_ndS
				+ id_dst_act) = dis_act;
		
		if (relaciones_bidireccionales) {
			
			*(mtx_diss + id_dst_act * MAX_COLS_ndS
					+ id_org_act) = dis_act;
		}
		if (!*(nds_registrados + id_org_act)) {
			nuevo_nd = gf_nd_alloc(ctx, 1);
			nuevo_nd->id = id_org_act;
			if (ctx->inicio) {
				ctx->final->sig = nuevo_nd;
			} else {
				ctx->inicio = nuevo_nd;
			}
			ctx->final = nuevo_nd;
			*(nds_registrados + id_org_act) = tru;
			ctd_nds++;
		}
		if (!*(nds_registrados + id_dst_act)) {
			nuevo_nd = gf_nd_alloc(ctx, 1);
			nuevo_nd->id = id_dst_act;
			ctx->final->sig = nuevo_nd;
			ctx->final = nuevo_nd;
			*(nds_registrados + id_dst_act) = tru;
			ctd_nds++;
		}
	}
	return ctd_nds;
}

nd *gf_nd_alloc(gf_ctx *ctx, int localidades_solicitadas) {
	nd *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nds_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nds_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

int cc_apr_valido(void *p) {
	return (p != NULL );
}


int aa_compara_nds(nd_ab *nd1,
		nd_ab *nd2) {
	if (nd1->vl < nd2->vl) {
		return CC_COMPARACION_IZQ_MENOR;
	} else {
		if (nd1->vl > nd2->vl) {
			return CC_COMPARACION_IZQ_MAYOR;
		} else {
			return CC_COMPARACION_IZQ_IGUAL;
		}
	}
}

int cc_int_max(int a, int b) {
	return (a > b) ? a : b;
}


void ab_recorrido_inoder(nd_ab *raiz) {
	if (!raiz) {
		return;
	}
	ab_recorrido_inoder(raiz->hijo_izq);
	
	ab_recorrido_inoder(raiz->hijo_der);
}

void cp_modificar_vl_nd(cp_ctx *cpctx,
		td id, td nuevo_vl) {
	nd_ab *referencia_directa = NULL;
	nd_ab **refs_directas = NULL;

	refs_directas = cpctx->refs_directas_por_id;

	referencia_directa = *(refs_directas + id);

	
	referencia_directa->vl = nuevo_vl;

}

void dij_relaxar_nd(gf_ctx *gctx, cp_ctx *cpctx,
		td ind_nd_org, td ind_nd_dst,
		td *ances, nd_cp *nd_org) {
	td dist_org_dest = 0;

	td *mtx_diss = NULL;

	nd_ab *dis_min_org = NULL;
	nd_ab *dis_min_dst = NULL;
	nd_ab **diss_mims = NULL;

	mtx_diss = (td*) gctx->mtx_diss;
	dist_org_dest = *(mtx_diss
			+ ind_nd_org * MAX_COLS_ndS + ind_nd_dst);
	

	diss_mims = cpctx->refs_directas_por_id;

	dis_min_org = *(diss_mims + ind_nd_org);
	if (nd_org) {
		dis_min_org = nd_org;
	}
	dis_min_dst = *(diss_mims + ind_nd_dst);

	if (dis_min_dst->vl
			> dis_min_org->vl + dist_org_dest) {
		
		cp_modificar_vl_nd(cpctx, ind_nd_dst,
				dis_min_org->vl + dist_org_dest);
		if (ances) {
			
			*(ances + ind_nd_dst) = ind_nd_org;
		}
	}
}
void dij_main(void *mtx_diss, int num_fils,
		td ind_nd_org, td ind_nd_dst,
		gf_ctx *gctx, td *diss_mims,
		td *ances) {

	int i, j;

	int ctd = 0;
	int num_nds = 0;

	td id_org_act = 0;
	td id_dst_act = 0;
	td dis_act = 0;
	td max_id = 0;
	td *mtx_diss_int = NULL;

	gf_ctx gctx_mem;
	gf_ctx *gctx_int;
	cp_ctx cpctx;

	nd *nd_org_act = NULL;
	nd_cp *nd_mas_cercas = NULL;

	bool nds_diss_mims_calculadas[MAX_ndS] = { falso };
	nd_cp *diss_mims_nds;
	nd_cp **diss_mims_nds_calculadas;

	diss_mims_nds = calloc(MAX_ndS, sizeof(nd_cp));
	if (!diss_mims_nds) {
		perror("no ay memm para diss mims nds");
		abort();
	}
	diss_mims_nds_calculadas = calloc(MAX_ndS,
			sizeof(nd_cp*));
	if (!diss_mims_nds_calculadas) {
		perror("no ay memm para diss mims nds cclculadas");
		abort();
	}

	cc_inutiliza_nd_cp(diss_mims_nds, MAX_ndS);

	if (gctx) {
		gctx_int = gctx;
	} else {
		gctx_int = &gctx_mem;
		init_gf(mtx_diss, num_fils, gctx_int, falso, tru);
	}
	mtx_diss_int = (td *) gctx_int->mtx_diss;
	
	nd_org_act = gctx_int->inicio;

	
	while (nd_org_act) {
		if (nd_org_act->id == ind_nd_org) {
			(diss_mims_nds + nd_org_act->id)->vl = 0;
		} else {
			(diss_mims_nds + nd_org_act->id)->vl =
					MAX_VL;
		}
		if (nd_org_act->id > max_id) {
			max_id = nd_org_act->id;
			if (max_id > MAX_ndS) {
				perror(
						"El id maximo supera el maximo de nds permitidos, a la mierda todo");
				abort();
			}
		}
		(diss_mims_nds + nd_org_act->id)->id =
				nd_org_act->id;
		GF_AVANZAR_nd(nd_org_act, GF_PRINCIPAL, falso);
		ctd++;
	}
	num_nds = ctd;

	
	cp_init(&cpctx, diss_mims_nds, NULL, NULL,
			max_id + 1, NULL, NULL );
	

	ctd = 0;
	while (!cp_es_vacia(&cpctx)) {
		nd_mas_cercas = cp_pop(&cpctx);
		nds_diss_mims_calculadas[nd_mas_cercas->id] =
				tru;
		*(diss_mims_nds_calculadas + nd_mas_cercas->id) =
				nd_mas_cercas;

		id_org_act = nd_mas_cercas->id;
		

		for (j = 0; j < MAX_COLS_ndS; j++) {
			dis_act = (td) *(mtx_diss_int
					+ id_org_act * MAX_fils_ndS + j);
			id_dst_act = j;
			if (dis_act != GF_VL_INVALIDO
					&& !(*(nds_diss_mims_calculadas
							+ id_dst_act))) {
				
				dij_relaxar_nd(gctx_int, &cpctx, id_org_act,
						id_dst_act, ances, nd_mas_cercas);
			}
		}

		ctd++;
	}
	
	*(ances + ind_nd_org) = 0;
	for (i = 0; i < max_id + 1; i++) {
		*(diss_mims + i) =
				i == ind_nd_org ? 0 :
				cc_apr_valido(
						(*(diss_mims_nds_calculadas + i))) ?
						(*(diss_mims_nds_calculadas + i))->vl
								== MAX_VL ?
								cp_VL_INVALIDO :
								(*(diss_mims_nds_calculadas + i))->vl
						:cp_VL_INVALIDO;
	}
	

}

void cp_init(cp_ctx *ctx,
		nd_cp *nds, td *vles, td *ids,
		int num_nds, ab_ctx *actx,
		nd_ab **refs_directas) {
	int i;
	int num_nds_int = 0;
	nd_cp **nds_int = NULL;

	memset(ctx, 0, sizeof(cp_ctx));
	memset(ctx->refs_directas_por_id_mem, 0,
			sizeof(ctx->refs_directas_por_id_mem));
	nds_int =
			(nd_cp **) &ctx->refs_directas_por_id_mem;

	if (actx) {
		if (!refs_directas) {
			perror("se paso un ctx de arbol sin refs directas");
			exit(1);
		}
		ctx->refs_directas_por_id = refs_directas;
		num_nds_int = num_nds;
	} else {
		for (i = 0; i < num_nds; i++) {
			if (nds) {
				if ((nds + i)->id == cp_VL_INVALIDO) {
					continue;
				}
				*(nds_int + aa_GET_id((nds + i))) = (nds + i);
				
			} else {
				if (!vles) {
					perror("no se proporcionaron nds ni vles");
					exit(1);
				}
				if (ids) {
					*(nds_int + *(ids + i)) = calloc(1,
							sizeof(nd_cp));
					if (!*(nds_int + *(ids + i))) {
						perror(
								"No se pudo obtener mem para nd cp nuevo con ids");
					}
					cp_ASIGNA_VL(*(nds_int + *(ids + i)),
							*(vles + i));
					cp_ASIGNA_id(*(nds_int + *(ids + i)),
							*(ids + i));
					
				} else {
					*(nds_int + i + 1) = calloc(1,
							sizeof(nd_cp));
					if (!*(nds_int + i + 1)) {
						perror(
								"No se pudo obtener mem para nd cp nuevo sin ids");
					}
					cp_ASIGNA_VL(*(nds_int + i + 1),
							*(vles + i));
					cp_ASIGNA_id(*(nds_int + i + 1), i + 1);
					
				}
			}
			num_nds_int++;
		}

		ctx->refs_directas_por_id =
				ctx->refs_directas_por_id_mem;
		ctx->num_nds = num_nds_int;

	}

}

nd_cp *cp_pop(cp_ctx *ctx) {
	bool alguno_no_es_maximo = falso;
	int i = 0;
	td id_min = 0;
	td vl_min = MAX_VL;
	nd_cp *nd_encontrado = NULL;
	nd_cp *primer_nd_no_vacio = NULL;

	for (i = 0; i < MAX_ndS; i++) {
		nd_encontrado = *(ctx->refs_directas_por_id + i);
		if (nd_encontrado) {
			
			if (!primer_nd_no_vacio) {
				primer_nd_no_vacio = nd_encontrado;
			}
			if (aa_GET_VL(nd_encontrado) < vl_min) {
				vl_min = aa_GET_VL(nd_encontrado);
				id_min = aa_GET_id(nd_encontrado);
				alguno_no_es_maximo = tru;
			}
		}
	}

	

	if (id_min < MAX_ndS && alguno_no_es_maximo) {
		
		nd_encontrado = *(ctx->refs_directas_por_id + id_min);
		*(ctx->refs_directas_por_id + id_min) = NULL;
		ctx->num_nds--;
		
	} else {
		if (primer_nd_no_vacio) {
			
			nd_encontrado = primer_nd_no_vacio;
			*(ctx->refs_directas_por_id
					+ aa_GET_id(primer_nd_no_vacio)) = NULL;
			ctx->num_nds--;
			
		} else {
			
		}
	}

	return nd_encontrado;
}

void cp_get_vles(cp_ctx *ctx,
		td *vles, int *num_vles) {
	int i;
	int ctd_nds_validos = 0;
	nd_cp *nd_act = NULL;
	for (i = 0; i < MAX_ndS; i++) {
		nd_act = *(ctx->refs_directas_por_id + i);
		if (nd_act) {
			
			*(vles + ctd_nds_validos) = nd_act->vl;
			ctd_nds_validos++;
		}
	}
	*num_vles = ctd_nds_validos;
}

bool cp_es_vacia(cp_ctx *ctx) {
	return !ctx->num_nds;
}

void gf_copia_profunda(const gf_ctx *ctx_org,
		gf_ctx *ctx_dst, td *ids_a_ignorar,
		int tam_ids_a_ignorar) {
	int i, j;
	td id_nd_org_act = 0;

	td *mtx_org = NULL;
	td *mtx_dst = NULL;

	nd *nd_org_principal_act = NULL;
	nd *nd_dst_principal_act = NULL;
	nd *nd_dst_principal_previo = NULL;

	

	mtx_org = (td*) ctx_org->mtx_diss;
	mtx_dst = (td *) ctx_dst->mtx_diss;
	memcpy(mtx_dst, mtx_org,
			sizeof(ctx_org->mtx_diss));

	

	nd_org_principal_act = ctx_org->inicio;
	
	while (nd_org_principal_act) {
		id_nd_org_act = nd_org_principal_act->id;
		
		if (ids_a_ignorar
				&& cc_arreglo_contiene(ids_a_ignorar,
						tam_ids_a_ignorar, id_nd_org_act)) {

			
			for (i = 0; i < MAX_fils_ndS; i++) {
				*(mtx_dst + i * MAX_COLS_ndS
						+ id_nd_org_act) = GF_VL_INVALIDO;
			}
			for (j = 0; j < MAX_COLS_ndS; j++) {
				*(mtx_dst
						+ id_nd_org_act * MAX_COLS_ndS + j) =
						GF_VL_INVALIDO;
			}
			GF_AVANZAR_nd(nd_org_principal_act, 0, 0);
			
			continue;
		}
		
		nd_dst_principal_act = gf_nd_alloc(ctx_dst, 1);
		memset(nd_dst_principal_act, 0, sizeof(nd));
		gf_copia_nd(nd_org_principal_act,
				nd_dst_principal_act);
		if (nd_dst_principal_previo) {
			nd_dst_principal_previo->sig =
					nd_dst_principal_act;
			nd_dst_principal_act->ant =
					nd_dst_principal_previo;
		} else {
			ctx_dst->inicio = nd_dst_principal_act;
		}
		nd_dst_principal_previo = nd_dst_principal_act;

		GF_AVANZAR_nd(nd_org_principal_act, 0, 0);
	}

}

#define GF_COPIA_PROPIEDAD(propiedad) nd_dst->propiedad = nd_org->propiedad
void gf_copia_nd(const nd *nd_org, nd *nd_dst) {
	GF_COPIA_PROPIEDAD(dis);
	GF_COPIA_PROPIEDAD(id);
	GF_COPIA_PROPIEDAD(num_nds_asociados);
	GF_COPIA_PROPIEDAD(num_nds_asociados_dis);
	GF_COPIA_PROPIEDAD(num_nds_asociados_id);
	GF_COPIA_PROPIEDAD(num_nds_asociados_vl);
	GF_COPIA_PROPIEDAD(vl);
}

bool cc_arreglo_contiene(td *arreglo, int tam_arreglo,
		td vl_buscado) {
	int i;
	for (i = 0; i < tam_arreglo; i++) {
		
		if (*(arreglo + i) == vl_buscado) {
			return tru;
		}
	}
	return falso;
}

#define GF_GET_APR_pos_mtx(apr_dst,pos_fils,pos_cols) \
			if (es_array) { \
				apr_dst= (mtx_array + pos_fils * num_cols + pos_cols); \
			} else { \
				apr_dst= (*(mtx_pointer + pos_fils) + pos_cols); \
			}

void cc_inutiliza_nd_cp(nd_cp *nds,
		int num_nds) {
	int i;
	for (i = 0; i < num_nds; i++) {
		cp_ASIGNA_id((nds + i),
				cp_VL_INVALIDO);
		cp_ASIGNA_VL((nds + i), cp_VL_INVALIDO);
	}
}

void cc_realinea_array(td *arreglo, int num_fils,
		int alineacion_act, int alineacion_nueva) {
	int i, j;
	for (i = 0; i < num_fils; i++) {
		for (j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_act + j);
		}

	}
}

int lee_matriz_int_archivo(const char * nombre_archivo,
		td mtx[MAX_COLS_INPUT][MAX_fils_INPUT], int *fils) {
	int id_fils = 0;
	int id_cols = 0;
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
		id_cols = 0;
		while (inicio_cadena_num != NULL ) {
			numero = strtol(inicio_cadena_num, NULL, 10);
			mtx[id_cols][id_fils] = (td) numero;
			inicio_cadena_num = strtok(NULL, " ");
			id_cols++;
		}
		id_fils++;
	}
	*fils = id_fils;
	fclose(fp);
	return 0;
}

int lee_matriz_long_stdin(td mtx[MAX_COLS_INPUT][MAX_fils_INPUT],
		int *fils) {
	int id_fils = 0;
	char linea[TAM_MAX_LINEA];

	fgets(linea, TAM_MAX_LINEA, stdin);
	sscanf(linea, "%ld %ld", &mtx[0][id_fils],
			&mtx[1][id_fils]);
	id_fils++;
	while (fgets(linea, TAM_MAX_LINEA, stdin)
			&& sscanf(linea, "%ld %ld", &mtx[0][id_fils],
					&mtx[1][id_fils]) == 2) {
		id_fils++;
	}

	*fils = id_fils;
	return 0;
}

void ab_colectar_dts_recorrido_inoder(nd_ab *raiz,
		td *dts_ordenados, int *num_dts_colectados) {
	if (!raiz) {
		return;
	}
	ab_colectar_dts_recorrido_inoder(raiz->hijo_izq,
			dts_ordenados, num_dts_colectados);
	*(dts_ordenados + (*num_dts_colectados)++) = raiz->vl;
	ab_colectar_dts_recorrido_inoder(raiz->hijo_der,
			dts_ordenados, num_dts_colectados);
}

void ab_colectar_dts_recorrido_preoder(nd_ab *raiz,
		td *dts_ordenados, int *num_dts_colectados) {
	if (!raiz) {
		return;
	}
	*(dts_ordenados + (*num_dts_colectados)++) = raiz->vl;
	ab_colectar_dts_recorrido_preoder(raiz->hijo_izq,
			dts_ordenados, num_dts_colectados);
	ab_colectar_dts_recorrido_preoder(raiz->hijo_der,
			dts_ordenados, num_dts_colectados);
}

bool from_stack(void *ptr) {
	return tru;
}

void ab_recorrido_preoder(nd_ab *raiz) {
	if (!raiz) {
		return;
	}
	
	ab_recorrido_preoder(raiz->hijo_izq);
	ab_recorrido_preoder(raiz->hijo_der);
}

#define MAX_VEL_POLIS 160
#define ESCAPE_CABRON_MAX_fils_INPUT 5003
#define ESCAPE_CABRON_MAX_COLS_INPUT 100

int escape_cabron_determina_nds_viables(void *mtx_vertices, int num_fils,
		gf_ctx *gf_viable_ctx, td pos_incomoda,
		td pos_inicial,
		td *dis_pos_incomoda_a_inicial);

double escape_cabron_encuentra_escape(void *mtx_vertices, int num_fils,
		td pos_polis, td pos_ratas,
		td *salidas_carretera, int num_salidas_carretera);

double escape_cabron_main();

void dij_calcula_ruta(td *ances,int tam_ances, td pos_inicial,
		td pos_dst, td *ruta, int *tam_ruta);


int escape_cabron_determina_nds_viables(void *mtx_aristas, int num_fils,
		gf_ctx *gf_viable_ctx, td pos_incomoda,
		td pos_inicial,
		td *dis_pos_incomoda_a_inicial) {

	int num_nds = 0;
	int ctd_nds_ruta_maldita = 0;
	int ctd_nds_recorridos = 0;
	td ancestro_act = 0;
	gf_ctx gf_inicial_ctx;

	char *bfr = NULL;
	td *diss_mims = NULL, *ances = NULL;
	td *ruta_maldita;

	bfr = malloc(MAX_TAM_CADENA * sizeof(char));

	num_nds = init_gf(mtx_aristas, num_fils, &gf_inicial_ctx, falso,
			tru);

	diss_mims = calloc(num_nds + 1, sizeof(td));
	if (!diss_mims) {
		perror("no se consigio memoria para diss");
		exit(EXIT_FAILURE);
	}
	ances = calloc(num_nds + 1, sizeof(td));
	if (!ances) {
		perror("no se consigio memoria para ances");
		exit(EXIT_FAILURE);
	}
	memset(ances, dij_VL_INVALIDO,
			(num_nds + 1) * sizeof(td));
	ruta_maldita = calloc(num_nds + 1, sizeof(td));
	
	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(EXIT_FAILURE);
	}

	
	dij_main(NULL, 0, pos_incomoda, pos_inicial,
			&gf_inicial_ctx, diss_mims, ances);

	

	

	
	*(ruta_maldita + ctd_nds_ruta_maldita++) = pos_inicial;

	while (*(ruta_maldita + ctd_nds_ruta_maldita) != pos_incomoda
			&& ctd_nds_recorridos < num_nds + 1) {
		ancestro_act = *(ances
				+ *(ruta_maldita + ctd_nds_ruta_maldita - 1));
		
		if (ancestro_act != 0) {
			*(ruta_maldita + ctd_nds_ruta_maldita) = ancestro_act;
			ctd_nds_ruta_maldita++;
		} else {
			break;
		}
		ctd_nds_recorridos++;
	}

	if (ctd_nds_ruta_maldita < 2) {
		perror("no c encontraron nds prohibidos, no mames!");
		abort();
	}

	

	gf_copia_profunda(&gf_inicial_ctx, gf_viable_ctx, ruta_maldita + 1,
			ctd_nds_ruta_maldita - 1);

	if (dis_pos_incomoda_a_inicial) {
		*dis_pos_incomoda_a_inicial = *(diss_mims
				+ pos_inicial);
	}
	return num_nds - ctd_nds_ruta_maldita + 1;
}

double escape_cabron_encuentra_escape(void *mtx_aristas, int num_fils,
		td pos_polis, td pos_ratas,
		td *salidas_carretera, int num_salidas_carretera) {
	int i, j;
	int num_nds = 0;
	int tam_ruta_a_salida_act = 0;
	double maxima_velocidad = 0;
	double velocidad_persecucion = 0;
	double velocidad_mim = (double) MAX_VL;
	double razon_max_rata_y_poli_a_nd_act = MAX_VL;
	double razon_rata_y_poli_a_nd_act = MAX_VL;
	td salida_carretera_act = 0;
	td dis_recorrida_polis = 0;
	td dis_recorrida_bandidos = 0;
	td ind_nd_act = 0;
	td dis_poli_a_nd_act;
	td dis_rata_a_nd_act;
	td ind_razon_max_rata_y_poli_a_nd_act = MAX_VL;
	char *bfr = NULL;
	td *diss_mims_bandido = NULL;
	td *ances_bandido = NULL;
	td *diss_mims_polis = NULL;
	td *ances_polis = NULL;
	gf_ctx *gf_bandido_ctx = NULL;
	gf_ctx *gf_poli_ctx = NULL;
	td *ruta_a_salida_act = NULL;

	bfr = calloc(1000, sizeof(char));

	
	
	
	
	
	

	if (cc_arreglo_contiene(salidas_carretera, num_salidas_carretera,
			pos_ratas)) {
		
		return 0;
	}

	if (pos_polis == pos_ratas) {
		
		return velocidad_mim;
	}

	gf_poli_ctx = calloc(1, sizeof(gf_ctx));
	if (!gf_poli_ctx) {
		perror("no se consigio memoria para gf poli");
		abort();
	}

	gf_bandido_ctx = calloc(1, sizeof(gf_ctx));
	if (!gf_bandido_ctx) {
		perror("no se consigio memoria para gf bandido");
		abort();
	}

	num_nds = init_gf(mtx_aristas, num_fils, gf_poli_ctx, falso,
			tru);

	diss_mims_bandido = calloc((num_nds + 1), sizeof(td));
	if (!diss_mims_bandido) {
		perror("no se consigio memoria para diss bandido");
		abort();
	}
	ances_bandido = calloc((num_nds + 1), sizeof(td));
	if (!ances_bandido) {
		perror("no se consigio memoria para ances");
		abort();
	}

	diss_mims_polis = calloc((num_nds + 1), sizeof(td));
	if (!diss_mims_polis) {
		perror("no se consigio memoria para diss poli");
		abort();
	}
	ances_polis = calloc((num_nds + 1), sizeof(td));
	if (!ances_polis) {
		perror("no se consigio memoria para ances");
		abort();
	}

	ruta_a_salida_act = calloc(num_nds + 1, sizeof(td));
	if (!ruta_a_salida_act) {
		perror("no se consigio memoria para ruta_salida_act");
		abort();
	}

	

	gf_copia_profunda(gf_poli_ctx, gf_bandido_ctx, &pos_polis, 1);

	dij_main(NULL, 0, pos_polis, 0, gf_poli_ctx,
			diss_mims_polis, ances_polis);

	
	

	dij_main(NULL, 0, pos_ratas, 0, gf_bandido_ctx,
			diss_mims_bandido, ances_bandido);

	
	

	for (i = 0; i < num_salidas_carretera; i++) {
		salida_carretera_act = *(salidas_carretera + i);
		if (salida_carretera_act == pos_polis) {
			
			continue;
		}
		if (*(diss_mims_bandido + salida_carretera_act)
				== cp_VL_INVALIDO) {
			
			continue;
		}

		dij_calcula_ruta(ances_bandido, num_nds + 1,
				pos_ratas, salida_carretera_act, ruta_a_salida_act,
				&tam_ruta_a_salida_act);
		

		if (tam_ruta_a_salida_act < 2) {
			
			continue;
		}

		razon_max_rata_y_poli_a_nd_act = DBL_MIN;
		ind_razon_max_rata_y_poli_a_nd_act = MAX_VL;
		for (j = tam_ruta_a_salida_act - 2; j >= 0; j--) {
			ind_nd_act = *(ruta_a_salida_act + j);
			dis_poli_a_nd_act = *(diss_mims_polis
					+ ind_nd_act);
			
			dis_rata_a_nd_act = *(diss_mims_bandido
					+ ind_nd_act);
			
			razon_rata_y_poli_a_nd_act =
					(double) dis_rata_a_nd_act
							/ (double) dis_poli_a_nd_act;
			
			if (razon_rata_y_poli_a_nd_act
					> razon_max_rata_y_poli_a_nd_act) {
				razon_max_rata_y_poli_a_nd_act =
						razon_rata_y_poli_a_nd_act;
				ind_razon_max_rata_y_poli_a_nd_act = ind_nd_act;
			}
		}
		
		
		assert(razon_max_rata_y_poli_a_nd_act!=MAX_VL);
		assert(ind_razon_max_rata_y_poli_a_nd_act!=MAX_VL);

		dis_recorrida_polis = *(diss_mims_polis
				+ ind_razon_max_rata_y_poli_a_nd_act);
		dis_recorrida_bandidos = *(diss_mims_bandido
				+ ind_razon_max_rata_y_poli_a_nd_act);

		maxima_velocidad = (double) (dis_recorrida_bandidos
				* MAX_VEL_POLIS) / ((double) dis_recorrida_polis);
		
		

		if (maxima_velocidad < MAX_VEL_POLIS) {
			

			dis_recorrida_bandidos = *(diss_mims_bandido
					+ salida_carretera_act);
			dis_recorrida_polis = *(diss_mims_polis
					+ salida_carretera_act) + dis_recorrida_bandidos;
			velocidad_persecucion = (double) (dis_recorrida_bandidos
					* MAX_VEL_POLIS) / ((double) dis_recorrida_polis);

			

			if (velocidad_persecucion > maxima_velocidad) {
				maxima_velocidad = velocidad_persecucion;
			}

		}

		if (maxima_velocidad < velocidad_mim) {
			velocidad_mim = maxima_velocidad;
		}

	}

	return velocidad_mim;
}

double escape_cabron_main() {
	double maxima_velocidad = 0;

	int num_aristas = 0;

	td num_nds = 0, num_salidas = 0;
	td pos_ratas = 0, pos_polis = 0;

	td *dts_escape_mem = NULL;

	td *dts_escape = (td *) dts_escape_mem;
	td *inicio_aristas = NULL;
	td *salidas = NULL;

	dts_escape_mem = calloc(
			ESCAPE_CABRON_MAX_fils_INPUT * ESCAPE_CABRON_MAX_COLS_INPUT,
			sizeof(td));
	if (!dts_escape_mem) {
		perror("no se obtubo memoria para los dts del escape");
		abort();
	}
	dts_escape = dts_escape_mem;

	lee_mtx_long_stdin((td *) dts_escape, &num_aristas, NULL,
			ESCAPE_CABRON_MAX_fils_INPUT, ESCAPE_CABRON_MAX_COLS_INPUT);
	

	if (!num_aristas) {
		perror("vale verga, no c leyo nada");
		abort();
	}

	num_nds = *dts_escape;
	num_aristas = *(dts_escape + 1);
	num_salidas = *(dts_escape + 2);

	inicio_aristas = dts_escape + ESCAPE_CABRON_MAX_COLS_INPUT;
	salidas = inicio_aristas + num_aristas * ESCAPE_CABRON_MAX_COLS_INPUT;
	pos_ratas = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT);
	pos_polis = *(salidas + ESCAPE_CABRON_MAX_COLS_INPUT + 1);

	cc_realinea_array(inicio_aristas, num_aristas,
			ESCAPE_CABRON_MAX_COLS_INPUT, 3);

	maxima_velocidad = escape_cabron_encuentra_escape(inicio_aristas,
			num_aristas, pos_polis, pos_ratas, salidas, num_salidas);

	
	return maxima_velocidad;
}

void dij_calcula_ruta(td *ances, int tam_ances,
		td pos_inicial, td pos_dst,
		td *ruta_maldita, int *tam_ruta) {
	int ctd_nds_recorridos = 0;
	int ctd_nds_ruta_maldita = 0;
	td ancestro_act = 0;

	
	*(ruta_maldita + ctd_nds_ruta_maldita++) = pos_dst;
	
	while (*(ruta_maldita + ctd_nds_ruta_maldita - 1) != pos_inicial
			&& ctd_nds_recorridos < tam_ances) {
		ancestro_act = *(ances
				+ *(ruta_maldita + ctd_nds_ruta_maldita - 1));
		
		if (ancestro_act != 0) {
			*(ruta_maldita + ctd_nds_ruta_maldita) = ancestro_act;
			ctd_nds_ruta_maldita++;
		} else {
			break;
		}
		ctd_nds_recorridos++;
	}
	*tam_ruta = ctd_nds_recorridos + 1;
	
}

int main(int argc, char *argv[]) {
	double resultado = 0;

	resultado = escape_cabron_main();
	if (resultado != MAX_VL) {
		printf("%.10f\n", resultado);
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
