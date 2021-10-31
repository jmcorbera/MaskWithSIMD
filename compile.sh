sudo nasm -f elf32 enmascarar_asm.asm -o enmascarar_asm.o;
sudo gcc -m32 enmascarar_c.c enmascarar_asm.o -o maskSIMD;
./maskSIMD "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080
