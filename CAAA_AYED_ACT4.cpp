#include <stdio.h>
#include <stdlib.h>

// Definición de nodo para lista simple
typedef struct Nodo
{
    int dato;
    struct Nodo *sig;
} Nodo;

// Prototipos generales
void menuPrincipal();

// ---- LISTA ABIERTA ----
void menuListaAbierta();
void agregarAbierta(Nodo **cabeza, int valor);
void eliminarAbierta(Nodo **cabeza, int valor);
void buscarAbierta(Nodo *cabeza, int valor);
void imprimirAbierta(Nodo *cabeza);
void liberarLista(Nodo **cabeza);

// ---- LISTA ORDENADA ----
void menuListaOrdenada();
void agregarOrdenada(Nodo **cabeza, int valor);
void eliminarOrdenada(Nodo **cabeza, int valor);
void buscarOrdenada(Nodo *cabeza, int valor);
void imprimirOrdenada(Nodo *cabeza);

int main()
{
    menuPrincipal();
    return 0;
}

/* ============================================================
   MENÚ PRINCIPAL
   ============================================================ */
void menuPrincipal()
{
    int opcion;
    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Lista Simple Abierta\n");
        printf("2. Lista Simple Ordenada\n");
        printf("3. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menuListaAbierta();
            break;
        case 2:
            menuListaOrdenada();
            break;
        case 3:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida.\n");
        }
    } while (opcion != 3);
}

/* ============================================================
   LISTA ABIERTA
   ============================================================ */
void menuListaAbierta()
{
    Nodo *cabeza = NULL;
    int opcion, valor;
    do
    {
        printf("\n--- MENU LISTA ABIERTA ---\n");
        printf("1. Agregar\n2. Eliminar\n3. Buscar\n4. Imprimir\n5. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese valor: ");
            scanf("%d", &valor);
            agregarAbierta(&cabeza, valor);
            break;
        case 2:
            printf("Ingrese valor a eliminar: ");
            scanf("%d", &valor);
            eliminarAbierta(&cabeza, valor);
            break;
        case 3:
            printf("Ingrese valor a buscar: ");
            scanf("%d", &valor);
            buscarAbierta(cabeza, valor);
            break;
        case 4:
            imprimirAbierta(cabeza);
            break;
        case 5:
            liberarLista(&cabeza);
            printf("Liberando memoria y regresando...\n");
            break;
        default:
            printf("Opción no válida.\n");
        }
    } while (opcion != 5);
}

void agregarAbierta(Nodo **cabeza, int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (!nuevo)
    {
        printf("Error de memoria.\n");
        return;
    }
    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (*cabeza == NULL)
    {
        *cabeza = nuevo;
    }
    else
    {
        Nodo *aux = *cabeza;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
    printf("Se agregó %d a la lista abierta.\n", valor);
}

void eliminarAbierta(Nodo **cabeza, int valor)
{
    Nodo *actual = *cabeza, *anterior = NULL;
    while (actual != NULL && actual->dato != valor)
    {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == NULL)
    {
        printf("El valor %d no se encontró.\n", valor);
        return;
    }
    if (anterior == NULL)
    {
        *cabeza = actual->sig;
    }
    else
    {
        anterior->sig = actual->sig;
    }
    free(actual);
    printf("Se eliminó %d de la lista abierta.\n", valor);
}

void buscarAbierta(Nodo *cabeza, int valor)
{
    Nodo *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->dato == valor)
        {
            printf("El valor %d se encuentra en la lista.\n", valor);
            return;
        }
        aux = aux->sig;
    }
    printf("El valor %d no está en la lista.\n", valor);
}

void imprimirAbierta(Nodo *cabeza)
{
    if (cabeza == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *aux = cabeza;
    printf("Lista abierta: ");
    while (aux != NULL)
    {
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }
    printf("NULL\n");
}

void liberarLista(Nodo **cabeza)
{
    Nodo *aux;
    while (*cabeza != NULL)
    {
        aux = *cabeza;
        *cabeza = (*cabeza)->sig;
        free(aux);
    }
}

/* ============================================================
   LISTA ORDENADA
   ============================================================ */
void menuListaOrdenada()
{
    Nodo *cabeza = NULL;
    int opcion, valor;
    do
    {
        printf("\n--- MENU LISTA ORDENADA ---\n");
        printf("1. Agregar\n2. Eliminar\n3. Buscar\n4. Imprimir\n5. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese valor: ");
            scanf("%d", &valor);
            agregarOrdenada(&cabeza, valor);
            break;
        case 2:
            printf("Ingrese valor a eliminar: ");
            scanf("%d", &valor);
            eliminarOrdenada(&cabeza, valor);
            break;
        case 3:
            printf("Ingrese valor a buscar: ");
            scanf("%d", &valor);
            buscarOrdenada(cabeza, valor);
            break;
        case 4:
            imprimirOrdenada(cabeza);
            break;
        case 5:
            liberarLista(&cabeza);
            printf("Liberando memoria y regresando...\n");
            break;
        default:
            printf("Opción no válida.\n");
        }
    } while (opcion != 5);
}

void agregarOrdenada(Nodo **cabeza, int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (!nuevo)
    {
        printf("Error de memoria.\n");
        return;
    }
    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (*cabeza == NULL || (*cabeza)->dato >= valor)
    {
        nuevo->sig = *cabeza;
        *cabeza = nuevo;
    }
    else
    {
        Nodo *aux = *cabeza;
        while (aux->sig != NULL && aux->sig->dato < valor)
        {
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
    }
    printf("Se agregó %d en orden a la lista.\n", valor);
}

void eliminarOrdenada(Nodo **cabeza, int valor)
{
    Nodo *actual = *cabeza, *anterior = NULL;
    while (actual != NULL && actual->dato != valor)
    {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == NULL)
    {
        printf("El valor %d no se encontró.\n", valor);
        return;
    }
    if (anterior == NULL)
    {
        *cabeza = actual->sig;
    }
    else
    {
        anterior->sig = actual->sig;
    }
    free(actual);
    printf("Se eliminó %d de la lista ordenada.\n", valor);
}

void buscarOrdenada(Nodo *cabeza, int valor)
{
    Nodo *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->dato == valor)
        {
            printf("El valor %d se encuentra en la lista.\n", valor);
            return;
        }
        aux = aux->sig;
    }
    printf("El valor %d no está en la lista.\n", valor);
}

void imprimirOrdenada(Nodo *cabeza)
{
    if (cabeza == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *aux = cabeza;
    printf("Lista ordenada: ");
    while (aux != NULL)
    {
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }
    printf("NULL\n");
}