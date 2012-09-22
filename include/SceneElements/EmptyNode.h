#ifndef EmptyNode_H__
#define EmptyNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CEmptyNode : public ModelElement
	{
	public:
		CEmptyNode();
		~CEmptyNode() { Delete(); }
		virtual bool VLoad( TiXmlElement* xmlelement );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "EmptyNode"; }

		virtual TiXmlElement* xml();

	private:
		virtual void Delete();

	};
}

#endif
