#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#include <gtk/gtk.h>
#include "hipermercado.h"
#include <productos.h>
#define MAXCH 50
#define MAXD 100
#define MAX 100
// Definicion de la estructura de los productos 
typedef struct Productos{
    char cd[MAX];// codigo del producto en caracteres
	int codigo;// codigo del producto
	char nombre[MAXCH]; //nombre del producto
	char desc[MAXD];// descripcion del producto
    char bs[MAX];//precio en bolivares
	float preciobs;//precio en bolivares como caracter
    int cant;//cantidad del producto en almace
	int veces_comprado; // numero de veces del producto comprado
}Pro;

// Funcion para crear la ventana del producto
void crear_ventana_de_producto(GtkApplication *app);

// Funcion para registrar un producto
int registrar_producto(const char *archivopro, Pro productos,const char *codigo,const char *nombre,const char *desc,const char *bs);

// Callback para guardar un producto desde un dialogo GTK
void guardar_producto_callback(GtkDialog *dialog, gint response_id, gpointer user_data);

// Funcion para buscar un producto
int buscar_producto(const char *archivopro,Pro *producto, const char *codigo );
// Callback para buscar un producto widget GTK
void buscar_producto_callback(GtkWidget* widget, gpointer data);

int validar_campos(Pro productos,const char *codigo,const char *nombre,const char *desc,const char *bs);
// Funcion para modificar un producto ya existente
int modificar_producto(const char *archivopro, int codigo,char nombre[MAXCH],char desc[MAXD],float preciobs);

// Callback para guardar un producto desde un widget GTK
void guardar_producto_modificado(GtkWidget *widget, gpointer data);

// Funcion para eliminar un producto por su codigo
int eliminar_producto(const char* archivopro, const char *codigo);

// Callback para eliminar un producto desde un widget GTK
void eliminar_producto_callback(GtkWidget* widget, gpointer data);

void mostrar_productos(GtkWidget *widget, gpointer data);

void QuickSort(Pro vectorpro [], int inicio, int fin);

#endif PRODUCTOS_H