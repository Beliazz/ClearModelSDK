#ifndef GlobalTimeSettings_H__
#define GlobalTimeSettings_H__

#include "ClearModelSDK.h"

namespace ClearModelSDK
{
	class CGlobalTimeSettings : public ModelElement
	{
	public:
		CGlobalTimeSettings();
		~CGlobalTimeSettings() { Delete(); }

		virtual bool VLoad( TiXmlElement* xmlElement_ );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "GlobalTimeSettings"; }

		virtual string str();
		virtual TiXmlElement* xml();
		
		string GetTimeMode()  { return m_sTimeMode; }
		float  GetStartTime() { return m_fStart; }
		float  GetEndTime()   { return m_fEnd; }

		void SetTimeMode( string mode )  { m_sTimeMode = mode; }
		void SetStartTime( float start ) { m_fStart = start; }
		void SetEndTime( float end )     { m_fEnd = end; }

	private:
		virtual void Delete();

		string m_sTimeMode;
		float  m_fStart;
		float  m_fEnd;
	};
}

#endif
