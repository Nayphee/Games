#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int rndnum(int a , int b);

int main (void)
{
	//init
	int r[6];
	int p[6];
	int i,xx,g,right,close;
	char z[6];
	char handle[1];
	srand(time(NULL));
	//title
	printf("BAGELS Q[Öæ¤±»II\n");
	printf("Ìé§R[hÌ·³ÍTÅ·B\n");
	printf("»ÌTÍ1©ç5ÜÅÅ·B\n");
	printf("R[hð¢¢ ÄÄÝÄ­¾³¢I\n\n");
	printf("ñA È½ÌÄÄÝ½R[hÍé§ÌR[hÆä×Ü·B\n");
	printf("êÂ¸ÂÌªÄéÆA'-' ð\µÜ·B\n");
	printf("àµ»ÌÍ½¾µ¢êÉ êÎA'+' ð\µÜ·B\n");
	printf("ÄÄÝ½R[gÍ³ð¾ÆA+++++ Í»êÜ·B\n");
	printf("æ£ÁÄËI!\n\n");
	// select number
	for (i=0;i<5;i++){
		r[i]=rndnum(5,1);
		g=0;
	}
	// game main loop
	do {
		//player input
		do {
			printf("OK!R[hÍ½Åµå¤HF");
			gets(z);
		} while (strlen(z)!=5);
		for (i=0;i<5;i++) {
			handle[0]=z[i];
			p[i]=atoi(handle);
		}
		g++;
		right=0;
		close=0;
		//scan for score
		for (i=0;i<5;i++) {
			if (p[i]==r[i]) {
				right++;
				continue;
			}
			else {			
				for (xx=0;xx<5;xx++)
				if (p[i]==r[xx]) {
					close++;
					break;
				}
			}
		}
		//display score
		printf(" È½ÌXRAÍ : ");
		for (i=0;i<right;i++) {
			printf("+");
		}
		for (i=0;i<close;i++) {
			printf("-");
		}
		printf("\n");
	} while (right !=5);
	//player win
	printf("âÁ½ËI");
	printf("%dñÚÉÅ«½I" , g);
	return 0;
}

int rndnum(int a , int b)
{
	int i;
	
	i = rand()*123456789 / (RAND_MAX + 1); // Randomize
	return (rand() * (a+1-b) / (RAND_MAX + 1)) + b; // select number
}
