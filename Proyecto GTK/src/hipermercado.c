#include <gtk/gtk.h> // Incluir la biblioteca GTK para la interfaz gráfica
#include <stdlib.h> // Incluir la biblioteca estándar de C
#include "hipermercado.h" // Incluir el archivo de cabecera personalizado

#define ICON_PATH "../src/icono.ico" // Definir la ruta relativa del icono
#define IMAGE_PATH "../src/logo.png" // Definir la ruta relativa de la imagen
#define CSS_PATH "../src/estilo.css" // Definir la ruta relativa del archivo CSS

// Función para obtener la ruta absoluta a partir de una ruta relativa
char* get_absolute_path(const char* relative_path) {
    char *current_dir = g_get_current_dir(); // Obtener el directorio actual
    char *absolute_path = g_build_filename(current_dir, relative_path, NULL); // Construir la ruta absoluta
    g_free(current_dir); // Liberar la memoria del directorio actual
    return absolute_path; // Devolver la ruta absoluta
}

// Función para crear una nueva ventana
void crear_ventana(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Crear una nueva ventana de nivel superior
    gtk_window_set_title(GTK_WINDOW(window), (const gchar *)data); // Establecer el título de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200); // Establecer el tamaño predeterminado de la ventana
    
    GtkWidget *label = gtk_label_new((const gchar *)data); // Crear una nueva etiqueta con el título
    gtk_container_add(GTK_CONTAINER(window), label); // Añadir la etiqueta a la ventana
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL); // Conectar la señal de destrucción de la ventana
    gtk_widget_show_all(window); // Mostrar todos los widgets de la ventana
}

// Función para aplicar el estilo CSS
void aplicar_estilo_css(GtkWidget *widget, const char *css_file) {
    GtkCssProvider *provider = gtk_css_provider_new(); // Crear un nuevo proveedor de CSS
    GdkDisplay *display = gdk_display_get_default(); // Obtener la pantalla predeterminada
    GdkScreen *screen = gdk_display_get_default_screen(display); // Obtener la pantalla predeterminada
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER); // Añadir el proveedor de CSS a la pantalla
    
    GError *error = NULL; // Inicializar el puntero de error
    gtk_css_provider_load_from_path(provider, css_file, &error); // Cargar el archivo CSS
    if (error) { // Comprobar si hay errores
        g_printerr("Error al cargar el archivo CSS: %s\n", error->message); // Imprimir el mensaje de error
        g_error_free(error); // Liberar la memoria del error
    }
    g_object_unref(provider); // Liberar la memoria del proveedor de CSS
}

// Función para crear la ventana principal
void crear_ventana_principal(GtkApplication *app) {
    GtkWidget *window, *main_box, *left_box, *right_box, *image, *label, *button; // Declarar los widgets
    GtkWidget *vbox_labels, *vbox_buttons; // Declarar los contenedores verticales
    
    // Crear la ventana principal
    window = gtk_application_window_new(app); // Crear una nueva ventana de aplicación
    gtk_window_set_title(GTK_WINDOW(window), "Hipermercado Cachamay"); // Establecer el título de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 500); // Establecer el tamaño predeterminado de la ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centrar la ventana en la pantalla
    
    // Establecer el color de fondo de la ventana
    GdkRGBA color; // Declarar una estructura de color
    gdk_rgba_parse(&color, "#387647"); // Parsear el color desde una cadena
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS // Ignorar las advertencias de deprecación
    gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &color); // Establecer el color de fondo
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    
    // Contenedor principal horizontal
    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20); // Crear un nuevo contenedor horizontal
    gtk_container_add(GTK_CONTAINER(window), main_box); // Añadir el contenedor a la ventana
    
    // Sección izquierda (imagen y etiquetas)
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Crear un nuevo contenedor vertical
    gtk_box_pack_start(GTK_BOX(main_box), left_box, FALSE, FALSE, 20); // Añadir el contenedor a la caja principal
    
    // Cargar imagen
    char *image_path = get_absolute_path(IMAGE_PATH); // Obtener la ruta absoluta de la imagen
    image = gtk_image_new_from_file(image_path); // Crear una nueva imagen desde el archivo
    gtk_box_pack_start(GTK_BOX(left_box), image, FALSE, FALSE, 0); // Añadir la imagen a la caja izquierda
    g_free(image_path); // Liberar la memoria de la ruta de la imagen
    
    // Contenedor de etiquetas
    vbox_labels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Crear un nuevo contenedor vertical para las etiquetas
    gtk_box_pack_start(GTK_BOX(left_box), vbox_labels, FALSE, FALSE, 0); // Añadir el contenedor de etiquetas a la caja izquierda
    
    const char *label_texts[] = {"HIPERMERCADO CACHAMAY", " J-123456789", "0414-0463588", "Puerto Ordaz"}; // Definir los textos de las etiquetas
    for (int i = 0; i < 4; i++) { // Iterar sobre los textos de las etiquetas
        label = gtk_label_new(label_texts[i]); // Crear una nueva etiqueta con el texto
        PangoAttrList *attrs = pango_attr_list_new(); // Crear una nueva lista de atributos Pango
        pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD)); // Insertar el atributo de negrita
        pango_attr_list_insert(attrs, pango_attr_size_new(18 * PANGO_SCALE)); // Insertar el atributo de tamaño
        gtk_label_set_attributes(GTK_LABEL(label), attrs); // Establecer los atributos de la etiqueta
        pango_attr_list_unref(attrs); // Liberar la memoria de la lista de atributos
        gtk_box_pack_start(GTK_BOX(vbox_labels), label, FALSE, FALSE, 0); // Añadir la etiqueta al contenedor de etiquetas
    }
    
    // Sección derecha (botones en columna)
    right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Crear un nuevo contenedor vertical para los botones
    gtk_box_pack_start(GTK_BOX(main_box), right_box, TRUE, TRUE, 50); // Añadir el contenedor de botones a la caja principal
    
    const char *button_labels[] = {"Productos", "Clientes", "Facturas", "Ventas", "Control de cajas", "Trabajadores", "Reportes"}; // Definir los textos de los botones
    for (int i = 0; i < 7; i++) { // Iterar sobre los textos de los botones
        button = gtk_button_new_with_label(button_labels[i]); // Crear un nuevo botón con el texto
        gtk_widget_set_size_request(button, 200, -1); // Ajustar solo el ancho del botón
        gtk_box_pack_start(GTK_BOX(right_box), button, TRUE, TRUE, 5); // Añadir el botón al contenedor de botones
        g_signal_connect(button, "clicked", G_CALLBACK(crear_ventana), (gpointer)button_labels[i]); // Conectar la señal de clic del botón
    }
    
    // Aplicar el estilo CSS
    char *css_path = get_absolute_path(CSS_PATH); // Obtener la ruta absoluta del archivo CSS
    aplicar_estilo_css(GTK_WIDGET(window), css_path); // Aplicar el estilo CSS a la ventana
    g_free(css_path); // Liberar la memoria de la ruta del archivo CSS

    gtk_widget_show_all(window); // Mostrar todos los widgets de la ventana
}