#pragma once

#include "bobopch.h"
#include "Shader.h"

/** Loads Shaders */

namespace Bobo
{
	class BOBO_API ShaderLoader
	{
	public:
		static ShaderLoader& GetInstance()
		{
			static ShaderLoader* instance = new ShaderLoader();
			return *instance;
		}
		ShaderLoader();
		virtual ~ShaderLoader() {
			delete m_LoadedShaders;
		};
		void ParseShader(std::string filelocation);
	private:
		ShaderLoader();
		std::string LoadShader(std::string filelocation);
		std::unordered_map<std::string, Shader*> m_LoadedShaders;
	};
}