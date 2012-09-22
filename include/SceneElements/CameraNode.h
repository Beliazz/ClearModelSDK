#ifndef CameraNode_H__
#define CameraNode_H__

#include "..\ClearModelSDK.h"

namespace ClearModelSDK
{
	class CCameraPositionOrientation
	{
	public:
		CCameraPositionOrientation(){}
		CCameraPositionOrientation( TiXmlElement* xmlelement )
		{
			m_Position	  = xmlConverter( xmlelement->FirstChildElement( "Position" )->FirstChild() );
			m_sTargetName = xmlConverter( xmlelement->FirstChildElement( "CameraInterest" )->FirstChild() );
			m_sTargetUpName	=  xmlConverter( xmlelement->FirstChildElement( "CameraUpTarget" )->FirstChild() );
			m_InterestPosition = xmlConverter( xmlelement->FirstChildElement( "CameraInterest-Position" )->FirstChild() );
			m_Up = xmlConverter( xmlelement->FirstChildElement( "UpVector" )->FirstChild() );
			m_fRoll = xmlConverter( xmlelement->FirstChildElement( "Roll" )->FirstChild() ); 
		}
		
		operator TiXmlElement*()
		{
			TiXmlElement* xmlPositionOrientation = new TiXmlElement( "Position-Orientation" );
			TiXmlElement* xmlPosition = new TiXmlElement( "Position" );
			xmlPosition->LinkEndChild( xmlText( m_Position.str() ) );

			TiXmlElement* xmlCameraInterest = new TiXmlElement( "CameraInterest" );
			xmlCameraInterest->LinkEndChild( xmlText( m_sTargetName ) );

			TiXmlElement* xmlCameraInterestPos = new TiXmlElement( "CameraInterest-Position" );
			xmlCameraInterestPos->LinkEndChild( xmlText( m_InterestPosition.str() ) );

			TiXmlElement* xmlCameraUpTarget = new TiXmlElement( "CameraUpTarget" );
			xmlCameraUpTarget->LinkEndChild( xmlText( m_sTargetUpName ) );

			TiXmlElement* xmlUpVector = new TiXmlElement( "UpVector" );
			xmlUpVector->LinkEndChild( xmlText( m_Up.str() ) );

			TiXmlElement* xmlRoll = new TiXmlElement( "Roll" );
			xmlRoll->LinkEndChild( xmlText( m_fRoll ) );


			xmlPositionOrientation->LinkEndChild( xmlPosition );
			xmlPositionOrientation->LinkEndChild( xmlCameraInterest );
			xmlPositionOrientation->LinkEndChild( xmlCameraInterestPos );
			xmlPositionOrientation->LinkEndChild( xmlCameraUpTarget );
			xmlPositionOrientation->LinkEndChild( xmlUpVector );
			xmlPositionOrientation->LinkEndChild( xmlRoll );

			return xmlPositionOrientation;
		}

		Vector m_Position;
		string m_sTargetName;
		string m_sTargetUpName;
		Vector m_InterestPosition;
		Vector m_Up;
		float m_fRoll;
	};

	class CCameraViewingAreaControls
	{
	public:
		CCameraViewingAreaControls(){}
		CCameraViewingAreaControls( TiXmlElement* xmlelement )
		{
			m_sFormat = xmlelement->Attribute( "Format" );
			m_sAspectRatioMode = xmlelement->Attribute( "Aspect-Ratio-Mode" );

			if ( m_sAspectRatioMode == "Window Size" )
			{
				m_fAspectWidth  = xmlConverter( xmlelement->Attribute( "Aspect-Width" ) );
				m_fAspectHeight = xmlConverter( xmlelement->Attribute( "Aspect-Height" ) );
			}

			m_fPixelAspectRatio = xmlConverter( xmlelement->FirstChildElement( "Pixel-Ratio" )->FirstChild() );
			m_fNearPlane = xmlConverter( xmlelement->FirstChildElement( "Near-Plane" )->FirstChild() );
			m_fFarPlane  = xmlConverter( xmlelement->FirstChildElement( "Far-Plane" )->FirstChild() );
			m_bLockMode  = xmlConverter( xmlelement->FirstChildElement( "Mouse-Lock" )->FirstChild() );
		}

		operator TiXmlElement*()
		{
			TiXmlElement* xmlViewingAreaControls = new TiXmlElement( "Viewing-Area-Controls" );
			xmlViewingAreaControls->SetAttribute( "Format", m_sFormat.c_str() );
			xmlViewingAreaControls->SetAttribute( " Aspect-Ratio-Mode", m_sAspectRatioMode.c_str() );

			if (m_sAspectRatioMode == "Window Size")
			{
				stringstream stm;

				stm << m_fAspectWidth;
				xmlViewingAreaControls->SetAttribute( "Aspect-Width", stm.str().c_str() );

				stm = stringstream("");
				stm << m_fAspectHeight;
				xmlViewingAreaControls->SetAttribute( "Aspect-Height", stm.str().c_str() );
			}


			TiXmlElement* xmlPixelRatio = new TiXmlElement( "Pixel-Ratio" );
			xmlPixelRatio->LinkEndChild( xmlText( m_fPixelAspectRatio ) );

			TiXmlElement* xmlNearPlane = new TiXmlElement( "Near-Plane" );
			xmlNearPlane->LinkEndChild( xmlText( m_fNearPlane ) );

			TiXmlElement* xmlFarPlane = new TiXmlElement( "Far-Plane" );
			xmlFarPlane->LinkEndChild( xmlText( m_fFarPlane ) );

			TiXmlElement* xmlMouseLock = new TiXmlElement( "Mouse-Lock" );
			xmlMouseLock->LinkEndChild( xmlText( m_bLockMode ) );

			xmlViewingAreaControls->LinkEndChild( xmlPixelRatio );
			xmlViewingAreaControls->LinkEndChild( xmlNearPlane );
			xmlViewingAreaControls->LinkEndChild( xmlFarPlane );
			xmlViewingAreaControls->LinkEndChild( xmlMouseLock );
			
			return xmlViewingAreaControls;
		}

		string m_sFormat;
		string m_sAspectRatioMode;
		float m_fAspectWidth;
		float m_fAspectHeight;
		float m_fPixelAspectRatio;
		float m_fNearPlane;
		float m_fFarPlane;
		bool  m_bLockMode;
	};

	class CCameraDefaultAnimationValues
	{
	public:
		CCameraDefaultAnimationValues(){}
		CCameraDefaultAnimationValues( TiXmlElement* xmlelement )
		{
			m_fDefaultFieldOfView = xmlConverter( xmlelement->FirstChildElement( "Default-Field-of-View" )->FirstChild() );
			m_fDefaultFieldOfViewX = xmlConverter( xmlelement->FirstChildElement( "Default-Field-of-View-X" )->FirstChild() );
			m_fDefaultFieldOfViewY = xmlConverter( xmlelement->FirstChildElement( "Default-Field-of-View-Y" )->FirstChild() );
			m_fDefaultOpticalCenterX = xmlConverter( xmlelement->FirstChildElement( "Default-Optical-Center-X" )->FirstChild() );
			m_fDefaultOpticalCenterY = xmlConverter( xmlelement->FirstChildElement( "Default-Optical-Center-Y" )->FirstChild() );
			m_fDefaultRoll = xmlConverter( xmlelement->FirstChildElement( "Default-Roll" )->FirstChild() );
		}

		operator TiXmlElement*()
		{
			TiXmlElement* xmlDefaultAnimationValues = new TiXmlElement( "Default-Animation-Values" );

			TiXmlElement* xmlDefaultFieldofView = new TiXmlElement( "Default-Field-of-View" );
			xmlDefaultFieldofView->LinkEndChild( xmlText( m_fDefaultFieldOfView ) );

			TiXmlElement* xmlDefaultFieldofViewX = new TiXmlElement( "Default-Field-of-View-X" );
			xmlDefaultFieldofViewX->LinkEndChild( xmlText( m_fDefaultFieldOfViewX ) );

			TiXmlElement* xmlDefaultFieldofViewY = new TiXmlElement( "Default-Field-of-View-Y" );
			xmlDefaultFieldofViewY->LinkEndChild( xmlText( m_fDefaultFieldOfViewY ) );

			TiXmlElement* xmlDefaultOpticalCenterX = new TiXmlElement( "Default-Optical-Center-X" );
			xmlDefaultOpticalCenterX->LinkEndChild( xmlText( m_fDefaultOpticalCenterX ) );

			TiXmlElement* xmlDefaultOpticalCenterY = new TiXmlElement( "Default-Optical-Center-Y" );
			xmlDefaultOpticalCenterY->LinkEndChild( xmlText( m_fDefaultOpticalCenterY ) );

			TiXmlElement* xmlDefaultRoll = new TiXmlElement( "Default-Roll" );
			xmlDefaultRoll->LinkEndChild( xmlText( m_fDefaultRoll ) );


			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultFieldofView );
			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultFieldofViewX );
			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultFieldofViewY );
			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultOpticalCenterX );
			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultOpticalCenterY );
			xmlDefaultAnimationValues->LinkEndChild( xmlDefaultRoll );

			return xmlDefaultAnimationValues;
		}

		float m_fDefaultFieldOfView;
		float m_fDefaultFieldOfViewX;
		float m_fDefaultFieldOfViewY;
		float m_fDefaultOpticalCenterX;
		float m_fDefaultOpticalCenterY;
		float m_fDefaultRoll;
	};

	class CCameraNode : public ModelElement
	{
	public:
		CCameraNode();
		~CCameraNode() { Delete(); }
		virtual bool VLoad( TiXmlElement* pScene );
		virtual bool VLoad( IOHelper* reader );

		virtual string GetType() { return "CameraNode"; }
		virtual TiXmlElement* xml();

		//Access Functions
		string GetName()				{ return m_sName; }
		string GetProjectionType()		{ return m_sProjectionType; }

		Vector GetPosition()			{ return m_PositionOrientation.m_Position; }
		Vector GetInterestPosition()	{ return m_PositionOrientation.m_InterestPosition; }
		Vector GetUp()					{ return m_PositionOrientation.m_Up; }
		float  GetRoll()				{ return m_PositionOrientation.m_fRoll; }
		string GetTargetName()			{ return m_PositionOrientation.m_sTargetName; }
		string GetTargetUpName()		{ return m_PositionOrientation.m_sTargetUpName; }

		string GetVACFormat()			{ return m_ViewingAreaControls.m_sFormat; }
		string GetVACAspectRatioMode()	{ return m_ViewingAreaControls.m_sAspectRatioMode; }
		float  GetVACAspectWidth()		{ return m_ViewingAreaControls.m_fAspectWidth; }
		float  GetVACAspectHeight()		{ return m_ViewingAreaControls.m_fAspectHeight; }
		float  GetVACPixelAspectRatio()	{ return m_ViewingAreaControls.m_fPixelAspectRatio; }
		float  GetVACNearPlane()		{ return m_ViewingAreaControls.m_fNearPlane; }
		float  GetVACFarPlane()			{ return m_ViewingAreaControls.m_fFarPlane; }
		bool   GetVACLockMode()			{ return m_ViewingAreaControls.m_bLockMode; }

		float  GetDAVFieldOfView()		{ return m_DefaultAnimationValues.m_fDefaultFieldOfView; }
		float  GetDAVFieldOfViewX()		{ return m_DefaultAnimationValues.m_fDefaultFieldOfViewX; }
		float  GetDAVFieldOfViewY()		{ return m_DefaultAnimationValues.m_fDefaultFieldOfViewY; }
		float  GetDAVOpticalCenterX()	{ return m_DefaultAnimationValues.m_fDefaultOpticalCenterX; }
		float  GetDAVOpticalCenterY()	{ return m_DefaultAnimationValues.m_fDefaultOpticalCenterY; }
		float  GetDAVRoll()				{ return m_DefaultAnimationValues.m_fDefaultRoll; }

		//Set Functions
		void SetName( string value )				{ m_sName = value;  }
		void SetProjectionType( string value )		{ m_sProjectionType = value; }

		void SetPosition( Vector value )			{ m_PositionOrientation.m_Position = value; }
		void SetInterestPosition( Vector value )	{ m_PositionOrientation.m_InterestPosition = value; }
		void SetUp( Vector value )					{ m_PositionOrientation.m_Up = value; }
		void SetRoll( float value )					{ m_PositionOrientation.m_fRoll = value; }
		void SetTargetName( string value )			{ m_PositionOrientation.m_sTargetName = value; }
		void SetTargetUpName( string value )		{ m_PositionOrientation.m_sTargetUpName = value; }

		void SetVACFormat( string value )			{ m_ViewingAreaControls.m_sFormat = value; }
		void SetVACAspectRatioMode( string value )	{ m_ViewingAreaControls.m_sAspectRatioMode = value; }
		void SetVACAspectWidth( float value )		{ m_ViewingAreaControls.m_fAspectWidth = value; }
		void SetVACAspectHeight( float value )		{ m_ViewingAreaControls.m_fAspectHeight = value; }
		void SetVACPixelAspectRatio( float value )	{ m_ViewingAreaControls.m_fPixelAspectRatio = value; }
		void SetVACNearPlane( float value )			{ m_ViewingAreaControls.m_fNearPlane = value; }
		void SetVACFarPlane( float value )			{ m_ViewingAreaControls.m_fFarPlane = value; }
		void SetVACLockMode( bool value )			{ m_ViewingAreaControls.m_bLockMode = value; }

		void SetDAVFieldOfView( float value )		{ m_DefaultAnimationValues.m_fDefaultFieldOfView = value; }
		void SetDAVFieldOfViewX( float value )		{ m_DefaultAnimationValues.m_fDefaultFieldOfViewX = value; }
		void SetDAVFieldOfViewY( float value )		{ m_DefaultAnimationValues.m_fDefaultFieldOfViewY = value; }
		void SetDAVOpticalCenterX( float value )	{ m_DefaultAnimationValues.m_fDefaultOpticalCenterX; }
		void SetDAVOpticalCenterY( float value )	{ m_DefaultAnimationValues.m_fDefaultOpticalCenterY; }
		void SetDAVRoll( float value )				{ m_DefaultAnimationValues.m_fDefaultRoll; }

	private:
		string m_sName;
		string m_sProjectionType;

		CCameraPositionOrientation m_PositionOrientation;
		CCameraViewingAreaControls m_ViewingAreaControls;
		CCameraDefaultAnimationValues m_DefaultAnimationValues;

		virtual void Delete();

	};
}
#endif
