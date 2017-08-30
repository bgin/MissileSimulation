
#ifndef __VERSION_H__
#define __VERSION_H__

// Tab: 4
        
/*
	Mathlib version aggregated data.
*/

#include <string>
#include <tuple>
#include <memory>

namespace mathlib{
	namespace version_info {


	struct SMathlib_Version_Info {

		static constexpr int Mathlib_Version_Major{ 1};

		static constexpr int Mathlib_Version_Minor{ 0};

		static constexpr int Mathlib_Version_Patch{ 0};

		static constexpr int Mathlib_Version{1000 * Mathlib_Version_Major + 100 * Mathlib_Version_Minor + 1 * Mathlib_Version_Patch};

		const char* Project_Name = "MissileSimulation";

		const char* Library_Name = "Mathlib";

		const char* Library_Purpose = "Project's mathematical backbone";

		const char* Library_Type = "static";

		const char* Library_Arch = "x64";

		const char* Library_OS   = "Win";

		const char* Library_Machine_CPU = "Intel Core i7-4700 HQ";

		const char* Library_Create_Date = "Date: 2015-07-14";

		const char* Library_Last_Build = "Date: 2016-04-09 Time: 20:14 PM";

		const char* Library_Compiler_Version = "1500";

		};


	class CMathlib_Version_Info{
	         

			 public:


				 ~CMathlib_Version_Info() = default;
				
				 CMathlib_Version_Info(_In_ const CMathlib_Version_Info &) = delete;

				 CMathlib_Version_Info & operator=(_In_ const CMathlib_Version_Info &) = delete;

				 static std::shared_ptr<CMathlib_Version_Info> getCMathlib_Version_Info();

				 inline  int    getVersion_Major()const;

				 inline  int    getVersion_Minor()const;

				 inline  int    getPatch_Version()const;

				 inline  int    getLib_Version()const;

				 const std::string    getProject_Name()const;

				 const std::string    getLib_Name()const;

				 const std::string    getLib_Purpose()const;

				 const std::string    getLib_Type()const;

				 const std::string    getLib_Arch()const;

				 const std::string    getLib_OS()const;

				 const std::string    getLib_CPU()const;

				 const std::string    getLib_Create_Date()const;

				 const std::string    getLib_Last_Build()const;

				 const std::string    getLib_Compiler_Ver()const;

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
							std::string>  getLib_Description()const;

			 private:

				 CMathlib_Version_Info();

				 CMathlib_Version_Info(_In_ const int,
				                       _In_ const int,
									   _In_ const int,
									   _In_ const int,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *,
									   _In_ const char *);

			 int m_VersionMajor;

			 int m_VersionMinor;

			 int m_PatchVersion;

			 int m_LibVersion;

			 std::string m_ProjectName;

			 std::string m_LibName;

			 std::string m_LibPurpose;

			 std::string m_LibType;

			 std::string m_LibArch;

			 std::string m_LibOS;

			 std::string m_LibCPU;

			 std::string m_LibCreateDate;

			 std::string m_LibLastBuild;

			 std::string m_LibCompilerVer;

	};


#include "Version.inl"
	}
 }

#endif /*__VERSION_H__*/