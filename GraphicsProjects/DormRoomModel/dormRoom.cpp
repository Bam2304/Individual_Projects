/********************************************
 Name: Bamidele Adeyemo
 
 Call me Bam
 
 Email: bbadeyem@syr.edu
 
 Assignment: Final Project
 
 Environment: Xcode 16.2
 
 Submitted: April 27, 2025
 
 Interactions:
    -Press the arrow keys to move around the scene
    -Press d or click door to open or close it
    -Press l to toggle room light on/off
    -Press r to change avatar color
    -Click the lid of minicooler to open/close it
    -Press esc to quit
 **********************************************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <random>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#  include <GL/glext.h>
#endif

#define PI 3.14159

using namespace std;

static int t=0;
static bool animDoor = false;
static bool animLid = false;
static bool lidOpen = false;
static bool select = false;
int xClick, yClick;
static bool lightOn = true; //light switch
static bool open = false;
static float doorOffset = 0.0;
static float meX=0;
static float meY=50;
static float meZ=135;
static float angle=0;  //angle facing
static float stepsize=3.0;  //step size
static float turnsize=5.0; //degrees to turn
float lidOffset = 0.0f;         // animated for the sliding lid
static unsigned int texture[5]; // array of textures
std::random_device rd; //object seed for generating random nums
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distr(0.0f, 1.0f); // btwn 0 and 1
float r, b, g = 0.5; // for ball color


void setMaterial(float r, float g, float b) {
    float ambient[] = {r , g , b , 1.0f};
    float diffuse[] = {r, g, b, 1.0f};
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float shininess = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


struct BitMapFile
{
   int sizeX;
   int sizeY;
   unsigned char *data;
};


BitMapFile *getBMPData(string filename)
{
   BitMapFile *bmp = new BitMapFile;
   unsigned int size, offset, headerSize;
  
   // Read input file name.
   ifstream infile(filename.c_str(), ios::binary);
 
   // Get the starting point of the image data.
   infile.seekg(10);
   infile.read((char *) &offset, 4);
   
   // Get the header size of the bitmap.
   infile.read((char *) &headerSize,4);

   // Get width and height values in the bitmap header.
   infile.seekg(18);
   infile.read( (char *) &bmp->sizeX, 4);
   infile.read( (char *) &bmp->sizeY, 4);

   // Allocate buffer for the image.
   size = bmp->sizeX * bmp->sizeY * 24;
   bmp->data = new unsigned char[size];

   // Read bitmap data.
   infile.seekg(offset);
   infile.read((char *) bmp->data , size);
   
   // Reverse color from bgr to rgb.
   int temp;
   for (int i = 0; i < size; i += 3)
   {
      temp = bmp->data[i];
      bmp->data[i] = bmp->data[i+2];
      bmp->data[i+2] = temp;
   }

   return bmp;
}


void loadExternalTextures()
{
   // Local storage for bmp image data.
   BitMapFile *image[5];
   
   
   // Load the first texture.
   image[0] = getBMPData("bbadeyemTEXTURES/carpet.bmp");

   // Activate texture index texture[0].
   glBindTexture(GL_TEXTURE_2D, texture[0]);

   // Set texture parameters for wrapping.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   // Set texture parameters for filtering.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Specify an image as the texture to be bound with the currently active texture index.
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
    
    // Load the second texture.
    image[1] = getBMPData("bbadeyemTEXTURES/aya.bmp");

    // Activate texture index texture[1].
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
    
    // Load the third texture.
    image[2] = getBMPData("bbadeyemTEXTURES/wall.bmp");

    // Activate texture index texture[2].
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[2]->sizeX, image[2]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);
    
    // Load the fourth texture.
    image[3] = getBMPData("bbadeyemTEXTURES/chelsea.bmp");

    // Activate texture index texture[3].
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[3]->sizeX, image[3]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);
    
    
}


void moveDoor(void){
    if (!open) {
            if (doorOffset < 35.0) {
                doorOffset += 1.0;
            } else {
                open = true; // Mark as open once fully open
                animDoor = false;
            }
        } else {
            if (doorOffset > 0.0) {
                doorOffset -= 1.0;
            } else {
                open = false; // Mark as closed once back to original position
                animDoor = false;
            }
        }

        glutPostRedisplay();
}

void moveLid(void){
    if (!lidOpen) {
            if (lidOffset < 18.0) {
                lidOffset += 1.0;
            } else {
                lidOpen = true;
                animLid = false;
            }
        } else {
            if (lidOffset > 0.0) {
                lidOffset -= 1.0;
            } else {
                lidOpen = false;
                animLid = false;
            }
        }

        glutPostRedisplay();
}


// Drawing routine.
void drawHouse(void){
    
    float width = 200.0f;
    float heightNDepth = 100.0f; //(height)
    float dep = 170; //(depth)
    float doorWidth = 40.0f;
    float doorHeight = 60.0f;
    float doorX = doorWidth / 2;
    //window variables
    float windowWidth = 30.0f;
    float windowHeight = 40.0f;
    float centerX = 0;
    float centerY = heightNDepth / 2;
    float left = -windowWidth / 2;
    float right =  windowWidth / 2;
    float bottom = centerY - windowHeight / 2;
    float top = centerY + windowHeight / 2;
    float z = -dep / 2;
    
    setMaterial(0.6, 0.6, 0.6); //reset to not mess up textures
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    glBegin(GL_QUADS);
        
        // Floor
        glNormal3f(0, 1, 0); // Normal pointing up with carpet texture
        glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, 0, -dep / 2);
        glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, 0, -dep / 2);
        glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, 0, dep / 2);
        glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, 0, dep / 2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
        setMaterial(1, 0.937, 0.835);
        // Ceiling
        glNormal3f(0, -1, 0); // Normal pointing down
        glVertex3f(-width / 2, heightNDepth, -dep / 2);
        glVertex3f(width / 2, heightNDepth, -dep / 2);
        glVertex3f(width / 2, heightNDepth, dep / 2);
        glVertex3f(-width / 2, heightNDepth, dep / 2);
    glEnd();
    
    //top part of hallway
    setMaterial(0.89, 0.87, 0.70);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(width / 2, heightNDepth, dep / 2);
    glVertex3f(-width / 2, heightNDepth, dep / 2);
    glVertex3f(-width / 2, heightNDepth, dep / 2 + 100);
    glVertex3f(width / 2, heightNDepth, dep / 2 + 100);
    
    //back part
    glNormal3f(0, 0, -1);
    glVertex3f(-width / 2, heightNDepth, dep / 2 + 100);
    glVertex3f(width / 2, heightNDepth, dep / 2 + 100);
    glVertex3f(width / 2, 0, dep / 2 + 100);
    glVertex3f(-width / 2, 0, dep / 2 + 100);
    glEnd();
    
    //hallway floor
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, 0, dep / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, 0, dep / 2);
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, 0, dep / 2 + 100);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, 0, dep / 2 + 100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //left & right sides respectively
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(-width / 2, 0, dep / 2);
    glVertex3f(-width / 2, heightNDepth, dep / 2);
    glVertex3f(-width / 2, heightNDepth, dep / 2 + 100);
    glVertex3f(-width / 2, 0, dep / 2 + 100);
    
    glNormal3f(-1, 0, 0);
    glVertex3f(width / 2, 0, dep / 2);
    glVertex3f(width / 2, heightNDepth, dep / 2);
    glVertex3f(width / 2, heightNDepth, dep / 2 + 100);
    glVertex3f(width / 2, 0, dep / 2 + 100);

    glEnd();
    
    
    
    setMaterial(1.0, 0.937, 0.835);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    // Back Wall
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    // Left piece
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, 0, z);
    glTexCoord2f(1.0, 0.0); glVertex3f(left, 0, z);
    glTexCoord2f(1.0, 1.0); glVertex3f(left, heightNDepth, z);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, heightNDepth, z);

    // Right piece
    glTexCoord2f(0.0, 0.0); glVertex3f(right, 0, z);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, 0, z);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, heightNDepth, z);
    glTexCoord2f(0.0, 1.0); glVertex3f(right, heightNDepth, z);

    // Top piece
    glTexCoord2f(0.0, 0.0); glVertex3f(left, top, z);
    glTexCoord2f(1.0, 0.0); glVertex3f(right, top, z);
    glTexCoord2f(1.0, 1.0); glVertex3f(right, heightNDepth, z);
    glTexCoord2f(0.0, 1.0); glVertex3f(left, heightNDepth, z);

    // Bottom piece
    glTexCoord2f(0.0, 0.0); glVertex3f(left, 0, z);
    glTexCoord2f(1.0, 0.0); glVertex3f(right, 0, z);
    glTexCoord2f(1.0, 1.0); glVertex3f(right, bottom, z);
    glTexCoord2f(0.0, 1.0); glVertex3f(left, bottom, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    
    //setMaterial(1.0, 0.937, 0.835);
    
    glBegin(GL_QUADS);
        //front wall
        // Left Side of the Wall
        glNormal3f(0, 0, -1);
        glVertex3f(-width / 2, 0, dep / 2);
        glVertex3f(-doorX, 0, dep / 2);
        glVertex3f(-doorX, heightNDepth, dep / 2);
        glVertex3f(-width / 2, heightNDepth, dep / 2);
    

        // Right Side of the Wall
        glNormal3f(0, 0, -1);
        glVertex3f(doorX, 0, dep / 2);
        glVertex3f(width / 2, 0, dep / 2);
        glVertex3f(width / 2, heightNDepth, dep / 2);
        glVertex3f(doorX, heightNDepth, dep / 2);

        // Top of the Wall (Above the Door)
        glNormal3f(0, 0, -1);
        glVertex3f(-doorX, doorHeight, dep / 2);
        glVertex3f(doorX, doorHeight, dep / 2);
        glVertex3f(doorX, heightNDepth, dep / 2);
        glVertex3f(-doorX, heightNDepth, dep / 2);

    glEnd();
    
    //poster 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2 + 0.1, 90, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2 + 0.1, 50, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-width / 2 + 0.1, 50, -45);
    glTexCoord2f(1.0, 1.0); glVertex3f(-width / 2 + 0.1, 90, -45);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    //poster 2 credit: https://www.theguardian.com/football/live/2021/may/29/manchester-city-v-chelsea-champions-league-final-live
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    
    glNormal3f(-1, 0, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2 - 0.1, 90, 10);
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2 - 0.1, 50, 10);
    glTexCoord2f(0.0, 0.0); glVertex3f(width / 2 - 0.1, 50, -35);
    glTexCoord2f(0.0, 1.0); glVertex3f(width / 2 - 0.1, 90, -35);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    
    glBegin(GL_QUADS);
        //setMaterial(1.0, 0.937, 0.835);
        // Left Wall
    glNormal3f(1, 0, 0); // Normal pointing right
    glTexCoord2f(1.0, 0.0); glVertex3f(-width / 2, 0, -dep / 2);
    glTexCoord2f(0.0, 0.0); glVertex3f(-width / 2, 0, dep / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(-width / 2, heightNDepth, dep / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(-width / 2, heightNDepth, -dep / 2);
    glEnd();
    glBegin(GL_QUADS);
        //setMaterial(1.0, 0.937, 0.835);
        // Right Wall
    glNormal3f(-1, 0, 0); // Normal pointing left
    glTexCoord2f(1.0, 0.0); glVertex3f(width / 2, 0, -dep / 2);
    glTexCoord2f(0.0, 0.0); glVertex3f(width / 2, 0, dep / 2);
    glTexCoord2f(0.0, 1.0); glVertex3f(width / 2, heightNDepth, dep / 2);
    glTexCoord2f(1.0, 1.0); glVertex3f(width / 2, heightNDepth, -dep / 2);

    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    //window with blending to see through
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    float windowColor[] = {0.82, 0.82, 0.82, 0.25}; //to make see through
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, windowColor);
    
    // Draw the window
    glBegin(GL_QUADS);
    glVertex3f(left, bottom, z);
    glVertex3f(right, bottom, z);
    glVertex3f(right, top, z);
    glVertex3f(left, top, z);
    glEnd();
    
    glDisable(GL_BLEND);
    
    glDisable(GL_LIGHTING);// to draw line
    glBegin(GL_LINE_LOOP); //outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5.0);
    glVertex3f(left, bottom, z + 0.01);
    glVertex3f(right, bottom, z + 0.01);
    glVertex3f(right, top, z + 0.01);
    glVertex3f(left, top, z + 0.01);
    glLineWidth(1.0);
    glEnd();
    
    glEnable(GL_LIGHTING);
   
}



void animateAll(int value){
    if(animDoor){
        moveDoor();
    } else if (animLid){
        moveLid();
    }
    glutTimerFunc(190, animateAll, 1);
}

void drawDoor(void) {
    float doorWidth = 40.0f;
    float doorHeight = 60.0f;
    float heightNDepth = 100.0f;
    float dep = 170;
    if(select){
        glDisable(GL_LIGHTING);
        glColor3ub(200, 0, 0);
    }else {
        setMaterial(0.1, 0.1, 0.8);// blueish
    }
    
    glPushMatrix();
        glTranslatef(doorOffset, 0, dep / 2 + 0.1f);

        glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3f(-doorWidth / 2, 0, 0);
        glVertex3f(doorWidth / 2, 0, 0);
        glVertex3f(doorWidth / 2, doorHeight, 0);
        glVertex3f(-doorWidth / 2, doorHeight, 0);
        glEnd();
    glPopMatrix();
}

void drawBedFrame(float bedWidth = 45.0, float bedLength = 50.0, float bedHeight = 25.0, float legThickness = 4.0, float legHeight = 10.0) {
    // Center of the bed frame
    float xCenter = 70.0;  // right side of the room
    float zCenter = -10.0;   // center in terms of z

   
    setMaterial(0.55, 0.27, 0.07);

    // Drawing the 4 legs
    float halfW = bedWidth / 2.0;
    float halfL = bedLength / 2.0;
    float legOffset = legThickness / 2.0;
    //positions for legs
    float legX[] = {
        xCenter - halfW + legOffset,
        xCenter + halfW - legOffset,
        xCenter - halfW + legOffset,
        xCenter + halfW - legOffset
    };

    float legZ[] = {
        zCenter - halfL + legOffset,
        zCenter - halfL + legOffset,
        zCenter + halfL - legOffset,
        zCenter + halfL - legOffset
    };

    for (int i = 0; i < 4; i++) { //draw them one by one
        glPushMatrix();
        glTranslatef(legX[i], legHeight / 2.0, legZ[i]);
        glScalef(legThickness, legHeight, legThickness);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // top frame (bed base)
    glPushMatrix();
    glTranslatef(xCenter, legHeight + bedHeight / 2.0f, zCenter);
    glScalef(bedWidth, bedHeight, bedLength);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // the bed itself
    setMaterial(0.0, 0.0, 0.6); // blue sheets
    glPushMatrix();
    glTranslatef(69.8, 38.0, -10.0);
    glScalef(45, 8, 50);
    glutSolidCube(1.0);
    glPopMatrix();
    
    //pillow
    setMaterial(0.7, 0.7, 0.7); //white
    glPushMatrix();
    glTranslatef(69.8, 43.0, -30.0);
    glScalef(15, 4, 10);
    glutSolidCube(1.0);
    glPopMatrix();
    
}

void drawDesk(){
    setMaterial(0.5, 0.3, 0.075); // dark brown
    
    //top left leg
    glPushMatrix();
    glTranslatef(-85, 19.0, -5.0);
    glScalef(4, 30, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //top right
    glPushMatrix();
    glTranslatef(-55, 19.0, -5.0);
    glScalef(4, 30, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //back right
    glPushMatrix();
    glTranslatef(-55, 19.0, -15.0);
    glScalef(4, 30, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //back left
    glPushMatrix();
    glTranslatef(-85, 19.0, -15.0);
    glScalef(4, 30, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    
    //table top
    glPushMatrix();
    glTranslatef(-68, 35.0, -10.0);
    glScalef(34, 2, 25);
    glutSolidCube(1.0);
    glPopMatrix();
    
    setMaterial(0.0, 0.0, 0.0); //black
    //chair (legs)
    //top left leg
    glPushMatrix();
    glTranslatef(-82, 10.0, -2.0);
    glScalef(2, 15, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //top right
    glPushMatrix();
    glTranslatef(-61, 10.0, -2.0);
    glScalef(2, 15, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //back right
    glPushMatrix();
    glTranslatef(-61, 10.0, 12.0);
    glScalef(2, 15, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //back left
    glPushMatrix();
    glTranslatef(-80, 10.0, 14.0);
    glScalef(2, 15, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    //seat
    glPushMatrix();
    glTranslatef(-72, 17.0, 4.5);
    glScalef(22, 2, 19);
    glutSolidCube(1.0);
    glPopMatrix();
    //back rest
    glPushMatrix();
    glTranslatef(-72, 25.0, 12.0);
    glScalef(25, 16, 2);
    glutSolidCube(1.0);
    glPopMatrix();
    
}

void drawMiniCooler()
{
    float coolerSize = 20.0f;
    float coolerX = 70.0f;
    float coolerZ = -65.0f;
    
    
    float wallThickness = 1.0f;
    float halfSize = coolerSize / 2.0f;

    // light gray
    setMaterial(0.8f, 0.8f, 0.8f);

    // Bottom
    glPushMatrix();
    glTranslatef(coolerX, wallThickness / 2.0f, coolerZ);
    glScalef(coolerSize, wallThickness, coolerSize);
    glutSolidCube(1.0);
    glPopMatrix();

    // Back wall
    glPushMatrix();
    glTranslatef(coolerX, halfSize, coolerZ - halfSize + wallThickness / 2.0f);
    glScalef(coolerSize, coolerSize, wallThickness);
    glutSolidCube(1.0);
    glPopMatrix();

    // Front wall
    glPushMatrix();
    glTranslatef(coolerX, halfSize, coolerZ + halfSize - wallThickness / 2.0f);
    glScalef(coolerSize, coolerSize, wallThickness);
    glutSolidCube(1.0);
    glPopMatrix();

    // Left wall
    glPushMatrix();
    glTranslatef(coolerX - halfSize + wallThickness / 2.0f, halfSize, coolerZ);
    glScalef(wallThickness, coolerSize, coolerSize);
    glutSolidCube(1.0);
    glPopMatrix();

    // Right wall
    glPushMatrix();
    glTranslatef(coolerX + halfSize - wallThickness / 2.0f, halfSize, coolerZ);
    glScalef(wallThickness, coolerSize, coolerSize);
    glutSolidCube(1.0);
    glPopMatrix();

    if (select){
        glDisable(GL_LIGHTING);
        glColor3ub(100, 100, 100);
    } else {
        setMaterial(0.0, 0.0, 0.0); //black for lid
    }
    
    // Lid
    glPushMatrix();
    glTranslatef(coolerX + lidOffset, coolerSize + wallThickness / 2.0f, coolerZ);
    glScalef(coolerSize, wallThickness, coolerSize);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawFurniture(){
    float beanbagCtrlPoints[4][4][3] = {
            {
                { -1.5, 0.0,  1.5 }, { -0.5, 0.6,  1.5 }, { 0.5, 0.6,  1.5 }, {1.5, 0.0,  1.5}
            },
            {
                { -1.5, 0.6,  0.5 }, { -0.5, 1.2,  0.5 }, { 0.5, 1.2,  0.5 }, {1.5, 0.6,  0.5}
            },
            {
                { -1.5, 0.6, -0.5 }, { -0.5, 1.2, -0.5 }, { 0.5, 1.2, -0.5 }, {1.5, 0.6, -0.5}
            },
            {
                { -1.5, 0.0, -1.5 }, { -0.5, 0.6, -1.5 }, { 0.5, 0.6, -1.5 }, {1.5, 0.0, -1.5}
            }
    };
    
    beanbagCtrlPoints[1][1][1] = -0.8f; // for the middle to be deeper
    beanbagCtrlPoints[1][2][1] = -0.8f;
    beanbagCtrlPoints[2][1][1] = -0.8f;
    beanbagCtrlPoints[2][2][1] = -0.8f;
    
    glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3,
            0.0f, 1.0f,
            3,
            4,
            0.0f, 1.0f,
            12,
            4,
            &beanbagCtrlPoints[0][0][0]);
    glEnable(GL_AUTO_NORMAL);  //lighting normals
    glMapGrid2f(20, 0.0f, 1.0f, 20, 0.0f, 1.0f);
    
    glPushMatrix();
    glTranslatef(-75.0f, 10.0f, -70.0f); //location
    glScalef(10, 15, 10);
    setMaterial(0.5, 0.2, 0.6);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    
    glDisable(GL_MAP2_VERTEX_3);
    glDisable(GL_AUTO_NORMAL);
    
    //seat base
    glBegin(GL_QUADS);
    glVertex3f(-90, 0, -59);
    glVertex3f(-90, 12.5, -59);
    glVertex3f(-60, 12.5, -59);
    glVertex3f(-60, 0, -59);
    
    glVertex3f(-60, 14.5, -59);
    glVertex3f(-60, 0, -59);
    glVertex3f(-60, 0, -79);
    glVertex3f(-60, 14.5, -79);
    glEnd();
    
    //dresser
    setMaterial(0.62, 0.32, 0.17);
    glPushMatrix();
    glTranslatef(80.0, 20, 37);
    glScalef(20, 46, 19);
    glutSolidCube(1);
    glPopMatrix();
    
    
    
    //laundry basket
    GLUquadric* basket = gluNewQuadric();
    gluQuadricNormals(basket, GLU_SMOOTH);
    setMaterial(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-86, 0, 38);
    glRotated(-90, 1, 0, 0);
    gluCylinder(basket, 10, 10, 30, 20, 20);
    glPopMatrix();
    
}

void drawAvatar(){
    //moves in relation to camera
    float avX = meX + 5.0 * sin(angle * PI / 180.0);
    float avY = meY - 2.0;
    float avZ = meZ - 5.0 * cos(angle * PI / 180.0);

    glPushMatrix();
    glTranslatef(avX, avY, avZ);
    setMaterial(r, b, g); // random color
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

}


void identifyObject(int x, int y){
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    
    if ((int)pixel[0]==100 && (int)pixel[1]==100 && (int)pixel[2]==100){ //
        animLid = true;
    }
    else if ((int)pixel[0]==200 && (int)pixel[1]==0 && (int)pixel[2]==0){
        animDoor = true;
    }
    select=false;
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
}



void drawFinal(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  main view first person
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 265);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(meX, meY, meZ,
              meX + sin(angle * PI / 180.0), meY, meZ - cos(angle * PI / 180.0),
              0, 1, 0);

    if (select) {
        drawHouse();
        drawDoor();
        drawMiniCooler();
        identifyObject(xClick, yClick);
    } else {
        if (!lightOn) {
            glDisable(GL_LIGHT0);
        } else {
            glEnable(GL_LIGHT0);
        }

        drawHouse();
        drawDoor();
        drawBedFrame();
        drawDesk();
        drawMiniCooler();
        drawFurniture();
        
    }

    // third person MINIMAP
    glViewport(500 - 200, 500 - 200, 200, 200); // Top-right of screen 200x200
    
    glEnable(GL_SCISSOR_TEST);//this clears the depth buffer for only the minimap so main scene doesnt block it
    glScissor(500 - 200, 500 - 200, 200, 200); //minimap dimensions
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 265);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(meX, meY, meZ - 1.5,
              meX + sin(angle * PI / 180.0), meY, meZ - 1.5 - cos(angle * PI / 180.0),
              0, 1, 0);

    // Draw scene with the avatar ball this time
    drawHouse();
    drawDoor();
    drawBedFrame();
    drawDesk();
    drawMiniCooler();
    drawFurniture();
    drawAvatar();
    
    // minimap border
    // Switch to the second viewport so I can align properly

    glViewport(500 - 200, 500 - 200, 200, 200);

    // Disable depth test and lighting so things dont get messed up
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    // Set up 2D orthographic projection for pixel alignment
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f); // Black border
    glLineWidth(2.3f);

    glBegin(GL_LINE_LOOP);
        glVertex2i(0, 0);
        glVertex2i(200, 0);
        glVertex2i(200, 200);
        glVertex2i(0, 200);
    glEnd();

    // Restore all the previous states
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    


    glutSwapBuffers();
}



void mouseControl(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN && button == GLUT_LEFT)
    {   select=true;
        xClick=x;
        yClick=500-y;
        glutPostRedisplay();
        
    }
}



// Initialization routine.
void setup(void){
    glClearColor(0.53, 0.81, 0.98, 1.0); // sky blue
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Turn on light 0
    glEnable(GL_NORMALIZE);
    
        // light properties
        float lightPos[] = {0.0f, 96.5f, 0.0f, 1.0f}; // Position near the ceiling
        float ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};
        float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float global_ambient[] = {0.55f, 0.55f, 0.55f, 1.0f};
        // Applying light settings
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    

    glGenTextures(5, texture);


    loadExternalTextures();


    glEnable(GL_TEXTURE_2D);


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
        
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {	  
      case 27:
         exit(0);
         break;
      case 'd':
           animDoor = true;
           break;
       case 'l':
           lightOn = !lightOn;
           glutPostRedisplay();
           break;
       case 'r':
           r = distr(gen);
           b = distr(gen);
           g = distr(gen);
           glutPostRedisplay();
           break;
      default:
         break;
   }
}

void specialKeyInput(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP: //forward
            meZ -= stepsize * cos(angle*PI/180);
            meX += stepsize * sin(angle*PI/180);
            break;
        case GLUT_KEY_DOWN: //back
            meZ += stepsize * cos(angle*PI/180);
            meX -= stepsize * sin(angle*PI/180);
            break;
        case GLUT_KEY_RIGHT: //turn right
            angle += turnsize;
            break;
        case GLUT_KEY_LEFT: //turn left
            angle -= turnsize;
            break;
    }//end switch
    glutPostRedisplay();
}

void printInstructions(void){
    cout << "Use the arrow keys to move around" << endl;
    cout << "Press l to toggle light on/off for room" << endl;
    cout << "Press r to switch avatar color (random)" << endl;
    cout << "Click door or press d to open/close it" << endl;
    cout << "Click the lid of the minicooler to open/close it" << endl;
    cout << "Press esc to quit window" << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("DormRoom.cpp");
   setup();
   printInstructions();
   glutDisplayFunc(drawFinal);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutMouseFunc(mouseControl);
   glutTimerFunc(190, animateAll, 1);//to start the animation when necessary
   glutMainLoop();

   return 0;  
}
