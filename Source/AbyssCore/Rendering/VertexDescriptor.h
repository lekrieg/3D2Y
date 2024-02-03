#ifndef VERTEX_DESCRIPTOR_H
#define VERTEX_DESCRIPTOR_H

#include "../Utils/Enums.h"

#include <vector>

namespace abyss
{
	namespace render
	{
		class VertexElement
		{
		public:
			ABYSS_ELEMENT_TYPE elementType;
			int bytes;
			int offset;

			VertexElement() : elementType(ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_NULL), bytes(0), offset(0) {}

			bool operator==(VertexElement& e)
			{
				return (elementType == e.elementType && bytes == e.bytes && offset == e.offset);
			}
		};

		class VertexDescriptor
		{
			std::vector<VertexElement> m_elements;
			int m_currentStride;

		public:
			VertexDescriptor()
			{
				m_currentStride = 0;
			}

			void Clear()
			{
				m_elements.clear();
				m_currentStride = 0;
			}

			ABYSS_RESULT AddElement(ABYSS_ELEMENT_TYPE t)
			{
				VertexElement element;
				element.elementType = t;

				switch (t)
				{
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_IGNORE_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_VERTEX_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_NORMAL_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_COLOR_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX1_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX2_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX3_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX4_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX5_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX6_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX7_3F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX8_3F:
					element.bytes = sizeof(float) * 3;
					break;

				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_IGNORE_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX1_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX2_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX3_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX4_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX5_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX6_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX7_2F:
				case ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_TEX8_2F:
					element.bytes = sizeof(float) * 2;
					break;

				default:
					break;
				};

				if (t == ABYSS_ELEMENT_TYPE::ABYSS_ELEMENT_TYPE_NULL || element.bytes <= 0)
				{
					return ABYSS_RESULT::ABYSS_FAIL;
				}

				element.offset = m_currentStride;
				m_currentStride += element.bytes;

				m_elements.push_back(element);

				return ABYSS_RESULT::ABYSS_SUCCESS;
			}

			VertexElement GetElement(int index)
			{
				VertexElement element;

				if (index >= 0 && index < (int)m_elements.size())
				{
					return m_elements[index];
				}

				return element;
			}

			int GetTotalElements()
			{
				return static_cast<int>(m_elements.size());
			}

			int GetStride()
			{
				return m_currentStride;
			}
		};
	}
}

#endif