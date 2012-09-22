#ifndef GlobalCameraSettings_H__
#define GlobalCameraSettings_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{

	class CGlobalCameraSettings : public ModelElement
	{
	public:
		CGlobalCameraSettings();
		~CGlobalCameraSettings() { Delete(); }

		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "GlobalCameraSettings"; }
		virtual string str();
		virtual TiXmlElement* xml();

		//Access/Set Functions
		string GetDefaultCamera() { return m_sDefaultCamera; }
		void   SetDefaultCamera( string name ) { m_sDefaultCamera = name;  }

	private:
		virtual void Delete();
		string m_sDefaultCamera;
	};

}

#endif
