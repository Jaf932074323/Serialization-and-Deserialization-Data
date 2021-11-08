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
#include "SddInclude/SddItem\SddBitItem\SddCharBit.h"
#include <assert.h>

namespace jaf
{
	CSddCharBit::CSddCharBit(char& rChar, size_t nBitIndex, size_t nBitSize)
		: m_rChar(rChar)
		, m_nBitIndex(nBitIndex)
		, m_nBitSize(nBitSize)
	{
		assert(nBitSize <= 8);
	}

	CSddCharBit::~CSddCharBit()
	{
	}

	bool CSddCharBit::BufferToData(const char* pBuff, size_t nLength)
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

	bool CSddCharBit::DataToBuffer(char* pBuff, size_t nLength)
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

	void CSddCharBit::BitCopy(char* pDst, size_t nDstIndex, const char* pSrc, size_t nSrcIndex, size_t nBitSize)
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

} // namespace jaf
