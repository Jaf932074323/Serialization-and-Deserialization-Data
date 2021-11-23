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
描述:序列化和反序列化一块数据
**************************************************************************/
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"

// 创建一块数据的序列化反序列化对象
#define SDD_CHUNK(pVariate, nLength) jaf::CSddChunk::Creation(pVariate, nLength)

namespace jaf
{

	// 块的序列化和反序列化对象
	// 某个或多个数据集合到一起形成一块数据，对它序列化和反序列化
	class SDD_EXPORT CSddChunk :public CSddInterface
	{
	public:
		// 块的序列化和反序列化对象
		// 某个或多个数据集合到一起形成一块数据，对它序列化和反序列化
		// pVariate 块地址
		// nLength 块大小
		CSddChunk(void* pVariate, size_t nLength);
		~CSddChunk();
		// 创建字符串的序列化和反序列化的数据项
		static std::shared_ptr<CSddInterface> Creation(void* pVariate, size_t nLength);

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
		size_t m_nLength; // 长度
		void* m_pChunk; // 块地址
	};

} // namespace jaf
