/*store each vertex in the file*/

#pragma once

struct Vertex{
	float x;
	float y;
	float z;
	double weight[20];
	/*reload cross operation*/
	Vertex cross(const Vertex& right)
	{
		Vertex result;
		result.x = y*right.z - z*right.y;
		result.y = z*right.x - x*right.z;
		result.z = x*right.y - y*right.x;
		return result;
	}
	const Vertex operator - (const Vertex& right) const
	{
		Vertex result;
		result.x = x - right.x;
		result.y = y - right.y;
		result.z = z - right.z;
		return result;
	}
	/*Reload + operator*/
	const Vertex operator + (const Vertex& right) const
	{
		Vertex result;
		result.x = x + right.x;
		result.y = y + right.y;
		result.z = z + right.z;
		return result;
	}
	/*Reload * operator to times a number*/
	const Vertex operator * (const float right) const
	{
		Vertex result;
		result.x = x*right;
		result.y = y*right;
		result.z = z*right;
		return result;
	}
	/*For normalized vector dot product use*/
	float dotProduct(const Vertex& right) const
	{
		float r;
		r = 1.0*x*right.x + 1.0*y*right.y + 1.0*z*right.z;
		return r;
	}
};
/*store each triangles in the file*/
struct Triangle{
	int v1;
	int v2;
	int v3;
};
struct Matrix{
	float elem[4][4];
	float value[4];
	/*Mat times another Mat function*/
	const Matrix operator *(const Matrix& right) const
	{
		Matrix result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.elem[i][j] = elem[i][0] * right.elem[0][j] + elem[i][1] * right.elem[1][j] + elem[i][2] * right.elem[2][j] + elem[i][3] * right.elem[3][j];
			}
		}
		return result;
	}
	/*Mat times a vertex and return another vertex*/
	const Vertex operator *(const Vertex& v) const
	{
		Vertex result;
		Matrix r;
		for (int i = 0; i < 4; i++)
		{
			r.value[i] = elem[i][0] * v.x + elem[i][1] * v.y + elem[i][2] * v.z + elem[i][3];
		}
		for (int i = 0; i < 3; i++)
		{
			r.value[i] = r.value[i] / r.value[3];
		}
		result.x = r.value[0];
		result.y = r.value[1];
		result.z = r.value[2];
		return result;
	}
};
struct Weight{
	int num;
	double w;
	int ske;
};

