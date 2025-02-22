#include <gtk/gtk.h> // Incluye la biblioteca GTK para la interfaz gráfica
#include "hipermercado.h" // Incluye el archivo de cabecera para las funciones de la interfaz gráfica

int main(int argc, char **argv) {
    GtkApplication *app; // Declara un puntero a GtkApplication
    int status; // Declara una variable para almacenar el estado de la aplicación

    // Crea una nueva instancia de GtkApplication con un application_id válido
    app = gtk_application_new("org.gtk.HipermercadoCachamay", G_APPLICATION_DEFAULT_FLAGS);
    
    // Conecta la señal "activate" de la aplicación a la función crear_ventana_principal
    g_signal_connect(app, "activate", G_CALLBACK(crear_ventana_principal), NULL);
    
    // Ejecuta la aplicación GTK
    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // Libera la memoria utilizada por la instancia de GtkApplication
    g_object_unref(app);

    return status; // Devuelve el estado de la aplicación
}