
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct node *p_dalsi;
}NODE;

int rataj();
NODE *alokuj();
NODE *nacitaj(NODE *head);
void vypis(NODE *head);
NODE* pridaj(NODE *head);
void hladaj(NODE *head);
void vymaz(NODE *head);
void skonci(NODE* head);

int main() {
	char v;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	while (v!='k') {
		scanf("%c",&v);
		switch (v) {
			case 'n' : head = nacitaj(head); break;
			case 'v' : vypis(head); break;
			case 'p' : pridaj(head); break;
			case 'h' : hladaj(head); break;
			case 'z' : vymaz(head); break;
			case 'k' : skonci(head); return 0;
		}
	}
}

int rataj() { 
	int riadky = 1;
	char ch;
	FILE *fr = fopen("auta.txt","r");
	while (!feof(fr)) {
		ch = fgetc(fr);
		if (ch == '\n') {
			++riadky;
		}
	}
	fclose(fr);
	return riadky/7; 
}

NODE *alokuj() { 
	NODE *pp;
	pp = (NODE*)malloc(sizeof(NODE));
	return pp;
}

NODE *nacitaj(NODE* head) {		//funkcia n
	int i,n,k=rataj();
	char dolar[2],riadok[4];
	NODE *p_prv, *p_akt,*temp;
	FILE *fr = fopen("auta.txt","r");
	rewind(fr);
	p_prv = alokuj();
	head = alokuj();
	
	if (fr == NULL) {
		printf("Subory neboli nacitane\n");
		return NULL;
	}
	
	while (head != NULL) {		
		temp = head;
		head = head->p_dalsi;
		free(temp);
	}
	fscanf(fr,"%[^\n] %[^\n] %[^\n] %[^\n] %d %d %[^\n]",dolar, &p_prv->kategoria, &p_prv->znacka, &p_prv->predajca, &p_prv->cena, &p_prv->rok_vyroby, &p_prv->stav_vozidla);
	p_prv->p_dalsi = NULL;
	p_akt = p_prv;	
	
	for (i=2;i<=k;i++) {
		p_akt->p_dalsi = alokuj();
		p_akt = p_akt->p_dalsi;
		fgets(riadok,50,fr);
		fscanf(fr,"%[^\n] %[^\n] %[^\n] %[^\n] %d %d %[^\n]",dolar, &p_akt->kategoria, &p_akt->znacka, &p_akt->predajca, &p_akt->cena, &p_akt->rok_vyroby, &p_akt->stav_vozidla);
		p_akt->p_dalsi = NULL;
		}
	p_akt->p_dalsi = NULL;
	head = p_prv;
	printf("Nacitalo sa %d zaznamov\n",k);
	
	return head;
}

void vypis(NODE* head) {		//funkcia v
	int i=1;
	NODE  *p_zobr = head;
	
	while(p_zobr!=NULL) {
		printf("%d.\n",i);
		printf("kategoria: %s\n",p_zobr->kategoria);
		printf("znacka: %s\n",p_zobr->znacka);
		printf("predajca: %s\n",p_zobr->predajca);
		printf("cena: %d\n",p_zobr->cena);
		printf("rok_vyroby: %d\n",p_zobr->rok_vyroby);
		printf("stav_vozidla: %s\n",p_zobr->stav_vozidla);
		p_zobr = p_zobr->p_dalsi;
		i++;
	}
	
}

NODE *pridaj(NODE* head) {		//funkcia p
	int k = rataj(),i,n;
	NODE *p_vloz,*temp,*temp1;
	p_vloz = alokuj();
	temp1 = alokuj();
	
	scanf("%d",&n);
	if (n < 0) {
		printf("Zle cislo\n");
		return head;
	}
	
	fscanf(stdin,"%[^\n]",&p_vloz->kategoria);
	fscanf(stdin,"%[^\n]",&p_vloz->znacka);
	fscanf(stdin,"%[^\n]",&p_vloz->predajca);
	scanf("%d",&p_vloz->cena);
	scanf("%d",&p_vloz->rok_vyroby);
	fscanf(stdin,"%[^\n]",&p_vloz->kategoria);
	p_vloz->p_dalsi = NULL;
	
	if (n == 1) {
		temp = head;
		head = p_vloz;
		head->p_dalsi = temp;
		return head;
	}
	else {
		temp = head;
	
	if (n == 2) {
		temp1 = temp->p_dalsi;
		temp->p_dalsi = p_vloz;
		p_vloz->p_dalsi = temp1;
	}
		else {
		for (i=1;i<n-1;i++) {
			temp = temp->p_dalsi;
			if (temp->p_dalsi == NULL) {
				break; 
			}
		} 
		
	temp1 = temp->p_dalsi;
	temp->p_dalsi = p_vloz;
	p_vloz->p_dalsi = temp1;
	}
  }
}

void hladaj(NODE* head) {		//funkcia h
	int podm = 0,c;
	NODE *p_zobr,*temp;
	p_zobr = head;
	scanf("%d",&c);
	while (p_zobr!=NULL) {
		if (p_zobr->cena <= c) {
			podm++;
			printf("%d.\n",podm);
			printf("kategoria: %s\n",p_zobr->kategoria);
			printf("znacka: %s\n",p_zobr->znacka);
			printf("predajca: %s\n",p_zobr->predajca);
			printf("cena: %d\n",p_zobr->cena);
			printf("rok_vyroby: %d\n",p_zobr->rok_vyroby);
			printf("stav_vozidla: %s\n",p_zobr->stav_vozidla);
			}
		p_zobr = p_zobr->p_dalsi;
	}
	if (podm < 1) {
		printf("V ponuke su len auta s vyssou cenou\n");
	}
	
}

void vymaz(NODE* head) {		//funkcia z
	int i=0,k;
	char vymaz[50],pomocna[50];
	char *ret;
	getchar();
	scanf("%s",vymaz);
	vymaz[strcspn(vymaz,"\n")] = 0;
	NODE *p_akt = head;
	//strcpy(p_akt->znacka,pomocna);
	char *podm = strstr(p_akt->znacka,vymaz);
			
}	

void skonci(NODE* head) { //funkcia k
   NODE *temp;

   while (head != NULL)
    {
       temp = head;
       head = head->p_dalsi;
       free(temp);
    }
}
