#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#define DEF_D 5
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
#define PI 3.1415926535898
#include <stdio.h>

//Deklarasi Fungsi
void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void ukuran(int, int);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

//Deklarasi Variable
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;
float z_pos=-10.0f;
float rot=0.0f;


float m1,c1,m2,c2,x,y;
void cari1 (float x1,float x2,float y1,float y2){
m1=(y2-y1)/(x2-x1);
c1=y1-(m1*x1);
}
void cari2 (float x1,float x2,float y1,float y2){
m2=(y2-y1)/(x2-x1);
c2=y1-(m2*x1);
}
void hasil (){
x=(c2-c1)/(m1-m2);
y=(m2*x)+c2;
//printf("%f\n",c1);
}








const double pi = 3.141592653589793;
 void myTimeOut(int id)
{
       rot+=1;
       glutPostRedisplay(); 
       glutTimerFunc(100, myTimeOut, 0); // Kecepatan
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

void sampah(int x1,int y1,int z1,int s,int p,int l,int t){
	int x2 = x1+p;
	int y2= y1;
	int z2=z1;

	//depan
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2+s,y2+t,z2+s);
	glVertex3f(x1-s,y1+t,z1+s);
	glEnd();
	
	//belakang
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2+s,y2+t,z2-l-s);
	glVertex3f(x1-s,y1+t,z1-l-s);
	glEnd();
	
	//samping kanan
	glBegin(GL_QUADS);
	glVertex3f(x2,y2,z2);
	glVertex3f(x2,y2,z2-l);
	glVertex3f(x2+s,y2+t,z2-l-s);
	glVertex3f(x2+s,y2+t,z2+s);
	glEnd();
	
	//samping kiri
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x1,y1,z1-l);
	glVertex3f(x1-s,y1+t,z1-l-s);
	glVertex3f(x1-s,y1+t,z1+s);
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

void lingkaranh(float x_mid,float y,float z_mid, float r,float n,float rot){
	float rotangle= rot*pi/180;
	for(int i=1;i<=n;i++){
		float x= x_mid + (r*cos((i*2*pi/n)+rotangle));
		float z= z_mid + (r*sin((i*2*pi/n)+rotangle));
		glVertex3f(x,y,z);
	}

}

float titik1[20][2];
float titik2[20][2];

void lingkaransave(float x_mid,float z_mid, float r,float n,int p){
	
	for(int i=0;i<n;i++){
		float x= x_mid + (r*cos(i*2*pi/n));
		float z= z_mid + (r*sin(i*2*pi/n));
		if (p==1){
		titik1[i][0]= x;
		titik1[i][1]= z;
		}
		else {
		titik2[i][0]= x;
		titik2[i][1]= z;
		}
	}
}

void selimut(float x,float y, float z,float r,float t){
	 for (int j=0;j<=400;j+=DEF_D) {
	
		glVertex3f(r*Cos(j)+x,t,r*Sin(j)+z);
	    glVertex3f(r*Cos(j)+x,y,r*Sin(j)+z);
		}
}

void init(void)
{
	glClearColor(0.4823529411764706, 0.7176470588235294, 1,0);
	glMatrixMode(GL_PROJECTION);

	//fungsi ke belakang gelap
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);
	glPointSize(9.0);
	glLineWidth(6.0f);
	is_depth = 1;
}

void tampil(void)
{  
	float u = ((float)rand()/(float)(RAND_MAX)) * 1;
    float p = ((float)rand()/(float)(RAND_MAX)) * 1;
     float q = ((float)rand()/(float)(RAND_MAX)) * 1;
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (is_depth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//mengatur kamera
	gluLookAt(0.0f, 5.0f, 50.0f,0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f);
	
	//biar bisa muter
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	
    //main building 1
	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
	kubus(-400,-40,-220,500,100,40);
	   //main sep 1
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,0,-220,500,100,5);
   	   
   	//main building 2
	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
	kubus(-400,5,-220,500,100,30);
	    //main sep 2
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,35,-220,500,100,5);
   	   
   	//main building 3	
	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
	kubus(-400,40,-220,500,100,30);
	    //main sep 3
	    glColor3f(0.95,0.9,0.85);
   	   kubus(-400,70,-220,500,100,5);
   	   
				   	//mainside1
				   	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
					kubus(0,75,-220,100,100,15);
					   //mainside sep 1
					   glColor3f(0.95,0.9,0.85);
				   	   kubus(0,90,-220,100,100,1);
				   	   
				   	//mainside2
				   	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
					kubus(0,91,-220,100,100,4);
					  //mainside sep 2
					    glColor3f(0.95,0.9,0.85);
				   	   kubus(0,95,-220,100,100,1);
				   	   
				   	   int yy=0;
				   	   for(int j=0;j<=2;j++){
				   	   	int sp=0;
				   	   	for(int i=0;i<=11;i++){
				   	   	glColor3f(0.95,0.9,0.85);
				     	kubus(5+sp,-30+yy,-219,5,1.5,20);
						sp+=8;  }
						yy+=39;
						  }
						  	
						  	//jendelaa biru
					    int yo=0;
				   	   for(int j=0;j<=1;j++){
				   	   	int sp=0;
				   	   	for(int i=0;i<=15;i++){
				   	   	glColor3f(0.7, 0.7, 0.7);
				     	kubus(-400+sp,9+yo,-219,20,1.5,20);
						sp+=25;  }
						yo+=39;
						  }
						  
		//pilarselimut		
		glBegin(GL_QUAD_STRIP);
     	glColor3f(0.9,0.9,0.85);
	    selimut(-15,-40,-155,3,100);
		glEnd();
		
		glBegin(GL_QUAD_STRIP);
	    selimut(-15,-40,-175,3,100);
		glEnd();
			
		glBegin(GL_QUAD_STRIP);
	    selimut(-15,-40,-200,3,100);
		glEnd();
		
		glBegin(GL_QUAD_STRIP);
	    selimut(-55,-40,-155,3,100);
		glEnd();
		
		glBegin(GL_QUAD_STRIP);
	    selimut(-55,-40,-175,3,100);
		glEnd();
			
		glBegin(GL_QUAD_STRIP);
	    selimut(-55,-40,-200,3,100);
		glEnd();
		//lantai
		kubus(-400,-40,-100,330,120,1);
		
	//mainbuilding 4
   	glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
	kubus(-400,75,-220,400,100,25);
	 //main sep 4
	    glColor3f(0.95,0.9,0.85);
   	   kubus(-400,100,-220,400,100,5);
   	   
   	//mainbuilding 5
    glColor3f(0.8117647058823529,0.3882352941176471,0.2156862745098039);
	kubus(-400,105,-220,400,100,30);
	 //main sep 5
	   glColor3f(0.95,0.9,0.85);
   	   kubus(-400,135,-220,400,100,5);
  	   
   	     //roof1
	     glColor3f(0.9058823529411765,0.9058823529411765,0.9);
   	     kubus(-70,98,-100,75,120,12);
	   	     //pil1
	   	     kubus(-5,-40,-100,10,10,150);
	   	     //pil2
	   	     kubus(-5,-40,-120,10,10,150);
	   	     //-1
	   	     kubus(-5,60,-110,10,10,10);
	   	      //-2
	   	     kubus(-5,20,-110,10,10,10);
	   	     //pilb
	   	       kubus(-70,-40,-100,10,30,150);
	   	       
   	           glTranslatef(0,0,-30);
	   	       //roofup1
            	glColor3f(0.8,0.8,0.8);
   	           kubus(-105,98,-50,35,170,12);
   	           //pilar
   	           glBegin(GL_QUAD_STRIP);
	           selimut(-90,-40,-70,3,100);
	         	glEnd();
	         	//pilkanan kecil
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-72,-40,-53,1,100);
	         	glEnd();
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-72,-40,-80,1,100);
	         	glEnd();
	         	//pilkiri kecil
	         	
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-103,-40,-53,1,100);
	         	glEnd();
	            //1
	         	kubus(-104,80,-53,2,50,2);
	         	kubus(-104,70,-53,2,50,2);
	         	
	         	kubus(-73,80,-53,2,50,2);
	         	kubus(-73,70,-53,2,50,2);
	         	
	         	kubus(-104,80,-53,31,1,2);
	         	kubus(-104,70,-53,31,1,2);
	         	//2
	         	kubus(-104,50,-53,2,50,2);
	         	kubus(-104,40,-53,2,50,2);
	         	
	         	kubus(-73,50,-53,2,50,2);
	         	kubus(-73,40,-53,2,50,2);
	         	
	         	kubus(-104,50,-53,31,1,2);
	         	kubus(-104,40,-53,31,1,2);
	         	
	            //3
	         	kubus(-104,20,-53,2,50,2);
	         	kubus(-104,10,-53,2,50,2);
	         	
	         	kubus(-73,20,-53,2,50,2);
	         	kubus(-73,10,-53,2,50,2);
	         	
	         	kubus(-104,20,-53,31,1,2);
	         	kubus(-104,10,-53,31,1,2);
	         	//4
	         	
	         	kubus(-104,-10,-53,2,50,2);
	         	kubus(-104,-20,-53,2,50,2);
	         	
	         	kubus(-73,-10,-53,2,50,2);
	         	kubus(-73,-20,-53,2,50,2);
	         	
	         	kubus(-104,-10,-53,31,1,2);
	         	kubus(-104,-20,-53,31,1,2);
   	           
   	            glTranslatef(0,0,30);
   	            glTranslatef(-220,0,-30);
   	            
   	            //abu2
   	            //roofup1
            	glColor3f(0.8,0.8,0.8);
   	           kubus(-105,98,-50,35,170,12);
   	            //pilar
   	           glBegin(GL_QUAD_STRIP);
	           selimut(-90,-40,-70,3,100);
	         	glEnd();
	         	//pilkanan kecil
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-72,-40,-53,1,100);
	         	glEnd();
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-72,-40,-80,1,100);
	         	glEnd();
	         	//pilkiri kecil
	         	
	         	glBegin(GL_QUAD_STRIP);
	            selimut(-103,-40,-53,1,100);
	         	glEnd();
	            //1
	         	kubus(-104,80,-53,2,50,2);
	         	kubus(-104,70,-53,2,50,2);
	         	
	         	kubus(-73,80,-53,2,50,2);
	         	kubus(-73,70,-53,2,50,2);
	         	
	         	kubus(-104,80,-53,31,1,2);
	         	kubus(-104,70,-53,31,1,2);
	         	//2
	         	kubus(-104,50,-53,2,50,2);
	         	kubus(-104,40,-53,2,50,2);
	         	
	         	kubus(-73,50,-53,2,50,2);
	         	kubus(-73,40,-53,2,50,2);
	         	
	         	kubus(-104,50,-53,31,1,2);
	         	kubus(-104,40,-53,31,1,2);
	         	
	            //3
	         	kubus(-104,20,-53,2,50,2);
	         	kubus(-104,10,-53,2,50,2);
	         	
	         	kubus(-73,20,-53,2,50,2);
	         	kubus(-73,10,-53,2,50,2);
	         	
	         	kubus(-104,20,-53,31,1,2);
	         	kubus(-104,10,-53,31,1,2);
	         	//4
	         	
	         	kubus(-104,-10,-53,2,50,2);
	         	kubus(-104,-20,-53,2,50,2);
	         	
	         	kubus(-73,-10,-53,2,50,2);
	         	kubus(-73,-20,-53,2,50,2);
	         	
	         	kubus(-104,-10,-53,31,1,2);
	         	kubus(-104,-20,-53,31,1,2);
   	           
   	            glTranslatef(220,0,30);
   	            
   	            
   	           glColor3f(0.9058823529411765,0.9058823529411765,0.9);
	    //roof2
     	   kubus(-180,98,-100,75,120,12);
     	     //pila
	   	       kubus(-115,-40,-100,10,30,150);
     	     //pilb
	   	       kubus(-180,-40,-100,10,30,150);
	   	       
   	   //rooffbawah
   	   glTranslatef(0,0,30);
   	   glColor3f(0.9,0.9,0.85);
	   kubus(-215,5,-50,35,90,6);
			//pila
			kubus(-215,-40,-50,5,10,51);
			 //pilb
	   		kubus(-185,-40,-50,5,10,51);
   	   glTranslatef(0,0,-30);
	   
	     glColor3f(0.9058823529411765,0.9058823529411765,0.9);
	   //pintu
	     kubus(-210,-40.5,-219.5,20,1,30);
   	    //roof3
   	   kubus(-290,98,-100,75,120,12);
   	   //pila
	   	       kubus(-290,-40,-100,10,30,150);
     	     //pilb
	   	       kubus(-225,-40,-100,10,30,150);
  	    //roof4
  	   kubus(-400,98,-100,75,120,12);
  	   //pila
	   	       kubus(-400,-40,-100,10,30,150);
     	     //pilb
	   	       kubus(-335,-40,-100,10,30,150);

	   	//pilsamping
	   	  glColor3f(1,0.9058823529411765,0.9);
	   	    kubus(100,-40,-230,10,10,150);
	   	    kubus(100,-40,-260,10,10,150);
	   	    
	   	    kubus(100,20,-230,10,30,10);
	   	     kubus(100,50,-230,10,30,10);
	   	     kubus(100,95,-230,10,30,15);
	//tanah
	glColor3f(0.6196078431372549,0.5294117647058824,0.3529411764705882);
    kubus(-450,-80,20,700,400,39.9);
	
	//struktur tanah bawah
	glColor3f(0.7098039215686275,0.6470588235294118,0.607843137254902);
	glBegin(GL_POLYGON);
	lingkaranh(120,-40,-90,50,20,0);
	glEnd();
	
	lingkaransave(120,-90,55,20,1);
	lingkaransave(120,-90,90,20,2);

	// tanah melingkar 
	for(int i=0;i<5;i++){
		int a=0;
		glBegin(GL_POLYGON);
		for(int j=4*i;j<=(4*i)+3;j++){
			glVertex3f(titik1[j][0],-40,titik1[j][1]);
		}
		for(int j=4*i;j<=(4*i)+3;j++){
			glBegin(GL_POLYGON);
			glVertex3f(titik2[(4*i)+3-a][0],-40,titik2[(4*i)+3-a][1]);
			a++;
		}
		glEnd();
	}
	
	//lingkaran merah taman
	glColor3f(0.6431372549019608,0.1686274509803922,0.0549019607843137);
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,0);
	lingkaranh(120,-30,-90,30,20,180);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,180);
	lingkaranh(120,-30,-90,30,20,0);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,270);
	lingkaranh(120,-30,-90,30,20,90);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,90);
	lingkaranh(120,-30,-90,30,20,270);
	glEnd();
	//rumput atas lingkar merah
	glColor3f(0.5137254901960784,1,0.2);
	glTranslatef(120,-45,-90);
    glutSolidSphere(25,10,10);
	glTranslatef(-120,45,40);
	//rumput kecil atasnya lagi
	glColor3f(0.5137254901960784,0.8,0.2);
	glTranslatef(105,-25,-40);
    glutSolidSphere(7,10,10);
	glTranslatef(-105,25,40);
	glTranslatef(115,-25,-25);
    glutSolidSphere(7,10,10);
	glTranslatef(-115,25,25);
	glTranslatef(130,-25,-40);
    glutSolidSphere(7,10,10);
	glTranslatef(-130,25,40);
	glTranslatef(120,-25,-50);
    glutSolidSphere(7,10,10);
	glTranslatef(-120,25,50);
	//tongkat senter di keliling lingkaran
	glColor3f(0,0,0);
	kubus(175,-40, -25, 2,2,10);
	kubus(163,-40, -5, 2,2,10);
	kubus(100,-40, 15, 2,2,10);
	kubus(120,-40, 17, 2,2,10);
	kubus(65,-40, -40, 2,2,10);
	kubus(70,-40, -20, 2,2,10);
	kubus(80,-40, -85, 2,2,10);
	kubus(100,-40, -95, 2,2,10);
	kubus(150,-40, -85, 2,2,10);
	kubus(168,-40, -65, 2,2,10);
	//rumput hijau
	glColor3f(0.5137254901960784,0.8,0.2);
	glTranslatef(95,-35,30);
    glutSolidSphere(10,10,10);
	glTranslatef(-95,35,-30);
	glTranslatef(125,-35,32);
    glutSolidSphere(10,10,10);
	glTranslatef(-125,35,-32);
	glTranslatef(190,-35,-20);
    glutSolidSphere(10,10,10);
	glTranslatef(-12,0,28);
    glutSolidSphere(10,10,10);
	glTranslatef(-178,35,-8);
	glTranslatef(97,-35,-110);
    glutSolidSphere(10,10,10);
	glTranslatef(-97,35,110);
	glTranslatef(72,-35,-100);
    glutSolidSphere(10,10,10);
	glTranslatef(-72,35,100);
	glTranslatef(160,-35,-100);
    glutSolidSphere(10,10,10);
	glTranslatef(-160,35,100);	
	glTranslatef(180,-35,-80);
    glutSolidSphere(10,10,10);
	glTranslatef(-180,35,80);	
	glTranslatef(50,-35,-15);
    glutSolidSphere(10,10,10);
	glTranslatef(-50,35,15);	
	glTranslatef(47,-35,-50);
    glutSolidSphere(10,10,10);
	glTranslatef(47,35,50);	
	
	//tanah kiri1
	glColor3f(0.7098039215686275,0.6470588235294118,0.607843137254902);
	kubus(-165,-40,0,75,50,1);
	//tempat sampah
	glColor3f(1,1,0);
	sampah(-150,-40,-15,5,10,20,25);
	glColor3f(0,0,0);
	sampah(-149,-40,-15,5,12,22,27);
	glColor3f(1,0,1);
	sampah(-115,-40,-15,5,10,20,25);
	glColor3f(0,0,0);
	sampah(-114,-40,-15,5,12,22,27);
	
	//tanah kiri2
	glColor3f(0.7098039215686275,0.6470588235294118,0.607843137254902);
	kubus(-275,-40,0,75,50,1);
    //pohon
	glColor3f(0.5137254901960784,1,0.2);
	glTranslatef(-250,5,-20);
    glutSolidSphere(15,50,10);
	glTranslatef(250,-5,20);   
    glTranslatef(-250,20,-20);
    glutSolidSphere(10,50,10);
	glTranslatef(250,-20,20);   
    glTranslatef(-260,8,-20);
    glutSolidSphere(10,50,10);
	glTranslatef(260,-8,20);    
    glTranslatef(-245,0,-30);
    glutSolidSphere(10,50,10);
	glTranslatef(260,-3,20);  
    //tongkat
    glColor3f(0.5,0.3,0.2);
    kubus(-270,-39,-10,5,5,35);
    glTranslatef(30,0,0);
    glColor3f(0.7098039215686275,0.6470588235294118,0.607843137254902);
	kubus(-275,-40,0,75,50,1);
    //pohon
	glColor3f(0.5137254901960784,1,0.2);
	glTranslatef(-250,5,-20);
    glutSolidSphere(15,50,10);
	glTranslatef(250,-5,20);   
    glTranslatef(-250,20,-20);
    glutSolidSphere(10,50,10);
	glTranslatef(250,-20,20);   
    glTranslatef(-260,8,-20);
    glutSolidSphere(10,50,10);
	glTranslatef(260,-8,20);    
    glTranslatef(-245,0,-30);
    glutSolidSphere(10,50,10);
	glTranslatef(260,-3,20);  
    //tongkat
    glColor3f(0.5,0.3,0.2);
    kubus(-270,-39,-10,5,5,35);
    glTranslatef(-30,0,0);
    glTranslatef(-610,6,120);
    //tanah4
    glColor3f(0.7098039215686275,0.6470588235294118,0.607843137254902);
	glBegin(GL_POLYGON);
	lingkaranh(120,-40,-90,50,20,0);
	glEnd();
    //lingkaran merah taman
	glColor3f(0.6431372549019608,0.1686274509803922,0.0549019607843137);
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,0);
	lingkaranh(120,-30,-90,30,20,180);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,180);
	lingkaranh(120,-30,-90,30,20,0);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,270);
	lingkaranh(120,-30,-90,30,20,90);
	glEnd();
	glBegin(GL_POLYGON);
	lingkaranh(120,-39.9,-90,30,20,90);
	lingkaranh(120,-30,-90,30,20,270);
	glEnd();
    //rumput atas lingkar merah
	glColor3f(0.5137254901960784,1,0.2);
	glTranslatef(120,-45,-90);
    glutSolidSphere(25,10,10);
	glTranslatef(-120,45,40);
	//rumput kecil atasnya lagi
	glColor3f(0.5137254901960784,0.8,0.2);
	glTranslatef(105,-25,-40);
    glutSolidSphere(7,10,10);
	glTranslatef(-105,25,40);
	glTranslatef(115,-25,-25);
    glutSolidSphere(7,10,10);
	glTranslatef(-115,25,25);
	glTranslatef(130,-25,-40);
    glutSolidSphere(7,10,10);
	glTranslatef(-130,25,40);
	glTranslatef(120,-25,-50);
    glutSolidSphere(7,10,10);
	glTranslatef(-120,25,50);
	
    //tempat parkir
    glColor3f(0.1,0.1,0.1);
    //tanahnya
    kubus(90,-40,-320,640,50,1);
    kubus(610,-40,-200,120,120,1);
    //garis putih
    glColor3f(1,1,1);
    for(int i=0;i<=7;i++){
    	kubus(670,-39,-200-(15*i),2,10,1);
	}
	for(int i=0;i<=5;i++){
    	kubus(610+(10*i),-39,-240,5,2,1);
	}
	for(int i=0;i<=5;i++){
    	kubus(610+(10*i),-39,-280,5,2,1);
	}
	for(int i=0;i<=57;i++){
    	kubus(90+(10*i),-39,-320,5,2,1);
	}
	for(int i=0;i<=63;i++){
    	kubus(90+(10*i),-39,-365,5,2,1);
	}
	for(int i=0;i<=10;i++){
    	kubus(725,-39,-200-(15*i),2,10,1);
	}
    glColor3f(0.8,0.8,0.8);
    for(int i=0;i<=2;i++){
    	kubus(610,-39,-210-(40*i),2,20,2);
	}
    kubus(90,-39,-335,2,20,2);
    
    
    glColor3f(1,1,0);
    //tiang kuning
     kubus(612,-38.9,-200,2,2,15);
      kubus(725,-38.9,-200,2,2,15);
       kubus(725,-38.9,-365,2,2,15);
       kubus(95,-38.9,-366,2,2,15);
        kubus(95,-38.9,-323,2,2,15);


        
        
        //tipong
			float ax=413.4, ay=-39.9, az=-40,
			      bx=413, by=-39.9, bz=-100,
			      
			      ex=410, ey=-39.9, ez=-47,
			      fx=495, fy=-39.9, fz=-47,
			      
			      gx=493.4, gy=-39.9, gz=-40,
			      hx=493, hy=-39.9, hz=-100;
			      
			glBegin(GL_LINES);
			glColor3f(0.00,0.00,0.00);
			glVertex3f(ax,ay,az);
			glVertex3f(bx,by,bz);
			glVertex3f(ex,ey,ez);
			glVertex3f(fx,fy,fz);
			glVertex3f(gx,gy,gz);
			glVertex3f(hx,hy,hz);
			glEnd();
			
			glBegin(GL_POINTS);
			//pot ab ef
			cari1(ax,bx,az,bz);
			cari2(ex,fx,ez,fz);
			hasil();
			glColor3f(1.00,1.00,1.00);
			glVertex3f(x,ay+0.1,y);
			glEnd();
			
			glBegin(GL_POINTS);
			//pot gh ef
			cari1(gx,hx,gz,hz);
			cari2(ex,fx,ez,fz);
			hasil();
			glColor3f(1.00,1.00,1.00);
			glVertex3f(x,ay+0.1,y);
			glEnd();


	//matahari animasi
	glRotatef(rot, 0, 0, 200);
	glColor3f(1,1,0);
	glTranslatef(120,300,-500);
    glutSolidSphere(100,100,100);
	glTranslatef(-120,105,40);
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
	gluPerspective(50.0, lebar / tinggi, 5.0, 1000.0);
	glTranslatef(0.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}
