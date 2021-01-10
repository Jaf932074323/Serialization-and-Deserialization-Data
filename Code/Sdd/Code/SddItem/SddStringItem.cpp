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
#include "SddItem/SddStringItem.h"
#include <vector>
#include "SddException.h"

namespace jaf
{
	CSddStringItem::CSddStringItem(std::string& str, size_t nLength) :m_str(str), m_nLength(nLength)
	{
	}

	CSddStringItem::~CSddStringItem()
	{
	}

	std::shared_ptr<CSddInterface> CSddStringItem::Creation(std::string& value, size_t nLength)
	{
		std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddStringItem>(value, nLength);
		if (pItem == nullptr)
		{
			throw CSddException("创建字符串数据项失败", __FILE__, __LINE__);
		}
		return pItem;
	}

	bool CSddStringItem::BufferToData(CBuffReaderBase& rBuffReader)
	{
		std::vector<char> vector;
		vector.resize(m_nLength + 1);
		vector[m_nLength] = 0;
		if (!rBuffReader.Read(vector.data(), m_nLength))
		{
			return false;
		}
		m_str = vector.data();
		return true;
	}

	void CSddStringItem::DataToBuffer(CBufferBase& rBuffer)
	{
		std::vector<char> vector;
		vector.resize(m_nLength + 1);
		vector[m_nLength] = 0;

		size_t nLength = m_nLength < m_str.size() ? m_nLength : m_str.size();
		memcpy_s(vector.data(), m_nLength, m_str.data(), nLength);
		rBuffer.Write(vector.data(), m_nLength);
	}

	// 获取序列化或反序列化使用的字节长度
	size_t CSddStringItem::GetBufferLength()
	{
		return m_nLength;
	}

} // namespace jaf
