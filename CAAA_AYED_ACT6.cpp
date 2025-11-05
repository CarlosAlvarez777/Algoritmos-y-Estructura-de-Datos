#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===========================================================
   ESTRUCTURAS DE DATOS
   =========================================================== */

typedef struct _nodoInt {
    int dato;
    struct _nodoInt *ant;
    struct _nodoInt *sig;
} NodoInt;
typedef NodoInt* ListaInt;

typedef struct _nodoEst {
    int matricula;
    char nombre[50];
    int edad;
    char sexo;
    struct _nodoEst *ant;
    struct _nodoEst *sig;
} NodoEst;
typedef NodoEst* ListaEst;

/* ===========================================================
   PROTOTIPOS
   =========================================================== */

/* Menús principales */
void menuPrincipal(void);
void menuEnteros(void);
void menuEstudiantes(void);

/* Parte 1: Enteros */
void agregarEntero(ListaInt *inicio);
int existeEntero(ListaInt inicio, int valor);
void eliminarEntero(ListaInt *inicio);
void buscarEntero(ListaInt inicio);
void mostrarAscInt(ListaInt inicio);
void mostrarDescInt(ListaInt inicio);
void liberarListaInt(ListaInt *inicio);

/* Parte 2: Estudiantes */
void agregarEstudiante(ListaEst *inicio);
int existeMatricula(ListaEst inicio, int matricula);
void generarNombre(char *nombre);
void eliminarEstudiante(ListaEst *inicio);
void buscarEstudiante(ListaEst inicio);
void mostrarAscEst(ListaEst inicio);
void mostrarDescEst(ListaEst inicio);
void liberarListaEst(ListaEst *inicio);

/* ===========================================================
   FUNCIÓN PRINCIPAL
   =========================================================== */

int main(void) {
    srand((unsigned int)time(NULL));
    menuPrincipal();
    return 0;
}

/* ===========================================================
   MENÚ PRINCIPAL
   =========================================================== */

void menuPrincipal(void) {
    int opcion;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Lista doble con datos enteros\n");
        printf("2. Lista doble con datos de estudiantes\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1: menuEnteros(); break;
            case 2: menuEstudiantes(); break;
            case 3: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 3);
}

/* ===========================================================
   PARTE 1: LISTA DOBLE DE ENTEROS
   =========================================================== */

void menuEnteros(void) {
    ListaInt inicio = NULL;
    int opcion;

    do {
        printf("\n--- MENU LISTA DOBLE (ENTEROS) ---\n");
        printf("1. Agregar nodo\n");
        printf("2. Eliminar nodo\n");
        printf("3. Buscar nodo\n");
        printf("4. Mostrar ascendente\n");
        printf("5. Mostrar descendente\n");
        printf("6. Eliminar toda la lista\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1: agregarEntero(&inicio); break;
            case 2: eliminarEntero(&inicio); break;
            case 3: buscarEntero(inicio); break;
            case 4: mostrarAscInt(inicio); break;
            case 5: mostrarDescInt(inicio); break;
            case 6: liberarListaInt(&inicio); printf("Lista eliminada completamente.\n"); break;
            case 7: liberarListaInt(&inicio); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 7);
}

/* ---- Operaciones sobre lista de enteros ---- */

void agregarEntero(ListaInt *inicio) {
    int valor = rand() % 1000 + 1;
    while (existeEntero(*inicio, valor)) {
        valor = rand() % 1000 + 1;
    }

    NodoInt *nuevo = (NodoInt *)malloc(sizeof(NodoInt)); // ← CAST NECESARIO EN .CPP
    if (nuevo == NULL) {
        printf("Error de memoria.\n");
        return;
    }

    nuevo->dato = valor;
    nuevo->ant = NULL;
    nuevo->sig = NULL;

    if (*inicio == NULL) {
        *inicio = nuevo;
    } else {
        NodoInt *aux = *inicio;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        nuevo->ant = aux;
    }
    printf("Nodo agregado con valor: %d\n", valor);
}

int existeEntero(ListaInt inicio, int valor) {
    NodoInt *aux = inicio;
    while (aux != NULL) {
        if (aux->dato == valor) return 1;
        aux = aux->sig;
    }
    return 0;
}

void eliminarEntero(ListaInt *inicio) {
    if (inicio == NULL || *inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    int valor;
    printf("Ingrese el valor a eliminar: ");
    if (scanf("%d", &valor) != 1) {
        while (getchar() != '\n');
        printf("Entrada invalida.\n");
        return;
    }

    NodoInt *aux = *inicio;
    while (aux != NULL && aux->dato != valor)
        aux = aux->sig;

    if (aux == NULL) {
        printf("Valor no encontrado.\n");
        return;
    }

    if (aux->ant != NULL)
        aux->ant->sig = aux->sig;
    else
        *inicio = aux->sig;

    if (aux->sig != NULL)
        aux->sig->ant = aux->ant;

    free(aux);
    printf("Nodo con valor %d eliminado.\n", valor);
}

void buscarEntero(ListaInt inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    int valor;
    printf("Ingrese el valor a buscar: ");
    scanf("%d", &valor);

    NodoInt *aux = inicio;
    while (aux != NULL) {
        if (aux->dato == valor) {
            printf("Valor %d encontrado.\n", valor);
            return;
        }
        aux = aux->sig;
    }
    printf("Valor no encontrado.\n");
}

void mostrarAscInt(ListaInt inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    NodoInt *aux = inicio;
    printf("Lista ascendente: ");
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
    printf("\n");
}

void mostrarDescInt(ListaInt inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    NodoInt *aux = inicio;
    while (aux->sig != NULL)
        aux = aux->sig;

    printf("Lista descendente: ");
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->ant;
    }
    printf("\n");
}

void liberarListaInt(ListaInt *inicio) {
    NodoInt *aux;
    while (*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->sig;
        free(aux);
    }
}

/* ===========================================================
   PARTE 2: LISTA DOBLE DE ESTUDIANTES
   =========================================================== */

void menuEstudiantes(void) {
    ListaEst inicio = NULL;
    int opcion;

    do {
        printf("\n--- MENU LISTA DOBLE (ESTUDIANTES) ---\n");
        printf("1. Agregar estudiante\n");
        printf("2. Eliminar estudiante\n");
        printf("3. Buscar estudiante\n");
        printf("4. Mostrar ascendente\n");
        printf("5. Mostrar descendente\n");
        printf("6. Eliminar toda la lista\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1: agregarEstudiante(&inicio); break;
            case 2: eliminarEstudiante(&inicio); break;
            case 3: buscarEstudiante(inicio); break;
            case 4: mostrarAscEst(inicio); break;
            case 5: mostrarDescEst(inicio); break;
            case 6: liberarListaEst(&inicio); printf("Lista eliminada completamente.\n"); break;
            case 7: liberarListaEst(&inicio); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 7);
}

void generarNombre(char *nombre) {
    const char *nombres[] = {"Ana", "Luis", "Carlos", "Maria", "Pedro",
                             "Laura", "Diego", "Fernanda", "Sofia", "Jorge"};
    strcpy(nombre, nombres[rand() % 10]);
}

void agregarEstudiante(ListaEst *inicio) {
    int matricula = rand() % 9000 + 1000;
    while (existeMatricula(*inicio, matricula))
        matricula = rand() % 9000 + 1000;

    NodoEst *nuevo = (NodoEst *)malloc(sizeof(NodoEst)); // ← CAST NECESARIO EN .CPP
    if (nuevo == NULL) {
        printf("Error de memoria.\n");
        return;
    }

    nuevo->matricula = matricula;
    generarNombre(nuevo->nombre);
    nuevo->edad = rand() % 8 + 18;
    nuevo->sexo = (rand() % 2 == 0) ? 'M' : 'F';
    nuevo->ant = NULL;
    nuevo->sig = NULL;

    if (*inicio == NULL) {
        *inicio = nuevo;
    } else {
        NodoEst *aux = *inicio;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        nuevo->ant = aux;
    }

    printf("Estudiante agregado: [%d] %s, %d años, %c\n",
           nuevo->matricula, nuevo->nombre, nuevo->edad, nuevo->sexo);
}

int existeMatricula(ListaEst inicio, int matricula) {
    NodoEst *aux = inicio;
    while (aux != NULL) {
        if (aux->matricula == matricula)
            return 1;
        aux = aux->sig;
    }
    return 0;
}

void eliminarEstudiante(ListaEst *inicio) {
    if (inicio == NULL || *inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    int mat;
    printf("Ingrese la matricula a eliminar: ");
    if (scanf("%d", &mat) != 1) {
        while (getchar() != '\n');
        printf("Entrada invalida.\n");
        return;
    }

    NodoEst *aux = *inicio;
    while (aux != NULL && aux->matricula != mat)
        aux = aux->sig;

    if (aux == NULL) {
        printf("Matricula no encontrada.\n");
        return;
    }

    if (aux->ant != NULL)
        aux->ant->sig = aux->sig;
    else
        *inicio = aux->sig;

    if (aux->sig != NULL)
        aux->sig->ant = aux->ant;

    printf("Estudiante [%d] eliminado.\n", mat);
    free(aux);
}

void buscarEstudiante(ListaEst inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    int mat;
    printf("Ingrese la matricula a buscar: ");
    scanf("%d", &mat);

    NodoEst *aux = inicio;
    while (aux != NULL) {
        if (aux->matricula == mat) {
            printf("Encontrado: [%d] %s, %d años, %c\n",
                   aux->matricula, aux->nombre, aux->edad, aux->sexo);
            return;
        }
        aux = aux->sig;
    }
    printf("Estudiante no encontrado.\n");
}

void mostrarAscEst(ListaEst inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    NodoEst *aux = inicio;
    printf("\nLista ascendente:\n");
    while (aux != NULL) {
        printf("[%d] %s - %d - %c\n",
               aux->matricula, aux->nombre, aux->edad, aux->sexo);
        aux = aux->sig;
    }
}

void mostrarDescEst(ListaEst inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    NodoEst *aux = inicio;
    while (aux->sig != NULL)
        aux = aux->sig;

    printf("\nLista descendente:\n");
    while (aux != NULL) {
        printf("[%d] %s - %d - %c\n",
               aux->matricula, aux->nombre, aux->edad, aux->sexo);
        aux = aux->ant;
    }
}

void liberarListaEst(ListaEst *inicio) {
    NodoEst *aux;
    while (*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->sig;
        free(aux);
    }
}
