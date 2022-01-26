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
时间:2020/11/5
描述:字符串的序列化和反序列化对象
**************************************************************************/
#include <string>
#include <vector>
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

// 创建字符串的序列化和反序列化对象
#define SDD_STRING(rVariate, nLength) jaf::CSddString::Creation(rVariate, nLength)
namespace jaf
{

	// 字符串的序列化和反序列化对象
	class CSddString :public CSddInterface
	{
	public:
		CSddString(std::string& str, size_t nLength) :m_str(str), m_nLength(nLength)
		{
		}

		~CSddString()
		{
		}

		// 创建字符串的序列化和反序列化对象
		static std::shared_ptr<CSddString> Creation(std::string& value, size_t nLength)
		{
			std::shared_ptr<CSddString> pItem = std::make_shared<CSddString>(value, nLength);
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
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			std::vector<char> vector;
			vector.resize(m_nLength + 1);
			vector[m_nLength] = 0;

			size_t nLength = m_nLength < m_str.size() ? m_nLength : m_str.size();
			memcpy_s(vector.data(), m_nLength, m_str.data(), nLength);
			rBuffer.Write(vector.data(), m_nLength);
		}

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}

	protected:
		size_t m_nLength; // 字符串长度
		std::string& m_str; // 字符串内容
	};

} // namespace jaf
