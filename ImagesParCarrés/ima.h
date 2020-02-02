#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <GL/gl.h>	

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;

typedef unsigned short utab [3][3][3];

struct PixelHSV {
    double h;
    double s;
    double v;
} __attribute__((packed));
typedef struct PixelHSV PixelHSV;

struct Pixel {
    GLubyte r;
    GLubyte g;
    GLubyte b;
} __attribute__((packed));
typedef struct Pixel Pixel;

struct Pixelsom {
    int r;
    int g;
    int b;
    int somme;
} __attribute__((packed));
typedef struct Pixelsom Pixelsom;


int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);

// fonctions_references.c
int nb_fenetre(Image *image, int fenetre);
void triermax(Pixelsom *tab, int taille);
void distance(Pixelsom *tab, Pixelsom x, int taille);
int equal(Pixelsom a,Pixelsom b);
int appatient(Pixelsom a, Pixelsom *tab,int val);

Pixelsom trouverMax(Pixelsom *tab,int n);
Pixelsom couleur_moy(Pixelsom *tab,int fenetre);
Pixelsom couleur_frequente(Pixelsom *tab, int fenetre);
Pixelsom couleur_eloignee(Pixelsom *tab, int fenetre);

// modif.c
double max3 (double r,double g,double b);
double min3 (double r,double g,double b);
double codeH(PixelHSV a);
PixelHSV codeHSV (PixelHSV a);
void max_fenetrehsv(Image *image, int fenetre);

void max_fenetre(Image * i,int fenetre);
void trimax(Image *image, int fenetre);
void contraste(Image *image, int fenetre);
void redef_pixel(Image *image, int fenetre);