#include "..\ClearModelSDK.h"

ClearModelSDK::CNurbNode::CNurbNode()
{
}

ClearModelSDK::CNurbNode::~CNurbNode()
{

}

bool ClearModelSDK::CNurbNode::VLoad( TiXmlElement* xmlelement )
{
	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CNurbNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CNurbNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CNurbNode::xml()
{
	TiXmlElement* xmlNurb = new TiXmlElement( GetType().c_str() );
	xmlNurb->SetAttribute( "Name", m_sName.c_str() );
	xmlNurb->SetAttribute( "Info", "Unsupported" );

	return xmlNurb;
}
