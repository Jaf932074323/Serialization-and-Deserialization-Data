//MIT License
//
//Copyright(c) 2021 Jaf932074323 ������
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
#include "SddEndian/SddEndianBig.h"
#include <vector>
#include <assert.h>

namespace jaf
{
	void CSddEndianBig::DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);

		// �����ݿ�����vector��
		std::vector<char> vector(nDataLen);
		memcpy_s(vector.data(), nDataLen, pData, nDataLen);

		// ת������
		if (m_hostEndian == E_ENDIAN::E_ENDIAN_LITTLE)
		{
			EndianChange(vector.data(), nDataLen);
		}

		rBuffer.Write(vector.data() + nDataLen - nNeedLen, nNeedLen);
	}

	bool CSddEndianBig::BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen)
	{
		assert(nDataLen >= nNeedLen);

		std::vector<char> vector(nDataLen);
		memset(vector.data(), 0, nDataLen);

		// �ӻ������ж�ȡ���ݵ�vector��
		if (!rBuffReader.Read(vector.data() + nDataLen - nNeedLen, nNeedLen))
		{
			return false;
		}

		// ת������
		if (m_hostEndian == E_ENDIAN::E_ENDIAN_LITTLE)
		{
			EndianChange(vector.data(), nDataLen);
		}

		memcpy_s(pData, nDataLen, vector.data(), nDataLen);

		return true;
	}

	E_ENDIAN CSddEndianBig::GetEndian()
	{
		return E_ENDIAN::E_ENDIAN_BIG;
	}

} // namespace jaf
