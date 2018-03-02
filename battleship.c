#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

///program v1.0

//global variables
signed int rndnum(int a , int b); // random number function
int map(int a); // draw map routine
int pinput(void); // get coordinates for player input
int nogo(int x, int y, int p); // check place on map for object. Returns error=1 if space is "no-go"
char ply[11][11]; // player map
char cpu[11][11]; // cpu placement map
char gam[11][11]; // player guessing at cpu map
int shotx, shoty, error; // variables for game play and shot making
char ship[][10] = {
	"","","ìÍ","öÍ","mÍ","qóêÍ","" //names of ships
};

int main (void)
{
	//initialise
	int i,ii,turn,x1,y1,x2,y2;// i,ii (counters), turn (player or computer), x1/2,y1/2 (assist placing/cpu a.i)
	int plcx,plcy; //placement registers
	char input;
	int pscore, cscore; //player/computer score
	int cpuai, firstx, firsty; //cpu artificial intelligence registers
	signed int cpux, cpuy;
	srand(time(NULL));//randomize from clock
	//title
	printf("BATTLESHIPS! íDQ[I by ub`[B\n");
	printf("±ÌQ[ÌÚIÍ·×ÄÌCPUÌíDð¾ßéI\n");
	printf("»Ì½ßACPUÌíDÌÊuð¢¢ÄÄÝÄµÜµå¤I\n");
	printf("CðÂ¯ÄBBBCPUÍ È½ÌíDð_¢Ü·BBBB\n\n");
	printf("ÅÉA©ªÌDðu«Üµå¤B\n");
	//place ships
	for(i=5;i>1;i--) {
		do {
			map(0);
			for(ii=0; ship[i][ii];ii++) {
				printf("%c", ship[i][ii]);
			}
			printf("ðÇ±Éu«½¢Å·©H");
			printf("%dubNðgpµÜ·B", i);
			pinput();
			x1=shotx;
			y1=shoty;
			do {
				printf("\nã©çºÜÅAciv)A¡ih)AEÎßir)A¶Îßil)H :");
				rewind(stdin);
				scanf("%c", &input);
				plcx=0, plcy=0;
				if(input=='v') plcx=0, plcy=1;
				else if(input=='h') plcx=1, plcy=0;
				else if(input=='r') plcx=1, plcy=1;
				else if(input=='l') plcx=-1, plcy=1;
			} while((plcx==0)&&(plcy==0));
			shotx=x1, shoty=y1, error=0;
			for (ii=0;ii<i;ii++){	
				nogo(shoty,shotx,0);
				shotx=shotx+plcx;
				shoty=shoty+plcy;
			}
			if(error==0) {
				shotx=x1, shoty=y1;
				for (ii=0;ii<i;ii++) {
					ply[shoty][shotx]='#';
					shotx=shotx+plcx;
					shoty=shoty+plcy;
				}
			}
			if(error==1) {
				printf("\n***»±Í¾ß¾æI***\n");
			}
		} while(error==1);				
	}	
	map(0);
	// cpu places ships
	printf("\n­XÜ¿­¾³¢BBBÍ©ªÌDðu«Ü·B\n");
	for(i=5;i>1;i--) {
		do {
			x1=rndnum(9,0);
			y1=rndnum(9,0);
			input=rndnum(4,1);
			plcx=0, plcy=0;
			if(input==1) plcx=0, plcy=1;
			else if(input==2) plcx=1, plcy=0;
			else if(input==3) plcx=1, plcy=1;
			else if(input==4) plcx=-1, plcy=1;
			shotx=x1, shoty=y1, error=0;
			for (ii=0;ii<i;ii++){	
				nogo(shoty,shotx,2);
				shotx=shotx+plcx;
				shoty=shoty+plcy;
			}
			if(error==0) {
				shotx=x1, shoty=y1;
				for (ii=0;ii<i;ii++) {
					cpu[shoty][shotx]='#';
					shotx=shotx+plcx;
					shoty=shoty+plcy;
				}
			}
		} while(error==1);	
	}	
	// who starts?
	printf("ÅÍNÅ·©HvC[(p)©Rs[^(c)? :");
	rewind(stdin);
	scanf("%c", &input);
	if(input=='c') turn=1;
	else turn=0;
	// start game
	pscore=0, cscore=0, cpuai=0, firsty=0, firstx=0;
	do {
		//player plays
		if(turn==0) {
			printf(" È½ÌÔÅ·B\n");
			do {
				map(1);
				pinput();
				error=0;
				nogo(shoty,shotx,1);
				if(error==1) printf("***»±Í¾ßÅ·I***\n");
			} while(error==1);
			if(cpu[shoty][shotx]=='#') {
				gam[shoty][shotx]='*';
				printf("Ä½I*****oK°!*****\n");
				pscore++;
			}
			else {
				gam[shoty][shotx]='.';
				printf("~XII\n");
			}
			map(1);
		}
		//cpu plays
		else if(turn==1) {
			printf("CPUÌÔÅ·B\n");
			do {
				if(cpuai<=0) {
					shotx=rndnum(9,0); // CPUAI = 0; Computer has no idea, so makes a random guess
					shoty=rndnum(9,0);					
				}
				if((cpuai>0)&&(cpuai<=90)) {
					cpuai--; // CPUAI >0 &< 90. 8 direction search around hit for more boat 
					input=rndnum(1,-1); // (90 chances to find free 8 direction spot before giving up)
					shotx=(x1+input);
					input=rndnum(1,-1);
					shoty=(y1+input);
				}
				if(cpuai>=100) {
					shotx=(x1+cpux); // CPUAI=100 sets about destoying line
					shoty=(y1+cpuy); // CPUAI=200 destroys other side of boat
				}
				error=0;
				nogo(shoty,shotx,3);
				if((error==1)&&(cpuai==200)) cpuai=0;
				if((error==1)&&(cpuai==100)) cpuai=200, x1=(firstx), y1=(firsty), cpux=-cpux, cpuy=-cpuy;
			} while(error==1);
			printf("Íi%c , %c)ÉUµÜ·B\n",(shoty+97),(shotx+97));
			if(ply[shoty][shotx]=='#') {
				ply[shoty][shotx]='*';
				printf("Ä½I*****oK°!*****\n"); // a hit!
				cscore++;		
				if((cpuai>0)&&(cpuai<100)) {  
					x2=shotx, y2=shoty; // set up computer a.i. to destroy boat line
					cpux=(x2-x1), cpuy=(y2-y1);
					if((cpux>=-1)&&(cpux<=1)&&(cpuy>=-1)&&(cpuy<=1)) {
						cpuai=100;
					}
				}
				if(cpuai==0) {
					firstx=(shotx), firsty=(shoty); //first hit on boat. Taking note for a.i.
					cpuai=90; 
				}
				x1=shotx, y1=shoty;
			}
			else {
				ply[shoty][shotx]='.';
				printf("Í~XI\n"); // computer miss
				if(cpuai==200) cpuai=0;
				if(cpuai==100) { 
					cpuai=200; // set cpu a.i. to hunt down other side of boat cpuai=200
					x1=(firstx), y1=(firsty), cpux=-cpux, cpuy=-cpuy;
				}
			}
			map(0);
		}
		if(turn==0) turn=1;
		else turn=0;
	}while((pscore<14)&&(cscore<14));
	printf("\nQ[ÍIíèÜµ½B\n");
	if(pscore==14) map(1), printf(" È½ÍÁ½II\n");
	if(cscore==14) map(1), map(2), printf("CPUÍÁ½BBB\n");
	return 0;
} 

signed int rndnum(int a , int b)
{
	int i;
	
	i = rand()*123456789 / (RAND_MAX + 1); // Randomize further
	return (rand() * (a+1-b) / (RAND_MAX + 1)) + b; // select number
}

int map(a)
{
	int i, ii;
	printf("\n*|a|b|c|d|e|f|g|h|i|j\n");
	printf("-+-------------------\n");
	for(i=0;i<10;i++){
		printf("%C|", (97+i));
		for(ii=0;ii<10;ii++){
			if (a==0) printf("%C ",ply[i][ii]);
			else if (a==2) printf("%C ",cpu[i][ii]);
			else if (a==1) printf("%C ",gam[i][ii]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int pinput(void)
{	
	char z[2];	
	do {
		rewind(stdin);
		printf("\nA-J (s-ñ) R[fBl[gðüÍµÄº³¢:");
		gets(z);
		shoty=("%d", z[0])-97;
		shotx=("%d", z[1])-97;
	} while((shotx<0)||(shotx>9)||(shoty<0)||(shoty>9));
	return 0;
}

int nogo(int y, int x, int p)
{
		if((x<0)||(x>9)||(y<0)||(y>9)) {
			error=1;
		}
		if(p==0) {
			if(("%d",ply[y][x])!=0) error=1;
		}
		if(p==1) {
			if(("%d",gam[y][x])!=0) error=1;
		}
		if(p==2) {
			if(("%d",cpu[y][x])!=0) error=1;
		}
		if(p==3) {
			if((ply[y][x]=='.')||(ply[y][x]=='*')) error=1;
		}
	return 0;
}

