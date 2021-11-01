# TP 2 - Organización del Computador II
Proyecto de Enmascarado de Imágenes con SIMD

## Objetivo

Se debe implementan 2 funciones de Enmascaramiento de imágenes, una función llamada **enmascarar_c**, integramente en el lenguaje C y otra función llamada **enmascarar_asm** en lenguaje ensamblador de 32 bits usando instrucciones SIMD, la cual recibe de una aplicación en C los parámetros.  
El funcionamiento de las lógicas en los diferentes lenguajes es el mismo, se carga la imagen principal en un buffer, luego la segunda imagen y la mascara en otros 2 buffers distintos y se debe combinar las imágenes 1 y 2 aplicandole un enmascarado. El resultado de esta combinación se guarda en el primer buffer. 
Además se implementa un programa en C que recibe los parámetros a utilizar por línea de comandos y llama a las dos funciones para generar dos archivos (salida_c.rgb y salida_asm.rgb) que corresponden a las imágenes producidas por las dos llamadas.


### Ejecución del programa:
El programa ejecuta ambas funciones devolviendo las imagenes nuevas generadas. Las imágenes son obtenidas de la carpeta **"/Images"** y el resultado de los enmascarados son guardados en **"/Output"**

**Pasos preeliminares** Descargue el archivo y descomprima, **ubiquese** dentro de la carpeta /MaskWithSIMD


**Para ejecutar las pruebas**, primero que nada asegurese de ser el superusuario y de darle permisos de ejecucion al archivo "compile.sh" (le podemos asegurar que no es un virus)


![dar permisos](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251777435_10217838325744013_8475622212545039199_n.jpg?_nc_cat=104&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=0I9dwCwBOIEAX8HhBzF&_nc_ht=scontent.faep8-2.fna&oh=fd71b2b7a4f9e95656096f749ec22d62&oe=61A42D65)

luego puede ejecutar las pruebas con el siguiente comando:

abra la terminal `ctrl+alt+t`
ingrese el siguiente comando:
sudo ./complie.sh
le deberia mostrarle algo asi:

![ejecutar_prueba](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/252088367_10217838325984019_8172154905620179787_n.jpg?_nc_cat=106&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=uC4bpNbhobwAX-SfJpS&_nc_ht=scontent.faep8-1.fna&oh=7a06e438b39b7e892677e1d0fc33ac46&oe=61A6A0C8)

dependiendo de la velocidad de su computador puede tardar mas o menos, y mostrar mas o menos tiempo.

Para ver la salida dirigase a la carpeta output, y abra alguno de los dos archivos, deberia quedar asi:

![imagen resultado](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/247078269_10217838348424580_2651080192619419760_n.jpg?_nc_cat=111&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=S_utowiqlx0AX_RltPG&_nc_ht=scontent.faep8-1.fna&oh=39119f4a895f72bf052da71e72236aae&oe=61A72261)

si **quiere ejecutar el programa** con alguna otra imagen de su galeria, debe asegurarse de que las imagenes y mascara tengan el mismo tamaño, ponga las imagenes en la carpeta image/

**Importante**: si no realizo las pruebas, debe primero compilar el programa, puede hacerlo al ejecutar las  pruebas, o de la siguiente manera:
abra la terminal `ctrl +alt+ t`
ingrese los siguientes comandos:

sudo nasm -f elf32 enmascarar_asm.asm -o enmascarar_asm.o;

sudo gcc -m32 enmascarar_c.c enmascarar_asm.o -o maskSIMD;

_ahora el programa ha compilado, ya esta listo para usar!_

para usar ejecute el siguiente comando:

`./maskSIMD "suprimerimagen.bmp" "susegundaimagen.bmp" "sumascara.bmp" alto ancho`
**!ATENCION:** EN  LUGAR DE "suprimerimagen" debe reemplazar por el verdadero nombre del archivo/imagen en formato bmp, que usted esta intentando enmascarar, lo mismo para "usegundaimagen" y "sumascara" , en alto y ancho reemplace por el alto y ancho.

por ejemplo:

`./maskSIMD "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080`

observe los resultados en la carpeta output

### Informe
Se comenzo por hacer el lado de C, lo primero que llevamos a cabo fue la implementacion de un codigo para abrir una imagen, y otro para cerrar y guardar.

![abrir imagen](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251482470_10217838023016445_1032772892767641671_n.jpg?_nc_cat=102&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=22D1ZSXBUiYAX8vLBPB&_nc_ht=scontent.faep8-2.fna&oh=5ad428089217c07c13195a8577e7403c&oe=61A6AAC9)

Comenzamos buscando el archivo en la carpeta image.luego lo abrimos, y condicionamos su existencia.
Como se puede ver en esta funcion nos apoyamos de una variable `largoimg` para comparar el tamaño de imagenes y lanzar un error cuando no se pasan imagenes del mismo tamaño.

![guardar imagen](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/251047134_10217838047257051_3998477145262876613_n.jpg?_nc_cat=107&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=ZjbQ0nH1EmsAX-o_c_-&_nc_ht=scontent.faep8-2.fna&oh=7efddaf438a7339b5a06c5b49dc5674e&oe=61A4DE9D)


Con guardar imagen nos encargamos de guardar el nuevo archivo en una carpeta llamada output.

Mas tarde se prosiguio con la funcion de enmascarado en c
![enmascarar_c](https://scontent.faep8-2.fna.fbcdn.net/v/t1.6435-9/247155695_10217838058897342_902104059066661664_n.jpg?_nc_cat=107&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=Iz4pWcySgEUAX-0x6Nn&_nc_ht=scontent.faep8-2.fna&oh=3af29eed86b5534f027961faf418630f&oe=61A69E5F)
esta funcion hace un for que recorre la mascara desde el primer al ultimo byte, y si se cruza con un cero no hace nada porque 0 corresponde a negro, si se encuentra un byte distinto de cero pasa el contenido del buffer b al a en la misma posicion. <asumimos que la mascara solo contiene colores blancos y negros> 

Mas adelante se implemento el codigo para `enmascarar_asm` desde el lado de asm
  
  ![enmascarar_asm](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/251604756_10217838105578509_2386260856377204698_n.jpg?_nc_cat=110&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=ZsHyy9A07CgAX8qVBSg&_nc_ht=scontent.faep8-1.fna&oh=44a70b05c97487334c40f5f69a2fb474&oe=61A4D7B2 
  )
 Desde el codigo asm,se implemento esta funcion que hace un loop teniendo en cuenta la cantidad de bytes de la variable local, va ejecutando el ciclo y comparando su contador con la cantidad para poder `salir` . este ciclo guarda los paquetes de a b y mascara en mm0,mm1 y mm2 y luego hace un AND logico entre la mascara y b (donde haya negro ,ceros, va quedar ceros, y el resto se respeta la imagen) y un AND NOT entre la mascara y a para finalmente poder hacer on OR logico en entre lo que por un lado tendra la imagen1 y pixeles negros y por el otro pixeles negros y la imagen2, y finalmente cuando se termine el ciclo quedara enmascarado.
 
Finalmente continuamos con la funcion `procesarArchivos` que se encarga de conectar las funciones, el buffer (usando malloc), variables, etc. Para que todo corra, en ella se hace uso del clock para calcular cuanto tiempo le lleva a cada funcion de enmascarado llevarse a cabo.


### Conclusiones
hicimos 3 pruebas cada prueba con un tamaño distinto de imagen y mascara y los resultados fueron los siguientes
  
 ![graficos](https://scontent.faep8-1.fna.fbcdn.net/v/t1.6435-9/251873397_10217838780315377_4266679851793519300_n.jpg?_nc_cat=105&_nc_rgb565=1&ccb=1-5&_nc_sid=730e14&_nc_ohc=naF06mLAOxYAX8MybQ6&tn=HE71w9qu0gGBze0U&_nc_ht=scontent.faep8-1.fna&oh=17eb5c5fe9cc0953b027ad13b7d79014&oe=61A41432)
 
  link al [grafico](https://docs.google.com/spreadsheets/d/e/2PACX-1vSaXXvnTpx8s7szfz8n3vajmtvT0GrOuswb9Y2VAvWH2cvRYvbclIyvVLLaB8zYjrkwZpgrWsa3VGZt/pubchart?oid=1087145314&format=interactive) interactivo.
 Como se puede observar, la funcion en asm,usando mmx ( la extension SIMD de ia32) es mas veloz y eficiente que la programada en c que tarda mas,  con una diferencia de hasta 5 veces mayor. De esta manera podemos concluir que al usar paralelismo de datos podemos hacer un programa ligero.
 
  
  -Eso es todo, que tenga buen dia!
