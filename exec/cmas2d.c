#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>


#define MAXMAT 1000
#define MAXCND 1000
   
char projname[ 1024];
int i, ielem, inod, icnd;
double *x, *y;
int *N, *imat;
int nodc[ MAXCND];
double rho[ MAXMAT], wval[ MAXCND];
int Nelem, Nnod, Nmat, Ncnd;
double x_CG, y_CG;

void input( void);
void calculate( void);
void output( void);

int main( int argc, char *argv[ ]) {
  if ( argc < 2) {
    printf( "Error: no projectname provided.\n");
    printf( "Usage: Cmas2D full_path_to_project\n");
    // system( "pause");
    return 1;
  }
  strcpy( projname, argv[ 1]);
  input( );
  calculate( );
  output( );
  return 0;
}
  
void jumpline( FILE*); 

void input( ) {
  char filedat[ 1024], fileerr[1024], sau1[ 1024], sau2[ 1024];
  FILE *fp, *ferr;
  int aux,j, error=0;
   
  strcpy( filedat, projname);
  strcat( filedat,".dat");
  fp = fopen( filedat, "r");
   
  for ( i=0; i<6; i++) jumpline( fp);
  fscanf( fp, "%d %d", &Nelem, &Nnod);
    
  x=( double *) malloc(( Nnod+1)*sizeof( double)); if ( x==NULL) {error=1;}
  y=( double *) malloc(( Nnod+1)*sizeof( double)); if ( y==NULL) {error=1;}

  N=  ( int *) malloc(( Nelem+1)*3*sizeof( int)); if ( N==NULL) {error=1;}
  imat=( int *) malloc(( Nelem+1)*sizeof( int));  if ( N==NULL) {error=1;}
   
  if ( error) {
    strcpy( fileerr, projname);
    strcat( fileerr,".err");
    ferr = fopen( fileerr, "w");
    fprintf( ferr, "\n \n \n *****  ERROR: Not enough memory. ***** \n");              
    fprintf( ferr, "( Try to calculate with less elements)\n");              
    exit( 1); 
  }

  for ( i=0; i<6; i++) jumpline( fp);

  /* reading the coordinates */
  for ( inod=1; inod<=Nnod; inod++)       
    fscanf( fp, "%d %lf %lf", &aux, &x[ inod], &y[ inod]); 

  for ( i=0; i<6; i++) jumpline( fp);
  
  /* reading connectivities  */
  for ( ielem=1; ielem<=Nelem; ielem++) {
    fscanf( fp, "%d", &aux);
    for ( j=0;j<3;j++) fscanf( fp, "%d", &N[ ( ielem-1)*3+j]);
    fscanf( fp, "%d", &imat[ ielem]);
    if ( imat[ ielem]==0) {
      strcpy( fileerr, projname);
      strcat( fileerr,".err");
      ferr = fopen( fileerr, "w");
      fprintf( ferr, "\n \n \n **ERROR: Elements with no material!!** \n"); 
      exit( 1); 
    }
  }
  
  for ( i=0; i<5; i++) jumpline( fp);
  fscanf( fp, "%s %s  %d",sau1, sau2, &Nmat );
  
  for ( i=0; i<3; i++)
    jumpline( fp);

  /* reading density of each material  */
  for ( i=1; i<=Nmat; i++)
    fscanf( fp, "%d %lf", &aux, &rho[ i]);      
    
  for ( i=0; i<4; i++) jumpline( fp);

  /* reading conditions */
  fscanf( fp, "%d", &Ncnd); 

  for ( i=0; i<6; i++) jumpline( fp);

  for ( icnd=1; icnd<=Ncnd; icnd++) { 
    fscanf( fp, "%d %lf", &nodc[ icnd], &wval[ icnd]);
    jumpline( fp);             
  }
  
  fclose( fp);
}

void calculate () {
   double v;
   int n1, n2, n3;
   int mat;
   double x_CGi, y_CGi;
   double x_num=0, y_num=0,  den=0;

   for (ielem=1; ielem<=Nelem; ielem++) {
     n1= N[0+(ielem-1)*3];
     n2= N[1+(ielem-1)*3];
     n3= N[2+(ielem-1)*3];

     /* Calculating the volume (volume is the area, 
        provided we are dealing with 3D surfaces) */
     
    v=fabs(x[n1]*y[n2]+x[n2]*y[n3]+x[n3]*y[n1]-x[n1]*y[n3]-x[n2]*y[n1]-x[n3]*y[n2])/2;

     /* The geometric center of the element is calculated */
     x_CGi= (x[n1]+x[n2]+x[n3])/3;
     y_CGi= (y[n1]+y[n2]+y[n3])/3;

     /* sums are calculated */
     mat= imat[ielem];
     x_num+= rho[mat]*v*x_CGi;
     y_num+= rho[mat]*v*y_CGi;

     den+= rho[mat]*v;
   }

   /* point weights */
   for (icnd=1; icnd<=Ncnd; icnd++) {
     inod= nodc[icnd];
     x_num+= wval[icnd]*x[inod];
     y_num+= wval[icnd]*y[inod];       
     den+= wval[icnd]; 
   }

   x_CG= (x_num/den);
   y_CG= (y_num/den);  
 }


void output( ) {
  char filedat[ 1024];
  FILE *fp, *fptest;
   double raiz;
   double pot;

   strcpy(filedat, projname);
   strcat(filedat,".boh");
   fptest = fopen(filedat, "w");
   fprintf (fptest, "FILE: %s\n", projname);
   fprintf (fptest, "CMAS2D\n2D routine to calculate the mass center of an object.\n");
   fprintf (fptest, "\n\n\t====> mass center: %lf %lf \n", x_CG, y_CG);
  
   /* writing .post.res */
   strcpy(filedat, projname);
   strcat(filedat,".post.res");
   fp = fopen(filedat, "w");
   fprintf (fp, "MC-DISTANCE    2    1    1    1    0\n");
   for (inod=1; inod<=Nnod; inod++){
     /* distance from the center of masses */
     raiz= (x_CG-x[inod])*(x_CG-x[inod]) + (y_CG-y[inod])*(y_CG-y[inod]);
     pot = sqrt (raiz);
     fprintf (fp, " %6d %14.6lf\n", inod, pot);
   }
   fclose (fp);   
   fclose (fptest);
   free(x);
   free(y);
   free(N);
   free(imat);
}

/* funcion de salto de linea */
void jumpline( FILE* filep) {
  char buffer[ 81];
  
  fgets( buffer, 80, filep);
}
