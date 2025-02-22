#include <gtk/gtk.h> // Incluye la biblioteca GTK para la interfaz gráfica

#ifndef HIPERMERCADO_H // Verifica si no ha sido definido
#define HIPERMERCADO_H // Define 

// función para crear la ventana principal de la aplicación
void crear_ventana_principal(GtkApplication *app);

// función para crear la ventana de un widget
void crear_ventana(GtkWidget *widget, gpointer data);

// función para añadir un estilo CSS a un widget
void aplicar_estilo_css(GtkWidget *widget, const char *css_file);

#endif // HIPERMERCADO_H