#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0
#include"game.h"
#include<vector>

using std::vector;

namespace runtime
{
	static float deltaTime;
	static 
	class CGfxOpenGL
	{
	private:
		int m_windowWidth;
		int m_windowHeight;

	public:
		CGfxOpenGL();
		virtual ~CGfxOpenGL();

		bool Init();
		bool Shutdown();

		void SetupProjection(int width, int height);

		void Prepare(float dt);
		void Render();
	};

	void PichCollision();
}

#endif