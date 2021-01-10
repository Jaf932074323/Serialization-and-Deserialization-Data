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
时间:2020-12-013
描述:固定的头和尾的包的解析类
**************************************************************************/
#include <string>
#include "Buffer/Buffer.h"
#include "Buffer/BuffReader.h"
#include "ParsePackage/ParsePackBase.h"
#include "ParsePackage/SpecialPack/PackHeadBase.h"
#include "ParsePackage/SpecialPack/PackTailBase.h"
#include "ParsePackage/PackFactBase.h"
#include "ParsePackage/DealPackInterface.h"

namespace jaf
{
	// 固定的头和尾的包的解析类
	class CParsePackHeadTail :public CParsePackBase
	{
	public:
		// 固定的头和尾的包的解析类的构造函数
		// pHead 包头
		// pTail 包尾
		// rPackFactory 包工厂
		// rDealPack 处理包对象
		CParsePackHeadTail(CPackHeadBase& rHead, CPackTailBase& rTail
			, CPackFactBase& rPackFactory);
		virtual ~CParsePackHeadTail();

		// 有新的数据
		virtual void NewData(const char* pData, size_t nLength);

	protected:
		void Parse();
		// 解析一包数据
		// 返回是否还需要继续解析，当缓冲区中有可能还能解析出包时返回true，不可能解析出时返回false
		bool ParseOne();

	protected:
		CPackHeadBase& m_rHead; // 包头
		CPackTailBase& m_rTail; // 包尾
		CPackFactBase& m_rPackFactory; // 包工厂

		CBuffer m_dataBuffer; // 接收到的数据缓冲区
	};


} // namespace jaf
