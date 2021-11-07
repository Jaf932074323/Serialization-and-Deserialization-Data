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
描述:序列化和反序列化float浮点数项
**************************************************************************/
#include <memory>
#include "SddItemBase.h"

// 创建float数据项序列化反序列化数据项
#define SDD_FLOAT(rVariate) jaf::CSddFloatItem::Creation(rVariate)

namespace jaf
{

	// 字符串的序列化和反序列化的数据项
	class SDD_EXPORT CSddFloatItem :public CSddItemBase
	{
	public:
		CSddFloatItem(float& rVariate);
		~CSddFloatItem();
		// 创建double浮点数的序列化和反序列化的数据项
		static std::shared_ptr<CSddInterface> Creation(float& rVariate);

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
		float& m_f;
	};

} // namespace jaf


