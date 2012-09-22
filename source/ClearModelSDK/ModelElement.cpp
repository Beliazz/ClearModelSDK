#include "ClearModelSDK.h"

bool ClearModelSDK::ModelElement::VSave( TiXmlElement* parent )
{
	TiXmlElement* xmlelement = xml();

	for (unsigned int i = 0; i < m_pChildren.size() ; i++)
	{
		m_pChildren[i]->VSave( xmlelement );
	}

	parent->LinkEndChild( xmlelement );

	return true;
}

TiXmlElement* ClearModelSDK::ModelElement::xml()
{
	TiXmlElement* var = new TiXmlElement( GetType().c_str() );
	var->SetAttribute( "Info", "Unsupported" );

	return var;
}

void ClearModelSDK::ModelElement::Delete()
{
	while (!m_pChildren.empty())
	{
		m_pChildren.erase(m_pChildren.begin());
	}
}

bool ClearModelSDK::ModelElement::VLoad( TiXmlElement* xmlElement  )
{
	return ProcessXMLNode( xmlElement);
}

bool ClearModelSDK::ModelElement::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );

	return true;
}

bool ClearModelSDK::ModelElement::ProcessXMLNode( TiXmlElement* xmlelement )
{
	for ( TiXmlElement* xmlChild = xmlelement->FirstChildElement(); xmlChild ; xmlChild = xmlChild->NextSiblingElement())
	{
		string sNodeType = xmlChild->Value();

		if ( sNodeType == "GlobalTimeSettings" )
		{
			shared_ptr<CGlobalTimeSettings> pSceneElement = shared_ptr<CGlobalTimeSettings>(new CGlobalTimeSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "GlobalCameraSettings" )
		{
			shared_ptr<CGlobalCameraSettings> pSceneElement = shared_ptr<CGlobalCameraSettings>(new CGlobalCameraSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "GlobalLightSettings" )
		{
			shared_ptr<CGlobalLightSettings> pSceneElement = shared_ptr<CGlobalLightSettings>(new CGlobalLightSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if (sNodeType == "EmptyNode")
		{
			shared_ptr<CEmptyNode> pSceneElement = shared_ptr<CEmptyNode>(new CEmptyNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "CameraNode" )
		{
			shared_ptr<CCameraNode> pSceneElement = shared_ptr<CCameraNode>(new CCameraNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "LightNode" )
		{
			shared_ptr<CLightNode> pSceneElement = shared_ptr<CLightNode>(new CLightNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "LODGroudNode" )
		{
			shared_ptr<CLODGroudNode> pSceneElement = shared_ptr<CLODGroudNode>(new CLODGroudNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "MarkerNode" )
		{
			shared_ptr<CMarkerNode> pSceneElement = shared_ptr<CMarkerNode>(new CMarkerNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "MeshNode" )
		{
			shared_ptr<CMeshNode> pSceneElement = shared_ptr<CMeshNode>(new CMeshNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "NurbNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "PatchNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( sNodeType == "SkeletonNode" )
		{
			shared_ptr<CSkeletonNode> pSceneElement = shared_ptr<CSkeletonNode>(new CSkeletonNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			AddElement( pSceneElement );
		}
	}

	return true;
}

bool ClearModelSDK::ModelElement::ProcessBinaryNode( IOHelper* reader )
{
	DWORD childCount;
	char  ctype[256];

	reader->read( childCount );

	for (unsigned int i = 0; i < childCount ; i++)
	{
		reader->read(  ctype, 256 );
		string stype = ctype;

		//Check type

		if ( stype == "GlobalTimeSettings" )
		{
			shared_ptr<CGlobalTimeSettings> pSceneElement = shared_ptr<CGlobalTimeSettings>(new CGlobalTimeSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "GlobalCameraSettings" )
		{
			shared_ptr<CGlobalCameraSettings> pSceneElement = shared_ptr<CGlobalCameraSettings>(new CGlobalCameraSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "GlobalLightSettings" )
		{
			shared_ptr<CGlobalLightSettings> pSceneElement = shared_ptr<CGlobalLightSettings>(new CGlobalLightSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if (stype == "EmptyNode")
		{
			shared_ptr<CEmptyNode> pSceneElement = shared_ptr<CEmptyNode>(new CEmptyNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "CameraNode" )
		{
			shared_ptr<CCameraNode> pSceneElement = shared_ptr<CCameraNode>(new CCameraNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "LightNode" )
		{
			shared_ptr<CLightNode> pSceneElement = shared_ptr<CLightNode>(new CLightNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "LODGroudNode" )
		{
			shared_ptr<CLODGroudNode> pSceneElement = shared_ptr<CLODGroudNode>(new CLODGroudNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "MarkerNode" )
		{
			shared_ptr<CMarkerNode> pSceneElement = shared_ptr<CMarkerNode>(new CMarkerNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "MeshNode" )
		{
			shared_ptr<CMeshNode> pSceneElement = shared_ptr<CMeshNode>(new CMeshNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "NurbNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "PatchNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}

		else if ( stype == "SkeletonNode" )
		{
			shared_ptr<CSkeletonNode> pSceneElement = shared_ptr<CSkeletonNode>(new CSkeletonNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			AddElement( pSceneElement );
		}
	}

	return true;
}


bool ClearModelSDK::RootElement::VLoad( TiXmlElement* xmlParent )
{
	for ( TiXmlElement* xmlChild = xmlParent->FirstChildElement(); xmlChild ; xmlChild = xmlChild->NextSiblingElement())
	{
		string sNodeType = xmlChild->Value();


		if ( sNodeType == "GlobalTimeSettings" )
		{
			shared_ptr<CGlobalTimeSettings> pSceneElement = shared_ptr<CGlobalTimeSettings>(new CGlobalTimeSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

 			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "GlobalCameraSettings" )
		{
			shared_ptr<CGlobalCameraSettings> pSceneElement = shared_ptr<CGlobalCameraSettings>(new CGlobalCameraSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "GlobalLightSettings" )
		{
			shared_ptr<CGlobalLightSettings> pSceneElement = shared_ptr<CGlobalLightSettings>(new CGlobalLightSettings());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if (sNodeType == "EmptyNode")
		{
			shared_ptr<CEmptyNode> pSceneElement = shared_ptr<CEmptyNode>(new CEmptyNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "CameraNode" )
		{
			shared_ptr<CCameraNode> pSceneElement = shared_ptr<CCameraNode>(new CCameraNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "LightNode" )
		{
			shared_ptr<CLightNode> pSceneElement = shared_ptr<CLightNode>(new CLightNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "LODGroudNode" )
		{
			shared_ptr<CLODGroudNode> pSceneElement = shared_ptr<CLODGroudNode>(new CLODGroudNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "MarkerNode" )
		{
			shared_ptr<CMarkerNode> pSceneElement = shared_ptr<CMarkerNode>(new CMarkerNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "MeshNode" )
		{
			shared_ptr<CMeshNode> pSceneElement = shared_ptr<CMeshNode>(new CMeshNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "NurbNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "PatchNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( sNodeType == "SkeletonNode" )
		{
			shared_ptr<CSkeletonNode> pSceneElement = shared_ptr<CSkeletonNode>(new CSkeletonNode());

			if (!pSceneElement->VLoad( xmlChild ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}
	}

	return true;
}

bool ClearModelSDK::RootElement::VLoad( IOHelper* reader )
{
	DWORD childCount;
	char  ctype[256];

	reader->read( childCount );

	for (unsigned int i = 0; i < childCount ; i++)
	{
		reader->read(  ctype, 256 );
		string stype = ctype;

		//Check type

		if ( stype == "GlobalTimeSettings" )
		{
			shared_ptr<CGlobalTimeSettings> pSceneElement = shared_ptr<CGlobalTimeSettings>(new CGlobalTimeSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "GlobalCameraSettings" )
		{
			shared_ptr<CGlobalCameraSettings> pSceneElement = shared_ptr<CGlobalCameraSettings>(new CGlobalCameraSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "GlobalLightSettings" )
		{
			shared_ptr<CGlobalLightSettings> pSceneElement = shared_ptr<CGlobalLightSettings>(new CGlobalLightSettings());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if (stype == "EmptyNode")
		{
			shared_ptr<CEmptyNode> pSceneElement = shared_ptr<CEmptyNode>(new CEmptyNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "CameraNode" )
		{
			shared_ptr<CCameraNode> pSceneElement = shared_ptr<CCameraNode>(new CCameraNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "LightNode" )
		{
			shared_ptr<CLightNode> pSceneElement = shared_ptr<CLightNode>(new CLightNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "LODGroudNode" )
		{
			shared_ptr<CLODGroudNode> pSceneElement = shared_ptr<CLODGroudNode>(new CLODGroudNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "MarkerNode" )
		{
			shared_ptr<CMarkerNode> pSceneElement = shared_ptr<CMarkerNode>(new CMarkerNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "MeshNode" )
		{
			shared_ptr<CMeshNode> pSceneElement = shared_ptr<CMeshNode>(new CMeshNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "NurbNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "PatchNode" )
		{
			shared_ptr<CNurbNode> pSceneElement = shared_ptr<CNurbNode>(new CNurbNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}

		else if ( stype == "SkeletonNode" )
		{
			shared_ptr<CSkeletonNode> pSceneElement = shared_ptr<CSkeletonNode>(new CSkeletonNode());

			if (!pSceneElement->VLoad( reader ))
				return false;

			m_pChildren.push_back(pSceneElement);
		}
	}

	return true;
}

TiXmlElement* ClearModelSDK::RootElement::xml()
{
	TiXmlElement* xmlVariable = new TiXmlElement( GetType().c_str() );

	return xmlVariable;
}

bool ClearModelSDK::RootElement::VSave( TiXmlElement* xmlelement )
{
	for (unsigned int i = 0; i < m_pChildren.size() ; i++)
	{
		if (!m_pChildren[i]->VSave( xmlelement ))
			return false;
	}

	return true;
}
