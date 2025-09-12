#include <stdio.h>
#include <stdlib.h>

/* 
   Definición de la estructura para un nodo de la lista enlazada.
   Cada nodo almacena un dato y un apuntador al siguiente nodo.
*/
typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;
} Nodo;

/* Prototipos de funciones */
Nodo* crearNodo(int valor);
void insertarCola(Nodo **frente, Nodo **final, int valor);
void mostrarCola(Nodo *frente);
void buscarElemento(Nodo *frente, int valor);
void eliminarElemento(Nodo **frente, Nodo **final);
void vaciarCola(Nodo **frente, Nodo **final);
void menu();

/* 
   Funcion principal.
   Llama al menu para iniciar la ejecucion del programa.
*/
int main() {
    menu();
    return 0;
}

/* 
   Funcion que despliega el menu principal del programa.
   Permite al usuario interactuar con la cola.
*/
void menu() {
    Nodo *frente = NULL, *final = NULL; /* Inicialmente la cola esta vacia */
    int opcion, valor;

    do {
        printf("\n===== MENU COLA (LISTAS ENLAZADAS) =====\n");
        printf("1. Insertar elemento a la cola\n");
        printf("2. Mostrar elementos de la cola\n");
        printf("3. Buscar un elemento en la cola\n");
        printf("4. Eliminar el primer elemento de la cola\n");
        printf("5. Vaciar la cola\n");
        printf("6. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingresa el valor a insertar: ");
                scanf("%d", &valor);
                insertarCola(&frente, &final, valor);
                break;
            case 2:
                mostrarCola(frente);
                break;
            case 3:
                printf("Ingresa el valor a buscar: ");
                scanf("%d", &valor);
                buscarElemento(frente, valor);
                break;
            case 4:
                eliminarElemento(&frente, &final);
                break;
            case 5:
                vaciarCola(&frente, &final);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                vaciarCola(&frente, &final); /* Limpieza antes de salir */
                break;
            default:
                printf("Opcion invalida, intenta de nuevo.\n");
        }
    } while (opcion != 6);
}

/* 
   Funcion que crea un nodo con el valor indicado.
   Se asigna memoria dinamica y se inicializa el nodo.
*/
Nodo* crearNodo(int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) { /* Validación en caso de error de memoria */
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

/* 
   Funcion para insertar un elemento al final de la cola.
   Esto garantiza el comportamiento FIFO (First In, First Out).
*/
void insertarCola(Nodo **frente, Nodo **final, int valor) {
    Nodo *nuevo = crearNodo(valor);
    if (*final == NULL) {
        /* Si la cola esta vacia, frente y final apuntan al mismo nodo */
        *frente = *final = nuevo;
    } else {
        /* Si ya hay elementos, se agrega al final */
        (*final)->siguiente = nuevo;
        *final = nuevo;
    }
    printf("Elemento %d insertado en la cola.\n", valor);
}

/* 
   Funcion para mostrar los elementos de la cola.
   Se recorre desde el frente hasta el final.
*/
void mostrarCola(Nodo *frente) {
    if (frente == NULL) {
        printf("La cola esta vacia.\n");
        return;
    }
    printf("Elementos en la cola: ");
    while (frente != NULL) {
        printf("%d ", frente->dato);
        frente = frente->siguiente;
    }
    printf("\n");
}

/* 
   Funcion para buscar un elemento en la cola.
   Recorre la lista y verifica si el valor existe.
*/
void buscarElemento(Nodo *frente, int valor) {
    int encontrado = 0;
    while (frente != NULL) {
        if (frente->dato == valor) {
            encontrado = 1;
            break;
        }
        frente = frente->siguiente;
    }
    if (encontrado) {
        printf("El elemento %d SI se encuentra en la cola.\n", valor);
    } else {
        printf("El elemento %d NO se encuentra en la cola.\n", valor);
    }
}

/* 
   Funcion para eliminar el primer elemento de la cola.
   Esto respeta la regla FIFO: el primer elemento en entrar es el primero en salir.
*/
void eliminarElemento(Nodo **frente, Nodo **final) {
    if (*frente == NULL) {
        printf("La cola esta vacia. No se puede eliminar.\n");
        return;
    }
    Nodo *aux = *frente;
    printf("Elemento eliminado: %d\n", aux->dato);
    *frente = (*frente)->siguiente;
    if (*frente == NULL) {
        /* Si la cola queda vacia, final tambien debe apuntar a NULL */
        *final = NULL;
    }
    free(aux); /* Liberamos la memoria del nodo eliminado */
}

/* 
   Funcion para vaciar la cola completamente.
   Se eliminan todos los nodos uno por uno liberando la memoria.
*/
void vaciarCola(Nodo **frente, Nodo **final) {
    while (*frente != NULL) {
        eliminarElemento(frente, final);
    }
    printf("La cola ha sido vaciada.\n");
}