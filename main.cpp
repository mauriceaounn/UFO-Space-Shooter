#ifdef _WIN32
#include<windows.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define GL_SILENCE_DEPRECATION

#define XMAX 1200
#define YMAX 700
#define SPACESHIP_SPEED 20
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3


GLint m_viewport[4];
bool mButtonPressed = false;
float mouseX, mouseY;
enum view { INTRO, MENU, INSTRUCTIONS, GAME, GAMEOVER };
view viewPage = INTRO; // initial value
bool keyStates[256] = { false };
bool direction[4] = { false };
bool laser1Dir[2] = { false };
bool laser2Dir[2] = { false };

int alienLife1 = 100;
int alienLife2 = 100;
bool gameOver = false;
float xOne = 500, yOne = 0;
float xTwo = 500, yTwo = 0;
bool laser1 = false, laser2 = false;
GLint CI = 0;
GLfloat a[][2] = { 0,-50, 70,-50, 70,70, -70,70 };
GLfloat LightColor[][3] = { 1,1,0,   0,1,1,   0,1,0 };



void displayRasterText(float x, float y, float z, char* stringToDisplay) {
	glRasterPos3f(x, y, z);
	for (char* c = stringToDisplay; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1200, 1200, -700, 700);                
	glMatrixMode(GL_MODELVIEW);
}

void introScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-475, 490, 0.0, "American University Of Science And Technology");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-300, 300, 0.0, "CSI 470 - Computer Graphics");
	glColor3f(1.0, 0.0, 1.0);
	displayRasterText(-130, 225, 0.0, "Space Shooter");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-800, -100, 0.0, "Created By:");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-800, -200, 0.0, "Maurice Aoun - 12200222");
	displayRasterText(-800, -285, 0.0, "Hassan Khalil - 12200383");
	displayRasterText(-800, -370, 0.0, "Karl Khattar Abi Nader - 12200056");
	displayRasterText(-800, -455, 0.0, "Jad Shreim - 12210056");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(500, -100, 0.0, "Presented to:");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(500, -200, 0.0, "Dr. Ali Abdallah");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-300, -550, 0.0, "Press ENTER to start the game");
	glFlush();
	glutSwapBuffers();
}

void startScreenDisplay()
{
	glLineWidth(10);
	//SetDisplayMode(MENU_SCREEN);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);               //Border
	glVertex2f(-750, -500);
	glVertex2f(-750, 550);
	glVertex2f(750, 550);
	glVertex2f(750, -500);
	glEnd();

	glLineWidth(1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
	glVertex2f(-200, 300);
	glVertex2f(-200, 400);
	glVertex2f(200, 400);
	glVertex2f(200, 300);
	glEnd();

	glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
	glVertex2f(-200, 50);
	glVertex2f(-200, 150);
	glVertex2f(200, 150);
	glVertex2f(200, 50);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
	glVertex2f(-200, -200);
	glVertex2f(-200, -100);
	glVertex2f(200, -100);
	glVertex2f(200, -200);
	glEnd();

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 150 && mouseY <= 200) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			alienLife1 = alienLife2 = 100;
			viewPage = GAME;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);

	displayRasterText(-100, 340, 0.4, "Start Game");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 30 && mouseY <= 80) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			viewPage = INSTRUCTIONS;
			printf("button pressed \n");
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-120, 80, 0.4, "Instructions");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= -90 && mouseY <= -40) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			mButtonPressed = false;
			exit(0);
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-100, -170, 0.4, "    Quit");
	glutPostRedisplay();
}

void backButton() {
	if (mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			viewPage = MENU;
			mButtonPressed = false;
			//instructionsGame = false;
			glutPostRedisplay();
		}
	}
	else glColor3f(1, 0, 0);
	displayRasterText(-1000, -550, 0, "Back");
}

void instructionsScreenDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(1, 0, 0);
	displayRasterText(-475, 550, 0.4, "INSTRUCTIONS");
	glColor3f(1, 0, 0);
	displayRasterText(-1000, 400, 0.4, "PLAYER 1");
	displayRasterText(200, 400, 0.4, "PLAYER 2");
	glColor3f(1, 1, 1);
	displayRasterText(-1100, 300, 0.4, "Key 'W' to move up.");
	displayRasterText(-1100, 200, 0.4, "Key 'S' to move down.");
	displayRasterText(-1100, 100, 0.4, "Key 'D' to move right.");
	displayRasterText(-1100, 0, 0.4, "Key 'A' to move left.");
	displayRasterText(100, 300, 0.4, "Key 'I' to move up.");
	displayRasterText(100, 200, 0.4, "Key 'K' to move down.");
	displayRasterText(100, 100, 0.4, "Key 'J' to move right.");
	displayRasterText(100, 0, 0.4, "Key 'L' to move left.");
	displayRasterText(-1100, -100, 0.4, "Key 'C' to shoot, Use 'w' and 's' to change direction.");
	displayRasterText(100, -100, 0.4, "Key 'M' to shoot, Use 'i' and 'k' to change direction.");
	//displayRasterText(-1100 ,-100 ,0.4 ,"The packet can be placed only when 's' is pressed before.");
	backButton();
	//if(previousScreen)
	//	nextScreen = false ,previousScreen = false; //as set by backButton()
}


void DrawSpaceshipBody(bool isPlayer1)
{
	if (isPlayer1)
		glColor3f(0.0f, 1.0f, 1.0f);			//BASE
	else
		glColor3f(1.0f, 0.0f, 1.0f);

	glPushMatrix();
	glScalef(70, 20, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPushMatrix();							//LIGHTS
	glScalef(3, 3, 1);
	glTranslated(-20, 0, 0);			//1
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//2
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//3
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//4
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//5
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//6
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//7
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//8
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//9
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);

	glPopMatrix();
}

void DrawSpaceshipDoom()
{
	glColor4f(0.7, 1, 1, 0.0011);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glScalef(35, 50, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

void DrawLaser(int x, int y, bool dir[]) {
	//glPushMatrix();
	int xend = -XMAX, yend = y;
	if (dir[0])
		yend = YMAX;
	else if (dir[1])
		yend = -YMAX;
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(xend, yend);
	glEnd();
	//glPopMatrix();
}

void SpaceshipCreate(int x, int y, bool isPlayer1) {
	glPushMatrix();
	glTranslated(x, y, 0);
	// if(!checkIfSpaceShipIsSafe() && alienLife1 ){
	// 	alienLife1-=10;
	// 	xStart -= 23;
	// }
	DrawSpaceshipDoom();
	glPushMatrix();
	glTranslated(4, 19, 0);
	glPopMatrix();
	DrawSpaceshipBody(isPlayer1);
	// DrawSpaceShipLazer();
	// if(mButtonPressed) {
	// 	DrawLazerBeam();
	// }
	glEnd();
	glPopMatrix();
}

void DisplayHealthBar1() {
	char temp1[40];
	glColor3f(1, 1, 1);
	sprintf(temp1, "  LIFE = %d", alienLife1);
	displayRasterText(-1100, 600, 0.4, temp1);
	glColor3f(1, 0, 0);
}

void DisplayHealthBar2() {
	char temp2[40];
	glColor3f(1, 1, 1);
	sprintf(temp2, "  LIFE = %d", alienLife2);
	displayRasterText(800, 600, 0.4, temp2);
	glColor3f(1, 0, 0);
}

void checkLaserContact(int x, int y, bool dir[], int xp, int yp, bool player1) {
	int xend = -XMAX, yend = y;
	xp += 8; yp += 8; // moving circle slightly up to fix laser issue
	if (dir[0])
		yend = YMAX;
	else if (dir[1])
		yend = -YMAX;

	// Here we find out if the laser(line) intersects with spaceship(circle)
	// by solving the equations for the same and finding the discriminant of the
	// quadratic equation obtained
	float m = (float)(yend - y) / (float)(xend - x);
	float k = y - m * x;
	int r = 50; // approx radius of the spaceship

	//calculating value of b, a, and c needed to find discriminant
	float b = 2 * xp - 2 * m * (k - yp);
	float a = 1 + m * m;
	float c = xp * xp + (k - yp) * (k - yp) - r * r;

	float d = (b * b - 4 * a * c); // discriminant for the equation
	printf("\nDisc: %f x: %d, y: %d, xp: %d, yp: %d", d, x, y, xp, yp);
	if (d >= 0) {
		if (player1)
			alienLife1 -= 5;
		else
			alienLife2 -= 5;

		printf("%d %d\n", alienLife1, alienLife2);
	}
}

void gameScreenDisplay()
{
	DisplayHealthBar1();
	DisplayHealthBar2();
	glScalef(2, 2, 0);

	if (alienLife1 > 0) {
		SpaceshipCreate(xOne, yOne, true);
		if (laser1) {
			DrawLaser(xOne, yOne, laser1Dir);
			checkLaserContact(xOne, yOne, laser1Dir, -xTwo, yTwo, true);
		}
	}
	else {
		viewPage = GAMEOVER;
	}

	if (alienLife2 > 0) {
		glPushMatrix();
		glScalef(-1, 1, 1);
		SpaceshipCreate(xTwo, yTwo, false);
		if (laser2) {
			DrawLaser(xTwo, yTwo, laser2Dir);
			checkLaserContact(xTwo, yTwo, laser2Dir, -xOne, yOne, false);
		}
		glPopMatrix();
	}
	else {
		viewPage = GAMEOVER;
	}

	if (viewPage == GAMEOVER) {
		xOne = xTwo = 500;
		yOne = yTwo = 0;
	}
}

void displayGameOverMessage() {
	glColor3f(1, 1, 0);
	char* message;
	if (alienLife1 > 0)
		message = "Game Over! Player 1 won the game";
	else
		message = "Game Over! Player 2 won the game";

	displayRasterText(-350, 600, 0.4, message);
}

void keyOperations() {
	if (keyStates[13] == true && viewPage == INTRO) {
		viewPage = MENU;
		printf("view value changed to %d", viewPage);
		printf("enter key pressed\n");
	}
	if (viewPage == GAME) {
		laser1Dir[0] = laser1Dir[1] = false;
		laser2Dir[0] = laser2Dir[1] = false;
		if (keyStates['c'] == true) {
			laser2 = true;
			if (keyStates['w'] == true) 	laser2Dir[0] = true;
			if (keyStates['s'] == true) 	laser2Dir[1] = true;
		}
		else {
			laser2 = false;
			if (keyStates['d'] == true) xTwo -= SPACESHIP_SPEED;
			if (keyStates['a'] == true) xTwo += SPACESHIP_SPEED;
			if (keyStates['w'] == true) yTwo += SPACESHIP_SPEED;
			if (keyStates['s'] == true) yTwo -= SPACESHIP_SPEED;
		}

		if (keyStates['m'] == true) {
			laser1 = true;
			if (keyStates['i'] == true) laser1Dir[0] = true;
			if (keyStates['k'] == true) laser1Dir[1] = true;
		}
		else {
			laser1 = false;
			if (keyStates['l'] == true) xOne += SPACESHIP_SPEED;
			if (keyStates['j'] == true) xOne -= SPACESHIP_SPEED;
			if (keyStates['i'] == true) yOne += SPACESHIP_SPEED;
			if (keyStates['k'] == true) yOne -= SPACESHIP_SPEED;
		}
	}
}

void display()
{
	//glClearColor(, 0 , 0, 1);
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	switch (viewPage)
	{
	case INTRO:
		introScreen();
		break;
	case MENU:
		startScreenDisplay();
		break;
	case INSTRUCTIONS:
		instructionsScreenDisplay();
		break;
	case GAME:
		gameScreenDisplay();
		//reset scaling values
		glScalef(1 / 2, 1 / 2, 0);
		break;
	case GAMEOVER:
		displayGameOverMessage();
		startScreenDisplay();
		break;
	}

	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}

// void reshape(GLint w, GLint h)
// {
// 	glViewport(0, 0, w, h);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	if(h>w)
// 	{
// 		gluOrtho2D(0, 500, ((float)h/(float)w)*(0), ((float)h/(float)w)*500);
// 	}
// 	else
// 	{
// 		gluOrtho2D(((float)w/(float)h)*(0), ((float)w/(float)h)*(500), 0, 500);
// 	}
// 	glMatrixMode(GL_MODELVIEW);
// 	glutPostRedisplay();
// }

void passiveMotionFunc(int x, int y) {

	//when mouse not clicked
	mouseX = float(x) / (m_viewport[2] / 1200.0) - 600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y) / (m_viewport[3] / 700.0) - 350.0);

	//Do calculations to find value of LaserAngle
	//somethingMovedRecalculateLaserAngle();
	glutPostRedisplay();
}

void mouseClick(int buttonPressed, int state, int x, int y) {

	if (buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();
}

void refresh() {
	glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("Space Shooter");
	init();
	//glutReshapeFunc(reshape);
	glutIdleFunc(refresh);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(passiveMotionFunc);
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	glutDisplayFunc(display);
	glutMainLoop();
}
