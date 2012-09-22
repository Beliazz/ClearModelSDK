#include "ClearModelSDK.h"

using namespace ClearModelSDK;

string   ClearModelSDK::FilenameTitle( string filename )
{
	std::string title = filename;

	for (int i = filename.length() - 1; i >= 0 ; i--)
	{
		if (filename[i] == '\\')
		{
			title.erase(title.begin(), title.begin() + i + 1);
			break;
		}
	}

	return title;
}

string   ClearModelSDK::FilenameExtension( string filename )
{
	std::string extension = filename;

	for (int i = filename.length() - 1; i >= 0 ; i--)
	{
		if (filename[i] == '.')
		{
			extension.erase(extension.begin(), extension.begin() + i + 1);
			break;
		}
	}

	return extension;
}

LoadType ClearModelSDK::FileType( string filename )
{
	string extension = FilenameExtension( filename );

	if ( extension == "BCX" || extension == "bcx" )
		return BCX;

	if ( extension == "BCA" || extension == "bca" )
		return BCA;

	if ( extension == "BCB" || extension == "bcb" )
		return BCB;

	return UNSUPPORTED;
}

bool CLEARMODELSDK_API::Print( LPCSTR log, ... )
{
#ifdef _DEBUG // only output messages when debugging

	static CHAR buffer[4096];		
	static SYSTEMTIME time;

	//////////////////////////////////////////////////////////////////////////
	// get arguments
	va_list pArgList;						
	if (sizeof(va_list) + sizeof(log) > 4096)
	{	
		return false;
	}

	va_start (pArgList, log);	
	vsprintf_s(buffer, log, pArgList);
	va_end (pArgList);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// build log msg
	GetSystemTime(&time);
	char msg[4096];
	sprintf_s(msg, "ModelSDK - %02i:%02i:%02i.%03i - %s\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, buffer);

	//////////////////////////////////////////////////////////////////////////
	// post message to the output window
	_RPT0(0, msg);

	//////////////////////////////////////////////////////////////////////////
	// reset static data
	ZeroMemory(&msg[0], sizeof(4096));
	ZeroMemory(&time, sizeof(time));

#endif // _DEBUG

	return true;
}

