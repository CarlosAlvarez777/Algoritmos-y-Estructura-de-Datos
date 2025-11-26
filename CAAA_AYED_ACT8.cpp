#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   DEFINICIÓN DEL NODO PARA CADA BUCKET DEL HASH
   ============================================================ */

typedef struct _tnodo
{
    int dato;
    struct _tnodo *sig;
} sTnodo;

typedef sTnodo *Tnodo;

/* ============================================================
   PROTOTIPOS DE FUNCIONES
   ============================================================ */

int hashFunction(int clave, int tam);
void inicializarTabla(Tnodo tabla[], int tam);
void agregarElemento(Tnodo tabla[], int tam);
void insertarEnLista(Tnodo *lista, int valor);
void eliminarElemento(Tnodo tabla[], int tam);
void eliminarDeLista(Tnodo *lista, int valor);
void buscarElemento(Tnodo tabla[], int tam);
int buscarEnLista(Tnodo lista, int valor);
void mostrarTabla(Tnodo tabla[], int tam);
void liberarTabla(Tnodo tabla[], int tam);
int leerEnteroValidado(const char *msg);

/* ============================================================
   FUNCIÓN PRINCIPAL
   ============================================================ */

int main()
{
    const int TAM = 17; // tamaño primo para mejorar dispersión
    Tnodo tabla[TAM];
    int opcion;
    int contadorDatos = 0;

    inicializarTabla(tabla, TAM);

    do
    {
        printf("\n========== TABLA HASH ==========\n");
        printf("1. AGREGAR\n");
        printf("2. ELIMINAR\n");
        printf("3. BUSCAR\n");
        printf("4. MOSTRAR TODA LA TABLA\n");
        printf("5. SALIR\n");

        opcion = leerEnteroValidado("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            if (contadorDatos >= 75)
            {
                printf("Ya se alcanzó el máximo de 75 datos.\n");
            }
            else
            {
                agregarElemento(tabla, TAM);
                contadorDatos++;
            }
            break;

        case 2:
            eliminarElemento(tabla, TAM);
            break;

        case 3:
            buscarElemento(tabla, TAM);
            break;

        case 4:
            mostrarTabla(tabla, TAM);
            break;

        case 5:
            liberarTabla(tabla, TAM);
            printf("Saliendo y liberando memoria...\n");
            break;

        default:
            printf("Opción inválida.\n");
        }

    } while (opcion != 5);

    return 0;
}

/* ============================================================
   IMPLEMENTACIÓN DE FUNCIONES
   ============================================================ */

int hashFunction(int clave, int tam)
{
    return clave % tam;
}

void inicializarTabla(Tnodo tabla[], int tam)
{
    for (int i = 0; i < tam; i++)
        tabla[i] = NULL;
}

int leerEnteroValidado(const char *msg)
{
    int val, ok;

    do
    {
        printf("%s", msg);
        ok = scanf("%d", &val);

        if (!ok)
        {
            printf("Entrada inválida.\n");
            while (getchar() != '\n')
                ;
        }
    } while (!ok);

    return val;
}

/* -------------------- AGREGAR -------------------- */

void agregarElemento(Tnodo tabla[], int tam)
{
    int valor = leerEnteroValidado("Ingrese un entero entre 1 y 1000: ");

    while (valor < 1 || valor > 1000)
    {
        valor = leerEnteroValidado("ERROR. Debe ser 1-1000. Intente otra vez: ");
    }

    int indice = hashFunction(valor, tam);

    insertarEnLista(&tabla[indice], valor);

    printf("Valor %d agregado en bucket %d.\n", valor, indice);
}

void insertarEnLista(Tnodo *lista, int valor)
{
    Tnodo nuevo = (Tnodo)malloc(sizeof(sTnodo)); // Cast necesario en .cpp
    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (*lista == NULL)
    {
        *lista = nuevo;
        return;
    }

    Tnodo aux = *lista;
    while (aux->sig != NULL)
        aux = aux->sig;

    aux->sig = nuevo;
}

/* -------------------- ELIMINAR -------------------- */

void eliminarElemento(Tnodo tabla[], int tam)
{
    int valor = leerEnteroValidado("Ingrese el valor a eliminar: ");
    int indice = hashFunction(valor, tam);

    if (tabla[indice] == NULL)
    {
        printf("Bucket %d vacío. No se puede eliminar.\n", indice);
        return;
    }

    eliminarDeLista(&tabla[indice], valor);
}

void eliminarDeLista(Tnodo *lista, int valor)
{
    Tnodo aux = *lista, ant = NULL;

    while (aux != NULL && aux->dato != valor)
    {
        ant = aux;
        aux = aux->sig;
    }

    if (aux == NULL)
    {
        printf("El valor no se encontró en este bucket.\n");
        return;
    }

    if (ant == NULL)
        *lista = aux->sig;
    else
        ant->sig = aux->sig;

    free(aux);

    printf("Valor eliminado correctamente.\n");
}

/* -------------------- BUSCAR -------------------- */

void buscarElemento(Tnodo tabla[], int tam)
{
    int valor = leerEnteroValidado("Valor a buscar: ");
    int indice = hashFunction(valor, tam);

    if (buscarEnLista(tabla[indice], valor))
        printf("Valor %d encontrado en bucket %d.\n", valor, indice);
    else
        printf("Valor %d NO encontrado.\n", valor);
}

int buscarEnLista(Tnodo lista, int valor)
{
    while (lista != NULL)
    {
        if (lista->dato == valor)
            return 1;
        lista = lista->sig;
    }
    return 0;
}

/* -------------------- MOSTRAR -------------------- */

void mostrarTabla(Tnodo tabla[], int tam)
{
    printf("\n===== CONTENIDO DE LA TABLA HASH =====\n");

    for (int i = 0; i < tam; i++)
    {
        printf("%d [ ", i);

        if (tabla[i] == NULL)
        {
            printf("NULL ");
        }
        else
        {
            Tnodo aux = tabla[i];
            while (aux != NULL)
            {
                printf("%d ", aux->dato);
                if (aux->sig != NULL)
                    printf("→ ");
                aux = aux->sig;
            }
        }

        printf("]\n");
    }
}

/* -------------------- LIBERAR MEMORIA -------------------- */

void liberarTabla(Tnodo tabla[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        Tnodo aux = tabla[i];
        while (aux != NULL)
        {
            Tnodo tmp = aux;
            aux = aux->sig;
            free(tmp);
        }
        tabla[i] = NULL;
    }
}
