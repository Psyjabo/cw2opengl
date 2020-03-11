#include "MyScene.h"

int height;
int width;


void reshape(int _width, int _height)
{
	// update global dimension variables
	width = _width;
	height = _height;
	// calculate new aspect ratio
	GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();     // reset matrix
	gluPerspective(45.0, aspect, 1, 1000);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
}

void setup()
{
	width = 600;                                   // initialise global window variables
	height = 400;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("My Scene");                   // create and show window (named MyScene)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}

void draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);                   // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
	glLoadIdentity();                                   // reset drawing

	glPushMatrix();
	glTranslatef(0.f, 0.f, -3.f);                     // move drawing further back in the scene

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-.5f, -.5f, 0.f);
	glVertex3f(-.5f, .5f, 0.f);
	glVertex3f(.5f, -.5f, 0.f);
	glVertex3f(.5f, .5f, 0.f);
	glEnd();

	glColor3f(0.3f, 0.3f, 0.3f);
	glutSolidTeapot(0.4);


	glPopMatrix();

	spotlight();



	checkGLError();
	glutSwapBuffers();                                  // execute all commands, swap buffers
	glutPostRedisplay();
}


void spotlight()
{
	// Set lighting effect colours and positional parameter
	float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
	float diffuse[] = { .8f, .8f, .5f, 1.f };      // diffuse light (50% white)
	float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
	float position[] = { 0.f, 0.f, 0.f, -5.f };      // directional light (w = 0)
	float spDirParam[] = { 0.f, 0.f, -1.f };
	// Attach properties to single light source (GL_LIGHT0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
	glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spDirParam );	
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.f);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 5.f);
	// Enable this lighting effects
	glEnable(GL_LIGHTING);  // enable scene lighting (required to enable a light source)
	glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)    
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // Initialise GL environment
	setup();                        // Call additional initialisation commands
	glutDisplayFunc(draw);          // Register scene to render contents of draw() function
	checkGLError();                 // Check any OpenGL errors in initialisation
	glutReshapeFunc(reshape);
	glutMainLoop();                 // Begin rendering sequence
	return 0;
}

void checkGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}