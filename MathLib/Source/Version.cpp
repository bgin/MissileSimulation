
#include "Version.h"

// Default value initialization.
mathlib::version_info::CMathlib_Version_Info::
                                CMathlib_Version_Info()
:

  m_VersionMajor{ -1 },
  m_VersionMinor{ -1 },
  m_PatchVersion{ -1 },
  m_LibVersion{ -1 },
  m_ProjectName{ "" },
  m_LibName{ "" },
  m_LibPurpose{ "" },
  m_LibType{ "" },
  m_LibArch{ "" },
  m_LibOS{ "" },
  m_LibCPU{ "" },
  m_LibCreateDate{ "" },
  m_LibLastBuild{ "" },
  m_LibCompilerVer{ "" } {}

mathlib::version_info::CMathlib_Version_Info::
                       CMathlib_Version_Info(_In_ int VersionMajor,
                                             _In_ int VersionMinor,
                                             _In_ int PatchVersion,
                                             _In_ int LibVersion,
                                             _In_ const char *pProjectName,
                                             _In_ const char *pLibName,
                                             _In_ const char *pLibPurpose,
                                             _In_ const char *pLibType,
                                             _In_ const char *pLibArch,
                                             _In_ const char *pLibOS,
                                             _In_ const char *pLibCPU,
                                             _In_ const char *pLibCreateDate,
                                             _In_ const char *pLibLastBuild,
                                             _In_ const char *pLibCompilerVer)
                                       :

   m_VersionMajor{ VersionMajor },
   m_VersionMinor{ VersionMinor },
   m_PatchVersion{ PatchVersion },
   m_LibVersion{ LibVersion },
   m_ProjectName{ pProjectName },
   m_LibName{ pLibName },
   m_LibPurpose{ pLibPurpose },
   m_LibType{ pLibType },
   m_LibArch{ pLibArch },
   m_LibOS{ pLibOS },
   m_LibCPU{ pLibCPU },
   m_LibCreateDate{ pLibCreateDate },
   m_LibLastBuild{ pLibLastBuild },
   m_LibCompilerVer{ pLibCompilerVer } {}

   
 const std::string mathlib::version_info::CMathlib_Version_Info::getProject_Name()const {
	return (this->m_ProjectName);
}

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Name()const {
	 return (this->m_LibName);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Purpose()const {
	 return (this->m_LibPurpose);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Type()const {
	 return (this->m_LibType);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Arch()const {
	 return (this->m_LibArch);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_OS()const {
	 return (this->m_LibOS);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_CPU()const {
	 return (this->m_LibCPU);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Create_Date()const {
	 return (this->m_LibCreateDate);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Last_Build()const {
	 return (this->m_LibLastBuild);
 }

 const std::string mathlib::version_info::CMathlib_Version_Info::getLib_Compiler_Ver()const {
	 return (this->m_LibCompilerVer);
 }

 std::tuple<int,
	 int,
	 int,
	 int,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string,
	 std::string > mathlib::version_info::CMathlib_Version_Info::getLib_Description()const {

		 return (std::make_tuple(this->m_VersionMajor,
		                         this->m_VersionMinor,
								 this->m_PatchVersion,
								 this->m_LibVersion,
								 this->m_ProjectName,
								 this->m_LibName,
								 this->m_LibPurpose,
								 this->m_LibType,
								 this->m_LibArch,
								 this->m_LibCPU,
								 this->m_LibOS,
								 this->m_LibCreateDate,
								 this->m_LibLastBuild,
								 this->m_LibCompilerVer));
	 }

 std::shared_ptr<mathlib::version_info::CMathlib_Version_Info> 
	 mathlib::version_info::CMathlib_Version_Info::getCMathlib_Version_Info() {

		 using namespace mathlib::version_info;
		 constexpr int lib_ver{1000 * 1 + 100 * 0 + 10 * 0};
		 return (std::make_shared<CMathlib_Version_Info>(new CMathlib_Version_Info(1,0,0,lib_ver,
		                                                                           "MissileSimulation",
																				   "Mathlib",
																				   "Project's mathmatical backbone",
																				   "static .lib",
																				   "x64",
																				   "Win",
																				   "Intel Core i7 4770 HQ",
																				   "Date: 2015-07-14",
																				   "Date: 2016-04-09 Time: 20:14 PM",
																				   "ICL: 15.0.2.179 Build 20150121"   )));
	 }
