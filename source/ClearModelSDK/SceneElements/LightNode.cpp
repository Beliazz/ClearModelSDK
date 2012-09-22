#include "LightNode.h"


ClearModelSDK::CLightNode::CLightNode()
{
}

ClearModelSDK::CLightNode::~CLightNode()
{
	Delete();
}

bool ClearModelSDK::CLightNode::VLoad( TiXmlElement* xmlelement )
{
	m_sName = xmlConverter( xmlelement->Attribute( "Name" ) );
	m_sType = xmlConverter( xmlelement->Attribute( "Type" ) );
	m_bCastLight = xmlConverter( xmlelement->Attribute( "CastLight" ) );
	m_bHasGobo	 = xmlConverter( xmlelement->Attribute( "Gobo" ) );

	if (m_bHasGobo)
		m_Gobo = xmlelement->FirstChildElement( "Gobo" );

	TiXmlElement* xmlDefaultAnimationValues = xmlelement->FirstChildElement( "Default-Animation-Values" );

	m_DefaultColor		= xmlConverter( xmlDefaultAnimationValues->FirstChildElement( "Color" )->FirstChild() );
	m_fDefaultIntensity = xmlConverter( xmlDefaultAnimationValues->FirstChildElement( "DefaultIntensity" )->FirstChild() );
	m_fDefaultConeAngle = xmlConverter( xmlDefaultAnimationValues->FirstChildElement( "DefaultConeAngle" )->FirstChild() );
	m_fDefaultFog		= xmlConverter( xmlDefaultAnimationValues->FirstChildElement( "DefaultFog" )->FirstChild() );

	return ProcessXMLNode( xmlelement);
}

bool ClearModelSDK::CLightNode::VLoad( IOHelper* reader )
{
	return ProcessBinaryNode( reader);
}

void ClearModelSDK::CLightNode::Delete()
{

}

TiXmlElement* ClearModelSDK::CLightNode::xml()
{
	TiXmlElement* xmlLight = new TiXmlElement( GetType().c_str() );
	xmlLight->SetAttribute( "Name", m_sName.c_str() );
	xmlLight->SetAttribute( "Type", m_sType.c_str() );

	if (m_bCastLight)
		xmlLight->SetAttribute( "CastLight", "true" );
	else 
		xmlLight->SetAttribute( "CastLight", "false" );

	if (m_bHasGobo)
	{
		xmlLight->SetAttribute( "Gobo", "true" );
		xmlLight->LinkEndChild( m_Gobo.xml() );
	}
	else
		xmlLight->SetAttribute( "Gobo", "false" );


	//Default Animation Values
	TiXmlElement* xmlDefaultAnimation = new TiXmlElement( "Default-Animation-Values" );

	TiXmlElement* xmlColor = new TiXmlElement( "Color" );
	xmlColor->LinkEndChild( xmlText( m_DefaultColor ) );
	xmlDefaultAnimation->LinkEndChild( xmlColor );

	TiXmlElement* xmlDefaultIntensity = new TiXmlElement( "DefaultIntensity" );
	xmlDefaultIntensity->LinkEndChild( xmlText( m_fDefaultIntensity ) );
	xmlDefaultAnimation->LinkEndChild( xmlDefaultIntensity );

	TiXmlElement* xmlDefaultConeAngle = new TiXmlElement( "DefaultConeAngle" );
	xmlDefaultConeAngle->LinkEndChild( xmlText( m_fDefaultConeAngle ) );
	xmlDefaultAnimation->LinkEndChild( xmlDefaultConeAngle );

	TiXmlElement* xmlDefaultFog = new TiXmlElement( "DefaultFog" );
	xmlDefaultFog->LinkEndChild( xmlText( m_fDefaultFog ) );
	xmlDefaultAnimation->LinkEndChild( xmlDefaultFog );

	xmlLight->LinkEndChild( xmlDefaultAnimation );

	return xmlLight;
}


