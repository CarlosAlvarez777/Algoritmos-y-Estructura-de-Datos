#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
   Definición de la estructura para una canción.
   Cada nodo de la lista contiene:
   - El título de la canción.
   - Un puntero al siguiente nodo.
*/
typedef struct Cancion {
    char titulo[50];             
    struct Cancion *siguiente;   
} Cancion;

/* 
   Estructura de la lista de reproducción.
   Contiene:
   - Puntero a la primera canción (head).
   - Puntero a la canción actual (actual).
*/
typedef struct {
    Cancion *head;   
    Cancion *actual; 
} ListaReproduccion;

/* Prototipos de funciones */
Cancion* crearCancion(char titulo[]);
void inicializarLista(ListaReproduccion *lista);
void agregarCancion(ListaReproduccion *lista, char titulo[]);
void eliminarCancion(ListaReproduccion *lista, char titulo[]);
void mostrarLista(ListaReproduccion *lista);
void siguiente(ListaReproduccion *lista);
void buscarCancion(ListaReproduccion *lista, char titulo[]);
void menu();

/* 
   Funcion principal.
   Inicia el programa llamando al menú.
*/
int main()
{
    menu();
    return 0;
}

/* 
   Menu principal del programa.
   Permite al usuario elegir operaciones sobre la lista.
*/
void menu()
{
    ListaReproduccion lista;
    inicializarLista(&lista);

    int opcion;
    char titulo[50];

    do {
        printf("\n===== MENU LISTA DE REPRODUCCION =====\n");
        printf("1. Agregar cancion\n");
        printf("2. Eliminar cancion\n");
        printf("3. Reproducir siguiente cancion\n");
        printf("4. Mostrar lista completa\n");
        printf("5. Buscar una cancion\n");
        printf("6. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar(); /* limpiar buffer de entrada */

        switch(opcion) {
            case 1:
                printf("Ingresa el titulo de la cancion: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; /* eliminar salto de línea */
                agregarCancion(&lista, titulo);
                break;
            case 2:
                printf("Ingresa el titulo de la cancion a eliminar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                eliminarCancion(&lista, titulo);
                break;
            case 3:
                siguiente(&lista);
                break;
            case 4:
                mostrarLista(&lista);
                break;
            case 5:
                printf("Ingresa el titulo de la cancion a buscar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                buscarCancion(&lista, titulo);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 6);
}

/* 
   Funcion que crea una nueva canción con memoria dinámica.
   Retorna un puntero al nuevo nodo.
*/
Cancion* crearCancion(char titulo[])
{
    Cancion *nueva = (Cancion*)malloc(sizeof(Cancion));
    if (nueva == NULL) { /* Verificar si hay memoria disponible */
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    strcpy(nueva->titulo, titulo); /* Guardar el título */
    nueva->siguiente = NULL;       /* Al inicio no apunta a nadie */
    return nueva;
}

/* 
   Inicializar la lista de reproducción.
   Head y actual comienzan como NULL (lista vacía).
*/
void inicializarLista(ListaReproduccion *lista)
{
    lista->head = NULL;
    lista->actual = NULL;
}

/* 
   Funcion para agregar una canción al final de la lista.
   Si la lista está vacía, se convierte en la primera.
*/
void agregarCancion(ListaReproduccion *lista, char titulo[])
{
    Cancion *nueva = crearCancion(titulo);

    if (lista->head == NULL) {
        /* Lista vacía: la nueva canción es la primera y actual */
        lista->head = lista->actual = nueva;
    } else {
        /* Recorremos hasta el final */
        Cancion *aux = lista->head;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nueva; /* Insertar al final */
    }
    printf("Cancion \"%s\" agregada a la lista.\n", titulo);
}

/* 
   Funcion para eliminar una canción de la lista.
   Busca por título, ajusta los punteros y libera memoria.
*/
void eliminarCancion(ListaReproduccion *lista, char titulo[])
{
    if (lista->head == NULL) {
        printf("La lista de reproduccion esta vacia.\n");
        return;
    }

    Cancion *aux = lista->head, *anterior = NULL;

    /* Buscar la canción a eliminar */
    while (aux != NULL && strcmp(aux->titulo, titulo) != 0) {
        anterior = aux;
        aux = aux->siguiente;
    }

    if (aux == NULL) {
        /* No se encontró la canción */
        printf("La cancion \"%s\" no se encuentra en la lista.\n", titulo);
        return;
    }

    /* Caso: la canción es la primera */
    if (anterior == NULL) {
        lista->head = aux->siguiente;
    } else {
        /* Caso: la canción está en medio o al final */
        anterior->siguiente = aux->siguiente;
    }

    /* Si la canción actual era la eliminada, mover puntero */
    if (lista->actual == aux) {
        lista->actual = aux->siguiente != NULL ? aux->siguiente : lista->head;
    }

    printf("Cancion \"%s\" eliminada de la lista.\n", titulo);
    free(aux); /* Liberar memoria */
}

/* 
   Funcion para mostrar todas las canciones de la lista.
   Recorre desde head hasta el final.
*/
void mostrarLista(ListaReproduccion *lista)
{
    if (lista->head == NULL) {
        printf("La lista de reproduccion esta vacia.\n");
        return;
    }

    Cancion *aux = lista->head;
    int pos = 1;
    printf("\nLista de Reproduccion:\n");
    while (aux != NULL) {
        printf("%d. %s\n", pos, aux->titulo);
        aux = aux->siguiente;
        pos++;
    }
}

/* 
   Funcion para reproducir la siguiente canción.
   Mueve el puntero "actual" al siguiente nodo.
*/
void siguiente(ListaReproduccion *lista)
{
    if (lista->actual == NULL) {
        printf("No hay canciones en la lista.\n");
        return;
    }
    if (lista->actual->siguiente != NULL) {
        lista->actual = lista->actual->siguiente;
        printf("Reproduciendo siguiente: %s\n", lista->actual->titulo);
    } else {
        printf("Ya estas en la ultima cancion.\n");
    }
}

/* 
   Funcion para buscar una canción por título.
   Recorre la lista e imprime la posición si la encuentra.
*/
void buscarCancion(ListaReproduccion *lista, char titulo[])
{
    Cancion *aux = lista->head;
    int pos = 1;
    while (aux != NULL) {
        if (strcmp(aux->titulo, titulo) == 0) {
            printf("La cancion \"%s\" se encuentra en la posicion %d.\n", titulo, pos);
            return;
        }
        aux = aux->siguiente;
        pos++;
    }
    printf("La cancion \"%s\" no se encontro en la lista.\n", titulo);
}
