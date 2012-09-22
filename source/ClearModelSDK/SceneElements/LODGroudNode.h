#ifndef LODGroudNode_H__
#define LODGroudNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CLODGroudNode : public ModelElement
	{
	public:
		CLODGroudNode();
		~CLODGroudNode() { Delete(); }
		virtual bool VLoad( TiXmlElement* xmlelement );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "LODGroudNode"; }

	private:
		virtual void Delete();

	};
}

#endif
