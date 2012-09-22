#include "ClearModelSDK.h"


ClearModelSDK::CModel::CModel(void)
{
	m_pRootElement = shared_ptr<RootElement>( new RootElement() );
}

ClearModelSDK::CModel::~CModel(void)
{
	Delete();
}

void ClearModelSDK::CModel::Delete()
{
}

bool ClearModelSDK::CModel::Load( std::string filename )
{
	switch(FileType( filename ))
	{
	case BCX:
		return LoadXML( filename );
		break;

	case BCA:
		return LoadASCII( filename );
		break;

	case BCB:
		return LoadBINARY( filename );
		break;

	case UNSUPPORTED:	
		printf("[Error] wrong File format!\n");
		return false;
		break;
	}

	return true;
}

bool ClearModelSDK::CModel::Save( string filename, SaveType mode  )
{
	switch(mode)
	{
	case ASCII:

		break;

	case XML:
		{

		//Test for saving it to XML
		TiXmlDocument doc;
		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
		doc.LinkEndChild( decl );
		TiXmlElement* xmlRoot = new TiXmlElement( "Bloco-XML-Scene" );

		m_pRootElement->VSave( xmlRoot );

		doc.LinkEndChild( xmlRoot );
		doc.SaveFile( filename.c_str() );

		}
		break;

	case BINARY:

		break;
	}


	return true;
}

bool ClearModelSDK::CModel::LoadXML( std::string filename )
{
	//Open the XML-Document
	TiXmlDocument xmlDocument = TiXmlDocument( filename.c_str() );
	if (!xmlDocument.LoadFile())
	{
		Print("Error opening XML-Scene-File: %s\n", filename.c_str());
		return false;
	}

	//RootElement
	TiXmlElement* xmlRootElement = xmlDocument.RootElement();
	if (!xmlRootElement)
	{
		Print("Error XML-File is corrupt\n");
		return false;
	}

	if ( !m_pRootElement->VLoad( xmlRootElement ) )
		return false;

	return true;
}

bool ClearModelSDK::CModel::LoadASCII( std::string filename )
{
	return true;
}

bool ClearModelSDK::CModel::LoadBINARY( std::string filename )
{
	IOHelper* reader = new IOHelper();

	if ( !reader->open(filename, "rb") )
		return false;

	if(!m_pRootElement->VLoad( reader ) )
		return false;

	reader->close();

	SAFE_DELETE( reader );

	return true;
}