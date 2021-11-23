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
#include "SddInclude/Sdd/SddBase.h"
#include "SddInclude/SddEndian/SddEndianManage.h"

namespace jaf
{
	CSddBase::CSddBase(void) :m_rEndian(CSddEndianManage::GetDefaultEndian())
	{
		m_pItems = new std::list<std::shared_ptr<CSddInterface>>();
	}

	CSddBase::CSddBase(E_ENDIAN eEndian) : m_rEndian(CSddEndianManage::GetEndian(eEndian))
	{
		m_pItems = new std::list<std::shared_ptr<CSddInterface>>();
	}

	CSddBase::~CSddBase(void)
	{
		delete (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
	}

	bool CSddBase::BufferToData(CBuffReaderBase& rBuffReader)
	{
		std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
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
		std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
		{
			(*it)->DataToBuffer(rBuffer);
		}
	}

	size_t CSddBase::GetBufferLength()
	{
		size_t nLength = 0;
		std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
		for (std::list<std::shared_ptr<CSddInterface>>::iterator it = pItems->begin(); it != pItems->end(); ++it)
		{
			nLength += (*it)->GetBufferLength();
		}
		return nLength;
	}


	// 添加子项
	void CSddBase::AddChildItem(std::shared_ptr<CSddInterface> pChildItem)
	{
		std::list<std::shared_ptr<CSddInterface>>* pItems = (std::list<std::shared_ptr<CSddInterface>>*)m_pItems;
		pItems->push_back(pChildItem);
	}

} // namespace jaf

