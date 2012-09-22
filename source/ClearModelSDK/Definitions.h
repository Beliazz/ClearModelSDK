#ifndef DEFINITION_H__
#define DEFINITION_H__

#include "ClearModelSDK.h"

namespace ClearModelSDK
{
	//Colors
	class CLEARMODELSDK_API Color
	{
	public:
		Color()
		{
			m_data[0] = 0.0f;
			m_data[1] = 0.0f;
			m_data[2] = 0.0f;
			m_data[3] = 0.0f;
		}
		Color(float red, float green, float blue, float alpha) 
		{
			m_data[0] = red;
			m_data[1] = green;
			m_data[2] = blue;
			m_data[3] = alpha;
		}
		Color(float *color)
		{
			m_data[0] = color[0];
			m_data[1] = color[1];
			m_data[2] = color[2];
			m_data[3] = color[3];
		}

		Color(string color)
		{
			stringstream stm(color);
			stm >> m_data[0] >> m_data[1] >> m_data[2] >> m_data[3];
		}

		Color(stringstream &stm)
		{
			stm >> m_data[0] >> m_data[1] >> m_data[2] >> m_data[3];
		}

		string str()
		{
			stringstream stm;

			stm << m_data[0] << " ";
			stm << m_data[1] << " ";
			stm << m_data[2] << " ";
			stm << m_data[3] << " ";

			return stm.str().c_str();
		}

		float* GetArray()
		{
			return m_data;
		}

	private:
		float m_data[4];
	};

	//Vectors
	class CLEARMODELSDK_API Vector
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

		Vector(stringstream &stm)
		{
			stm >> x >> y >> z >> w;
		}

		string str()
		{
			stringstream stm;

			stm << x << " ";
			stm << y << " ";
			stm << z << " ";
			stm << w << " ";

			return stm.str().c_str();
		}

		float x;
		float y;
		float z;
		float w;
	};

	class CLEARMODELSDK_API VectorUINT
	{
	public:
		VectorUINT()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		VectorUINT(UINT X, UINT Y, UINT Z, UINT W) 
		{
			x = X;
			y = Y;
			z = Z;
			w = W;
		}
		VectorUINT(UINT *vec)
		{
			x = vec[0];
			y = vec[1];
			z = vec[2];
			w = vec[3];
		}
		VectorUINT(string vec)
		{
			stringstream stm(vec);
			stm >> x >> y >> z >> w;

			w = 0;
		}

		string str()
		{
			stringstream stm;

			stm << (int)x << " ";
			stm << (int)y << " ";
			stm << (int)z << " ";
			stm << (int)w << " ";

			return stm.str().c_str();
		}


		UINT x;
		UINT y;
		UINT z;
		UINT w;
	};

	class CLEARMODELSDK_API Vector3
	{
	public:
		Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		Vector3(float X, float Y, float Z) 
		{
			x = X;
			y = Y;
			z = Z;
		}
		Vector3(float *vec)
		{
			x = vec[0];
			y = vec[1];
			z = vec[2];
		}
		Vector3(string vec)
		{
			stringstream stm(vec);
			stm >> x >> y >> z;
		}

		Vector3(stringstream &stm)
		{
			stm >> x >> y >> z;
		}

		string str()
		{
			stringstream stm;

			stm << x << " ";
			stm << y << " ";
			stm << z << " ";

			return stm.str().c_str();
		}

		float x;
		float y;
		float z;
	};

	class CLEARMODELSDK_API Vector2
	{
	public:
		Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		Vector2(float X, float Y, float Z, float W) 
		{
			x = X;
			y = Y;
		}
		Vector2(float X, float Y) 
		{
			x = X;
			y = Y;
		}
		Vector2(float *vec)
		{
			x = vec[0];
			y = vec[1];
		}
		Vector2(string vec)
		{
			stringstream stm(vec);
			stm >> x >> y;
		}
		Vector2(stringstream &stm)
		{
			stm >> x >> y;
		}

		string str()
		{
			stringstream stm;

			stm << x << " ";
			stm << y << " ";

			return stm.str().c_str();
		}

		float x;
		float y;
	};

	//Vertex
	struct CLEARMODELSDK_API Vertex
	{
		Vertex()
		{
			boneIndices[0] = 0;
			boneIndices[1] = 0;
			boneIndices[2] = 0;
			boneIndices[3] = 0;
		}

		Vector pos;
		Vector normal;
		Vector tex;
		Color  color;
		Vector tangent;
		Vector biNormals;
		Vector boneWeights;
		UINT   boneIndices[4];
	};

	//Matrix
	struct CLEARMODELSDK_API Matrix
	{
		Matrix()
		{
			for (unsigned int i = 0; i < 16 ; i++)
			{
				m_data[i] = 0;
			}
		}
		Matrix( float* data)
		{
			memcpy( &m_data[0], &data[0], sizeof(float)*16 );
		}
		Matrix( stringstream &stm )
		{
			for (unsigned int i = 0; i < 16 ; i++)
			{
				stm >> m_data[i];	
			}
		}

		Matrix( string value )
		{
			stringstream stm(value);

			for (unsigned int i = 0; i < 16 ; i++)
			{
				stm >> m_data[i];	
			}
		}

		string str()
		{
			stringstream stm;

			for (unsigned int i = 0; i < 16 ; i++)
			{
				stm << m_data[i] << " ";
			}
			return stm.str();
		}

		float m_data[16];
	};

	//xmlText
	class CLEARMODELSDK_API xmlText
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
		xmlText( Vector value)
		{
			pTiXmlText = new TiXmlText( value.str().c_str() );
		}
		xmlText( Matrix	value)
		{
			pTiXmlText = new TiXmlText( value.str().c_str() );
		}
		
		operator TiXmlText*()
		{
			return pTiXmlText;
		}
	};

	//SaveTyps
	enum  CLEARMODELSDK_API SaveType
	{
		ASCII,
		XML,
		BINARY,
	};

	//FileTyps
	enum CLEARMODELSDK_API LoadType
	{
		BCX,
		BCA,
		BCB,
		UNSUPPORTED,
	};

	struct xmlConverter
	{ 
		stringstream m_sdata;

		xmlConverter( string var )
		{
			m_sdata = stringstream(var);
		}

		xmlConverter( TiXmlElement* var )
		{
			m_sdata = stringstream(var->Value());
		}

		xmlConverter( TiXmlNode* var )
		{
			m_sdata = stringstream(var->Value());
		}

		operator float()
		{
			float result;
			m_sdata >> result;
			return result;
		}

		operator int()
		{
			int result;
			m_sdata >> result;
			return result;
		}

		operator DWORD()
		{
			DWORD result;
			m_sdata >> result;
			return result;
		}

		operator bool()
		{
			string result;
			m_sdata >> result;

			if ( result == "false" || result == "FALSE" || result == "0"  )
				return false;
			
			return true;
		}

		operator double()
		{
			double result;
			m_sdata >> result;
			return result;
		}

		operator string()
		{
			return m_sdata.str();
		}

		operator Color()
		{
			return Color( m_sdata );
		}
		
		operator Vector()
		{
			return Vector( m_sdata );
		}

		operator Matrix()
		{

			string cs = m_sdata.str();
			
			return Matrix( m_sdata );
		}
	};

	string CLEARMODELSDK_API FilenameTitle( string filename );

	string CLEARMODELSDK_API FilenameExtension( string filename );

	LoadType CLEARMODELSDK_API FileType( string filename );

	bool CLEARMODELSDK_API Print(LPCSTR log, ...);
}

#endif //DEFINITION_H__