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
#include "SddInclude/SddEndian/SddEndianManage.h"
#include <assert.h>

namespace jaf
{
	CSddEndianNo CSddEndianManage::m_endianNo;
	CSddEndianBig CSddEndianManage::m_endianBig;
	CSddEndianLittle CSddEndianManage::m_endianLittle;
	CSddEndianBase* CSddEndianManage::m_pDefaultEdndian = &CSddEndianManage::m_endianBig; // 默认端序为大端

	void CSddEndianManage::SetDefaultEndian(E_ENDIAN eDefaultEndian)
	{
		m_pDefaultEdndian = &GetEndian(eDefaultEndian);
	}

	CSddEndianBase& CSddEndianManage::GetDefaultEndian()
	{
		assert(m_pDefaultEdndian != nullptr);
		return *m_pDefaultEdndian;
	}

	CSddEndianBase& CSddEndianManage::GetEndian(E_ENDIAN eEndian)
	{
		switch (eEndian)
		{
		case E_ENDIAN::E_ENDIAN_BIG:
			return m_endianBig;
		case E_ENDIAN::E_ENDIAN_LITTLE:
			return m_endianLittle;
		default:
			return m_endianNo;
		}
	}

} // namespace jaf
