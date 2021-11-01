#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//declaracion de variables globales

void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto);
void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void abrirImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
void guardarImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
/* programa para lectura y escritura de imagenes rgb o ppm en C*/
int largoimg;
double clocKs_seg = CLOCKS_PER_SEC;

int main(int argc, char *argv[])
{
  

  if (argc != 6)
  {
    printf("Error al ingresar los parametros\n");
    return 0;
  }

  //Parametros
  char *imagen1 = argv[1];      //imagene1
  char *imagen2 = argv[2];   //imagen2
  char *mask = argv[3];      //mascara
  int ancho = atoi(argv[4]); //para pasar el argumento a int
  int alto = atoi(argv[5]);  //para pasar el argumento a int
 
  procesarArchivos(imagen1,imagen2,mask,ancho,alto);

  
  

  return 1;
}

void abrirImagen(char *nombreArchivo, int tamano, unsigned char *buffer)
{
  char path[100];
  strcpy(path, "images/"); 
  strcat(path, nombreArchivo);
  printf("abriendo el archivo %s\n", path);

  FILE *fp;
  fp = fopen(path, "rb");//indicamos lectura
  fseek(fp,0L,SEEK_END);//voy al inicio del archivo
  if (largoimg==0){
    largoimg=ftell(fp);//aviso el largo
    fseek(fp, 0L, SEEK_SET);//vuelvo al principio
    
  }
  else if (largoimg!=0){
    if(largoimg!=ftell(fp)){
      printf("ERROR:los archivos no tienen el mismo tamaño\n");
      printf("PROGRAMA FINALIZADO\n");
      exit(-1);
      }
    else {//
      largoimg=ftell(fp);//aviso el largo
      fseek(fp, 0L, SEEK_SET);//vuelvo al principio
   }
  }
  

  if (fp == NULL)//si no existe..
  {
    printf("Error al abrir el archivo\n");
  }
  else
  {
    fread(buffer, tamano, 1, fp);
  }
  
  fclose(fp);
}


void guardarImagen(char *nombreArchivo, int tamano, unsigned char *buffer)
{
  char path[100];
  strcpy(path, "output/"); 
  strcat(path, nombreArchivo);

  FILE *fp;
  fp = fopen(path, "wb");//indicamos escritura
  fwrite(buffer, 1, tamano, fp);
  fclose(fp);
}

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{
  for (int i = 0; i < cant; i++)
  {
    if (mask[i] != 0)
    { //0 si es negro - 255 si es blanco
      a[i] = b[i];
    }
  }
}

void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto)
{

  int cantidadxPixel = 3; //RGB 3 bytes por pixel, un byte hasta 255 por cada color R,G O B
  int cant = ancho * alto * cantidadxPixel;

  //Reservar memoria dinámica
  unsigned char *memoriaParaImg1 = malloc(cant);
  unsigned char *memoriaParaImg2 = malloc(cant);
  unsigned char *mascara = malloc(cant);

  //Abrimos las imagenes
  abrirImagen(imagen1, cant, memoriaParaImg1);
  abrirImagen(imagen2, cant, memoriaParaImg2);
  abrirImagen(mask, cant, mascara);

clock_t tiempo_inicio, tiempo_final, tmasmf , tmasm;
  double segundos = 0.0;

  tiempo_inicio = clock();

  enmascarar_c(memoriaParaImg1, memoriaParaImg2, mascara, cant);
 tiempo_final = clock();
  segundos = ( double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
  
  printf("el tiempo de enmascarado en c es de ");
  printf("%.16g milisegundos\n", segundos * 1000.0);


  tiempo_inicio = clock();
  enmascarar_asm(memoriaParaImg1, memoriaParaImg2, mascara, cant);
  tiempo_final = clock();
  
    
 segundos = ( double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
 segundos = ( double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
 printf("tiempo de enmascarado en asm %.16g milisegundos\n", segundos *1000.0);
  guardarImagen("salida_c.rgb", cant, memoriaParaImg1);
  guardarImagen("salida_asm.rgb", cant, memoriaParaImg1);

  //Liberar memoria
  free(memoriaParaImg1);
  free(memoriaParaImg2);
  free(mascara);
}

//para probar.
//gcc imagen.c -o a.out
//./a.out avengers.bmp ligaj.bmp mascara.bmp 1920 1080
//va producir un archivo llamado "imagen_c.rgb"
//abrir y ver resultados.