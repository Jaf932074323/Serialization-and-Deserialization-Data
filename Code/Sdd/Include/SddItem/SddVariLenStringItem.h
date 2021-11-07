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
时间:2021/1/26
描述:序列化和反序列化变长字符串项
**************************************************************************/
#include <string>
#include <vector>
#include <memory>
#include "SddItemBase.h"
#include "SddException.h"

// 创建变长字符串序列化反序列化数据项
#define SDD_VARI_LEN_STRING(rVariate) jaf::CSddVariLenStringItem::Creation(rVariate)
namespace jaf
{

// 字符串的序列化和反序列化的数据项
	class CSddVariLenStringItem :public CSddItemBase
	{
	public:
		CSddVariLenStringItem(std::string& str) :m_str(str)
		{
		}
		~CSddVariLenStringItem(){}

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddInterface> Creation(std::string& value)
		{
			std::shared_ptr<CSddInterface> pItem = std::make_shared<CSddVariLenStringItem>(value);
			if (pItem == nullptr)
			{
				throw CSddException("创建字符串数据项失败", __FILE__, __LINE__);
			}
			return pItem;
		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			// 查找字符串长度
			size_t nPos = 0;
			if (!rBuffReader.SeekAtOffset("\0", 1, nPos))
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

		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			std::vector<char> vector;
			size_t nLen = m_str.size() + 1;
			vector.resize(nLen);
			vector[nLen - 1] = 0;

			memcpy_s(vector.data(), nLen, m_str.data(), nLen);
			rBuffer.Write(vector.data(), nLen);
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return m_str.size() + 1;
		}

	protected:
		std::string& m_str; // 字符串内容
	};

} // namespace jaf
