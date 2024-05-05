# SEA - TP1

Repo con los archivos para bootear y cargar el kernel para la raspberry pi 3 b v1.2 2015 y los fuentes de la aplicación solicitada.

## Organización del proyecto

* **bin**. Acá se guarda el compilado del fuente de la aplicación. Se guarda la carpeta vacía para mantener la estructura de archivos.
* **rpi**. Archivos relacionados con el kernel y el booteo de la placa. Se incluye también un comprimido del sistema de archivos.
    * **boot**. Los archivos de esta carpeta tienen que ir en la primer partición de la SD, de tipo fat32.
    * **kernel**. Se incluyen la imagen del kernel, el device tree (source) y el archivo de configuración de make del kernel. El dts va en el directorio `${PROJECT_ROOT}/kernel/linux-stable/arch/arm/boot/dts/broadcom`.
* **src**. Se incluyen los fuentes de la aplicación.
    * **scripts**. Se incluyen los scripts de shell para modificar el archivo html del sevidor http.
        - Es necesario tener el archivo `index.html` (puede ser una copia de `index.html_bak`).
        - Para modificar este index.html hay que modificar el archivo `htmlUpdate` y correr `updateHtml.sh`.

## Instrucciones de compilación para aplicación

Se asume en los pasos que siguen que se tiene instalado el juego de herramientas de compilación cruzada para arm y que se inicializó la variable de entorno *CROSS_COMPILE* (según archivo `dev_rpi_glibc`).

Se compila el fuente de manera estática.

1. Entrar al directorio `src/`.
2. Correr script `buildMain.sh` para compilar el fuente de la aplicación. Se puede correr de dos maneras:

    2.a. Pasando una ruta como parámetro. En este caso copia el archivo compilado `tp1main.o` a la ruta especificada.
    Ejemplo de uso:
    ```
    ./buildMain.sh <ruta/absoluta/destino>
    ```
    
    2.b. No pasarle ningún argumento. En este caso el archivo compilado queda en el directorio `bin/`.

**Nota**. Si no se encuentra definida la variable *CROSS_COMPILE*, se va a compilar el fuente de la aplicación para la arquitectura nativa de la computadora que lo esté corriendo. Esto puede ser útil para testear el código. En caso de que se quiera testearlo, tener en cuenta modificar las rutas definidas en el archivo `src/main.c`.
