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
时间:2020-11-1
描述:端序基类 头文件
**************************************************************************/
#include "Buffer/BufferBase.h"
#include "Buffer/BuffReaderBase.h"
#include "ExportDefine.h"

namespace jaf
{
	// 字节序
	enum class E_ENDIAN
	{
		E_ENDIAN_NULL = 0, // 不区分大小端 
		E_ENDIAN_BIG = 1, // 大端 Big-Endian
		E_ENDIAN_LITTLE = 2, // 小端 Little-Endian
	};

	class SDD_EXPORT CSddEndianBase
	{
	public:
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// pData 数据地址
		// nDataLeng 数据长度
		// nNeedLeng 需要的长度
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen) = 0;
		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// pData 数据地址
		// nDataLeng 数据长度
		// nNeedLeng 需要的长度
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen) = 0;

		// 获取端序枚举值
		virtual E_ENDIAN GetEndian() = 0;

		// 获取主机字节序
		// 大端：低位放在高地址，高位放在低地址
		// 小端：低位放在低地址，高位放在高地址
		static E_ENDIAN GetHostEndian();

		// 字节序转换 返回t的反字节序(大端返回小端、小端返回大端)
		// pData 要转换数据地址
		// nLeng 要转换数据长度
		static void EndianChange(char* pData, size_t nLeng);

	protected:
		static E_ENDIAN m_hostEndian; // 主机端序
	};

} // namespace jaf

