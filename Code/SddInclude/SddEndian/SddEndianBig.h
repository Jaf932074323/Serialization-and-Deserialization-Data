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
描述:大端端序
**************************************************************************/
#include <vector>
#include <assert.h>
#include "SddEndianBase.h"

namespace jaf
{
	class CSddEndianBig : public CSddEndianBase
	{
		// 将数据写入到缓冲区
		// rBuffer 缓冲区
		// pData 数据地址
		// nDataLeng 数据长度
		// nNeedLeng 需要的长度
		// 成功返回true,失败返回false
		virtual void DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen)
		{
			assert(nDataLen >= nNeedLen);

			// 将数据拷贝到vector中
			std::vector<char> vector(nDataLen);
			memcpy_s(vector.data(), nDataLen, pData, nDataLen);

			// 转换端序
			if (GetHostEndian() == E_ENDIAN::E_ENDIAN_LITTLE)
			{
				EndianChange(vector.data(), nDataLen);
			}

			rBuffer.Write(vector.data() + nDataLen - nNeedLen, nNeedLen);
		}

		// 从缓冲区中读取数据
		// rBuffer 缓冲区
		// pData 数据地址
		// nDataLeng 数据长度
		// nNeedLeng 需要的长度
		// 成功返回true,失败返回false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen)
		{
			assert(nDataLen >= nNeedLen);

			std::vector<char> vector(nDataLen);
			memset(vector.data(), 0, nDataLen);

			// 从缓冲区中读取数据到vector中
			if (!rBuffReader.Read(vector.data() + nDataLen - nNeedLen, nNeedLen))
			{
				return false;
			}

			// 转换端序
			if (GetHostEndian() == E_ENDIAN::E_ENDIAN_LITTLE)
			{
				EndianChange(vector.data(), nDataLen);
			}

			memcpy_s(pData, nDataLen, vector.data(), nDataLen);

			return true;
		}

		// 获取端序枚举值
		virtual E_ENDIAN GetEndian()
		{
			return E_ENDIAN::E_ENDIAN_BIG;
		}
	};

} // namespace jaf

