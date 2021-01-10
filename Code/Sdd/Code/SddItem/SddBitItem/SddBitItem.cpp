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
#include "SddItem/SddBitItem/SddBitItem.h"
#include <assert.h>
#include "SddException.h"

namespace jaf
{
	CSddBitItem::CSddBitItem(size_t nLength) : m_nLength(nLength), m_vectorBuff(m_nLength)
	{
	}

	CSddBitItem::~CSddBitItem()
	{

	}

	bool CSddBitItem::BufferToData(CBuffReaderBase& rBuffReader)
	{
		rBuffReader.Read(m_vectorBuff.data(), m_nLength);

		for (std::list<std::shared_ptr<CSddBitInterface>>::iterator it = m_listBit.begin(); it != m_listBit.end(); ++it)
		{
			if (!(*it)->BufferToData(m_vectorBuff.data(), m_nLength))
			{
				return false;
			}
		}

		return true;
	}

	void CSddBitItem::DataToBuffer(CBufferBase& rBuffer)
	{
		for (std::list<std::shared_ptr<CSddBitInterface>>::iterator it = m_listBit.begin(); it != m_listBit.end(); ++it)
		{
			(*it)->DataToBuffer(m_vectorBuff.data(), m_nLength);
		}

		rBuffer.Write(m_vectorBuff.data(), m_nLength);
	}

	// 获取序列化或反序列化使用的字节长度
	size_t CSddBitItem::GetBufferLength()
	{
		return m_nLength;
	}

	void CSddBitItem::AddChildBitItem(std::shared_ptr<CSddBitInterface> pChildBitItem)
	{
		m_listBit.push_back(pChildBitItem);
	}

} // namespace jaf
