#ifdef __cplusplus
extern "C" {
#endif

#ifdef _BUILD_DLL_
#define FUNCTION __declspec(dllexport)
#else
#define FUNCTION __declspec(dllimport)
#endif


FUNCTION char* convertCppToRuby(char** code_in);


#ifdef __cplusplus
}
#endif