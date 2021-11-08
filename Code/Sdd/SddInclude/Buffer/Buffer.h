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
描述:缓冲区，存储字节
提供了一个默认栈，字节优先存储在默认栈中。
在使用者不指定存储方式时，当要存储的字节串长度小于默认栈长度，默认存储在这个栈中。
当超过默认栈长度时，存储在动态分配内存中。
**************************************************************************/
#include <memory.h>
#include "SddInclude/Buffer/BufferBase.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	const size_t g_nAllotMemoryUnit = 32; // 分配空间时，以这个值的倍数分配
	const size_t g_nDefaultStackLen = 32; // 默认栈长度

	// 缓冲区
	class SDD_EXPORT CBuffer :public CBufferBase
	{
	protected:
		// 字节存储位置
		enum class E_STORE_SITE
		{
			E_STORE_SITE_STACK = 0, // 存储在默认栈中
			E_STORE_SITE_DYNAMIC = 1 // 存储在动态内存中
		};
	public:
		CBuffer(void);
		~CBuffer(void);

		// 清空 释放内存、清空已读已写字节等
		void Clear();

		// 预约nSize空间,用于写入字节 让缓存区能够再写入nSize个字节
		// 在总容量不够时，重新分配更大的内存空间，以能够存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nSize 要预约空间的大小
		void Reserve(size_t nSize);

		// 扩展缓冲区空间
		// 扩展容量到总容量至少有nCapacity个字节大小，在总容量不够时，重新分配更大的内存空间，以能够再存取nSize个字节
		// 当使用存储在用户提供的内存时，若总容量不够，返回false
		// nCapacity 要扩展的目标大小大小
		void ExtendCapacity(size_t nCapacity);

		// 获取已写入字节数量
		size_t GetWriteLength() const;

		// 获取缓冲区地址
		const char* GetBuffer() const;

	public:
		// 写入数据到缓冲区中
		// pData 要写入对象的地址 不能为空
		// nLength 要写入的长度
		void Write(const char* pData, size_t nLength);

		// 重复写入同一个字符到缓冲区中
		// c 要写入的字符
		// nLength 要写入字符的个数
		// return 成功返回true，失败返回false
		void WriteChar(char c, size_t nLength);

	public:
		// 删除前指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopFront(size_t nLength);
		// 删除后指定长度
		// nLength 要删除的长度,如果长度不够则全部删除
		virtual void PopBack(size_t nLength);

		// 搜索子内存
		// pSeekContent 被搜索内容的首地址
		// nSeekcontentLength 被搜索内容的长度
		// rIndex 返回被搜索到内容的索引
		// 返回是否搜索到
		virtual bool SeekFront(const char* pSeekContent, size_t nSeekContentLength, size_t& rIndex);

	private:
		// 释放动态分配的内存空间 这个函数仅仅释放了内存，其它相关值如容量、已写字节等等都没处理，调用需谨慎，否则有隐患
		void ReleaseAllotMemory();

	protected:
		// 缓冲区指针,指向存储字节的首地址
		// 当使用默认栈时，它指向默认栈首地址
		// 当使用动态内存空间时，指向动态内存首地址
		char* m_pBuffer = nullptr;
		char m_arrBufferStack[g_nDefaultStackLen]; // 默认栈
		E_STORE_SITE m_eStoreSite = E_STORE_SITE::E_STORE_SITE_STACK; // 字节存储位置

		size_t m_nCapacity = g_nDefaultStackLen; // 总容量
		size_t m_nWriteByteLen = 0; // 已经写入字节的长度
	};

} // namespace jaf
