#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Tamaño máximo de la cola estática

/* ===========================================================
   ==============  SECCIÓN: COLA DINÁMICA  ===================
   ===========================================================*/

// Definición del nodo para la cola dinámica
typedef struct Nodo {
    int dato;
    struct Nodo *sig;
} Nodo;

// Punteros globales para la cola dinámica
Nodo *frenteD = NULL;
Nodo *finalD = NULL;

// Prototipos de funciones de cola dinámica
void pushD(int valor);
void popD();
int estaVaciaD();
void mostrarColaD();
void menuDinamica();

/* ===========================================================
   ==============  SECCIÓN: COLA ESTÁTICA  ===================
   ===========================================================*/

// Variables globales para la cola estática
int colaE[MAX];
int frenteE = -1;
int finalE = -1;

// Prototipos de funciones de cola estática
void pushE(int valor);
void popE();
int estaVaciaE();
int estaLlenaE();
void mostrarColaE();
void menuEstatica();

/* ===========================================================
   ==============  SECCIÓN: MENÚ PRINCIPAL  ==================
   ===========================================================*/
void menuPrincipal();

/* ===========================================================
   =====================   MAIN   ============================
   ===========================================================*/
int main() {
    menuPrincipal();
    return 0;
}

/* ===========================================================
   ============== IMPLEMENTACIÓN COLA DINÁMICA ===============
   ===========================================================*/

void pushD(int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }
    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (estaVaciaD()) {
        frenteD = finalD = nuevo;
    } else {
        finalD->sig = nuevo;
        finalD = nuevo;
    }
    printf("Se inserto %d en la cola dinamica.\n", valor);
}

void popD() {
    if (estaVaciaD()) {
        printf("La cola dinámica esta vacia, no se puede eliminar.\n");
        return;
    }
    Nodo *aux = frenteD;
    printf("Se atendio y elimino: %d\n", aux->dato);
    frenteD = frenteD->sig;
    if (frenteD == NULL) {
        finalD = NULL;
    }
    free(aux);
}

int estaVaciaD() {
    return (frenteD == NULL);
}

void mostrarColaD() {
    if (estaVaciaD()) {
        printf("La cola dinamica esta vacia.\n");
        return;
    }
    Nodo *aux = frenteD;
    printf("Contenido de la cola dinamica: ");
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
    printf("\n");
}

void menuDinamica() {
    int opcion, valor;
    do {
        printf("\n--- MENU COLA DINAMICA ---\n");
        printf("1. Insertar (PUSH)\n");
        printf("2. Atender (POP)\n");
        printf("3. Mostrar cola\n");
        printf("4. Regresar al menu principal\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("Ingresa el valor a insertar: ");
                scanf("%d", &valor);
                pushD(valor);
                break;
            case 2:
                popD();
                break;
            case 3:
                mostrarColaD();
                break;
            case 4:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion no valida, intenta de nuevo.\n");
        }
    } while(opcion != 4);
}

/* ===========================================================
   ============== IMPLEMENTACIÓN COLA ESTÁTICA ===============
   ===========================================================*/

void pushE(int valor) {
    if (estaLlenaE()) {
        printf("Error: la cola esta llena.\n");
        return;
    }
    if (frenteE == -1) frenteE = 0;
    finalE = (finalE + 1) % MAX;
    colaE[finalE] = valor;
    printf("Se inserto %d en la cola estatica.\n", valor);
}

void popE() {
    if (estaVaciaE()) {
        printf("La cola está vacia, no se puede eliminar.\n");
        return;
    }
    printf("Se atendio y elimino: %d\n", colaE[frenteE]);
    if (frenteE == finalE) {
        frenteE = finalE = -1; // cola vacía
    } else {
        frenteE = (frenteE + 1) % MAX;
    }
}

int estaVaciaE() {
    return (frenteE == -1);
}

int estaLlenaE() {
    return ((finalE + 1) % MAX == frenteE);
}

void mostrarColaE() {
    if (estaVaciaE()) {
        printf("La cola está vacia.\n");
        return;
    }
    printf("Contenido de la cola estatica: ");
    int i = frenteE;
    while (1) {
        printf("%d ", colaE[i]);
        if (i == finalE) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void menuEstatica() {
    int opcion, valor;
    do {
        printf("\n--- MENU COLA ESTATICA ---\n");
        printf("1. Insertar (PUSH)\n");
        printf("2. Atender (POP)\n");
        printf("3. Mostrar cola\n");
        printf("4. Regresar al menu principal\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("Ingresa el valor a insertar: ");
                scanf("%d", &valor);
                pushE(valor);
                break;
            case 2:
                popE();
                break;
            case 3:
                mostrarColaE();
                break;
            case 4:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opción no valida, intenta de nuevo.\n");
        }
    } while(opcion != 4);
}

/* ===========================================================
   ============== MENÚ PRINCIPAL GENERAL =====================
   ===========================================================*/
void menuPrincipal() {
    int opcion;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Usar Cola Dinamica\n");
        printf("2. Usar Cola Estatica\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                menuDinamica();
                break;
            case 2:
                menuEstatica();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida, intenta de nuevo.\n");
        }
    } while(opcion != 3);
}
