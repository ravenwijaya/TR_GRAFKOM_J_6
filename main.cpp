#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void ukuran(int, int);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;
 //Deklarasi Variable
float z_pos=-10.0f;
float rot=0.0f;

 void myTimeOut(int id)
{
// called if timer event
// ...advance the state of animation incrementally...
       rot+=10;
       glutPostRedisplay(); // request redisplay
       glutTimerFunc(100, myTimeOut, 0); // request next timer event
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("TR_GRAFKOM_J_6");
	glutTimerFunc(100, myTimeOut, 0);
	init();
	glutDisplayFunc(tampil);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(ukuran);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(tampil);
	glutMainLoop();
	return 0;
}

void atap(int x1,int y1,int z1,int s,int p,int l,int t){
	//bawah
	int x2 = x1+p;
	int y2= y1;
	int z2=z1;
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x1,y1,z1-l);
	glEnd();

	//atas 
	glBegin(GL_QUADS);
	glVertex3f(x1+s,y1+t,z1-s);
	glVertex3f(x2-s,y2+t,z2-s);
	glVertex3f(x2-s,y2+t,z2-l+s);
	glVertex3f(x1+s,y1+t,z1-l+s);
	glEnd();
	
	//depan
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2-s,y2+t,z2-s);
	glVertex3f(x1+s,y1+t,z1-s);
	glEnd();
	
	//belakang
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2-s,y2+t,z2-l+s);
	glVertex3f(x1+s,y1+t,z1-l+s);
	glEnd();
	
	//samping kanan
	glBegin(GL_QUADS);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2-s,y2+t,z2-l+s);
	glVertex3f(x2-s,y2+t,z2-s);
	glEnd();
	
	//samping kiri
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x1+s,y1+t,z1-l+s);
	glVertex3f(x1+s,y1+t,z1-s);
	glEnd();	
		
}


void kubus(int x1,int y1,int z1,int p,int l,int t){
	//bawah
	int x2 = x1+p;
	int y2= y1;
	int z2=z1;
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x1,y1,z1-l);
	glEnd();

	//atas 
	glBegin(GL_QUADS);
	glVertex3f(x1,y1+t,z1);
	glVertex3f(x2,y2+t,z2);
	glVertex3f(x2,y2+t,z2-l);
	glVertex3f(x1,y1+t,z1-l);
	glEnd();
	
	//depan
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2+t,z2);
	glVertex3f(x1,y1+t,z1);
	glEnd();
	
	//belakang
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2,y2+t,z2-l);
	glVertex3f(x1,y1+t,z1-l);
	glEnd();
	
	//samping kanan
	glBegin(GL_QUADS);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2,y2+t,z2-l);
	glVertex3f(x2,y2+t,z2);
	glEnd();
	
	//samping kiri
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x1,y1+t,z1-l);
	glVertex3f(x1,y1+t,z1);
	glEnd();	
		
}

//void jendela(int x1,int y1,int z,int p,int t){
//  for(int i=0;i<11;i++){
//  	int sp=0;
//  	x1+=sp;
//	int x2 = x1+p;
//	int y2= y1;
//	glBegin(GL_QUADS);
//	glVertex3f(x1,y1,z);
//	glVertex3f(x2,y2,z);
//	glVertex3f(x2,y2+t,z);
//	glVertex3f(x1,y1+t,z);
//	glEnd();
//	sp+=5;
//	  }
//	
//	
//		
//}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	//fungsi ke belakang gelap
//	glEnable(GL_LIGHTING);
//	glEnable(GL_COLOR_MATERIAL);
//	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);
	glPointSize(9.0);
	glLineWidth(6.0f);
	is_depth = 1;
}

void tampil(void)
{  float u = ((float)rand()/(float)(RAND_MAX)) * 1;
    float p = ((float)rand()/(float)(RAND_MAX)) * 1;
     float q = ((float)rand()/(float)(RAND_MAX)) * 1;
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (is_depth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
//	glLoadIdentity();

	//mengatur kamera
	gluLookAt(0.0f, 5.0f, 50.0f,0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f);
	//biar bisa muter
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	
    //main building 1
	glColor3f(0.95,0.40,0.20);
	kubus(-400,-40,-20,500,100,40);
	   //main sep 1
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,0,-20,500,100,5);
   	   
   	//main building 2
	glColor3f(0.95,0.40,0.20);
	kubus(-400,5,-20,500,100,30);
	    //main sep 2
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,35,-20,500,100,5);
   	   
   	//main building 3
	glColor3f(0.95,0.40,0.20);
	kubus(-400,40,-20,500,100,30);
	    //main sep 3
	    glColor3f(0.95,0.9,0.85);
   	   kubus(-400,70,-20,500,100,5);
   	   
				   	//mainside1
				   	glColor3f(0.95,0.40,0.20);
					kubus(0,75,-20,100,100,15);
					   //mainside sep 1
					   glColor3f(0.95,0.9,0.85);
				   	   kubus(0,90,-20,100,100,1);
				   	   
				   	//mainside2
				   	 glColor3f(0.95,0.40,0.20);
					kubus(0,91,-20,100,100,4);
					  //mainside sep 2
					    glColor3f(0.95,0.9,0.85);
				   	   kubus(0,95,-20,100,100,1);
				   	   
				   	   int yy=0;
				   	   for(int j=0;j<=2;j++){
				   	   	int sp=0;
				   	   	for(int i=0;i<=11;i++){
				   	   	glColor3f(0.95,0.9,0.85);
				     	kubus(5+sp,-30+yy,-19,5,1.5,20);
						sp+=8;  }
						yy+=39;
						  }
				   	   
				     	
				     
				     
				   
				   	
	//mainbuilding 4
   	glColor3f(0.95,0.40,0.20);
	kubus(-400,75,-20,400,100,25);
	 //main sep 4
	    glColor3f(0.95,0.9,0.85);
   	   kubus(-400,100,-20,400,100,5);
   	   
   	//mainbuilding 5
     glColor3f(0.95,0.40,0.20);
	kubus(-400,105,-20,400,100,30);
	 //main sep 5
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,135,-20,400,100,5);
  	   
   	     //roof1
	     glColor3f(1,1,1);
   	     kubus(-70,98,100,75,120,12);
	   	     //pil1
		     glColor3f(1,1,1);
	   	     kubus(-5,-40,100,10,10,150);
	   	     //pil2
		     glColor3f(1,1,1);
	   	     kubus(-5,-40,80,10,10,150);
	   	     //-1
	   	     glColor3f(1,1,1);
	   	     kubus(-5,60,90,10,10,10);
	   	      //-2
	   	     glColor3f(1,1,1);
	   	     kubus(-5,20,90,10,10,10);
	   	     //pilb
	   	     glColor3f(1,1,1);
	   	       kubus(-70,-40,100,10,30,150);
	   	     
	   	     
	   	     
	   	     
	    //roof2
	     glColor3f(1,1,1);
     	   kubus(-180,98,100,75,120,12);
     	     //pila
	   	     glColor3f(1,1,1);
	   	       kubus(-115,-40,100,10,30,150);
     	     //pilb
	   	     glColor3f(1,1,1);
	   	       kubus(-180,-40,100,10,30,150);
   	   //rooffbawah
	   glColor3f(1,1,1);
	   kubus(-215,5,100,35,120,6);
   	    //roof3
	  glColor3f(1,1,1);
   	   kubus(-290,98,100,75,120,12);
   	   //pila
	   	     glColor3f(1,1,1);
	   	       kubus(-290,-40,100,10,30,150);
     	     //pilb
	   	     glColor3f(1,1,1);
	   	       kubus(-225,-40,100,10,30,150);
  	    //roof4
	    glColor3f(1,1,1);
  	   kubus(-400,98,100,75,120,12);
  	   //pila
	   	     glColor3f(1,1,1);
	   	       kubus(-400,-40,100,10,30,150);
     	     //pilb
	   	     glColor3f(1,1,1);
	   	       kubus(-335,-40,100,10,30,150);
	
   	   
	
		//tanah
    
    kubus(-400,-80,200,600,400,39.9);
	
	glRotatef(rot, 0, 1, 0);
	
	glColor3f(u,p,q);
	kubus(20,150,20,60,20,39.9);


	glPopMatrix();
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//zoom in
	case 'w':
	case 'W':
		glTranslatef(0.0, 0.0, 3.0);
		break;
	//geser kanan
	case 'd':
	case 'D':
		glTranslatef(3.0, 0.0, 0.0);
		break;
	//zoom out
	case 's':
	case 'S':
		glTranslatef(0.0, 0.0, -3.0);
		break;
	//geser kiri
	case 'a':
	case 'A':
		glTranslatef(-3.0, 0.0, 0.0);
		break;
	//geser atas
	case '7':
		glTranslatef(0.0, 3.0, 0.0);
		break;
	//geser bawah
	case '9':
		glTranslatef(0.0, -3.0, 0.0);
		break;
	//putar ke tanah
	case '2':
		glRotatef(2.0, 1.0, 0.0, 0.0);
		break;
	//putar ke langit
	case '8':
		glRotatef(-2.0, 1.0, 0.0, 0.0);
		break;
	//putar ke kanan
	case '6':
		glRotatef(2.0, 0.0, 1.0, 0.0);
		break;
	//putar ke kiri
	case '4':
		glRotatef(-2.0, 0.0, 1.0, 0.0);
		break;
	//putar arah jarum jam
	case '1':
		glRotatef(-2.0, 0.0, 0.0, 1.0);
		break;
	//cek kedalaman objek
	case '5':
		if (is_depth)
		{
			is_depth = 0;
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			is_depth = 1;
			glEnable(GL_DEPTH_TEST);
		}
	}
	tampil();
}
void idle()
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{	
	//menggerakan mouse saat ditahan kiri nya
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void ukuran(GLsizei lebar, GLsizei tinggi)
{
	if (tinggi == 0) tinggi = 1;
	GLfloat aspect = (GLfloat)lebar/(GLfloat)tinggi;
	glViewport(0,0,lebar,tinggi);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}
