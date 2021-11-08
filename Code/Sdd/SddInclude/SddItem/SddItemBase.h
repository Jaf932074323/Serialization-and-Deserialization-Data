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
时间:2020/10/24
描述:序列化和反序列化一项
**************************************************************************/
#include "SddInclude/TypeDefine.h"
#include "SddInclude/SddObject/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"
#include "SddInclude/SddEndian/SddEndianManage.h"

namespace jaf
{
	class SDD_EXPORT CSddItemBase :public CSddInterface
	{
	public:
		CSddItemBase() : m_rEndian(CSddEndianManage::GetDefaultEndian())
		{};
		CSddItemBase(E_ENDIAN eEndian) :m_rEndian(CSddEndianManage::GetEndian(eEndian))
		{};

		virtual ~CSddItemBase(void) {};

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader) = 0;
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer) = 0;

		// 获取序列化或反序列化使用的字节长度
		virtual size_t GetBufferLength() = 0;

	protected:
		CSddEndianBase& m_rEndian; // 端序
	};

} // namespace jaf

