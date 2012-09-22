#include "..\ClearModelSDK.h"

ClearModelSDK::CGlobalCameraSettings::CGlobalCameraSettings()
{
	m_sDefaultCamera = "UNKOWN";
}

bool ClearModelSDK::CGlobalCameraSettings::VLoad( TiXmlElement* xmlElement )
{
	//DefaultCamera
	TiXmlElement* xmlDefaultCamera = xmlElement->FirstChildElement( "DefaultCamera" );
	
	m_sDefaultCamera = xmlConverter(xmlDefaultCamera->FirstChild());

	return ProcessXMLNode( xmlElement);
}

bool ClearModelSDK::CGlobalCameraSettings::VLoad( IOHelper* reader )
{
	//DefaultCamera
	char cDefaultCamera[256];
	reader->read( cDefaultCamera, 256 );
	m_sDefaultCamera = cDefaultCamera;

	return ProcessBinaryNode( reader);
}

void ClearModelSDK::CGlobalCameraSettings::Delete()
{

}

std::string ClearModelSDK::CGlobalCameraSettings::str()
{
	stringstream stm;

	stm << m_sDefaultCamera << endl;

	return stm.str();
}

TiXmlElement* ClearModelSDK::CGlobalCameraSettings::xml()
{
	TiXmlElement* xmlCameraSettings = new TiXmlElement( GetType().c_str() );

	TiXmlElement* xmlDefaultCamera = new TiXmlElement("DefaultCamera");
	xmlDefaultCamera->LinkEndChild( xmlText( m_sDefaultCamera ) );
	xmlCameraSettings->LinkEndChild( xmlDefaultCamera );

	return xmlCameraSettings;
}