#pragma once
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
/**************************************************************************
作者:姜安富
时间:2020-12-09
描述:可序列化数据包工厂接口
**************************************************************************/
#include <map>
#include <string>
#include <assert.h>
#include "PackFactBase.h"

namespace jaf
{
	// 序列化包的工厂
	class CPackFactory :public CPackFactBase
	{
	public:
		CPackFactory() {}; // 隐藏构造函数
		~CPackFactory() {};
	public:
		// 注册创建包的函数
		// nPackageType 包类型
		// createFun 创建包的函数
		virtual void RegisterCreateFun(unsigned int nPackageType, CreatePackageFun createFun)
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

			m_mapCreateFun.insert(std::pair<unsigned int, CreatePackageFun>(nPackageType, createFun));
		}

		// 用包类型和字节数组创建包
		// nPackageType 包类型
		// pData 用于创建包的数据
		// nLen pData数据的长度
		virtual std::shared_ptr<CPackBase> Create(unsigned int nPackageType, char* pData, size_t nLen)
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

	protected:
		std::map<unsigned int, CreatePackageFun> m_mapCreateFun; // 用于保存每种包的类型与其创建函数
	};

} // namespace jaf

