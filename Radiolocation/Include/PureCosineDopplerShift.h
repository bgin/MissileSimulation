#ifndef _PURE_COSINE_DOPPLER_SHIFT_H_
#define _PURE_COSINE_DOPPLER_SHIFT_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Doppler Shift class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "WaveformInterface.h"
#include "Polarization.h"
#include "../MathLib/VectorF64AVX.h"


namespace   radiolocation
{

	class PureCosDopplerShifted : public Waveform
	{
		

	public:

		/*
		brief Constructors and Destructor.
		*/

		PureCosDopplerShifted(_In_  struct PCDSParams const&);

		PureCosDopplerShifted(_In_ PureCosDopplerShifted const&);

		PureCosDopplerShifted(_In_ PureCosDopplerShifted &&);

		~PureCosDopplerShifted();

		/*
		@brief: Friend and member operators.
		*/

		PureCosDopplerShifted &      operator=(_In_ PureCosDopplerShifted const&);

		PureCosDopplerShifted &      operator=(_In_ PureCosDopplerShifted &&);

		friend  std::ostream &       operator<<(_In_ std::ostream &, _In_ PureCosDopplerShifted const&);

		std::pair<double, double>     operator[](_In_ const std::size_t);

		const std::pair<double, double>  operator[](_In_ const std::size_t) const;

		std::vector<std::pair<std::size_t, double>>  operator==(_In_ PureCosDopplerShifted const&) const;

		std::vector<std::pair<std::size_t, double>>   operator!=(_In_ PureCosDopplerShifted const&) const;

		friend   std::vector<std::pair<double, double>>  operator==(_In_ PureCosDopplerShifted const&, _In_ PureCosDopplerShifted const&);

		friend   std::vector<std::pair<double, double>>   operator!=(_In_ PureCosDopplerShifted const&, _In_ PureCosDopplerShifted const&);

		/*
		@brief  accessor inline functions
		*/

		_Field_size_(m_uiSamplesCount) __forceinline  std::vector<std::pair<double, double>>  PureCosDopplerShift() const;

		_Field_size_(m_uiSamplesCount) __forceinline  const   double          *PCDopplerShiftArray() const;

		_Field_size_(m_uiSamplesCount) __forceinline std::vector<double>    PhaseArg() const;

		__forceinline	std::size_t      SamplesCount() const;

		__forceinline	double           InitTargetDetRange() const;

		__forceinline   double           DopplerFrequency() const;

		__forceinline   double           F0() const;

		__forceinline   double           Amplitude() const;

		__forceinline   double            TargetVelocity() const;

		__forceinline   double           TargetRange() const;

		__forceinline   double           InitTime() const;

		__forceinline   double           TimeStep() const;

		__forceinline   JonesVector      Polarization() const;

		// True for incoming direction, False for outgoing direction
		//__forceinline   bool             TargetDirection() const;

		__forceinline   mathlib::VecF64AVX    TargetDirection() const;
		// Cases: theta == 0 rad , theta != 0 rad.
		__forceinline   double           TargetRadarAngle() const;
		/*
		@brief virtual and member functions.
		*/

#if defined _DEBUG
		virtual      void          debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
		_Raises_SEH_exception_	void                        save_to_file(_In_z_ const char*, _In_z_ const char*) const;
#endif

		_Raises_SEH_exception_     virtual        void       quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

		_Raises_SEH_exception_     virtual        void       complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;

		_Raises_SEH_exception_     virtual        void       analytic_signal(_In_ std::vector<double> const&, _In_ const int) override;

		_Raises_SEH_exception_     virtual        void       instantaneous_frequency(_Inout_ std::vector<double> &) override;

		virtual        std::vector<std::pair<double, double>> pulse_samples() const override;

		virtual        std::vector<double>                    pulse_phase() const override;

		virtual        std::size_t                            pulse_samples_count() const override;

		virtual     void    amplitude_modulation(const double, const double, const double) override;

		virtual     void    frequency_modulation(double, size_t) override;

		virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;

	private:

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oPureCosDopplerShift;

		_Field_size_(m_uiSamplesCount) std::vector<double> m_oPhaseArg;

		std::size_t  m_uiSamplesCount;

		double       m_dInitTargetDetRange;

		double       m_dDopplerFrequency;
		
		
		// Central carrier frequency
		double       m_dF0;

		double       m_dAmplitude;

		double       m_dTargetVelocity;

		double       m_dTargetRange;

		double       m_dInitTime;

		double       m_dTimeStep;

		JonesVector  m_oPolarization;

		//bool         m_bTargetDirection;

		double       m_dTargetRadarAngle;
	    
		// Incoming target x = -1.0, outgoing target x = 1.0
		mathlib::VecF64AVX   m_oTargetDirection;

	};


	struct PCDSParams
	{
		_In_ double  Frequency;
		_In_ double  Velocity;
		_In_ double   Range;
		_In_ double  Amplitude;
		_In_ double   InitTime;
		_In_ double  TimeStep;
		_In_ std::size_t SamplesCount;
		_In_ int     ThreadCount;
		_In_ double    TargetDirection;
		_In_ double  TragetRadarAngle;
	};

#include "PureCosineDopplerShift.inl"
}
#endif /*_PURE_COSINE_DOPPLER_SHIFT_H_*/