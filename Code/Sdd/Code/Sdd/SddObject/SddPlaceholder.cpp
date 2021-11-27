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
#include "SddInclude/Sdd/SddObject/SddPlaceholder.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	CSddPlaceholder::CSddPlaceholder(size_t nLength, char c) :m_nLength(nLength), m_c(c)
	{
	}

	CSddPlaceholder::~CSddPlaceholder()
	{
	}

	std::shared_ptr<CSddPlaceholder> CSddPlaceholder::Creation(size_t nLength, char c)
	{
		std::shared_ptr<CSddPlaceholder> pItem = std::make_shared<CSddPlaceholder>(nLength, c);
		if (pItem == nullptr)
		{
			throw CSddException("创建占位符数据项失败", __FILE__, __LINE__);
		}
		return pItem;
	}

	bool CSddPlaceholder::BufferToData(CBuffReaderBase& rBuffReader)
	{
		return rBuffReader.SkipRead(m_nLength);
	}

	void CSddPlaceholder::DataToBuffer(CBufferBase& rBuffer)
	{
		rBuffer.WriteChar(m_c, m_nLength);
	}

	size_t CSddPlaceholder::GetBufferLength()
	{
		return m_nLength;
	}

} // namespace jaf
