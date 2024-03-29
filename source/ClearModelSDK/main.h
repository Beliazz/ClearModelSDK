#ifndef Main_H__
#define Main_H__

#include <Windows.h>

//STL
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#include <vector>

//XML
#include "tinystr.h"
#include "tinyxml.h"
#pragma comment(lib,"tinyxml.lib")

//FBX
#include <fbxsdk.h>
#pragma comment(lib,"fbxsdk-2012.2-mdd.lib")

using namespace std;

//Colors
class Color
{
public:
	Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}
	Color(float red, float green, float blue, float alpha) 
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	Color(float *color)
	{
		r = color[0];
		g = color[1];
		b = color[2];
		a = color[3];
	}
	Color(string color)
	{
		stringstream stm(color);
		stm >> r >> g >> b >> a;
	}
	Color(KFbxColor color)
	{
		r = (float)color.mRed;
		g = (float)color.mGreen;
		b = (float)color.mBlue;
		a = (float)color.mAlpha;
	}

	string str()
	{
		stringstream stm;

		stm << r << " ";
		stm << g << " ";
		stm << b << " ";
		stm << a << " ";

		return stm.str().c_str();
	}

private:
	float r;
	float g;
	float b;
	float a;
};

//Vectors
class Vector
{
public:
	Vector()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	Vector(float X, float Y, float Z, float W) 
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
	Vector(float *vec)
	{
		x = vec[0];
		y = vec[1];
		z = vec[2];
		w = vec[3];
	}
	Vector(string vec)
	{
		stringstream stm(vec);
		stm >> x >> y >> z >> w;
	}

	Vector( KFbxVector4 vector)
	{
		x = (float)vector.mData[0];
		y = (float)vector.mData[1];
		z = (float)vector.mData[2];
		w = (float)vector.mData[3];
	}

	Vector( KFbxVector2 vector)
	{
		x = (float)vector.mData[0];
		y = (float)vector.mData[1];
		z = 1.0f;
		w = 1.0f;
	}

	string str()
	{
		stringstream stm;

		stm << x << " ";
		stm << y << " ";
		stm << z << " ";
		
		return stm.str().c_str();
	}


private:
	float x;
	float y;
	float z;
	float w;
};

//Vertex
struct Vertex
{
	Vertex()
	{
		groupIndex	= 0;
		pos			= Vector();
		normal		= Vector();
		tex			= Vector();
		tangent		= Vector();
		biNormals	= Vector();
		boneWeights = Vector();
		color		= Color();

		boneIndices[0] = 0;
		boneIndices[1] = 0;
		boneIndices[2] = 0;
		boneIndices[3] = 0;
	}

	DWORD groupIndex;

	Vector pos;
	Vector normal;
	Vector tex;
	Color  color;
	Vector tangent;
	Vector biNormals;
	Vector boneWeights;
	UINT   boneIndices[4];
};

class xmlText
{
	TiXmlText* pTiXmlText;

	public:
		xmlText( float value)
		{
			stringstream stm;
			stm << value;

			pTiXmlText = new TiXmlText( stm.str().c_str() );
		}
		xmlText( const char* value)
		{
			pTiXmlText = new TiXmlText( value );
		}
		xmlText( string value)
		{
			pTiXmlText = new TiXmlText( value.c_str() );
		}
		xmlText( Color value)
		{
			pTiXmlText = new TiXmlText( value.str().c_str() );
		}
		xmlText( KFbxMatrix matrix )
		{
			stringstream stm("");

			const DOUBLE* pDoubles = (const DOUBLE*)matrix.mData;
			for( DWORD i = 0; i < 16; ++i )
			{
				stm << (FLOAT)pDoubles[i] << " ";
			}

			pTiXmlText = new TiXmlText( stm.str().c_str() );
		}
		xmlText( KFbxXMatrix matrix )
		{
			stringstream stm("");

			const DOUBLE* pDoubles = (const DOUBLE*)matrix.mData;
			for( DWORD i = 0; i < 16; ++i )
			{
				stm << (FLOAT)pDoubles[i] << " ";
			}

			pTiXmlText = new TiXmlText( stm.str().c_str() );
		}

		operator TiXmlText*()
		{
			return pTiXmlText;
		}
};

//Model
#include "Definitions.h"
#include "ModelElement.h"
#include "SceneElements/EmptyNode.h"
#include "GlobalTimeSettings/GlobalTimeSettings.h"
#include "GlobalLightSettings/GlobalLightSettings.h"
#include "GlobalCameraSettings/GlobalCameraSettings.h"
#include "SceneElements/CameraNode.h"
#include "SceneElements/LightNode.h"
#include "SceneElements/LODGroudNode.h"
#include "SceneElements/MeshNode.h"
#include "SceneElements/MarkerNode.h"
#include "SceneElements/NurbNode.h"
#include "SceneElements/PatchNode.h"
#include "SceneElements/SkeletonNode.h"
#include "ModelSDK.h"

#endif