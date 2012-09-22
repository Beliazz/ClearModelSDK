#include "..\ClearModelSDK.h"


ClearModelSDK::CGlobalTimeSettings::CGlobalTimeSettings()
{
	m_sTimeMode = "30 fps";
	m_fStart    = 0.0f;
	m_fEnd		= 0.0f;
}

bool ClearModelSDK::CGlobalTimeSettings::VLoad( TiXmlElement* xmlElement  )
{
	//Mode
	m_sTimeMode = xmlElement->Attribute( "Mode" );

	//Start
	TiXmlElement* xmlStartTime = xmlElement->FirstChildElement( "Start" );
	m_fStart = xmlConverter(xmlStartTime->FirstChild());

	//End
	TiXmlElement* xmlEndTime = xmlElement->FirstChildElement( "End" );
	m_fEnd = xmlConverter(xmlEndTime->FirstChild());

	return ProcessXMLNode( xmlElement);
}

bool ClearModelSDK::CGlobalTimeSettings::VLoad( IOHelper* reader )
{
	//Time Mode
	char mode[32];
	reader->read( mode, 32 );
	m_sTimeMode = mode;

	//Start Time
	reader->read( m_fStart );

	//End Time
	reader->read( m_fEnd );

	return ProcessBinaryNode( reader);
}

std::string ClearModelSDK::CGlobalTimeSettings::str()
{
	stringstream stm;

	stm << m_sTimeMode << endl;
	stm << m_fStart << endl;
	stm << m_fEnd;

	return stm.str();
}

TiXmlElement* ClearModelSDK::CGlobalTimeSettings::xml()
{
	TiXmlElement* xmlTimeSettings = new TiXmlElement( GetType().c_str() );
	xmlTimeSettings->SetAttribute("Mode", m_sTimeMode.c_str() );
	
	TiXmlElement* xmlStartTime = new TiXmlElement("Start");
	xmlStartTime->SetAttribute( "Format", "Seconds" );
	xmlStartTime->LinkEndChild( xmlText(m_fStart) );
	xmlTimeSettings->LinkEndChild( xmlStartTime );

	TiXmlElement* xmlEndTime = new TiXmlElement("End");
	xmlEndTime->SetAttribute( "Format", "Seconds" );
	xmlEndTime->LinkEndChild( xmlText(m_fEnd) );
	xmlTimeSettings->LinkEndChild( xmlEndTime );

	return xmlTimeSettings;
}

void ClearModelSDK::CGlobalTimeSettings::Delete()
{
	
}
