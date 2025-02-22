//trabajadores.c
#include "hipermercado_cachamay.h" // Incluir el archivo de cabecera para la interfaz gráfica
#include "trabajadores.h" // Incluir el archivo de cabecera para la estructura trabajador y funciones relacionadas
#include <stdio.h> // Incluir la biblioteca estándar de entrada/salida
#include <stdlib.h> // Incluir la biblioteca estándar de utilidades
#include <string.h> // Incluir la biblioteca estándar de manejo de cadenas
#include <ctype.h> // Incluir la biblioteca estándar de funciones de caracteres
#include <time.h> // Incluir la biblioteca estándar de tiempo

//mostrar los botonesz de crear, modificar, y crear 
void crear_ventana_de_trabajdores(GtkApplication *app){
    GtkWidget *window; // Puntero a la ventana principal
    GtkWidget *box; // Puntero al contenedor vertical para los botones
    GtkWidget *button; // Puntero a los botones de la interfaz

    // Crear una nueva ventana de la aplicación
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema del Hipermercado Cachamay"); // Establecer el título de la ventana
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
    button = gtk_button_new_with_label("Registrar Trabajador");
    g_signal_connect(button, "clicked", G_CALLBACK(mostrar_formulario_registro_empleado), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    // Botón para modificar un empleado
    button = gtk_button_new_with_label("Modificar Trabajador");
    g_signal_connect(button, "clicked", G_CALLBACK(modificar_empleado), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    // Botón para eliminar un empleado
    button = gtk_button_new_with_label("Eliminar Trabajador");
    g_signal_connect(button, "clicked", G_CALLBACK(mostrar_formulario_eliminar_empleado), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

    
    // Botón para mostrar la lista de empleados
    button = gtk_button_new_with_label("Mostrar Trabajadores");
    g_signal_connect(button, "clicked", G_CALLBACK(mostrar_empleados), NULL); // Conectar la señal "clicked" al callback
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // Agregar el botón al GtkBox

        // Mostrar todos los widgets en la ventana
        gtk_widget_show_all(window);
}

void mostrar_formulario_registro_empleado(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;  //puntero a GtkWidget para el diálogo
    GtkWidget *content_area;    //puntero a GtkWidget para el área de contenido del diálogo
    GtkWidget *grid;    //puntero a GtkWidget para la cuadrícula dentro del área de contenido
    GtkWidget *label;   //puntero a GtkWidget para una etiqueta dentro de la cuadrícula
    GtkWidget **entrys = g_malloc(sizeof(GtkWidget *) * 12); // Array para almacenar los campos de entrada

    // Crear un nuevo cuadro de diálogo con botones "Cancelar" y "Registrar"
    dialog = gtk_dialog_new_with_buttons("Registrar Empleado",
                                        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_DIALOG_MODAL,
                                        "_Cancelar", GTK_RESPONSE_CANCEL,
                                        "Registrar", GTK_RESPONSE_ACCEPT,
                                        NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo

    // Obtener el área de contenido del cuadro de diálogo
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    grid = gtk_grid_new(); // Crear una nueva cuadrícula para organizar los widgets
    gtk_container_add(GTK_CONTAINER(content_area), grid); // Agregar la cuadrícula al área de contenido

    // Crear y agregar los campos de entrada al grid
    const char *labels[] = {"Cédula", "Nombre", "Segundo Nombre", "Apellido", "Segundo Apellido",
                            "Dirección", "Telefono","Fecha de Ingreso(DD-MM-AAAA)"};
    for (int i = 0; i < 10; i++) {
        label = gtk_label_new(labels[i]); // Crear una nueva etiqueta para cada campo
        entrys[i] = gtk_entry_new(); // Crear un nuevo campo de entrada
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1); // Agregar la etiqueta a la cuadrícula
        gtk_grid_attach(GTK_GRID(grid), entrys[i], 1, i, 1, 1); // Agregar el campo de entrada a la cuadrícula
    }

    // Conectar la señal "response" del diálogo a la función guardar_empleado_callback
    g_signal_connect(dialog, "response", G_CALLBACK(guardar_empleado_callback), entrys);

    gtk_widget_show_all(dialog); // Mostrar todos los widgets en el cuadro de diálogo
}

void mostrar_formulario_eliminar_empleado(GtkWidget *widget, gpointer data) {
    GtkWidget *window; // Puntero a la ventana principal
    GtkWidget *grid; // Puntero a la cuadrícula para organizar los widgets
    GtkWidget *label_cedula; // Puntero a la etiqueta para el campo de cédula
    GtkWidget *entry_cedula; // Puntero al campo de entrada para la cédula
    GtkWidget *button_eliminar; // Puntero al botón de eliminar

    // Crear una nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Empleado"); // Establecer el título de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 50); // Establecer el tamaño predeterminado de la ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centrar la ventana

    // Crear una nueva cuadrícula y agregarla a la ventana
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear una etiqueta para el campo de cédula y agregarla a la cuadrícula
    label_cedula = gtk_label_new("Cédula:");
    gtk_grid_attach(GTK_GRID(grid), label_cedula, 0, 0, 1, 1);

    // Crear un campo de entrada para la cédula y agregarlo a la cuadrícula
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 0, 2, 1);

    // Crear un botón de eliminar y agregarlo a la cuadrícula
    button_eliminar = gtk_button_new_with_label("Eliminar");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 3, 0, 1, 1);

    // Conectar el botón "Eliminar" al callback
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(eliminar_empleado_callback), entry_cedula);

    // Mostrar todos los widgets en la ventana
    gtk_widget_show_all(window);
}
// Para generar un código al azar
char* generar_codigo() {
    static char codigo[9]; // Asume que el código tendrá 8 caracteres + terminador nulo
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 8; i++) {
        codigo[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    codigo[8] = '\0';
    return codigo;
}
// Callback para guardar un empleado
void guardar_empleado_callback(GtkDialog *dialog, gint response_id, gpointer user_data) {
    GtkWidget **entrys = (GtkWidget **)user_data; // Obtener los widgets de entrada

    if (response_id == GTK_RESPONSE_ACCEPT) { // Si la respuesta es aceptar
        trabajador empleado; // Crear una estructura Empleado

        // Obtener los valores de los campos de entrada
        const char *cedula = gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener texto de la cédula
        const char *nombre = gtk_entry_get_text(GTK_ENTRY(entrys[1])); // Obtener texto del nombre
        const char *segundo_nombre = gtk_entry_get_text(GTK_ENTRY(entrys[2])); // Obtener texto del segundo nombre
        const char *apellido = gtk_entry_get_text(GTK_ENTRY(entrys[3])); // Obtener texto del apellido
        const char *segundo_apellido = gtk_entry_get_text(GTK_ENTRY(entrys[4])); // Obtener texto del segundo apellido
        const char *direccion = gtk_entry_get_text(GTK_ENTRY(entrys[5])); // Obtener texto de la dirección
        const char *fecha_ingreso = gtk_entry_get_text(GTK_ENTRY(entrys[6])); // Obtener texto de la fecha de ingreso
        const char *telefono = gtk_entry_get_text(GTK_ENTRY(entrys[12])); // Obtener texto de telefono

        // Copiar los valores a la estructura Empleado
        strncpy(empleado.cedula, cedula, sizeof(empleado.cedula) - 1); // Copiar la cédula
        empleado.cedula[sizeof(empleado.cedula) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.nombre, nombre, sizeof(empleado.nombre) - 1); // Copiar el nombre
        empleado.nombre[sizeof(empleado.nombre) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.segundo_nombre, segundo_nombre, sizeof(empleado.segundo_nombre) - 1); // Copiar el segundo nombre
        empleado.segundo_nombre[sizeof(empleado.segundo_nombre) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.apellido, apellido, sizeof(empleado.apellido) - 1); // Copiar el apellido
        empleado.apellido[sizeof(empleado.apellido) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.segundo_apellido, segundo_apellido, sizeof(empleado.segundo_apellido) - 1); // Copiar el segundo apellido
        empleado.segundo_apellido[sizeof(empleado.segundo_apellido) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.direccion, direccion, sizeof(empleado.direccion) - 1); // Copiar la dirección
        empleado.direccion[sizeof(empleado.direccion) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo
        strncpy(empleado.telefono, telefono, sizeof(empleado.telefono) - 1); // Copiar la fecha de ingreso
        empleado.telefono[sizeof(empleado.telefono) - 1] = '\0'; // Asegurarse de que la cadena termine en nulo

        // Validar campos y registrar el empleado
        if (validar_campos(empleado, cedula, NULL) && registrar_empleado("trabajador.txt", empleado, cedula)) { // Si los campos son válidos y el registro es exitoso
            GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), // Crear un diálogo de éxito
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "Trabajador registrado correctamente.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
            gtk_dialog_run(GTK_DIALOG(success_dialog)); // Mostrar el diálogo de éxito
            gtk_widget_destroy(success_dialog); // Destruir el diálogo de éxito
            gtk_widget_destroy(GTK_WIDGET(dialog)); // Cerrar el diálogo solo si el registro es exitoso
            g_free(entrys); // Liberar la memoria de las entradas solo si el registro es exitoso
        }
    } else { // Si la respuesta no es aceptar
        gtk_widget_destroy(GTK_WIDGET(dialog)); // Cerrar el diálogo si se cancela
        g_free(entrys); // Liberar la memoria de las entradas si se cancela
    }
}

int registrar_empleado(const char* archivo, trabajador empleado, const char *cedula) {
    // Validar los campos del empleado y la categoría
    if (!validar_campos(empleado, cedula, NULL)) {
        return 0; // Fallo en la validación
    }

    // Verificar si la cédula ya está registrada
    if (cedula_duplicada(archivo, empleado.cedula)) {
        // Mostrar un mensaje de advertencia si la cédula ya está registrada
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "La cedula ya está registrada.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return 0; // Fallo
    }

    // Abrir el archivo en modo de adición
    FILE* file = fopen(archivo, "a");
    if (!file) return 0; // Fallo al abrir el archivo
    // Escribir los datos del empleado en el archivo
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,\n",
            empleado.cedula, empleado.nombre, empleado.segundo_nombre,
            empleado.apellido, empleado.segundo_apellido, empleado.direccion,
            empleado.fecha_ingreso,empleado.telefono, empleado.codigo);
    fclose(file); // Cerrar el archivo
    return 1; // Éxito
}

int validar_campos(trabajador empleado, const char *cedula, const char *codigo) {
    // Validar cédula
    if (strlen(empleado.cedula) == 0) { // Verificar si el campo 'Cédula' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Cédula' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(empleado.cedula); i++) { // Recorrer cada carácter de la cédula
        if (!g_ascii_isdigit(empleado.cedula[i])) { // Verificar si no es un dígito
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: La cédula solo puede contener dígitos.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el diálogo
            return 0; // Retornar 0 indicando error
        }
    }

    // Validar nombre
    if (strlen(empleado.nombre) == 0) { // Verificar si el campo 'Nombre' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Nombre' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(empleado.nombre); i++) { // Recorrer cada carácter del nombre
        if (!g_ascii_isalpha(empleado.nombre[i])) { // Verificar si no es una letra
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El nombre solo puede contener letras.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el diálogo
            return 0; // Retornar 0 indicando error
        }
    }

    // Validar segundo nombre
    if (strlen(empleado.segundo_nombre) == 0) { // Verificar si el campo 'Segundo Nombre' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Segundo Nombre' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(empleado.segundo_nombre); i++) { // Recorrer cada carácter del segundo nombre
        if (!g_ascii_isalpha(empleado.segundo_nombre[i])) { // Verificar si no es una letra
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El segundo nombre solo puede contener letras.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el diálogo
            return 0; // Retornar 0 indicando error
        }
    }

    // Validar apellido
    if (strlen(empleado.apellido) == 0) { // Verificar si el campo 'Apellido' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Apellido' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(empleado.apellido); i++) { // Recorrer cada carácter del apellido
        if (!g_ascii_isalpha(empleado.apellido[i])) { // Verificar si no es una letra
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El apellido solo puede contener letras.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el diálogo
            return 0; // Retornar 0 indicando error
        }
    }

    // Validar segundo apellido 
    if (strlen(empleado.segundo_apellido) == 0) { // Verificar si el campo 'Segundo Apellido' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Segundo Apellido' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }
    for (size_t i = 0; i < strlen(empleado.segundo_apellido); i++) { // Recorrer cada carácter del segundo apellido
        if (!g_ascii_isalpha(empleado.segundo_apellido[i])) { // Verificar si no es una letra
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El segundo apellido solo puede contener letras.");
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                    
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
            gtk_widget_destroy(dialog); // Destruir el diálogo
            return 0; // Retornar 0 indicando error
        }
    }

    // Validar dirección
    if (strlen(empleado.direccion) == 0) { // Verificar si el campo 'Dirección' está vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Dirección' está vacío.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }

    // Validar teléfono
    if (!validar_telefono(empleado.telefono)) { // Verificar si el teléfono es válido
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Teléfono' no es correcto, verifique los datos.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                        
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }

    // Validar fecha de ingreso
    if (!validar_fecha(empleado.fecha_ingreso)) { // Verificar si la fecha de ingreso es válida
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Error: El campo 'Fecha de Ingreso' no es correcto, verifique los datos.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo                                        
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar mensaje de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
        return 0; // Retornar 0 indicando error
    }

    return 1; // Validación exitosa
}

int validar_fecha(const char *fecha) {
    // Verificar longitud
    if (strlen(fecha) != 10) { // La fecha debe tener exactamente 10 caracteres
        return 0; // Retornar 0 si la longitud no es correcta
    }

    // Verificar formato DD-MM-AAAA
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) { // Las posiciones 2 y 5 deben ser guiones
            if (fecha[i] != '-') {
                return 0; // Retornar 0 si no hay guiones en las posiciones correctas
            }
        } else {
            if (!isdigit(fecha[i])) { // Las demás posiciones deben ser dígitos
                return 0; // Retornar 0 si no son dígitos
            }
        }
    }

    // Extraer día, mes y año
    int dia = atoi(fecha); // Convertir los primeros dos caracteres a entero (día)
    int mes = atoi(fecha + 3); // Convertir los caracteres 4 y 5 a entero (mes)
    int anio = atoi(fecha + 6); // Convertir los últimos cuatro caracteres a entero (año)

    // Verificar rango de día y mes
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12) { // Verificar que el día y el mes estén en rangos válidos
        return 0; // Retornar 0 si el día o el mes están fuera de rango
    }

    // Verificar días válidos para cada mes
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) { // Abril, junio, septiembre y noviembre tienen máximo 30 días
        return 0; // Retornar 0 si el día es mayor a 30 en estos meses
    }
    if (mes == 2) { // Febrero
        // Verificar año bisiesto
        int es_bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0); // Determinar si el año es bisiesto
        if (dia > 29 || (dia == 29 && !es_bisiesto)) { // Febrero tiene máximo 29 días en años bisiestos y 28 en no bisiestos
            return 0; // Retornar 0 si el día es inválido para febrero
        }
    }

    return 1; // Retornar 1 si la fecha es válida
}

int cedula_duplicada(const char* archivo, const char* cedula) {
    FILE* file = fopen(archivo, "r"); // Abrir el archivo en modo lectura
    if (!file) return 0; // Si el archivo no existe, no hay duplicados

    char linea[256]; // Buffer para leer cada línea del archivo
    while (fgets(linea, sizeof(linea), file)) { // Leer línea por línea
        char cedula_existente[20]; // Buffer para almacenar la cédula existente
        sscanf(linea, "%[^,]", cedula_existente); // Extraer la cédula de la línea
        if (strcmp(cedula, cedula_existente) == 0) { // Comparar la cédula con la cédula existente
            fclose(file); // Cerrar el archivo
            return 1; // Cédula encontrada, hay duplicado
        }
    }
    fclose(file); // Cerrar el archivo
    return 0; // No se encontró duplicado
}

int modificar_empleado(const char* archivo, const char* cedula, trabajador nuevo_empleado) {
    FILE *file = fopen(archivo, "r"); // Abrir el archivo en modo lectura
    if (!file) return 0; // Si no se puede abrir el archivo, retornar 0

    FILE *temp = fopen("temp.txt", "w"); // Crear un archivo temporal en modo escritura
    if (!temp) { // Si no se puede crear el archivo temporal
        fclose(file); // Cerrar el archivo original
        return 0; // Retornar 0
    }

    char linea[512]; // Buffer para leer cada línea del archivo
    int encontrado = 0; // Variable para indicar si se encontró el empleado

    while (fgets(linea, sizeof(linea), file)) { // Leer línea por línea del archivo
        trabajador empleado; // Crear una estructura Empleado
        sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d",
               empleado.cedula, empleado.nombre, empleado.segundo_nombre, empleado.apellido,
               empleado.segundo_apellido, empleado.direccion, empleado.fecha_ingreso, 
               empleado.codigo); // Extraer los datos del empleado de la línea

        if (strcmp(empleado.cedula, cedula) == 0) { // Si la cédula coincide con la buscada
            encontrado = 1; // Marcar como encontrado
            // Escribir los datos del nuevo empleado en el archivo temporal
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s",
            nuevo_empleado.cedula, nuevo_empleado.nombre, nuevo_empleado.segundo_nombre,
            nuevo_empleado.apellido, nuevo_empleado.segundo_apellido, nuevo_empleado.direccion,
            nuevo_empleado.fecha_ingreso, nuevo_empleado.codigo);
        } else { // Si la cédula no coincide
            fputs(linea, temp); // Escribir la línea original en el archivo temporal
        }
    }

    fclose(file); // Cerrar el archivo original
    fclose(temp); // Cerrar el archivo temporal
    remove(archivo); // Eliminar el archivo original
    rename("temp.txt", archivo); // Renombrar el archivo temporal al nombre original

    return encontrado; // Retornar si se encontró el empleado
}

void buscar_empleado_callback(GtkWidget *widget, gpointer data) {
    GtkWidget **entrys = (GtkWidget **)data; // Obtener los widgets de entrada

    // Validar que el campo de cédula sea un GtkEntry
    if (!GTK_IS_ENTRY(entrys[0])) {
        g_warning("El campo de cédula no es un GtkEntry válido."); // Mostrar advertencia si no es un GtkEntry válido
        return; // Salir de la función
    }

    const char *cedula = gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener el texto de la cédula
    trabajador empleado; // Crear una estructura Empleado

    // Buscar el empleado por cédula
    if (buscar_empleado("trabajadores.txt", cedula, &empleado)) {
        // Si se encuentra el empleado, llenar los campos con sus datos
        gtk_entry_set_text(GTK_ENTRY(entrys[1]), empleado.nombre); // Establecer el nombre
        gtk_entry_set_text(GTK_ENTRY(entrys[2]), empleado.segundo_nombre); // Establecer el segundo nombre
        gtk_entry_set_text(GTK_ENTRY(entrys[3]), empleado.apellido); // Establecer el apellido
        gtk_entry_set_text(GTK_ENTRY(entrys[4]), empleado.segundo_apellido); // Establecer el segundo apellido
        gtk_entry_set_text(GTK_ENTRY(entrys[5]), empleado.direccion); // Establecer la dirección
        gtk_entry_set_text(GTK_ENTRY(entrys[6]), empleado.fecha_ingreso); // Establecer la fecha de ingreso
        gtk_entry_set_text(GTK_ENTRY(entrys[7]), empleado.codigo); // Establecer codigo
 
    } else {
        // Si no se encuentra el empleado, mostrar un mensaje de error
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_OK, "Empleado no encontrado.");
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de error
        gtk_widget_destroy(dialog); // Destruir el diálogo
    }
}

// Función para buscar un empleado por cédula
int buscar_empleado(const char *archivo, const char *cedula, trabajador *empleado) {
    FILE *file = fopen(archivo, "r"); // Abrir el archivo en modo lectura
    if (!file) return 0; // Si no se puede abrir el archivo, retornar 0

    char buffer[512]; // Buffer para leer cada línea del archivo
    while (fgets(buffer, sizeof(buffer), file)) { // Leer línea por línea del archivo
        // Extraer los datos del empleado de la línea
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
               empleado->cedula, empleado->nombre, empleado->segundo_nombre, empleado->apellido,
               empleado->segundo_apellido, empleado->direccion, empleado->fecha_ingreso, empleado->codigo);

        if (strcmp(empleado->cedula, cedula) == 0) { // Comparar la cédula con la cédula buscada
            fclose(file); // Cerrar el archivo
            return 1; // Retornar 1 si se encuentra el empleado
        }
    }
    fclose(file); // Cerrar el archivo
    return 0; // Retornar 0 si no se encuentra el empleado
}

void guardar_empleado_modificado(GtkWidget *widget, gpointer data) {
    GtkWidget **entrys = (GtkWidget **)data; // Obtener los widgets de entrada

    // Validar que todos los widgets sean GtkEntry o GtkComboBoxText
    for (int i = 0; i < 12; i++) {
        if (i != 10 && !GTK_IS_ENTRY(entrys[i])) { // Si no es el índice 10 y no es un GtkEntry
            g_warning("El campo en el índice %d no es un GtkEntry válido.", i); // Mostrar advertencia
            return; // Salir de la función
        }
        if (i == 10 && !GTK_IS_COMBO_BOX_TEXT(entrys[i])) { // Si es el índice 10 y no es un GtkComboBoxText
            g_warning("El campo en el índice %d no es un GtkComboBoxText válido.", i); // Mostrar advertencia
            return; // Salir de la función
        }
    }

    trabajador empleado; // Crear una estructura Empleado
    const char *cedula = gtk_entry_get_text(GTK_ENTRY(entrys[0])); // Obtener texto de la cédula

    if (!cedula || strlen(cedula) == 0) { // Si la cédula está vacía
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK, "Error: El campo 'Cédula' está vacío."); // Crear un diálogo de error
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de error
        gtk_widget_destroy(dialog); // Destruir el diálogo de error
        return; // Salir de la función
    }

    // Obtener los valores de los campos de entrada
    const char *nombre = gtk_entry_get_text(GTK_ENTRY(entrys[1])); // Obtener texto del nombre
    const char *segundo_nombre = gtk_entry_get_text(GTK_ENTRY(entrys[2])); // Obtener texto del segundo nombre
    const char *apellido = gtk_entry_get_text(GTK_ENTRY(entrys[3])); // Obtener texto del apellido
    const char *segundo_apellido = gtk_entry_get_text(GTK_ENTRY(entrys[4])); // Obtener texto del segundo apellido
    const char *direccion = gtk_entry_get_text(GTK_ENTRY(entrys[5])); // Obtener texto de la dirección
    const char *fecha_ingreso = gtk_entry_get_text(GTK_ENTRY(entrys[6])); // Obtener texto de la fecha de ingreso
    const char *generar_codigo = gtk_entry_get_text(GTK_ENTRY(entrys[8])); // Obtener texto del cargo
    const char *departamento = gtk_entry_get_text(GTK_ENTRY(entrys[9])); // Obtener texto del departamento
    const char *categoria = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(entrys[10])); // Obtener la categoría seleccionada
    const char *salario_base_str = gtk_entry_get_text(GTK_ENTRY(entrys[11])); // Obtener texto del salario base

    // Copiar los valores a la estructura Empleado
    strncpy(empleado.cedula, cedula, sizeof(empleado.cedula) - 1); // Copiar la cédula
    strncpy(empleado.nombre, nombre, sizeof(empleado.nombre) - 1); // Copiar el nombre
    strncpy(empleado.segundo_nombre, segundo_nombre, sizeof(empleado.segundo_nombre) - 1); // Copiar el segundo nombre
    strncpy(empleado.apellido, apellido, sizeof(empleado.apellido) - 1); // Copiar el apellido
    strncpy(empleado.segundo_apellido, segundo_apellido, sizeof(empleado.segundo_apellido) - 1); // Copiar el segundo apellido
    strncpy(empleado.direccion, direccion, sizeof(empleado.direccion) - 1); // Copiar la dirección
    strncpy(empleado.fecha_ingreso, fecha_ingreso, sizeof(empleado.fecha_ingreso) - 1); // Copiar la fecha de ingreso
    strncpy(empleado.codigo, generar_codigo, sizeof(empleado.codigo) - 1); // Copiar codigo

    if (modificar_empleado("trabajadores.txt", cedula, empleado)) { // Si la modificación es exitosa
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK, "Empleado modificado correctamente."); // Crear un diálogo de éxito
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de éxito
        gtk_widget_destroy(dialog); // Destruir el diálogo de éxito
    } else { // Si hay un error en la modificación
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK, "Error al modificar el empleado."); // Crear un diálogo de error
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de error
        gtk_widget_destroy(dialog); // Destruir el diálogo de error
    }
}

int eliminar_empleado(const char* archivo, const char* cedula) {
    FILE* file = fopen(archivo, "r"); // Abrir el archivo en modo lectura
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

    char buffer[512]; // Buffer para leer cada línea del archivo
    int encontrado = 0; // Variable para indicar si se encontró el empleado

    while (fgets(buffer, sizeof(buffer), file)) { // Leer línea por línea del archivo
        char cedula_actual[20]; // Buffer para almacenar la cédula actual
        sscanf(buffer, "%19[^,]", cedula_actual); // Extraer la cédula (hasta la primera coma)

        if (strcmp(cedula_actual, cedula) == 0) {
            encontrado = 1; // Marcar como encontrado si la cédula coincide
        } else {
            fputs(buffer, temp); // Copiar las líneas no coincidentes al archivo temporal
        }
    }

    fclose(file); // Cerrar el archivo original
    fclose(temp); // Cerrar el archivo temporal

    // Reemplazar el archivo original solo si se encontró el empleado
    if (encontrado) {
        remove(archivo); // Eliminar el archivo original
        rename("temp.txt", archivo); // Renombrar el archivo temporal al nombre original
    } else {
        remove("temp.txt"); // Eliminar el archivo temporal si no se encontró nada
    }

    return encontrado; // Retornar si se encontró el empleado
}

void eliminar_empleado_callback(GtkWidget* widget, gpointer data) {
    GtkWidget* entry_cedula = GTK_WIDGET(data); // Obtener el GtkEntry pasado como "data"

    if (!GTK_IS_ENTRY(entry_cedula)) { // Validar que sea un GtkEntry
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "El campo Cédula no es válido."); // Crear un diálogo de advertencia
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el diálogo de advertencia
        return; // Salir de la función
    }

    const char* cedula = gtk_entry_get_text(GTK_ENTRY(entry_cedula)); // Obtener el texto de la cédula

    if (cedula == NULL || strlen(cedula) == 0) { // Validar que no esté vacío
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "El campo está vacío."); // Crear un diálogo de advertencia
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el diálogo de advertencia
        return; // Salir de la función
    }

    trabajador empleado; // Crear una estructura Empleado
    if (!buscar_empleado("trabajadores.txt", cedula, &empleado)) { // Buscar el empleado por cédula
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                GTK_BUTTONS_OK, "Empleado no encontrado."); // Crear un diálogo de advertencia
                                                gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
        gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de advertencia
        gtk_widget_destroy(dialog); // Destruir el diálogo de advertencia
        return; // Salir de la función
    }

    GtkWidget* dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO,
        "Empleado: %s %s %s %s\n"
        "Dirección: %s\nFecha de Ingreso: %s\nCodigo: %s\n"
        "¿Está seguro de que desea eliminar al empleado?",
        empleado.nombre, empleado.segundo_nombre, empleado.apellido, empleado.segundo_apellido,
        empleado.direccion, empleado.fecha_ingreso, empleado.codigo); // Crear un diálogo de confirmación
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
    gint respuesta = gtk_dialog_run(GTK_DIALOG(dialog)); // Ejecutar el diálogo de confirmación
    gtk_widget_destroy(dialog); // Destruir el diálogo de confirmación

    if (respuesta == GTK_RESPONSE_YES) { // Si la respuesta es "Sí"
        if (eliminar_empleado("trabajadores.txt", cedula)) { // Eliminar el empleado
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                    GTK_BUTTONS_OK, "Empleado eliminado correctamente."); // Crear un diálogo de éxito
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de éxito
            gtk_widget_destroy(dialog); // Destruir el diálogo de éxito
            gtk_widget_destroy(gtk_widget_get_toplevel(widget)); // Cerrar la ventana del formulario
            return; // Salir de la función
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, 
                                                    GTK_BUTTONS_OK, "Error al eliminar el empleado."); // Crear un diálogo de error
                                                    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER); // Centrar el cuadro de diálogo
            gtk_dialog_run(GTK_DIALOG(dialog)); // Mostrar el diálogo de error
            gtk_widget_destroy(dialog); // Destruir el diálogo de error
            return; // Salir de la función
        }
    }
}

void mostrar_empleados(GtkWidget *widget, gpointer data) {
    // Crear una nueva ventana
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lista de Empleados"); // Establecer el título de la ventana
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
        "Cédula", "Nombre", "Segundo Nombre", "Apellido", "Segundo Apellido",
        "Dirección", "Fecha de Ingreso", "Profesión", "Cargo", "Departamento", 
        "Categoría", "Salario Base"
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
    FILE *file_trababajadores = fopen("trabajadoresdos.txt", "r");
    if (!file_trababajadores) { // Verificar si se pudo abrir el archivo de empleados
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
    while (fgets(linea, sizeof(linea), file_trababajadores)) { // Leer cada línea del archivo
        trabajador empleado;
        sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f",
            empleado.cedula, empleado.nombre, empleado.segundo_nombre, empleado.apellido,
            empleado.segundo_apellido, empleado.direccion, empleado.fecha_ingreso,
            empleado.codigo); // Parsear los datos del empleado

        // Crear etiquetas para cada campo y agregar al grid
        const char *datos[] = {empleado.cedula, empleado.nombre, empleado.segundo_nombre, empleado.apellido,
                            empleado.segundo_apellido, empleado.direccion, empleado.fecha_ingreso,
                            empleado.codigo};
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
    fclose(file_trababajadores); // Cerrar el archivo de empleados

    // Mostrar la ventana con todos los datos
    gtk_widget_show_all(window);
}
