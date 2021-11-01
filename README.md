# TP 2 - Organización del Computador II
Proyecto de Enmascarado de Imágenes con SIMD

## Objetivo

Se debe implementan 2 funciones de Enmascaramiento de imágenes, una función llamada **enmascarar_c**, integramente en el lenguaje C y otra función llamada **enmascarar_asm** en lenguaje ensamblador de 32 bits usando instrucciones SIMD, la cual recibe de una aplicación en C los parámetros.  
El funcionamiento de las lógicas en los diferentes lenguajes es el mismo, se carga la imagen principal en un buffer, luego la segunda imagen y la mascara en otros 2 buffers distintos y se debe combinar las imágenes 1 y 2 aplicandole un enmascarado. El resultado de esta combinación se guarda en el primer buffer. 
Además se implementa los programas en C (para ejecutar las funciones en C y en ASM) que reciben los parámetros a utilizar por línea de comandos y llama a las funciones para generar los archivos, salida_c.rgb (ejecución en C) y salida_asm.rgb (Ejecución de ASM) que corresponden a las imágenes producidas por las diferentes funciones.


## Ejecución del programa:
El programa compile.sh ejecuta ambas funciones devolviendo las imagenes nuevas generadas. Las imágenes son obtenidas de la carpeta **"/Images"** y el resultado de los enmascarados son guardados en **"/Output"**

### Pasos de Ejecución Automática
**Pasos preeliminares** Descargue el archivo y descomprima, **ubiquese** dentro de la carpeta /MaskWithSIMD

**Para ejecutar las pruebas**, primero que nada asegurese de ser el superusuario y de darle permisos de ejecucion al archivo "compile.sh"

![dar permisos](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251777435_10217838325744013_8475622212545039199_n.jpg?_nc_cat=104&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=0I9dwCwBOIEAX8HhBzF&_nc_ht=scontent.faep8-2.fna&oh=fd71b2b7a4f9e95656096f749ec22d62&oe=61A42D65)

#### Abrir carpeta del programa
```
abra la terminal `ctrl+alt+t`
ingrese el siguiente comando:
sudo ./complie.sh
```

O ejecute los programas por separados

```
sudo ./ScriptC.sh
sudo ./ScriptASM.sh
```

le deberia mostrarle algo asi:

![captura1](https://user-images.githubusercontent.com/9463666/139738998-722b277c-e505-4a44-9e50-52cec8e5bfca.png)
![captura2](https://user-images.githubusercontent.com/9463666/139739096-d1c13a9c-d4e9-420c-bd92-7f27546a708e.png)

* *Los tiempos de ejecución pueden variar de acuerdo al procesador que se esté utilizando*.

Para ver el resultado del enmascaramiento dirijase a la carpeta output, y abra alguno de los dos archivos, deberia quedar asi:

![imagen resultado](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/247078269_10217838348424580_2651080192619419760_n.jpg?_nc_cat=111&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=S_utowiqlx0AX_RltPG&_nc_ht=scontent.faep8-1.fna&oh=39119f4a895f72bf052da71e72236aae&oe=61A72261)

### Pasos de Ejecución Manual

#### Ejecucion Programa enmascarado en C

Para compilar el codigo y generar un nuevo ejecutable se pueden ejecutar los siguientes comandos:

```
abra la terminal `ctrl +alt+ t`  
sudo gcc -m32 ./Enmascarado_C/enmascarar_c.c -o maskC;
```

para usar el programa ejecute el siguiente comando:
```
`./maskC "imagen1.bmp" "imagen2.bmp" "mascara.bmp" alto ancho`
```
Ejemplo:

*  ./maskC "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080

#### Ejecucion Programa enmascarado en ASM

Para compilar el codigo y generar un nuevo ejecutable se pueden ejecutar los siguientes comandos:

```
abra la terminal `ctrl +alt+ t`  
sudo nasm -f elf32 ./Enmascarado_ASM/enmascarar_asm.asm -o ./Enmascarado_ASM/enmascarar_asm.o;
sudo gcc -m32 ./Enmascarado_ASM/enmascarar_asm.c ./Enmascarado_ASM/enmascarar_asm.o -o maskASM;
```

para usar el programa ejecute el siguiente comando:
```
`./maskASM "imagen1.bmp" "imagen2.bmp" "mascara.bmp" alto ancho`
```
Ejemplo:

*  ./maskASM "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080

**!ATENCION:** El alto y el ancho tienen que coincidir con el de las imagenes, de lo contrario la ejecución arrojara un error.
observe los resultados en la carpeta output

### Ejecución de otras fuentes

si **quiere ejecutar el programa** con alguna otra imagen de su galeria personal, debe asegurarse de que las imagenes y mascara tengan el mismo tamaño. Coloque las imagenes deseadas en la carpeta **image/**

## Informe
En primera instancia se comenzó por el desarrollo de la aplicación en C, las primeras funcionalidades que se desarrollaron fueran las que se utilizan para abrir las imagenes, para cerrarlas y guardarlas.

![abrir imagen](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251482470_10217838023016445_1032772892767641671_n.jpg?_nc_cat=102&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=22D1ZSXBUiYAX8vLBPB&_nc_ht=scontent.faep8-2.fna&oh=5ad428089217c07c13195a8577e7403c&oe=61A6AAC9)

Comenzamos buscando el archivo en la carpeta **images**, luego lo abrimos, y condicionamos su existencia.
Como se puede ver en esta funcion nos apoyamos de una variable *`largoimg`* para comparar el tamaño de imagenes y lanzar un error cuando no se pasan imagenes del mismo tamaño.

![guardar imagen](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251047134_10217838047257051_3998477145262876613_n.jpg?_nc_cat=107&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=ZjbQ0nH1EmsAX-o_c_-&_nc_ht=scontent.faep8-2.fna&oh=7efddaf438a7339b5a06c5b49dc5674e&oe=61A4DE9D)

Con guardar imagen nos encargamos de guardar el nuevo archivo en una carpeta llamada output.

Luego se continuó con la función de enmascarado en c  

![enmascarar_c](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/247155695_10217838058897342_902104059066661664_n.jpg?_nc_cat=107&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=Iz4pWcySgEUAX-0x6Nn&_nc_ht=scontent.faep8-2.fna&oh=3af29eed86b5534f027961faf418630f&oe=61A69E5F)  

La lógica de esta funcion es hacer un **FOR** que recorre la mascara desde el primer al ultimo byte, y si se cruza con un cero no hace nada porque 0 corresponde a negro, si se encuentra un byte distinto de cero pasa el contenido del buffer **b** al **a** en la misma posición. <asumimos que la mascara solo contiene colores blancos y negros> 

Por último se implemento el código para `enmascarar_asm` desde el lado de asm
  
  ![enmascarar_asm](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/251604756_10217838105578509_2386260856377204698_n.jpg?_nc_cat=110&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=ZsHyy9A07CgAX8qVBSg&_nc_ht=scontent.faep8-1.fna&oh=44a70b05c97487334c40f5f69a2fb474&oe=61A4D7B2 
  )  
  
Desde el codigo asm, se implemento una función que hace un loop teniendo en cuenta la cantidad de bytes de la variable local **cant** (cantidad de pixeles de la imagen), se ejecuta el ciclo y compara un contador con la cantidad para poder `salir` . En la ejecución de este ciclo guarda los paquetes de **a** en **mm0**, **b** en **mm1** y **mascara** en **mm2** y luego hace un AND logico entre la **mascara** y **b** (mantiene la imagen b cuando el pixel de la mascara es distinto de negro) y un AND NOT lógico entre la **mascara** y a (mantiene la imagen a cuando el pixel es distinto de FFFFFF) para finalmente poder hacer on OR lógico en entre las imagenes generadas en mm1 y mm2 (mantiene los valores altos de las 2 imagenes (pisa los blancos y negros), y finalmente cuando se termina el ciclo quedara el enmascarado en mm1.
 
Por último continuamos con la funcion `procesarArchivos` que se encarga de llamar a las funciones, asignar buffers a las imagenes (usando malloc), inicializar variables, etc. Para la medición de los tiempos de ejecución la función hace uso de la función clock, <time.h>, que calcula cuanto tiempo le lleva a cada funcion llevar a caboel enmascarado de las imagenes.
  
Finalizando se separan las aplicaciones para que funcionen independientemente.
  
PD. el siguiente lin fue de mucha ayuda para el enmascarado en assembler
  
* https://www.intel.com/content/dam/develop/external/us/en/documents/mmx-app-filter-median-140701.pdf

## Conclusiones
hicimos 3 pruebas, cada prueba con un tamaño distinto de imagen y mascara y los resultados fueron los siguientes
  
 ![graficos](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/251873397_10217838780315377_4266679851793519300_n.jpg?_nc_cat=105&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=naF06mLAOxYAX8MybQ6&tn=HE71w9qu0gGBze0U&_nc_ht=scontent.faep8-1.fna&oh=17eb5c5fe9cc0953b027ad13b7d79014&oe=61A41432)
 
  link al [grafico](https://docs.google.com/spreadsheets/d/e/2PACX-1vSaXXvnTpx8s7szfz8n3vajmtvT0GrOuswb9Y2VAvWH2cvRYvbclIyvVLLaB8zYjrkwZpgrWsa3VGZt/pubchart?oid=1087145314&format=interactive) interactivo.
 Como se puede observar, la funcion en **asm**, usando **mmx** (la extension SIMD de ia32) es mas veloz y eficiente que la programada en **C** que tarda más, con una diferencia de hasta 5 veces mayor. De esta manera podemos concluir que al usar paralelismo de datos podemos aumentar la velocidad de los procesos.
