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
ʱ��:2020/11/5
����:�ַ��������л��ͷ����л�����
**************************************************************************/
#include <string>
#include <vector>
#include <memory>
#include "SddInclude/Sdd/SddInterface.h"
#include "SddInclude/SddException.h"

// �����ַ��������л��ͷ����л�����
#define SDD_STRING(rVariate, nLength) jaf::CSddString::Creation(rVariate, nLength)
namespace jaf
{

	// �ַ��������л��ͷ����л�����
	class CSddString :public CSddInterface
	{
	public:
		CSddString(std::string& str, size_t nLength) :m_str(str), m_nLength(nLength)
		{
		}

		~CSddString()
		{
		}

		// �����ַ��������л��ͷ����л�����
		static std::shared_ptr<CSddString> Creation(std::string& value, size_t nLength)
		{
			std::shared_ptr<CSddString> pItem = std::make_shared<CSddString>(value, nLength);
			if (pItem == nullptr)
			{
				throw CSddException("�����ַ���������ʧ��", __FILE__, __LINE__);
			}
			return pItem;
		}

		// �ӻ������ж�ȡ����
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual bool BufferToData(CBuffReaderBase& rBuffReader)
		{
			std::vector<char> vector;
			vector.resize(m_nLength + 1);
			vector[m_nLength] = 0;
			if (!rBuffReader.Read(vector.data(), m_nLength))
			{
				return false;
			}
			m_str = vector.data();
			return true;
		}
		// ������д�뵽������
		// rBuffer ������
		// �ɹ�����true,ʧ�ܷ���false
		virtual void DataToBuffer(CBufferBase& rBuffer)
		{
			std::vector<char> vector;
			vector.resize(m_nLength + 1);
			vector[m_nLength] = 0;

			size_t nLength = m_nLength < m_str.size() ? m_nLength : m_str.size();
			memcpy_s(vector.data(), m_nLength, m_str.data(), nLength);
			rBuffer.Write(vector.data(), m_nLength);
		}

		// ��ȡ���л������л�ʹ�õ��ֽڳ���
		virtual size_t GetBufferLength()
		{
			return m_nLength;
		}

	protected:
		size_t m_nLength; // �ַ�������
		std::string& m_str; // �ַ�������
	};

} // namespace jaf
