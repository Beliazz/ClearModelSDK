#ifndef ClearModelSDK_API_h__
#define ClearModelSDK_API_h__



#ifdef CLEARMODELSDK_EXPORTS
	#define CLEARMODELSDK_API __declspec(dllexport)
#else
	#define CLEARMODELSDK_API __declspec(dllimport)
#endif

#define SAFE_RELEASE(x)			if(x){x->Release(); x = NULL;}
#define SAFE_DELETE(x)			if(x){delete x; x = NULL;}
#define SAFE_DELETE_ARRAY(x)	if(x){delete[] x; x = NULL;}

#pragma warning(disable : 4251)
#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WindowsX.h>

//STL
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#include <vector>

//XML
#include "tinystr.h"
#include "tinyxml.h"
#pragma comment(lib,"tinyxml.lib")

// bullet
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>

using namespace std;

#include "Definitions.h"
#include "IOHelper.h"
#include "ModelElement.h"
#include "Model.h"
#include "GlobalTimeSettings/GlobalTimeSettings.h"
#include "GlobalCameraSettings/GlobalCameraSettings.h"
#include "GlobalLightSettings/GlobalLightSettings.h"
#include "SceneElements/CameraNode.h"
#include "SceneElements/EmptyNode.h"
#include "SceneElements/LightNode.h"
#include "SceneElements/LODGroudNode.h"
#include "SceneElements/MarkerNode.h"
#include "SceneElements/MeshNode.h"
#include "SceneElements/NurbNode.h"
#include "SceneElements/PatchNode.h"
#include "SceneElements/SkeletonNode.h"

#endif // ClearModelSDK_API_h__
