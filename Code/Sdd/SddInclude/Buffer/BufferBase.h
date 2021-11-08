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
时间:2018-10-31 16:57
描述:缓冲区基类
**************************************************************************/
#include "SddInclude/ExportDefine.h"

namespace jaf
{
	class SDD_EXPORT CBufferBase
	{
	public:
		CBufferBase(void) {};
		~CBufferBase(void) {};

		// 清空 释放内存、清空已读字节等
		virtual void Clear() = 0;

		// 预约nSize空间,用于写入字节 让缓存区能够再写入nSize个字节
		// 在总容量不够时，重新分配更大的内存空间，以能够存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nSize 要预约空间的大小
		virtual void Reserve(size_t nSize) = 0;

		// 扩展缓冲区空间
		// 扩展容量到总容量至少有nCapacity个字节大小，在总容量不够时，重新分配更大的内存空间，以能够再存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nCapacity 要扩展的目标大小大小
		virtual void ExtendCapacity(size_t nCapacity) = 0;

		// 获取已写入字节数量
		virtual size_t GetWriteLength() const = 0;

		// 获取缓冲区地址
		virtual const char* GetBuffer() const = 0;

	public:
		// 写入数据到缓冲区中
		// pData 要写入对象的地址 不能为空
		// nLength 要写入的长度
		virtual void Write(const char* pData, size_t nLength) = 0;

		// 重复写入同一个字符到缓冲区中
		// c 要写入的字符
		// nLength 要写入字符的个数
		// return 成功返回true，失败返回false
		virtual void WriteChar(char c, size_t nLength) = 0;

	public:
		// 删除前指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopFront(size_t nLength) = 0;
		// 删除后指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopBack(size_t nLength) = 0;

		// 搜索子内存
		// pSeekContent 被搜索内容的首地址
		// nSeekcontentLength 被搜索内容的长度
		// rIndex 返回被搜索到内容的索引
		// 返回是否搜索到
		virtual bool SeekFront(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex) = 0;
	};

} // namespace jaf

