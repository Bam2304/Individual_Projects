/*
 *********************************************************
 * Name: Bamidele Adeyemo
 *
 *
 *
 * email: bbadeyem@syr.edu
 *
 * Assigment: Homework 2
 *
 * Environment: Xcode 16.2
 *
 * Submitted: February 19, 2025
 *
 * Interactions:    Press escape to quit
 *                  Press s, p, and c to select soup, pizza, and chicken parm
 *                  Press i, k, d, and e to toggle ice cream, cake pop, donut, and cookie
 *                  Press r to choose a random entree
 *                  Press 1 to rotate plate 22.5 degrees
 *                  Press 2 to toggle between circle and square plate
 *                  Press 3, 4, and 5 to switch plate color to blue, purple, and green
 **********************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

static int GUI, display; //2 different windows
static int mainChoice = 0; //choice of main
static bool iceCream = false; //toggles choice of desserts
static bool cookie = false;
static bool cake = false;
static bool donut = false;
static float rotation = 0.0; //for rotating the plate
static int isCircle = 1; //for choosing the plate shape
static int plateColorChoice = 1; // color
static float centerX = 10.0; //centerX for display plate
static float centerY = 10.0; //centerY for display plate


using namespace std;


void writeStrokeString(void *font, const char *string)
{
    const char *c;
    for (c = string; *c !='\0'; c++) glutStrokeCharacter(font,*c);
}

void topMenu(int id){
    if(id == 6){
        rotation += 22.5;
    }
    glutPostRedisplay();
}

void colorMenu(int id){
    if(id == 1){
        plateColorChoice = 2;
    } else if (id == 2){
        plateColorChoice = 1;
    } else{
        plateColorChoice = 3;
    }
    glutPostRedisplay();
}

void shapeMenu(int id){
    if(id == 4){
        isCircle = 0;
    } else {
        isCircle = 1;
    }
    glutPostRedisplay();
}

void setMenu(void){
    //setting sub-menu for color
    int subMenu1;
    subMenu1 = glutCreateMenu(colorMenu);
    glutAddMenuEntry("Purple", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    
    //submenu for shape
    int subMenu2;
    subMenu2 = glutCreateMenu(shapeMenu);
    glutAddMenuEntry("Square", 4);
    glutAddMenuEntry("Circle", 5);
    
    //top level menu creation
    glutCreateMenu(topMenu);
    glutAddSubMenu("Color", subMenu1);
    glutAddSubMenu("Shape", subMenu2);
    glutAddMenuEntry("Rotate", 6);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
}

void drawSideBox(void){
    //Main title
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(5.5, 8.0, 0.0);
    glScalef(0.0060, 0.0060, 0.0060);
    glLineWidth(3.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Desserts");
    glPopMatrix();
    
    //Background boxes
    float startingtopY = 7.4;
    float startingbottomY = 6.55;
    for(int x = 0; x < 4; x++){
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex3f(5.0, startingtopY, 0.0);
        glVertex3f(5.85, startingtopY, 0.0);
        glVertex3f(5.85, startingbottomY, 0.0);
        glVertex3f(5.0, startingbottomY, 0.0);
        glEnd();
        startingtopY -= 2.0;
        startingbottomY -= 2.0;
        
    }
    
    //dessert labels
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(6.35, 6.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Ice Cream");
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(6.35, 4.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Cake Pop");
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(6.35, 2.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Donut");
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(6.35, 0.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Cookie");
    glPopMatrix();
    
    //cross off selections
    if(iceCream){
        glColor3f(0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_LINES);
        glVertex3f(5.1, 7.3, 1.0);
        glVertex3f(5.75, 6.65, 1.0);
        glVertex3f(5.1, 6.65, 1.0);
        glVertex3f(5.75, 7.3, 1.0);
        glEnd();
        glDisable(GL_DEPTH_TEST);
    }
    if(cake){
        glColor3f(0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_LINES);
        glVertex3f(5.1, 5.3, 1.0);
        glVertex3f(5.75, 4.65, 1.0);
        glVertex3f(5.1, 4.65, 1.0);
        glVertex3f(5.75, 5.3, 1.0);
        glEnd();
        glDisable(GL_DEPTH_TEST);
    }
    if(donut){
        glColor3f(0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_LINES);
        glVertex3f(5.1, 3.3, 1.0);
        glVertex3f(5.75, 2.65, 1.0);
        glVertex3f(5.1, 2.65, 1.0);
        glVertex3f(5.75, 3.3, 1.0);
        glEnd();
        glDisable(GL_DEPTH_TEST);
    }
    if(cookie){
        glColor3f(0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_LINES);
        glVertex3f(5.1, 1.3, 1.0);
        glVertex3f(5.75, 0.65, 1.0);
        glVertex3f(5.1, 0.65, 1.0);
        glVertex3f(5.75, 1.3, 1.0);
        glEnd();
        glDisable(GL_DEPTH_TEST);
    }
    
}

void drawMainRadio(void){
    //Menu title
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(1.75, 9.0, 0.0);
    glScalef(0.0070, 0.0070, 0.0070);
    glLineWidth(3.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Today's Menu");
    glPopMatrix();
    
    //Main title
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.5, 8.0, 0.0);
    glScalef(0.0060, 0.0060, 0.0060);
    glLineWidth(3.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Entrees");
    glPopMatrix();
    
    //Background circles
    float centerX = 1.0;
    float centerY = 7.0;
    float r = 0.5;
    for(int i = 0; i < 4; i++){
        glBegin(GL_TRIANGLE_FAN);
          glColor3f(1.0, 1.0, 1.0);
          glVertex3f(centerX, centerY, 0.0);
          for(int l = 0; l<=50; l++){
              glVertex3f(r * cos( (float)(l)/50 * 2*PI ) +centerX,
                         r * sin( (float)(l)/50 * 2*PI )+centerY,
                         0.0);
          }
        centerY -= 2.0;
        glEnd();
    }
    
    //Food labels
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(2.0, 6.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Soup");
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.0, 4.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Pizza");
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.0, 2.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Chicken Parm");
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.0, 0.80, 0.0);
    glScalef(0.0030, 0.0030, 0.0030);
    glLineWidth(2.0);
    writeStrokeString(GLUT_STROKE_ROMAN, "Random?");
    glPopMatrix();
    
    //radio selections
    float r2 = 0.4;
    if(mainChoice == 1){
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_TRIANGLE_FAN);
          glColor3f(0.0, 0.0, 0.0);
          glVertex3f(1.0, 7.0, 0.0);
          for(int l = 0; l<=50; l++){
              glVertex3f(r2 * cos( (float)(l)/50 * 2*PI ) +1.0,
                         r2 * sin( (float)(l)/50 * 2*PI )+ 7.0,
                         1.0);
          }
        glEnd();
        glDisable(GL_DEPTH_TEST);
    } else if (mainChoice == 2){
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_TRIANGLE_FAN);
          glColor3f(0.0, 0.0, 0.0);
          glVertex3f(1.0, 5.0, 0.0);
          for(int l = 0; l<=50; l++){
              glVertex3f(r2 * cos( (float)(l)/50 * 2*PI ) +1.0,
                         r2 * sin( (float)(l)/50 * 2*PI )+ 5.0,
                         1.0);
          }
        glEnd();
        glDisable(GL_DEPTH_TEST);
    } else if (mainChoice == 3){
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_TRIANGLE_FAN);
          glColor3f(0.0, 0.0, 0.0);
          glVertex3f(1.0, 3.0, 0.0);
          for(int l = 0; l<=50; l++){
              glVertex3f(r2 * cos( (float)(l)/50 * 2*PI ) +1.0,
                         r2 * sin( (float)(l)/50 * 2*PI )+ 3.0,
                         1.0);
          }
        glEnd();
        glDisable(GL_DEPTH_TEST);
    }
    
    
}

void drawPlate(void){
    
    if(plateColorChoice == 1){
        glColor3f(0.118, 0.565, 1.0); //blue
    } else if (plateColorChoice == 2){
        glColor3f(0.541, 0.169, 0.886); //purple
    } else{
        glColor3f(0.235, 0.702, 0.443); //green
    }
    
    //depending on shape choice, draw plate
    if(isCircle == 0){
        glBegin(GL_QUADS);
        glVertex3f(1.5, 18.5, 0.0);
        glVertex3f(18.5, 18.5, 0.0);
        glVertex3f(18.5, 1.5, 0.0);
        glVertex3f(1.5, 1.5, 0.0);
        glEnd();
    } else{
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(centerX, centerY, 0.0);
        for(int x=0; x<=50; x++){
            glVertex3f(9.5 * cos( (float)(x)/50 * 2*PI ) + centerX,
                       9.5 * sin( (float)(x)/50 * 2*PI )+ centerY,
                       0.0);
        }
        glEnd();
    }
}

void drawSoup(void){
    //the bowl
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(centerX - 2.0, centerY, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(1.0 * cos( (float)(y)/30 * 2*PI ) + centerX - 2.0,
                   1.0 * sin( (float)(y)/30 * 2*PI )+ centerY,
                   0.0);
    }
    glEnd();
    //pot base
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(7.1, 10.0, 0.0);
    glVertex3f(7.1, 8.0, 0.0);
    glVertex3f(8.9, 8.0, 0.0);
    glVertex3f(8.9, 10.0, 0.0);
    glEnd();
    
    
    //handles
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(7.1, 9.0, 0.0);
    glVertex3f(6.6, 9.0, 0.0);
    glVertex3f(6.6, 8.7, 0.0);
    glVertex3f(7.1, 8.7, 0.0);
    glEnd();
    
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(8.9, 9.0, 0.0);
    glVertex3f(9.4, 9.0, 0.0);
    glVertex3f(9.4, 8.7, 0.0);
    glVertex3f(8.9, 8.7, 0.0);
    glEnd();
    
    //soup
    glColor3f(0.855, 0.647, 0.125);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(centerX - 2.0, centerY, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(0.95 * cos( (float)(y)/30 * 2*PI ) + centerX - 2.0,
                   0.95 * sin( (float)(y)/30 * 2*PI )+ centerY,
                   0.0);
    }
    glEnd();
    
    
}

void drawCParm(void){
    //plate
    glColor3f(0.753, 0.753, 0.753);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(12.0, 12.0, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(1.6 * cos( (float)(y)/30 * 2*PI ) + 12.0,
                   1.6 * sin( (float)(y)/30 * 2*PI )+ 12.0,
                   0.0);
    }
    glEnd();
    
    //chicken
    glColor3f(0.804, 0.522, 0.247);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(12.0, 12.0, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(1.2 * cos( (float)(y)/30 * 2*PI ) + 12.0,
                   1.2 * sin( (float)(y)/30 * 2*PI )+ 12.0,
                   0.0);
    }
    glEnd();
    
    //cheese on top
    glColor3f(1.0, 0.98, 0.98);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(12.0, 12.0, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(0.95 * cos( (float)(y)/30 * 2*PI ) + 12.0,
                   0.95 * sin( (float)(y)/30 * 2*PI )+ 12.0,
                   0.0);
    }
    glEnd();
    
}

void drawPizza(void){
    //bread
    glColor3f(0.93, 0.76, 0.49);
    glBegin(GL_TRIANGLES);
    glVertex3f(4.0, 15.0, 0.0);
    glVertex3f(5.0, 12.0, 0.0);
    glVertex3f(6.0, 15.0, 0.0);
    glEnd();
    
    //sauce
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(4.05, 14.8, 1.0);
    glVertex3f(5.0, 12.0, 1.0);
    glVertex3f(5.95, 14.8, 1.0);
    glEnd();
    
    //cheese
    glColor3f(0.98, 0.94, 0.78);
    glBegin(GL_TRIANGLES);
    glVertex3f(4.17, 14.5, 2.0);
    glVertex3f(5.0, 12.0, 2.0);
    glVertex3f(5.83, 14.5, 2.0);
    glEnd();
    
    glDisable(GL_DEPTH_TEST);
    
}

void drawCookie(void){
    //cookie
    glColor3f(0.85, 0.65, 0.40);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(10.0, 7.0, 0.0);
    for(int y=0; y<=30; y++){
        glVertex3f(1.0 * cos( (float)(y)/30 * 2*PI ) + 10.0,
                   1.0 * sin( (float)(y)/30 * 2*PI )+ 7.0,
                   0.0);
    }
    glEnd();
    //choc chips
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.38, 0.23, 0.14);
    glBegin(GL_TRIANGLES);
    glVertex3f(9.5, 7.5, 1.0);
    glVertex3f(9.25, 7.25, 1.0);
    glVertex3f(9.75, 7.25, 1.0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3f(10.5, 7.5, 1.0);
    glVertex3f(10.25, 7.25, 1.0);
    glVertex3f(10.75, 7.25, 1.0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3f(10.0, 6.5, 1.0);
    glVertex3f(9.75, 6.3, 1.0);
    glVertex3f(10.25, 6.3, 1.0);
    glEnd();
    glDisable(GL_DEPTH_TEST);
    
    
}

void drawIceCream(void){
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.5);
    glPushMatrix();
    glTranslatef(14.75, 9.0, 1.0);
    //brown chocolate cone
    glColor3f(0.824, 0.412, 0.118);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glutWireCone(1.5, 3, 10, 10);
    glPopMatrix();
    
    //mint ice cream
    glColor3f(0.961, 1.000, 0.980);
    glPushMatrix();
    glTranslatef(0, 1.1, -1.0);
    glutWireSphere(1.5, 20, 20);
    glPopMatrix();
    
    
    glPopMatrix();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}

void drawDonut(void){
    glLineWidth(2.5);
    glColor3f(0.96, 0.80, 0.56);
    glPushMatrix();
    glTranslatef(9.0, 15.0, 0.0);
    
    glRotated(45, 1, 0, 0);
    glutWireTorus(0.5, 1.5, 30, 30);
    glPopMatrix();
    
    glPopMatrix();
    glLineWidth(1.0);
    
}

void drawCakePop(void){
    glColor3f(0.647, 0.165, 0.165);
    glLineWidth(2.5);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glTranslatef(4.8, 9.0, 1.0);
    glutWireSphere(1.5, 20, 20);
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(4.8, 9.0, 0.0);
    glVertex3f(4.8, 4.0, 0.0);
    glEnd();
    glDisable(GL_DEPTH_TEST);
    glLineWidth(1.0);
    
}

void mouseControl(int button, int state, int x, int y)
{
    float trueY = 10 - (y * 0.02); //multiply by 0.02 to scale from pixels to ortho
    float trueX = x * 0.02;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(trueX >= 0.5 && trueX <= 1.5 && trueY >= 6.5 && trueY <= 7.5){
            mainChoice = 1;
        } else if(trueX >= 0.5 && trueX <= 1.5 && trueY >= 4.5 && trueY <= 5.5){
            mainChoice = 2;
        } else if(trueX >= 0.5 && trueX <=1.5 && trueY >= 2.5 && trueY <=3.5){
            mainChoice = 3;
        } else if(trueX >= 0.5 && trueX <= 1.5 && trueY >= 0.5 && trueY <=1.5){
            mainChoice =  1 + (std::rand() % 3); //random entree
        }
        
        if(trueX >= 5.0 && trueX <= 5.85 && trueY <= 7.4 && trueY >= 6.55){
            iceCream = !iceCream;
        } else if(trueX >= 5.0 && trueX <= 5.85 && trueY <= 5.4 && trueY >= 4.55){
            cake = !cake;
        } else if(trueX >= 5.0 && trueX <= 5.85 && trueY <= 3.4 && trueY >= 2.55){
            donut = !donut;
        } else if(trueX >= 5.0 && trueX <= 5.85 && trueY <= 1.4 && trueY >= 0.55){
            cookie = !cookie;
        }
        
        
        glutPostRedisplay();
        glutSetWindow(display);
        glutPostRedisplay();
        glutSetWindow(GUI);
    }

      

   
   glutPostRedisplay();
}

// Drawing routine for GUI
void drawGUIScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawMainRadio();
    drawSideBox();
    glFlush();
}

// drawing routine for food display
void drawDisplayScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
    //rotate based on menu choice
    glPushMatrix();
    glTranslatef(10.0, 10.0, 0.0);
    glRotated(rotation, 0, 0, 1);
    glTranslatef(-10.0, -10.0, 0.0);
    drawPlate();
    glPopMatrix();
    
    if(mainChoice == 1){
        drawSoup();
    } else if (mainChoice == 2){
        drawPizza();
    } else if (mainChoice == 3){
        drawCParm();
    }
    
    if(cookie){
        drawCookie();
    }
    if(iceCream){
        drawIceCream();
    }
    if(donut){
        drawDonut();
    }
    if(cake){
        drawCakePop();
    }
    
   glFlush();
}

// Initialization for GUI
void setupGUI(void)
{
   glClearColor(0.529, 0.808, 0.980, 0.0);  
}
//Initialization for food display
void setupDisplay(void)
{
   glClearColor(1.0, 0.75, 0.79, 0.0);
}

// reshape routine for GUI
void resizeGUI(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 10.0, 0.0, 10.0, -2.0, 2.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
//reshape for food display
void resizeDisplay(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 20.0, 0.0, 20.0, -5.0, 5.0);

   glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine for both windows.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
       case 27:
         exit(0);
         break;
       case '1':
           rotation += 22.5;
           glutSetWindow(display);
           glutPostRedisplay();
           break;
       case '2':
           if(isCircle == 0){
               isCircle = 1;
           } else{
               isCircle = 0;
           }
           glutSetWindow(display);
           glutPostRedisplay();
           break;
       case '3':
           plateColorChoice = 1;
           glutSetWindow(display);
           glutPostRedisplay();
           break;
       case '4':
           plateColorChoice = 2;
           glutSetWindow(display);
           glutPostRedisplay();
           break;
       case '5':
           plateColorChoice = 3;
           glutSetWindow(display);
           glutPostRedisplay();
           break;
       case 's':
           mainChoice = 1;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'p':
           mainChoice = 2;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'c':
           mainChoice = 3;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'r':
           mainChoice = 1 + (std::rand() % 3);
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'i':
           iceCream = !iceCream;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'k':
           cake = !cake;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'd':
           donut = !donut;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
       case 'e':
           cookie = !cookie;
           glutSetWindow(GUI);
           glutPostRedisplay();
           glutSetWindow(display);
           glutPostRedisplay();
           glutSetWindow(GUI);
           break;
      default:
         break;
   }
}

//Instructions for interacting
void printInstructions(void){
    cout << "Instructions:" << endl;
    cout << "Press s, p, and c to choose between soup, pizza, and chicken parm, respectively" << endl;
    cout << "Additionally, if you can't choose an entree, press r to randomly choose" << endl;
    cout << "For desserts, press i, k, d, and e to to select/deselect ice cream, cake pop, donut, and cookie, respectively" << endl;
    cout << "Press 1 to rotate plate 22.5 degrees" << endl;
    cout << "Press 2 to toggle between circle and square plate" << endl;
    cout << "Press 3, 4, and 5 to change plate color to blue, purple, and green, respectively" << endl;
    cout << "Press escape to quit" << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    printInstructions();
    //gui window size
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
    //GUI window
   GUI = glutCreateWindow("Menu");
   setupGUI();
   glutDisplayFunc(drawGUIScene);
   glutReshapeFunc(resizeGUI);
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl);
    
    //food display size
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(650, 100);
    //food display window
    display = glutCreateWindow("FoodDisplay");
    setupDisplay();
    glutDisplayFunc(drawDisplayScene);
    glutReshapeFunc(resizeDisplay);
    glutKeyboardFunc(keyInput);
    setMenu();
    
   glutMainLoop();

   return 0;  
}

