#include "..\ClearModelSDK.h"


ClearModelSDK::CCameraNode::CCameraNode()
{
}

bool ClearModelSDK::CCameraNode::VLoad( TiXmlElement* xmlElement )
{
	m_sName = xmlElement->Attribute( "Name" );
	m_sProjectionType = xmlElement->Attribute( "ProjectionType" );

	m_PositionOrientation = xmlElement->FirstChildElement( "Position-Orientation" );

	m_ViewingAreaControls = xmlElement->FirstChildElement( "Viewing-Area-Controls" );

	m_DefaultAnimationValues = xmlElement->FirstChildElement( "Default-Animation-Values" );

	return ProcessXMLNode( xmlElement);
}

bool ClearModelSDK::CCameraNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader);
}

void ClearModelSDK::CCameraNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CCameraNode::xml()
{
	TiXmlElement* xmlCamera = new TiXmlElement( GetType().c_str() );

	xmlCamera->SetAttribute( "Name", m_sName.c_str() );
	xmlCamera->SetAttribute( "ProjectionType", m_sProjectionType.c_str() );

	xmlCamera->LinkEndChild( m_PositionOrientation );
	xmlCamera->LinkEndChild( m_ViewingAreaControls );
	xmlCamera->LinkEndChild( m_DefaultAnimationValues );
	
	return xmlCamera;
}

