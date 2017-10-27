#include"game.h"
#include<math.h>
namespace game
{
	Vector3::Vector3() :x(0.0f), y(0.0f), z(0.0f)
	{
	}
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}
	Vector3::Vector3(const Vector3 &v)
	{
		memcpy(data, v.data, sizeof(data));
	}
	Vector3::Vector3(const Vector3* v)
	{
		memcpy(data, v->data, sizeof(data));
	}
	float Vector3::LengthPow()
	{
		return x*x + y*y + z*z;
	}
	float Vector3::operator*(const Vector3 &v)
	{
		return x*v.x + y*v.y + z*v.z;
	}
	Vector3* Vector3::operator+(const Vector3 &v)
	{
		return new Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3* Vector3::operator-(const Vector3 &v)
	{
		return new Vector3(x - v.x, y - v.y, z - v.z);
	}
	bool Vector3::operator==(const Vector3 &v)
	{
		return Equal(v);
	}
	void Vector3::operator=(const Vector3 &v)
	{
		memcpy(data, v.data, sizeof(data));
	}
	Vector3* Vector3::GetUnitVector()
	{
		float len = sqrtf(this->LengthPow());
		Vector3 *re = new Vector3(x / len, y / len, z / len);
		return re;
	}
	void Vector3::Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Vector3::Translate(const Vector3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void Vector3::Rota(Vector3 &vector, float angle)
	{
		Vector3 *v0 = vector.GetUnitVector();
		float temp = v0->x*x + v0->y*y + v0->z*z;
		float cosT = cosf(angle);
		float sinT = sinf(angle);
		float ncosT = 1 - cosT;
		float u = x;
		float v = y;
		float w = z;
		x = u*cosT + (v0->y*w - v0->z*v)*sinT + v0->x*temp*ncosT;
		y = v*cosT + (v0->z*u - v0->x*w)*sinT + v0->y*temp*ncosT;
		z = w*cosT + (v0->x*v - v0->y*u)*sinT + v0->z*temp*ncosT;
		delete v0;
	}
	void Vector3::Show()
	{
		std::cout << " x:" << x << " y:" << y << " z:" << z << endl;
	}
	bool Vector3::Equal(const Vector3 &v)
	{
		if (fabsf(x - v.x) <= GAME_ACCURACY&&fabsf(y - v.y) <= GAME_ACCURACY&&fabsf(z - v.z) <= GAME_ACCURACY)
		{
			return true;
		}
		return false;
	}
	GameObject3::GameObject3(const Vector3 &v, const String& str)
	{
		taget = new String(str);
		center = new Vector3(v);
	}
	GameObject3::GameObject3()
	{
		center = new Vector3(0.0f, 0.0f, 0.0f);
		taget = new String("test");
	}
	GameObject3::GameObject3(Vector3 *cen, char *name)
	{
		if (cen != nullptr)
		{
			center = new Vector3(cen->x, cen->y, cen->z);
		}
		else
		{
			center = new Vector3(0.0f, 0.0f, 0.0f);
		}
		taget = new String(name);
	}
	GameObject3::GameObject3(Vector3* cen, String *name)
	{
		if (cen != nullptr)
		{
			center = new Vector3(cen->x, cen->y, cen->z);
		}
		else
		{
			center = new Vector3(0.0f, 0.0f, 0.0f);
		}
		taget = new String(name->Str());
	}
	GameObject3::~GameObject3()
	{
		delete center;
		delete taget;
	}
	void GameObject3::Rota(Vector3 &v, float angle)
	{
		center->Rota(v, angle);
		col->Rota(v, angle);
	}
	void GameObject3::PushCollision(Collision * col)
	{
		if (this->col != nullptr)
		{
			delete this->col;
		}
		this->col = col;
	}
	void GameObject3::Translate(const Vector3 &v)
	{
		center->Translate(v);
		col->Translate(v);
	}
	void GameObject3::Update()
	{
		for (Ushort i = 0; i < update.size(); i++)
		{
			update[i](*this);
		}
		col->Update();
	}
	void GameObject3::operator+=(GameObjectUpdateHandle handle)
	{
		update.push_back(handle);
	}
	void GameObject3::operator-=(GameObjectUpdateHandle handle)
	{
		vector<GameObjectUpdateHandle>::iterator it;
		for (it = update.begin(); it != update.end();)
		{
			if (*it == handle)
			{
				it = update.erase(it);
			}
			else
			{
				it++;
			}
		}
	}


	ShapeCollis::ShapeCollis()
	{
		type = GAME_COLLIS_TYPE_CUB;
	}
	ShapeCollis::ShapeCollis(Ushort type)
	{
		this->type = type;
	}
	ShapeCollis::~ShapeCollis()
	{
		update.clear();
	}
	void ShapeCollis::operator+=(ShapeCollisUpdateHandle handle)
	{
		update.push_back(handle);
	}
	void ShapeCollis::operator-=(ShapeCollisUpdateHandle handle)
	{
		vector<ShapeCollisUpdateHandle>::iterator it;
		for (it = update.begin(); it != update.end();)
		{
			if (*it == handle)
			{
				it = update.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	void ShapeCollis::Update()
	{
		for (Ushort i = 0; i < update.size(); i++)
		{
			update[i](*this);
		}
	}
	void ShapeCollis::Translate(const Vector3 &v)
	{

	}
	void ShapeCollis::Rota(Vector3 &v, float angle)
	{

	}

	Cub::Cub()
	{
		data[0].Set(0.0f, 0.0f, 0.0f);
		data[1].Set(1.0f, 0.0f, 0.0f);
		data[2].Set(0.0f, 1.0f, 0.0f);
		data[3].Set(0.0f, 0.0f, 1.0f);
		data[4].Set(0.5f, 0.5f, 0.5f);
		initBuffer();
		info[0] = 0.5f; 
		info[1] = 0.5f;
		info[2] = 0.5f;
		type = GAME_COLLIS_TYPE_CUB;
	}
	Cub::Cub(Vector3 &center, float px, float py, float pz)
	{
		float le = px / 2;
		float wi = py / 2;
		float we = pz / 2;
		data[0].Set(center.x - le, center.y - wi, center.z - we);
		data[1].Set(center.x + le, center.y - wi, center.z - we);
		data[2].Set(center.x - le, center.y + wi, center.z - we);
		data[3].Set(center.x - le, center.y - wi, center.z + we);
		data[4].Set(center.x, center.y, center.z);
		initBuffer();
		info[0] = le;
		info[1] = wi;
		info[2] = we;
		type = GAME_COLLIS_TYPE_CUB;
	}
	Cub::~Cub()
	{
		delete[] data;
		delete[] buffer;
		delete[] info;
	}
	Vector3* Cub::ToLocalVector(Vector3 &v)
	{
		Vector3 *v_0 = v - data[0];
		Vector3 *re = new Vector3();
		re->x = *v_0*buffer[0] >= 0.0f ? v_0->x : -v_0->x;
		re->y = *v_0*buffer[1] >= 0.0f ? v_0->y : -v_0->y;
		re->z = *v_0*buffer[2] >= 0.0f ? v_0->z : -v_0->z;
		return re;
	}
	bool Cub::IsInit(Vector3 &v)
	{
		bool flag = false;
		Vector3 *v0 = ToLocalVector(v);
		if (v0->x >= 0 && v0->x <= buffer[0].x&&v0->y >= 0 && v0->y <= buffer[1].y&&v0->z >= 0 && v0->z <= buffer[2].z)
		{
			flag = true;
		}
		delete v0;
		return flag;
	}
	void Cub::initBuffer()
	{
		buffer[0].Set(data[1].x-data[0].x,data[1].y-data[0].y,data[1].z-data[0].z);
		buffer[1].Set(data[2].x - data[0].x, data[2].y - data[0].y, data[2].z - data[0].z);
		buffer[2].Set(data[3].x - data[0].x, data[3].y - data[0].y, data[3].z - data[0].z);
	}
	void Cub::Reinit()
	{
		if (fabsf(sqrtf(buffer[0].LengthPow())-info[0]*2) >= GAME_ACCURACY)
		{
			reFlag = true;
			data[0].Set(data[4].x - info[0], data[4].y - info[1], data[4].z - info[2]);
			data[1].Set(data[4].x + info[0], data[4].y - info[1], data[4].z - info[2]);
			data[2].Set(data[4].x - info[0], data[4].y + info[1], data[4].z - info[2]);
			data[3].Set(data[4].x - info[0], data[4].y - info[1], data[4].z + info[2]);
			initBuffer();
			cout << "re" << endl;
		}

	}
	void Cub::Translate(const Vector3 &v)
	{
		for (Ushort i = 0; i < 5; i++)
		{
			data[i].Translate(v);
		}
	}
	void Cub::Rota(Vector3 &v, float angle)
	{
		for (Ushort i = 0; i < 5; i++)
		{
			data[i].Rota(v, angle);
		}
		count++;
		if (count >= 20000)
		{
			Reinit();
			count = 0;
		}
		if (!reFlag)
		{
			initBuffer();
		}
		else
		{
			reFlag = false;
		}
	}
	void Cub::Update(float deltaTime)
	{
		for (Ushort i = 0; i < update.size(); i++)
		{
			update[i](*this);
		}
	}
	void Cub::operator+=(CubUpdateHandle handle)
	{
		update.push_back(handle);
	}
	void Cub::operator-=(CubUpdateHandle handle)
	{
		std::vector<CubUpdateHandle>::iterator it;
		for (it = update.begin(); it != update.end();)
		{
			if (*it = handle)
			{
				it = update.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	void Cub::Show()
	{
		cout << "center:";
		data[4].Show();
		cout << "other:";
		data[0].Show();
		data[1].Show();
		data[2].Show();
		data[3].Show();
	}

	Collision::Collision()
	{
		shape = new Cub();
	}
	Collision::Collision(ShapeCollis *sp)
	{
		shape = sp;
	}
	void Collision::Update()
	{
		for (Ushort i = 0; i < updata.size(); i++)
		{
			updata[i](*this);
		}
		shape->Update();
	}
	void Collision::Translate(const Vector3 &v)
	{
		shape->Translate(v);
	}
	void Collision::Rota(Vector3 &v, float angle)
	{
		shape->Rota(v, angle);
	}
	void Collision::operator+=(CollisionUpdateHandle handle)
	{
		updata.push_back(handle);
	}
	void Collision::operator-=(CollisionUpdateHandle handle)
	{
		vector<CollisionUpdateHandle>::iterator it;
		for (it = updata.begin(); it != updata.end();)
		{
			if (*it == handle)
			{
				it = updata.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	Collision::~Collision()
	{
		delete shape;
		updata.clear();
	}
}