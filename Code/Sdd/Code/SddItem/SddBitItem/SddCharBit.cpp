//MIT License
//
//Copyright(c) 2021 Jaf932074323 ������
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
		assert(nLength * 8 > m_nBitIndex + m_nBitSize); // ����������Ҫס����

		const char* p = pBuff + m_nBitIndex / 8; // �ҵ��ַ���ַ
		size_t nIndex = m_nBitIndex % 8; // �ҵ���ʼ��λ����

		if ((nIndex + m_nBitSize) <= 8)
		{
			BitCopy(&m_rChar, 0, p, nIndex, m_nBitSize); // һ�ξͿ������
		}
		else
		{
			// Ҫ�ֳ�2�ο���
			size_t nCopyBitNumbeer = 8 - nIndex;
			BitCopy(&m_rChar, 0, p, nIndex, nCopyBitNumbeer); // ������λ����
			BitCopy(&m_rChar, nCopyBitNumbeer, p + 1, 0, m_nBitSize - nCopyBitNumbeer); // ������λ����
		}

		return true;
	}

	bool CSddCharBit::DataToBuffer(char* pBuff, size_t nLength)
	{
		assert(pBuff != nullptr);
		assert((nLength * 8) > m_nBitIndex); // ����������Ҫ�㹻��

		char* p = pBuff + m_nBitIndex / 8; // �ҵ��ַ���ַ
		size_t nIndex = m_nBitIndex % 8; // �ҵ���ʼ��λ����

		if ((nIndex + m_nBitSize) <= 8)
		{
			BitCopy(p, nIndex, &m_rChar, 0, m_nBitSize); // һ�ξͿ������
		}
		else
		{
			// Ҫ�ֳ�2�ο���
			size_t nCopyBitNumbeer = 8 - nIndex;
			BitCopy(p, nIndex, &m_rChar, 0, nCopyBitNumbeer); // ������λ����
			BitCopy(p + 1, 0, &m_rChar, nCopyBitNumbeer, m_nBitSize - nCopyBitNumbeer); // ������λ����
		}

		return true;
	}

	void CSddCharBit::BitCopy(char* pDst, size_t nDstIndex, const char* pSrc, size_t nSrcIndex, size_t nBitSize)
	{
		assert(pDst != nullptr);
		assert(pSrc != nullptr);
		assert((nDstIndex + nBitSize) <= 8);
		assert((nSrcIndex + nBitSize) <= 8);

		unsigned char c = ((char)0x01 << nBitSize) - 1; // ��ȡnBitSizeΪ������1
		unsigned char cTemp = (c << nSrcIndex) & (*pSrc); // ��ȡԴ�е�������λ

		cTemp = (nSrcIndex <= nDstIndex) ? (cTemp >> nSrcIndex << nDstIndex) : (cTemp << nDstIndex >> nSrcIndex); // �ƶ���Ŀ��λ��

		// ��Ŀ���ֽڵĶ�Ӧλ��Ϊ0
		c = ~(c << nDstIndex);
		*pDst = (*pDst) & c;

		*pDst |= cTemp;
	}

} // namespace jaf
