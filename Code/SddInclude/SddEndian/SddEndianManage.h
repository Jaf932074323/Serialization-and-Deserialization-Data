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
ʱ��:2020-11-8
����:�������
**************************************************************************/
#include "SddInclude/SddEndian/SddEndianNo.h"
#include "SddInclude/SddEndian/SddEndianBig.h"
#include "SddInclude/SddEndian/SddEndianLittle.h"

namespace jaf
{
	class CSddEndianManage
	{
	private:
		CSddEndianManage()
		{}
	public:
		// ����Ĭ�϶���
		static void SetDefaultEndian(E_ENDIAN eDefaultEndian)
		{
			Intance().m_pDefaultEdndian = &GetEndian(eDefaultEndian);
		}
		// ��ȡĬ�϶���
		static CSddEndianBase& GetDefaultEndian()
		{
			assert(Intance().m_pDefaultEdndian != nullptr);
			return *Intance().m_pDefaultEdndian;
		}

		// ��ȡ�������ʵ��
		static CSddEndianBase& GetEndian(E_ENDIAN eEndian)
		{
			switch (eEndian)
			{
			case E_ENDIAN::E_ENDIAN_BIG:
				return Intance().m_endianBig;
			case E_ENDIAN::E_ENDIAN_LITTLE:
				return Intance().m_endianLittle;
			default:
				return Intance().m_endianNo;
			}
		}

	private:
		// ��̬����ʵ��
		static CSddEndianManage& Intance()
		{
			static CSddEndianManage endianManage;
			return endianManage;
		}
	private:
		// ����
		CSddEndianNo m_endianNo;
		CSddEndianBig m_endianBig;
		CSddEndianLittle m_endianLittle;
		CSddEndianBase* m_pDefaultEdndian = &m_endianBig; // Ĭ�϶���
	};

} // namespace jaf

