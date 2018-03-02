#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rndnum(int a , int b);
int hiscore(void);
long int scr[4];
int main(void)
{
	// init
	int mines, people, money, mprice, oprice, prod, store, year, playyear, input, i;
	double satis;
	FILE *hiscr;
	if((hiscr = fopen("hi-kouzan","rb"))!=NULL) {
		for(i=0;i<4;i++) {
			if(fread(&scr[i],sizeof(long int),1,hiscr)!=1) {
				printf("SCOREÇÝæèG[\n");
				exit(1);
			}
		}
		fclose(hiscr);
	}
	else {
		for(i=0;i<4;i++) {
			scr[i]=0;
		}
	}
	srand(time(NULL));
	mines=rndnum(3,1)+5;
	people=rndnum(60,1)+40;
	money=(rndnum(50,1)+10)*people;
	prod=(rndnum(40,1)+80);
	store=0;
	satis=1;
	year=1;
	printf("ub`[ÌzRQ[Öæ¤±»III\n\n");
	hiscore();
	do {
		printf("¢­ÂÌQ[NÔðvCµÜ·©H(10/30/50/100?) :@");
		scanf("%d",&input);
	} while((input!=10)&&(input!=30)&&(input!=50)&&(input!=100));
	playyear=input;
	// main loop
	do {
		mprice=rndnum(2000,1)+2000;
		oprice=rndnum(12,1)+7;
		printf("\n¡NÍ%dNB\n", year);
		printf("\n È½Í %d zRðLµÜ·B\n",mines);
		printf("%d lÍzRÌA¯nÉZñÅ¢Ü·B\n",people);
		printf("lû«vfÍ %1.1f Å·B\n",satis);
		printf("\n È½Í%d ðÁÄ¢Ü·B\n", money);
		printf("\nêÂ¸ÂÌzRÍ %d zÎð@èoµÜµ½B\n",prod);
		printf("ðN©çA È½ÌqÉÉ %d zÎðÛµÄ¢Ü·B\n",store);
		printf("¡NÌzÎliÍ%d Å·B\n",oprice);
		printf("¡NÌzRliÍ%d Å·B\n\n",mprice);
		store=store+(prod*mines);
		if(mines==0) {
			prod=0;
		}
		do {
			printf("¡AqÉÍ%d zÎðÛµÄ¢Ü·B\n",store);
			printf("zÎÌ½Âðè½¢Å·©H :");
			scanf("%d",&input);
		} while((input>store)||(input<0));
		money=money+(input*oprice);
		store=store-input;
		do {
			printf("¢­ÂÌzRðè½¢Å·©H :");
			scanf("%d",&input);
		} while((input>mines)||(input<0));
		money=money+(input*mprice);
		mines=mines-input;
		printf("\n¡A È½Í%d ðÁÄ¢Ü·B\n",money);
		do {
			printf("H×¨Ì½ßÉ¢­çð¥¢Ü·©H:");
			scanf("%d",&input);
		} while((input>money)||(input<0));
		money=money-input;
		if((input/people>120)) {
			satis=satis+0.1;
		}
		if((input/people<80)) {
			satis=satis-0.2;
		}
		do {
			printf("¢­ÂÌzRð¢Ü·©H :");
			scanf("%d",&input);
		} while((input<0)||((mprice*input)>money));
		money=money-(input*mprice);
		mines=mines+input;
		if(satis<0.6) {
			printf("***SõÍ È½Éw«Üµ½BIíèB\n\n");
			return 0;
		}
		if(satis>1.1) {
			prod=prod+(rndnum(20,1)+1);
			people=people+(rndnum(10,1)+1);
		}
		if(satis<0.9) {
			prod=prod-(rndnum(20,1)+1);
			people=people-(rndnum(10,1)+1);
		}
		if(mines>0) {
			if(people/mines<10){
				printf("***SõÍKAROSHI!BIíèB\n\n");
				return 0;
			}
		}
		if(people<30) {
			printf("***lûÍ­È¢ß¬Ü·BIíèB\n\n");
			return 0;
		}
		input=rndnum(100,1);
		if(input<=5) {
			printf("\n***lûÍs¡ÌaCð´õµÜ¢Üµ½B\n");
			printf("***å¨ªÉÜµ½B\n");
			people=(int)people/2;
		}
		if(prod>150) {
			printf("\n***zÎÌ}[PbgÍNbVµÜ¢Üµ½B\n");
			printf("***zRÌ@èoµ¦ª¿éBBB\n");
			prod=prod/2;
		}
		printf("\n%dNIíèÜµ½B\n",year);
		year++;
	} while(year<(playyear+1));
	input=(money+(mines*mprice)+(store*oprice));
	printf("*** %d NÔðß²µÜµ½B È½ÌdÍIíèÜµ½B\n", playyear);
	printf("***¨ßÅÆ¤!!!\n");
	printf("***cÁ½¨àÍ%d Åµ½B\n",money);
	printf("*** È½ÌzRÌliÍ%d Å·B\n\n", input);
	if(playyear==10) i=0;
	else if(playyear==30) i=1;
	else if(playyear==50) i=2;
	else if(playyear==100) i=3;
	if(input>scr[i]){
		scr[i]=input;
		printf("·²¢IVµ¢HIGH SCOREðÅ«½II¨ßÅÆ¤I\n");
	}
	if((hiscr = fopen("hi-kouzan","wb"))!=NULL) {
		for(i=0;i<4;i++) {
			if(fwrite(&scr[i],sizeof(long int),1,hiscr)!=1) {
				printf("SCORE«ÝG[\n");
				exit(1);
			}
		}
		fclose(hiscr);
	}
	hiscore();
	return 0;
}

int rndnum(int a , int b)
{
	int i;
	
	i = rand()*123456789 / (RAND_MAX + 1); // Randomize
	return (rand() * (a+1-b) / (RAND_MAX + 1)) + b; // select number
}

int hiscore(void)
{
	printf("HIGH SCORES !\n-------------\n");
	printf("10NÔ  : $%d\n",scr[0]);
	printf("30NÔ  : $%d\n",scr[1]);
	printf("50NÔ  : $%d\n",scr[2]);
	printf("100NÔ : $%d\n\n",scr[3]);
	return 0;
}
