# SEA - TP1

Repo con los archivos para bootear y cargar el kernel para la raspberry pi 3 b v1.2 2015 y los fuentes de la aplicación solicitada.

## Organización

* rpi. Archivos relacionados con el kernel y el booteo de la placa. Se incluye también un comprimido del sistema de archivos.
    * boot. Los archivos de esta carpeta tienen que ir en la primer partición de la SD, de tipo fat32.
    * kernel. Se incluyen la imagen del kernel, el device tree (source) y el archivo de configuración de make del kernel.
* src. Se incluyen los fuentes de la aplicación.
