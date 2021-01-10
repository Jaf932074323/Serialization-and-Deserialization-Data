//MIT License
//
//Copyright(c) 2021 Jaf932074323 姜安富
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
#include "ParsePackage/PackFactory.h"
#include <assert.h>

namespace jaf
{
	void CPackFactory::RegisterCreateFun(unsigned int nPackageType, CreatePackageFun createFun)
	{
		std::map<unsigned int, CreatePackageFun>::iterator it = m_mapCreateFun.find(nPackageType);
		if (it != m_mapCreateFun.end()) // 没有对应类型的包的创建函数
		{
			throw "类型" + std::to_string(nPackageType) + "的包已经被注册";
		}
		if (!createFun)
		{
			throw "要注册的创建包的函数为空";
		}

		m_mapCreateFun.insert(std::pair<unsigned short, CreatePackageFun>(nPackageType, createFun));
	}

	std::shared_ptr<CPackBase> CPackFactory::Create(unsigned int nPackageType, char* pData, size_t nLen)
	{
		std::map<unsigned int, CreatePackageFun>::iterator it = m_mapCreateFun.find(nPackageType);
		if (it == m_mapCreateFun.end()) // 没有对应类型的包的创建函数
		{
			return std::shared_ptr<CPackBase>(); // 返回一个空指针
		}

		assert(it->second);

		std::shared_ptr<CPackBase> p;
		p = (it->second)(pData, nLen);
		return p;
	}

} // namespace jaf
