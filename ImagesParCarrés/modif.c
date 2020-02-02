#include "ima.h"

#define min(a,b) (a <= b?a:b)
#define max(a,b) (a >= b?a:b)


double max3 (double r,double g,double b){
	if(max(r,g) > b){
		return max(r,g);
	}
	return b;
} 

double min3 (double r,double g,double b){
	if(min(r,g) > b){
		return b;
	}
	return min(r,g);
}

double codeH(PixelHSV a){
	double r1,g1,b1,Cmax,Cmin,Delta;
	double h;
	r1 = a.h/255.0;
	g1 = a.s/255.0;
	b1 = a.v/255.0;

	Cmax = max3(r1,g1,b1);
	Cmin = min3(r1,g1,b1);
	Delta = Cmax - Cmin;

	if(Delta == 0.0){
		return h = 0.0;
	}
	if(Cmax == r1){
		return h = 60.0 * (fmod(((g1-b1)/Delta),6));
	}
	if(Cmax == g1){
		return h = 60.0*(((b1-r1)/Delta)+2.0);
	}
	return h = 60.0*(((r1-g1)/Delta)+4.0);
}



PixelHSV codeHSV (PixelHSV a){
	double r1,g1,b1,Cmax,Cmin,Delta;
	PixelHSV res;
	r1 = a.h/255.0;
	g1 = a.s/255.0;
	b1 = a.v/255.0;

	Cmax = max3(r1,g1,b1);
	Cmin = min3(r1,g1,b1);
	Delta = Cmax - Cmin;

	res.h = codeH(a);
	res.v  = Cmax*100;

	if(Cmax == 0){
		res.s = 0;
	}
	res.s = (Delta/Cmax)*100;

	return res;
}

void max_fenetrehsv(Image *image, int fenetre){
	GLubyte * pixel;
	pixel = image->data;
	int n, k, x, y;
	double e,d,f, max=0;
	int coreMaxX, coreMaxY;
	for(n=0;n<image->sizeY;n+=fenetre){
		for(k=0;k<image->sizeX;k+=fenetre){
			max = 0;
			for(y=n;y<n+fenetre;y++){
				for(x=k;x<k+fenetre;x++){
					PixelHSV a;
					a.h= *(pixel + (image->sizeX*3*y)+x*3);
					a.s= *(pixel + (image->sizeX*3*y)+x*3+1);
            	    a.v= *(pixel + (image->sizeX*3*y)+x*3+2);

            		if(max< codeHSV(a).v){
            			max=codeHSV(a).v;
						coreMaxX = x;
						coreMaxY = y;
					}
				}
			}

       		d = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3);
			e = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+1);
			f = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+2);

			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3) = *(pixel + (image->sizeX *3*n)+k*3);
			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+1) = *(pixel + (image->sizeX *3*n)+k*3+1);
			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+2) = *(pixel + (image->sizeX *3*n)+k*3+2);

			*(pixel + (image->sizeX *3*n)+k*3) = d;
			*(pixel + (image->sizeX *3*n)+k*3+1) = e;
			*(pixel + (image->sizeX *3*n)+k*3+2)= f;
		}
	}
}

void max_fenetre(Image *image, int fenetre){
	GLubyte * pixel;
	pixel = image->data;
	int fx, fy, x, y;
	int r_tmp, g_tmp, b_tmp, somme_rgb=0, max_fenetre=0;
	int coreMaxX, coreMaxY;
	for(fy=0;fy<image->sizeY;fy+=fenetre){
		for(fx=0;fx<image->sizeX;fx+=fenetre){
			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					somme_rgb = *(pixel + (image->sizeX*3*y)+x*3)+*(pixel + (image->sizeX*3*y)+x*3+1)+*(pixel + (image->sizeX*3*y)+x*3+2);
            		
            		if(max_fenetre<somme_rgb){
            		max_fenetre=somme_rgb;
					coreMaxX = x;
					coreMaxY = y;
					}
				}
			}

       		r_tmp = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3);
			g_tmp = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+1);
			b_tmp = *(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+2);

			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3) = *(pixel + (image->sizeX *3*fy)+fx*3);
			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+1) = *(pixel + (image->sizeX *3*fy)+fx*3+1);
			*(pixel + (image->sizeX *3*coreMaxY)+coreMaxX*3+2) = *(pixel + (image->sizeX *3*fy)+fx*3+2);

			*(pixel + (image->sizeX *3*fy)+fx*3) = r_tmp;
			*(pixel + (image->sizeX *3*fy)+fx*3+1) = g_tmp;
			*(pixel + (image->sizeX *3*fy)+fx*3+2)= b_tmp;
		}
	}
}

void trimax(Image *image, int fenetre){
	GLubyte * pixel;
	pixel = image->data;
	int fx, fy, x, y;
	int f=fenetre*fenetre;		
	int val=0;
	int z=0;
	Pixelsom restab;
	Pixelsom *tab = (Pixelsom *)malloc(f*sizeof(Pixelsom));

	for(fy=0;fy<image->sizeY;fy+=fenetre){
		for(fx=0;fx<image->sizeX;fx+=fenetre){
			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					restab.r = *(pixel + (image->sizeX*3*y)+x*3);
					restab.g = *(pixel + (image->sizeX*3*y)+x*3+1);
            	    restab.b = *(pixel + (image->sizeX*3*y)+x*3+2);

            		restab.somme = restab.r + restab.g + restab.b;
            		tab[val] = restab;
            		val++;
				}
			}

			triermax(tab,f);
			val=0;
			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					
					*(pixel + (image->sizeX*3*y)+x*3) = tab[z].r;
					*(pixel + (image->sizeX*3*y)+x*3+1)= tab[z].g;
            	    *(pixel + (image->sizeX*3*y)+x*3+2)= tab[z].b;
            		z++;
				}
			}
			z=0;
		}
	}		
}

void contraste(Image *image, int fenetre){
	GLubyte * pixel;
	pixel = image->data;
	int fx, fy, x, y;
	int f=fenetre*fenetre;
	int val=0;
	int z=0;
	Pixelsom moyenne;
	Pixelsom *tab = (Pixelsom *)malloc(f*sizeof(Pixelsom));
	
	for(fy=0;fy<image->sizeY;fy+=fenetre){
		for(fx=0;fx<image->sizeX;fx+=fenetre){
			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					tab[val].r = *(pixel + (image->sizeX*3*y)+x*3);
					tab[val].g = *(pixel + (image->sizeX*3*y)+x*3+1);
            	    tab[val].b = *(pixel + (image->sizeX*3*y)+x*3+2);
            	   
            		val++;

				}
			}
			moyenne = couleur_moy(tab,f);
			distance(tab,moyenne,f);
			val = 0;

			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					
					*(pixel + (image->sizeX*3*y)+x*3) = tab[z].r;
					*(pixel + (image->sizeX*3*y)+x*3+1)= tab[z].g;
            	    *(pixel + (image->sizeX*3*y)+x*3+2)= tab[z].b;
            		z++;
				}
			}
			z = 0;
		}
	}
}

void redef_pixel(Image *image, int fenetre){
	GLubyte * pixel;
	pixel = image->data;
	int fx, fy, x, y;
	int f=fenetre*fenetre;
	int val=0;
	Pixelsom c_moy;
	Pixelsom c_freq;
	Pixelsom c_eloigne;
	int somme_pixel;
	Pixelsom *tab1 = (Pixelsom *)malloc(f*sizeof(Pixelsom));
	
	for(fy=0;fy<image->sizeY;fy+=fenetre){
		for(fx=0;fx<image->sizeX;fx+=fenetre){
			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					
					tab1[val].r = *(pixel + (image->sizeX*3*y)+x*3);
					tab1[val].g = *(pixel + (image->sizeX*3*y)+x*3+1);
            	    tab1[val].b = *(pixel + (image->sizeX*3*y)+x*3+2);
            		tab1[val].somme = 0;
            		val++;
				}
			}
			c_moy = couleur_moy(tab1,f);
			c_freq = couleur_frequente(tab1,f);
			c_eloigne = couleur_eloignee(tab1,f);
			val = 0;

			for(y=fy;y<fy+fenetre;y++){
				for(x=fx;x<fx+fenetre;x++){
					somme_pixel = *(pixel + (image->sizeX*3*y)+x*3)
								+ *(pixel + (image->sizeX*3*y)+x*3+1)
								+ *(pixel + (image->sizeX*3*y)+x*3+2);
					if(somme_pixel < 382){
						*(pixel + (image->sizeX*3*y)+x*3) = c_moy.r;
						*(pixel + (image->sizeX*3*y)+x*3+1) = c_moy.g;
						*(pixel + (image->sizeX*3*y)+x*3+2) = c_moy.b;
					}
					else if((*(pixel + (image->sizeX*3*y)+x*3)= c_eloigne.r) && (*(pixel + (image->sizeX*3*y)+x*3+1) = c_eloigne.g) && (*(pixel + (image->sizeX*3*y)+x*3+2) = c_eloigne.b)){
						*(pixel + (image->sizeX*3*y)+x*3) = c_eloigne.r;
						*(pixel + (image->sizeX*3*y)+x*3+1) = c_eloigne.g;
						*(pixel + (image->sizeX*3*y)+x*3+2) = c_eloigne.b;
					}
					else{
						*(pixel + (image->sizeX*3*y)+x*3) = c_freq.r;
						*(pixel + (image->sizeX*3*y)+x*3+1) = c_freq.g;
						*(pixel + (image->sizeX*3*y)+x*3+2) = c_freq.b;
					}
				}
			}
		}
	}
}