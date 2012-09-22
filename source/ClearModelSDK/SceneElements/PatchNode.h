#ifndef PatchNode_H__
#define PatchNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CPatchNode : public ModelElement
	{
	public:
		CPatchNode();
		~CPatchNode();
		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "PatchNode"; }
		virtual TiXmlElement* xml();

	private:
		string m_sName;

		virtual void Delete();

	};
}

#endif
