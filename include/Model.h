#ifndef Model_H__
#define Model_H__

#include "ClearModelSDK.h"

namespace ClearModelSDK
{
	class CLEARMODELSDK_API CModel
	{
	public:
		CModel(void);
		~CModel(void);

		bool Load( std::string filename );
		bool Save( std::string filename, SaveType mode );

		inline shared_ptr<RootElement> GetRootNode() { return m_pRootElement; }

	private:
		void Delete();
		bool LoadXML(	std::string filename );
		bool LoadASCII(	std::string filename );
		bool LoadBINARY( std::string filename );

		shared_ptr<RootElement> m_pRootElement;
	};
}

#endif
