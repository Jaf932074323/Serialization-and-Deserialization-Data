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
时间:2020-12-16
描述:内存读取器
通过这个类能够比较方便的从内存中读取
**************************************************************************/
#include "BuffReaderBase.h"
#include <assert.h>
#include "SddInclude/SddException.h"

namespace jaf
{
	class CBuffReader :public CBuffReaderBase
	{
	public:
		CBuffReader() {}
		// pBuff 要读取内存的地址
		// nLength 要读取内存的长度
		CBuffReader(const char* pBuff, size_t nLength)
			:m_pBuff(pBuff), m_nLength(nLength)
		{}
		virtual ~CBuffReader() {}

		// 依附上一段要被读取的内存，并且读取偏移重置为0
		// pBuff 内存地址
		// nLength 内存长度 不能小于0
		void Attach(const char* pBuff, size_t nLength)
		{
			assert(pBuff != nullptr);
			m_pBuff = pBuff;
			m_nLength = nLength;
			m_nReadOffset = 0;
		}

		// 移除依附的内存
		void Clear()
		{
			m_pBuff = nullptr;
			m_nLength = 0;
			m_nReadOffset = 0;
		}

		// 设置读取偏移
		// nOffset 设置读取偏移 不能小于0，不能大于总长度，否则抛出异常
		void SetReadOffset(size_t nOffset)
		{
			if (nOffset >= m_nLength)
			{
				throw CSddException("偏移位置大于内存总长度.", __FILE__, __LINE__);
			}

			m_nReadOffset = nOffset;
		}
		// 获取读取偏移
		size_t GetReadOffset()
		{
			return m_nReadOffset;
		}

		// 从内存中读取数据
		// pData 要读取数据到的对象的地址 不能为空
		// nLength 要读取的长度
		// return 成功返回true，失败返回false
		// 读取成功后，读取偏移增长读取的长度，失败不变
		bool Read(char* pData, size_t nLength)
		{
			if (pData == nullptr)
			{
				return false;
			}
			if (nLength > m_nLength - m_nReadOffset)
			{
				// 内存数据长度不够
				return false;
			}

			memcpy_s(pData, nLength, m_pBuff + m_nReadOffset, nLength);
			m_nReadOffset += nLength;
			return true;
		}

		// 跳过多个要读取的字符
		// nLength 要跳过的长度
		// return 成功返回true，失败返回false
		// 跳过成功后，读取偏移增长读取的长度，失败不变
		bool SkipRead(size_t nLength)
		{
			if (nLength > m_nLength - m_nReadOffset)
			{
				return false;
			}

			m_nReadOffset += nLength;
			return true;
		}

		// 搜索子内存
		// pSeekContent 被搜索内容的首地址
		// nSeekcontentLength 被搜索内容的长度
		// rIndex 返回被搜索到内容的相对于偏移处的索引
		// 返回是否搜索到
		bool SeekAtOffset(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex)
		{
			for (size_t i = m_nReadOffset; i < m_nLength; ++i)
			{
				size_t j = 0;
				for (; j < nSeekContentLength; ++j)
				{
					if (m_pBuff[i + j] != pSeekContent[j])
					{
						break;
					}
				}
				if (j >= nSeekContentLength)
				{
					rIndex = i;
					return true;
				}
			}

			return false;
		}

	protected:
		const char* m_pBuff = nullptr; // 要读取的内存地址
		size_t m_nLength = 0; // 要读取的内存地址的长度
		size_t m_nReadOffset = 0; // 读取数据偏移，每次读取都是冲偏移处读取
	};

} // namespace jaf

