#include "..\ClearModelSDK.h"


ClearModelSDK::CMeshNode::CMeshNode()
{
	m_VB = NULL;
}

ClearModelSDK::CMeshNode::~CMeshNode()
{
	Delete();
}

bool ClearModelSDK::CMeshNode::VLoad( TiXmlElement* xmlelement )
{
	m_sName = xmlConverter( xmlelement->Attribute( "Name" ) );

	m_GlobalPosition = xmlConverter( xmlelement->FirstChildElement( "GlobalMatrix" )->FirstChild() );

	m_VB = new VertexBuffer( xmlelement->FirstChildElement( "Geometry" )->FirstChildElement( "VertexBuffer" ) );
	
	//Bones
	TiXmlElement* xmlBones = xmlelement->FirstChildElement( "Bones" );
	DWORD boneCount = xmlConverter( xmlBones->Attribute( "Size" ) );

	for ( TiXmlElement* xmlBone = xmlBones->FirstChildElement( "Bone" ); xmlBone ; xmlBone = xmlBone->NextSiblingElement("Bone"))
		m_vecBones.push_back( xmlBone );


	//Animation
	TiXmlElement* xmlAnimation = xmlelement->FirstChildElement( "Animation" );

	for ( TiXmlElement* xmlAnimationTake = xmlAnimation->FirstChildElement( "AnimationTake" ); xmlAnimationTake ; xmlAnimationTake = xmlAnimationTake->NextSiblingElement("AnimationTake"))
		m_vecAnimationTakes.push_back( xmlAnimationTake );


	//Materials
	TiXmlElement* xmlMaterials = xmlelement->FirstChildElement( "Materials" );

	for ( TiXmlElement* xmlMaterial = xmlMaterials->FirstChildElement( "Material" ); xmlMaterial ; xmlMaterial = xmlMaterial->NextSiblingElement("Material"))
		m_vecMaterials.push_back( xmlMaterial );


	//Textures
	TiXmlElement* xmlTextures = xmlelement->FirstChildElement( "Textures" );

	for ( TiXmlElement* xmlTexture = xmlTextures->FirstChildElement( "Texture" ); xmlTexture ; xmlTexture = xmlTexture->NextSiblingElement("Texture"))
		m_vecTextures.push_back( xmlTexture );


	//Material-Connections
	m_MaterialConnection = xmlelement->FirstChildElement( "Material-Connections" );

	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CMeshNode::VLoad( IOHelper* reader )
{
	//Name
	char cName[256];
	reader->read( cName, 256 );
	m_sName = cName;


	//Geometry
	m_VB = new VertexBuffer( reader );


	//Bones
	DWORD boneCount;
	reader->read( boneCount );
	for (unsigned int i = 0; i < boneCount ; i++)
	{
		sMeshBone bone;
		char cBoneName[256];
		char cParentBoneName[256];

		reader->read( cBoneName, 256 );
		bone.m_sName = cBoneName;

		reader->read( cParentBoneName, 256 );
		bone.m_sParentName = cParentBoneName;

		reader->read( (char*)&bone.m_GlobalMatrix, sizeof(float), 16 );
		reader->read( (char*)&bone.m_BindPoseMatrix, sizeof(float), 16 );
		reader->read( (char*)&bone.m_boundingBox, sizeof(float), 3 );

		m_vecBones.push_back( bone );
	}


	//Animations
	DWORD animationsCount;
	reader->read( animationsCount );
	for (unsigned int i = 0; i < animationsCount ; i++)
	{
		sAnimationsTake__ take;

		reader->read( take.m_sName, 256 );

		reader->read( take.m_fStart );
		reader->read( take.m_fEnd );

		DWORD keyCount;
		reader->read( keyCount );

		take.m_vecAnimationKeys.resize( keyCount );
		reader->read( take.m_vecAnimationKeys.data(), sizeof(sAnimationsKey__), keyCount );

		m_vecAnimationTakes.push_back( take );
	}


	//Materials
	DWORD MaterialCount;
	reader->read( MaterialCount );
	for (unsigned int i = 0; i < MaterialCount ; i++)
	{
		sMaterial__ material;
		material.fromBinaryData( reader );

		m_vecMaterials.push_back( material );
	}


	//Textures
	DWORD texturesCount;
	reader->read( texturesCount );
	for (unsigned int i = 0; i < texturesCount ; i++)
	{
		sTexture__ texture;
		texture.fromBinaryData( reader );

		m_vecTextures.push_back( texture );
	}

	//Materia Connetion
	m_MaterialConnection = sMaterialConnection__( reader );

	//Global Position
	reader->read((char*)m_GlobalPosition.m_data, sizeof(float), 16 );


	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CMeshNode::Delete()
{
	SAFE_DELETE(m_VB);
}

std::string ClearModelSDK::CMeshNode::str()
{
	stringstream stm;
	stm << m_sName << endl;
	return stm.str();
}

TiXmlElement* ClearModelSDK::CMeshNode::xml()
{
	TiXmlElement* xmlMesh = new TiXmlElement( GetType().c_str() );
	xmlMesh->SetAttribute( "Name", m_sName.c_str() );


	//Geometry
	TiXmlElement* xmlGeometry = new TiXmlElement( "Geometry" );
	xmlGeometry->LinkEndChild( m_VB->xml() );



	//Joints
	TiXmlElement* xmlBones = new TiXmlElement( "Bones" );
	xmlBones->SetAttribute( "Size", m_vecBones.size() );

	for (unsigned int i = 0; i < m_vecBones.size() ; i++)
	{
		xmlBones->LinkEndChild( m_vecBones[i].xml() );
	}

	//Animation
	TiXmlElement* xmlAnimation = new TiXmlElement( "Animation" );
	xmlAnimation->SetAttribute( "Size", m_vecAnimationTakes.size() );

	for (unsigned int i = 0; i < m_vecAnimationTakes.size() ; i++)
	{
		xmlAnimation->LinkEndChild( m_vecAnimationTakes[i].xml() );
	}

	//Materials
	TiXmlElement* xmlMaterial = new TiXmlElement( "Materials" );
	xmlMaterial->SetAttribute( "Size", m_vecMaterials.size() );

	for (unsigned int i = 0; i < m_vecMaterials.size() ; i++)
	{
		xmlMaterial->LinkEndChild( m_vecMaterials[i].xml() );
	}

	//Textures
	TiXmlElement* xmlTextures = new TiXmlElement( "Textures" );
	xmlTextures->SetAttribute( "Size", m_vecTextures.size() );

	for (unsigned int i = 0; i < m_vecTextures.size() ; i++)
	{
		xmlTextures->LinkEndChild( m_vecTextures[i].xml() );
	}

	//Global Matrix
	TiXmlElement* xmlGlobalMatrix = new TiXmlElement( "GlobalMatrix" );
	xmlGlobalMatrix->LinkEndChild( xmlText(m_GlobalPosition) );

	xmlMesh->LinkEndChild( xmlGlobalMatrix );
	xmlMesh->LinkEndChild( xmlGeometry );
	xmlMesh->LinkEndChild( xmlBones );
	xmlMesh->LinkEndChild( xmlAnimation );
	xmlMesh->LinkEndChild( xmlMaterial );
	xmlMesh->LinkEndChild( xmlTextures );
	xmlMesh->LinkEndChild( m_MaterialConnection.xml() );

	return xmlMesh;
}

bool ClearModelSDK::CMeshNode::HasVertexData( string semanticName )
{
	if ( _stricmp( semanticName.c_str(), "Position") == 0  && !m_VB->m_vecPositions.empty() )
		return true;

	else if ( _stricmp( semanticName.c_str(), "Normal") == 0  && !m_VB->m_vecNormals.empty()   )
		return true;

	else if ( _stricmp( semanticName.c_str(), "Colors") == 0  && !m_VB->m_vecColors.empty()   )
		return true;	

	else if ( _stricmp( semanticName.c_str(), "TexCoord") == 0  && !m_VB->m_vecTexCoord.empty() )
		return true;

	else if ( _stricmp( semanticName.c_str(), "Tangents") == 0  && !m_VB->m_vecTangents.empty()  )
		return true;			

	else if ( _stricmp( semanticName.c_str(), "BiNormals") == 0  && !m_VB->m_vecBiNormals.empty()   )
		return true;

	else if ( _stricmp( semanticName.c_str(), "BoneWeights") == 0  && !m_VB->m_vecBoneWeights.empty() )
		return true;		

	else if ( _stricmp( semanticName.c_str(), "BoneIndices") == 0  && !m_VB->m_vecBoneIndices.empty() )
		return true;

	return false;
}


void ClearModelSDK::VertexBuffer::AddData( string type, char* data )
{
	if ( _stricmp( type.c_str(), "Position") == 0  )
	{
		Vector3 vdata;
		memcpy( &vdata, data, sizeof(Vector));
		m_vecPositions.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "Normal") == 0  )
	{
		Vector3 vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecNormals.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "Colors") == 0  )
	{
		Vector vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecColors.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "TexCoord") == 0  )
	{
		Vector2 vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecTexCoord.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "Tangents") )
	{
		Vector3 vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecTangents.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "BiNormals") == 0  )
	{
		Vector3 vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecBiNormals.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "BoneWeights") == 0  )
	{
		Vector vdata;
		memcpy( &vdata, data, sizeof(Vector));

		m_vecBoneWeights.push_back( vdata );
	}

	else if ( _stricmp( type.c_str(), "BoneIndices") == 0  )
	{
		UINT vdata[4];
		memcpy( &vdata, data, sizeof(UINT)*4);

		m_vecBoneIndices.push_back( vdata );
	}
}

ClearModelSDK::VertexBuffer::VertexBuffer( IOHelper* reader )
{
	DWORD posCount;
	DWORD normalCount;
	DWORD colorCount;
	DWORD uvCount;
	DWORD tangentCount;
	DWORD biNormalCount;
	DWORD boneWeightCount;
	DWORD boneIndexCount;

	//Position
	reader->read( posCount );
	m_vecPositions.resize( posCount );
	reader->read( (char*)m_vecPositions.data(), sizeof(float)*3, posCount );

	//Normal
	reader->read( normalCount );
	m_vecNormals.resize( normalCount );
	reader->read( (char*)m_vecNormals.data(), sizeof(float)*3, normalCount );

	//Colors
	reader->read(  colorCount );
	m_vecColors.resize(  colorCount );
	reader->read( (char*)m_vecColors.data(), sizeof(float)*4,  colorCount );

	//TexCoords
	reader->read(  uvCount );
	m_vecTexCoord.resize(  uvCount );
	reader->read( (char*)m_vecTexCoord.data(), sizeof(float)*2,  uvCount );

	//Tangents
	reader->read(  tangentCount );
	m_vecTangents.resize(  tangentCount );
	reader->read( (char*)m_vecTangents.data(), sizeof(float)*3,  tangentCount );

	//BinNormals
	reader->read( biNormalCount );
	m_vecBiNormals.resize(  biNormalCount );
	reader->read( (char*)m_vecBiNormals.data(), sizeof(float)*3,  biNormalCount );

	//BoneWeights
	reader->read( boneWeightCount );
	m_vecBoneWeights.resize(  boneWeightCount );
	reader->read( (char*)m_vecBoneWeights.data(), sizeof(float)*4,  boneWeightCount );

	//BoneWeights
	reader->read( boneIndexCount );
	m_vecBoneIndices.resize(  boneIndexCount );
	reader->read( (char*)m_vecBoneIndices.data(), sizeof(UINT)*4,  boneIndexCount );
}

void ClearModelSDK::sMaterialGroup__::CalculateAABB( VertexBuffer* buffer )
{
	m_sizeMax = Vector3(-99999.0f,-99999.0f,-99999.0f);
	m_sizeMin = Vector3(99999.0f,99999.0f,99999.0f);

	for (unsigned int i = 0; i < m_vecVertexIndices.size() ; i++)
	{
		//Minimum
		if ( m_sizeMax.x < buffer->m_vecPositions[ m_vecVertexIndices[i] ].x )
			m_sizeMax.x = buffer->m_vecPositions[ m_vecVertexIndices[i] ].x;

		if ( m_sizeMax.y < buffer->m_vecPositions[ m_vecVertexIndices[i] ].y )
			m_sizeMax.y = buffer->m_vecPositions[ m_vecVertexIndices[i] ].y;

		if ( m_sizeMax.z < buffer->m_vecPositions[ m_vecVertexIndices[i] ].z )
			m_sizeMax.z = buffer->m_vecPositions[ m_vecVertexIndices[i] ].z;

		//Maximum
		if ( m_sizeMin.x > buffer->m_vecPositions[ m_vecVertexIndices[i] ].x )
			m_sizeMin.x = buffer->m_vecPositions[ m_vecVertexIndices[i] ].x;

		if ( m_sizeMin.y > buffer->m_vecPositions[ m_vecVertexIndices[i] ].y )
			m_sizeMin.y = buffer->m_vecPositions[ m_vecVertexIndices[i] ].y;

		if ( m_sizeMin.z > buffer->m_vecPositions[ m_vecVertexIndices[i] ].z )
			m_sizeMin.z = buffer->m_vecPositions[ m_vecVertexIndices[i] ].z;
	}
}
