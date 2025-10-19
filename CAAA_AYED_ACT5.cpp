#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura básica para todas las listas circulares
typedef struct Nodo
{
    int clave;
    char color[10];
    struct Nodo *sig;
} Nodo;

// Prototipos globales
void menuPrincipal();

// ---- Parte A: Lista Circular ----
void menuListaCircular();
void agregarNodo(Nodo **inicio, int valor);
void eliminarNodo(Nodo **inicio, int valor);
Nodo *buscarNodo(Nodo *inicio, int valor);
void imprimirLista(Nodo *inicio);
void liberarLista(Nodo **inicio);

// ---- Parte B: Papa Caliente ----
void menuPapaCaliente();
void papaCaliente(int n, int pasos);

// ---- Parte C: Ruleta Americana ----
void menuRuleta();
void crearRuleta(Nodo **inicio);
void mostrarRuleta(Nodo *inicio);
void girarRuleta(Nodo *inicio, int apuesta);

int main()
{
    srand(time(NULL));
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
        printf("1. Lista Circular\n");
        printf("2. Simulación: Papa Caliente\n");
        printf("3. Simulación: Ruleta Americana\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menuListaCircular();
            break;
        case 2:
            menuPapaCaliente();
            break;
        case 3:
            menuRuleta();
            break;
        case 4:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida.\n");
        }
    } while (opcion != 4);
}

/* ============================================================
   PARTE A: LISTA CIRCULAR
   ============================================================ */
void menuListaCircular()
{
    Nodo *inicio = NULL;
    int opcion, valor;
    do
    {
        printf("\n--- MENU LISTA CIRCULAR ---\n");
        printf("1. Agregar\n2. Eliminar\n3. Buscar\n4. Imprimir\n5. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingresa un valor entero: ");
            scanf("%d", &valor);
            agregarNodo(&inicio, valor);
            break;
        case 2:
            printf("Ingresa el valor a eliminar: ");
            scanf("%d", &valor);
            eliminarNodo(&inicio, valor);
            break;
        case 3:
            printf("Ingresa el valor a buscar: ");
            scanf("%d", &valor);
            if (buscarNodo(inicio, valor))
                printf("El valor %d se encuentra en la lista.\n", valor);
            else
                printf("El valor %d no está en la lista.\n", valor);
            break;
        case 4:
            imprimirLista(inicio);
            break;
        case 5:
            liberarLista(&inicio);
            printf("Memoria liberada. Regresando...\n");
            break;
        default:
            printf("Opción no válida.\n");
        }
    } while (opcion != 5);
}

void agregarNodo(Nodo **inicio, int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (!nuevo)
        return;
    nuevo->clave = valor;
    nuevo->sig = nuevo;

    if (*inicio == NULL)
    {
        *inicio = nuevo;
    }
    else
    {
        Nodo *aux = *inicio;
        while (aux->sig != *inicio)
            aux = aux->sig;
        aux->sig = nuevo;
        nuevo->sig = *inicio;
    }
    printf("Nodo %d agregado correctamente.\n", valor);
}

void eliminarNodo(Nodo **inicio, int valor)
{
    if (*inicio == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *actual = *inicio, *anterior = NULL;
    do
    {
        if (actual->clave == valor)
            break;
        anterior = actual;
        actual = actual->sig;
    } while (actual != *inicio);

    if (actual->clave != valor)
    {
        printf("El valor %d no existe.\n", valor);
        return;
    }

    if (actual == *inicio && actual->sig == *inicio)
    {
        *inicio = NULL;
    }
    else
    {
        if (actual == *inicio)
            *inicio = actual->sig;
        anterior->sig = actual->sig;
    }
    free(actual);
    printf("Nodo %d eliminado.\n", valor);
}

Nodo *buscarNodo(Nodo *inicio, int valor)
{
    if (inicio == NULL)
        return NULL;
    Nodo *aux = inicio;
    do
    {
        if (aux->clave == valor)
            return aux;
        aux = aux->sig;
    } while (aux != inicio);
    return NULL;
}

void imprimirLista(Nodo *inicio)
{
    if (inicio == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *aux = inicio;
    printf("Lista circular: ");
    do
    {
        printf("%d -> ", aux->clave);
        aux = aux->sig;
    } while (aux != inicio);
    printf("(inicio)\n");
}

void liberarLista(Nodo **inicio)
{
    if (*inicio == NULL)
        return;
    Nodo *actual = *inicio, *sig;
    do
    {
        sig = actual->sig;
        free(actual);
        actual = sig;
    } while (actual != *inicio);
    *inicio = NULL;
}

/* ============================================================
   PARTE B: PAPA CALIENTE
   ============================================================ */
void menuPapaCaliente()
{
    int n, pasos;
    printf("\n--- SIMULACIÓN: PAPA CALIENTE ---\n");
    printf("Número de jugadores: ");
    scanf("%d", &n);
    printf("Número de pases antes de eliminar: ");
    scanf("%d", &pasos);
    papaCaliente(n, pasos);
}

void papaCaliente(int n, int pasos)
{
    if (n <= 0)
        return;

    Nodo *inicio = NULL, *aux, *prev = NULL;
    for (int i = 1; i <= n; i++)
    {
        Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
        nuevo->clave = i;
        nuevo->sig = NULL;
        if (inicio == NULL)
            inicio = nuevo;
        else
            prev->sig = nuevo;
        prev = nuevo;
    }
    prev->sig = inicio; // Hacer circular

    printf("\nJugadores: ");
    imprimirLista(inicio);

    Nodo *actual = inicio;
    while (actual->sig != actual)
    {
        for (int i = 1; i < pasos; i++)
        {
            prev = actual;
            actual = actual->sig;
        }
        printf("El jugador %d tiene la papa y queda eliminado.\n", actual->clave);
        prev->sig = actual->sig;
        free(actual);
        actual = prev->sig;
    }
    printf("\n¡El ganador es el jugador %d!\n", actual->clave);
    free(actual);
}

/* ============================================================
   PARTE C: RULETA AMERICANA
   ============================================================ */
void menuRuleta()
{
    Nodo *ruleta = NULL;
    crearRuleta(&ruleta);
    int apuesta;
    char seguir;
    do
    {
        printf("\n--- RULETA AMERICANA ---\n");
        mostrarRuleta(ruleta);
        printf("Apuesta a un número (0 a 36, o 37 para 00): ");
        scanf("%d", &apuesta);
        girarRuleta(ruleta, apuesta);
        printf("¿Jugar otra vez? (s/n): ");
        scanf(" %c", &seguir);
    } while (seguir == 's' || seguir == 'S');
    liberarLista(&ruleta);
}

void crearRuleta(Nodo **inicio)
{
    // Números de la ruleta americana (00 se representa como 37)
    int numeros[] = {
        0, 37, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
    };
    int total = 38;

    // Colores correspondientes a cada número (rojo, negro o verde)
    const char *colores[] = {
        "VERDE", "VERDE", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO",
        "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO",
        "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO",
        "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO", "ROJO", "NEGRO"
    };

    // Crear los nodos de la ruleta
    for (int i = 0; i < total; i++)
    {
        Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
        if (nuevo == NULL)
        {
            printf("Error: no se pudo asignar memoria.\n");
            return;
        }

        nuevo->clave = numeros[i];
        strcpy(nuevo->color, colores[i]); // Copia el color correspondiente

        if (*inicio == NULL)
        {
            *inicio = nuevo;
            nuevo->sig = nuevo; // Primer nodo se apunta a sí mismo
        }
        else
        {
            Nodo *aux = *inicio;
            while (aux->sig != *inicio)
                aux = aux->sig;
            aux->sig = nuevo;
            nuevo->sig = *inicio; // Mantiene la circularidad
        }
    }

    printf("Ruleta creada exitosamente con %d números.\n", total);
}

void mostrarRuleta(Nodo *inicio)
{
    if (!inicio)
        return;
    Nodo *aux = inicio;
    printf("Números de la ruleta:\n");
    do
    {
        if (aux->clave == 37)
            printf("00(%s) ", aux->color);
        else
            printf("%d(%s) ", aux->clave, aux->color);
        aux = aux->sig;
    } while (aux != inicio);
    printf("\n");
}

void girarRuleta(Nodo *inicio, int apuesta)
{
    if (!inicio)
        return;
    int vueltas = rand() % 60 + 10;
    Nodo *aux = inicio;
    printf("Girando la ruleta...\n");
    for (int i = 0; i < vueltas; i++)
    {
        if (aux->clave == 37)
            printf("00 ");
        else
            printf("%d ", aux->clave);
        aux = aux->sig;
    }
    printf("\n");
    printf("Número ganador: ");
    if (aux->clave == 37)
        printf("00 (%s)\n", aux->color);
    else
        printf("%d (%s)\n", aux->clave, aux->color);

    if (aux->clave == apuesta)
        printf("¡Felicidades! Has ganado.\n");
    else
        printf("Perdiste. Intenta de nuevo.\n");
}