#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

	int i, z, g, minlimit, maxlimit;
	char name[20];
	srand(time(NULL));
	minlimit=0; // Minimum number possible for random selection
	maxlimit=100; // Maxiumum number possible for random selection
	
	printf("±êÍÔQ[Å·B\n");
	printf("¨¼OÍ½Å·©HF");
	gets(name);
	printf("±ñÉ¿ÍA");
	for (z=0; z<strlen(name); z++)
	{
		printf("%c",name[z]);
	}
	printf("³ñB");
	printf("\né§ÌÔð¢¢ÄÄÝÄº³¢ ! (%d-%d)\n" , minlimit, minlimit+maxlimit);
	printf("pÓÍ¢¢Å·©H");
    i = rand()*123456789 / (RAND_MAX + 1); // Randomize
	z=0;
	g=0;
    i = (rand() * (maxlimit+1-minlimit) / (RAND_MAX + 1)) + minlimit; // select number
	do {
		printf("\né§ÔÍ½Åµå¤©H");
		scanf("%d",&z);
		if (z>=minlimit && z<=minlimit+maxlimit) {
			g++;
			if (z>i) {
				printf("\n¢ß¬éI");
				}
			if (z<i) {
				printf("\ná¢ß¬éI");
				}
			}
	} while (z!=i);
	printf("¨ßÅÆ¤");
	for (z=0; z<strlen(name); z++)
	{
		printf("%c",name[z]);
	}
	printf("³ñ!!");
	printf("\nâÁ½ËI%dñÚÉÅ«Üµ½I", g);
	printf("\né§ÔÍ%dÅµ½I", i);
	return 0;
}
