
#include <Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include <math.h>

#include "CGfxOpenGL.h"


//全局常量声明
//颜色

// disable implicit float-double casting
#pragma warning(disable:4305)

namespace runtime
{
	void PichCollision()
	{


	}

	CGfxOpenGL::CGfxOpenGL()
	{
	}

	CGfxOpenGL::~CGfxOpenGL()
	{
	}

	bool CGfxOpenGL::Init()
	{
		// clear to black background
		glClearColor(0.0, 0.0, 0.0, 0.0);

		m_angle = 0.0f;

		return true;
	}

	bool CGfxOpenGL::Shutdown()
	{
		return true;
	}

	void CGfxOpenGL::SetupProjection(int width, int height)
	{
		if (height == 0)                    // don't want a divide by zero
		{
			height = 1;
		}

		glViewport(0, 0, width, height);        // reset the viewport to new dimensions
		glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
		glLoadIdentity();                       // reset projection matrix

												// calculate aspect ratio of window
		gluPerspective(100.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);             // set modelview matrix
		glLoadIdentity();                       // reset modelview matrix

		m_windowWidth = width;
		m_windowHeight = height;
		glEnable(GL_CULL_FACE);
	}

	void CGfxOpenGL::Prepare(float dt)
	{
		runtime::deltaTime = dt;
	}

	void CGfxOpenGL::Render()
	{
		float dt = (float)deltaTime / 1000.0f;

		// clear screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glClearColor(0.1f,0.2f,0.4, 0.5f);
		// move back 5 units and rotate about all 3 axes


		// lime greenish color

		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		glEnable(GL_LIGHT1);

		Vertex4f globalAmbient = { 0.0f,0.7f,0.8f,1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient.data);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -10.0f);
		glRotatef(this->m_angle, 1.0f, 0.0f, 0.0f);
		glRotatef(this->m_angle, 0.0f, 1.0f, 0.0f);
		glRotatef(this->m_angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);

		glVertex3f(10.0f, 0.0f, -10.0f);
		glVertex3f(0.0f, 10.0f, -10.0f);
		glVertex3f(0.0f, 0.0f, -10.0f);

		glEnd();
		glPopMatrix();
	}
}