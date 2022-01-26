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
时间:2020/11/12
描述:对布尔位项的序列化和反序列化
**************************************************************************/
#include "SddInclude/Sdd/SddObject/SddBitObject/SddBitInterface.h"
#include <assert.h>

namespace jaf
{
	class CSddBoolBit :public CSddBitInterface
	{
	public:
		CSddBoolBit(bool& rBool, size_t nBitIndex) :m_rBool(rBool), m_nBitIndex(nBitIndex)
		{
		}

		~CSddBoolBit()
		{
		}

		// 从缓冲区中读取位数据
		// pBuff 缓冲区
		// nLength 缓冲区总长度
		// 成功返回true,失败返回false
		virtual bool BufferToData(const char* pBuff, size_t nLength)
		{
			assert(nLength * 8 > m_nBitIndex); // 缓冲区必须要住够长
			const char* p = pBuff + m_nBitIndex / 8; // 找到要反序列化的字符地址
			size_t nIndex = m_nBitIndex % 8; // 找到反序列化的位索引

			char c = 0x01 << nIndex;
			c &= *p;
			m_rBool = (bool)c;

			return true;
		}

		// 将位数据写入到缓冲区
		// pBuff 缓冲区
		// nLength 缓冲区总长度
		// 成功返回true,失败返回false
		virtual bool DataToBuffer(char* pBuff, size_t nLength)
		{
			assert(nLength * 8 > m_nBitIndex); // 缓冲区必须要住够长
			char* p = pBuff + m_nBitIndex / 8; // 找到要序列化的字符地址
			size_t nIndex = m_nBitIndex % 8; // 找到序列化的位索引

			char c = (char)m_rBool;
			c <<= nIndex;
			*p |= c;

			return true;
		}

	protected:
		bool& m_rBool; // 要序列化的布尔值的引用
		size_t m_nBitIndex; // 序列化到的位索引
	};

} // namespace jaf

