/*
 *  Final Project (Project Review): Hyrule Castle
 *
 *  Demonstrates the class material as of now.
 *	
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=0;      //  Lighting ****CHANGE BACK TO 1 TO TOGGLE LIGHTING!***
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=26.3;   //  Size of world 
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   12;  // Elevation of light
unsigned int texture[9]; // Texture names

//tornado vars
float counter = 0.0;


static void SpawnFloor(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //Platform For Tornado
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 5);
   glTexCoord2f(1,0); glVertex3d(7 , 5, 5);
   glTexCoord2f(1,1); glVertex3d( 7, 4.5, 5);
   glTexCoord2f(0,1); glVertex3d( -7, 4.5, 5 ); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 3);
   glTexCoord2f(1,0); glVertex3d(7 , 5, 3);
   glTexCoord2f(1,1); glVertex3d( 7, 4.5, 3);
   glTexCoord2f(0,1); glVertex3d( -7, 4.5, 3 ); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 5);
   glTexCoord2f(3,0); glVertex3d(-7, 5, 3);
   glTexCoord2f(3,3); glVertex3d(7, 5, 3);
   glTexCoord2f(0,3); glVertex3d(7, 5, 5); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , 5);
   glTexCoord2f(1,0); glVertex3d(-7, 4.5, 3);
   glTexCoord2f(1,1); glVertex3d(7, 4.5, 3);
   glTexCoord2f(0,1); glVertex3d(7, 4.5, 5); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 5);
   glTexCoord2f(1,1); glVertex3d( -7, 4.5, 5);
   glTexCoord2f(1,0); glVertex3d(-7 , 4.5, 3);
   glTexCoord2f(0,1); glVertex3d( -7, 5, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(7, 5 , 5);
   glTexCoord2f(1,1); glVertex3d(7, 4.5, 5);
   glTexCoord2f(1,0); glVertex3d(7 , 4.5, 3);
   glTexCoord2f(0,1); glVertex3d( 7, 5, 3); 
   glEnd();

   //Rest of Floor (the back of the platform)
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 3);
   glTexCoord2f(2,0); glVertex3d(-7, 5, -4);
   glTexCoord2f(2,2); glVertex3d(7, 5, -4);
   glTexCoord2f(0,2); glVertex3d(7, 5, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , 3);
   glTexCoord2f(1,0); glVertex3d(-7, 4.5, -4);
   glTexCoord2f(1,1); glVertex3d(7, 4.5, -4);
   glTexCoord2f(0,1); glVertex3d(7, 4.5, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , 3);
   glTexCoord2f(1,0); glVertex3d(-7, 4.5, 3);
   glTexCoord2f(1,1); glVertex3d(-7, 4.5, -4);
   glTexCoord2f(0,1); glVertex3d(-7, 5, -4); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(7, 5 , 3);
   glTexCoord2f(1,0); glVertex3d(7, 4.5, 3);
   glTexCoord2f(1,1); glVertex3d(7, 4.5, -4);
   glTexCoord2f(0,1); glVertex3d(7, 5, -4); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-7, 5 , -4);
   glTexCoord2f(1,0); glVertex3d(7 , 5, -4);
   glTexCoord2f(1,1); glVertex3d(7, 4.5, -4);
   glTexCoord2f(0,1); glVertex3d(-7, 4.5, -4 ); 
   glEnd();
   
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerMain(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   //Base Sqaure for tower
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(5.2, 5 , 3);
   glTexCoord2f(3,0); glVertex3d(2 , 5, 3);
   glTexCoord2f(3,3); glVertex3d( 2, 8, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 8, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(5.2, 5 , -1);
   glTexCoord2f(3,0); glVertex3d(2 , 5, -1);
   glTexCoord2f(3,3); glVertex3d( 2, 8, -1);
   glTexCoord2f(0,3); glVertex3d( 5.2, 8, -1); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(5.2, 5 , -1);
   glTexCoord2f(3,0); glVertex3d(5.2, 5, 3);
   glTexCoord2f(3,3); glVertex3d( 5.2, 8, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 8, -1); 
   glEnd();


   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 5 , -1);
   glTexCoord2f(3,0); glVertex3d(2, 5, 3);
   glTexCoord2f(3,3); glVertex3d(2, 8, 3);
   glTexCoord2f(0,3); glVertex3d(2, 8, -1); 
   glEnd();

   //thin square between blocks
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(1.8, 8, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 8.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 8.2, 3.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 8, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 8, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 8, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 8, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 8, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 8.2, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 8.2, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 8.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 8.2, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(1.8, 8, -1.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 8.2, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 8.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 8, -1.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 8, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 8.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(1.8, 8.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(1.8, 8, -1.2); 
   glEnd();


   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(5.4, 8, 3.2);
   glTexCoord2f(1,0); glVertex3d(5.4 , 8.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 8.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 8, -1.2); 
   glEnd();
  
   //Second block of tower
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(5.2, 8.2 , 3);
   glTexCoord2f(3,0); glVertex3d(2 , 8.2, 3);
   glTexCoord2f(3,3); glVertex3d( 2, 10, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 10, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(5.2, 8.2 , -1);
   glTexCoord2f(3,0); glVertex3d(2 , 8.2, -1);
   glTexCoord2f(3,3); glVertex3d( 2, 10, -1);
   glTexCoord2f(0,3); glVertex3d( 5.2, 10, -1); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(5.2, 8.2 , -1);
   glTexCoord2f(3,0); glVertex3d(5.2, 8.2, 3);
   glTexCoord2f(3,3); glVertex3d( 5.2, 10, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 10, -1); 
   glEnd();


   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 8.2 , -1);
   glTexCoord2f(3,0); glVertex3d(2, 8.2, 3);
   glTexCoord2f(3,3); glVertex3d(2, 10, 3);
   glTexCoord2f(0,3); glVertex3d(2, 10, -1); 
   glEnd();

   //second thin square between blocks
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(1.8, 10, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 10.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 10.2, 3.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 10, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 10, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 10, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 10, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 10, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 10.2, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 10.2, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 10.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 10.2, 3.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(1.8, 10, -1.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 10.2, -1.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 10.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 10, -1.2); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.8, 10, 3.2);
   glTexCoord2f(1,0); glVertex3d(1.8 , 10.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(1.8, 10.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(1.8, 10, -1.2); 
   glEnd();


   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(5.4, 10, 3.2);
   glTexCoord2f(1,0); glVertex3d(5.4 , 10.2, 3.2);
   glTexCoord2f(1,1); glVertex3d(5.4, 10.2, -1.2);
   glTexCoord2f(0,1); glVertex3d(5.4, 10, -1.2); 
   glEnd();

   //third block for tower and top of tower
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(5.2, 10.2 , 3);
   glTexCoord2f(3,0); glVertex3d(2 , 10.2, 3);
   glTexCoord2f(3,3); glVertex3d( 2, 13.2, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 13.2, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(5.2, 10.2 , -1);
   glTexCoord2f(3,0); glVertex3d(2 , 10.2, -1);
   glTexCoord2f(3,3); glVertex3d( 2, 13.2, -1);
   glTexCoord2f(0,3); glVertex3d( 5.2, 13.2, -1); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(5.2, 10.2 , -1);
   glTexCoord2f(3,0); glVertex3d(5.2, 10.2, 3);
   glTexCoord2f(3,3); glVertex3d( 5.2, 13.2, 3);
   glTexCoord2f(0,3); glVertex3d( 5.2, 13.2, -1); 
   glEnd();


   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 10.2 , -1);
   glTexCoord2f(3,0); glVertex3d(2, 10.2, 3);
   glTexCoord2f(3,3); glVertex3d(2, 13.2, 3);
   glTexCoord2f(0,3); glVertex3d(2, 13.2, -1); 
   glEnd();
   
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(5.2, 13.2 , 3);
   glTexCoord2f(3,0); glVertex3d(2 , 13.2, 3);
   glTexCoord2f(3,3); glVertex3d( 2, 13.2, -1);
   glTexCoord2f(0,3); glVertex3d( 5.2, 13.2, -1); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerDecoration1(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //left smallest pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 3, 13.6, 3);
   glTexCoord2f(0,1); glVertex3d( 3.2,13.6, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(3, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3, 13.6, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3,13.6, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3, 13.6, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3.2,13.6, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.6 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3, 13.6, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3, 13.6, 3);
   glTexCoord2f(0,1); glVertex3d( 3.2,13.6, 3); 
   glEnd();

   //left medium pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.4, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 3.4, 13.8, 3);
   glTexCoord2f(0,1); glVertex3d( 3.2,13.8, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.2, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.2, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.2,13.8, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.4, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.4, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3.2,13.8, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.8 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.2, 13.8, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.2, 13.8, 3);
   glTexCoord2f(0,1); glVertex3d( 3.4,13.8, 3); 
   glEnd();

   //middle tallest pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 3.6, 14, 3);
   glTexCoord2f(0,1); glVertex3d( 3.4,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.4, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.4, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.4,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.6, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3.4, 14, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(3.6, 14 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.4, 14, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.4, 14, 3);
   glTexCoord2f(0,1); glVertex3d( 3.6,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.6, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.6, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.6,14, 3); 
   glEnd();

   
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerDecoration2(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //right medium pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.8, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 3.6, 13.8, 3);
   glTexCoord2f(0,1); glVertex3d( 3.8,13.8, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.6, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.8, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.6, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3.8, 13.8, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(3.8, 13.8 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.8, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.6, 13.8, 3);
   glTexCoord2f(0,1); glVertex3d( 3.8,13.8, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.8, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.8, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.8, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.8,13.8, 3); 
   glEnd();

   //right smallest pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.8, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(4, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 4, 13.6, 3);
   glTexCoord2f(0,1); glVertex3d( 3.8,13.6, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.8, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(4, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.8, 13.6, 2.9);
   glTexCoord2f(0,1); glVertex3d( 4, 13.6, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(4, 13.6 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.8, 13.6, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.8, 13.6, 3);
   glTexCoord2f(0,1); glVertex3d( 4,13.6, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(4, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(4, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(4, 13.6, 2.9);
   glTexCoord2f(0,1); glVertex3d(4,13.6, 3); 
   glEnd();

   //middle tallest pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 3);
   glTexCoord2f(1,1); glVertex3d( 3.6, 14, 3);
   glTexCoord2f(0,1); glVertex3d( 3.4,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.4, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.4, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.4,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(3.4, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.6, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d( 3.4, 14, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(3.6, 14 , 2.9);
   glTexCoord2f(1,0); glVertex3d(3.4, 14, 2.9);
   glTexCoord2f(1,1); glVertex3d( 3.4, 14, 3);
   glTexCoord2f(0,1); glVertex3d( 3.6,14, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.6, 13.2 , 3);
   glTexCoord2f(1,0); glVertex3d(3.6, 13.2, 2.9);
   glTexCoord2f(1,1); glVertex3d(3.6, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d(3.6,14, 3); 
   glEnd();

   
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerDecoration3(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

    //left medium pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.9, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.2, 2.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.8, 2.7);
   glTexCoord2f(0,1); glVertex3d(1.9,13.8, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.2, 2.7);
   glTexCoord2f(1,1); glVertex3d(2, 13.8, 2.7);
   glTexCoord2f(0,1); glVertex3d(2,13.8, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.8 , 2.7);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.8, 2.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d(2, 13.8, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.7);
   glTexCoord2f(1,0); glVertex3d(2, 13.8, 2.7);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.8, 2.7);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.7); 
   glEnd();

   //left small pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.9, 13.2 , 2.7);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.2, 2.5);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.6, 2.5);
   glTexCoord2f(0,1); glVertex3d(1.9,13.6, 2.7); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.7);
   glTexCoord2f(1,0); glVertex3d(2, 13.2, 2.5);
   glTexCoord2f(1,1); glVertex3d(2, 13.6, 2.5);
   glTexCoord2f(0,1); glVertex3d(2,13.6, 2.7); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.6 , 2.5);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.6, 2.5);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.6, 2.7);
   glTexCoord2f(0,1); glVertex3d(2, 13.6, 2.7); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.5);
   glTexCoord2f(1,0); glVertex3d(2, 13.6, 2.5);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.6, 2.5);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.5); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.8, 2.9);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.8, 2.9);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.9); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerDecoration4(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

    //middle pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.9, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.2, 2.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 14, 2.7);
   glTexCoord2f(0,1); glVertex3d(1.9,14, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.2, 2.7);
   glTexCoord2f(1,1); glVertex3d(2, 14, 2.7);
   glTexCoord2f(0,1); glVertex3d(2,14, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 14 , 2.7);
   glTexCoord2f(1,0); glVertex3d(1.9, 14, 2.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d(2, 14, 2.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.7);
   glTexCoord2f(1,0); glVertex3d(2, 14, 2.7);
   glTexCoord2f(1,1); glVertex3d( 1.9, 14, 2.7);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.7); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.9);
   glTexCoord2f(1,0); glVertex3d(2, 14, 2.9);
   glTexCoord2f(1,1); glVertex3d( 1.9, 14, 2.9);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.9); 
   glEnd();
   
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerDecoration5(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //medium pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.9, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.2, 1.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.8, 1.7);
   glTexCoord2f(0,1); glVertex3d(1.9,13.8, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.2, 1.7);
   glTexCoord2f(1,1); glVertex3d(2, 13.8, 1.7);
   glTexCoord2f(0,1); glVertex3d(2,13.8, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.8 , 1.7);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.8, 1.7);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.8, 1.9);
   glTexCoord2f(0,1); glVertex3d(2, 13.8, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 1.7);
   glTexCoord2f(1,0); glVertex3d(2, 13.8, 1.7);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.8, 1.7);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 1.7); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.8, 1.9);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.8, 1.9);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 1.9); 
   glEnd();

   //small pillar
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(1.9, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.2, 2.1);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.6, 2.1);
   glTexCoord2f(0,1); glVertex3d(1.9,13.6, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.2, 2.1);
   glTexCoord2f(1,1); glVertex3d(2, 13.6, 2.1);
   glTexCoord2f(0,1); glVertex3d(2,13.6, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 13.6 , 2.1);
   glTexCoord2f(1,0); glVertex3d(1.9, 13.6, 2.1);
   glTexCoord2f(1,1); glVertex3d(1.9, 13.6, 1.9);
   glTexCoord2f(0,1); glVertex3d(2, 13.6, 1.9); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 2.1);
   glTexCoord2f(1,0); glVertex3d(2, 13.6, 2.1);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.6, 2.1);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 2.1); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(2, 13.2 , 1.9);
   glTexCoord2f(1,0); glVertex3d(2, 13.6, 1.9);
   glTexCoord2f(1,1); glVertex3d( 1.9, 13.6, 1.9);
   glTexCoord2f(0,1); glVertex3d( 1.9, 13.2, 1.9); 
   glEnd();


   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}



static void TowerCone(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //base of cone
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,0);
   glTexCoord2f(0,0); glVertex3d(4.8, 13.3 , 2);
   glTexCoord2f(1,0); glVertex3d(2.5 , 13.3, 2);
   glTexCoord2f(1,1); glVertex3d( 2.5, 13.3, 0);
   glTexCoord2f(0,1); glVertex3d( 4.8, 13.3, 0); 
   glEnd();

   //4 sides of cone
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,1); //need to fix this
   glTexCoord2f(0,0); glVertex3d(2.5, 13.3, 2);
   glTexCoord2f(1/2,1); glVertex3d(3.65, 21, 1); 
   glTexCoord2f(1,0); glVertex3d(4.8, 13.3, 2); 
   glEnd();

   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-1,0,0); //need to fix this
   glTexCoord2f(0,0); glVertex3d(2.5, 13.3, 0);
   glTexCoord2f(1/2,1); glVertex3d(3.65, 21, 1); 
   glTexCoord2f(1,0); glVertex3d(2.5, 13.3, 2); 
   glEnd();

   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(1,0,0); //need to fix this
   glTexCoord2f(0,0); glVertex3d(4.8, 13.3, 0);
   glTexCoord2f(1/2,1); glVertex3d(3.65, 21, 1); 
   glTexCoord2f(1,0); glVertex3d(4.8, 13.3, 2); 
   glEnd();

   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,-1); //need to fix this
   glTexCoord2f(0,0); glVertex3d(2.5, 13.3, 0);
   glTexCoord2f(1/2,1); glVertex3d(3.65, 21, 1); 
   glTexCoord2f(1,0); glVertex3d(4.8, 13.3, 0); 
   glEnd();


   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void CastleBody(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //Main Castle
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , 5);
   glTexCoord2f(3,0); glVertex3d(7 , 4.5, 5);
   glTexCoord2f(3,3); glVertex3d( 7, -16, 5);
   glTexCoord2f(0,3); glVertex3d( -7, -16, 5 ); 
   glEnd();

   //right side
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(7, 4.5 , 5);
   glTexCoord2f(3,0); glVertex3d(7, 4.5, -4); 
   glTexCoord2f(3,3); glVertex3d( 7, -16, -4);
   glTexCoord2f(0,3); glVertex3d( 7 , -16, 5); 
   glEnd();

   //left side
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , 5);
   glTexCoord2f(3,0); glVertex3d(-7, 4.5, -4); 
   glTexCoord2f(3,3); glVertex3d(-7, -16, -4);
   glTexCoord2f(0,3); glVertex3d(-7 , -16, 5); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , -4);
   glTexCoord2f(3,0); glVertex3d(7 , 4.5, -4);
   glTexCoord2f(3,3); glVertex3d( 7, -16, -4);
   glTexCoord2f(0,3); glVertex3d( -7, -16, -4 ); 
   glEnd();

   //bottom
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-7, -16 , 5);
   glTexCoord2f(3,0); glVertex3d(7 , -16, 5);
   glTexCoord2f(3,3); glVertex3d( 7, -16, -4);
   glTexCoord2f(0,3); glVertex3d( -7, -16, -4); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void RightSidePlatform(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //Right side platform
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(6, 2 , 6);
   glTexCoord2f(3,0); glVertex3d(18 , 2, 6);
   glTexCoord2f(3,3); glVertex3d( 18, -16.1, 6);
   glTexCoord2f(0,3); glVertex3d( 6, -16.1, 6 ); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(18, 2 , 6);
   glTexCoord2f(3,0); glVertex3d(18, 2, -5 );
   glTexCoord2f(3,3); glVertex3d( 18, -16.1, -5);
   glTexCoord2f(0,3); glVertex3d(18 , -16.1, 6 ); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(6, 2 , -5);
   glTexCoord2f(3,0); glVertex3d(18 , 2, -5);
   glTexCoord2f(3,3); glVertex3d( 18, -16.1, -5);
   glTexCoord2f(0,3); glVertex3d( 6, -16.1, -5 ); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(6, 2 , 6);
   glTexCoord2f(3,0); glVertex3d(6, 2, -5);
   glTexCoord2f(3,3); glVertex3d(6, -16.1, -5);
   glTexCoord2f(0,3); glVertex3d( 6 , -16.1, 6); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(6, 2, 6);
   glTexCoord2f(3,0); glVertex3d(18, 2, 6);
   glTexCoord2f(3,3); glVertex3d(18, 2, -5);
   glTexCoord2f(0,3); glVertex3d(6, 2, -5); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(6, -16.1, 6);
   glTexCoord2f(3,0); glVertex3d(18, -16.1, 6);
   glTexCoord2f(3,3); glVertex3d(18, -16.1, -5);
   glTexCoord2f(0,3); glVertex3d(6, -16.1, -5); 
   glEnd();

   //Spawn floor continuted
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(6, 2.05 , 5);
   glTexCoord2f(3,0); glVertex3d(6 , 2.05, 3);
   glTexCoord2f(3,3); glVertex3d( 18, 2.05, 3);
   glTexCoord2f(0,3); glVertex3d( 18, 2.05, 5 ); 
   glEnd();


   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void RightSideHut(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //left side
   //left front triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(12, 2, 5.8);
   glTexCoord2f(1/2,1); glVertex3d(13, 9, 4.4);
   glTexCoord2f(1,1); glVertex3d(12.5, 5, 4.8);
   glEnd();

   //left back triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(12, 2, 2);
   glTexCoord2f(1/2,1); glVertex3d(13, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(12.5, 5, 2.9);
   glEnd();

   //left trapozoid between front and back triangles
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(12.5, 5,  2.9);
   glTexCoord2f(1,0); glVertex3d(13, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(13, 9, 4.4);
   glTexCoord2f(0,1);glVertex3d(12.5, 5, 4.8);
   glEnd();

   //hut, mini roof for entrances of hut
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(12, 5, 4.8);
   glTexCoord2f(1,0); glVertex3d(16, 5, 4.8);
   glTexCoord2f(1,1); glVertex3d(16, 5, 2.9);
   glTexCoord2f(0,1);glVertex3d(12, 5,  2.9);
   glEnd();

   //left side hut, mini roof face
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(12, 5, 4.8);
   glTexCoord2f(1,0); glVertex3d(12, 4.7, 4.9);
   glTexCoord2f(1,1); glVertex3d(12, 4.7, 2.8);
   glTexCoord2f(0,1);glVertex3d(12, 5,  2.9);
   glEnd();

   //left side front entrance triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(12, 5, 4.8);
   glTexCoord2f(1/2,1); glVertex3d(12.5, 5, 4.8);
   glTexCoord2f(1,1); glVertex3d(12, 2, 5.8);
   glEnd();
   
   //left side back entrance triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,-1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(12, 5, 2.9);
   glTexCoord2f(1/2,1); glVertex3d(12.5, 5, 2.9);
   glTexCoord2f(1,1); glVertex3d(12, 2, 2);
   glEnd();

   //right side front triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(1,0,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(16, 2, 5.8);
   glTexCoord2f(1/2,1); glVertex3d(15, 9, 4.4);
   glTexCoord2f(1,1); glVertex3d(15.5, 5, 4.8);
   glEnd();

   //right side back triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(1,0,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(16, 2, 2);
   glTexCoord2f(1/2,1); glVertex3d(15, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(15.5, 5, 2.9);
   glEnd();

   //right side trapazoid between triangles 
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(15.5, 5,  2.9);
   glTexCoord2f(1,0); glVertex3d(15, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(15, 9, 4.4);
   glTexCoord2f(0,1);glVertex3d(15.5, 5, 4.8);
   glEnd();

   //right side hut roof sides
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(16, 5, 4.8);
   glTexCoord2f(1,0); glVertex3d(16, 4.7, 4.9);
   glTexCoord2f(1,1); glVertex3d(16, 4.7, 2.8);
   glTexCoord2f(0,1);glVertex3d(16, 5,  2.9);
   glEnd();

   //right side front entrance triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(16, 5, 4.8);
   glTexCoord2f(1/2,1); glVertex3d(15.5, 5, 4.8);
   glTexCoord2f(1,1); glVertex3d(16, 2, 5.8);
   glEnd();

   //right side back entrance triangle
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,-1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(16, 5, 2.9);
   glTexCoord2f(1/2,1); glVertex3d(15.5, 5, 2.9);
   glTexCoord2f(1,1); glVertex3d(16, 2, 2);
   glEnd();

   //back of hut
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(13, 9, 3.2);
   glTexCoord2f(1,0); glVertex3d(15, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(16, 2, 2);
   glTexCoord2f(0,1);glVertex3d(12, 2,  2);
   glEnd();

   //top of hut
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(13, 9, 3.2);
   glTexCoord2f(1,0); glVertex3d(15, 9, 3.2);
   glTexCoord2f(1,1); glVertex3d(15, 9, 4.4);
   glTexCoord2f(0,1);glVertex3d(13, 9,  4.4);
   glEnd();

   //Front of hut (top piece) trapazoid
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(12.45, 4.8, 5.1);
   glTexCoord2f(1,0);glVertex3d(13, 9, 4.4);
   glTexCoord2f(1,1); glVertex3d(15, 9, 4.4);
   glTexCoord2f(0,1); glVertex3d(15.55, 4.8, 5.1);
   glEnd();

   //Front of hut, right side bottom piece trapazoid
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(12.45, 4.8, 5.1);
   glTexCoord2f(1,0); glVertex3d(13, 4.8, 5.1);
   glTexCoord2f(1,1); glVertex3d(12.8, 2, 5.8);
   glTexCoord2f(0,1);glVertex3d(12, 2, 5.8);
   glEnd();

   //Front of hut, left side bottom piece trapazoid
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(15.55, 4.8, 5.1);
   glTexCoord2f(1,0); glVertex3d(14.95, 4.8, 5.1);
   glTexCoord2f(1,1); glVertex3d(15, 2, 5.8);
   glTexCoord2f(0,1);glVertex3d(16, 2, 5.8);
   glEnd();

   //Front of hut, botom piece trapazoid
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(12.8, 3, 5.5);
   glTexCoord2f(1,0); glVertex3d(14.95, 3, 5.5);
   glTexCoord2f(1,1); glVertex3d(15, 2, 5.8);
   glTexCoord2f(0,1);glVertex3d(12.8, 2, 5.8);
   glEnd();

   



   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void HutWindow(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //horizontal bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-0.1, 0, 0.01);
   glTexCoord2f(2,0);glVertex3d(2, 0, 0.01);
   glTexCoord2f(2,2);    glVertex3d(2, .2, 0.01);
   glTexCoord2f(0,2);  glVertex3d(-0.1, .2, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0, .4, -0.08);
   glTexCoord2f(2,0);glVertex3d(2, .4, -0.08);
   glTexCoord2f(2,2);   glVertex3d(2, .6, -0.08);
   glTexCoord2f(0,2);  glVertex3d(0, .6, -0.08); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0, .8, -0.15);
   glTexCoord2f(2,0);glVertex3d(2, .8, -0.15);
   glTexCoord2f(2,2); glVertex3d(2, 1, -0.15);
   glTexCoord2f(0,2);   glVertex3d(0, 1, -0.15); 
   glEnd();

  glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.01, 1.2, -0.25);
      glTexCoord2f(2,0);glVertex3d(2, 1.2, -0.25);
     glTexCoord2f(2,2);  glVertex3d(1.9, 1.4, -0.25);
   glTexCoord2f(0,2);   glVertex3d(0.1, 1.4, -0.25); 
   glEnd();

   //vertical bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.2, 0 , 0.015);
     glTexCoord2f(2,0); glVertex3d(0.2, 1.8, -0.25);
      glTexCoord2f(2,2); glVertex3d(0.4, 1.8, -0.25);
   glTexCoord2f(0,2);   glVertex3d(0.4, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.6, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(0.6, 1.8, -0.25);
     glTexCoord2f(2,2);  glVertex3d(0.8, 1.8, -0.25);
   glTexCoord2f(0,2);   glVertex3d(0.8, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1, 1.8, -0.25);
      glTexCoord2f(2,2); glVertex3d(1.2, 1.8, -0.25);
   glTexCoord2f(0,2);   glVertex3d(1.2, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.4, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.4, 1.8, -0.25);
      glTexCoord2f(2,2); glVertex3d(1.6, 1.8, -0.25);
   glTexCoord2f(0,2);   glVertex3d(1.6, 0, 0.015); 
   glEnd();


  glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.8, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.8, 1.8, -0.25);
     glTexCoord2f(2,2);  glVertex3d(1.95, 1.8, -0.25);
   glTexCoord2f(0,2);   glVertex3d(1.95, 0, 0.015); 
   glEnd();


   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void LeftSidePlatform(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

   //Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //front
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(-4.5, 1.5, 8);
   glTexCoord2f(3,0); glVertex3d(-15, 1.5,  8);
   glTexCoord2f(3,3); glVertex3d(-15, -16.1, 8);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, 8);
   glEnd();

   //left
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-15, 1.5, 8);
   glTexCoord2f(3,0); glVertex3d(-15, 1.5,  -2);
   glTexCoord2f(3,3); glVertex3d(-15, -16.1, -2);
   glTexCoord2f(0,3);glVertex3d(-15, -16.1, 8);
   glEnd();
   
   //right
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(-4.5, 1.5, 8);
   glTexCoord2f(3,0); glVertex3d(-4.5, -16.1, 8);
   glTexCoord2f(3,3); glVertex3d(-4.5, -16.1, -2);
   glTexCoord2f(0,3);glVertex3d(-4.5, 1.5,  -2);
   glEnd();

   //back
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-4.5, 1.5, -2);
   glTexCoord2f(3,0); glVertex3d(-15, 1.5,  -2);
   glTexCoord2f(3,3); glVertex3d(-15, -16.1, -2);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, -2);
   glEnd();

   //bottom
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-4.5, -16.1, 8);
   glTexCoord2f(3,0); glVertex3d(-15, -16.1,  8);
   glTexCoord2f(3,3); glVertex3d(-15, -16.1, -2);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, -2);
   glEnd();

   //front of roof
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(-4.5, 1.5, 8);
   glTexCoord2f(1/2,1); glVertex3d(-15, 1.5 ,8);
   glTexCoord2f(1,1); glVertex3d(-7, 3 , 7);
   glEnd();

   //back of roof
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLES);
   glNormal3f(0,0,-1);//need to fix this
   glTexCoord2f(0,0); glVertex3d(-4.5, 1.5, -2);
   glTexCoord2f(1/2,1); glVertex3d(-15, 1.5 ,-2);
   glTexCoord2f(1,1); glVertex3d(-7, 3 , -1);
   glEnd();

   //right side of roof
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(-7, 3, 7);
   glTexCoord2f(1,0); glVertex3d(-7, 3, -1);
   glTexCoord2f(1,1); glVertex3d(-4.5, 1.5 , -2);
   glTexCoord2f(0,1); glVertex3d(-4.5, 1.5, 8);
   glEnd();

   //top of roof
   glColor3f(0,0.5,0);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);//need to fix this
   glTexCoord2f(0,0); glVertex3d(-7, 3, 7);
   glTexCoord2f(1,0); glVertex3d(-7, 3, -1);
   glTexCoord2f(1,1); glVertex3d(-15, 1.5 , -2);
   glTexCoord2f(0,1); glVertex3d(-15, 1.5, 8);
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void FrontPlatform(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

   //Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   //front
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-4.5, -1, 11);
   glTexCoord2f(3,0); glVertex3d(4, -1,  11);
   glTexCoord2f(3,3); glVertex3d(4, -16.1, 11);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, 11);
   glEnd();

   //top
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(-4.5, -1, 11);
   glTexCoord2f(2,0); glVertex3d(4, -1,  11);
   glTexCoord2f(2,2); glVertex3d(4, -1, 5);
   glTexCoord2f(0,2); glVertex3d(-4.5, -1, 5);
   glEnd();

   //right
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(4, -1, 11);
   glTexCoord2f(3,0); glVertex3d(4, -1,  5);
   glTexCoord2f(3,3); glVertex3d(4, -16.1, 5);
   glTexCoord2f(0,3); glVertex3d(4, -16.1, 11);
   glEnd();

   //left
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(-4.5, -1, 11);
   glTexCoord2f(3,0); glVertex3d(-4.5, -1,  5);
   glTexCoord2f(3,3); glVertex3d(-4.5, -16.1, 5);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, 11);
   glEnd();

   //bottom
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(-4.5, -16.1, 11);
   glTexCoord2f(3,0); glVertex3d(4, -16.1,  11);
   glTexCoord2f(3,3); glVertex3d(4, -16.1, 5);
   glTexCoord2f(0,3); glVertex3d(-4.5, -16.1, 5);
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void WoodenLedges(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //The bottom ledge.
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(2, 7, 4);
   glTexCoord2f(1,0); glVertex3d(2 , 7.3, 4);
   glTexCoord2f(1,1); glVertex3d(3.7, 7.3, 4);
   glTexCoord2f(0,1); glVertex3d(3.7, 7, 4); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3d(2, 7, 4);
   glTexCoord2f(1,0); glVertex3d(2 , 7, 3);
   glTexCoord2f(1,1); glVertex3d(3.7, 7, 3);
   glTexCoord2f(0,1); glVertex3d(3.7, 7, 4); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3d(2, 7.3, 4);
   glTexCoord2f(1,0); glVertex3d(2 , 7.3, 3);
   glTexCoord2f(1,1); glVertex3d(3.7, 7.3, 3);
   glTexCoord2f(0,1); glVertex3d(3.7, 7.3, 4); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3d(2, 7, 4);
   glTexCoord2f(1,0); glVertex3d(2 , 7.3, 4);
   glTexCoord2f(1,1); glVertex3d(2, 7.3, 3);
   glTexCoord2f(0,1); glVertex3d(2, 7, 3); 
   glEnd();

   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3d(3.7, 7, 4);
   glTexCoord2f(1,0); glVertex3d(3.7 , 7.3, 4);
   glTexCoord2f(1,1); glVertex3d(3.7, 7.3, 3);
   glTexCoord2f(0,1); glVertex3d(3.7, 7, 3); 
   glEnd();
  
   
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void CenterVerticalBricks(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(-7, 4.5 , 5.01);
   glTexCoord2f(2,0); glVertex3d(-6 , 4.5, 5.01);
   glTexCoord2f(2,2); glVertex3d( -6, -16, 5.01);
   glTexCoord2f(0,2); glVertex3d( -7, -16, 5.01); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void RightVerticalBricks(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3d(6, 2 , 6.01);
   glTexCoord2f(2,0); glVertex3d(7 , 2, 6.01);
   glTexCoord2f(2,2); glVertex3d(7, -16.1, 6.01);
   glTexCoord2f(0,2); glVertex3d(6, -16.1, 6.01); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void Windows(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=1;
   x1 = 1,
   y1=1;
   
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(0,0,0);
   glVertex3f(x1,y1,0.0);

   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //rectangle
   glColor3f(0,0,0);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glVertex3d(0, 0, 0);
   glVertex3d(2, 0, 0);
   glVertex3d(2, 1, 0);
   glVertex3d(0, 1, 0); 
   glEnd();

   //horizontal bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
    glTexCoord2f(0,0); glVertex3d(0, 0, 0.01);
      glTexCoord2f(2,0);glVertex3d(2, 0, 0.01);
   glTexCoord2f(2,2);    glVertex3d(2, .2, 0.01);
    glTexCoord2f(0,2);  glVertex3d(0, .2, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0, .4, 0.01);
      glTexCoord2f(2,0);glVertex3d(2, .4, 0.01);
    glTexCoord2f(2,2);   glVertex3d(2, .6, 0.01);
    glTexCoord2f(0,2);  glVertex3d(0, .6, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0, .8, 0.01);
      glTexCoord2f(2,0);glVertex3d(2, .8, 0.01);
      glTexCoord2f(2,2); glVertex3d(2, 1, 0.01);
   glTexCoord2f(0,2);   glVertex3d(0, 1, 0.01); 
   glEnd();

  glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.01, 1.2, 0.01);
      glTexCoord2f(2,0);glVertex3d(2, 1.2, 0.01);
     glTexCoord2f(2,2);  glVertex3d(1.9, 1.4, 0.01);
   glTexCoord2f(0,2);   glVertex3d(0.1, 1.4, 0.01); 
   glEnd();

   //vertical bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.2, 0 , 0.015);
     glTexCoord2f(2,0); glVertex3d(0.2, 1.6, 0.015);
      glTexCoord2f(2,2); glVertex3d(0.4, 1.8, 0.015);
   glTexCoord2f(0,2);   glVertex3d(0.4, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.6, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(0.6, 1.91, 0.015);
     glTexCoord2f(2,2);  glVertex3d(0.8, 1.98, 0.015);
   glTexCoord2f(0,2);   glVertex3d(0.8, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1, 2, 0.015);
      glTexCoord2f(2,2); glVertex3d(1.2, 1.98, 0.015);
   glTexCoord2f(0,2);   glVertex3d(1.2, 0, 0.015); 
   glEnd();

    glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.4, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.4, 1.92, 0.015);
      glTexCoord2f(2,2); glVertex3d(1.6, 1.8, 0.015);
   glTexCoord2f(0,2);   glVertex3d(1.6, 0, 0.015); 
   glEnd();


  glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.8, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.8, 1.64, 0.015);
     glTexCoord2f(2,2);  glVertex3d(1.95, 1.35, 0.015);
   glTexCoord2f(0,2);   glVertex3d(1.95, 0, 0.015); 
   glEnd();



   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void TowerWindow(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.8;
   x1 = 1,
   y1=1;
   
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(0,0,0);
   glVertex3f(x1,y1,0.0);

   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //rectangle
   glColor3f(0,0,0);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glVertex3d(0.2, 0, 0);
   glVertex3d(1.8, 0, 0);
   glVertex3d(1.8, 1, 0);
   glVertex3d(0.2, 1, 0); 
   glEnd();

   //horizontal bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.2, 0, 0.01);
   glTexCoord2f(2,0);  glVertex3d(1.8, 0, 0.01);
   glTexCoord2f(2,2);  glVertex3d(1.8, .2, 0.01);
   glTexCoord2f(2,2);  glVertex3d(0.2, .2, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.2, .4, 0.01);
   glTexCoord2f(2,0);glVertex3d(1.8, .4, 0.01);
   glTexCoord2f(2,2);   glVertex3d(1.8, .6, 0.01);
   glTexCoord2f(2,2);  glVertex3d(0.2, .6, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.2, .8, 0.01);
   glTexCoord2f(2,0);glVertex3d(1.8, .8, 0.01);
   glTexCoord2f(2,2); glVertex3d(1.8, 1, 0.01);
   glTexCoord2f(2,2);   glVertex3d(0.2, 1, 0.01); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.21, 1.2, 0.01);
   glTexCoord2f(2,0);glVertex3d(1.8, 1.2, 0.01);
   glTexCoord2f(2,2);  glVertex3d(1.7, 1.4, 0.01);
   glTexCoord2f(2,2);   glVertex3d(0.28, 1.4, 0.01); 
   glEnd();

   //vertical bars
   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.3, 0 , 0.015);
   glTexCoord2f(2,0); glVertex3d(0.3, 1.4, 0.015);
   glTexCoord2f(2,2); glVertex3d(0.5, 1.6, 0.015);
   glTexCoord2f(2,2);   glVertex3d(0.5, 0, 0.015); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(0.7, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(0.7, 1.71, 0.015);
   glTexCoord2f(2,2);  glVertex3d(0.9, 1.78, 0.015);
   glTexCoord2f(2,2);   glVertex3d(0.9, 0, 0.015); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.1, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.1, 1.8, 0.015);
   glTexCoord2f(2,2); glVertex3d(1.3, 1.7, 0.015);
   glTexCoord2f(2,2);   glVertex3d(1.3, 0, 0.015); 
   glEnd();

   glColor3f(1,1 ,1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(1.5, 0 , 0.015);
   glTexCoord2f(2,0);   glVertex3d(1.5, 1.62, 0.015);
   glTexCoord2f(2,2); glVertex3d(1.7, 1.4, 0.015);
   glTexCoord2f(2,2);   glVertex3d(1.7, 0, 0.015); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void Tornado(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.1;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void Tornado1(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.2;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado2(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.3;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado3(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.4;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado4(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.5;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado5(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.6;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado6(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.7;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado7(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.8;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado8(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=.9;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Tornado9(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glTranslatef(counter/600.0, 0.0, 0.0);
   glRotatef(counter, 1.0, 1.0, 1.0);
   counter += 1.0;

   if(counter > 8000)
      counter =0.0;

   //circle
   float x1,y1,x2,y2;
   float angle;
   double radius=1;
   x1 = 0,
   y1=0;
   glLineWidth(3.0);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_LINE_LOOP); 
   glColor3f(1,1,1);
   glVertex3f(x1,y1,0.0);
   for (angle=1.0f;angle<361.0f;angle+=0.2)
   {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glTexCoord2f(0,0); glVertex3f(x2,y2,0.0);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void Background(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{

   
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

//  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //Save current transforms
   glPushMatrix();
   //Offset, scale and rotate
   glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   glMultMatrixd(mat);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   
   
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(-200, -200, -200);
   glTexCoord2f(1,0);  glVertex3d(200, -200, -200);
   glTexCoord2f(1,1);  glVertex3d(200, 200, -200);
   glTexCoord2f(0,1);  glVertex3d(-200, 200, -200); 
   glEnd();

   glRotatef(-90.0,0.0,1.0,0.0);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(-200, -200, -200);
   glTexCoord2f(1,0);  glVertex3d(200, -200, -200);
   glTexCoord2f(1,1);  glVertex3d(200, 200, -200);
   glTexCoord2f(0,1);  glVertex3d(-200, 200, -200); 
   glEnd();

   glRotatef(-180.0,0.0,1.0,0.0);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(-200, -200, -200);
   glTexCoord2f(1,0);  glVertex3d(200, -200, -200);
   glTexCoord2f(1,1);  glVertex3d(200, 200, -200);
   glTexCoord2f(0,1);  glVertex3d(-200, 200, -200); 
   glEnd();

   //sky above
   glRotatef(90.0,1.0,0.0,0.0);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(-200, -200, -200);
   glTexCoord2f(1,0);  glVertex3d(200, -200, -200);
   glTexCoord2f(1,1);  glVertex3d(200, 200, -200);
   glTexCoord2f(0,1);  glVertex3d(-200, 200, -200); 
   glEnd();

   // ground
   glRotatef(180.0,0.0,1.0,0.0);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);  glVertex3d(-200, -200, -200);
   glTexCoord2f(1,0);  glVertex3d(200, -200, -200);
   glTexCoord2f(1,1);  glVertex3d(200, 200, -200);
   glTexCoord2f(0,1);  glVertex3d(-200, 200, -200); 
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {25*Cos(zh),ylight,10*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

   SpawnFloor(0,0,0, 1,0,0,  0,1,0);
   TowerMain(0,0,0, 1,0,0, 0,1,0);
   TowerCone(0,0,0, 1,0,0, 0,1,0);
   TowerCone(-7,-8.5,0, 1,0,0, 0,1,0);
   CastleBody(0,0,0, 1,0,0, 0,1,0);
   RightSidePlatform(0,0,0, 1,0,0, 0,1,0);
   RightSideHut(0,0,0, 1,0,0, 0,1,0);
   LeftSidePlatform(0,0,0, 1,0,0, 0,1,0);
   FrontPlatform(0,0,0, 1,0,0, 0,1,0);
   TowerCone(-4,-15,7, 1,0,0, 0,1,0);
   HutWindow(13,3,5.5, 1,0,0,  0,1,0);
   WoodenLedges(0,0,0, 1,0,0,  0,1,0);
   WoodenLedges(1.3,2,0, 1,0,0,  0,1,0);
   WoodenLedges(0,4.2,0, 1,0,0,  0,1,0);

   //right platform
   Windows(11.5,-1.3,6.1, 1,0,0,  0,1,0);
   //front platform
   Windows(-1.4,-4,11.1, 1,0,0,  0,1,0);
   //left platform
   Windows(-10,-2,8.1, 1,0,0,  0,1,0);
   //tower
   TowerWindow(3.35,11,3.01, 1,0,0,  0,1,0);

   //CastleBody Verticals
   CenterVerticalBricks(0,0,0, 1,0,0,  0,1,0);
   CenterVerticalBricks(4,0,0, 1,0,0,  0,1,0);
   CenterVerticalBricks(9,0,0, 1,0,0,  0,1,0);
   CenterVerticalBricks(13,0,0, 1,0,0,  0,1,0);

   RightVerticalBricks(0,0,0, 1,0,0,  0,1,0);
   RightVerticalBricks(4,0,0, 1,0,0,  0,1,0);
   RightVerticalBricks(8,0,0, 1,0,0,  0,1,0);
   RightVerticalBricks(11,0,0, 1,0,0,  0,1,0);

   //decorations (kind of messy)
   TowerDecoration1(0.1,0,0, 1,0,0,  0,1,0);
   TowerDecoration1(1.6,0,0, 1,0,0,  0,1,0);
   TowerDecoration2(0.1,0,0, 1,0,0,  0,1,0);
   TowerDecoration2(-1.4,0,0, 1,0,0,  0,1,0);

   TowerDecoration1(0.1,0,-3.9, 1,0,0,  0,1,0);
   TowerDecoration1(1.6,0,-3.9, 1,0,0,  0,1,0);
   TowerDecoration2(0.1,0,-3.9, 1,0,0,  0,1,0);
   TowerDecoration2(-1.4,0,-3.9, 1,0,0,  0,1,0);

   TowerDecoration3(0.1,0,0, 1,0,0,  0,1,0);
   TowerDecoration3(0.1,0,-2.1, 1,0,0,  0,1,0);
   TowerDecoration3(3.2,0,-2.1, 1,0,0,  0,1,0);

   TowerDecoration4(0.1,0,-1.9, 1,0,0,  0,1,0);
   TowerDecoration4(3.2,0,-1.9, 1,0,0,  0,1,0);
   TowerDecoration3(3.2,0,0, 1,0,0,  0,1,0);

   TowerDecoration5(0.1,0,-.7, 1,0,0,  0,1,0);
   TowerDecoration5(0.1,0,-2.6, 1,0,0,  0,1,0);
   TowerDecoration5(3.2,0,-2.6, 1,0,0,  0,1,0);
   TowerDecoration5(3.2,0,-.7, 1,0,0,  0,1,0);

   Tornado(-6.8,5.2,4, 1,0,0,  0,1,0);
   Tornado1(-6.8,5.4,4, 1,0,0,  0,1,0);
   Tornado2(-6.8,5.6,4, 1,0,0,  0,1,0);
   Tornado3(-6.8,5.8,4, 1,0,0,  0,1,0);
   Tornado4(-6.8,6,4, 1,0,0,  0,1,0);
   Tornado5(-6.8,6.2,4, 1,0,0,  0,1,0);
   Tornado6(-6.8,6.4,4, 1,0,0,  0,1,0);
   Tornado7(-6.8,6.6,4, 1,0,0,  0,1,0);
   Tornado8(-6.8,6.8,4, 1,0,0,  0,1,0);
   Tornado9(-6.8,7,4, 1,0,0,  0,1,0);

   Background(0,0,0, 1,0,0,  0,1,0);


   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Light=%s",th,ph,dim,light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(45,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Brian Alfano Final Project");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("shingles-jpg.bmp");
   texture[1] = LoadTexBMP("brickfloor-jpg.bmp");
   texture[2] = LoadTexBMP("cleanstone2-jpg.bmp");
   texture[3] = LoadTexBMP("boarderbrick-jpeg.bmp");
   texture[4] = LoadTexBMP("wood-jpg.bmp");
   texture[5] = LoadTexBMP("steelbar-jpg.bmp");
   texture[6] = LoadTexBMP("wind-jpg.bmp");
   texture[7] = LoadTexBMP("background-jpg.bmp");
   texture[8] = LoadTexBMP("grassbottom-jpeg.bmp");


   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
