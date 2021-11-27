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
#include "SddInclude/Sdd/SddObject/SddDouble.h"
#include "SddInclude/SddException.h"

namespace jaf
{
	CSddDouble::CSddDouble(double& rVariate) :m_f(rVariate)
	{
	}

	CSddDouble::~CSddDouble()
	{
	}

	std::shared_ptr<CSddDouble> CSddDouble::Creation(double& rVariate)
	{
		std::shared_ptr<CSddDouble> pItem = std::make_shared<CSddDouble>(rVariate);
		if (pItem == nullptr)
		{
			throw CSddException("创建double数据项失败", __FILE__, __LINE__);
		}
		return pItem;
	}

	bool CSddDouble::BufferToData(CBuffReaderBase& rBuffReader)
	{
		return rBuffReader.Read((char*)&m_f, sizeof(double));
	}

	void CSddDouble::DataToBuffer(CBufferBase& rBuffer)
	{
		rBuffer.Write((char*)&m_f, sizeof(double));
	}

	size_t CSddDouble::GetBufferLength()
	{
		return sizeof(double);
	}

} // namespace jaf
