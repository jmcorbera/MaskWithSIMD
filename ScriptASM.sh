sudo nasm -f elf32 ./Enmascarado_ASM/enmascarar_asm.asm -o ./Enmascarado_ASM/enmascarar_asm.o;
sudo gcc -m32 ./Enmascarado_ASM/enmascarar_asm.c ./Enmascarado_ASM/enmascarar_asm.o -o maskASM;
#./maskASM "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080