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
#include "SddItem/SddVariLenStringItem.h"
#include <vector>
#include "SddException.h"

namespace jaf
{
	CSddVariLenStringItem::CSddVariLenStringItem(std::string& str) :m_str(str)
	{
	}

	CSddVariLenStringItem::~CSddVariLenStringItem()
	{
	}

	std::shared_ptr<CSddInterface> CSddVariLenStringItem::Creation(std::string& value)
	{
		std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddVariLenStringItem>(value);
		if (pItem == nullptr)
		{
			throw CSddException("创建字符串数据项失败", __FILE__, __LINE__);
		}
		return pItem;
	}

	bool CSddVariLenStringItem::BufferToData(CBuffReaderBase& rBuffReader)
	{
		// 查找字符串长度
		size_t nPos = 0;
		if(!rBuffReader.SeekAtOffset("\0",1, nPos))
		{
			return false;
		}

		std::vector<char> vector;
		vector.resize(nPos);
		vector[nPos] = 0;

		if (!rBuffReader.Read(vector.data(), nPos))
		{
			return false;
		}
		m_str = vector.data();
		return true;
	}

	void CSddVariLenStringItem::DataToBuffer(CBufferBase& rBuffer)
	{
		std::vector<char> vector;
		size_t nLen = m_str.size() + 1;
		vector.resize(nLen);
		vector[nLen - 1] = 0;

		memcpy_s(vector.data(), nLen, m_str.data(), nLen);
		rBuffer.Write(vector.data(), nLen);
	}

	// 获取序列化或反序列化使用的字节长度
	size_t CSddVariLenStringItem::GetBufferLength()
	{
		return m_str.size() + 1;
	}

} // namespace jaf
