#include <windows.h>
#include<math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define PI 3.14159265358979323846

// Object positions, speeds and control flags
GLfloat carPosition = -5.2f;
GLfloat boatPosition = 5.2f;
GLfloat cloudPosition = -4.8f;
GLfloat cloudPosition2 = 0.4f;
GLfloat cloudPosition3 = 2.8f;
GLfloat rainPosition = 0.0f;
GLfloat carSpeed = 0.040f;
GLfloat boatSpeed = 0.032f;
GLfloat cloudSpeed = 0.016f;
GLfloat rainSpeed = 0.08f;
int dayMode = 1;
int rainOn = 1;
int cloudOn = 1;

// Car animation
void update(int value) {
      if(carPosition > 5.4f)
         carPosition = -5.4f;
      carPosition += carSpeed;
   glutPostRedisplay();
   glutTimerFunc(40, update, 0);
}

// Boat animation
void update1(int value) {
      if(boatPosition < -5.4f)
         boatPosition = 5.4f;
      boatPosition -= boatSpeed;
   glutPostRedisplay();
   glutTimerFunc(40, update1, 0);
}

// Cloud animation
void updateCloud(int value) {
      if(cloudPosition > 5.4f)
         cloudPosition = -5.4f;
      if(cloudPosition2 > 5.4f)
         cloudPosition2 = -5.4f;
      if(cloudPosition3 > 5.4f)
         cloudPosition3 = -5.4f;
      cloudPosition += cloudSpeed;
      cloudPosition2 += cloudSpeed;
      cloudPosition3 += cloudSpeed;
   glutPostRedisplay();
   glutTimerFunc(60, updateCloud, 0);
}

// Rain animation
void updateRain(int value) {
   if(rainOn == 1) {
      rainPosition -= rainSpeed;
      if(rainPosition < -8.0f)
         rainPosition = 0.0f;
   }
   glutPostRedisplay();
   glutTimerFunc(50, updateRain, 0);
}

// Background sound
void sound() {
   PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
}

// Circle drawing helper function
void circle(GLfloat x, GLfloat y, GLfloat radius) {
   int i;
   int triangleAmount = 30;
   GLfloat twicePi = 2.0f * PI;
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x, y);
   for(i = 0; i <= triangleAmount; i++) {
      glVertex2f(
         x + (radius * cos(i * twicePi / triangleAmount)),
         y + (radius * sin(i * twicePi / triangleAmount))
      );
   }
   glEnd();
}

// Sky
void drawSky() {
   if(dayMode == 1)
      glColor3f(0.2f, 0.7f, 0.9f);
   else
      glColor3f(0.0f, 0.1f, 0.1f);
   glBegin(GL_QUADS);
   glVertex2f(-4.0f, 0.2f);
   glVertex2f(4.0f, 0.2f);
   glVertex2f(4.0f, 4.0f);
   glVertex2f(-4.0f, 4.0f);
   glEnd();
}

// Sun and moon
void drawSunMoon() {
   if(dayMode == 1) {
      glColor3f(1.0f, 0.8f, 0.1f);
      circle(-3.0f, 3.1f, 0.4f);
   }
   else {
      glColor3f(0.9f, 0.9f, 0.8f);
      circle(-3.0f, 3.1f, 0.4f);
   }
}

// Cloud shape
void drawCloudShape() {
   if(dayMode == 1)
      glColor3f(0.9f, 1.0f, 1.0f);
   else
      glColor3f(0.3f, 0.3f, 0.4f);
   circle(-0.4f, 3.0f, 0.3f);
   circle(-0.1f, 3.2f, 0.4f);
   circle(0.2f, 3.0f, 0.3f);
   circle(0.4f, 3.0f, 0.2f);
}

// Clouds
void drawClouds() {

      glPushMatrix();
      glTranslatef(cloudPosition, 0.3f, 0.0f);
      drawCloudShape();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(cloudPosition2, -0.3f, 0.0f);
      drawCloudShape();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(cloudPosition3, 0.6f, 0.0f);
      drawCloudShape();
      glPopMatrix();

}

// Distant land
void drawDistantLand() {
   if(dayMode == 1)
      glColor3f(0.1f, 0.4f, 0.2f);
   else
      glColor3f(0.1f, 0.2f, 0.1f);
   glBegin(GL_POLYGON);
   glVertex2f(-4.0f, 0.5f);
   glVertex2f(-3.2f, 0.7f);
   glVertex2f(3.2f, 0.7f);
   glVertex2f(4.0f, 0.5f);
   glVertex2f(4.0f, 0.2f);
   glVertex2f(-4.0f, 0.2f);
   glEnd();
}

// Fort
void drawFortBase() {

   if(dayMode == 1)
      glColor3f(0.7f, 0.6f, 0.4f);
   else
      glColor3f(0.3f, 0.2f, 0.2f);

   // Main middle part
   glBegin(GL_QUADS);

   glVertex2f(-2.5f, -0.2f);
   glVertex2f( 2.5f, -0.2f);
   glVertex2f( 2.5f,  1.7f);
   glVertex2f(-2.5f,  1.7f);

   glEnd();


   if(dayMode == 1)
      glColor3f(0.8f, 0.6f, 0.5f);
   else
      glColor3f(0.3f, 0.3f, 0.2f);


   // Left side
   glBegin(GL_POLYGON);

   glVertex2f(-3.2f, -0.2f);
   glVertex2f(-2.5f, -0.2f);
   glVertex2f(-2.5f,  1.9f);
   glVertex2f(-2.7f,  2.1f);
   glVertex2f(-3.0f,  2.1f);
   glVertex2f(-3.2f,  1.9f);

   glEnd();


   // Right side
   glBegin(GL_POLYGON);

   glVertex2f( 2.5f, -0.2f);
   glVertex2f( 3.2f, -0.2f);
   glVertex2f( 3.2f,  1.9f);
   glVertex2f( 3.0f,  2.1f);
   glVertex2f( 2.7f,  2.1f);
   glVertex2f( 2.5f,  1.9f);

   glEnd();
}
// Fort battlements
void drawBattlement2() {
   glBegin(GL_QUADS);
   glVertex2f(-2.2f, 1.7f);
   glVertex2f(-2.0f, 1.7f);
   glVertex2f(-2.0f, 2.0f);
   glVertex2f(-2.2f, 2.0f);
   glEnd();
}

void drawBattlement3() {
   glBegin(GL_QUADS);
   glVertex2f(-1.4f, 1.7f);
   glVertex2f(-1.2f, 1.7f);
   glVertex2f(-1.2f, 2.0f);
   glVertex2f(-1.4f, 2.0f);
   glEnd();
}

void drawBattlement4() {
   glBegin(GL_QUADS);
   glVertex2f(-0.6f, 1.7f);
   glVertex2f(-0.4f, 1.7f);
   glVertex2f(-0.4f, 2.0f);
   glVertex2f(-0.6f, 2.0f);
   glEnd();
}

void drawBattlement5() {
   glBegin(GL_QUADS);
   glVertex2f(0.2f, 1.7f);
   glVertex2f(0.4f, 1.7f);
   glVertex2f(0.4f, 2.0f);
   glVertex2f(0.2f, 2.0f);
   glEnd();
}

void drawBattlement6() {
   glBegin(GL_QUADS);
   glVertex2f(1.0f, 1.7f);
   glVertex2f(1.2f, 1.7f);
   glVertex2f(1.2f, 2.0f);
   glVertex2f(1.0f, 2.0f);
   glEnd();
}

void drawBattlement7() {
   glBegin(GL_QUADS);
   glVertex2f(1.8f, 1.7f);
   glVertex2f(2.0f, 1.7f);
   glVertex2f(2.0f, 2.0f);
   glVertex2f(1.8f, 2.0f);
   glEnd();
}

void drawBattlements() {

   if(dayMode == 1)
      glColor3f(0.8f, 0.6f, 0.5f);
   else
      glColor3f(0.3f, 0.3f, 0.2f);

   drawBattlement2();
   drawBattlement3();
   drawBattlement4();
   drawBattlement5();
   drawBattlement6();
   drawBattlement7();
}
// Fort windows
void drawFortWindow1() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-2.1f, 1.1f);
   glVertex2f(-1.9f, 1.1f);
   glVertex2f(-1.9f, 1.4f);
   glVertex2f(-2.1f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-2.0f, 1.1f);
   glVertex2f(-2.0f, 1.4f);
   glVertex2f(-2.1f, 1.3f);
   glVertex2f(-1.9f, 1.3f);
   glEnd();
}
void drawFortWindow2() {
     if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-1.6f, 1.1f);
   glVertex2f(-1.4f, 1.1f);
   glVertex2f(-1.4f, 1.4f);
   glVertex2f(-1.6f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-1.5f, 1.1f);
   glVertex2f(-1.5f, 1.4f);
   glVertex2f(-1.6f, 1.3f);
   glVertex2f(-1.4f, 1.3f);
   glEnd();
}
void drawFortWindow3() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-1.1f, 1.1f);
   glVertex2f(-0.9f, 1.1f);
   glVertex2f(-0.9f, 1.4f);
   glVertex2f(-1.1f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-1.0f, 1.1f);
   glVertex2f(-1.0f, 1.4f);
   glVertex2f(-1.1f, 1.3f);
   glVertex2f(-0.9f, 1.3f);
   glEnd();
}
void drawFortWindow4() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-0.6f, 1.1f);
   glVertex2f(-0.4f, 1.1f);
   glVertex2f(-0.4f, 1.4f);
   glVertex2f(-0.6f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-0.5f, 1.1f);
   glVertex2f(-0.5f, 1.4f);
   glVertex2f(-0.6f, 1.3f);
   glVertex2f(-0.4f, 1.3f);
   glEnd();
}
void drawFortWindow5() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-0.1f, 1.1f);
   glVertex2f(0.1f, 1.1f);
   glVertex2f(0.1f, 1.4f);
   glVertex2f(-0.1f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(0.0f, 1.1f);
   glVertex2f(0.0f, 1.4f);
   glVertex2f(-0.1f, 1.3f);
   glVertex2f(0.1f, 1.3f);
   glEnd();
}
void drawFortWindow6() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(0.4f, 1.1f);
   glVertex2f(0.6f, 1.1f);
   glVertex2f(0.6f, 1.4f);
   glVertex2f(0.4f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(0.5f, 1.1f);
   glVertex2f(0.5f, 1.4f);
   glVertex2f(0.4f, 1.3f);
   glVertex2f(0.6f, 1.3f);
   glEnd();
}
void drawFortWindow7() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(0.9f, 1.1f);
   glVertex2f(1.1f, 1.1f);
   glVertex2f(1.1f, 1.4f);
   glVertex2f(0.9f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(1.0f, 1.1f);
   glVertex2f(1.0f, 1.4f);
   glVertex2f(0.9f, 1.3f);
   glVertex2f(1.1f, 1.3f);
   glEnd();
}
void drawFortWindow8() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(1.4f, 1.1f);
   glVertex2f(1.6f, 1.1f);
   glVertex2f(1.6f, 1.4f);
   glVertex2f(1.4f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(1.5f, 1.1f);
   glVertex2f(1.5f, 1.4f);
   glVertex2f(1.4f, 1.3f);
   glVertex2f(1.6f, 1.3f);
   glEnd();
}
void drawFortWindow9() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(1.9f, 1.1f);
   glVertex2f(2.1f, 1.1f);
   glVertex2f(2.1f, 1.4f);
   glVertex2f(1.9f, 1.4f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(2.0f, 1.1f);
   glVertex2f(2.0f, 1.4f);
   glVertex2f(1.9f, 1.3f);
   glVertex2f(2.1f, 1.3f);
   glEnd();
}
void drawFortWindow10() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-2.1f, 0.5f);
   glVertex2f(-1.9f, 0.5f);
   glVertex2f(-1.9f, 0.8f);
   glVertex2f(-2.1f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-2.0f, 0.5f);
   glVertex2f(-2.0f, 0.8f);
   glVertex2f(-2.1f, 0.6f);
   glVertex2f(-1.9f, 0.6f);
   glEnd();
}
void drawFortWindow11() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-1.6f, 0.5f);
   glVertex2f(-1.4f, 0.5f);
   glVertex2f(-1.4f, 0.8f);
   glVertex2f(-1.6f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-1.5f, 0.5f);
   glVertex2f(-1.5f, 0.8f);
   glVertex2f(-1.6f, 0.6f);
   glVertex2f(-1.4f, 0.6f);
   glEnd();
}
void drawFortWindow12() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-1.1f, 0.5f);
   glVertex2f(-0.9f, 0.5f);
   glVertex2f(-0.9f, 0.8f);
   glVertex2f(-1.1f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-1.0f, 0.5f);
   glVertex2f(-1.0f, 0.8f);
   glVertex2f(-1.1f, 0.6f);
   glVertex2f(-0.9f, 0.6f);
   glEnd();
}
void drawFortWindow13() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-0.6f, 0.5f);
   glVertex2f(-0.4f, 0.5f);
   glVertex2f(-0.4f, 0.8f);
   glVertex2f(-0.6f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(-0.5f, 0.5f);
   glVertex2f(-0.5f, 0.8f);
   glVertex2f(-0.6f, 0.6f);
   glVertex2f(-0.4f, 0.6f);
   glEnd();
}
void drawFortWindow14() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(-0.1f, 0.5f);
   glVertex2f(0.1f, 0.5f);
   glVertex2f(0.1f, 0.8f);
   glVertex2f(-0.1f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(0.0f, 0.5f);
   glVertex2f(0.0f, 0.8f);
   glVertex2f(-0.1f, 0.6f);
   glVertex2f(0.1f, 0.6f);
   glEnd();
}
void drawFortWindow15() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(0.4f, 0.5f);
   glVertex2f(0.6f, 0.5f);
   glVertex2f(0.6f, 0.8f);
   glVertex2f(0.4f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(0.5f, 0.5f);
   glVertex2f(0.5f, 0.8f);
   glVertex2f(0.4f, 0.6f);
   glVertex2f(0.6f, 0.6f);
   glEnd();
}
void drawFortWindow16() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(0.9f, 0.5f);
   glVertex2f(1.1f, 0.5f);
   glVertex2f(1.1f, 0.8f);
   glVertex2f(0.9f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(1.0f, 0.5f);
   glVertex2f(1.0f, 0.8f);
   glVertex2f(0.9f, 0.6f);
   glVertex2f(1.1f, 0.6f);
   glEnd();
}
void drawFortWindow17() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(1.4f, 0.5f);
   glVertex2f(1.6f, 0.5f);
   glVertex2f(1.6f, 0.8f);
   glVertex2f(1.4f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(1.5f, 0.5f);
   glVertex2f(1.5f, 0.8f);
   glVertex2f(1.4f, 0.6f);
   glVertex2f(1.6f, 0.6f);
   glEnd();
}
void drawFortWindow18() {
  if(dayMode == 1)
   glColor3f(0.2f, 0.2f, 0.1f);
else
   glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
   glVertex2f(1.9f, 0.5f);
   glVertex2f(2.1f, 0.5f);
   glVertex2f(2.1f, 0.8f);
   glVertex2f(1.9f, 0.8f);
   glEnd();
   glColor3f(0.5f, 0.4f, 0.3f);
   glLineWidth(1.0f);
   glBegin(GL_LINES);
   glVertex2f(2.0f, 0.5f);
   glVertex2f(2.0f, 0.8f);
   glVertex2f(1.9f, 0.6f);
   glVertex2f(2.1f, 0.6f);
   glEnd();
}
void drawFortWindows() {
   drawFortWindow1();
   drawFortWindow2();
   drawFortWindow3();
   drawFortWindow4();
   drawFortWindow5();
   drawFortWindow6();
   drawFortWindow7();
   drawFortWindow8();
   drawFortWindow9();
   drawFortWindow10();
   drawFortWindow11();
   drawFortWindow12();
   drawFortWindow13();
   drawFortWindow14();
   drawFortWindow15();
   drawFortWindow16();
   drawFortWindow17();
   drawFortWindow18();
}


void drawFort() {
   drawFortBase();
   drawBattlements();
   drawFortWindows();
}

// Water
void drawWater() {
   if(dayMode == 1)
      glColor3f(0.1f, 0.5f, 0.6f);
   else
      glColor3f(0.0f, 0.1f, 0.2f);
   glBegin(GL_QUADS);
   glVertex2f(-4.0f, -2.6f);
   glVertex2f(4.0f, -2.6f);
   glVertex2f(4.0f, 0.2f);
   glVertex2f(-4.0f, 0.2f);
   glEnd();
}

// Road
void drawRoad() {
   glColor3f(0.2f, 0.2f, 0.2f);
   glBegin(GL_QUADS);
   glVertex2f(-4.0f, -4.0f);
   glVertex2f(4.0f, -4.0f);
   glVertex2f(4.0f, -3.0f);
   glVertex2f(-4.0f, -3.0f);
   glEnd();

   glColor3f(0.9f, 0.9f, 0.4f);
   glBegin(GL_LINES);
   glVertex2f(-4.0f, -3.5f);
   glVertex2f(-2.9f, -3.5f);
   glVertex2f(-2.2f, -3.5f);
   glVertex2f(-1.1f, -3.5f);
   glVertex2f(-0.4f, -3.5f);
   glVertex2f(0.7f, -3.5f);
   glVertex2f(1.4f, -3.5f);
   glVertex2f(2.5f, -3.5f);
   glVertex2f(3.2f, -3.5f);
   glVertex2f(4.0f, -3.5f);
   glEnd();
}

void drawCarWheel() {

   glColor3f(0.0f, 0.0f, 0.0f);
   circle(0.0f, 0.0f, 0.2f);

   glColor3f(0.6f, 0.6f, 0.6f);
   circle(0.0f, 0.0f, 0.1f);
}

void drawCar() {
      glPushMatrix();
      // Move the full car
      glTranslatef(carPosition, -3.3f, 0.0f);
      //car body - lower part
      glColor3f(0.8f, 0.1f, 0.1f);
      glBegin(GL_POLYGON);

      glVertex2f(-0.75f, 0.0f);
      glVertex2f(-0.65f, -0.1f);
      glVertex2f(0.65f, -0.1f);
      glVertex2f(0.75f, 0.0f);
      glVertex2f(0.75f, 0.25f);
      glVertex2f(0.6f, 0.4f);
      glVertex2f(-0.6f, 0.4f);
      glVertex2f(-0.75f, 0.25f);
      glEnd();

      //car body - upper part
      glBegin(GL_QUADS);
      glVertex2f(-0.4f, 0.4f);
      glVertex2f(-0.25f, 0.75f);
      glVertex2f(0.25f, 0.75f);
      glVertex2f(0.4f, 0.4f);
      glEnd();

      // Left window
      glColor3f(0.7f, 0.9f, 0.9f);
      glBegin(GL_QUADS);
      glVertex2f(-0.3f, 0.45f);
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(0.0f, 0.7f);
      glVertex2f(0.0f, 0.45f);
      glEnd();
      // Right window
      glBegin(GL_QUADS);
      glVertex2f(0.05f, 0.45f);
      glVertex2f(0.05f, 0.7f);
      glVertex2f(0.2f, 0.7f);
      glVertex2f(0.3f, 0.45f);
      glEnd();
      // Front light
      glColor3f(1.0f, 1.0f, 0.3f);
      glBegin(GL_QUADS);
      glVertex2f(0.68f, 0.1f);
      glVertex2f(0.75f, 0.1f);
      glVertex2f(0.75f, 0.22f);
      glVertex2f(0.68f, 0.22f);
      glEnd();
      // Left wheel
      glPushMatrix();
      glTranslatef(-0.4f, -0.1f, 0.0f);
      drawCarWheel();
      glPopMatrix();
      // Right wheel
      glPushMatrix();
      glTranslatef(0.4f, -0.1f, 0.0f);
      drawCarWheel();
      glPopMatrix();

      glPopMatrix();
}
void drawBoat() {
      glPushMatrix();
      // Move the boat
      glTranslatef(boatPosition, -1.6f, 0.0f);

      // Boat lower body
      glColor3f(0.4f, 0.2f, 0.1f);
      glBegin(GL_QUADS);
      glVertex2f(-0.8f, 0.1f);
      glVertex2f(0.9f, 0.1f);
      glVertex2f(0.6f, -0.3f);
      glVertex2f(-0.5f, -0.3f);
      glEnd();

      // Boat upper body
      glColor3f(0.7f, 0.4f, 0.1f);
      glBegin(GL_QUADS);
      glVertex2f(-0.4f, 0.1f);
      glVertex2f(0.4f, 0.1f);
      glVertex2f(0.3f, 0.4f);
      glVertex2f(-0.3f, 0.4f);
      glEnd();

      // Boat mast
      glColor3f(0.2f, 0.1f, 0.1f);
      //glLineWidth(3.0f);
      glBegin(GL_LINES);
      glVertex2f(-0.1f, 0.4f);
      glVertex2f(-0.1f, 1.0f);
      glEnd();

      // Boat sail
      glColor3f(0.9f, 0.9f, 0.7f);
      glBegin(GL_TRIANGLES);
      glVertex2f(-0.1f, 0.9f);
      glVertex2f(-0.1f, 0.5f);
      glVertex2f(0.4f, 0.6f);
      glEnd();

      glPopMatrix();

}
// Rain
void drawRain() {

   if(rainOn == 1) {

      glPushMatrix();

    glTranslatef(0.0f, rainPosition, 0.0f);
    glColor3f(0.7f, 0.8f, 0.9f);
    glBegin(GL_LINES);

    // Row 1
    glVertex2f(-3.8f, 4.0f);
    glVertex2f(-3.8f, 3.7f);

    glVertex2f(-3.4f, 3.6f);
    glVertex2f(-3.4f, 3.3f);

    glVertex2f(-3.0f, 4.2f);
    glVertex2f(-3.0f, 3.9f);

    glVertex2f(-2.6f, 3.3f);
    glVertex2f(-2.6f, 3.0f);

    glVertex2f(-2.2f, 4.0f);
    glVertex2f(-2.2f, 3.7f);

    glVertex2f(-1.8f, 3.5f);
    glVertex2f(-1.8f, 3.2f);

    glVertex2f(-1.4f, 4.2f);
    glVertex2f(-1.4f, 3.9f);

    glVertex2f(-1.0f, 3.6f);
    glVertex2f(-1.0f, 3.3f);

    glVertex2f(-0.6f, 4.0f);
    glVertex2f(-0.6f, 3.7f);

    glVertex2f(-0.2f, 3.4f);
    glVertex2f(-0.2f, 3.1f);

    glVertex2f(0.2f, 4.2f);
    glVertex2f(0.2f, 3.9f);

    glVertex2f(0.6f, 3.6f);
    glVertex2f(0.6f, 3.3f);

    glVertex2f(1.0f, 4.0f);
    glVertex2f(1.0f, 3.7f);

    glVertex2f(1.4f, 3.4f);
    glVertex2f(1.4f, 3.1f);

    glVertex2f(1.8f, 4.2f);
    glVertex2f(1.8f, 3.9f);

    glVertex2f(2.2f, 3.6f);
    glVertex2f(2.2f, 3.3f);

    glVertex2f(2.6f, 4.0f);
    glVertex2f(2.6f, 3.7f);

    glVertex2f(3.0f, 3.4f);
    glVertex2f(3.0f, 3.1f);

    glVertex2f(3.4f, 4.2f);
    glVertex2f(3.4f, 3.9f);

    glVertex2f(3.8f, 3.5f);
    glVertex2f(3.8f, 3.2f);


    // Row 2
    glVertex2f(-3.6f, 2.8f);
    glVertex2f(-3.6f, 2.5f);

    glVertex2f(-3.2f, 2.3f);
    glVertex2f(-3.2f, 2.0f);

    glVertex2f(-2.8f, 2.9f);
    glVertex2f(-2.8f, 2.6f);

    glVertex2f(-2.4f, 2.2f);
    glVertex2f(-2.4f, 1.9f);

    glVertex2f(-2.0f, 2.7f);
    glVertex2f(-2.0f, 2.4f);

    glVertex2f(-1.6f, 2.1f);
    glVertex2f(-1.6f, 1.8f);

    glVertex2f(-1.2f, 2.8f);
    glVertex2f(-1.2f, 2.5f);

    glVertex2f(-0.8f, 2.3f);
    glVertex2f(-0.8f, 2.0f);

    glVertex2f(-0.4f, 2.9f);
    glVertex2f(-0.4f, 2.6f);

    glVertex2f(0.0f, 2.2f);
    glVertex2f(0.0f, 1.9f);

    glVertex2f(0.4f, 2.7f);
    glVertex2f(0.4f, 2.4f);

    glVertex2f(0.8f, 2.1f);
    glVertex2f(0.8f, 1.8f);

    glVertex2f(1.2f, 2.8f);
    glVertex2f(1.2f, 2.5f);

    glVertex2f(1.6f, 2.3f);
    glVertex2f(1.6f, 2.0f);

    glVertex2f(2.0f, 2.9f);
    glVertex2f(2.0f, 2.6f);

    glVertex2f(2.4f, 2.2f);
    glVertex2f(2.4f, 1.9f);

    glVertex2f(2.8f, 2.7f);
    glVertex2f(2.8f, 2.4f);

    glVertex2f(3.2f, 2.1f);
    glVertex2f(3.2f, 1.8f);

    glVertex2f(3.6f, 2.8f);
    glVertex2f(3.6f, 2.5f);


    // Row 3
    glVertex2f(-3.8f, 1.6f);
    glVertex2f(-3.8f, 1.3f);

    glVertex2f(-3.4f, 1.1f);
    glVertex2f(-3.4f, 0.8f);

    glVertex2f(-3.0f, 1.7f);
    glVertex2f(-3.0f, 1.4f);

    glVertex2f(-2.6f, 1.0f);
    glVertex2f(-2.6f, 0.7f);

    glVertex2f(-2.2f, 1.5f);
    glVertex2f(-2.2f, 1.2f);

    glVertex2f(-1.8f, 0.9f);
    glVertex2f(-1.8f, 0.6f);

    glVertex2f(-1.4f, 1.6f);
    glVertex2f(-1.4f, 1.3f);

    glVertex2f(-1.0f, 1.1f);
    glVertex2f(-1.0f, 0.8f);

    glVertex2f(-0.6f, 1.7f);
    glVertex2f(-0.6f, 1.4f);

    glVertex2f(-0.2f, 1.0f);
    glVertex2f(-0.2f, 0.7f);

    glVertex2f(0.2f, 1.5f);
    glVertex2f(0.2f, 1.2f);

    glVertex2f(0.6f, 0.9f);
    glVertex2f(0.6f, 0.6f);

    glVertex2f(1.0f, 1.6f);
    glVertex2f(1.0f, 1.3f);

    glVertex2f(1.4f, 1.1f);
    glVertex2f(1.4f, 0.8f);

    glVertex2f(1.8f, 1.7f);
    glVertex2f(1.8f, 1.4f);

    glVertex2f(2.2f, 1.0f);
    glVertex2f(2.2f, 0.7f);

    glVertex2f(2.6f, 1.5f);
    glVertex2f(2.6f, 1.2f);

    glVertex2f(3.0f, 0.9f);
    glVertex2f(3.0f, 0.6f);

    glVertex2f(3.4f, 1.6f);
    glVertex2f(3.4f, 1.3f);


    // Row 4
    glVertex2f(-3.6f, 0.4f);
    glVertex2f(-3.6f, 0.1f);

    glVertex2f(-3.2f, -0.2f);
    glVertex2f(-3.2f, -0.5f);

    glVertex2f(-2.8f, 0.5f);
    glVertex2f(-2.8f, 0.2f);

    glVertex2f(-2.4f, -0.1f);
    glVertex2f(-2.4f, -0.4f);

    glVertex2f(-2.0f, 0.3f);
    glVertex2f(-2.0f, 0.0f);

    glVertex2f(-1.6f, -0.3f);
    glVertex2f(-1.6f, -0.6f);

    glVertex2f(-1.2f, 0.4f);
    glVertex2f(-1.2f, 0.1f);

    glVertex2f(-0.8f, -0.2f);
    glVertex2f(-0.8f, -0.5f);

    glVertex2f(-0.4f, 0.5f);
    glVertex2f(-0.4f, 0.2f);

    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, -0.4f);

    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.4f, 0.0f);

    glVertex2f(0.8f, -0.3f);
    glVertex2f(0.8f, -0.6f);

    glVertex2f(1.2f, 0.4f);
    glVertex2f(1.2f, 0.1f);

    glVertex2f(1.6f, -0.2f);
    glVertex2f(1.6f, -0.5f);

    glVertex2f(2.0f, 0.5f);
    glVertex2f(2.0f, 0.2f);

    glVertex2f(2.4f, -0.1f);
    glVertex2f(2.4f, -0.4f);

    glVertex2f(2.8f, 0.3f);
    glVertex2f(2.8f, 0.0f);

    glVertex2f(3.2f, -0.3f);
    glVertex2f(3.2f, -0.6f);

    glVertex2f(3.6f, 0.4f);
    glVertex2f(3.6f, 0.1f);

    glEnd();

    glPopMatrix();

   }
}
// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glScalef(0.25f, 0.25f, 1.0f);

   drawSky();
   drawSunMoon();
   drawClouds();
   drawDistantLand();
   drawFort();
   drawWater();
   drawBoat();
   drawRoad();

   if(dayMode == 1)
      glColor3f(0.2f, 0.5f, 0.2f);
   else
      glColor3f(0.1f, 0.2f, 0.1f);
//ground area between water and road
   glBegin(GL_QUADS);
   glVertex2f(-4.0f, -3.0f);
   glVertex2f(4.0f, -3.0f);
   glVertex2f(4.0f, -2.6f);
   glVertex2f(-4.0f, -2.6f);
   glEnd();

   drawCar();
   drawRain();

   glFlush();
}

// Day and night controls
void day() {
   dayMode = 1;
   glutPostRedisplay();
}

void night() {
   dayMode = 0;
   glutPostRedisplay();
}

void SpecialInput(int key, int x, int y) {
   switch(key) {

      case GLUT_KEY_UP:
         carSpeed = 0.15f;
         boatSpeed = 0.10f;
         break;

      case GLUT_KEY_DOWN:
         carSpeed = 0.040f;
         boatSpeed = 0.032f;
         break;

      case GLUT_KEY_LEFT:
         if(cloudSpeed > 0.016f)
            cloudSpeed = 0.016f;
         else
            cloudSpeed = 0.0f;
         break;

      case GLUT_KEY_RIGHT:
         cloudSpeed = 0.08f;
         break;
   }

   glutPostRedisplay();
}
// Keyboard controls
void handleKeypress(unsigned char key, int x, int y) {
   switch(key) {
      case 'd':
         day();
         break;
      case 'n':
         night();
         break;
      case 'r':
         if(rainOn == 1)
            rainOn = 0;
         else
            rainOn = 1;
         break;

   }
   glutPostRedisplay();
}
// Main function
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitWindowSize(1000, 700);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Idrakpur Fort Scene");
   glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
   glutDisplayFunc(display);
   glutKeyboardFunc(handleKeypress);
   glutSpecialFunc(SpecialInput);
   glutTimerFunc(40, update, 0);
   glutTimerFunc(40, update1, 0);
   glutTimerFunc(60, updateCloud, 0);
   glutTimerFunc(100, updateRain, 0);
   sound();
   glutMainLoop();
   return 0;
}
