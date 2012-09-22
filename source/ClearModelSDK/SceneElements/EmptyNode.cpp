#include "..\ClearModelSDK.h"


ClearModelSDK::CEmptyNode::CEmptyNode()
{
}

bool ClearModelSDK::CEmptyNode::VLoad( TiXmlElement* xmlelement )
{
	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CEmptyNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CEmptyNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CEmptyNode::xml()
{
	TiXmlElement* xmlEmpty = new TiXmlElement( GetType().c_str() );

	return xmlEmpty; 
}
