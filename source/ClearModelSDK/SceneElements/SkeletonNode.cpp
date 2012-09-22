#include "SkeletonNode.h"


ClearModelSDK::CSkeletonNode::CSkeletonNode()
{
}

ClearModelSDK::CSkeletonNode::~CSkeletonNode()
{

}

bool ClearModelSDK::CSkeletonNode::VLoad( TiXmlElement* xmlelement )
{
	m_sName = xmlConverter( xmlelement->Attribute("Name") );
	m_sType = xmlConverter( xmlelement->Attribute("Type") );

	if (m_sType == "Limb")
		m_fLimbLengh = xmlConverter( xmlelement->Attribute("LimbLengh") );
	
	else if (m_sType == "Limb Node")
		m_fLimbSize = xmlConverter( xmlelement->Attribute("LimbSize") );
	
	else if (m_sType == "Root")
		m_fRootSize = xmlConverter( xmlelement->Attribute("RootSize") );
	
	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CSkeletonNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader );
}

void ClearModelSDK::CSkeletonNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CSkeletonNode::xml()
{
	TiXmlElement* xmlSkeleton = new TiXmlElement( GetType().c_str() );
	xmlSkeleton->SetAttribute( "Name", m_sName.c_str() );
	xmlSkeleton->SetAttribute( "Type", m_sType.c_str() );
	
	if (m_sType == "Limb")
	{
		stringstream stm;
		stm << m_fLimbLengh;

		xmlSkeleton->SetAttribute( "LimbLengh", stm.str().c_str() );
	}
	else if (m_sType == "Limb Node")
	{
		stringstream stm;
		stm << m_fLimbSize;

		xmlSkeleton->SetAttribute( "LimbSize", stm.str().c_str() );
	}
	else if (m_sType == "Root")
	{
		stringstream stm;
		stm << m_fRootSize;

		xmlSkeleton->SetAttribute( "RootSize", stm.str().c_str() );
	}

	TiXmlElement* xmlColor = new TiXmlElement( "Color" );
	xmlColor->LinkEndChild( xmlText(m_Color) );

	xmlSkeleton->LinkEndChild( xmlColor );

	return xmlSkeleton;
}
