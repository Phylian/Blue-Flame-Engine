#pragma once
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX)
	#include <GL/glew.h>
#elif BF_PLATFORM_WEBGL || defined (BF_PLATFORM_ANDROID)
	#include <GLES3/gl3.h>
#endif

#include <vector>
#include "BF/IO/FileLoader.h"
#include "BF/Common.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace OpenGL
			{
				class BF_API GLShader
				{
					private:
						GLuint programID;
						GLint result;
						int errorLength;

					private:
						GLuint CompileShader(const std::string& shaderCode, GLenum shaderType);

					public:
						GLShader();
						~GLShader();

						void Load(const std::string& vertexShaderFilePath, const std::string& pixelShaderFilePath);

						void Bind() const;
						void Unbind() const;

						inline const GLuint& GetProgramID() const { return programID; }
				};
			}
		}
	}
}