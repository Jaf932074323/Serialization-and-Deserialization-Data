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
ʱ��:2020-11-1
����:������� ͷ�ļ�
**************************************************************************/
#include "SddInclude/Buffer/BufferBase.h"
#include "SddInclude/Buffer/BuffReaderBase.h"

namespace jaf
{
	// �ֽ���
	enum class E_ENDIAN
	{
		E_ENDIAN_NULL = 0, // �����ִ�С�� 
		E_ENDIAN_BIG = 1, // ��� Big-Endian
		E_ENDIAN_LITTLE = 2, // С�� Little-Endian
	};

	class CSddEndianBase
	{
	public:
		// ������д�뵽������
		// rBuffer ������
		// pData ���ݵ�ַ
		// nDataLeng ���ݳ���
		// nNeedLeng ��Ҫ�ĳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer, const char* pData, size_t nDataLen, size_t nNeedLen) = 0;
		// �ӻ������ж�ȡ����
		// rBuffer ������
		// pData ���ݵ�ַ
		// nDataLeng ���ݳ���
		// nNeedLeng ��Ҫ�ĳ���
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader, char* pData, size_t nDataLen, size_t nNeedLen) = 0;

		// ��ȡ����ö��ֵ
		virtual E_ENDIAN GetEndian() = 0;

		// �ֽ���ת�� ����t�ķ��ֽ���(��˷���С�ˡ�С�˷��ش��)
		// pData Ҫת�����ݵ�ַ
		// nLeng Ҫת�����ݳ���
		static void EndianChange(char* pData, size_t nLeng)
		{
			size_t nCycleTime = nLeng / 2; // ѭ������
			char cTemp;
			for (size_t i = 0; i < nCycleTime; ++i)
			{
				cTemp = pData[i];
				pData[i] = pData[nLeng - 1 - i];
				pData[nLeng - 1 - i] = cTemp;
			}
		}

		// ��ȡ�����ֽ���
		// ��ˣ���λ���ڸߵ�ַ����λ���ڵ͵�ַ
		// С�ˣ���λ���ڵ͵�ַ����λ���ڸߵ�ַ
		static E_ENDIAN GetHostEndian()
		{
			static E_ENDIAN hostEndian = InterGetHostEndian(); // ��������
			return hostEndian;
		}

	private:
		// ��ȡ�����ֽ���
		// ��ˣ���λ���ڸߵ�ַ����λ���ڵ͵�ַ
		// С�ˣ���λ���ڵ͵�ַ����λ���ڸߵ�ַ
		static E_ENDIAN InterGetHostEndian()
		{
			union
			{
				short value;
				char union_bytes[sizeof(short)];
			} test;
			test.value = 0x0102;
			if ((test.union_bytes[0] == 0x01))
			{
				return E_ENDIAN::E_ENDIAN_BIG;
			}
			else
			{
				return E_ENDIAN::E_ENDIAN_LITTLE;
			}
		}
	};

} // namespace jaf

