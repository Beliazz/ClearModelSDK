#ifndef IOHelper__H_
#define IOHelper__H_

#include "ClearModelSDK.h"

namespace ClearModelSDK
{

	class  CLEARMODELSDK_API IOHelper
	{
	public:
		IOHelper()
		{

		}
		~IOHelper()
		{
			close();
		}

		bool open( string filename, const char* mode )
		{
			if( fopen_s(&m_pFile, filename.c_str(), mode ) != NULL)
				return false;

			if ( m_pFile == NULL)
				return false;

			return true;
		}
		void close()
		{
			fclose(m_pFile);
		}

		void write( bool value )		
		{
			write( (char*)&value, sizeof(bool) );
		}
		void write( int value )		
		{
			write( (char*)&value, sizeof(int) );
		}
		void write( WORD value )
		{
			write( (char*)&value, sizeof(WORD) );
		}
		void write( DWORD value )
		{
			write( (char*)&value, sizeof(DWORD) );
		}
		void write( double value )
		{
			write( (char*)&value, sizeof(double) );
		}
		void write( float value )
		{
			write( (char*)&value, sizeof(float) );
		}
		void write( Color value )
		{
			write( (char*)&value, sizeof(float), 4 );
		}

		void read( bool &value )		
		{
			read( (char*)&value, sizeof(bool) );
		}
		void read( int& value )		
		{
			read( (char*)&value, sizeof(int) );
		}
		void read( WORD& value )
		{
			read( (char*)&value, sizeof(WORD) );
		}
		void read( DWORD& value )
		{
			read( (char*)&value, sizeof(DWORD) );
		}
		void read( double& value )
		{
			read( (char*)&value, sizeof(double) );
		}
		void read( float& value )
		{
			read( (char*)&value, sizeof(float) );
		}
		void read( Color &value )
		{
			read( (char*)&value, sizeof(float), 4 );
		}

		void write(const void* data, DWORD size, DWORD count = 1 )
		{
			fwrite( data, size, count, m_pFile );
		}
		void read( void* data, DWORD size, DWORD count = 1 )
		{
			fread( data, size, count, m_pFile );
		}

	private:
		FILE* m_pFile;

	};
}

#endif