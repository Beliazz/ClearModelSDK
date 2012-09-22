#ifndef ModelElement_H__
#define ModelElement_H__

#include "ClearModelSDK.h"

namespace ClearModelSDK
{
	class CLEARMODELSDK_API ModelElement
	{
	public:
		ModelElement(){};
		~ModelElement() 
		{ 
			Delete(); 
		}

		virtual bool VSave( TiXmlElement* );
		virtual bool VLoad( TiXmlElement* );
		virtual bool VLoad( IOHelper*  );
		virtual string GetType()=0;

		void AddElement( shared_ptr<ModelElement> pElement) { return m_pChildren.push_back(pElement); }
		DWORD GetChildCount()								{ return m_pChildren.size(); }
		shared_ptr<ModelElement> GetChild( DWORD index )	{ return m_pChildren[index]; }

		virtual string str() {return "Unsupported"; }
		virtual TiXmlElement* xml();

		float* GetGlobalMatrix() { return m_GlobalPosition.m_data; }

		vector<shared_ptr<ModelElement>> m_pChildren;
		Matrix m_GlobalPosition;

		virtual void Delete();
		bool ProcessXMLNode( TiXmlElement* xmlelement );
		bool ProcessBinaryNode( IOHelper* reader );
	};

	class CLEARMODELSDK_API RootElement : public ModelElement
	{
	public:
		virtual bool VLoad( TiXmlElement* );
		virtual bool VLoad( IOHelper*  );
		virtual bool VSave( TiXmlElement* );
		virtual string GetType() { return "Root"; };
		virtual TiXmlElement* xml();

	private:
		string m_sName;
	};
}



#endif