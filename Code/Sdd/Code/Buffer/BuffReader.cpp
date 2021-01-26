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
#include "Buffer/BuffReader.h"
#include <assert.h>
#include "SddException.h"

namespace jaf
{
	CBuffReader::CBuffReader()
	{
	}

	CBuffReader::CBuffReader(const char* pBuff, size_t nLength)
		:m_pBuff(pBuff), m_nLength(nLength)
	{
	}

	CBuffReader::~CBuffReader()
	{
	}

	void CBuffReader::Attach(const char* pBuff, size_t nLength)
	{
		assert(pBuff != nullptr);
		m_pBuff = pBuff;
		m_nLength = nLength;
		m_nReadOffset = 0;
	}

	void CBuffReader::Clear()
	{
		m_pBuff = nullptr;
		m_nLength = 0;
		m_nReadOffset = 0;
	}

	void CBuffReader::SetReadOffset(size_t nOffset)
	{
		if (nOffset >= m_nLength)
		{
			throw CSddException("偏移位置大于内存总长度.", __FILE__, __LINE__);
		}

		m_nReadOffset = nOffset;
	}

	size_t CBuffReader::GetReadOffset()
	{
		return m_nReadOffset;
	}

	bool CBuffReader::Read(char* pData, size_t nLength)
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

	bool CBuffReader::SkipRead(size_t nLength)
	{
		if (nLength > m_nLength - m_nReadOffset)
		{
			return false;
		}

		m_nReadOffset += nLength;
		return true;
	}

	bool CBuffReader::SeekAtOffset(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex)
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

} // namespace jaf
