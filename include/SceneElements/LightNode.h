#ifndef LightNode_H__
#define LightNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	struct sLightGobo
	{
		sLightGobo(){}
		sLightGobo( TiXmlElement* xmlelement )
		{

		}

		string  m_sFilename;
		bool m_bGroundProjection;
		bool m_bVolumetricProjection;
		bool m_bFrontVolumetricProjection;

		TiXmlElement* xml()
		{
			TiXmlElement* xmlGobo = new TiXmlElement( "Gobo" );
			xmlGobo->SetAttribute( "Filename", m_sFilename.c_str() );

			if (m_bGroundProjection)
				xmlGobo->SetAttribute( "DrawGroundProjection", "true" );
			else
				xmlGobo->SetAttribute( "DrawGroundProjection", "false" );

			if (m_bVolumetricProjection)
				xmlGobo->SetAttribute( "VolumetricProjection", "true" );
			else
				xmlGobo->SetAttribute( "VolumetricProjection", "false" );

			if (m_bFrontVolumetricProjection)
				xmlGobo->SetAttribute( "FrontVolumetricProjection", "true" );
			else
				xmlGobo->SetAttribute( "FrontVolumetricProjection", "false" );

			return xmlGobo;
		}
	};

	class CLightNode : public ModelElement
	{
	public:
		CLightNode();
		~CLightNode();
		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "LightNode"; }

		virtual TiXmlElement* xml();

		//Access functions
		string GetName()			 { return m_sName; }
		string GetLightType()		 { return m_sType; }
		bool   IsCastLight()		 { return m_bCastLight; }
		bool   HasGobo()			 { return m_bHasGobo; }
		Color  GetDefaultColor()	 { return m_DefaultColor; }
		float  GetDefaultIntensity() { return m_fDefaultIntensity; }
		float  GetDefaultConeAngle() { return m_fDefaultConeAngle; }
		float  GetDefaulFog()		 { return m_fDefaultFog; }
		sLightGobo GetGobo()		 { return m_Gobo; }

		//Set functions
		void SetName( string value )			{ m_sName = value; }
		void SetLightType( string value )		{ m_sType = value; }
		void EnableCastLight( bool value )		{ m_bCastLight = value; }
		void SetHasGobo( bool value )			{ m_bHasGobo = value; }
		void SetDefaultColor( Color value )		{ m_DefaultColor = value; }
		void SetDefaultIntensity( float value )	{ m_fDefaultIntensity = value; }
		void SetDefaultConeAngle( float value )	{ m_fDefaultConeAngle = value; }
		void SetDefaulFog( float value )		{ m_fDefaultFog = value; }
		void SetGobo( sLightGobo value )		{ m_Gobo = value; }

	private:
		string m_sName;
		string m_sType;
		bool   m_bCastLight;

		bool m_bHasGobo;
		sLightGobo m_Gobo;

		//Default Animation Values
		Color m_DefaultColor;
		float m_fDefaultIntensity;
		float m_fDefaultConeAngle;
		float m_fDefaultFog;

		virtual void Delete();

	};
}

#endif
