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
描述:序列化和反序列化字符串项
**************************************************************************/
#include <string>
#include <memory>
#include "SddItemBase.h"

	// 创建字符串序列化反序列化数据项
#define SDD_STRING(rVariate, nLength) jaf::CSddStringItem::Creation(rVariate, nLength)
namespace jaf
{

// 字符串的序列化和反序列化的数据项
	class CSddStringItem :public CSddItemBase
	{
	public:
		CSddStringItem(std::string& str, size_t nLength);
		~CSddStringItem();

		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddInterface> Creation(std::string& value, size_t nLength);

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader);
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer);
		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength();

	protected:
		size_t m_nLength; // 字符串长度
		std::string& m_str; // 字符串内容
	};

} // namespace jaf
