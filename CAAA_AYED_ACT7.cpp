#include <stdio.h>
#include <stdlib.h>

/* ===== ESTRUCTURA DEL NODO ===== */
typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
} Nodo;

/* ===== PROTOTIPOS ===== */
void menuPrincipal(void);
void menuMostrar(Nodo *raiz);
void menuInformacion(Nodo *raiz);

Nodo *crearNodo(int valor);
Nodo *insertarNodo(Nodo *raiz, int valor);
Nodo *buscarNodo(Nodo *raiz, int valor);
void recorridoInOrden(Nodo *raiz);
void recorridoPreOrden(Nodo *raiz);
void recorridoPostOrden(Nodo *raiz);
int alturaArbol(Nodo *raiz);        /* retorna número de niveles (0 si vacío) */
int contarHojas(Nodo *raiz);
void eliminarArbol(Nodo **raiz);    /* libera memoria y deja *raiz = NULL */

int leerEnteroValidado(const char *mensaje);

/* ===== MAIN ===== */
int main(void) {
    menuPrincipal();
    return 0;
}

/* ===== IMPLEMENTACIÓN DEL MENÚ PRINCIPAL ===== */
void menuPrincipal(void) {
    Nodo *raiz = NULL;
    int opcion;

    do {
        printf("\n===== MENU ABB =====\n");
        printf("1. Agregar\n");
        printf("2. Buscar\n");
        printf("3. Mostrar (InOrden / PreOrden / PostOrden)\n");
        printf("4. Informacion (Altura / Cantidad de hojas)\n");
        printf("5. Eliminar todo el arbol\n");
        printf("6. Salir\n");
        opcion = leerEnteroValidado("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                int v = leerEnteroValidado("Valor a insertar: ");
                /* Insertar evita duplicados */
                raiz = insertarNodo(raiz, v);
            } break;
            case 2: {
                int v = leerEnteroValidado("Valor a buscar: ");
                Nodo *res = buscarNodo(raiz, v);
                if (res) printf("Valor %d encontrado en el arbol.\n", v);
                else printf("Valor %d NO encontrado.\n", v);
            } break;
            case 3:
                menuMostrar(raiz);
                break;
            case 4:
                menuInformacion(raiz);
                break;
            case 5:
                eliminarArbol(&raiz);
                printf("Arbol eliminado completamente.\n");
                break;
            case 6:
                eliminarArbol(&raiz);
                printf("Saliendo. Arbol liberado si existia.\n");
                break;
            default:
                printf("Opcion no valida, intente de nuevo.\n");
        }
    } while (opcion != 6);
}

/* ===== SUBMENU Mostrar ===== */
void menuMostrar(Nodo *raiz) {
    int opcion;
    do {
        printf("\n--- Mostrar ---\n");
        printf("1. InOrden\n");
        printf("2. PreOrden\n");
        printf("3. PostOrden\n");
        printf("4. Regresar\n");
        opcion = leerEnteroValidado("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                printf("Recorrido InOrden: ");
                recorridoInOrden(raiz);
                printf("\n");
                break;
            case 2:
                printf("Recorrido PreOrden: ");
                recorridoPreOrden(raiz);
                printf("\n");
                break;
            case 3:
                printf("Recorrido PostOrden: ");
                recorridoPostOrden(raiz);
                printf("\n");
                break;
            case 4:
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);
}

/* ===== SUBMENÚ Informacion ===== */
void menuInformacion(Nodo *raiz) {
    int opcion;
    do {
        printf("\n--- Informacion ---\n");
        printf("1. Altura del arbol\n");
        printf("2. Cantidad de hojas\n");
        printf("3. Regresar\n");
        opcion = leerEnteroValidado("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                int h = alturaArbol(raiz);
                printf("Altura del arbol (niveles): %d\n", h);
            } break;
            case 2: {
                int hojas = contarHojas(raiz);
                printf("Cantidad de hojas: %d\n", hojas);
            } break;
            case 3:
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 3);
}

/* ===== FUNCIONES DEL ABB ===== */

/* Crear un nuevo nodo con valor dado.*/
Nodo *crearNodo(int valor) {
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (n == NULL) {
        printf("Error: memoria insuficiente.\n");
        return NULL;
    }
    n->dato = valor;
    n->izq = NULL;
    n->der = NULL;
    return n;
}

/* Insertar nodo en ABB.
   Si el valor ya existe, no inserta y notifica. Retorna la (posible) nueva raiz. */
Nodo *insertarNodo(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        Nodo *nuevo = crearNodo(valor);
        if (nuevo) printf("Insertado: %d\n", valor);
        return nuevo;
    }
    if (valor < raiz->dato) {
        raiz->izq = insertarNodo(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = insertarNodo(raiz->der, valor);
    } else {
        printf("Valor %d ya existe. No se insertan duplicados.\n", valor);
    }
    return raiz;
}

/* Buscar nodo por valor. Retorna puntero al nodo o NULL si no existe. */
Nodo *buscarNodo(Nodo *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor == raiz->dato) return raiz;
    if (valor < raiz->dato) return buscarNodo(raiz->izq, valor);
    return buscarNodo(raiz->der, valor);
}

/* Recorridos (recursivos) */
void recorridoInOrden(Nodo *raiz) {
    if (raiz == NULL) return;
    recorridoInOrden(raiz->izq);
    printf("%d ", raiz->dato);
    recorridoInOrden(raiz->der);
}

void recorridoPreOrden(Nodo *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dato);
    recorridoPreOrden(raiz->izq);
    recorridoPreOrden(raiz->der);
}

void recorridoPostOrden(Nodo *raiz) {
    if (raiz == NULL) return;
    recorridoPostOrden(raiz->izq);
    recorridoPostOrden(raiz->der);
    printf("%d ", raiz->dato);
}

/* Altura: definimos altura como número de niveles.
   - Arbol vacío -> 0
   - Solo raiz -> 1
*/
int alturaArbol(Nodo *raiz) {
    if (raiz == NULL) return 0;
    int hi = alturaArbol(raiz->izq);
    int hd = alturaArbol(raiz->der);
    return (hi > hd ? hi : hd) + 1;
}

/* Contar hojas: nodos sin hijos */
int contarHojas(Nodo *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->izq == NULL && raiz->der == NULL) return 1;
    return contarHojas(raiz->izq) + contarHojas(raiz->der);
}

/* Eliminar todo el arbol liberando memoria (postorden). Pone *raiz = NULL */
void eliminarArbol(Nodo **raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    eliminarArbol(&((*raiz)->izq));
    eliminarArbol(&((*raiz)->der));
    free(*raiz);
    *raiz = NULL;
}

/* ===== FUNCIONES AUXILIARES ===== */

/* Leer entero con validación básica (evita caracteres no numéricos) */
int leerEnteroValidado(const char *mensaje) {
    int v;
    int r;
    do {
        printf("%s", mensaje);
        r = scanf("%d", &v);
        if (r != 1) {
            printf("Entrada invalida. Intente nuevamente.\n");
            while (getchar() != '\n'); /* limpiar buffer */
        } else break;
    } while (1);
    return v;
}