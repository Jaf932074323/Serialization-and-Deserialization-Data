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
����:��ʹ�ö���
**************************************************************************/
#include "SddEndianBase.h"
#include <vector>
#include <assert.h>

namespace jaf
{
	class CSddEndianNo : public CSddEndianBase
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
			rBuffer.Write(pData, nNeedLen);
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
			if (!rBuffReader.Read(pData, nNeedLen))
			{
				return false;
			}

			return true;
		}

		// ��ȡ����ö��ֵ
		virtual E_ENDIAN GetEndian()
		{
			return E_ENDIAN::E_ENDIAN_NULL;
		}
	};

} // namespace jaf
