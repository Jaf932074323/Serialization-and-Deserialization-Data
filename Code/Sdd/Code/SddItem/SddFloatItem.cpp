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
#include "SddItem\SddFloatItem.h"
#include "SddException.h"

namespace jaf
{
	CSddFloatItem::CSddFloatItem(float& rVariate) :m_f(rVariate)
	{
	}

	CSddFloatItem::~CSddFloatItem()
	{
	}

	std::shared_ptr<CSddInterface> CSddFloatItem::Creation(float& rVariate)
	{
		std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddFloatItem>(rVariate);
		if (pItem == nullptr)
		{
			throw CSddException("创建float数据项失败", __FILE__, __LINE__);
		}
		return pItem;
	}

	bool CSddFloatItem::BufferToData(CBuffReaderBase& rBuffReader)
	{
		return rBuffReader.Read((char*)&m_f, sizeof(float));
	}

	void CSddFloatItem::DataToBuffer(CBufferBase& rBuffer)
	{
		rBuffer.Write((char*)&m_f, sizeof(float));
	}

	size_t CSddFloatItem::GetBufferLength()
	{
		return sizeof(float);
	}

} // namespace jaf
