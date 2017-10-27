#pragma once
#include<vector>
#include<iostream>
#include"define.h"
#include"String.h"

#define GAME_PI 3.1415926f//圆周率

#define GAME_ACCURACY 0.001f//3位小数精度
#define GAME_ACCURACY_POW 0.00001f//9位小数精度

#define GAME_COLLIS_TYPE_CUB 0x0001//长方体碰撞监测
#define GAME_COLLIS_TYPE_SPHARE 0x0002//球形碰撞监测

using namespace myCode;
using std::cout;
using std::endl;
using std::vector;

namespace game 
{
	class Vector3;
	class Cub;
	class GameObject3;
	class ShapeCollis;
	class Collision;
	//更新函数,函数指针
	typedef void(*CubUpdateHandle)(Cub &cub);
	typedef void(*ShapeCollisUpdateHandle)(ShapeCollis&);
	typedef void(*CollisionUpdateHandle)(Collision&);
	typedef void(*GameObjectUpdateHandle)(GameObject3&);
	//点类
	class Vector3
	{
	public:
		struct
		{
			union
			{
				float data[3];
				struct
				{
					float x;
					float y;
					float z;
				};
			};

		};
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& v);
		Vector3(const Vector3* v);
		float LengthPow();
		float operator*(const Vector3 &v);
		Vector3* operator+(const Vector3 &v);
		Vector3* operator-(const Vector3 &v);
		void operator=(const Vector3 &v);
		bool operator==(const Vector3 &v);
		Vector3* GetUnitVector();
		void Set(float x, float y, float z);
		void Translate(const Vector3 &v);
		void Rota(Vector3 &v, float angle);
		void Show();
		bool Equal(const Vector3 &v);
	};
	//游戏对象基类
	class GameObject3
	{
	public:
		String* taget;
		Vector3* center;
		Collision* col=nullptr;
		vector<GameObjectUpdateHandle> update;

		GameObject3(Vector3 *cen, char *name);
		GameObject3(Vector3* cen, String *name);
		GameObject3(const Vector3& v, const String& str);
		GameObject3();
		virtual ~GameObject3();
		virtual void Update();
		virtual void Translate(const Vector3 &v);
		virtual void Rota(Vector3 &v, float angle);
		virtual void PushCollision(Collision *col);
		void operator+=(GameObjectUpdateHandle);
		void operator-=(GameObjectUpdateHandle);
	};
	//碰撞检测形状基类
	class ShapeCollis
	{
	public:
		Ushort type;
		vector<ShapeCollisUpdateHandle> update;

		ShapeCollis();
		ShapeCollis(Ushort type);

		virtual void Update();
		virtual void Rota(Vector3 &v, float angle);
		virtual void Translate(const Vector3 &v);
		void operator+=(ShapeCollisUpdateHandle);
		void operator-=(ShapeCollisUpdateHandle);
		virtual ~ShapeCollis();
	};
	//长方体碰撞监测
	class Cub:public ShapeCollis
	{
	private:
		Vector3 *buffer = new Vector3[3];
		std::vector<CubUpdateHandle> update;
		float *info = new float[3];
		bool reFlag = false;
		Uint count=0;
		void initBuffer();	
	public:
		Vector3 *data = new Vector3[5];
		Cub();
		Cub(Vector3 &center, float px, float py, float pz);
		~Cub();
		Vector3* ToLocalVector(Vector3 &v);
		bool IsInit(Vector3 &v);
		virtual void Translate(const Vector3 &v);
		virtual void Rota(Vector3 &v, float angle);
		void Reinit();
		virtual void Update(float deltaTime);
		void operator+=(CubUpdateHandle);
		void operator-=(CubUpdateHandle);
		void Show();
	};
	//碰撞监测类
	class Collision
	{
	public:
		ShapeCollis *shape;
		vector<CollisionUpdateHandle> updata;

		Collision();
		Collision(ShapeCollis *sp);
		~Collision();
		void operator+=(CollisionUpdateHandle);
		void operator-=(CollisionUpdateHandle);
		void Update();
		void Translate(const Vector3 &v);
		void Rota(Vector3 &v, float angle);
	};
} 