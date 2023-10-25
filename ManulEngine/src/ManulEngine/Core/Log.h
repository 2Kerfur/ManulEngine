#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace ManulEngine
{
	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define M_CORE_ERROR(...)		::ManulEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define M_CORE_INFO(...)		::ManulEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define M_CORE_WARNING(...)		::ManulEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define M_CORE_CRITICAL(...)	::ManulEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define M_ERROR(...)			::ManulEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define M_INFO(...)				::ManulEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define M_WARNING(...)			::ManulEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define M_CRITICAL(...)			::ManulEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)