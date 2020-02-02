#include "ima.h"
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define min(a,b) (a <= b?a:b)
#define max(a,b) (a >= b?a:b)
#define carre(a) (a)*(a)


int nb_fenetre(Image *image, int fenetre){
	int cmp = 0;
	int n, k, x, y;
	for(n=0;n<image->sizeY;n+=fenetre){
		for(k=0;k<image->sizeX;k+=fenetre){
			for(y=n;y<n+fenetre;y++){
				for(x=k;x<k+fenetre;x++){
				}
			}
			cmp++;
		}
	}
	return cmp;
}

void triermax(Pixelsom *tab, int taille){
	int i,j;
	Pixelsom tmp;
	for(i=0;i<taille-1;i++){
		for(j=i+1;j<taille;j++){
			if(tab[i].somme < tab[j].somme){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

void distance(Pixelsom *tab, Pixelsom x, int taille){
	int i;
	for(i=0;i<taille;i++){
		tab[i].somme = 	carre(x.r - tab[i].r) + carre(x.g - tab[i].g) + carre(x.b - tab[i].b);	
	}
	triermax(tab, taille);
}

int equal(Pixelsom a,Pixelsom b){
	if((a.r == b.r) && (a.g == b.g) && (a.b == b.b) ){
		return 1;
	}
	return 0;
}

int appatient(Pixelsom a, Pixelsom *tab,int val){
	int i;
	for(i=0;i< val;i++){
		if(equal(tab[i],a) == 1){
			tab[i].somme++;
			return 1;
		}
	}
	return 0;
}

Pixelsom trouverMax(Pixelsom *tab,int n){
	int i;
	Pixelsom max;
	max.r = 0;
	max.g = 0;
	max.b = 0;
	max.somme = 0;
	for(i=0;i<n;i++){
		if(tab[i].somme > max.somme ){
			max = tab[i];
		}
	}
	return max;
}

Pixelsom couleur_moy(Pixelsom *tab,int fenetre){
	Pixelsom moyenne;
	int i;
	int r=0,g=0,b=0;
	for(i=0;i<fenetre;i++){
        r+=tab[i].r;
        g+=tab[i].g;
        b+=tab[i].b;
    }

    r /= fenetre;
	g /= fenetre;
	b /= fenetre;
	moyenne.r = r;
	moyenne.g = g;
	moyenne.b = b;
	moyenne.somme = r+g+b;
	return moyenne;
}

Pixelsom couleur_frequente(Pixelsom *tab, int fenetre){
	Pixelsom *tab2 = (Pixelsom *)malloc(fenetre * sizeof(Pixelsom));

	Pixelsom res;
	int y;
	int val=0;
	for(y=0;y<fenetre;y++){
		if(appatient(tab[y],tab2,val) == 0){
			tab2[val] = tab[y];
        	val++;			
		}
	}
	res = trouverMax(tab2,val);
	return res;
}

Pixelsom couleur_eloignee(Pixelsom *tab, int fenetre){
	Pixelsom moyenne = couleur_moy(tab,fenetre);
	distance(tab,moyenne,fenetre);
	Pixelsom max =  tab[0];
	int i;
	for(i=1;i<fenetre;i++){
		if(tab[i].somme > max.somme){
			max = tab[i];
		}
	}

	return max;
}