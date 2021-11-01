sudo gcc -m32 ./Enmascarado_C/enmascarar_c.c -o maskC;
sudo nasm -f elf32 ./Enmascarado_ASM/enmascarar_asm.asm -o ./Enmascarado_ASM/enmascarar_asm.o;
sudo gcc -m32 ./Enmascarado_ASM/enmascarar_asm.c ./Enmascarado_ASM/enmascarar_asm.o -o maskASM;
./maskC "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080
./maskC "dragonball300x242.bmp" "codegeass.bmp" "mascara300x242.bmp" 300 242
./maskC "onepiece1024x768.bmp" "gogeta1024x768.bmp" "mascara1024x768.bmp" 1024 768
./maskASM "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080
./maskASM "dragonball300x242.bmp" "codegeass.bmp" "mascara300x242.bmp" 300 242
./maskASM "onepiece1024x768.bmp" "gogeta1024x768.bmp" "mascara1024x768.bmp" 1024 768

