sudo nasm -f elf32 enmascarar_asm.asm -o enmascarar_asm.o;
sudo gcc -m32 enmascarar_c.c enmascarar_asm.o -o maskSIMD;
./maskSIMD "avengers.bmp" "ligaj.bmp" "mascara.bmp" 1920 1080
./maskSIMD "dragonball300x242.bmp" "codegeass.bmp" "mascara300x242.bmp" 300 242
./maskSIMD "onepiece1024x768.bmp" "gogeta1024x768.bmp" "mascara1024x768.bmp" 1024 768

