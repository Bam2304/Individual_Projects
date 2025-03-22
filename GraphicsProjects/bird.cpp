/*
 *********************************************************
 * Name: Bamidele Adeyemo
 *
 * Call me: Bam
 *
 * email: bbadeyem@syr.edu
 *
 * Assigment: Homework 3
 *
 * Environment: Xcode 16.2
 *
 * Submitted: March 19, 2025
 *
 * Interactions:   -To make the bird fly, either press l or click on it
 *                 -The up and down arrows will speed up/slow down the bird's flight
 *                 -Pressing w will toggle the wings flapping
 *                 -The left and right keys will slow down/speed up wings
 *                 -Press 1,2,3,4 to view scene from north,east,south,west, respectively
 *                 -Click each fruit to drop it
 *                 -Alternatively, press a and b to drop left red apple and left green apple,                    respectively
                   -And press c and d to drop right red apple and right green apple,respectively
                   -Pressing r will reset everything to default
                   -Press esc to quit
 **********************************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
static int t=0;
static float startX, startY, startZ;//starting point for this leg of trip
static float endX, endY, endZ; //ending point for this leg of trip
//locations for bird's flight, coordinates are above the center of trees
static float tree1X = 2.8;
static float tree1Y = 4.95;
static float tree1Z = -0.4;
static float tree2X = 15.5;
static float tree2Y = 6.75;
static float tree2Z = -0.4;
static float tree3X = 15.5;
static float tree3Y = 6.75;
static float tree3Z = -11.4;
static float tree4X = 0.5;
static float tree4Y = 6.75;
static float tree4Z = -11.4;
//
int xClick, yClick;
int view = 1; //controls the view
static float angle = -90; //so that bird can always face direction of travel
static float Vx,Vy,Vz; //vector from tree X to tree Y
static float Mx=0,My=0,Mz=0; //partial vector in direction of V
static int leg = 1; //leg for animation
static bool animate = false;  //animating the bird
static bool animateWings = false; //for toggling wing flapping
static float wingAngle = 0.0; //for wing animation
static bool wingDir = true; //true = up, down = false
static float wingAngChng = 1.0; //speed of flapping the wings
//static int headAng = 180;
static float animateSpeed = 100; //speed of bird
static int dropped = 0; //controls if red apple 1 is dropped or not
static int dropped2 = 0; //controls if green apple 1 is dropped or not
static int dropped3 = 0; //controls if red apple 2 is dropped or not
static int dropped4 = 0; //controls if green apple 1 is dropped or not
static bool select = false;
static bool birdSelect = false;
static bool oneRound = false;
GLUquadric* quad; //for the cylinder birdhouse

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(90, 1, 1, 27);
    
    glMatrixMode(GL_MODELVIEW);
   
}


// Drawing routine.
void draw(void)
{
    //Clear buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set Projection
    setProjection();
    
    //Clear Modeview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Set View
   
    if(view == 1){
        //from the north
        gluLookAt(8, 4, 10,
                  8,5,-6,
                  0,1,0);
        //glutPostRedisplay();
    } else if(view == 3){
        
        //from the south
        gluLookAt(8,4,-22,
                    8,5,-6,
                    0,1,0);
        //glutPostRedisplay();
    } else if(view == 2){
        //from east
            gluLookAt(25, 4, -6,
                      8,5,-6,
                      0,1,0);
        //glutPostRedisplay();
    } else if(view == 4){
        //from west
            gluLookAt(-10,4,-6,
                      8, 5, -6,
                      0, 1, 0);
        //glutPostRedisplay();
        
    }
  
    
    glEnable(GL_DEPTH_TEST);
    
    
    //green grass
    glColor3f(.7,1.0,.7);
    glPushMatrix();
    glTranslated(8,-.5,-6.01);
    glScaled(16, 1, 12);
    glutSolidCube(1);
    glPopMatrix();
    
    //tree 1
    glColor3f(0.647, 0.165, 0.165);
    glPushMatrix();
    glTranslated(0.5, 2,-0.5);
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.133, 0.545, 0.133);
    glPushMatrix();
    //glScaled(0.5, 0.5, 0.5);
    glTranslated(0.5, 4.75, -0.4);
    glutSolidSphere(1.5, 20, 20);
    glPopMatrix();
    
        //red apple
        glColor3ub(220, 20, 60);
        glPushMatrix();
        if(!dropped){
            glTranslated(0.70, 4.55, 0.88);
        } else{
            glTranslated(2.70, 0.55, 0.10);
        }
        glutSolidSphere(0.3, 20, 20);
        glPopMatrix();
    
        //green apple
        glColor3ub(50, 205, 50);
        glPushMatrix();
        if(!dropped2){
            glTranslated(1.90, 4.85, 0.10);
        } else {
            glTranslated(3.00, 0.55, -0.70);
        }
        glutSolidSphere(0.3, 20, 20);
        glPopMatrix();
    
    //branch and nest
    glColor3f(0.647, 0.165, 0.165);
    glPushMatrix();
    glTranslated(2.0, 4.20, -0.4);
    glScaled(3.5, 0.25, 1.2);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.502, 0.502, 0.0);
    glPushMatrix();
    glTranslated(2.8, 4.45, -0.4);
    glRotated(90, 1, 0, 0);
    glScaled(1.2, 1, 1.1);
    glutSolidTorus(0.2, 0.4, 20, 20);
    glPopMatrix();
    //tree 2
    glColor3f(0.647, 0.165, 0.165);
    glPushMatrix();
    glTranslated(15.5, 2,-0.5);
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.133, 0.545, 0.133);
    glPushMatrix();
    //glScaled(0.5, 0.5, 0.5);
    glTranslated(15.5, 4.75, -0.4);
    glutSolidSphere(1.5, 20, 20);
    glPopMatrix();
    
        //red apple
        glColor3ub(255, 0, 0);
        glPushMatrix();
        if(!dropped3){
            glTranslated(15.30, 4.55, 0.9);
        } else{
            glTranslated(13.70, 0.55, -0.2);
        }
        glutSolidSphere(0.3, 20, 20);
        glPopMatrix();

        //green apple
        glColor3ub(144, 238, 144);
        glPushMatrix();
        if(!dropped4){
            glTranslated(14.10, 4.85, 0.1);
        } else{
            glTranslated(13.30, 0.55, -0.65);
        }
        glutSolidSphere(0.3, 20, 20);
        glPopMatrix();
    
    //tree 3
    glColor3f(0.647, 0.165, 0.165);
    glPushMatrix();
    glTranslated(15.5, 2,-11.5);
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.133, 0.545, 0.133);
    glPushMatrix();
    //glScaled(0.5, 0.5, 0.5);
    glTranslated(15.5, 4.75, -11.4);
    glutSolidSphere(1.5, 20, 20);
    glPopMatrix();
    
    //tree 4
    glColor3f(0.647, 0.165, 0.165);
    glPushMatrix();
    glTranslated(0.5, 2,-11.5);
    glScaled(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.133, 0.545, 0.133);
    glPushMatrix();
    //glScaled(0.5, 0.5, 0.5);
    glTranslated(0.5, 4.75, -11.4);
    glutSolidSphere(1.5, 20, 20);
    glPopMatrix();
    
    //bird
    glColor3ub(51, 102, 204);
    glPushMatrix();
        glTranslated(Mx, My, Mz);
        glTranslated(startX,startY,startZ);
        glRotatef(angle, 0, 1, 0);
            //body
            glPushMatrix();
            glScaled(1, 1, 2);
            glutSolidSphere(0.37, 20, 20);
            glPopMatrix();
            //right wing
            glPushMatrix();
            glTranslated(0.6, 0, 0);
            if(leg == 2 || leg == 4){
                glRotated(-wingAngle, 0, 0, 1);
            } else if (leg == 1 || leg == 3){
                glRotated(-wingAngle, 1, 0, 0);
            }
            glScaled(1, 0.25, 1);
            glutSolidCube(0.5);
            glPopMatrix();
            //left wing
            glPushMatrix();
            glTranslated(-0.6, 0, 0);
            if(leg == 2 || leg == 4){
                glRotated(wingAngle, 0, 0, 1);
            } else if (leg == 1 || leg == 3){
                glRotated(wingAngle, 1, 0, 0);
            }
            glScaled(1, 0.25, 1);
            glutSolidCube(0.5);
            glPopMatrix();
    
    glPopMatrix();
    
    //birdhouse
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(8, 0, -6);
    glRotated(-90, 1, 0, 0);
    gluCylinder(quad, 0.7, 0.7, 2.0, 20, 20);
    glPopMatrix();
    
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(8, 2, -6);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.0, 2, 20, 20);
    glPopMatrix();
    
   //glutSwapBuffers();
}



void idle(void){
    if(animateWings){
        if(!wingDir && wingAngle >= 36){ //if reached maximum angle, switch direction
            wingDir = !wingDir;
        } else if (wingDir && wingAngle<= -36){
            wingDir = !wingDir;
        }
        
        if(!wingDir){ //if wings going down
            wingAngle += wingAngChng;
        } else if (wingDir){ //if wings going up
            wingAngle -= wingAngChng;
        }
        
        glutPostRedisplay();
        
    }
}



void makeDirectionVector(float x, float y, float z, float x2, float y2, float z2){
    startX = x;
    startY = y;
    startZ = z;
    endX = x2;
    endY = y2;
    endZ = z2;
    Vx = endX - startX;
    Vy = endY - startY;
    Vz = endZ - startZ;
}

void goForward(void){
    
    //time checking for the new leg
    if(t == 10 && leg == 1){
        t = 0;
        leg = 2;
        makeDirectionVector(tree2X, tree2Y, tree2Z, tree3X, tree3Y, tree3Z);
        angle += 90;
        //headAng += 90;
    } else if (t == 10 && leg == 2){
        t = 0;
        leg = 3;
        makeDirectionVector(tree3X, tree3Y, tree3Z, tree4X, tree4Y, tree4Z);
        angle += 90;
        //headAng += 90;
    } else if (t == 10 && leg == 3){
        t = 0;
        leg = 4;
        makeDirectionVector(tree4X, tree4Y, tree4Z, tree1X, tree1Y, tree1Z);
        angle += 90;
        //headAng += 90;
    } else if (t == 10 && leg == 4){
        t = 0;
        leg = 1;
        makeDirectionVector(tree1X, tree1Y, tree1Z, tree2X, tree2Y, tree2Z);
        angle += 90;
        //headAng += 90;
        if(oneRound){
            animate = false;
            Mx = tree1X;
            My = tree1Y;
            Mz = tree1Z;
        }
    }
//    if(oneRound && leg == 4 && t == 8){
//        animate = false;
//    }
    //partial vector
    //if(animate){
        //t++;
        Mx=(float)t/10.0*Vx;
        My=(float)t/10.0*Vy;
        Mz=(float)t/10.0*Vz;
        t++;
    //}
    glutPostRedisplay();
    
}

void animateBird(int value){
    if(animate){
        goForward();
    }
    glutTimerFunc(animateSpeed, animateBird, 1);
}

void identifyObject(int x, int y){
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    
    //dropped = 0;
    //dropped2 = 0;
    //dropped3 = 0;
    //dropped4 = 0;
    //birdSelect = 0;
    
    if ((int)pixel[0]==220 && (int)pixel[1]==20 && (int)pixel[2]==60){ //
        dropped = 1; //red apple 1 has fallen
    }
    else if ((int)pixel[0]==50 && (int)pixel[1]==205 && (int)pixel[2]==50){
        dropped2 = 1; //green appple 1 has fallen
    }
    else if ((int)pixel[0]==255 && (int)pixel[1]==0 && (int)pixel[2]==0){
        dropped3 = 1;
    }
    else if ((int)pixel[0]==144 && (int)pixel[1]==238 && (int)pixel[2]==144){
        dropped4 = 1;
    }
    else if ((int)pixel[0]==51 && (int)pixel[1]==102 && (int)pixel[2]==204){
        animate = true;
        oneRound = true;
        //glutTimerFunc(animateSpeed, animateBird, 1);
    }
    select=false;
    glutPostRedisplay();
}

void drawScene(void){
        if(select){
            draw();
            identifyObject(xClick, yClick);
            
        }
        else{
            draw();
            glutSwapBuffers();
        }
}


void setup(void) 
{
   glClearColor(0.53, 0.81, 0.98, 1.0);
   makeDirectionVector(tree1X, tree1Y, tree1Z, tree2X, tree2Y, tree2Z);
    quad = gluNewQuadric();
}


void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
    setProjection();
}

// Keyboard input processing routines
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
           
       case '1':
           view = 1;
           glutPostRedisplay();
           break;
           
       case '2':
           view = 2;
           glutPostRedisplay();
           break;
           
       case '3':
           view = 3;
           glutPostRedisplay();
           break;
           
       case '4':
           view = 4;
           glutPostRedisplay();
           break;
           
       case 'w':
           animateWings = !animateWings;
           break;
          
       case 'l':
           animate = true;
           oneRound = true;
           break;
           
       case 'a':
           dropped = 1;
           break;
           
       case 'b':
           dropped2 = 1;
           break;
           
       case 'c':
           dropped3 = 1;
           break;
           
       case 'd':
           dropped4 = 1;
           break;
           
       case 'r':
           view = 1;
           animate = false;
           t = 0;
           Mx = 0; My = 0; Mz = 0;
           leg = 1;
           makeDirectionVector(tree1X, tree1Y, tree1Z, tree2X, tree2Y, tree2Z);
           angle = -90.0;
           animateWings = false;
           animateSpeed = 100;
           wingAngChng = 1.0;
           wingDir = true;
           
           dropped = 0;
           dropped2 = 0;
           dropped3 = 0;
           dropped4 = 0;
           glutPostRedisplay();
           break;
           
      default:
         break;
   }
}

void specialKeyInput(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            if(wingAngChng <= 1){
                wingAngChng = 1;
            } else{
                wingAngChng -= 1;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(wingAngChng >= 4){
                wingAngChng = 4;
            } else{
                wingAngChng += 1;
            }
            break;
        case GLUT_KEY_UP:
            if(animateSpeed <= 40){
                animateSpeed = 40;
            } else{
                animateSpeed -= 10;
            }
            break;
        case GLUT_KEY_DOWN:
            if(animateSpeed >= 200){
                animateSpeed = 200;
            } else{
                animateSpeed += 10;
            }
            break;
            
            glutTimerFunc(animateSpeed, animateBird, 1);
            glutPostRedisplay();
    }
}

void mouseControl(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN && button == GLUT_LEFT)
    {   select=true;
        xClick=x;
        yClick=600-y; //for mouse vs window coordinates
        glutPostRedisplay();
        
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void){
    cout << "Interaction:" << endl;
    cout << "To make the bird fly, either press l or click on it" << endl;
    cout << "The up and down arrows will speed up/slow down the bird's flight" << endl;
    cout << "Pressing w will toggle the wings flapping" << endl;
    cout << "The left and right keys will slow down/speed up wings" << endl;
    cout << "Press 1,2,3,4 to view scene from north,east,south,west, respectively" << endl;
    cout << "Click each fruit to drop it" << endl;
    cout << "Alternatively, press a and b to drop left red apple and left green apple, respectively" << endl;
    cout << "And press c and d to drop right red apple and right green apple, respectively" << endl;
    cout << "Pressing r will reset everything to default" << endl;
    cout << "Press esc to quit" << endl;
    
}

// Main
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Bird Flying");
   setup();
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutMouseFunc(mouseControl);
   glutTimerFunc(100, animateBird, 1);//to start the animation when necessary
   glutIdleFunc(idle);
   printInteraction();
   glutMainLoop(); 

   return 0;  
}

