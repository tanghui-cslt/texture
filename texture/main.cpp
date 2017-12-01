

/*  checker.c
 *  This program texture maps a checkerboard image onto
 *  two rectangles.
 *
 *  If running this program on OpenGL 1.0, texture objects are
 *  not used.
 */

#include "psBMPLoader.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Eigen\Dense"
using namespace Eigen;
#define PI 3.14159
#ifdef GL_VERSION_1_1
static GLuint texName;
#endif
static int L = 0, day = 0;

Vector3d convert_to_8Sphere(Vector2d v2)
{
	Vector3d temp_value;
	double u = v2[0];
	double v = v2[1];

	double x = sin(u)*cos(v);
	double y = sin(u)*sin(v);
	double z = cos(u);

	temp_value << x, y, z;
	return temp_value;
}

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

  // makeCheckImage();
  // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	psBMPLoader *pl=new psBMPLoader();
	pl->psLoad("logo.bmp");
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	pl->psMakeTexture();

}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   
   glPushMatrix();
  // glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
	glRotatef ((GLfloat) L, 1.0, 0.0, 0.0);
   
   
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


   glBindTexture(GL_TEXTURE_2D, texName);
	glColor3f(1.0,1.0,0.0);
	int piece_len = 30;
	double sum_i = 0;
	double sum_j = 0;
   glBegin(GL_QUADS);
	for (int  i = 0; i < piece_len; i++)
	{
		sum_i = i*1.0 / piece_len;
		for (int  j = 0; j < piece_len; j++)
		{
			sum_j = j*1.0 / piece_len;
			double pi_i = 2 * PI;
			double pi_j = PI;
			Vector2d temp(sum_i*pi_i, sum_j*pi_j);
			Vector3d temp_sp = convert_to_8Sphere(temp);
			glTexCoord2f(temp[0]/ pi_i, temp(1)/ pi_j); glVertex3f(temp_sp(0), temp_sp(1), temp_sp(2));



			temp(0) = (i+1)*1.0 / piece_len*pi_i;
			temp(1) = (j )*1.0 / piece_len*pi_j;
			 temp_sp = convert_to_8Sphere(temp);
			//std::cout << sum_i << " " << sum_j << std::endl;
			glTexCoord2f(temp(0) / pi_i, temp(1) / (pi_j)); glVertex3f(temp_sp(0), temp_sp(1), temp_sp(2));


			temp(0) = (i + 1)*1.0 / piece_len*pi_i;
			temp(1) = (j+1)*1.0 / piece_len*pi_j;
			 temp_sp = convert_to_8Sphere(temp);
			//std::cout << sum_i << " " << sum_j << std::endl;
			glTexCoord2f(temp(0) / pi_i, temp(1) / (pi_j)); glVertex3f(temp_sp(0), temp_sp(1), temp_sp(2));

			temp(0) = i*1.0 / piece_len*pi_i;
			temp(1) = (j + 1)*1.0 / piece_len*pi_j;
			 temp_sp = convert_to_8Sphere(temp);
			glTexCoord2f(temp(0) / pi_i, temp(1) / (pi_j)); glVertex3f(temp_sp(0), temp_sp(1), temp_sp(2));

		}

	}
   //glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);

   //glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);

   //glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);

   //glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);

   //glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);

   //glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
   //glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
   //glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
   //glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);

   glEnd();



   glPopMatrix();
   glutSwapBuffers();

   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
   glRotatef(-20.0, 0.0, 1.0, 0.0);
   glRotatef(30.0, 1.0, 0.0, 0.0);

}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'a':
         L = (L + 10) % 360;
         glutPostRedisplay();
         break;
      case 'A':
         L = (L - 10) % 360;
         glutPostRedisplay();
         break;

      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(750, 750);
   glutInitWindowPosition( 0, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}

