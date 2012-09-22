#ifndef MarkerNode_H__
#define MarkerNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CMarkerNode : public ModelElement
	{
	public:
		CMarkerNode();
		~CMarkerNode() { Delete(); }
		virtual bool VLoad( TiXmlElement* xmlelement );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "MarkerNode"; }
		virtual TiXmlElement* xml();

		//Access functions
		string GetName()		{ return m_sName; }
		string GetMarkerType()	{ return m_sType; }
		string GetMarkerLook()	{ return m_sLook; }
		float  GetMarkerSize()	{ return m_fSize; }
		Color  GetColor()		{ return m_Color; }
		Vector GetIKPivot()		{ return m_IKPivot; }

		//Set functions
		void SetName( string value )		{ m_sName = value; }
		void SetMarkerType( string value )	{ m_sType = value; }
		void SetMarkerLook( string value )	{ m_sLook = value; }
		void  SetMarkerSize( float value )	{ m_fSize = value; }
		void  SetColor( Color value )		{ m_Color = value; }
		void SetIKPivot( Vector value )		{ m_IKPivot = value; }

	private:
		string m_sName;
		string m_sType;
		string m_sLook;
		float  m_fSize;
		Color  m_Color;
		Vector m_IKPivot;

		virtual void Delete();

	};
}

#endif
