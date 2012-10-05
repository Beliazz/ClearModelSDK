#ifndef MeshNode_H__
#define MeshNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CLEARMODELSDK_API VertexBuffer
	{
		friend class CMeshNode;

	public:
		VertexBuffer(){}
		VertexBuffer( IOHelper* reader );

		VertexBuffer( TiXmlElement* xmlelement )
		{
			DWORD size = xmlConverter( xmlelement->Attribute( "Size" ) );

			if (!xmlelement->FirstChildElement( "Position" ))
				return;


			stringstream strmPosition;
			stringstream strmNormal;
			stringstream strmTexCoord;
			stringstream strmColor;
			stringstream strmTangent;
			stringstream strmBiNormal;
			stringstream strmBoneWeight;
			stringstream strmBoneIndex;

			strmPosition = stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "Position" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "Normal" ))
				strmNormal	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "Normal" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "TexCoord" ))
				strmTexCoord = stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "TexCoord" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "Color" ))
				strmColor	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "Color" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "Tangent" ))
				strmTangent	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "Tangent" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "BiNormal" ))
				strmBiNormal	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "BiNormal" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "BoneWeight" ))
				strmBoneWeight	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "BoneWeight" )->FirstChild() ) );

			if (xmlelement->FirstChildElement( "BoneIndex" ))
				strmBoneIndex	= stringstream( (string)xmlConverter( xmlelement->FirstChildElement( "BoneIndex" )->FirstChild() ) );


			for (unsigned int i = 0; i < size ; i++)
			{
				m_vecPositions.push_back( strmPosition );

				if(strmNormal.str() != "")
					m_vecNormals.push_back( strmNormal );

				if(strmTexCoord.str() != "")
					m_vecTexCoord.push_back( strmTexCoord );

				if(strmColor.str() != "")
					m_vecColors.push_back( strmColor );

				if(strmTangent.str() != "")
					m_vecTangents.push_back( strmTangent );

				if(strmBiNormal.str() != "")
					m_vecBiNormals.push_back( strmBiNormal );

				if(strmBoneWeight.str() != "")
					m_vecBoneWeights.push_back( strmBoneWeight );

				if(strmBoneIndex.str() != "")
				{
					UINT boneIndices[4];
					strmBoneIndex >> boneIndices[0] >> boneIndices[1] >> boneIndices[2] >> boneIndices[3];
					m_vecBoneIndices.push_back( boneIndices );
				}
			}
		}
		~VertexBuffer()
		{
		}

		void   AddData( string type, char* data );
		char*  GetData( string type, DWORD index )
		{
			if ( _stricmp( type.c_str(), "Position") == 0  && m_vecPositions.size() >= index )
				return (char*)&m_vecPositions[index];

			else if ( _stricmp( type.c_str(), "Normal") == 0  && m_vecNormals.size() >= index   )
				return (char*)&m_vecNormals[index];

			else if ( _stricmp( type.c_str(), "Colors") == 0  && m_vecColors.size() >= index   )
				return (char*)&m_vecColors[index];		

			else if ( _stricmp( type.c_str(), "TexCoord") == 0  && m_vecTexCoord.size() >= index   )
				return (char*)&m_vecTexCoord[index];

			else if ( _stricmp( type.c_str(), "Tangents") == 0  && m_vecTangents.size() >= index  )
				return (char*)&m_vecTangents[index];			

			else if ( _stricmp( type.c_str(), "BiNormals") == 0  && m_vecBiNormals.size() >= index   )
				return (char*)&m_vecBiNormals[index];

			else if ( _stricmp( type.c_str(), "BoneWeights") == 0  && m_vecBoneWeights.size() >= index   )
				return (char*)&m_vecBoneWeights[index];			

			else if ( _stricmp( type.c_str(), "BoneIndices") == 0  && m_vecBoneIndices.size() >= index   )
				return (char*)&m_vecBoneIndices[index];

			return NULL;
		}
		DWORD  Size() 
		{ 
			return m_vecPositions.size(); 
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlVB = new TiXmlElement( "VertexBuffer" );
			xmlVB->SetAttribute( "Size", m_vecPositions.size() );

			TiXmlElement* xmlPosition	= new TiXmlElement( "Position" );

			string strPosition	 = "";
			string strNormal	 = "";
			string strTexCoord	 = "";
			string strColor		 = "";
			string strTangent	 = "";
			string strBiNormal	 = "";
			string strBoneWeight = "";
			string strBoneIndex	 = "";

			for (unsigned int i = 0; i < m_vecPositions.size() ; i++)
			{
				stringstream stm_boneindex;

				//Must have
				strPosition	  += m_vecPositions[i].str();

				//Intivitual
				if (!m_vecNormals.empty())
					strNormal += m_vecNormals[i].str();

				if (!m_vecTexCoord.empty())
					strTexCoord += m_vecTexCoord[i].str();

				if (!m_vecColors.empty())
					strTexCoord += m_vecColors[i].str();

				if (!m_vecColors.empty())
					strColor += m_vecColors[i].str();

				if (!m_vecTangents.empty())
					strTangent += m_vecTangents[i].str();


				if (!m_vecBiNormals.empty())
					strBiNormal += m_vecBiNormals[i].str();

				if (!m_vecBoneWeights.empty())
					strBoneWeight += m_vecBoneWeights[i].str();

				if (!m_vecBoneWeights.empty())
				{
					strBoneIndex  += m_vecBoneIndices[i].str();
				}
			}

			xmlPosition->LinkEndChild(	 xmlText(strPosition) );
			xmlVB->LinkEndChild( xmlPosition );


			if (strNormal != "")
			{
				TiXmlElement* xmlNormal		= new TiXmlElement( "Normal" );
				xmlNormal->LinkEndChild( xmlText(strNormal) );
				xmlVB->LinkEndChild( xmlNormal );
			}

			if (strTexCoord != "")
			{
				TiXmlElement* xmlTexCoord	= new TiXmlElement( "TexCoord" );
				xmlTexCoord->LinkEndChild( xmlText(strTexCoord) );
				xmlVB->LinkEndChild( xmlTexCoord );
			}

			if (strColor != "")
			{
				TiXmlElement* xmlColor		= new TiXmlElement( "Color" );
				xmlColor->LinkEndChild( xmlText(strColor) );
				xmlVB->LinkEndChild( xmlColor );
			}

			if (strTangent != "")
			{
				TiXmlElement* xmlTangent	= new TiXmlElement( "Tangent" );
				xmlTangent->LinkEndChild( xmlText(strTangent) );
				xmlVB->LinkEndChild( xmlTangent );
			}

			if (strBiNormal != "")
			{
				TiXmlElement* xmlBiNormal	= new TiXmlElement( "BiNormal" );
				xmlBiNormal->LinkEndChild( xmlText(strBiNormal) );
				xmlVB->LinkEndChild( xmlBiNormal );
			}

			if (strBoneWeight != "")
			{
				TiXmlElement* xmlBoneWeight	= new TiXmlElement( "BoneWeight" );
				xmlBoneWeight->LinkEndChild( xmlText(strBoneWeight) );
				xmlVB->LinkEndChild( xmlBoneWeight );
			}

			if (strBoneIndex != "")
			{
				TiXmlElement* xmlBoneIndex	= new TiXmlElement( "BoneIndex" );
				xmlBoneIndex->LinkEndChild( xmlText(strBoneIndex) );
				xmlVB->LinkEndChild( xmlBoneIndex );
			}

			return xmlVB;
		}

		vector<Vector3> m_vecPositions;
		vector<Vector3> m_vecNormals;
		vector<Vector> m_vecColors;
		vector<Vector2> m_vecTexCoord;
		vector<Vector3> m_vecTangents;
		vector<Vector3> m_vecBiNormals;
		vector<Vector> m_vecBoneWeights;
		vector<VectorUINT> m_vecBoneIndices;
	};

	struct CLEARMODELSDK_API sMeshBone
	{
		sMeshBone(){}
		sMeshBone( TiXmlElement* xmlelement )
		{
			m_sName	= xmlConverter( xmlelement->Attribute( "Name" ) );
			m_sParentName = xmlConverter( xmlelement->Attribute( "Parent" ) );

			m_GlobalMatrix   = xmlConverter( xmlelement->FirstChildElement( "GlobalMatrix" )->FirstChild() );
			m_BindPoseMatrix = xmlConverter( xmlelement->FirstChildElement( "BindPoseMatrix" )->FirstChild() );
			m_boundingBox    = xmlConverter( xmlelement->FirstChildElement( "BoundingBox" )->FirstChild() );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlBone = new TiXmlElement( "Bone" );
			xmlBone->SetAttribute( "Name", m_sName.c_str() );
			xmlBone->SetAttribute( "Parent", m_sParentName.c_str() );

			TiXmlElement* xmlGlobalMatrix	= new TiXmlElement( "GlobalMatrix" );
			TiXmlElement* xmlBindPoseMatrix = new TiXmlElement( "BindPoseMatrix" );
			TiXmlElement* xmlBoundingBox = new TiXmlElement( "BoundingBox" );

			xmlGlobalMatrix->LinkEndChild(	 xmlText( m_GlobalMatrix ) );
			xmlBindPoseMatrix->LinkEndChild( xmlText( m_BindPoseMatrix ) );
			xmlBoundingBox->LinkEndChild( xmlText( m_boundingBox.str() ) );

			xmlBone->LinkEndChild( xmlGlobalMatrix );
			xmlBone->LinkEndChild( xmlBindPoseMatrix );
			xmlBone->LinkEndChild( xmlBoundingBox );

			return xmlBone;
		}

		string m_sName;
		string m_sParentName;
		Matrix m_GlobalMatrix;
		Matrix m_BindPoseMatrix;
		Vector3 m_boundingBox;
	};

	struct CLEARMODELSDK_API sAnimationsKey__
	{
		sAnimationsKey__(){}
		sAnimationsKey__(TiXmlElement* xmlelement)
		{
			m_fBoneIndex =  xmlConverter( xmlelement->Attribute( "InfulencedBone" ) );
			m_fTimestamp = xmlConverter( xmlelement->Attribute( "Timestamp" ) );

			m_Matrix = xmlConverter( xmlelement->FirstChildElement( "KeyMatrix" )->FirstChild() );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlAnimKey = new TiXmlElement( "AnimationKey" );
			xmlAnimKey->SetAttribute( "InfulencedBone", m_fBoneIndex );

			stringstream stm;
			stm << m_fTimestamp;
			xmlAnimKey->SetAttribute( "Timestamp", stm.str().c_str() );

			TiXmlElement* xmlKeyMatrix = new TiXmlElement( "KeyMatrix" );
			xmlKeyMatrix->LinkEndChild( xmlText( m_Matrix ) );

			xmlAnimKey->LinkEndChild( xmlKeyMatrix );

			return xmlAnimKey;
		}

		DWORD  m_fBoneIndex;
		float  m_fTimestamp;
		Matrix m_Matrix;
	};

	struct CLEARMODELSDK_API sAnimationsTake__
	{
		sAnimationsTake__(){}
		sAnimationsTake__( TiXmlElement* xmlelement )
		{
			DWORD size = xmlConverter( xmlelement->Attribute( "Size" ) );

			strcpy( m_sName, xmlelement->Attribute( "Name" )); 
			m_fStart = xmlConverter( xmlelement->Attribute( "StartTime" ) ); 
			m_fEnd	 = xmlConverter( xmlelement->Attribute( "EndTime" ) ); 

			for ( TiXmlElement* xmlAnimKey = xmlelement->FirstChildElement("AnimationKey"); xmlAnimKey ; xmlAnimKey = xmlAnimKey->NextSiblingElement("AnimationKey"))
				m_vecAnimationKeys.push_back( xmlAnimKey );	
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlAnimTake = new TiXmlElement( "AnimationTake" );
			xmlAnimTake->SetAttribute( "Size", m_vecAnimationKeys.size() );
			xmlAnimTake->SetAttribute( "Name", m_sName );

			stringstream stm;
			stm << m_fStart;
			xmlAnimTake->SetAttribute( "StartTime", stm.str().c_str() );

			stm = stringstream("");
			stm << m_fEnd;
			xmlAnimTake->SetAttribute( "EndTime", stm.str().c_str() );


			for (unsigned int i = 0; i < m_vecAnimationKeys.size() ; i++)
			{
				xmlAnimTake->LinkEndChild( m_vecAnimationKeys[i].xml() );
			}

			return xmlAnimTake;
		}

		char m_sName[256];
		float m_fStart;
		float m_fEnd;
		vector<sAnimationsKey__> m_vecAnimationKeys;
	};

	struct CLEARMODELSDK_API sTexture__
	{
		sTexture__(){}
		sTexture__( TiXmlElement* xmlelement )
		{
			m_sFilename   = xmlConverter( xmlelement->Attribute( "Filename" ) );
			m_sType		  = xmlConverter( xmlelement->Attribute( "Type" ) );
			m_sTextureFor = xmlConverter( xmlelement->Attribute( "TextureFor" ) );
			m_dAssignedMaterial = xmlConverter( xmlelement->Attribute( "AssignedMaterialIndex" ) );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlTexture = new TiXmlElement( "Texture" );
			xmlTexture->SetAttribute( "Filename", m_sFilename.c_str() );
			xmlTexture->SetAttribute( "Type", m_sType.c_str() );
			xmlTexture->SetAttribute( "TextureFor",	m_sTextureFor.c_str() );

			stringstream stm;
			stm << m_dAssignedMaterial;
			xmlTexture->SetAttribute( "AssignedMaterialIndex",	stm.str().c_str() );

			return xmlTexture;
		}
		void fromBinaryData( IOHelper* reader )
		{
			char cFilename[256*2];
			char cTextureFor[256];
			char cType[32];

			reader->read( cFilename, 256*2 );
			reader->read( cType, 32 );
			reader->read( cTextureFor, 256 );

			m_sFilename = cFilename;
			m_sTextureFor = cTextureFor;
			m_sType = cType;

			reader->read( m_dAssignedMaterial );
		}

		string m_sType;
		string m_sFilename;
		string m_sTextureFor;
		DWORD m_dAssignedMaterial;
	};

	struct CLEARMODELSDK_API Hardwareshader__
	{
		string m_sType;
		string m_sEntry;
		vector<sTexture__> m_vecTextures;
	};

	struct CLEARMODELSDK_API sPhong__
	{
		sPhong__(){}
		sPhong__(TiXmlElement* xmlelement)
		{
			m_colAmbient	= xmlConverter( xmlelement->FirstChildElement("Ambient")->FirstChild() );
			m_colDiffuse	= xmlConverter( xmlelement->FirstChildElement("Diffuse")->FirstChild() );
			m_colSpecular	= xmlConverter( xmlelement->FirstChildElement("Specular")->FirstChild() );
			m_colEmissive   = xmlConverter( xmlelement->FirstChildElement("Emissive")->FirstChild() );

			m_fTransparency = xmlConverter( xmlelement->FirstChildElement("Transparency")->FirstChild() );
			m_fShininess    = xmlConverter( xmlelement->FirstChildElement("Shininess")->FirstChild() );
			m_fReflectivity = xmlConverter( xmlelement->FirstChildElement("Reflectivity")->FirstChild() );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlPhong = new TiXmlElement( "Phong" );

			TiXmlElement* xmlAmbient  = new TiXmlElement( "Ambient" );
			TiXmlElement* xmlDiffuse  = new TiXmlElement( "Diffuse" );
			TiXmlElement* xmlSpecular = new TiXmlElement( "Specular" );
			TiXmlElement* xmlEmissive		= new TiXmlElement( "Emissive" );
			TiXmlElement* xmlTransparency	= new TiXmlElement( "Transparency" );
			TiXmlElement* xmlShininess		= new TiXmlElement( "Shininess" );
			TiXmlElement* xmlReflectivity	= new TiXmlElement( "Reflectivity" );

			xmlAmbient->LinkEndChild( xmlText( m_colAmbient ) );
			xmlDiffuse->LinkEndChild( xmlText( m_colDiffuse ) );
			xmlSpecular->LinkEndChild( xmlText( m_colSpecular ) );
			xmlEmissive->LinkEndChild( xmlText( m_colEmissive ) );

			stringstream stm;
			stm << m_fTransparency;
			xmlTransparency->LinkEndChild( xmlText( stm.str().c_str() ) );

			stm = stringstream("");
			stm << m_fShininess;
			xmlShininess->LinkEndChild( xmlText( stm.str().c_str() ) );

			stm = stringstream("");
			stm << m_fReflectivity;
			xmlReflectivity->LinkEndChild( xmlText( stm.str().c_str() ) );

			xmlPhong->LinkEndChild( xmlAmbient );
			xmlPhong->LinkEndChild( xmlDiffuse );
			xmlPhong->LinkEndChild( xmlSpecular );
			xmlPhong->LinkEndChild( xmlEmissive );
			xmlPhong->LinkEndChild( xmlTransparency );
			xmlPhong->LinkEndChild( xmlShininess );
			xmlPhong->LinkEndChild( xmlReflectivity );

			return xmlPhong;
		}
		void fromBinaryData( IOHelper* reader )
		{
			reader->read( m_colAmbient );
			reader->read( m_colDiffuse );
			reader->read( m_colSpecular );
			reader->read( m_colEmissive );

			reader->read( m_fTransparency );
			reader->read( m_fShininess );
			reader->read( m_fReflectivity );
		}

		Color m_colAmbient;
		Color m_colDiffuse;
		Color m_colSpecular;
		Color m_colEmissive;

		float m_fTransparency;
		float m_fShininess;
		float m_fReflectivity;
	};

	struct CLEARMODELSDK_API sLambert__
	{
		sLambert__(){}
		sLambert__(TiXmlElement* xmlelement)
		{
			m_colAmbient	= xmlConverter( xmlelement->FirstChildElement("Ambient")->FirstChild() );
			m_colDiffuse	= xmlConverter( xmlelement->FirstChildElement("Diffuse")->FirstChild() );
			m_colEmissive   = xmlConverter( xmlelement->FirstChildElement("Emissive")->FirstChild() );

			m_fTransparency = xmlConverter( xmlelement->FirstChildElement("Transparency")->FirstChild() );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlLambert = new TiXmlElement( "Lambert" );

			TiXmlElement* xmlAmbient  = new TiXmlElement( "Ambient" );
			TiXmlElement* xmlDiffuse  = new TiXmlElement( "Diffuse" );
			TiXmlElement* xmlEmissive		= new TiXmlElement( "Emissive" );
			TiXmlElement* xmlTransparency	= new TiXmlElement( "Transparency" );

			xmlAmbient->LinkEndChild( xmlText( m_colAmbient ) );
			xmlDiffuse->LinkEndChild( xmlText( m_colDiffuse ) );
			xmlEmissive->LinkEndChild( xmlText( m_colEmissive ) );

			stringstream stm;
			stm << m_fTransparency;
			xmlTransparency->LinkEndChild( xmlText( stm.str().c_str() ) );


			xmlLambert->LinkEndChild( xmlAmbient );
			xmlLambert->LinkEndChild( xmlDiffuse );
			xmlLambert->LinkEndChild( xmlEmissive );
			xmlLambert->LinkEndChild( xmlTransparency );

			return xmlLambert;
		}
		void fromBinaryData( IOHelper* reader )
		{
			reader->read( m_colAmbient );
			reader->read( m_colDiffuse );
			reader->read( m_colEmissive );

			reader->read( m_fTransparency );
		}

		Color m_colAmbient;
		Color m_colDiffuse;
		Color m_colEmissive;

		float m_fTransparency;
	};

	struct CLEARMODELSDK_API sMaterial__
	{
		sMaterial__(){}
		sMaterial__( TiXmlElement* xmlelement )
		{
			m_sName = xmlConverter( xmlelement->Attribute( "Name" ) );
			m_sType = xmlConverter( xmlelement->Attribute( "Type" ) );
			m_sShadingModel = xmlConverter( xmlelement->Attribute( "ShadingModel" ) );

			m_HasTexture = xmlConverter( xmlelement->Attribute( "HasTexture" ) );

			if (m_HasTexture)
			{
				m_AssignedTexture = xmlConverter( xmlelement->Attribute( "TextureIndex" ) );
			}

			if (m_sType == "Phong")
				m_phong = xmlelement->FirstChildElement( "Phong" );

			else if (m_sType == "Phong")
				m_phong = xmlelement->FirstChildElement( "Lambert" );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlMaterial = new TiXmlElement( "Material" );
			xmlMaterial->SetAttribute( "Name", m_sName.c_str() );
			xmlMaterial->SetAttribute( "Type", m_sType.c_str() );
			xmlMaterial->SetAttribute( "ShadingModel", m_sShadingModel.c_str() );

			if (m_HasTexture)
			{
				xmlMaterial->SetAttribute( "HasTexture", "true" );
				xmlMaterial->SetAttribute( "TextureIndex", m_AssignedTexture );
			}
			else
			{
				xmlMaterial->SetAttribute( "HasTexture", "false" );
			}

			if (m_sType == "Phong" )
			{
				xmlMaterial->LinkEndChild( m_phong.xml() );
			}
			else if ( m_sType == "Lambert" )
			{
				xmlMaterial->LinkEndChild( m_lambert.xml() );
			}

			return xmlMaterial;
		}

		void fromBinaryData( IOHelper* reader )
		{
			char cName[256];	
			char cType[32];	
			char cShadingModel[256];	

			reader->read( cName, 256 );
			reader->read( cType, 32 );
			reader->read( cShadingModel, 256 );

			m_sName = cName;
			m_sType = cType;
			m_sShadingModel = cShadingModel;

			reader->read( m_HasTexture );
			m_AssignedTexture = 987654321;

			if (m_HasTexture)
				reader->read( m_AssignedTexture );


			if (m_sType == "Phong" )
			{
				m_phong.fromBinaryData( reader );
			}
			else if ( m_sType == "Lambert" )
			{
				m_lambert.fromBinaryData( reader );
			}
		}

		string m_sName;
		Hardwareshader__ m_hardwareShader;
		string m_sType;
		string m_sShadingModel;

		bool m_HasTexture;
		DWORD m_AssignedTexture;

		sPhong__	m_phong;
		sLambert__	m_lambert;
	};

	struct CLEARMODELSDK_API sMaterialGroup__
	{
		sMaterialGroup__(){}
		sMaterialGroup__( IOHelper* pReader )
		{
			char cName[256];
			DWORD indexCount;

			pReader->read( cName,256 );
			m_sMaterialName = cName;

			pReader->read( m_dMaterialIndex );

			pReader->read( indexCount );
			m_vecVertexIndices.resize( indexCount );

			pReader->read( (char*)m_vecVertexIndices.data(), sizeof(DWORD), indexCount );

			pReader->read( (char*)&m_sizeMax, sizeof(float), 3 );
			pReader->read( (char*)&m_sizeMin, sizeof(float), 3 );
		}
		sMaterialGroup__( TiXmlElement* xmlelement )
		{
			m_sMaterialName	 = xmlConverter( xmlelement->Attribute( "MaterialName" ) );
			m_dMaterialIndex = xmlConverter( xmlelement->Attribute( "MaterialIndex" ) );

			TiXmlElement* xmlInfluencedPolygons = xmlelement->FirstChildElement( "InfluencedPolygons" );

			DWORD size = xmlConverter( xmlInfluencedPolygons->Attribute( "Size" ) );

			stringstream stmPolygonIndices = stringstream( (string) xmlConverter( xmlInfluencedPolygons->FirstChild() ) );

			for (unsigned int i = 0; i < size ; i++)
			{
				DWORD index;
				stmPolygonIndices >> index;
				m_vecVertexIndices.push_back(index);
			}
		}

		void CalculateAABB( VertexBuffer* buffer );

		TiXmlElement* xml()
		{
			TiXmlElement* xmlMaterialGroup = new TiXmlElement( "MaterialGroup" );
			xmlMaterialGroup->SetAttribute( "MaterialName", m_sMaterialName.c_str() );

			stringstream stm;
			stm << m_dMaterialIndex;
			xmlMaterialGroup->SetAttribute( "MaterialIndex", stm.str().c_str() );

			TiXmlElement* xmlInfluencedPolygons = new TiXmlElement( "InfluencedPolygons" );
			xmlInfluencedPolygons->SetAttribute( "Size", m_vecVertexIndices.size() );

			stm = stringstream("");

			for (unsigned int i = 0; i < m_vecVertexIndices.size() ; i++)
			{
				stm << m_vecVertexIndices[i] << " ";
			}

			//Bounding Box
			TiXmlElement* xmlBoundingBox = new TiXmlElement( "Bounding-Box" );
			TiXmlElement* xmlBoundingBoxMin = new TiXmlElement( "Min" );
			TiXmlElement* xmlBoundingBoxMax = new TiXmlElement( "Max" );

			xmlBoundingBoxMin->LinkEndChild( xmlText(m_sizeMin.str()) );
			xmlBoundingBoxMax->LinkEndChild(  xmlText(m_sizeMax.str()) );

			xmlBoundingBox->LinkEndChild( xmlBoundingBoxMax );
			xmlBoundingBox->LinkEndChild( xmlBoundingBoxMin );


			xmlInfluencedPolygons->LinkEndChild( xmlText( stm.str().c_str() ) );
			xmlMaterialGroup->LinkEndChild( xmlInfluencedPolygons );

			return xmlMaterialGroup;
		}

		Vector3	m_sizeMax;
		Vector3	m_sizeMin;

		DWORD  m_dMaterialIndex;
		string m_sMaterialName;
		vector<DWORD> m_vecVertexIndices;
	};

	struct CLEARMODELSDK_API sMaterialConnection__
	{
		sMaterialConnection__(){}
		sMaterialConnection__( IOHelper* pReader )
		{
			char cType[32];
			pReader->read(cType,32);
			m_sType = cType;

			DWORD groupCount;
			pReader->read( groupCount );
			m_vecMaterialGroups.resize( groupCount );

			for (unsigned int i = 0; i < groupCount ; i++)
				m_vecMaterialGroups[i] = sMaterialGroup__( pReader );

		}
		sMaterialConnection__( TiXmlElement* xmlelement )
		{
			DWORD size;
			size    = xmlConverter( xmlelement->Attribute( "Size" ) );

			for ( TiXmlElement* xmlMaterialGroup = xmlelement->FirstChildElement("MaterialGroup"); xmlMaterialGroup ; xmlMaterialGroup = xmlMaterialGroup->NextSiblingElement("MaterialGroup"))
				m_vecMaterialGroups.push_back( xmlMaterialGroup );
		}

		TiXmlElement* xml()
		{
			TiXmlElement* xmlMaterialConnections = new TiXmlElement( "Material-Connections" );
			xmlMaterialConnections->SetAttribute( "Type", m_sType.c_str() );
			xmlMaterialConnections->SetAttribute( "Size", m_vecMaterialGroups.size() );

			if ( m_sType == "All-Same" )
			{
				TiXmlElement* xmlMaterialGroup = new TiXmlElement( "MaterialGroup" );
				xmlMaterialGroup->SetAttribute( "MaterialName", m_vecMaterialGroups[0].m_sMaterialName.c_str() );

				stringstream stm;
				stm <<  m_vecMaterialGroups[0].m_dMaterialIndex;
				xmlMaterialGroup->SetAttribute( "MaterialIndex", stm.str().c_str() );

				xmlMaterialConnections->LinkEndChild( xmlMaterialGroup );
			}
			else
			{
				for (unsigned int i = 0; i < m_vecMaterialGroups.size() ; i++)
				{
					xmlMaterialConnections->LinkEndChild( m_vecMaterialGroups[i].xml() );
				}
			}

			return xmlMaterialConnections;
		}

		string m_sType;
		vector<sMaterialGroup__> m_vecMaterialGroups;
	};

	class CLEARMODELSDK_API CMeshNode : public ModelElement
	{
	public:
		CMeshNode();
		~CMeshNode();
		virtual bool VLoad( TiXmlElement* xmlelement );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "MeshNode"; }
		virtual string str();
		virtual TiXmlElement* xml();

		virtual void Delete();

		//Access/Set Functions
		string			   GetName()						{ return m_sName; }		
		VertexBuffer*	   GetVertexBuffer()				{ return m_VB; }
		sMeshBone		   GetBone( DWORD index )			{ return m_vecBones[index]; }
		DWORD			   GetBoneCount( )					{ return m_vecBones.size(); }
		sAnimationsTake__  GetAnimationTake( DWORD index )	{ return m_vecAnimationTakes[index]; }
		DWORD			   GetAnimationTakeCount( )			{ return m_vecAnimationTakes.size(); }
		sMaterial__		   GetMaterial( DWORD index )		{ return m_vecMaterials[index]; }
		DWORD			   GetMaterialCount( )				{ return m_vecMaterials.size(); }
		sTexture__		   GetTexture( DWORD index )		{ return m_vecTextures[index]; }
		DWORD			   GetTextureCount( )				{ return m_vecTextures.size(); }
		sMaterialConnection__ GetMaterialConnection()		{ return m_MaterialConnection; }

		float* GetPositionData() { return (float*)m_VB->m_vecPositions.data();}

		bool HasVertexData( string semanticName );

		bool HasNormals()		{ return !m_VB->m_vecNormals.empty(); }
		bool HasTexCoords()		{ return !m_VB->m_vecTexCoord.empty(); }
		bool HasColors()		{ return !m_VB->m_vecColors.empty(); }
		bool HasTangents()		{ return !m_VB->m_vecTangents.empty(); }
		bool HasBiNormals()		{ return !m_VB->m_vecBiNormals.empty(); }
		bool HasBoneIndices()	{ return !m_VB->m_vecBoneIndices.empty(); }
		bool HasBoneWeights()   { return !m_VB->m_vecBoneWeights.empty(); }


		void SetName( string name )							{ m_sName = name; }
		void SetVertexBuffer( VertexBuffer* buffer )		{ m_VB = buffer; }
		void AddBone( sMeshBone bone )						{ m_vecBones.push_back(bone); }
		void DeleteBone( DWORD index )						{ m_vecBones.erase(m_vecBones.begin() + index); }
		void AddAnimationsTrack( sAnimationsTake__ track )	{ m_vecAnimationTakes.push_back(track); }
		void DeleteAnimationsTrack( DWORD index )			{ m_vecAnimationTakes.erase(m_vecAnimationTakes.begin() + index); }
		void AddMaterial( sMaterial__ material )			{ m_vecMaterials.push_back(material); }
		void DeleteMaterial( DWORD index )					{ m_vecMaterials.erase(m_vecMaterials.begin() + index); }
		void AddTexture( sTexture__ texture )			    { m_vecTextures.push_back(texture); }
		void DeleteTexture( DWORD index )					{ m_vecTextures.erase(m_vecTextures.begin() + index); }

	private:
		string		  m_sName;
		VertexBuffer* m_VB;
		vector<sMeshBone> m_vecBones;
		vector<sAnimationsTake__> m_vecAnimationTakes;
		vector<sMaterial__> m_vecMaterials;
		vector<sTexture__> m_vecTextures;
		sMaterialConnection__ m_MaterialConnection;
	};

}
#endif
