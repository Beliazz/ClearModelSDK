#include "..\ClearModelSDK.h"


ClearModelSDK::CGlobalLightSettings::CGlobalLightSettings()
{
	m_colAmbient = Color(1.0f,1.0f,1.0f,1.0f);
}

bool ClearModelSDK::CGlobalLightSettings::VLoad( TiXmlElement* xmlElement  )
{
	TiXmlElement* xmlAmbientColor = xmlElement->FirstChildElement( "AmbientColor" );
	m_colAmbient = xmlConverter( xmlAmbientColor->FirstChild() );

	return ProcessXMLNode( xmlElement);
}

bool ClearModelSDK::CGlobalLightSettings::VLoad( IOHelper* reader )
{
	reader->read( m_colAmbient );

	return ProcessBinaryNode( reader);
}

void ClearModelSDK::CGlobalLightSettings::Delete()
{

}

std::string ClearModelSDK::CGlobalLightSettings::str()
{
	stringstream stm;

	stm << m_colAmbient.str() << endl;

	return stm.str();
}

TiXmlElement* ClearModelSDK::CGlobalLightSettings::xml()
{
	TiXmlElement* xmlLightSettings = new TiXmlElement( GetType().c_str() );

	TiXmlElement* xmlAmbientColor = new TiXmlElement("AmbientColor");
	xmlAmbientColor->LinkEndChild( xmlText( m_colAmbient ) );
	xmlLightSettings->LinkEndChild( xmlAmbientColor );

	return xmlLightSettings;
}

std::string ClearModelSDK::CGlobalLightSettings::GetType()
{
	return "GlobalLightSettings";
}
