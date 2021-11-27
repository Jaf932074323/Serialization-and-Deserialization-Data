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
	// 序列化和反序列化 用户扩展行为
	class CSddExtendAct:public CSddInterface
	{
	public:
		// 构造函数
		// funBufferToData 用户定义从缓冲区中读取数据行为
		// funDataToBuffer 用户定义从写入数据到缓冲区行为
		CSddExtendAct(std::function<bool(CBuffReaderBase&)> funBufferToData
			, std::function<void(CBufferBase&)> funDataToBuffer)
			:m_funBufferToData(funBufferToData), m_funDataToBuffer(funDataToBuffer)
		{
		}

		CSddExtendAct(std::function<bool(CBuffReaderBase&)> funBufferToData)
			:m_funBufferToData(funBufferToData)
		{
		}

		CSddExtendAct(std::function<void(CBufferBase&)> funDataToBuffer)
			:m_funDataToBuffer(funDataToBuffer)
		{
		}

		~CSddExtendAct()
		{
		}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddExtendAct> Creation(std::function<bool(CBuffReaderBase&)> funBufferToData
			, std::function<void(CBufferBase&)> funDataToBuffer)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funBufferToData, funDataToBuffer);
			if (pItem == nullptr)
			{
				throw CSddException("创建用户扩展行为对象失败", __FILE__, __LINE__);
			}
			return pItem;
		}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddExtendAct> Creation(std::function<bool(CBuffReaderBase&)> funBufferToData)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funBufferToData);
			if (pItem == nullptr)
			{
				throw CSddException("创建用户扩展行为对象失败", __FILE__, __LINE__);
			}
			return pItem;
		}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddExtendAct> Creation(std::function<void(CBufferBase&)> funDataToBuffer)
		{
			std::shared_ptr<CSddExtendAct> pItem = std::make_shared<CSddExtendAct>(funDataToBuffer);
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
			if (m_funBufferToData == nullptr)
			{
				return true;
			}

			return m_funBufferToData(rBuffReader);
		}
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			if (m_funDataToBuffer != nullptr)
			{
				m_funDataToBuffer(rBuffer);
			}
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return 0;
		}

	protected:
		std::function<bool(CBuffReaderBase& rBuffReader)> m_funBufferToData = nullptr;
		std::function<void(CBufferBase& rBuffer)> m_funDataToBuffer = nullptr;
	};

}
