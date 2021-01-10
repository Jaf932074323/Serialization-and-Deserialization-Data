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
#include "SddEndian/SddEndianLittle.h"
#include <vector>
#include <assert.h>

namespace jaf
{
	void CSddEndianLittle::DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);

		if (m_hostEndian == E_ENDIAN::E_ENDIAN_LITTLE)
		{
			rBuffer.Write(pData, nNeedLen);
		}
		else
		{
			std::vector<char> vector(nDataLen);
			memcpy_s(vector.data(), nDataLen, pData, nDataLen);
			EndianChange(vector.data(), nDataLen); // 转换端序
			rBuffer.Write(vector.data() + (nDataLen - nNeedLen), nNeedLen);
		}
	}

	bool CSddEndianLittle::BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);

		if (m_hostEndian == E_ENDIAN::E_ENDIAN_LITTLE)
		{
			return rBuffReader.Read(pData, nNeedLen);
		}
		else
		{
			std::vector<char> vector(nDataLen);
			// 读取到vector中
			if (!rBuffReader.Read(vector.data() + (nDataLen - nNeedLen), nNeedLen))
			{
				return false;
			}

			EndianChange(vector.data(), nDataLen);
			memcpy_s(pData, nDataLen, vector.data(), nDataLen);
			return true;
		}
	}

	E_ENDIAN CSddEndianLittle::GetEndian()
	{
		return E_ENDIAN::E_ENDIAN_LITTLE;
	}

} // namespace jaf
