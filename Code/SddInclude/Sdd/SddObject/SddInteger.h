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
ʱ��:2018/11/13 16:21
����:���л��ͷ����л�������
**************************************************************************/
#include <assert.h>
#include "SddInclude/SddException.h"
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddEndian/SddEndianBase.h"

// �������������л������л���������
#define SDD_INTERGER(T,rEndian,rT, ...) jaf::CSddInteger<T>::Creation(rEndian, rT, ## __VA_ARGS__)

namespace jaf
{

	template<typename T>
	// ���������л������л�ͨ�ö���
	// T �������ͣ�������int/size_t/short int/unsigned short int/long/unsigned long�ȵ�
	class CSddInteger :public CSddInterface
	{
	public:
		// ���������л��ͷ����л���ͨ�ö���
		// m_rEndian ����
		// pTҪ���л��������л����ݵĵ�ַ
		// nBitLength Ҫ���л��ĳ��� ���Ϊ0����ȫ�����л�
		CSddInteger(CSddEndianBase& rEndian, T& rT, size_t nLength = 0) :m_rEndian(rEndian), m_rT(rT), m_nLength(nLength)
		{
			if ((0 != m_nLength) && (m_nLength > sizeof(T)))
			{
				throw CSddException("���л�����̫��", __FILE__, __LINE__);
			}
			if (m_nLength < 0)
			{
				throw CSddException("���л����ȴ���ֵΪ��", __FILE__, __LINE__);
			}

			if (m_nLength == 0)
			{
				m_nLength = sizeof(T);
			}
		}

		~CSddInteger(void)
		{
		}

		// �������������л��ͷ����л�����
		static std::shared_ptr<CSddInteger<T>> Creation(CSddEndianBase& m_rEndian, T& rT, size_t nLength = 0)
		{
			std::shared_ptr<CSddInteger<T>> pItem = std::make_shared<CSddInteger>(m_rEndian, rT, nLength);
			if (pItem == nullptr)
			{
				throw CSddException("����double������ʧ��", __FILE__, __LINE__);
			}
			return pItem;

		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			return m_rEndian.BufferToData(rBuffReader, (char*)&m_rT, sizeof(T), m_nLength);
		}
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			m_rEndian.DataToBuffer(rBuffer, (const char*)&m_rT, sizeof(T), m_nLength);
		}


		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			if (m_nLength == 0)
			{
				return sizeof(T);
			}
			else
			{
				return m_nLength;
			}
		}

	protected:
		size_t m_nLength; // ���л��������л����� ���Ϊ0����ȫ�����л�
		T& m_rT; // ͨ����������
		CSddEndianBase& m_rEndian; // ����
	};

} // namespace jaf
