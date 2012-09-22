#ifndef SkeletonNode_H__
#define SkeletonNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CSkeletonNode : public ModelElement
	{
	public:
		CSkeletonNode();
		~CSkeletonNode();
		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "SkeletonNode"; }
		virtual TiXmlElement* xml();
		
		//Access functions
		string GetName()			{ return m_sName; }
		string GetSkeletonType()	{ return m_sType; }
		float GetLimbLengh()		{ return m_fLimbLengh; }
		float GetLimbSize()			{ return m_fLimbSize; }
		float GetRootSize()			{ return m_fRootSize; }
		Color GetColor()		{ return m_Color; }

		//Set functions
		void SetName( string value )		 { m_sName = value; }
		void SetSkeletonType( string value ) { m_sType = value; }
		void SetLimbLengh( float value )	 { m_fLimbLengh = value; }
		void SetLimbSize( float value )		 { m_fLimbSize = value; }
		void SetRootSize( float value )		 { m_fRootSize = value; }
		void SetColor( Color value )	 { m_Color = value; }

	private:
		virtual void Delete();

		string m_sName;
		string m_sType; 
		float  m_fLimbLengh;
		float  m_fLimbSize;
		float  m_fRootSize;
		Color  m_Color;
	};
}

#endif
