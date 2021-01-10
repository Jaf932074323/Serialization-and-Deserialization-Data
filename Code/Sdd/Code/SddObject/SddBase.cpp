//MIT License
//
//Copyright(c) 2021 Jaf932074323 ½ª°²¸»
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
#include "SddObject\SddBase.h"
#include "SddEndian\SddEndianManage.h"

namespace jaf
{
	CSddBase::CSddBase(void) :m_rEndian(CSddEndianManage::GetDefaultEndian())
	{}

	CSddBase::CSddBase(E_ENDIAN eEndian) : m_rEndian(CSddEndianManage::GetEndian(eEndian))
	{
	}

	CSddBase::~CSddBase(void)
	{}

	bool CSddBase::BufferToData(CBuffReaderBase& rBuffReader)
	{
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = m_childItems.begin(); it != m_childItems.end(); ++it)
		{
			if (!(*it)->BufferToData(rBuffReader))
			{
				return false;
			}
		}
		return true;
	}

	void CSddBase::DataToBuffer(CBufferBase& rBuffer)
	{
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = m_childItems.begin(); it != m_childItems.end(); ++it)
		{
			(*it)->DataToBuffer(rBuffer);
		}
	}

	size_t CSddBase::GetBufferLength()
	{
		size_t nLength = 0;
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = m_childItems.begin(); it != m_childItems.end(); ++it)
		{
			nLength += (*it)->GetBufferLength();
		}
		return nLength;
	}

} // namespace jaf

