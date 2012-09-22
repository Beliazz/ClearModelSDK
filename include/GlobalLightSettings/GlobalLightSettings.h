#ifndef GlobalLightSettings_H__
#define GlobalLightSettings_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{

	class CGlobalLightSettings : public ModelElement
	{
	public:
		CGlobalLightSettings();
		~CGlobalLightSettings() { Delete(); }

		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType();
		virtual string str();
		virtual TiXmlElement* xml();

		Color GetAmbientColor() { return m_colAmbient; }
		void  SetAmbientColor( Color color ) { m_colAmbient = color; }

	private:
		virtual void Delete();

		Color m_colAmbient;
	};

}

#endif
