#ifndef _PURE_COSINE_H_
#define _PURE_COSINE_H_


#include "WaveformInterface.h"

#include "Polarization.h"

namespace  radiolocation
{

	class PureCosineWave : public Waveform
	{
             

	public:


		PureCosineWave() = default;
		/*
		@Brief: "Main" class Constructor.
		*/
	

	_Raises_SEH_exception_  PureCosineWave(_In_ struct PureCosineParams const&);

	/*
	@Brief: "Special" Constructor which creates zero amplitude object.
	*/
	_Raises_SEH_exception_  PureCosineWave(_In_ const double, _In_ const double, _In_ const double, _In_ std::size_t);

	
	/*
	@Brief: Copy-Constructor.
	*/
	                        PureCosineWave(_In_  PureCosineWave const&);
							/*
							@Brief:  Move-Constructor.
							*/
							PureCosineWave(_In_ PureCosineWave &&);
							/*
							@Brief: Destructor explicity default.
							*/
							~PureCosineWave()
							{

							}
							/*
							@Brief: operator= move-assignment
							*/
							PureCosineWave&                  operator=(_In_ PureCosineWave const&);
							/*
							@Brief: operator= copy-assignment
							*/
							PureCosineWave&                  operator=(_In_ PureCosineWave &&);
							/*
							@Brief: operator<<
							*/
							friend  std::ostream&            operator<<(_In_ std::ostream&, _In_ PureCosineWave const&);


		__forceinline   std::vector<std::pair<double, double>>  get_cos() const;

		__forceinline   std::vector<double>                     get_phase() const;

		__forceinline   const double                           *get_phase_ptr();
		/*
		@Brief: number of sampling points.
		*/
		__forceinline   size_t                                  get_samples() const;
		/*
		@Brief: Signal simulated frequency.
		*/
		__forceinline   double                                  get_frequency() const;
		/*
		@Brief: Signal time step interval.
		*/
		__forceinline   double                                  get_time_step() const;
		/*
		@Brief: Signal starting time , t0.
		*/
		__forceinline   double                                  get_init_time() const;
		/*
		@Brief: Signal amplitude.
		*/
		__forceinline   double                                  get_amplitude() const;

		/*
		@Brief: Signal Polarization either verical or horizontal.
		*/
		__forceinline   JonesVector                            polarization() const;
		/*
		@Brief: Returns *this modified by variadic template arguments.
		*/
		template<typename _Fx, typename... _Ty> __forceinline   PureCosineWave&   apply(_In_ _Fx, _In_ _Ty&&...);

		/*
		@Brief: Returns signal real frequency.
		*/
	  __forceinline 	double                                  n_cycles() const;

#if defined _DEBUG

		virtual         void                                     debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE

		_Raises_SEH_exception_   void             save_to_file(_In_z_ const char*, _In_z_ const char*);
#endif

		/*
		@Brief: pure virtual function simplementation
		*/

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
		*/
		_Raises_SEH_exception_  virtual    void             quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
		*/
		_Raises_SEH_exception_    virtual       void                           complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
		*/
		_Raises_SEH_exception_    virtual       void                           analytic_signal(_In_  std::vector<double> const&, _In_ const int) override;

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::instantaneous_frequency.
		*/
		_Raises_SEH_exception_    virtual       void                           instantaneous_frequency(_Inout_ std::vector<double> &) override;

	//	virtual         void                                    amplitude_modulation(const double, const double, const double);

	//	virtual         void                                    phase_modulation(const double, const double, const double, std::function<double(double, double)>&);

		virtual    std::vector<std::pair<double, double>>  pulse_samples() const override;

		virtual    std::vector<double>                     pulse_phase() const override;

		virtual    std::size_t                             pulse_samples_count() const override;

		virtual     void    amplitude_modulation(const double, const double, const double) override;

		virtual     void    frequency_modulation(double, size_t) override;

		virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;


	protected:
		/*
		@Brief: Signal cos(phase(t))
		*/
	_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_cos;

	/*
	@Brief:    Signal phase argument, phase(t)
	*/
	_Field_size_(m_samples) std::vector<double> m_phase;

	/*
	@Brief: SIgnal frequency (real) for ilustrative purpose.
	*/
		double  m_frequency;
		/*
		@Brief: Number of waveform samples.
		*/
		std::size_t  m_samples;
		/*
		@Brief: time step increment.
		*/
		double  m_time_step;
		/*
		@Brief: starting point of waveform
		*/
		double  m_init_time;
		/*
		@Brief: Waveform amplitude.
		*/
	    double m_amplitude;
		/*
		@Brief Waveform plarization vector set to fixed vertical linear polarization.
		*/
		JonesVector m_polarization;

		const static double TWO_PI;


		/*
		@Brief: Creates PureCosine Wave unmodulated
		*/
_Raises_SEH_exception_      void  create_signal(_In_ struct PureCosineParams const&);

/*
@Brief:  Creates special null waveform which serves as a inter-pulse time delay.
*/
_Raises_SEH_exception_		void  create_signal(_In_ const double, _In_ const double, _In_ const double, _In_ const std::size_t);

/*
@Brief: Copies PureCosineWave to this.
*/
		void  create_signal(_In_  PureCosineWave const&);
		/*
		@Brief: Moves PureCosineWave to this.
		*/
		void  create_signal(_In_  PureCosineWave &&);

		double    static      n_cycles(_In_ const std::size_t, _In_ const double);

		//void    initialize(const size_t, const double, double, const double);
	};

	/*
	@Brief Aggregated parameters structure.
	*/
	struct PureCosineParams
	{
		_In_ double amplitude;
		_In_ double init_time;
		_In_ double timestep;
		_In_ double sfreq;
		_In_ std::size_t n_samples;
		_In_ int n_threads;
	};

	/*
	@brief Inherited AWGNoiseCosine class.
	*/

	class AWGNoiseCosine : public PureCosineWave
	{

	public:

		/*
		@brief: Constructs only AWGNCosine object.
		*/
		AWGNoiseCosine(_In_ struct AWGNCosParams const&);

		/*
		@brief: Constructs PureCosineWave with additive White Gaussian Noise.
		*/
	_Raises_SEH_exception_	AWGNoiseCosine(_In_ struct PureCosineParams const&, _In_ struct AWGNCosParams const&);

	~AWGNoiseCosine()
	{

	}

		/*
		@brief: Copy Constructor.
		*/
		AWGNoiseCosine(_In_ AWGNoiseCosine const&);

		/*
		@brief: Move Constructor.
		*/
		AWGNoiseCosine(_In_ AWGNoiseCosine &&);

		/*
		@brief: operator= copy-assignment.
		*/
		AWGNoiseCosine &               operator=(_In_ AWGNoiseCosine const&);

		/*
		@brief: operator= move-assignment.
		*/
		AWGNoiseCosine &               operator=(_In_ AWGNoiseCosine &&);

		/*
		@brief: Returns White Gaussian Noise single value.
		*/
		double                         operator()(_In_ struct AWGNCosParams const&) const;

		std::pair<double, double>       operator[](_In_ const std::size_t);

		const  std::pair<double, double>  operator[](_In_ const std::size_t) const;

	friend	std::ostream&                  operator<<(_In_ std::ostream&, _In_ AWGNoiseCosine const&);

		__forceinline   std::function<double(double)>      WaveformGenerator() const;

		__forceinline   std::vector<std::pair<double, double>> AWGNCosine() const;

		__forceinline   std::size_t       Samples() const;

		__forceinline   double            Mean() const;

		__forceinline   double            Variance() const;

		
	private:
		/*
		@brief: Noise Waveform generator.
		*/
		std::function<double(double)> m_oWaveformGenerator;

		/*
		@brief: White Gaussian Noise vector.
		*/
		std::vector<std::pair<double, double>>  m_AWGNCosine;

		/*
		@brief: Number of Noise waveform samples.
		*/
		std::size_t  m_uisamples;

		/*
		@brief: mean.
		*/
		double  m_dmean;

		/*
		@brief: variance.
		*/
		double  m_dvariance;

	};

	struct AWGNCosParams
	{
		_In_  std::function<double(double)> WaveformGenerator;
		_In_  std::size_t samples;
		_In_  double  mean;
		_In_  double  variance;
	};

#include "PureCosine.inl"
}
#endif /*_PURE_COSINE*/