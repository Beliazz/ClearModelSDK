#include "..\ClearModelSDK.h"


ClearModelSDK::CPatchNode::CPatchNode()
{
}

ClearModelSDK::CPatchNode::~CPatchNode()
{

}

bool ClearModelSDK::CPatchNode::VLoad( TiXmlElement* xmlelement )
{
	m_sName = xmlConverter( xmlelement->Attribute( "Name" ) );

	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CPatchNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CPatchNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CPatchNode::xml()
{
	TiXmlElement* xmlPatch = new TiXmlElement( GetType().c_str() );
	xmlPatch->SetAttribute( "Name", m_sName.c_str() );
	xmlPatch->SetAttribute( "Info", "Unsupported" );

	return xmlPatch;
}
