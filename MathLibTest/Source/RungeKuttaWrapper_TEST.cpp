
#include "RungeKuttaWraper_TEST.h"
#include "../MathLib/MathConstants.h"

#define SQRT(x) std::sqrt(x);
#define ABS(x)  std::fabs(x);

/*
@brief Evaluate derivatives of PDE y'' = y.
*/
void          test::RKWTest::DerivY(double* T, double* Y, double* YP)
{
	YP[0] = Y[1];
	YP[1] = -Y[0];
}

/*
@brief  Measure timing performance.
*/
void           test::RKWTest::perf(unsigned long long* start, unsigned long long* end, int size, const char* funame)
{
	_ASSERT((size > 0) && (funame != nullptr));
	unsigned long long avr_start{ 0ULL }; unsigned long long avr_end{ 0ULL };
	int nIters = size;
	nIters = nIters + 1;
	std::printf("Timing performance of %s routine, using RDTSC intrinsic.\n", funame);
	std::printf("Dumping stats... \n");
	std::printf("Timing Iterations=%d\n", size);
	std::printf("Iter#   |    TSC_START    |      Delta/Iter     |     TSC_STOP\n");
	for (int i{ 1 }; i < nIters; ++i)
		std::printf("%d,          %ull,           %ull,        %ull\n", i, start[i], end[i], (end[i] - start[i]));
	std::printf(" Done!!\n");
	std::printf("Computing average number of TSC Cycles... \n");
	for (int i{ 1 }; i < nIters; ++i)
	{
		avr_start += start[i];
		avr_end += end[i];
	}
	double avr_cycles{ static_cast<double>((avr_end - avr_start) / size) };
	std::printf("Average of TSC_CYCLES=%.15f, nanoseconds=%.15f\n", avr_cycles, avr_cycles * 0.4166666666666666);
	std::printf("Done!!\n");
	
}

void             test::RKWTest::perf(std::vector<unsigned long long> &start, std::vector<unsigned long long> &stop, std::string const& fname)
{
	_ASSERTE(start.size() == stop.size());
	unsigned long long avr_start{ 0ULL };
	unsigned long long avr_stop{ 0ULL };
	std::vector<unsigned long long>::iterator iter1, iter2;
	iter1 = start.begin(); iter2 = stop.begin();
	std::printf("Timing performance of %s routine, using RDTSC intrinsic.\n", fname.c_str());
	std::printf("Dumping stats\n");
	std::printf("Iterations=%d\n", start.size());
	std::printf("   TSC_START    |     Delta/Iter     |         TSC_STOP          \n");
	while( (iter1 != start.end()) && (iter2 != stop.end()))
	{
		std::printf("%ull,            %ull,               %ull\n", *iter1.operator->(), *iter2.operator->(), (*iter2.operator->() - *iter1.operator->()));
		
		
			avr_stop += *iter2.operator->() - *iter1.operator->();
			
		++iter1;
		++iter2;
	}
	
	std::printf("%ull\n", avr_stop);
	//std::printf("Average of TSC_CYCLES/Iter=%ull, nanoseconds=%.15f\n", avr_stop / start.size(), static_cast<double>(avr_stop / start.size());
	std::printf("Done!!\n");
}
	




/*
@brief  Prepare Runge-Kutta method of calculation.
*/
void           test::RKWTest::Test1_RungeKutta()
{

	unsigned long long TSC_CYCLES_START[8] = { 0ULL };
	unsigned long long TSC_CYCLES_STOP[8] = { 0ULL };
	int NEQ{ 2 };  int LENWRK{ 32 * NEQ }; int METHOD{ 2 };
	double ZERO{ 0.0 }; double ONE{ 1.0 }; double TWO{ 2.0 }; double FOUR{ 4.0 };
	double HNEXT{ ZERO }; double HSTART{ ZERO }; double PI{ mathlib::MathConstants::PI_DBL() };
	double T{ ZERO };
	double TEND, TINC, TLAST, TOL, TSTART, TWANT; double WASTE{ 0.0 };
	int NOUT{ 8 }; int STPCST{ 0 }; int STPSOK{ 0 }; int TOTF{ 0 }; int UFLAG{ 0 };
	int ERRASS{ 0 }, MESAGE{ 1 };
	std::printf("Integrating Diff_EQ of type: Y'' = Y with METHOD=%d\n", METHOD);
	double THRES[2] = { 0.0 }; double WORK[32 * 2] = { 0.0 }; double Y[2] = { 0.0 };
	double YMAX[2] = { 0.0 }; double YP[2] = { 0.0 }; double YSTART[2] = { 0.0 };
	unsigned char TASK[] = "U";
	//void(*F)(double *, double *, double *) = &test::RKWTest::DerivY;
	TSTART = ZERO;
	YSTART[0] = ZERO;
	YSTART[1] = ONE;
	TLAST = TWO * PI;
	TEND = TLAST + PI;
	std::printf(" t:     |      y:       |     true y:   \n");
	std::printf("%.9f,   %.9f,    %.9f\n", TSTART, YSTART[0], ::sin(TSTART));
	std::printf("               %.9f,       %.9f\n", YSTART[1], ::cos(TSTART));
	std::printf("Setting ERROR and Control Parameters...");
	TOL = 5.0e-5;
	 THRES[0] = THRES[1] = 0.0000000001;
	//std::printf("THRES[1]=%.15f,THRES[2]=%.15f\n", THRES[1], THRES[2]);
	std::printf("Done\n");
	std::printf("Calling SETUP routine... ");
	SETUP(&NEQ, &TSTART, &YSTART[0], &TEND, &TOL, &THRES[0], &METHOD, &TASK[0],
		&ERRASS, &HSTART, &WORK[0], &LENWRK, &MESAGE);
	std::printf("Done\n");
	TINC = (TLAST - TSTART) / NOUT;
	std::printf("Integrating at STEPS:%u\n", NOUT);

	for (int i = 1; i < NOUT + 1; ++i)
	{
		TWANT = TLAST + (i - NOUT) * TINC;
		//mathlib::RungeKuttaSolver::rk_ut(F, TWANT, T, Y, YP, YMAX, WORK, UFLAG);
		TSC_CYCLES_START[i] = __rdtsc();
		UT([](double* T, double* Y, double* YP)->void{YP[0] = Y[1];
		YP[1] = -Y[0]; }, &TWANT, &T, &Y[0], &YP[0], &YMAX[0], WORK, &UFLAG);
		TSC_CYCLES_STOP[i] = __rdtsc();
		if (UFLAG > 2)
			goto label60;
		std::printf("%.9f, %.9f, %.9f\n", TWANT, Y[0], ::sin(TWANT));
		std::printf("              %.9f,    %.9f\n", Y[1], ::cos(TWANT));
	}
	
	std::printf("Maximum magnitude: YMAX[%d]=%.15f,YMAX[%d]=%.15f\n", 0, YMAX[0], 1, YMAX[1]);
	
		

	STAT(&TOTF, &STPCST, &WASTE, &STPSOK, &HNEXT);
	std::printf("Total calls of Derivative:%d\n", TOTF);
	std::printf("Number of Derivative calls per step:%d\n", STPCST);
	std::printf("The fraction od failed steps:%.15f\n", WASTE);
	std::printf("Number of useful steps:%d\n", STPSOK);
	std::printf("Integrator next step size:%.15f\n", HNEXT);
	
	perf(TSC_CYCLES_START, TSC_CYCLES_STOP, NOUT, "RK_UT");
	return;

label60:
	std::printf("Unexpected Soft or Hard Failure of value=%d\n", UFLAG);
	return;

}


void       test::RKWTest::Test2_RungeKutta()
{
	std::printf("Allocation and initialization of variables... ");
	//std::vector<unsigned long long> start;
	//std::vector<unsigned long long> stop;
	//const double EPS{ 0.0000001 };
	int NEQ{ 4 }; int METHOD{ 3 }; int LENWRK{ 32 * NEQ };
	double ECC{ 0.9 }; double ZERO{ 0.0 }; double ONE{ 1.0 };
	double ERROR, HNEXT, HSTART = 0.0, TEND, TNOW, TOL, TSTART, WASTE = 0.0, WEIGHT;
	int CFLAG{ 0 }; int CFLAG3; int STPCST{ 0 }, int STPSOK{ 0 }, int TOTF{ 0 };
	int ERRASS{ 0 }; int MESAGE{ 1 };
	double THRES[4] = { 0.0 }; double TRUY[4]; double WORK[32 * 4] = { 0.0 };
	double YMAX[4] = { 0.0 }; double YNOW[4] = { 0.0 }; double YPNOW[4] = { 0.0 };
	double YSTART[4] = { 0.0 };
	unsigned  char TASK[] = "C";
	std::printf("done\n");
	std::printf("Preparing to Integrate Diff_EQ of type x''  -x/r^3, y'' = -y/r^3\n");
	std::printf("Setting initial conditions... ");
	TSTART = ZERO;
	YSTART[0] = ONE - ECC;
	YSTART[1] = ZERO;
	YSTART[2] = ZERO;
	YSTART[3] = SQRT((ONE + ECC) / (ONE - ECC));
	TEND = 20.0;
	TRUY[0] = -1.29526625098758;
	TRUY[1] = 0.400393896379232;
	TRUY[2] = -0.67753909247075;
	TRUY[3] = -0.127083815427869;
	for (int i{ 0 }; i < NEQ; ++i) YMAX[i] = ABS(YSTART[i]);
	std::printf("done\n");
	std::printf("Setting error and control parameters... ");
	TOL = 0.0000000001;
	for (int i{ 0 }; i < NEQ; ++i) THRES[i] = 1.0e-13;
	std::printf("done\n");
	std::printf("Calling SETUP routine... ");
	SETUP(&NEQ, &TSTART, &YSTART[0], &TEND, &TOL, &THRES[0], &METHOD, &TASK[0],
		&ERRASS, &HSTART, &WORK[0], &LENWRK, &MESAGE);
	std::printf("done\n");
	CFLAG3 = 0;
	std::printf("Integration process started....");
	unsigned int nIters{ 0 };
	unsigned long long start{ __rdtsc() };
	do
	{
		++nIters;
		CT([](double* T, double* Y, double* YP)->void{
			double R{ std::sqrt(((Y[0] * Y[0]) + (Y[1] * Y[1]))) };
			YP[0] = Y[2];
			YP[1] = Y[3];
			YP[2] = -Y[0] / (R * R * R);
			YP[3] = -Y[1] / (R * R * R);
		}, &TNOW, &YNOW[0], &YPNOW[0], &WORK[0], &CFLAG);
		
		for (int i{ 0 }; i < NEQ; ++i) YMAX[i] = std::fmax(YMAX[i], std::fabs(YNOW[i]));

		if (CFLAG <= 3)
		{
			//std::printf("TNOW=%.15f,YNOW[%d]=%.15f,YNOW[%d]=%.15f,YNOW[%d]=%.15f,YNOW[%d]=%.15f\n", TNOW, 0, YNOW[0], 1, YNOW[1], 2, YNOW[2], 3, YNOW[3]);
			if (CFLAG == 3) CFLAG3 += 1;
			//if ((std::fabs(YNOW[0] - TRUY[0]) <= EPS) || (std::fabs(YNOW[1] - TRUY[1]) <= EPS) ||
			//(std::fabs(YNOW[2] - TRUY[3]) <= EPS) || (std::fabs(YNOW[3] - TRUY[3]) <= EPS))
			//break;
		}
		
	} while ((TNOW < TEND) && (CFLAG3 < 3));
	unsigned long long stop{ __rdtsc() };
	
	std::printf("Done!!\n");
	std::printf("Differential Equation Solution:\n");
	std::printf(" Y           |              True Y    \n");
	for (int i{ 0 }; i < NEQ; ++i) std::printf("%.15f,  %.15f\n", YNOW[i], TRUY[i]);
	std::printf("Main computation loop executed in:%llu TSC_Cycles/Iter\n", (stop - start) / nIters);
	std::printf("Solution maximum magnitude:\n");
	for (int i{ 0 }; i < NEQ; ++i)
		std::printf("YMAX[%d]=%.15f\n", i, YMAX[i]);
	std::printf("Calling STAT subroutine\n");

	STAT(&TOTF, &STPCST, &WASTE, &STPSOK, &HNEXT);
	std::printf("Integration reached %.15f\n", TNOW);
	std::printf("Total calls of Derivative:%d\n", TOTF);
	std::printf("Number of Derivative calls per step:%d\n", STPCST);
	std::printf("The fraction od failed steps:%.15f\n", WASTE);
	std::printf("Number of useful steps:%d\n", STPSOK);
	std::printf("Integrator next step size:%.15f\n", HNEXT);
	std::printf("Absolute Error analysis started\n");
	if ((std::fabs(TNOW) - std::fabs(TEND)) <= TOL)
	{
		ERROR = ZERO;
		for (int i{ 0 }; i < NEQ; ++i)
		{
			WEIGHT = std::fmax(std::fabs(YNOW[i]), THRES[i]);
			ERROR = std::fmax(ERROR, std::fabs(TRUY[i] - YNOW[i]) / WEIGHT);
		}
		std::printf("At t = 20, the error is:%.15f\n", ERROR);
		std::printf("Tolerance=%.15f\n", TOL);
	}
	//perf(start, stop, std::string("CT"));
	std::printf("Done!!\n");
}
	
void          test::RKWTest::Test3_RungeKutta()
{
	std::printf("Allocation and initialization of variables... ");

	int NEQ{ 2 }; int METHOD{ 2 }; int NWANT{ NEQ }; int NINT{ 6 * NEQ };
	int LENWRK{ 14 * NEQ }; int MAXPER{ 100 };
	double ZERO{ 0.0 }; double ONE{ 1.0 }; double FOUR{ 4.0 };
	double HNEXT, TEND, TNOW, TOUT, TSTART, TOL, WASTE;
	double HSTART{ ZERO }; double PI{ mathlib::MathConstants::PI_DBL() };
	double TWOPI{ mathlib::MathConstants::TWO_PI_DBL() }; 
	test::BPARAM bparam;
	bparam.B = 9.8;
	double B{ 9.8 };
	int CFLAG, KOUNTR, STPCST, STPSOK, TOTF;
	int ERRASS{ 0 }; int MESAGE{ 0 };
	double THRES[2] = { 0.0 }; double WORK[28] = { 0.0 }; double WRKINT[12] = { 0.0 };
	double YNOW[2] = { 0.0 }; double YOUT[2] = { 0.0 }; double YPNOW[2] = { 0.0 };
	double YPOUT[1] = { 0.0 }; double YSTART[2] = { 0.0 };
	unsigned char TASK[] = "C"; unsigned char REQUEST[] = "S";
	std::printf("Done!!\n");
	std::printf("Preparing to integrate Diff_EQ of form y1'=y2, y2'=-0.1*y2-y1^3+B*cos(t)\n");
	std::printf("Setting initial conditions... ");
	TSTART = ZERO;
	YSTART[0] = 3.3;
	YSTART[1] = -3.3;
	TEND = TSTART + MAXPER * TWOPI + TWOPI;
	std::printf("Done!!\n");
	std::printf("Setting error control parameters... ");
	TOL = 1.0e-5;
	THRES[0] = 1.0e-10; THRES[1] = 1.0e-10;
	std::printf("Done!!\n");
	std::printf("Calling SETUP Subroutine... ");
	SETUP(&NEQ, &TSTART, &YSTART[0], &TEND, &TOL, &THRES[0], &METHOD, &TASK[0],
		&ERRASS, &HSTART, &WORK[0], &LENWRK, &MESAGE);
	std::printf("Done!!\n");
	KOUNTR = 1;
	TOUT = TSTART + TWOPI;
	int nIters{ 0 };
	unsigned long long start{ __rdtsc() };
    label40:
	++nIters;
	
		CT([](double* T, double* Y, double* YP)->void{
			double K{ 0.1 };
			YP[0] = Y[1];
			YP[1] = -K*Y[1] - (Y[0] * Y[0] * Y[0]) + 9.8 * ::cos(*T);
		}, &TNOW, &YNOW[0], &YPNOW[0], &WORK[0], &CFLAG);
		unsigned long long end{ __rdtsc() };
	label80:
		if (TNOW < TOUT)
			goto label40;
		else
		{
			INTRP(&TOUT, &REQUEST[0], &NWANT, &YOUT[0], &YPOUT[0], [](double* T, double* Y, double* YP)->void{
				double K{ 0.1 };
				YP[0] = Y[1];
				YP[1] = -K*Y[1] - (Y[0] * Y[0] * Y[0]) + 9.8 * ::cos(*T);
			}, &WORK[0], &WRKINT[0], &NINT);
			
			if (KOUNTR < MAXPER)
			{
				KOUNTR += 1;
				TOUT += TWOPI;
				goto label80;
			}
			goto label180;
		}
	
		if (CFLAG == 3)
			goto label40;
		else if (CFLAG == 4)
		{
			std::printf("The problem appears to be stiff, exiting\n");
			goto Failure;
		}
		else if (CFLAG == 5)
		{
			std::printf("The accuracy request is too stringent, exiting\n");
			goto Failure;
		}
		else if (CFLAG == 6)
		{
			std::printf("Global error estimation broke down, exiting\n");
			goto Failure;
		}

	label180:
		//Call STAT.
		std::printf("Solution of Diff_EQ... ");
		std::printf("YOUT[%d]=%.15f\n", 0, YOUT[0]);
		std::printf(" YOUT[%d]=%.15f\n", 1, YOUT[1]);
					                    
		if (((end - start) > 0) && (nIters > 0))
		std::printf("Cost of single call to CT:%lluTSC_CYCLES\n", (end - start) / nIters);
		std::printf("Calling STAT Subroutine, getting statistics\n");
		STAT(&TOTF, &STPCST, &WASTE, &STPSOK, &HNEXT);
		std::printf("The integration reached:%.15f\n", TNOW);
		std::printf("The cost of integration in calls to Derivative:%d\n", TOTF);
		std::printf("The number of calls to Derivative per step:%d\n", STPCST);
		std::printf("The fraction of failed steps:%.15f\n", WASTE);
		std::printf("The number of accepted steps:%d\n", STPSOK);

		return;

	Failure :
		std::printf("Catastrophic error cannot continue, exiting\n");
			return;
}

void             test::RKWTest::Test4_RungeKutta()
{
	std::printf("Allocation and initialization of variables... ");
	int NEQ{ 2 }; int METHOD{ 3 }; int LENWRK{ 21 * NEQ }; int MAXPER{ 100 };
	double ZERO{ 0.0 }; double ONE{ 1.0 }; double FOUR{ 4.0 };
	double ERRMAX, HNEXT, HSTART, TEND, TERRMAX, TNOW, TOL, TSTART, WASTE;
	int CFLAG, KOUNTR, STPCST, STPSOK, TOTF;
	int ERRASS{ 1 }; int MESAGE{ 0 };
	double RMSERR[2] = { 0.0 }; double THRES[2] = { 0.0 }; double WORK[42] = { 0.0 };
	double YNOW[2] = { 0.0 }; double YPNOW[2] = { 0.0 }; double YSTART[2] = { 0.0 };
	double PI{ mathlib::MathConstants::PI_DBL() }; double TWOPI{ mathlib::MathConstants::TWO_PI_DBL() };
	unsigned char TASK[] = "C";
	std::printf("Done!!\n");
	std::printf("Setting initial conditions... ");
	TSTART = ZERO;
	YSTART[0] = 3.3;
	YSTART[1] = -3.3;
	TEND = TSTART + TWOPI;
	std::printf("Done!!\n");
	std::printf("Setting error conditions... ");
	TOL = 1.0E-7;
	THRES[0] = THRES[1] = 1.0E-10;
	std::printf("Done!!\n");
	HSTART = ZERO;
	std::printf("Calling SETUP Subroutine... ");
	SETUP(&NEQ, &TSTART, &YSTART[0], &TEND, &TOL, &THRES[0], &METHOD, &TASK[0],
		&ERRASS, &HSTART, &WORK[0], &LENWRK, &MESAGE);
	std::printf("Done!!\n");
	KOUNTR = 1;
	int nIters{ 0 };
	unsigned long long start{ __rdtsc() };
label40:
	++nIters;
	
	CT([](double* T, double* Y, double* YP)->void{
		double K{ 0.1 };
		YP[0] = Y[1];
		YP[1] = -K*Y[1] - (Y[0] * Y[0] * Y[0]) + 11.0*::cos(*T);
	}, &TNOW, &YNOW[0], &YPNOW[0], &WORK[0], &CFLAG);
	unsigned long long stop{ __rdtsc() };
	if ((CFLAG == 1) || (CFLAG == 2))
	if (TNOW < TEND)
		goto label40;
	else
	{
		std::printf("YNOW[%d]=%.15f, YNOW[%d]=%.15f\n", 0, YNOW[0], 1, YNOW[1]);
		if (KOUNTR < MAXPER)
		{
			KOUNTR += 1;
			TEND += TWOPI;
			RESET(&TEND);
			goto label40;
		}
		else
			goto label160;
	}
	if (CFLAG == 3)
		goto label40;
	else if (CFLAG == 4)
	{
		std::printf("The problem appears to be stiff, exiting\n");
		goto Failure;
	}
	else if (CFLAG == 5)
	{
		std::printf("The accuracy request is too stringent, exiting\n");
		goto Failure;
	}
	else if (CFLAG == 6)
	{
		std::printf("Global estimation error broke down\n");
		goto label160;
	}

	label160:
	std::printf("Calling GLBERR for an error assesment\n");
	if (ERRASS)
	{
		GLBERR(&RMSERR[0], &ERRMAX, &TERRMAX, &WORK[0]);
		std::printf("Tolerance:%.15f\n", TOL);
		std::printf("Worst global error was:%.15f,(It occured at:%.15f)\n", ERRMAX, TERRMAX);
		std::printf("RMS errors in individual components:\n");
		std::printf("RMSERR[%d]=%.15f,RMSERR[%d]=%.15f\n", 0, RMSERR[0], 1, RMSERR[1]);
	}
	std::printf("Calling STAT Subroutine... ");
	STAT(&TOTF, &STPCST, &WASTE, &STPSOK, &HNEXT);
	std::printf("Done!!\n");
	std::printf("Getting run-time stats\n");
	std::printf("The integration reached:%.15f\n", TNOW);
	std::printf("Cost of integration in terms of Derivative calls:%d\n", TOTF);
	std::printf("Number of Derivative calls per step:%d\n", STPCST);
	std::printf("Fraction of failed steps:%.15f\n", WASTE);
	std::printf("Number of accepted steps:%d\n", STPSOK);
	std::printf("Next integration step:%.15f\n", HNEXT);
	if (((stop - start) > 0) && (nIters > 0))
		std::printf("Cost of single call to CT is:%lluTSC_CYCLES\n", (stop - start) / nIters);
	return;

Failure :
	std::printf("Failure!! cannot continue... exiting\n");
		return;
}
	

		
	
	
	



	



void      test::RKWTest::Run_Tests()
{
	std::printf("Test #1 of Runge-Kutta ODE Solver has started\n");
	Test1_RungeKutta();
	std::printf("Test #1 of Runge-Kutta ODE Solver has ended\n\n");
	std::printf("Test #2 of Runge-Kutta ODE Solver has started\n");
	Test2_RungeKutta();
	std::printf("Test #2 of Runge-Kutta ODE Solver has ended\n\n");
	std::printf("Test #3 of Runge-Kutta ODE Solver has started\n");
	Test3_RungeKutta();
	std::printf("Test #3 of Runge-Kutta ODE Solver has ended\n\n");
	std::printf("Test #4 of Runge-Kutta ODE Solver has started\n");
	Test4_RungeKutta();
	std::printf("Test #4 of Runge-Kutta ODE Solver has ended\n\n");
}

