#ifndef _RUNGE_KUTTA_F77_DECLARATIONS_H_
#define _RUNGE_KUTTA_F77_DECLARATIONS_H_


#if defined __cplusplus
extern "C"
{
	/*
	@brief  SUBROUTINE SETUP(NEQ,TSTART,YSTART,TEND,TOL,THRES,METHOD,TASK,
                     ERRASS,HSTART,WORK,LENWRK,MESAGE)

					 INPUT VARIABLES
					 C
					 C     NEQ       - INTEGER
					 C                 The number of differential equations in the system.
					 C                 Constraint: NEQ >= 1
					 C     TSTART    - DOUBLE PRECISION
					 C                 The initial value of the independent variable.
					 C     YSTART(*) - DOUBLE PRECISION array of length NEQ
					 C                 The vector of initial values of the solution components.
					 C     TEND      - DOUBLE PRECISION
					 C                 The integration proceeds from TSTART in the direction of
					 C                 TEND. You cannot go past TEND.
					 C                 Constraint: TEND must be clearly distinguishable from TSTART
					 C                 in the precision available.
					 C     TOL       - DOUBLE PRECISION
					 C                 The relative error tolerance.
					 C                 Constraint: 0.01D0 >= TOL >= 10*MCHEPS
					 C     THRES(*)  - DOUBLE PRECISION array of length NEQ
					 C                 THRES(L) is the threshold for the Ith solution component.
					 C                 Constraint: THRES(L) >= SQRT(DWARF)
					 C     METHOD    - INTEGER
					 C                 Specifies which Runge-Kutta pair is to be used.
					 C                  = 1 - use the (2,3) pair
					 C                  = 2 - use the (4,5) pair
					 C                  = 3 - use the (7,8) pair
					 C     TASK      - CHARACTER*(*)
					 C                 Only the first character of TASK is significant.
					 C                 TASK(1:1) = `U' or `u' - UT is to be used
					 C                           = `C' or `c' - CT is to be used
					 C                 Constraint: TASK(1:1) = `U'or `u' or`C' or `c'
					 C     ERRASS    - LOGICAL
					 C                 = .FALSE. - do not attempt to assess the true error.
					 C                 = .TRUE.  - assess the true error. Costs roughly twice
					 C                             as much as the integration with METHODs 2 and
					 C                             3, and three times with METHOD = 1.
					 C     HSTART    - DOUBLE PRECISION
					 C                 0.0D0     - select automatically the first step size.
					 C                 non-zero  - try HSTART for the first step.
					 C
					 C  WORKSPACE
					 C
					 C     WORK(*) - DOUBLE PRECISION array of length LENWRK
					 C               Do not alter the contents of this array after calling SETUP.
					 C
					 C  INPUT VARIABLES
					 C
					 C     LENWRK  - INTEGER
					 C               Length of WORK(*): How big LENWRK must be depends
					 C               on the task and how it is to be solved.
					 C
					 C               LENWRK = 32*NEQ is sufficient for all cases.
					 C
					 C               If storage is a problem, the least storage possible
					 C               in the various cases is:
					 C
					 C                 If TASK = `U' or `u', then
					 C                   if ERRASS = .FALSE. and
					 C                     METHOD = 1, LENWRK must be at least 10*NEQ
					 C                            = 2                          20*NEQ
					 C                            = 3                          16*NEQ
					 C                   if ERRASS = .TRUE. and
					 C                     METHOD = 1, LENWRK must be at least 15*NEQ
					 C                            = 2                          32*NEQ
					 C                            = 3                          21*NEQ
					 C
					 C                 If TASK = `C' or `c', then
					 C                   if ERRASS = .FALSE. and
					 C                     METHOD = 1, LENWRK must be at least 10*NEQ
					 C                            = 2                          14*NEQ
					 C                            = 3                          16*NEQ
					 C                   if ERRASS = .TRUE. and
					 C                     METHOD = 1, LENWRK must be at least 15*NEQ
					 C                            = 2                          26*NEQ
					 C                            = 3                          21*NEQ
					 C
					 C                 Warning:  To exploit the interpolation capability
					 C                 of METHODs 1 and 2, you have to call INTRP.  This
					 C                 subroutine requires working storage in addition to
					 C                 that specified here.
					 C
					 C     MESAGE    - LOGICAL
					 C                 Specifies whether you want informative messages written to
					 C                 the standard output channel OUTCH.
					 C                 = .TRUE.   - provide messages
					 C                 = .FALSE.  - do not provide messages
	*/
	void  SETUP(int *, double *, double *, double *, double *, double *,
		int *, unsigned char *, int *, double *, double *, int *, int *);

	/*
	@brief SUBROUTINE UT(F,TWANT,TGOT,YGOT,YPGOT,YMAX,WORK,UFLAG)
	C  The subroutine F must have the form
	C
	C  SUBROUTINE F(T,Y,YP)
	C  DOUBLE PRECISION T,Y(*),YP(*)
	C     Given input values of the independent variable T and the solution
	C     components Y(*), for each L = 1,2,...,NEQ evaluate the differential
	C     equation for the derivative of the Ith solution component and place the
	C     value in YP(L).  Do not alter the input values of T and Y(*).
	C  RETURN
	C  END
	C
	C  INPUT VARIABLE
	C
	C     TWANT     - DOUBLE PRECISION
	C                 The next value of the independent variable where a
	C                 solution is desired.
	C
	C                 Constraints: TWANT must lie between the previous value
	C                 of TGOT (TSTART on the first call) and TEND. TWANT can be
	C                 equal to TEND, but it must be clearly distinguishable from
	C                 the previous value of TGOT (TSTART on the first call) in
	C                 the precision available.
	C
	C  OUTPUT VARIABLES
	C
	C     TGOT      - DOUBLE PRECISION
	C                 A solution has been computed at this value of the
	C                 independent variable.
	C     YGOT(*)   - DOUBLE PRECISION array of length NEQ
	C                 Approximation to the true solution at TGOT. Do not alter
	C                 the contents of this array
	C     YPGOT(*)  - DOUBLE PRECISION array of length NEQ
	C                 Approximation to the first derivative of the true
	C                 solution at TGOT.
	C     YMAX(*)   - DOUBLE PRECISION array of length NEQ
	C                 YMAX(L) is the largest magnitude of YGOT(L) computed at any
	C                 time in the integration from TSTART to TGOT. Do not alter
	C                 the contents of this array.
	C
	C  WORKSPACE
	C
	C     WORK(*)   - DOUBLE PRECISION array as used in SETUP
	C                 Do not alter the contents of this array.
	C
	C  OUTPUT VARIABLE
	C
	C     UFLAG     - INTEGER
	
	*/
	void     UT(void(*)(double *, double *, double *), double *, double *, double *, double *, double *, double *, int *);

	/*
	@brief SUBROUTINE STAT(TOTFCN,STPCST,WASTE,STPSOK,HNEXT)
	STAT is called to obtain some details about the integration.
	C
	C  OUTPUT VARIABLES
	C
	C     TOTFCN    - INTEGER
	C                 Total number of calls to F in the integration so far --
	C                 a measure of the cost of the integration.
	C     STPCST    - INTEGER
	C                 Cost of a typical step with this METHOD measured in
	C                 calls to F.
	C     WASTE     - DOUBLE PRECISION
	C                 The number of attempted steps that failed to meet the
	C                 local error requirement divided by the total number of
	C                 steps attempted so far in the integration.
	C     STPSOK    - INTEGER
	C                 The number of accepted steps.
	C     HNEXT     - DOUBLE PRECISION
	C                 The step size the integrator plans to use for the next step.
	*/
	void     STAT(int *, int *, double *, int *, double *);

	/*
	@brief   SUBROUTINE GLBERR(RMSERR,ERRMAX,TERRMX,WORK)
	OUTPUT VARIABLES
	C
	C     RMSERR(*) - DOUBLE PRECISION array of length NEQ
	C                 RMSERR(L) approximates the RMS average of the true error
	C                 of the numerical solution for the Ith solution component,
	C                 L = 1,2,...,NEQ.  The average is taken over all steps from
	C                 TSTART to TNOW.
	C     ERRMAX    - DOUBLE PRECISION
	C                 The maximum (approximate) true error taken over all
	C                 solution components and all steps from TSTART to TNOW.
	C     TERRMX    - DOUBLE PRECISION
	C                 First value of the independent variable where the
	C                 (approximate) true error attains the maximum value ERRMAX.
	C
	C  WORKSPACE
	C
	C     WORK(*)   - DOUBLE PRECISION array as used in SETUP and UT or CT
	C                 Do not alter the contents of this array.
	*/
	void      GLBERR(double *, double *, double *, double *);

	/*
	@brief  SUBROUTINE CT(F,TNOW,YNOW,YPNOW,WORK,CFLAG)
	SUBROUTINE F(T,Y,YP)
	C  DOUBLE PRECISION T,Y(*),YP(*)
	C     Using the input values of the independent variable T and the solution
	C     components Y(*), for each L = 1,2,...,NEQ evaluate the differential
	C     equation for the derivative of the Lth solution component and place the
	C     value in YP(L).  Do not alter the input values of T and Y(*).
	C  RETURN
	C  END
	C
	C  OUTPUT VARIABLES
	C
	C     TNOW      - DOUBLE PRECISION
	C                 Current value of the independent variable.
	C     YNOW(*)   - DOUBLE PRECISION array of length NEQ
	C                 Approximation to the true solution at TNOW.
	C     YPNOW(*)  - DOUBLE PRECISION array of length NEQ
	C                 Approximation to the first derivative of the
	C                 true solution at TNOW.
	C
	C  WORKSPACE
	C
	C     WORK(*)   - DOUBLE PRECISION array as used in SETUP
	C                 Do not alter the contents of this array.
	C
	C  OUTPUT VARIABLE
	C
	C     CFLAG     - INTEGER
	C
	C                       SUCCESS.  A STEP WAS TAKEN TO TNOW.
	*/
	void        CT(void(*)(double *, double *, double *), double *, double *, double *, double *, int *);

	/*
	@brief  SUBROUTINE INTRP(TWANT,REQEST,NWANT,YWANT,YPWANT,F,WORK,WRKINT,
                     LENINT)

					 INPUT VARIABLE
					 C
					 C     TWANT     - DOUBLE PRECISION
					 C                 The value of the independent variable where a solution
					 C                 is desired.
					 C
					 C  The interpolant is to be evaluated at TWANT to approximate the solution
					 C  and/or its first derivative there.  There are three cases:
					 C
					 C  INPUT VARIABLE
					 C
					 C     REQEST    - CHARACTER*(*)
					 C                 Only the first character of REQEST is significant.
					 C                 REQEST(1:1) = `S' or `s'- compute approximate `S'olution
					 C                                           only.
					 C                             = `D' or `d'- compute approximate first
					 C                                           `D'erivative of the solution only.
					 C                             = `B' or `b'- compute `B'oth approximate solution
					 C                                           and first derivative.
					 C                 Constraint: REQEST(1:1) must be `S',`s',`D',`d',`B' or `b'.
					 C
					 C  If you intend to interpolate at many points, you should arrange for the
					 C  the interesting components to be the first ones because the code
					 C  approximates only the first NWANT components.
					 C
					 C  INPUT VARIABLE
					 C
					 C     NWANT     - INTEGER
					 C                 Only the first NWANT components of the answer are to be
					 C                 computed.
					 C                 Constraint:  NEQ >= NWANT >= 1
					 C
					 C  OUTPUT VARIABLES
					 C
					 C     YWANT(*)  - DOUBLE PRECISION array of length NWANT
					 C                 Approximation to the first NWANT components of the true
					 C                 solution at TWANT when REQESTed.
					 C     YPWANT(*) - DOUBLE PRECISION array of length NWANT
					 C                 Approximation to the first NWANT components of the first
					 C                 derivative of the true solution at TWANT when REQESTed.
					 C
					 C  NAME DECLARED IN AN EXTERNAL STATEMENT IN THE PROGRAM CALLING INTRP:
					 C
					 C     F         - name of the subroutine for evaluating the differential
					 C                 equations as provided to CT.
					 C
					 C  WORKSPACE
					 C
					 C     WORK(*)   - DOUBLE PRECISION array as used in SETUP and CT
					 C                 Do not alter the contents of this array.
					 C
					 C     WRKINT(*) - DOUBLE PRECISION array of length LENINT
					 C                 Do not alter the contents of this array.
					 C
					 C     LENINT    - INTEGER
					 C                 Length of WRKINT. If
					 C                 METHOD = 1, LENINT must be at least 1
					 C                        = 2, LENINT must be at least NEQ+MAX(NEQ,5*NWANT)
					 C                        = 3--CANNOT BE USED WITH THIS SUBROUTINE
	*/
	void             INTRP(double *, unsigned char *, int *, double *, double *, void(*)(double *, double *, double *), double *, double *, int *);

	/*
	@brief          SUBROUTINE RESET(TENDNU)
	The integration using CT proceeds from TSTART in the direction of TEND, and
	C  is now at TNOW.  To reset TEND to a new value TENDNU, just call RESET with
	C  TENDNU as the argument.  You must continue integrating in the same
	C  direction, so the sign of (TENDNU - TNOW) must be the same as the sign of
	C  (TEND - TSTART). To change direction you must restart by a call to SETUP.
	C
	C  INPUT VARIABLE
	C
	C     TENDNU    - DOUBLE PRECISION
	C                 The new value of TEND.
	C                 Constraint: TENDNU and TNOW must be clearly distinguishable
	C                 in the precision used.  The sign of (TENDNU - TNOW) must be
	C                 the same as the sign of (TEND - TSTART).
	*/
	void             RESET(double *);

	/*
	@brief  SUBROUTINE MCONST(METHOD)
	Purpose:   Sets machine-dependent global quantities
	C
	C  Common:    Initializes:    /RKCOM7/ OUTCH, MCHEPS, DWARF, RNDOFF,
	C                                      SQRRMC, CUBRMC, TINY
	C             Reads:          none
	C             Alters:         none
	C
	C  Comments:
	C  =========
	C  OUTCH, MCHEPS, DWARF are pure environmental parameters with values
	C  obtained from a call to ENVIRN. The other quantities set depend on
	C  the environmental parameters, the implementation, and, possibly,
	C  METHOD. At present the METHODs implemented in the RK suite do not
	C  influence the values of these quantities.
	C  OUTCH  - Standard output channel
	C  MCHEPS - Largest positive number such that 1.0D0 + MCHEPS = 1.0D0
	C  DWARF  - Smallest positive number
	C  RNDOFF - 10 times MCHEPS
	C  SQRRMC - Square root of MCHEPS
	C  CUBRMC - Cube root of MCHEPS
	C  TINY   - Square root of DWARF
	*/
	void           MCONST(int *);

	/*
	@brief  SUBROUTINE ENVIRN(OUTCH,MCHEPS,DWARF)

	C  OUTPUT VARIABLES
	C
	C     OUTCH     - INTEGER
	C                 Standard output channel
	C     MCHEPS    - DOUBLE PRECISION
	C                 MCHEPS is the largest positive number such that
	C                 1.0D0 + MCHEPS = 1.0D0.
	C     DWARF     - DOUBLE PRECISION
	C                 DWARF is the smallest positive number.
	*/
	void           ENVIRN(int *, double *, double *);

	/*
	@brief  SUBROUTINE CONST(METHOD,VECSTG,REQSTG,LINTPL)
	Purpose:   Set formula definitions and formula characteristics for
	C             selected method. Return storage requirements for the
	C             selected method.
	C
	C  Input:     METHOD
	C  Output:    VECSTG, REQSTG, LINTPL
	C
	C  Common:    Initializes:    /RKCOM4/ A(*,*), B(*), C(*), BHAT(*), R(*),
	C                                      E(*), PTR(*), NSTAGE, METHD, INTP, MINTP
	C                             /RKCOM5/ TOOSML, COST, SAFETY, EXPON, STBRAD,
	C                                      TANANG, RS, RS1, RS2, RS3, RS4, ORDER,
	C                                      LSTSTG, MAXTRY, NSEC, FSAL
	C             Reads:          /RKCOM7/ RNDOFF
	C             Alters:         none
	*/
	//void           CONST(int *, int *, int *, int *);

	/*
	@brief  SUBROUTINE FORMI(F,NEQ,NWANT,Y,YP,YOLD,YPOLD,STAGES,CALSTG,
                     XSTAGE,P)
					 Purpose:    Forms an interpolating polynomial for use with
					 C              METHDs 1 or 2.
					 C
					 C  Input:      NEQ, NWANT, T, Y(*), YP(*), HOLD, YOLD(*), YPOLD(*),
					 C              STAGES(NEQ,*), CALSTG
					 C  Output:     P(*), XSTAGE(NEQ)
					 C  External:   F
					 C
					 C  Common:     Initializes:    none
					 C              Reads:          /RKCOM4/ A(*,*), C(*), R(*), METHD, MINTP
					 C                              /RKCOM2/ T, TOLD, HOLD
					 C              Alters:         /RKCOM2/ NFCN
					 C
					 C  Comments:
					 C  =========
					 C  The integration has reached T with a step HOLD from TOLD = T-HOLD.
					 C  Y(*),YP(*) and YOLD(*),YPOLD(*) approximate the solution and its
					 C  derivative at T and TOLD respectively.  STAGES(NEQ,*) holds the stages
					 C  computed in taking this step. In the case of METHD = 2 it is necessary
					 C  to compute some more stages in this subroutine. CALSTG indicates whether
					 C  or not the extra stages need to be computed. A(*,*) and C(*) are used in
					 C  computing these stages. The extra stages are stored in STAGES(NEQ,*) and
					 C  XSTAGE(*).  The coefficients of the interpolating polynomials for the first
					 C  NWANT components of the solution are returned in the array P(*). The
					 C  polynomial is of degree MINTP = 3 for METHD = 1 and of degree MINTP = 6
					 C  for METHD = 2. The vector R(*) is used for workspace when METHD = 2.
	*/
	void        FORMI(void(*)(double *, double *, double *), int *, int *, double *, double *, double *, double *, double *, int *, double *, double *);

	/*
	@brief  SUBROUTINE EVALI(Y,YP,P,TWANT,REQEST,NWANT,YWANT,YPWANT)
	Purpose:    Evaluation of an interpolating polynomial and/or its
	C              first derivative.
	C
	C  Input:      Y(*), YP(*), P(NWANT,*), TWANT, REQEST, NWANT
	C  Output:     YWANT(*), YPWANT(*)
	C
	C  Common:     Initializes:    none
	C              Reads:          /RKCOM2/ HOLD, T
	C                              /RKCOM4/ MINTP
	C              Alters:         none
	C
	C  Comments:
	C  =========
	C  The interpolant is evaluated at TWANT to approximate the solution,
	C  YWANT, and/or its first derivative there, YPWANT. Only the first
	C  NWANT components of the answer are computed. There are three cases
	C  that are indicated by the first character of REQEST:
	C    REQEST(1:1) = `S' or `s'- compute approximate `S'olution only.
	C                = `D' or `d'- compute approximate first `D'erivative
	C                              of the solution only.
	C                = `B' or `b'- compute `B'oth approximate solution and
	C                              first derivative.
	C  The coefficents of the polynomial are contained in Y(*), YP(*) and
	C  P(NWANT,*).
	*/
	void        EVALI(double *, double *, double *, double *, unsigned char *, int *, double *, double *);

	/*
	@brief   SUBROUTINE RKMSG(IER,SRNAME,NREC,FLAG)
	Purpose:      To process error messages and terminate the program
	C                in the event of a "catastrophic" failure.
	C
	C  Input:        IER, SRNAME, NREC
	C  Output:       FLAG
	C
	C  Common:       Initializes:    none
	C                Reads:          /RKCOM7/ OUTCH
	C                                /RKCOM8/ MSG, UTASK
	C                                /RKCOM9/ REC
	C                Alters:         none
	*/
	void         RKMSG(int *, unsigned char *, int *, int *);

	/*
	@brief  SUBROUTINE RKSIT(ASK,SRNAME,STATE)
	C  Purpose:      To save or enquire about the status of each
	C                subprogram in the suite.
	C
	C  Input:        ASK, SRNAME
	C  Input/output: STATE
	C
	C
	C  Comments:
	C  =========
	C  SRNAME indicates which routine is of interest in the call to RKSIT.
	*/
	void          RKSIT(int *, unsigned char *, int *);

	/*
	@brief    SUBROUTINE TRUERR(F,NEQ,Y,TOL,WEIGHT,ZY,ZYP,ZERROR,ZYNEW,ZERRES,
                      ZSTAGE,IER)
					  Purpose:      Compute a running RMS measure of the true (global) error
					  C                for a general Runge-Kutta pair.
					  C
					  C
					  C  Input:        NEQ, Y(*), TOL, WEIGHT(*),
					  C  Input/output: ZY(*), ZYP(*), ZERROR(*)
					  C  Workspace:    ZYNEW(*), ZERRES(*), ZSTAGE(NEQ,*)
					  C  Output:       IER
					  C  External:     F
					  C
					  C  Common:       Initializes:    none
					  C                Reads:          /RKCOM2/ T, HOLD
					  C                                /RKCOM5/ TOOSML, ORDER, NSEC
					  C                                /RKCOM7/ TINY
					  C                Alters:         /RKCOM6/ MAXERR, LOCMAX, GNFCN

	*/
	void     TRUERR(void(*)(double *, double *, double *), int *, double *, double *, double *, double *, double *, double *, double *, double *, double *, int *);

	/*
	@brief SUBROUTINE STEP(F,NEQ,TNOW,Y,YP,STAGES,TOL,HTRY,WEIGHT,YNEW,
                    ERREST,ERR,MAIN,HMIN,THRES,PHASE2)
					Purpose:      To compute a step of an explicit Runge-Kutta
					C                method and estimate the local error of the step.
					C
					C  Input:        NEQ, TNOW, Y(*), YP(*), TOL, MAIN, HMIN, THRES(*)
					C  Input/output: HTRY, PHASE2, LAST, WEIGHT(*)
					C  Output:       STAGES(NEQ,*), YNEW(*), ERREST(*), ERR
					C
					C  Common:       Initializes:    none
					C                Reads:          /RKCOM1/ TND
					C                                /RKCOM2/ LAST
					C                                /RKCOM4/ A, B, C, BHAT, PTR, NSTAGE, METHD
					C                                /RKCOM5/ FSAL
					C                Alters:         /RKCOM2/ NFCN, LAST
					C                                /RKCOM6/ GNFCN
	*/
	void     STEP(void(*)(double *, double *, double *), int *, double *, double *, double *, double *, double *,
		double *, double *, double *, double *, double *, int *, double *, double *, int *);

	/*
	@brief  SUBROUTINE STEPA(TNOW,Y,YP,TSTG,YSTG,YPSTG,HTRY,WEIGHT,CUTBAK)
	Purpose:      To calculate an "on-scale" step size for phase 2 of
	C                the initial step size computation.
	C
	C  Input:        TNOW, Y(*), YP(*), TSTG, YSTG(*), YPSTG(*)
	C  Input/output: HTRY, WEIGHT
	C  Output:       CUTBAK
	C
	C  Common:       Initializes:    none
	C                Reads:          /RKCOM1/ TND, NEQ
	C                                /RKCOM5/ STBRAD, RS1, RS4
	C                                /RKCOM7/ RNDOFF
	C                Alters:         none
	*/
	void     STEPA(double *, double *, double *, double *, double *, double *, double *, double *, int *);

	/*
	@brief  SUBROUTINE STEPB(NEQ,Y,YP,H,YNEW,STAGES,THRES,ERR,MAIN,WEIGHT)
	Purpose:      To compute an error estimate for METHD = 2 prior
	C                to completing the step.
	C
	C  Input:        NEQ, Y(*), YP(*), H, STAGES(NEQ,*), THRES(*), MAIN,
	C                WEIGHT(*)
	C  Output:       ERR
	C
	C  Common:       Initializes:    none
	C                Reads:          /RKCOM4/ E, PTR
	C                Alters:         none
	*/
	void      STEPB(int *, double *, double *, double *, double *, double *, double *, double *, int *, double *);

	/*
	@brief   SUBROUTINE STIFF(F,HAVG,JFLSTP,TOOMCH,MAXFCN,WORK,IER,NREC)
	Purpose:      Diagnose stiffness.  This depends on two things: whether
	C                the step size is being restricted on grounds of stability
	C                and whether the integration to TND can be completed in no
	C                more than MAXFCN function evaluations.
	C
	C  Input:        HAVG, TOOMCH, MAXFCN, WORK(*)
	C  Input/output: JFLSTP
	C  Output:       IER, NREC
	C  Workspace:    WORK(*)
	C  External:     F
	C
	C  Common:       Initializes:    /RKCOM9/ REC
	C                Reads:          /RKCOM1/ TND, NEQN
	C                                /RKCOM2/ T, H, NFCN, SVNFCN, OKSTP
	C                                /RKCOM3/ PRY, PRYP, PRTHRS, PRWT, PRSCR,
	C                                         PRSTGS, PRYOLD
	C                                /RKCOM5/ COST
	C                Alters:         /RKCOM2/ NFCN
	C                                /RKCOM9/ REC
	*/
	void    STIFF(void(*)(double *, double *, double *), double *, int *, int *, int *, double *, int *, int *);

	/*
	@brief  SUBROUTINE STIFFA(F,X,Y,HNOW,HAVG,XEND,MAXFCN,WT,FXY,V0,UNSURE,
     &                  STIF,V1,V2,V3,VTEMP)
	 C  External:     F
	 C  Input:        X, Y(*), HNOW, HAVG, XEND, MAXFCN, WT(*), FXY(*)
	 C  Input/Output  V0(*)
	 C  Output:       UNSURE, STIF
	 C  Workspace:    V1(*), V2(*), V3(*), VTEMP(*)
	 C
	 C  Common:       Initializes:    none
	 C                Reads:          /RKCOM1/ TND, NEQN
	 C                                /RKCOM5/ COST, STBRAD, TANANG
	 C                                /RKCOM7/ SQRRMC, CUBRMC
	 C                Alters:         none
	*/
	void    STIFFA(void(*)(double *, double *, double *), double *, double *, double *, double *, double *, int *,
		double *, double *, double *, int *, int *, double *, double *, double *, double *);

	/*
	@brief SUBROUTINE STIFFB(V1V1,V0V1,V0V0,ROLD,RHO,ROOT1,ROOT2,ROOTRE)
	Input:        V1V1, V0V1, V0V0
	C  Input/output: ROLD
	C  Output:       RHO, ROOT1(*),ROOT2(*),ROOTRE
	*/
	void    STIFFB(double *, double *, double *, double *, double *, double *, double *, int *);

	/*
	@brief  SUBROUTINE STIFFC(ALPHA,BETA,R1,R2)
	Input:  ALPHA, BETA
	C  Output: R1(*), R2(*)
	C
	C  This subroutine computes the two complex roots R1 and R2 of
	C  the quadratic equation X**2 + ALPHA*X + BETA = 0.  The magnitude
	C  of R1 is greater than or equal to the magnitude of R2. R1 and R2 are
	C  returned as vectors of two components with the first being the real
	C  part of the complex number and the second being the imaginary part.
	*/
	void    STIFFC(double *, double *, double *, double *);

	/*
	@brief   SUBROUTINE STIFFD(V,HAVG,X,Y,F,FXY,WT,SCALE,VDOTV,Z,ZDOTZ,VTEMP)
	External:     F
	C  Input:        V(*), HAVG, X, Y(*), FXY(*), WT(*), SCALE, VDOTV,
	C  Output:       Z(*), ZDOTZ
	C  Workspace:    VTEMP(*)
	C
	C  For an input vector V(*) of length NEQ, this subroutine computes a vector
	C  Z(*) that approximates the product HAVG*J*V where HAVG is an input scalar
	C  and J is the Jacobian matrix of a function F evaluated at the input
	C  arguments (X,Y(*)).  This function is defined by a subroutine of the form
	C  F(T,U,F) that when given T and U(*), returns the value of the function in
	C  F(*).  The input vector FXY(*) is defined by F(X,Y,FXY).  Scaling is a
	C  delicate matter.  A weighted Euclidean norm is used with the (positive)
	C  weights provided in WT(*).  The input scalar SCALE is the square root of
	C  the unit roundoff times the norm of Y(*).  The square of the norm of the
	C  input vector V(*) is input as VDOTV.  The routine outputs the square of
	C  the norm of the output vector Z(*) as ZDOTZ.  The subroutine calls the
	C  DOUBLE PRECISION FUNCTION DOTPRD(U,V,WT,NEQ) to compute the dot (inner)
	C  product.  The vector VTEMP(*) is used for working storage.
	*/
	void     STIFFD(double *, double *, double *, double *, void(*)(double *, double *, double *), double *,
		double *, double *, double *, double *, double *, double *);

	/*
	@brief  DOUBLE PRECISION FUNCTION DOTPRD(U,V,WT,NEQ)
	Purpose:   To compute a weighted Euclidean dot (inner) product of
	C             two vectors.
	C
	C  Input:     U(*), V(*), WT(*), NEQ
	C  Output:    the result DOTPRD is returned via the subprogram name
	C
	C  Comments:
	C  =========
	C  The vectors U(*), V(*), and WT(*) are of length NEQ. The components
	C  of WT(*) are weights that must be non-zero.
	*/
	double   DOTPRD(double *, double *, double *, int *);

	/*
	@brief   SUBROUTINE SOFTFL(ASK,ON)
	Purpose:      To prevent a program STOP after a "catastrophic"
	C                failure when using a routine from RKSUITE.
	C
	C  Input:        ASK (LOGICAL)
	C  Input/output: ON (LOGICAL)
	*/
	void     SOFTFL(int *, int *);

	/*
	@brief    SUBROUTINE CHKFL(ASK,ERROR)
	Purpose:      Enquiry routine used in conjunction with SOFTFL.
	C                Reports whether a "catastrophic" error was detected.
	C
	C  Input:        ASK
	C  Input/output: ERROR
	*/
	void    CHKFL(int *, int *);
}
#endif
#endif /*_RUNGE_KUTTA_F77_Declarations_H_*/