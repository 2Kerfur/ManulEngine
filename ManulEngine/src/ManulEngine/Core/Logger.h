class Logger
{
public:
	//static auto st<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	//static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	//static Ref<spdlog::logger> s_CoreLogger;
	//static Ref<spdlog::logger> s_ClientLogger;
};

#define M_CORE_ERROR(...) 
#define M_CORE_INFO(...)
#define M_CORE_WARNING(...)
#define M_CORE_CRITICAL(...)

#define M_ERROR(...) 
#define M_INFO(...)
#define M_WARNING(...)
#define M_CRITICAL(...)