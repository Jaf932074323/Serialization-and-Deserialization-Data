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
	class CSddCharBit :public CSddBitInterface
	{
	public:
		CSddCharBit(char& rChar, size_t nBitIndex, size_t nBitSize)
			: m_rChar(rChar)
			, m_nBitIndex(nBitIndex)
			, m_nBitSize(nBitSize)
		{
			assert(nBitSize <= 8);
		}

		~CSddCharBit()
		{
		}

		// 从缓冲区中读取位数据
		// pBuff 缓冲区
		// nLength 缓冲区总长度
		// 成功返回true,失败返回false
		virtual bool BufferToData(const char* pBuff, size_t nLength)
		{
			assert(pBuff != nullptr);
			assert(nLength * 8 > m_nBitIndex + m_nBitSize); // 缓冲区必须要住够长

			const char* p = pBuff + m_nBitIndex / 8; // 找到字符地址
			size_t nIndex = m_nBitIndex % 8; // 找到开始的位索引

			if ((nIndex + m_nBitSize) <= 8)
			{
				BitCopy(&m_rChar, 0, p, nIndex, m_nBitSize); // 一次就拷贝完成
			}
			else
			{
				// 要分成2次拷贝
				size_t nCopyBitNumbeer = 8 - nIndex;
				BitCopy(&m_rChar, 0, p, nIndex, nCopyBitNumbeer); // 拷贝低位部分
				BitCopy(&m_rChar, nCopyBitNumbeer, p + 1, 0, m_nBitSize - nCopyBitNumbeer); // 拷贝高位部分
			}

			return true;
		}

		// 将位数据写入到缓冲区
		// pBuff 缓冲区
		// nLength 缓冲区总长度
		// 成功返回true,失败返回false
		virtual bool DataToBuffer(char* pBuff, size_t nLength)
		{
			assert(pBuff != nullptr);
			assert((nLength * 8) > m_nBitIndex); // 缓冲区必须要足够长

			char* p = pBuff + m_nBitIndex / 8; // 找到字符地址
			size_t nIndex = m_nBitIndex % 8; // 找到开始的位索引

			if ((nIndex + m_nBitSize) <= 8)
			{
				BitCopy(p, nIndex, &m_rChar, 0, m_nBitSize); // 一次就拷贝完成
			}
			else
			{
				// 要分成2次拷贝
				size_t nCopyBitNumbeer = 8 - nIndex;
				BitCopy(p, nIndex, &m_rChar, 0, nCopyBitNumbeer); // 拷贝低位部分
				BitCopy(p + 1, 0, &m_rChar, nCopyBitNumbeer, m_nBitSize - nCopyBitNumbeer); // 拷贝高位部分
			}

			return true;
		}

	protected:
		// 拷贝一个字节中连续几位到另一个字节中
		// pDst 要拷贝到的目标字节地址
		// nDstIndex 目标字节的开始位置
		// pSrc 被拷贝的源字节地址
		// nSrcIndex 源字节的开始位置
		// nBitSize 拷贝的位数
		// 源字节和目标字节都不能超过一个字节的范围
		void BitCopy(char* pDst, size_t nDstIndex, const char* pSrc, size_t nSrcIndex, size_t nBitSize)
		{
			assert(pDst != nullptr);
			assert(pSrc != nullptr);
			assert((nDstIndex + nBitSize) <= 8);
			assert((nSrcIndex + nBitSize) <= 8);

			unsigned char c = ((char)0x01 << nBitSize) - 1; // 获取nBitSize为连续的1
			unsigned char cTemp = (c << nSrcIndex) & (*pSrc); // 获取源中的连续几位

			cTemp = (nSrcIndex <= nDstIndex) ? (cTemp >> nSrcIndex << nDstIndex) : (cTemp << nDstIndex >> nSrcIndex); // 移动到目标位置

			// 将目标字节的对应位设为0
			c = ~(c << nDstIndex);
			*pDst = (*pDst) & c;

			*pDst |= cTemp;
		}

	protected:
		char& m_rChar; // 要序列化的布尔值的引用
		size_t m_nBitIndex; // 序列化到的位的开始索引
		size_t m_nBitSize; // 要序列化的位数量 
	};

} // namespace jaf

