@rem Update these variables to reflect the location of your tools and libraries.

@SET VSINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 8
@SET VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 8\VC
@SET PLATFORMSDK=C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2
@SET DXSDK=C:\Program Files (x86)\Microsoft DirectX SDK (February 2007)
@SET CYGWINDIR=C:\Cygwin
@SET FrameworkDir=C:\WINDOWS\Microsoft.NET\Framework
@SET FrameworkVersion=v2.0.50727
@SET FrameworkSDKDir=C:\Program Files (x86)\Microsoft Visual Studio 8\SDK\v2.0

@if "%VSINSTALLDIR%"=="" goto error_no_VSINSTALLDIR
@if "%VCINSTALLDIR%"=="" goto error_no_VCINSTALLDIR


@echo Setting environment for using Microsoft Visual Studio 2005 x86 tools.

@rem
@rem Root of Visual Studio IDE installed files.
@rem
@set DevEnvDir=%VSINSTALLDIR%\Common7\IDE

@set PATH=%VSINSTALLDIR%\Common7\IDE;%VCINSTALLDIR%\BIN;%VSINSTALLDIR%\Common7\Tools;%FrameworkSDKDir%\bin;%FrameworkDir%\%FrameworkVersion%;%VCINSTALLDIR%\VCPackages;%CYGWINDIR%\bin;%PATH%
@set INCLUDE=%PLATFORMSDK%\Include;%DXSDK%\Include;%VCINSTALLDIR%\INCLUDE;%INCLUDE%
@set LIB=%DXSDK%\Lib\x86;%PLATFORMSDK%\Lib;%VCINSTALLDIR%\LIB;%FrameworkSDKDir%\lib;%LIB%
@set LIBPATH=%FrameworkDir%\%FrameworkVersion%

@goto end

:error_no_VSINSTALLDIR
@echo ERROR: VSINSTALLDIR variable is not set. 
@goto end

:error_no_VCINSTALLDIR
@echo ERROR: VCINSTALLDIR variable is not set. 
@goto end

:end
