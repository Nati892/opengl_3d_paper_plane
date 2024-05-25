#include "Scene.h"

//macros
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "drawPaperPlane"
#define AXISCOUNT 30
#define LINE_SIZE 0.5f


int scale_x_start = -960;
int scale_x_end = 960;
int scale_y_start = -540;
int scale_y_end = 540;
int scale_z_start = 960;
int scale_z_end = -960;

int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 1920;
int CurrentSceneHeight = 1080;

int WindowRectBounds_x = 0;
int WindowRectBounds_y = 0;
int WindowRectBounds_width = 0;
int WindowRectBounds_height = 0;

void CleanupAndExit()
{
	exit(0);
}

void DrawBackgroundWithColor(float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(-10000, -10000, -100);
	glVertex3f(10000, -10000, -100);
	glVertex3f(10000, 10000, -100);
	glVertex3f(-10000, 10000, -100);
	glEnd();
	//glRectf(scale_x_start, scale_y_start, scale_x_end, scale_y_end);
}

void Draw3DAxis()
{
	//x axis red
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();

	//draw axis count
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -AXISCOUNT; i < AXISCOUNT; i++)
	{
		glVertex3f(i, -(LINE_SIZE / 2), 0);
		glVertex3f(i, (LINE_SIZE / 2), 0);
	}
	glEnd();

	//y axis green
	glColor3f(0, 1, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(0, -500, 0);
	glVertex3f(0, 500, 0);
	glEnd();

	//draw axis count
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -AXISCOUNT; i < AXISCOUNT; i++)
	{
		glVertex3f(-(LINE_SIZE / 2), i, 0);
		glVertex3f((LINE_SIZE / 2), i, 0);
	}
	glEnd();

	//z axis blue
	glColor3f(0, 0, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();

	//draw axis count
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -AXISCOUNT; i < AXISCOUNT; i++)
	{
		glVertex3f(-(LINE_SIZE / 2), 0, i);
		glVertex3f((LINE_SIZE / 2), 0, i);
	}
	glEnd();
}

//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;

	WindowRectBounds_x = StartPos_X;
	WindowRectBounds_y = StartPos_Y;
	WindowRectBounds_width = finalW;
	WindowRectBounds_height = finalH;
}


//IMPORTANT NOTE!
//
//in the mmn they asked for these vertices {(0,0), (0,3), (2,0)}
//but in the drawing they asked for these {(0,0), (3,0), (0,2)}
//I went with the written ones : {(0,0), (0,3), (2,0)}
//so it might look different from the drawing in the course booklet

void drawWing()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to draw only outlines
	glColor3f(0.0f, 0.0f, 0.0f); // Outline color black
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(0, 3, 0);
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//draw fill
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.5f, 0.5f);//gray fill
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(0, 3, 0);
	glEnd();

}

void draw2wings()
{
	glTranslatef(2, 0, 0);
	glTranslatef(0, 03, 0);
	glRotatef(270, 0, 0, 1);
	glScalef(2.25f, 1, 1);
	drawWing();

	//do reverse operations
	glScalef(1 / 2.25f, 1, 1);
	glRotatef(-270, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(-2, 0, 0);

	//do the same and mirror over y axis
	glTranslatef(2, 0, 0);
	glScalef(-1, 1, 1);
	glTranslatef(0, 03, 0);
	glRotatef(270, 0, 0, 1);
	glScalef(2.25f, 1, 1);
	drawWing();
}



void drawPaperPlane()
{
	glPushMatrix();
	glTranslatef(2, 3, 0);//move aprox to same position as picture
	glScalef(-1, 1, 1);//mirror to be the back one - want to draw the farther one first
	glRotatef(300, 0, 1, 0);//fold
	glRotatef(270, 0, 0, 1);//rotate to match y axis
	glScalef(2.25f, 1, 1);//stretch it 

	drawWing();

	glPopMatrix();//remove all transfroms
	//do the same and mirror over y axis
	glTranslatef(2, 3, 0);//move aprox to position as picture
	glRotatef(300, 0, 1, 0);//fold
	glRotatef(270, 0, 0, 1);//rotate
	glScalef(2.25f, 1, 1);//stretch

	drawWing();

}


void DrawScene1()
{
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1, 1, -1, 1, 0.1, 2000.0);
	glOrtho(-6, 6, -10, 10, -1, 1000);//orthogonal shows diensions better


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawBackgroundWithColor(1, 1, 1);
	gluLookAt(
		0, 0, 0.5,
		0, 0, 0,
		0, 1, 0);

	Draw3DAxis();
	drawWing();
}


void DrawScene2()
{
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1, 1, -1, 1, 0.1, 2000.0);
	glOrtho(-6, 6, -10, 10, -1, 1000);//orthogonal shows diensions better


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawBackgroundWithColor(1, 0.4f, 0.7f);
	gluLookAt(
		0, 0, 0.5,
		0, 0, 0,
		0, 1, 0);

	Draw3DAxis();
	draw2wings();
}

void DrawScene3()
{
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1, 1, -1, 1, 0.1, 2000);
	glOrtho(-15, 15, -12, 15, -20, 200000);//went with ortho for this one because it looked better this way

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawBackgroundWithColor(1, 1, 0);
	gluLookAt(
		2, -2, 1,
		0, 0, 0,
		0, 0, 1);

	Draw3DAxis();
	drawPaperPlane();
}



//Redraw callback
void DisplayCallback()
{
	//draw all three scenes on one window
	FixAspectRatio();
	glViewport(WindowRectBounds_x, WindowRectBounds_y, WindowRectBounds_width / 3, WindowRectBounds_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawScene1();

	glViewport(WindowRectBounds_width / 3, WindowRectBounds_y, WindowRectBounds_width / 3, WindowRectBounds_height);
	DrawScene2();

	glViewport(WindowRectBounds_width * 2 / 3, WindowRectBounds_y, WindowRectBounds_width / 3, WindowRectBounds_height);
	DrawScene3();

	glutSwapBuffers();
}



//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;
	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;
	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);
}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{
	switch (c)
	{

	case 'q':
	case 'Q':
		exit(0);
	}
}

//my initiation function
void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1920;
	CurrentSceneHeight = 1080;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth;
	AspectRatioDenominator = CurrentSceneHeight;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(MY_HEADER);
}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);
	glutKeyboardFunc(KeyboardEventCallback);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{

	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();
}