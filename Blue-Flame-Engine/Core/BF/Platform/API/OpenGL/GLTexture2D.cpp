#include "GLTexture2D.h"
#include "BF/Graphics/API/Texture2D.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace OpenGL
			{
				using namespace std;
				using namespace BF::Graphics::API;

				GLTexture2D::GLTexture2D(const GLShader& glshader) :
					glshader(glshader), textureID(0)
				{
				}

				GLTexture2D::~GLTexture2D()
				{
				}

				void GLTexture2D::Create(unsigned int width, unsigned int height, Texture::Format format, const uint8_t* data, Texture::TextureWrap textureWrap, Texture::TextureFilter textureFilter)
				{
					glGenTextures(1, &textureID);

					glBindTexture(GL_TEXTURE_2D, textureID);

					if (format == Texture::Format::R8)
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

					glTexImage2D(GL_TEXTURE_2D, 0, GetGLTextureFormat(format), width, height, 0, GetGLTextureFormat(format), GL_UNSIGNED_BYTE, data);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLTextureWrap(textureWrap));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLTextureWrap(textureWrap));

					//TODO: Control both min and mag filter like d3d11
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLTextureFilter(textureFilter));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLTextureFilter(textureFilter));

					//TODO: Add mip maps.
					//TODO: Add a way to disable and enable mip maps

					glBindTexture(GL_TEXTURE_2D, 0);
				}

				void GLTexture2D::Bind() const
				{
					glBindTexture(GL_TEXTURE_2D, textureID);
				}

				void GLTexture2D::Bind(const string& samplerName, unsigned int index) const
				{
					glActiveTexture(GL_TEXTURE0 + index);
					glBindTexture(GL_TEXTURE_2D, textureID);
					glUniform1i(glGetUniformLocation(glshader.GetProgramID(), samplerName.c_str()), index);
				}

				void GLTexture2D::Unbind() const
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}

				void GLTexture2D::Unbind(const string& samplerName, unsigned int index) const
				{
					glActiveTexture(GL_TEXTURE0 + index);
					glBindTexture(GL_TEXTURE_2D, 0);
				}

				int GLTexture2D::GetGLTextureFormat(Texture::Format format) const
				{
					switch (format)
					{
						case Texture2D::Format::R8: return GL_RED;
						case Texture2D::Format::R8G8: return GL_RG;
						case Texture2D::Format::R8G8B8: return GL_RGB;
						case Texture2D::Format::R8G8B8A8: return GL_RGBA;
						default: return GL_RGBA;
					}
				}

				int GLTexture2D::GetGLTextureWrap(Texture::TextureWrap textureWrap) const
				{
					switch (textureWrap)
					{
						case Texture2D::TextureWrap::Repeat: return GL_REPEAT;
						case Texture2D::TextureWrap::MirroredReapeat: return GL_MIRRORED_REPEAT;
						case Texture2D::TextureWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
						case Texture2D::TextureWrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
						default: return GL_REPEAT;
					}
				}

				int GLTexture2D::GetGLTextureFilter(Texture::TextureFilter textureFilter) const
				{
					switch (textureFilter)
					{
						case Texture2D::TextureFilter::Neatest: return GL_NEAREST;
						case Texture2D::TextureFilter::Linear: return GL_LINEAR;
						default: return GL_NEAREST;
					}
				}
			}
		}
	}
}