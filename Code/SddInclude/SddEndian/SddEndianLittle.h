#pragma once
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
/**************************************************************************
����:������
ʱ��:2020-11-2
����:С�˶���
**************************************************************************/
#include "SddEndianBase.h"

namespace jaf
{
	class CSddEndianLittle : public CSddEndianBase
	{
		// ������д�뵽������
		// rBuffer ������
		// pData ���ݵ�ַ
		// nDataLeng ���ݳ���
		// nNeedLeng ��Ҫ�ĳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen)
		{
			assert(nDataLen >= nNeedLen);

			if (GetHostEndian() == E_ENDIAN::E_ENDIAN_LITTLE)
			{
				rBuffer.Write(pData, nNeedLen);
			}
			else
			{
				std::vector<char> vector(nDataLen);
				memcpy_s(vector.data(), nDataLen, pData, nDataLen);
				EndianChange(vector.data(), nDataLen); // ת������
				rBuffer.Write(vector.data() + (nDataLen - nNeedLen), nNeedLen);
			}
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// pData ���ݵ�ַ
		// nDataLeng ���ݳ���
		// nNeedLeng ��Ҫ�ĳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen)
		{
			assert(nDataLen >= nNeedLen);

			if (GetHostEndian() == E_ENDIAN::E_ENDIAN_LITTLE)
			{
				return rBuffReader.Read(pData, nNeedLen);
			}
			else
			{
				std::vector<char> vector(nDataLen);
				// ��ȡ��vector��
				if (!rBuffReader.Read(vector.data() + (nDataLen - nNeedLen), nNeedLen))
				{
					return false;
				}

				EndianChange(vector.data(), nDataLen);
				memcpy_s(pData, nDataLen, vector.data(), nDataLen);
				return true;
			}
		}

		// ��ȡ����ö��ֵ
		virtual E_ENDIAN GetEndian()
		{
			return E_ENDIAN::E_ENDIAN_LITTLE;
		}
	};

} // namespace jaf
