#pragma once
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
/**************************************************************************
作者:姜安富
时间:2020/11/22
描述:序列化和反序列化 用户扩展行为
**************************************************************************/
#include <functional>
#include <memory>
#include <string>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	class CSddExtendAction:public CSddInterface
	{
	public:
		CSddExtendAction(const std::function<bool(CBuffReaderBase&)>& funBufferToData
			, const std::function<void(CBufferBase&)>& funDataToBuffer)
			:m_funBufferToData(funBufferToData), m_funDataToBuffer(funDataToBuffer)
		{
		}

		~CSddExtendAction()
		{
		}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddInterface> Creation(const std::function<void(CBuffReaderBase&)>& funBufferToData
			, const std::function<void(CBufferBase&)>& funDataToBuffer)
		{
			std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddExtendAction>(funBufferToData, funDataToBuffer);
			if (pItem == nullptr)
			{
				throw CSddException("创建用户扩展行为对象失败", __FILE__, __LINE__);
			}
			return pItem;
		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return m_funBufferToData(rBuffReader);
		}
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			m_funDataToBuffer(rBuffer);
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return 0;
		}

	protected:
		std::function<bool(CBuffReaderBase& rBuffReader)> m_funBufferToData;
		std::function<void(CBufferBase& rBuffer)> m_funDataToBuffer;
	};

}
