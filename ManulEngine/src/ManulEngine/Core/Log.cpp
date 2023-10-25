#include "mapch.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Log.h"

namespace ManulEngine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	void Log::Init()
	{
		auto core_stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto client_stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

		core_stdout_sink->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>("MANUL", core_stdout_sink);
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", client_stdout_sink);
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}
}