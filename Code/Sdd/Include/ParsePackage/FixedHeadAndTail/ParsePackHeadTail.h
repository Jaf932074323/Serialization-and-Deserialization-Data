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
			, CPackFactBase& rPackFactory)
			:m_rHead(rHead), m_rTail(rTail), m_rPackFactory(rPackFactory)
		{
		}

		virtual ~CParsePackHeadTail()
		{}

		// 有新的数据
		virtual void NewData(const char* pData, size_t nLength)
		{
			m_dataBuffer.Write(pData, nLength);
			Parse();
		}

	protected:

		void Parse()
		{
			while (ParseOne())
			{
			}
		}

		// 解析一包数据
		// 返回是否还需要继续解析，当缓冲区中有可能还能解析出包时返回true，不可能解析出时返回false
		bool ParseOne()
		{
			if (m_dataBuffer.GetWriteLength() <= 0)
			{
				return false;
			}

			// 查找头
			size_t nHeadIndex;
			if (!m_rHead.SeekHead(m_dataBuffer.GetBuffer(), m_dataBuffer.GetWriteLength(), nHeadIndex))
			{
				// 如果没有找到头，则nHeadIndex前面的数据都是无效的
				m_dataBuffer.PopFront(nHeadIndex);
				return false;
			}
			// 如果找到了，也要移除nHeadIndex前面的数据
			m_dataBuffer.PopFront(nHeadIndex);

			CBuffReader buffReader;
			buffReader.Attach(m_dataBuffer.GetBuffer(), m_dataBuffer.GetWriteLength());

			// 读取头
			m_rHead.BufferToData(buffReader);
			if (!m_rHead.Check())
			{
				m_dataBuffer.PopFront(1);
				return true;
			}

			size_t nContentLen = m_rHead.GetContentLen();

			size_t nTotalLen = m_rHead.GetBufferLength() + m_rTail.GetBufferLength() + nContentLen; // 总长度
			if (nContentLen > m_dataBuffer.GetWriteLength()) // 长度不够
			{
				return false;
			}

			// 读取内容
			std::vector<char> vectorContent(nContentLen);
			buffReader.Read(vectorContent.data(), nContentLen);

			// 读取尾
			m_rTail.BufferToData(buffReader);
			if (!m_rTail.Check(m_dataBuffer.GetBuffer(), nContentLen))
			{
				m_dataBuffer.PopFront(1);
				return true;
			}

			std::shared_ptr<CPackBase> pPack = m_rPackFactory.Create(m_rHead.GetType(), vectorContent.data(), nContentLen);
			if (pPack != nullptr)
			{
				m_pDealPack->Deal(m_rHead.GetType(), pPack);
			}
			m_dataBuffer.PopFront(nTotalLen);

			return true;
		}

	protected:
		CPackHeadBase& m_rHead; // 包头
		CPackTailBase& m_rTail; // 包尾
		CPackFactBase& m_rPackFactory; // 包工厂

		CBuffer m_dataBuffer; // 接收到的数据缓冲区
	};


} // namespace jaf
