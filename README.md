# TP 2 - Organización del Computador II
Proyecto de Enmascadaro de Imagenes con SIMD

## Primera Parte

Se debe implementan 2 funciones de Enmascaramiento de imagenes, una función llamada **enmascarar_c**, integramente en el lenguaje C y otra función llamada **enmascarar_asm** en lenguaje ensamblador de 32 bits usando instrucciones SIMD, la cual recive de una aplicación en C los parámetros. 
El funcionamiento de las lógicas en los difernetes lenguajes es el mismo, se carga la imagen principal en un buffer, luego la segunda imagen y la mascara en otros 2 buffers distintos y se debe combinar las imagenes 1 y 2 aplicandole un enmascarado. El resultado de esta combinación se guarda en el primer buffer. 
Además se implementa un programa en C que recibe los parámetros a utilizar por línea de comandos y llama a las dos funciones para generar dos archivos (salida_c.rgb y salida_asm.rgb) que corresponden a las imágenes producidas por las dos llamadas.

### Funciones desarrolladas:

*Función* enmascarar_c (unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
*Función* enmascarar_asm (unsigned char *a, unsigned char *b, unsigned char *mask, int cant)

### Ejecucion del programa:
En esta primera parte, la versión del programa ejecuta ambas funciones devolviendo las imagenes nuevas generadas. Las imagenes son obtenidas de la carpeta **"/Images"** y el resultado de los enmascarados son guardados en **"/Output"**

./maskSIMD "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080

### Informe

### Conclusiones


