#include <stdio.h>

 main() {
 int c;
 FILE *f;
 printf("Real UID=%u\n",getuid());
 printf("Effective UID=%u\n\n",geteuid());
 f=fopen("/tmp/sborodziuk/plik.txt","r");
 while ((c=fgetc(f))!=EOF) putchar(c); // w przypadku pomyślnym wyświetla zawartość pliku o podanej nazwie					
 fclose(f);
 return;
 }