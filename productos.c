#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "productos.h"
#include "hipermercado.h"
#include <ctype.h>
#define MAXCH 50
#define MAXD 100
#define MAX 100
// Funcion para crear la ventana de los productos

void crear_ventana_de_producto(GtkApplication *app){
    GtkWidget *window; // Puntero a la ventana principal
    GtkWidget *box; // Puntero al contenedor vertical para los botones
    GtkWidget *button; // Puntero a los botones de la interfaz

    // Crear una nueva ventana de la aplicación
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema de productos"); // Establecer el título de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600); // Establecer el tamaño predeterminado de la ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centrar la ventana en la pantalla

    // Establecer el icono de la ventana
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "src/icono.ico", NULL);

    // Establecer el color de fondo de la ventana
    GdkRGBA color;
    gdk_rgba_parse(&color, "#455FA0"); //Color de la ventana   
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &color);
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS

    // Crear un GtkBox vertical para centrar los botones
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER); // Centrar horizontalmente el GtkBox
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER); // Centrar verticalmente el GtkBox
    gtk_container_add(GTK_CONTAINER(window), box); // Agregar el GtkBox a la ventana

    // Botón para registrar un empleado
    button = gtk_button_new_with_label("Registrar Producto");
    g_signal_connect(button, "clicked", G_CALLBACK(registrar_producto), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    // Botón para modificar un empleado
    button = gtk_button_new_with_label("Modificar Producto");
    g_signal_connect(button, "clicked", G_CALLBACK(modificar_producto), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    // Botón para eliminar un empleado
    button = gtk_button_new_with_label("Eliminar Producto");
    g_signal_connect(button, "clicked", G_CALLBACK(eliminar_producto), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    
    // Botón para mostrar la lista de empleados
    button = gtk_button_new_with_label("Mostrar Productos");
    g_signal_connect(button, "clicked", G_CALLBACK(mostrar_productos), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

        // Mostrar todos los widgets en la ventana
        gtk_widget_show_all(window);
}

// Callback para guardar un producto desde un dialogo GTK
void guardar_producto_callback(GtkDialog *dialog, gint response_id, gpointer user_data){
	GtkWidget **entrys = (GtkWidget **)user_data; // Obtener los widgets de entrada

    if (response_id == GTK_RESPONSE_ACCEPT) {// Si la respuesta es aceptar
		Pro productos;
 // Obtener los valores de los campos de entrada
 const char *codigo =gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener texto del nombre del producto;
 const char *nombre = gtk_entry_get_text(GTK_ENTRY(entrys[1])); // Obtener texto del nombre del producto
 const char *desc = gtk_entry_get_text(GTK_ENTRY(entrys[2])); // Obtener texto de la descripcion
 const char *bs = gtk_entry_get_text(GTK_ENTRY(entrys[3])); // Obtener texto del precio
 const char *cant = gtk_entry_get_text(GTK_ENTRY(entrys[4])); // Obtener texto de la cantidad de existencias de producto
 strncpy(productos.cd, codigo, sizeof(productos.cd) - 1); // Copiar el nombre del producto
 productos.cd[sizeof(productos.cd) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
 strncpy(productos.nombre, nombre, sizeof(productos.nombre) - 1); // Copiar el nombre del producto
 productos.nombre[sizeof (productos.nombre) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.desc, desc, sizeof(productos.desc) - 1); // Copiar la descripcion
 	productos.desc[sizeof (productos.desc) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.bs, bs, sizeof(productos.bs)-1); //Copiar el precio del producto
    productos.bs[sizeof (productos.bs) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.cant, cant, sizeof(cant)-1); //Copiar la cantidad del producto
    productos.preciobs=atoif(bs); // convertir el precio a una variable tipo flotante
    productos.cant=atoi(cant); //convertir la cantidad a una varible de tipo entera
    productos.codigo=atoi(codigo);//convertir el codigo a una variable de tipo entera
		// Validar campos y registrar el nombre
	if (validar_campos(productos,codigo,nombre, desc,bs) && registrar_producto("productos.txt", productos,codigo,nombre,desc,bs)) { // Si los campos son validos y el registro es exitoso
		GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), // Crear un dialogo de éxito
																	GTK_DIALOG_MODAL,
																	GTK_MESSAGE_INFO,
																	GTK_BUTTONS_OK,
																	"Producto registrado correctamente.");
					gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
					gtk_dialog_run(GTK_DIALOG(success_dialog)); // Mostrar el dialogo de éxito
					gtk_widget_destroy(success_dialog); // Destruir el dialogo de éxito
					gtk_widget_destroy(GTK_WIDGET(dialog)); // Cerrar el dialogo solo si el registro es exitoso
					g_free(entrys); // Liberar la memoria de las entradas solo si el registro es exitoso
				}
			} else { // Si la respuesta no es aceptar
				gtk_widget_destroy(GTK_WIDGET(dialog)); // Cerrar el dialogo si se cancela
				g_free(entrys); // Liberar la memoria de las entradas si se cancela
			}
} 


// Funcion para registrar un producto
int registrar_producto(const char *archivopro, Pro productos,const char *cod, const char *nombre,const char *desc,const char *bs){
		// Validar los campos del empleado y la categoria
		if (!validar_campos(productos, cod, nombre, desc, bs)) {
			return 0; // Fallo en la validacion
		}
	
		// Abrir el archivo en modo de adición
		FILE* file = fopen(archivopro, "a");
		if (!file) return 0; // Fallo al abrir el archivo
	
		// Escribir los datos del cliente en el archivo
		fprintf(file, "%s,%s,%s,%s,%s",productos.codigo, productos.nombre, productos.desc,productos.bs, productos.cant);
		fclose(file); // Cerrar el archivo
		return 1; 
	}


// Funcion para buscar un producto
int buscar_producto(const char *archivopro,Pro *producto ,const char *codigo){
		FILE *file = fopen(archivopro, "r");
		if (!file) {
			perror("Error al abrir el archivo"); // Imprimir mensaje de error
			return 0;
		}
	
		char linea[512];
		while (fgets(linea, sizeof(linea), file)) {
			// Validar que se hayan leído todos los campos
			if (sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,]" , producto->cd, producto->nombre, producto->desc, producto->bs, producto->cant) == 5){
				if (strcmp(producto->cd, codigo) == 0) {
					fclose(file);
					return 1;
				}
			} else {
				fprintf(stderr, "Error: línea con formato incorrecto: %s\n", linea);
			}
		}
	
		fclose(file);
		return 0;
	}

// Callback para buscar un producto widget GTK
void buscar_producto_callback(GtkWidget* widget, gpointer data){
	GtkWidget **entrys = (GtkWidget **)data; // Obtener los widgets de entrada

    // Validar que el campo de cédula sea un GtkEntry
    if (!GTK_IS_ENTRY(entrys[0])) {
        g_warning("El campo de cedula no es un GtkEntry valido."); // Mostrar advertencia si no es un GtkEntry valido
        return; // Salir de la funcion
    }

    const char *codigo = gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener el texto de la cedula
    Pro productos; // Crear una estructura Producto

    // Buscar el cliente por cedula
    if (buscar_producto("producto.txt",&productos,codigo)) {
        // Si se encuentra el Producto, llenar los campos con sus datos
        gtk_entry_set_text(GTK_ENTRY(entrys[0]), productos.codigo); // Establecer el codigo
        gtk_entry_set_text(GTK_ENTRY(entrys[1]), productos.nombre); // Establecer el nombre
        gtk_entry_set_text(GTK_ENTRY(entrys[2]), productos.desc); // Establecer la descripcion
        gtk_entry_set_text(GTK_ENTRY(entrys[3]), productos.bs); // Establecer la dirección
        gtk_entry_set_text(GTK_ENTRY(entrys[4]), productos.cant); // Establecer el telefono
        
        // Si no se encuentra el producto, mostrar un mensaje de error
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Producto no encontrado.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de error
        gtk_widget_destroy(dialog); // Destruir el dialogo
    }
}

// Funcion para modificar un producto ya existente
int modificar_producto(const char *archivopro, int codigo,char nombre[MAXCH],char desc[MAXD],float preciobs){
	FILE *file = fopen(archivopro, "r"); // Abrir el archivo en modo lectura
    if (!file) return 0; // Si no se puede abrir el archivo, retornar 0

    FILE *temp = fopen("temp.txt", "w"); // Crear un archivo temporal en modo escritura
    if (!temp) { // Si no se puede crear el archivo temporal
        fclose(file); // Cerrar el archivo original
        return 0; // Retornar 0
    }

    char linea[512]; // Buffer para leer cada linea del archivo
    int encontrado = 0; // Variable para indicar si se encontro el cliente

    while (fgets(linea, sizeof(linea), file)) { // Leer linea por linea del archivo
        Pro productos; // Crear una estructura productos   
        sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,]",productos.cd,productos.nombre, productos.desc, productos.bs,productos.cant);

        if (strcmp(productos.nombre, nombre) == 0) { // Si el producto coincide con la buscada
            encontrado = 1; // Marcar como encontrado
            // Escribir los datos del nuevo producto en el archivo temporal
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s\n");
        } else { // Si la cedula no coincide
            fputs(linea, temp); // Escribir la línea original en el archivo temporal
        }
    }

    fclose(file); // Cerrar el archivo original
    fclose(temp); // Cerrar el archivo temporal
    remove(archivopro); // Eliminar el archivo original
    rename("temp.txt", archivopro); // Renombrar el archivo temporal al nombre original

    return encontrado; // Retornar si se encontro el cliente
}

// Funcion para validar los campos de un producto
int validar_campos(Pro productos,const char *codigo,const char *nombre,const char *desc, const char *bs){

    // Validar nombre
    if (strlen(productos.nombre) == 0) { // Verificar si el campo 'Nombre' esta vacio
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Nombre' está vacio.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el dialogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(productos.nombre); i++) { // Recorrer cada caracter del nombre
        if (!g_ascii_isalpha(productos.nombre[i])) { // Verificar si no es una letra
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El nombre solo puede contener letras.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el dialogo
            return 0; // Retornar 0 indicando error
        }
    }

}

// Callback para guardar un producto desde un widget GTK
void guardar_producto_modificado(GtkWidget *widget, gpointer data){
    GtkWidget **entrys = (GtkWidget **)data; // Obtener los widgets de entrada

    // Validar que todos los widgets sean GtkEntry o GtkComboBoxText
    for (int i = 0; i < 12; i++) {
        if (i != 10 && !GTK_IS_ENTRY(entrys[i])) { // Si no es el indice 10 y no es un GtkEntry
            g_warning("El campo en el indice %d no es un GtkEntry valido.", i); // Mostrar advertencia
            return; // Salir de la funcion
        }
        if (i == 10 && !GTK_IS_COMBO_BOX_TEXT(entrys[i])) { // Si es el indice 10 y no es un GtkComboBoxText
            g_warning("El campo en el indice %d no es un GtkComboBoxText válido.", i); // Mostrar advertencia
            return; // Salir de la función
        }
    }

    Pro productos; // Crear una estructura Productos
    const char *codigo = gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener texto del codigo
    if (!codigo || strlen(codigo) == 0) { // Si la cedula esta vacia
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK, "Error: El campo 'Cedula' esta vacio."); // Crear un dialogo de error
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de error
        gtk_widget_destroy(dialog); // Destruir el dialogo de error
        return; // Salir de la función
    }

    // Obtener los valores de los campos de entrada
    const char *codigo =gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener texto del nombre del producto;
    const char *nombre = gtk_entry_get_text(GTK_ENTRY(entrys[1])); // Obtener texto del nombre del producto
    const char *desc = gtk_entry_get_text(GTK_ENTRY(entrys[2])); // Obtener texto de la descripcion
    const char *bs = gtk_entry_get_text(GTK_ENTRY(entrys[3])); // Obtener texto del precio
    const char *cant = gtk_entry_get_text(GTK_ENTRY(entrys[4])); // Obtener texto de la cantidad de existencias de producto


    // Copiar los valores a la estructura Productos
    strncpy(productos.cd, codigo, sizeof(productos.cd) - 1); // Copiar el nombre del producto
    productos.cd[sizeof(productos.cd) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.nombre, nombre, sizeof(productos.nombre) - 1); // Copiar el nombre del producto
    productos.nombre[sizeof (productos.nombre) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.desc, desc, sizeof(productos.desc) - 1); // Copiar la descripcion
    productos.desc[sizeof (productos.desc) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.bs, bs, sizeof(productos.bs)-1); //Copiar el precio del producto
productos.bs[sizeof (productos.bs) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
strncpy(productos.cant, cant, sizeof(cant)-1); //Copiar la cantidad del producto
productos.preciobs=atoif(bs); // convertir el precio a una variable tipo flotante
productos.cant=atoi(cant); //convertir la cantidad a una varible de tipo entera
productos.codigo=atoi(codigo);//convertir el codigo a una variable de tipo entera
    if (modificar_productos("productos.txt",productos,codigo)) { // Si la modificación es exitosa
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK, "Producto modificado correctamente."); // Crear un dialogo de exito
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de exito
        gtk_widget_destroy(dialog); // Destruir el dialogo de exito
    } else { // Si hay un error en la modificacion
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK, "Error al modificar el producto."); // Crear un dialogo de error
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de error
        gtk_widget_destroy(dialog); // Destruir el dialogo de error
    }

}

// Funcion para eliminar un producto por su codigo
int eliminar_producto(const char* archivopro, const char *codigo){
	FILE* file = fopen(archivopro, "r"); // Abrir el archivo en modo lectura
    if (!file) {
        perror("Error al abrir el archivo"); // Mostrar error si no se puede abrir el archivo
        return 0; // Retornar 0 indicando fallo
    }

    FILE* temp = fopen("temp.txt", "w"); // Crear un archivo temporal en modo escritura
    if (!temp) {
        perror("Error al crear el archivo temporal"); // Mostrar error si no se puede crear el archivo temporal
        fclose(file); // Cerrar el archivo original
        return 0; // Retornar 0 indicando fallo
    }

    char buffer[512]; // Buffer para leer cada linea del archivo
    int encontrado = 0; // Variable para indicar si se encontro el producto a eliminar

    while (fgets(buffer, sizeof(buffer), file)) { // Leer linea por linea del archivo
        char producto_actual[20]; // Buffer para almacenar el producto actual por su codigo
        sscanf(buffer,"%19[^,]",producto_actual); // Extraer el producto por su codigo (hasta la primera coma)

        if (strcmp(producto_actual,codigo) == 0) {
            encontrado = 1; // Marcar como encontrado si la cedula coincide
        } else {
            fputs(buffer, temp); // Copiar las lineas no coincidentes al archivo temporal
        }
    }

    fclose(file); // Cerrar el archivo original
    fclose(temp); // Cerrar el archivo temporal

    // Reemplazar el archivo original solo si se encontró el cliente a eliminar
    if (encontrado) {
        remove(archivopro); // Eliminar el archivo original
        rename("temp.txt", archivopro); // Renombrar el archivo temporal al nombre original
    } else {
        remove("temp.txt"); // Eliminar el archivo temporal si no se encontro nada
    }

    return encontrado; // Retornar si se encontro el cliente a eliminar

}

// Callback para eliminar un producto desde un widget GTK
void eliminar_producto_callback(GtkWidget* widget, gpointer data){
    GtkWidget* entry_cedula = GTK_WIDGET(data); // Obtener el GtkEntry pasado como "data"

    if (!GTK_IS_ENTRY(entry_cedula)) { // Validar que sea un GtkEntry
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "El campo Cedula no es valido."); // Crear un dialogo de advertencia
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el dialogo de advertencia
        return; // Salir de la funcion
    }

    const char* codigo = gtk_entry_get_text(GTK_ENTRY(entry_cedula)); // Obtener el texto de la cedula

    if (codigo == NULL || strlen(codigo) == 0) { // Validar que no este vacio
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "El campo esta vacio."); // Crear un dialogo de advertencia
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el dialogo de advertencia
        return; // Salir de la funcion
    }

    Pro productos; // Crear una estructura Productos
    if (!buscar_producto("productos.txt",&productos,codigo) ) { // Buscar al producto por codigo 
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "Producto no encontrado."); // Crear un dialogo de advertencia
                                                gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el dialogo de advertencia
        return; // Salir de la funcion
    }

    GtkWidget* dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO,
        "Codigo: %d \n"
        "Nombre: %s \n"
        "Descripcion: %s \n"
        "Precio: %f \n"
        "Cantidad: %d \n"
        "¿Está seguro de que desea eliminar este producto?",
        productos.codigo,productos.nombre,productos.desc,productos.preciobs,productos.cant); // Crear un dialogo de confirmacion
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
    gint respuesta = gtk_dialog_run(GTK_DIALOG(dialog)); // Ejecutar el dialogo de confirmacion
    gtk_widget_destroy(dialog); // Destruir el dialogo de confirmacion

    if (respuesta == GTK_RESPONSE_YES) { // Si la respuesta es "Si"
        if (eliminar_cliente("productos.txt", codigo)) { // Eliminar el cliente
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                    GTK_BUTTONS_OK, "Producto eliminado correctamente."); // Crear un dialogo de exito
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de exito
            gtk_widget_destroy(dialog); // Destruir el dialogo de exito
            gtk_widget_destroy(gtk_widget_get_toplevel(widget)); // Cerrar la ventana del formulario
            return; // Salir de la funcion
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                    GTK_BUTTONS_OK, "Error al eliminar el cliente."); // Crear un dialogo de error
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de dialogo
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el dialogo de error
            gtk_widget_destroy(dialog); // Destruir el dialogo de error
            return; // Salir de la funcion
        }
    }
}

void mostrar_productos(GtkWidget *widget, gpointer data){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lista de Productos"); // Establecer el título de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 1050, 600); // Establecer el tamaño predeterminado de la ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centrar la ventana

    // Crear un contenedor vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox); // Agregar el contenedor vertical a la ventana

    // Crear un contenedor con desplazamiento para los empleados
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0); // Agregar el contenedor con desplazamiento al contenedor vertical

    // Crear una tabla para mostrar los datos de los empleados
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5); // Establecer el espaciado entre filas
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10); // Establecer el espaciado entre columnas
    gtk_container_add(GTK_CONTAINER(scrolled_window), grid); // Agregar la tabla al contenedor con desplazamiento

    // Separador
    gtk_box_pack_start(GTK_BOX(vbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL), FALSE, FALSE, 5);

    // Encabezados de la tabla
    const char *headers[] = {
        "Codigo", "Nombre del producto", "Descripcion del producto", "Precio del producto" "Cantidad del producto"
    };
    int num_headers = sizeof(headers) / sizeof(headers[0]); // Calcular el número de encabezados

    for (int col = 0; col < num_headers; col++) {
        GtkWidget *label = gtk_label_new(headers[col]); // Crear un label para cada encabezado
        gtk_grid_attach(GTK_GRID(grid), label, col * 2, 0, 1, 1); // Agregar el label a la tabla
        if (col < num_headers - 1) {
            gtk_grid_attach(GTK_GRID(grid), gtk_separator_new(GTK_ORIENTATION_VERTICAL), col * 2 + 1, 0, 1, 1); // Agregar un separador vertical
        }
    }

    // Leer empleados desde el archivo
    FILE *file_productos = fopen("productos.txt", "r");
    if (!file_productos) { // Verificar si se pudo abrir el archivo de empleados
        GtkWidget *error_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Error: No se pudo abrir el archivo de empleados.");
        gtk_dialog_run(GTK_DIALOG(error_dialog)); // Mostrar un cuadro de diálogo de error
        gtk_widget_destroy(error_dialog); // Destruir el cuadro de diálogo de error
        return;
    }

    // Leer y mostrar cada empleado
    char linea[512];
    int row = 1;
    while (fgets(linea, sizeof(linea), file_productos)) { // Leer cada línea del archivo
        Pro productos;
        sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,]",productos.cd,productos.nombre, productos.desc, productos.bs,productos.cant);// Parsear los datos del producto

        // Crear etiquetas para cada campo y agregar al grid
        const char *datos[] = {productos.cd,productos.nombre, productos.desc, productos.bs};
        for (int col = 0; col < num_headers - 1; col++) {
            GtkWidget *label = gtk_label_new(datos[col]); // Crear un label para cada dato
            gtk_grid_attach(GTK_GRID(grid), label, col * 2, row, 1, 1); // Agregar el label a la tabla
            if (col < num_headers - 1) {
                gtk_grid_attach(GTK_GRID(grid), gtk_separator_new(GTK_ORIENTATION_VERTICAL), col * 2 + 1, row, 1, 1); // Agregar un separador vertical
            }
        }
        // Separador horizontal
        gtk_grid_attach(GTK_GRID(grid), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL), 0, row + 1, num_headers * 2 - 1, 1); // Agregar un separador horizontal

        row += 2; // Incrementar la fila
    }
    fclose(file_productos); // Cerrar el archivo de empleados

    // Mostrar la ventana con todos los datos
    gtk_widget_show_all(window);
}
void QuickSort(Pro vectorpro [], int inicio, int fin){
    
}
