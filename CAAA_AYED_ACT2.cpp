#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------------------------
// Definición de estructuras
// ---------------------------
typedef struct _tdato {
    int dato;
    struct _tdato *sig;
} sTdato;

typedef sTdato *Tdato;

typedef struct {
    char nombre[30];
    int edad;
    char matricula[15];
} Alumno;

// ---------------------------
// Prototipos
// ---------------------------
void menuPrincipal();
void ejercicio1();
void ejercicio2();
void ejercicio3();
void ejercicio4();

// Funciones para pila dinámica (Ej 2 y Ej 3)
int push(Tdato *pila, int valor);
int pop(Tdato *pila);

// Funciones para pila con Alumno (Ej 3)
int pushAlumno(Tdato *pila, Alumno a);
Alumno popAlumno(Tdato *pila);
void mostrarAlumno(Alumno a);

// Validación de entrada
int leerEnteroEnRango(const char *mensaje, int min, int max);

// ---------------------------
// MAIN
// ---------------------------
int main() {
    menuPrincipal();
    return 0;
}

// ---------------------------
// Menú Principal
// ---------------------------
void menuPrincipal() {
    int opc;
    do {
        system("CLS");
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("1. Pila Estatica (PUSH/POP)\n");
        printf("2. Pila Dinamica (Enteros)\n");
        printf("3. Pila con datos de Alumno\n");
        printf("4. Factorial con Pilas\n");
        printf("5. Salir\n");
        opc = leerEnteroEnRango("Seleccione una opcion: ", 1, 5);

        switch(opc) {
            case 1: ejercicio1(); break;
            case 2: ejercicio2(); break;
            case 3: ejercicio3(); break;
            case 4: ejercicio4(); break;
            case 5: printf("\nSaliendo...\n"); break;
        }
    } while(opc != 5);
    system("pause");
}

// ---------------------------
// EJERCICIO 1: Pila Estática
// ---------------------------
void ejercicio1() {
    int pila[100], tope = -1;
    int opc, valor;

    do {
        system("CLS");
        printf("\n--- EJERCICIO 1: PILA ESTATICA ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. SALIR\n");
        opc = leerEnteroEnRango("Opcion: ", 1, 3);

        switch(opc) {
            case 1:
                if (tope < 99) {
                    printf("Ingrese valor: ");
                    scanf("%d", &valor);
                    pila[++tope] = valor;
                } else {
                    printf("Pila llena!\n");
                }
                break;
            case 2:
                if (tope >= 0) {
                    printf("POP: %d\n", pila[tope--]);
                } else {
                    printf("Pila vacia!\n");
                }
                break;
            case 3: printf("Regresando al menu principal...\n"); break;
        }
        system("pause");
    } while(opc != 3);
}

// ---------------------------
// EJERCICIO 2: Pila Dinámica Enteros
// ---------------------------
void ejercicio2() {
    Tdato pila = NULL;
    int opc, valor;

    do {
        system("CLS");
        printf("\n--- EJERCICIO 2: PILA DINAMICA ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. SALIR\n");
        opc = leerEnteroEnRango("Opcion: ", 1, 3);

        switch(opc) {
            case 1:
                printf("Ingrese valor: ");
                scanf("%d", &valor);
                if (!push(&pila, valor)) {
                    printf("Error: no se pudo asignar memoria.\n");
                }
                break;
            case 2:
                if (pila) {
                    printf("POP: %d\n", pop(&pila));
                } else {
                    printf("Pila vacia!\n");
                }
                break;
            case 3: 
                while(pila) pop(&pila);
                printf("Memoria liberada. Regresando...\n");
                break;
        }
        system("pause");
    } while(opc != 3);
}

// ---------------------------
// EJERCICIO 3: Pila con datos de Alumno
// ---------------------------
void ejercicio3() {
    Tdato pila = NULL;
    int opc;
    Alumno a;

    do {
        system("CLS");
        printf("\n--- EJERCICIO 3: PILA ALUMNOS ---\n");
        printf("1. PUSH (Agregar alumno)\n");
        printf("2. POP (Eliminar alumno)\n");
        printf("3. SALIR\n");
        opc = leerEnteroEnRango("Opcion: ", 1, 3);

        switch(opc) {
            case 1:
                printf("Nombre: ");
                getchar(); // limpiar buffer
                fgets(a.nombre, sizeof(a.nombre), stdin);
                a.nombre[strcspn(a.nombre, "\n")] = 0;

                a.edad = leerEnteroEnRango("Edad: ", 1, 120);

                printf("Matricula: ");
                scanf("%14s", a.matricula);

                if (!pushAlumno(&pila, a)) {
                    printf("Error: no se pudo asignar memoria.\n");
                }
                break;
            case 2:
                if (pila) {
                    mostrarAlumno(popAlumno(&pila));
                } else {
                    printf("Pila vacia!\n");
                }
                break;
            case 3:
                while(pila) popAlumno(&pila);
                printf("Memoria liberada. Regresando...\n");
                break;
        }
        system("pause");
    } while(opc != 3);
}

// ---------------------------
// EJERCICIO 4: Factorial usando Pilas
// ---------------------------
void ejercicio4() {
    int n;
    char continuar;
    do {
        system("CLS");
        n = leerEnteroEnRango("\nIngrese un numero para calcular su factorial (>=1): ", 1, 100);

        Tdato pila = NULL;
        for (int i = n; i > 0; i--) {
            if (!push(&pila, i)) {
                printf("Error: no se pudo asignar memoria.\n");
                return;
            }
        }

        int resultado = 1;
        printf("\nProceso:\n");
        while(pila) {
            int val = pop(&pila);
            resultado *= val;
            printf("%d -> resultado parcial: %d\n", val, resultado);
        }

        printf("Factorial de %d = %d\n", n, resultado);

        printf("\nDesea calcular otro factorial? (s/n): ");
        getchar();
        continuar = getchar();
        system("pause");
    } while(continuar == 's' || continuar == 'S');
}

// ---------------------------
// Funciones auxiliares
// ---------------------------
int push(Tdato *pila, int valor) {
    Tdato nuevo = (Tdato)malloc(sizeof(sTdato));
    if (!nuevo) return 0; // fallo malloc
    nuevo->dato = valor;
    nuevo->sig = *pila;
    *pila = nuevo;
    return 1;
}

int pop(Tdato *pila) {
    if (*pila == NULL) return -1;
    Tdato temp = *pila;
    int valor = temp->dato;
    *pila = temp->sig;
    free(temp);
    return valor;
}

int pushAlumno(Tdato *pila, Alumno a) {
    Tdato nuevo = (Tdato)malloc(sizeof(sTdato) + sizeof(Alumno));
    if (!nuevo) return 0;
    nuevo->sig = *pila;
    memcpy(&(nuevo->dato), &a, sizeof(Alumno));
    *pila = nuevo;
    return 1;
}

Alumno popAlumno(Tdato *pila) {
    Alumno a;
    Tdato temp = *pila;
    memcpy(&a, &(temp->dato), sizeof(Alumno));
    *pila = temp->sig;
    free(temp);
    return a;
}

void mostrarAlumno(Alumno a) {
    printf("Alumno: %s | Edad: %d | Matricula: %s\n", a.nombre, a.edad, a.matricula);
}

int leerEnteroEnRango(const char *mensaje, int min, int max) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) == 1 && valor >= min && valor <= max) {
            return valor;
        } else {
            printf("Entrada invalida. Intente de nuevo.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
