# SEA - TP1

Repo con los archivos para bootear y cargar el kernel para la raspberry pi 3 b v1.2 2015 y los fuentes de la aplicación solicitada.

## Organización

* **rpi**. Archivos relacionados con el kernel y el booteo de la placa. Se incluye también un comprimido del sistema de archivos.
    * **boot**. Los archivos de esta carpeta tienen que ir en la primer partición de la SD, de tipo fat32.
    * **kernel**. Se incluyen la imagen del kernel, el device tree (source) y el archivo de configuración de make del kernel. El dts va en el directorio `${PROJECT_ROOT}/kernel/linux-stable/arch/arm/boot/dts/broadcom`.
* **src**. Se incluyen los fuentes de la aplicación.
    * **scripts**. Se incluyen los scripts de shell para modificar el archivo html del sevidor http.
        - Es necesario tener el archivo `index.html` (puede ser una copia de `index.html_bak`).
        - Para modificar este index.html hay que modificar el archivo `htmlUpdate` y correr `updateHtml.sh`.
