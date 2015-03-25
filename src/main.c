#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MIERDA printf("soldado del amor \n"),exit(0);

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
#define GRAFO_VALOR_INVALIDO -1

#define MAX_VALOR (tipo_dato) (2<<28)

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
	(nodo)->valor=nuevo_valor

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
	nodo *final;
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
	int num_nodos;
	arbol_binario_contexto actx_mem;
	arbol_binario_contexto *actx;
	nodo_arbol_binario *referencias_directas_por_indice_mem[MAX_NODOS];
	nodo_arbol_binario **referencias_directas_por_indice;
} cola_prioridad_contexto;

typedef nodo_arbol_binario nodo_cola_prioridad;

int lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas);

int caca_imprime_matrix(void *matrix, int num_filas, int *num_columnas,
		int num_columnas_fijo);

int init_grafo(void *matrix, int num_filas, grafo_contexto *ctx,
		bool usar_hashes, bool relaciones_bidireccionales);

nodo *grafo_nodo_alloc(grafo_contexto *ctx, int localidades_solicitadas);

/* XXX: : https://www.securecoding.cert.org/confluence/display/seccode/MEM10-C.+Define+and+use+a+pointer+validation+function */
int caca_apuntador_valido(void *p);

void arbol_avl_init(arbol_binario_contexto *ctx, tipo_dato *indices,
		tipo_dato *datos, int num_datos,
		nodo_arbol_binario **arreglo_referencias_nodos);

#define ARBOL_AVL_ALTURA_CARGADA_IZQ -1
#define ARBOL_AVL_ALTURA_CARGADA_DER 1
#define ARBOL_AVL_ALTURA_BALANCEADA 0

nodo_arbol_binario *arbol_binario_nodo_allocar(arbol_binario_contexto *ctx,
		int localidades_solicitadas);

void arbol_binario_colectar_datos_recorrido_preoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados);

void arbol_avl_insertar(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_insertar, bool no_indices_repetidos);

int arbol_avl_compara_nodos(nodo_arbol_binario *nodo1,
		nodo_arbol_binario *nodo2);

int caca_int_max(int a, int b);

void arbol_binario_rotar_izq(nodo_arbol_binario **nodo);
void arbol_binario_rotar_der(nodo_arbol_binario **nodo);

void arbol_binario_borrar_nodo(nodo_arbol_binario **raiz,
		tipo_dato valor_a_borrar);

void arbol_binario_colectar_datos_recorrido_inoder(nodo_arbol_binario *raiz,
		tipo_dato *datos_ordenados, int *num_datos_colectados);

void arbol_binario_recorrido_inoder(nodo_arbol_binario *raiz);

void arbol_avl_borrar(nodo_arbol_binario **raiz, tipo_dato valor_a_borrar);

void arbol_avl_borrar_referencia_directa(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_borrar, nodo_arbol_binario *tope);

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		tipo_dato indice, tipo_dato nuevo_valor);

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		tipo_dato *antecesores, nodo_cola_prioridad *nodo_origen);

void cola_prioridad_init(cola_prioridad_contexto *ctx,
		nodo_cola_prioridad *nodos, tipo_dato *valores, tipo_dato *indices,
		int num_nodos, arbol_binario_contexto *actx,
		nodo_arbol_binario **referencias_directas);

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx,
		tipo_dato *valores, int *num_valores);

nodo_cola_prioridad *cola_prioridad_pop(cola_prioridad_contexto *ctx);

bool cola_prioridad_es_vacia(cola_prioridad_contexto *ctx);

void dijkstra_main(void *matrix_distancias, int num_filas,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		grafo_contexto *gctx, tipo_dato *distancias_minimas,
		tipo_dato *antecesores);

char *caca_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo, char *buffer);

void grafo_copia_nodo(const nodo *nodo_origen, nodo *nodo_destino);

bool caca_arreglo_contiene(tipo_dato *arreglo, int tam_arreglo,
		tipo_dato valor_buscado);

void grafo_get_representacion_en_matriz_ordenada(grafo_contexto *ctx,
		void *matrix, int num_columnas);

void grafo_copia_profunda(const grafo_contexto *ctx_origen,
		grafo_contexto *ctx_destino, tipo_dato *indices_a_ignorar,
		int tam_indices_a_ignorar);

void caca_inutiliza_nodo_cola_prioridad(nodo_cola_prioridad *nodos,
		int num_nodos);

void caca_realinea_array(tipo_dato *arreglo, int num_filas,
		int alineacion_actual, int alineacion_nueva);

int arbol_avl_diferencia_alturas_subarboles(nodo_arbol_binario *nodo,
		int tolerancia, bool considerar_balanceado_cargado_der);

int lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas, int *num_columnas,
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
	tipo_dato indice_origen_actual = 0;
	tipo_dato indice_destino_actual = 0;
	tipo_dato distancia_actual = 0;
	tipo_dato *matrix_int = NULL;
	tipo_dato *matrix_distancias = NULL;
	nodo *nuevo_nodo = NULL;
	tipo_dato nodos_registrados[MAX_NODOS] = { falso };

	memset(ctx, 0, sizeof(grafo_contexto));

	matrix_int = matrix;
	matrix_distancias = (tipo_dato *) ctx->matrix_distancias;
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

void arbol_avl_init(arbol_binario_contexto *ctx, tipo_dato *indices,
		tipo_dato *datos, int num_datos,
		nodo_arbol_binario **arreglo_referencias_nodos) {
	int i = 0;
	tipo_dato dato_actual = 0;
	nodo_arbol_binario *nodo_actual = NULL;

	memset((void * ) ctx, 0, sizeof(arbol_binario_contexto));
	memset((void * ) ctx->nodos_disponibles, 0, sizeof(ctx->nodos_disponibles));

	for (i = 0; i < num_datos; i++) {
		if (indices && *(indices + i) == ARBOL_AVL_INDICE_INVALIDO) {
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
	}
}

void arbol_avl_insertar(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_insertar, bool no_indices_repetidos) {
	nodo_arbol_binario *raiz_int = NULL;

	raiz_int = *raiz;

	if (!raiz_int) {
		*raiz = nodo_a_insertar;

		return;
	}

	switch (arbol_avl_compara_nodos(raiz_int, nodo_a_insertar)) {
	case CACA_COMPARACION_IZQ_MENOR:

		if (raiz_int->hijo_der) {

			arbol_avl_insertar(&raiz_int->hijo_der, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			raiz_int->hijo_der = nodo_a_insertar;
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
		}
		break;
	case CACA_COMPARACION_IZQ_MAYOR:

		if (raiz_int->hijo_izq) {

			arbol_avl_insertar(&raiz_int->hijo_izq, nodo_a_insertar,
					no_indices_repetidos);
		} else {
			raiz_int->hijo_izq = nodo_a_insertar;
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
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
				ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_insertar, raiz_int);
			}
		}
		break;
	default:
		perror("NO mames, resultado increible en arbol_avl_insertar!");
		exit(1);
		break;
	}

	ARBOL_AVL_ACTUALIZAR_ALTURA(raiz_int);

	switch (arbol_avl_diferencia_alturas_subarboles(raiz_int, 1, verdadero)) {
	case ARBOL_AVL_ALTURA_CARGADA_IZQ:
		if (ARBOL_AVL_GET_VALOR(
				raiz_int->hijo_izq) < ARBOL_AVL_GET_VALOR(nodo_a_insertar)) {
			arbol_binario_rotar_izq(&raiz_int->hijo_izq);
		}
		arbol_binario_rotar_der(raiz);
		break;
	case ARBOL_AVL_ALTURA_CARGADA_DER:
		if (ARBOL_AVL_GET_VALOR(
				raiz_int->hijo_der) > ARBOL_AVL_GET_VALOR(nodo_a_insertar)) {
			arbol_binario_rotar_der(&raiz_int->hijo_der);
		}
		arbol_binario_rotar_izq(raiz);
		break;
	case ARBOL_AVL_ALTURA_BALANCEADA:
		break;
	default:
		perror("error en altura indeterminada, verga");
		exit(1);
		break;
	}

}

int arbol_avl_compara_nodos(nodo_arbol_binario *nodo1,
		nodo_arbol_binario *nodo2) {
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

int caca_int_max(int a, int b) {
	return (a > b) ? a : b;
}

void arbol_binario_rotar_izq(nodo_arbol_binario **nodo) {
	nodo_arbol_binario *nodo_int = NULL;
	nodo_arbol_binario *hijo_der = NULL;
	nodo_arbol_binario *hijo_der_subarbol_izq = NULL;

	nodo_int = *nodo;

	hijo_der = nodo_int->hijo_der;

	hijo_der_subarbol_izq = hijo_der->hijo_izq;

	nodo_int->hijo_der = hijo_der_subarbol_izq;
	hijo_der->hijo_izq = nodo_int;

	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_der, ARBOL_AVL_GET_PADRE(nodo_int));
	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_der_subarbol_izq, nodo_int);
	ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_int, hijo_der);

	ARBOL_AVL_ACTUALIZAR_ALTURA(nodo_int);
	ARBOL_AVL_ACTUALIZAR_ALTURA(hijo_der);

	*nodo = hijo_der;

}

nodo_arbol_binario *arbol_binario_nodo_allocar(arbol_binario_contexto *ctx,
		int localidades_solicitadas) {
	nodo_arbol_binario *inicio_localidades_allocadas = NULL;
	if ((sizeof(ctx->nodos_disponibles) - ctx->localidades_usadas)
			>= localidades_solicitadas) {
		inicio_localidades_allocadas = ctx->nodos_disponibles
				+ ctx->localidades_usadas;
		ctx->localidades_usadas += localidades_solicitadas;
	}
	return inicio_localidades_allocadas;
}

nodo_arbol_binario *arbol_binario_get_nodo_minimo_valor(
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

	arbol_binario_recorrido_inoder(raiz->hijo_der);
}

void arbol_avl_borrar(nodo_arbol_binario **raiz, tipo_dato valor_a_borrar) {

	nodo_arbol_binario *raiz_int = NULL;
	nodo_arbol_binario *nodo_min = NULL;

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

	if (!*raiz) {
		return;
	}

	ARBOL_AVL_ACTUALIZAR_ALTURA(raiz_int);

	switch (arbol_avl_diferencia_alturas_subarboles(raiz_int, 1, verdadero)) {
	case ARBOL_AVL_ALTURA_CARGADA_IZQ:
		if (arbol_avl_diferencia_alturas_subarboles(raiz_int->hijo_izq, 0,
				falso) == ARBOL_AVL_ALTURA_CARGADA_DER) {
			arbol_binario_rotar_izq(&raiz_int->hijo_izq);
		}
		arbol_binario_rotar_der(raiz);
		break;
	case ARBOL_AVL_ALTURA_CARGADA_DER:
		if (arbol_avl_diferencia_alturas_subarboles(raiz_int->hijo_der, 0,
				verdadero) == ARBOL_AVL_ALTURA_CARGADA_IZQ) {
			arbol_binario_rotar_der(&raiz_int->hijo_der);
		}
		arbol_binario_rotar_izq(raiz);
		break;
	case ARBOL_AVL_ALTURA_BALANCEADA:
		break;
	default:
		break;
	}

}

void arbol_avl_borrar_referencia_directa(nodo_arbol_binario **raiz,
		nodo_arbol_binario *nodo_a_borrar, nodo_arbol_binario *tope) {

	nodo_arbol_binario *ancestro_actual = NULL;
	nodo_arbol_binario *ancestro_actual_tmp = NULL;
	nodo_arbol_binario *nodo_a_borrar_padre = NULL;
	nodo_arbol_binario *nodo_min = NULL;

	nodo_arbol_binario **ancestro_actual_apuntador = NULL;
	nodo_arbol_binario **nodo_a_borrar_ref = NULL;

	if (!nodo_a_borrar) {
		abort();
	}

	if (!(nodo_a_borrar_padre = ARBOL_AVL_GET_PADRE(nodo_a_borrar))) {
		nodo_a_borrar_padre = NULL;
		nodo_a_borrar_ref = raiz;

	} else {

		nodo_a_borrar_ref =
				nodo_a_borrar->valor < (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_izq :
				nodo_a_borrar->valor > (nodo_a_borrar_padre)->valor ?
						&nodo_a_borrar_padre->hijo_der :
				nodo_a_borrar->indice
						== ARBOL_AVL_GET_INDICE(nodo_a_borrar_padre->hijo_izq) ?
						&nodo_a_borrar_padre->hijo_izq :
						&nodo_a_borrar_padre->hijo_der;

	}

	ancestro_actual = nodo_a_borrar->padre;
	ancestro_actual_apuntador = &nodo_a_borrar->padre;

	if (!nodo_a_borrar->hijo_izq) {

		ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_der,
				ancestro_actual);
		*nodo_a_borrar_ref = nodo_a_borrar->hijo_der;
	} else {
		if (!nodo_a_borrar->hijo_der) {

			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_izq,
					ancestro_actual);
			*nodo_a_borrar_ref = nodo_a_borrar->hijo_izq;
		} else {
			nodo_min = arbol_binario_get_nodo_minimo_valor(
					nodo_a_borrar->hijo_der);

			arbol_avl_borrar_referencia_directa(raiz, nodo_min, nodo_a_borrar);
			ARBOL_BINARIO_ACTUALIZAR_HIJO_IZQ(nodo_min,
					nodo_a_borrar->hijo_izq);
			ARBOL_BINARIO_ACTUALIZAR_HIJO_DER(nodo_min,
					nodo_a_borrar->hijo_der);
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_min, nodo_a_borrar->padre);
			nodo_min->altura = ARBOL_AVL_GET_ALTURA(nodo_a_borrar);

			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_izq, nodo_min);
			ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_a_borrar->hijo_der, nodo_min);

			*nodo_a_borrar_ref = nodo_min;
			ancestro_actual = nodo_min;
		}
	}

	do {
		if (!ARBOL_AVL_GET_PADRE(nodo_a_borrar)) {

			break;
		}

		if (tope && ancestro_actual == tope) {

			return;
		}
		ancestro_actual_tmp = ancestro_actual->padre;

		if (ARBOL_AVL_GET_PADRE(ancestro_actual)) {
			if (ARBOL_AVL_GET_VALOR(
					ancestro_actual)
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

			if (arbol_avl_diferencia_alturas_subarboles(
					ancestro_actual->hijo_izq, 0,
					falso) == ARBOL_AVL_ALTURA_CARGADA_DER) {

				arbol_binario_rotar_izq(&ancestro_actual->hijo_izq);
			}
			arbol_binario_rotar_der(ancestro_actual_apuntador);
			break;
		case ARBOL_AVL_ALTURA_CARGADA_DER:

			if (arbol_avl_diferencia_alturas_subarboles(
					ancestro_actual->hijo_der, 0,
					verdadero) == ARBOL_AVL_ALTURA_CARGADA_IZQ) {

				arbol_binario_rotar_der(&ancestro_actual->hijo_der);
			}
			arbol_binario_rotar_izq(ancestro_actual_apuntador);
			break;
		case ARBOL_AVL_ALTURA_BALANCEADA:

			break;
		default:
			break;
		}

		ancestro_actual = ancestro_actual_tmp;
	} while (ancestro_actual);

}

void cola_prioridad_modificar_valor_nodo(cola_prioridad_contexto *cpctx,
		tipo_dato indice, tipo_dato nuevo_valor) {
	nodo_arbol_binario *referencia_directa = NULL;
	nodo_arbol_binario **referencias_directas = NULL;

	referencias_directas = cpctx->referencias_directas_por_indice;

	referencia_directa = *(referencias_directas + indice);

	referencia_directa->valor = nuevo_valor;

}

void dijkstra_relaxar_nodo(grafo_contexto *gctx, cola_prioridad_contexto *cpctx,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		tipo_dato *antecesores, nodo_cola_prioridad *nodo_origen) {
	tipo_dato dist_origen_dest = 0;

	tipo_dato *matrix_distancias = NULL;

	nodo_arbol_binario *distancia_min_origen = NULL;
	nodo_arbol_binario *distancia_min_destino = NULL;
	nodo_arbol_binario **distancias_minimas = NULL;

	matrix_distancias = (tipo_dato*) gctx->matrix_distancias;
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
void dijkstra_main(void *matrix_distancias, int num_filas,
		tipo_dato ind_nodo_origen, tipo_dato ind_nodo_destino,
		grafo_contexto *gctx, tipo_dato *distancias_minimas,
		tipo_dato *antecesores) {

	int i, j;

	int contador = 0;
	int num_nodos = 0;

	tipo_dato indice_origen_actual = 0;
	tipo_dato indice_destino_actual = 0;
	tipo_dato distancia_actual = 0;
	tipo_dato max_indice = 0;
	tipo_dato *matrix_distancias_int = NULL;

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
	matrix_distancias_int = (tipo_dato *) gctx_int->matrix_distancias;

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
			distancia_actual = (tipo_dato) *(matrix_distancias_int
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
		nodo_cola_prioridad *nodos, tipo_dato *valores, tipo_dato *indices,
		int num_nodos, arbol_binario_contexto *actx,
		nodo_arbol_binario **referencias_directas) {
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
	tipo_dato indice_min = 0;
	tipo_dato valor_min = MAX_VALOR;
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

void cola_prioridad_get_valores(cola_prioridad_contexto *ctx,
		tipo_dato *valores, int *num_valores) {
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
		grafo_contexto *ctx_destino, tipo_dato *indices_a_ignorar,
		int tam_indices_a_ignorar) {
	int i, j;
	tipo_dato indice_nodo_origen_actual = 0;

	tipo_dato *matrix_origen = NULL;
	tipo_dato *matrix_destino = NULL;

	nodo *nodo_origen_principal_actual = NULL;
	nodo *nodo_destino_principal_actual = NULL;
	nodo *nodo_destino_principal_previo = NULL;

	matrix_origen = (tipo_dato*) ctx_origen->matrix_distancias;
	matrix_destino = (tipo_dato *) ctx_destino->matrix_distancias;
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

bool caca_arreglo_contiene(tipo_dato *arreglo, int tam_arreglo,
		tipo_dato valor_buscado) {
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

void caca_realinea_array(tipo_dato *arreglo, int num_filas,
		int alineacion_actual, int alineacion_nueva) {
	int i, j;
	for (i = 0; i < num_filas; i++) {
		for (j = 0; j < alineacion_nueva; j++) {
			*(arreglo + i * alineacion_nueva + j) = *(arreglo
					+ i * alineacion_actual + j);
		}

	}
}

int arbol_avl_diferencia_alturas_subarboles(nodo_arbol_binario *nodo,
		int tolerancia, bool considerar_balanceado_cargado_der) {
	int diferencia_alturas = 0;
	diferencia_alturas = ARBOL_AVL_GET_ALTURA(
			nodo->hijo_izq) - ARBOL_AVL_GET_ALTURA(nodo->hijo_der);
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

void arbol_binario_rotar_der(nodo_arbol_binario **nodo) {
	nodo_arbol_binario *nodo_int = NULL;
	nodo_arbol_binario *hijo_izq = NULL;
	nodo_arbol_binario *hijo_izq_subarbol_der = NULL;

	nodo_int = *nodo;

	hijo_izq = nodo_int->hijo_izq;

	hijo_izq_subarbol_der = hijo_izq->hijo_der;

	nodo_int->hijo_izq = hijo_izq_subarbol_der;
	hijo_izq->hijo_der = nodo_int;

	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_izq, ARBOL_AVL_GET_PADRE(nodo_int));
	ARBOL_BINARIO_ACTUALIZAR_PADRE(hijo_izq_subarbol_der, nodo_int);
	ARBOL_BINARIO_ACTUALIZAR_PADRE(nodo_int, hijo_izq);

	ARBOL_AVL_ACTUALIZAR_ALTURA(nodo_int);
	ARBOL_AVL_ACTUALIZAR_ALTURA(hijo_izq);

	*nodo = hijo_izq;

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

char *caca_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;

	memset(buffer, 0, 1000);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%ld",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	return ap_buffer;
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

	es_array = verdadero;

	if (!num_columnas && !num_columnas_fijo) {

	}

	num_columnas_actual = num_columnas_fijo ? num_columnas_fijo : 0;

	for (i = 0; i < num_filas; i++) {

		if (num_columnas) {
			num_columnas_actual = *(num_columnas + i);
		}
		if (num_columnas_fijo) {
			num_columnas_actual = num_columnas_fijo;
		}
		for (j = 0; j < num_columnas_actual; j++) {
			if (es_array) {
				numero_actual = *(matrix_array + i * num_columnas_actual + j);
			} else {

				numero_actual = *(*(matrix_pointer + i) + j);
			}
			if (numero_actual) {

			}
		}
	}

	if (num_columnas) {
		for (i = 0; i < num_filas; i++) {

		}
	} else {

	}

	return 0;
}

bool from_stack(void *ptr) {
	return verdadero;
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

	while (nodo_actual) {
		nodo_adjacente_actual = nodo_actual;
		GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_INDICE, verdadero);
		contador_columnas = 0;

		GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
				contador_filas, contador_columnas);

		*apuntador_a_posicion_en_matrix = nodo_actual->indice;

		contador_columnas++;

		while (nodo_adjacente_actual) {

			GRAFO_GET_APUNTADOR_POSICION_MATRIX(apuntador_a_posicion_en_matrix,
					contador_filas, contador_columnas);

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

			*apuntador_a_posicion_en_matrix = nodo_adjacente_actual->indice;

			GRAFO_AVANZAR_NODO(nodo_adjacente_actual, GRAFO_DISTANCIA,
					verdadero);
			contador_columnas++;
		}

		nodo_actual = nodo_actual->siguiente;

		contador_filas++;
	}

}

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

void dijkstra_calcula_ruta(tipo_dato *antecesores, int tam_antecesores,
		tipo_dato posicion_inicial, tipo_dato posicion_destino, tipo_dato *ruta,
		int *tam_ruta);

int escape_cabron_determina_nodos_viables(void *matrix_aristas, int num_filas,
		grafo_contexto *grafo_viable_ctx, tipo_dato posicion_incomoda,
		tipo_dato posicion_inicial,
		tipo_dato *distancia_posicion_incomoda_a_inicial) {

	int num_nodos = 0;
	int contador_nodos_ruta_maldita = 0;
	int contador_nodos_recorridos = 0;
	tipo_dato ancestro_actual = 0;
	grafo_contexto grafo_inicial_ctx;

	char *buffer = NULL;
	tipo_dato *distancias_minimas = NULL, *antecesores = NULL;
	tipo_dato *ruta_maldita;

	buffer = malloc(MAX_TAM_CADENA * sizeof(char));

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

	if (!ruta_maldita) {
		perror("no se consigio memoria para ruta_maldita");
		exit(EXIT_FAILURE);
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

double escape_cabron_encuentra_escape(void *matrix_aristas, int num_filas,
		tipo_dato posicion_polis, tipo_dato posicion_ratas,
		tipo_dato *salidas_carretera, int num_salidas_carretera) {
	int i, j;
	int num_nodos = 0;
	int tam_ruta_a_salida_actual = 0;
	double maxima_velocidad = 0;
	double tiempo_polis = 0;
	double velocidad_minima = (double) MAX_VALOR;
	tipo_dato salida_carretera_actual = 0;
	tipo_dato distancia_salida_carretera_actual = 0;
	tipo_dato distancia_polis_a_ratas = 0;
	tipo_dato distancia_recorrida_polis = 0;
	tipo_dato min_distancia_salida = MAX_VALOR;
	tipo_dato ind_min_distancia_salida = 0;
	tipo_dato ind_nodo_actual = 0;
	tipo_dato distancia_poli_a_nodo_actual;
	tipo_dato distancia_min_poli_a_nodo_actual = MAX_VALOR;
	tipo_dato ind_distancia_min_poli_a_nodo_actual = MAX_VALOR;
	char *buffer = NULL;
	tipo_dato *distancias_minimas_bandido = NULL;
	tipo_dato *antecesores_bandido = NULL;
	tipo_dato *distancias_minimas_polis = NULL;
	tipo_dato *antecesores_polis = NULL;
	nodo_cola_prioridad *nodo_salida_mas_cercana = NULL;
	grafo_contexto *grafo_bandido_ctx = NULL;
	grafo_contexto *grafo_poli_ctx = NULL;
	tipo_dato *ruta_a_salida_actual = NULL;

	buffer = calloc(1000, sizeof(char));

	caca_imprime_matrix(matrix_aristas, num_filas, NULL, 3);

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

	distancias_minimas_bandido = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!distancias_minimas_bandido) {
		perror("no se consigio memoria para distancias bandido");
		abort();
	}
	antecesores_bandido = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!antecesores_bandido) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	distancias_minimas_polis = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!distancias_minimas_polis) {
		perror("no se consigio memoria para distancias poli");
		abort();
	}
	antecesores_polis = calloc((num_nodos + 1), sizeof(tipo_dato));
	if (!antecesores_polis) {
		perror("no se consigio memoria para antecesores");
		abort();
	}

	ruta_a_salida_actual = calloc(num_nodos + 1, sizeof(tipo_dato));
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
		//TODO: Si ya se empieza en la salida

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
	if (velocidad_minima == (double) MAX_VALOR) {
		return 0;
	}

	return velocidad_minima;
}

double escape_cabron_main() {
	double maxima_velocidad = 0;

	int num_aristas = 0;

	tipo_dato num_nodos = 0, num_salidas = 0;
	tipo_dato posicion_ratas = 0, posicion_polis = 0;

	tipo_dato *datos_escape_mem = NULL;

	tipo_dato *datos_escape = (tipo_dato *) datos_escape_mem;
	tipo_dato *inicio_aristas = NULL;
	tipo_dato *salidas = NULL;

	datos_escape_mem = calloc(
			ESCAPE_CABRON_MAX_FILAS_INPUT * ESCAPE_CABRON_MAX_COLS_INPUT,
			sizeof(tipo_dato));
	if (!datos_escape_mem) {
		perror("no se obtubo memoria para los datos del escape");
		abort();
	}
	datos_escape = datos_escape_mem;

	lee_matrix_long_stdin((tipo_dato *) datos_escape, &num_aristas, NULL,
			ESCAPE_CABRON_MAX_FILAS_INPUT, ESCAPE_CABRON_MAX_COLS_INPUT);

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

	return maxima_velocidad;
}

void dijkstra_calcula_ruta(tipo_dato *antecesores, int tam_antecesores,
		tipo_dato posicion_inicial, tipo_dato posicion_destino,
		tipo_dato *ruta_maldita, int *tam_ruta) {
	int contador_nodos_recorridos = 0;
	int contador_nodos_ruta_maldita = 0;
	tipo_dato ancestro_actual = 0;

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
	float resultado = 0;

	resultado = escape_cabron_main();
	if (resultado) {
		printf("%.10f\n", resultado);
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
