#include "MarkerNode.h"


ClearModelSDK::CMarkerNode::CMarkerNode()
{
}

bool ClearModelSDK::CMarkerNode::VLoad( TiXmlElement* xmlelement )
{
	m_sName = xmlConverter( xmlelement->Attribute( "Name" ) );
	m_sType = xmlConverter( xmlelement->Attribute( "Type" ) );
	m_sLook = xmlConverter( xmlelement->Attribute( "Look" ) );

	m_fSize = xmlConverter( xmlelement->Attribute( "Size" ) );
	m_Color = xmlConverter( xmlelement->FirstChildElement( "Color" )->FirstChild() );
	m_IKPivot = xmlConverter( xmlelement->FirstChildElement( "IKPivot" )->FirstChild() );

	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CMarkerNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader);
}

void ClearModelSDK::CMarkerNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CMarkerNode::xml()
{
	TiXmlElement* xmlMarker = new TiXmlElement( GetType().c_str() );
	xmlMarker->SetAttribute( "Name", m_sName.c_str() );
	xmlMarker->SetAttribute( "Type", m_sType.c_str() );
	xmlMarker->SetAttribute( "Look", m_sLook.c_str() );

	stringstream stm;
	stm << m_fSize;

	xmlMarker->SetAttribute( "Size", stm.str().c_str() );

	TiXmlElement* xmlColor = new TiXmlElement( "Color" );
	xmlColor->LinkEndChild( xmlText(m_Color) );
	xmlMarker->LinkEndChild( xmlColor );

	TiXmlElement* xmlIKPivot = new TiXmlElement( "IKPivot" );
	xmlIKPivot->LinkEndChild( xmlText(m_IKPivot.str()) );
	xmlMarker->LinkEndChild( xmlIKPivot );

	return xmlMarker;
}
