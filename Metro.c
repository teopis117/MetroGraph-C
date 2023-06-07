void obtener_ruta(Estacion* origen, Estacion* destino) {
    // Verificar si el origen o el destino son nulos
    if (origen == NULL || destino == NULL) {
        printf("El origen o el destino son nulos.\n");
        return;
    }

    // Verificar si el origen y el destino son iguales
    if (origen == destino) {
        printf("El origen y el destino son iguales.\n");
        return;
    }

    // Inicializar el algoritmo Dijkstra
    int num_estaciones = obtener_numero_estaciones();
    Estacion** estaciones = obtener_todas_estaciones();
    inicializar_dijkstra(estaciones, num_estaciones, origen);

    // Ejecutar el algoritmo Dijkstra
    ejecutar_dijkstra(estaciones, num_estaciones);

    // Verificar si se puede llegar al destino
    if (destino->distancia == INT_MAX) {
        printf("No se puede llegar al destino desde el origen.\n");
        return;
    }

    // Construir la ruta desde el destino hasta el origen
    Ruta* ruta = construir_ruta(destino);

    // Imprimir la ruta
    printf("Ruta desde %s hasta %s:\n", origen->nombre, destino->nombre);
    imprimir_ruta(ruta);

    // Liberar la memoria de la ruta
    liberar_ruta(ruta);
}