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
描述:可序列化数据包工厂基类
**************************************************************************/
#include <functional>
#include <memory>
#include "PackBase.h"

namespace jaf
{
	// 预定义创建包的函数
	typedef std::function<std::shared_ptr<CPackBase>(char* pData, size_t nLen)> CreatePackageFun;

	// 可序列化数据包工厂
	class CPackFactBase
	{
	public:
		CPackFactBase() {};
		virtual ~CPackFactBase() {};
		// 注册创建包的函数
		// nPackageType 包类型
		// createFun 创建包的函数
		virtual void RegisterCreateFun(unsigned int nPackageType, CreatePackageFun createFun) = 0;

		// 用包类型和字节数组创建包
		// nPackageType 包类型
		// pData 用于创建包的数据
		// nLen pData数据的长度
		virtual std::shared_ptr<CPackBase> Create(unsigned int nPackageType, char* pData, size_t nLen) = 0;
	};

} // namespace jaf
