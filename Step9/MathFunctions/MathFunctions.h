#if defined(_WIN32)
#   if defined(EXPLORTING_MYMATH)
#	define DECLSPEC __declspec(dllexport)
#   else
#       define DECLSPEC __declspec(dllimport)
#   endif 
#else
#   define DECLSPEC
#endif
namespace mathfunctions {
double DECLSPEC sqrt(double x);
}
