//trabajadores.h
// Definición de las funciones y estructuras para el manejo de trabajadores
#ifndef TRABAJADORES_H
#define TRABAJADORES_H

#include <gtk/gtk.h>
#include "hipermercado_cachamay.h"
#include "trabajadores.h"

// Definición de la estructura trabajador
typedef struct {
    char cedula[20];               // Cédula 
    char nombre[50];               // Primer nombre 
    char segundo_nombre[50];       // Segundo nombre
    char apellido[50];             // Primer apellido 
    char segundo_apellido[50];     // Segundo apellido
    char direccion[100];           // Dirección
    char telefono [12];            // Teléfono
    char fecha_ingreso[20];        // Fecha de ingreso  
    char codigo[9];
}trabajador;

//crea los botones de registar,modificar,ekiminar y mostrar empleados
void crear_ventana_de_trabajdores(GtkApplication *app);

// Crea el formulario para registrar un empleado
void mostrar_formulario_registro_empleado(GtkWidget *widget, gpointer data);

// Crea el formulario para eliminar un empleado
void mostrar_formulario_eliminar_empleado(GtkWidget *widget, gpointer data);

// crea un codigo al azar
char* generar_codigo();

// Función para registrar un empleado
int registrar_empleado(const char* archivo, trabajador empleado, const char *cedula);

// Callback para guardar un empleado desde un diálogo GTK
void guardar_empleado_callback(GtkDialog *dialog, gint response_id, gpointer user_data);

// Función para validar los campos de un empleado
int validar_campos(trabajador empleado, const char *cedula, const char *codigo);

// Función para validar una fecha
int validar_fecha(const char *fecha);

// Verifica si la cédula de un empleado ya está registrada
int cedula_duplicada(const char* archivo, const char* cedula);

// Crea el formulario para modificar un empleado
int modificar_empleado(const char* archivo, const char* cedula, trabajador nuevo_empleado);

// Función para buscar un empleado por su cédula
int buscar_empleado(const char* archivo, const char* cedula, trabajador* resultado);

// Callback para buscar un empleado desde un widget GTK
void buscar_empleado_callback(GtkWidget *widget, gpointer data);

// Callback para guardar un empleado modificado desde un widget GTK
void guardar_empleado_modificado(GtkWidget *widget, gpointer data);

// Función para eliminar un empleado por su cédula
int eliminar_empleado(const char* archivo, const char* cedula);

// Callback para eliminar un empleado desde un widget GTK
void eliminar_empleado_callback(GtkWidget* widget, gpointer data);

// Muestra los empleados registrados
void mostrar_empleados(GtkWidget *widget, gpointer data);

#endif // TRABAJADORES_H
