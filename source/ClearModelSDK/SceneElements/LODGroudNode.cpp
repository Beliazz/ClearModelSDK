#include "LODGroudNode.h"


ClearModelSDK::CLODGroudNode::CLODGroudNode()
{
}

bool ClearModelSDK::CLODGroudNode::VLoad( TiXmlElement* xmlelement )
{
	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CLODGroudNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CLODGroudNode::Delete()
{

}