#ifndef NurbNode_H__
#define NurbNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CNurbNode : public ModelElement
	{
	public:
		CNurbNode();
		~CNurbNode();

		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "NurbNode"; }
		virtual TiXmlElement* xml();

	private:
		string m_sName;

		virtual void Delete();

	};
}

#endif
