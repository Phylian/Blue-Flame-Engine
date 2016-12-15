#include "GLVertexBuffer.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace OpenGL
			{
				using namespace BF::Graphics::API;

				GLVertexBuffer::GLVertexBuffer() :
					buffer(0), VAO(0)
				{
				}

				GLVertexBuffer::~GLVertexBuffer()
				{
					glDeleteBuffers(1, &buffer);
					glDeleteVertexArrays(1, &VAO);
				}

				void GLVertexBuffer::Create(const void* data, unsigned int size)
				{
					glGenVertexArrays(1, &VAO);
					glBindVertexArray(0);

					glGenBuffers(1, &buffer);
					glBindBuffer(GL_ARRAY_BUFFER, buffer);
					glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				void* GLVertexBuffer::Map() const
				{
					glBindBuffer(GL_ARRAY_BUFFER, buffer);
					return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
				}

				void GLVertexBuffer::Unmap() const
				{
					glUnmapBuffer(GL_ARRAY_BUFFER);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				void GLVertexBuffer::Bind() const
				{
					glBindVertexArray(VAO);
				}

				void GLVertexBuffer::Unbind() const
				{
					glBindVertexArray(0);
				}

				void GLVertexBuffer::SetLayout(const VertexBufferLayout& vertexBufferLayout)
				{
					glBindVertexArray(VAO);
					glBindBuffer(GL_ARRAY_BUFFER, buffer);

					for (size_t i = 0; i < vertexBufferLayout.GetBufferElement().size(); i++)
					{
						glEnableVertexAttribArray(vertexBufferLayout.GetBufferElement()[i].index);
						glVertexAttribPointer(vertexBufferLayout.GetBufferElement()[i].index, GetComponentCount(vertexBufferLayout.GetBufferElement()[i].dataType),
							GetGLDataType(vertexBufferLayout.GetBufferElement()[i].dataType), GL_FALSE, vertexBufferLayout.GetBufferElement()[i].stride, (GLvoid*)vertexBufferLayout.GetBufferElement()[i].offset);
					}

					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
				}

				GLenum GLVertexBuffer::GetGLDataType(VertexBufferLayout::DataType dataType)
				{
					switch (dataType)
					{
						case VertexBufferLayout::DataType::Float:
						{
							return GL_FLOAT;
							break;
						}
						case VertexBufferLayout::DataType::Float2:
						{
							return GL_FLOAT;
							break;
						}
						case VertexBufferLayout::DataType::Float3:
						{
							return GL_FLOAT;
							break;
						}
						case VertexBufferLayout::DataType::Float4:
						{
							return GL_FLOAT;
							break;
						}
						default:
							return -1;
							break;
					}
				}

				unsigned int GLVertexBuffer::GetComponentCount(VertexBufferLayout::DataType dataType)
				{
					switch (dataType)
					{
						case VertexBufferLayout::DataType::Float:
						{
							return 1;
							break;
						}
						case VertexBufferLayout::DataType::Float2:
						{
							return 2;
							break;
						}
						case VertexBufferLayout::DataType::Float3:
						{
							return 3;
							break;
						}
						case VertexBufferLayout::DataType::Float4:
						{
							return 4;
							break;
						}
						default:
							return -1;
							break;
					}
				}
			}
		}
	}
}