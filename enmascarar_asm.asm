;%include "io.inc"

section .data
    cant dd 0
    
section .text
    global enmascarar_asm
   
enmascarar_asm:
    push ebp 
    mov ebp, esp 
    
    mov ecx, 0          ;inicio el contador
  
    mov edx,[ebp+20]    ;apunta a la cantidad (pixeles de la imagen)
    mov [cant],edx      ;guardo la cantidad en la variable local
    
  cloop:
    cmp ecx, [cant]   
    JE salir
    
                        ;parametros
    mov eax,[ebp+8]     ;parametros de la imagen a
    MOVQ mm0,[eax+ecx] 
   
    mov eax,[ebp+12]    ;parametros de la imagen b
    MOVQ mm1,[eax+ecx]
    
    mov eax,[ebp+16]    ;parametros de la mascara
    MOVQ mm2,[eax+ecx]

   
    PAND mm1, mm2       ;mantiene la imagen b cuando el pixel es negro 
    PANDN mm2, mm0      ;mantiene la imagen a cuando el pixel es distinto de FFFFFF
    POR mm1, mm2
       
    mov eax,[ebp+8]     ;debe devolver la imagen a - combinada con a y b 
    MOVQ [eax+ecx], mm1
 
    add ecx, 8          ;nos desplazamos de a 64 bits (regs mmx)
    JMP cloop
    
   salir:
    mov esp, ebp 
    pop ebp 
    
    ret
