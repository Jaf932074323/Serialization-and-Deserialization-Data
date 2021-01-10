//MIT License
//
//Copyright(c) 2021 Jaf932074323 ½ª°²¸»
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
#include "SddEndian/SddEndianNo.h"
#include <vector>
#include <assert.h>

namespace jaf
{
	void CSddEndianNo::DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);
		rBuffer.Write(pData, nNeedLen);
	}

	bool CSddEndianNo::BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);
		if (!rBuffReader.Read(pData, nNeedLen))
		{
			return false;
		}

		return true;
	}

	E_ENDIAN CSddEndianNo::GetEndian()
	{
		return E_ENDIAN::E_ENDIAN_NULL;
	}

} // namespace jaf
