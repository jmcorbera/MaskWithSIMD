#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//declaracion de variables globales

void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void abrirImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
void guardarImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
/* programa para lectura y escritura de imagenes rgb o ppm en C*/
int largoimg;

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

  return 0;
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
    else {
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

void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto)
{
  clock_t tiempo_inicio, tiempo_final;
  double segundos = 0.0;

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

  tiempo_inicio = clock();

  enmascarar_asm(memoriaParaImg1, memoriaParaImg2, mascara, cant);

  tiempo_final = clock();   
  segundos = ( double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
  segundos = ( double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;

  printf("%.16g milisegundos\n", segundos * 1000.0);

  guardarImagen("salida_c.rgb", cant, memoriaParaImg1);
  guardarImagen("salida_asm.rgb", cant, memoriaParaImg1);

  //Liberar memoria
  free(memoriaParaImg1);
  free(memoriaParaImg2);
  free(mascara);
}