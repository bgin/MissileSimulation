
/*************************************************************************
*************             GTD7  IMPLEMENTATION         *******************
*************************************************************************/
template<typename T, class INPUT, class FLAGS, class OUTPUT, class SPLINE,
class SPLINT, class SPLINI> auto 
atmosphere::GTD7<T, INPUT, FLAGS, OUTPUT, SPLINE,SPLINT,SPLINI>::tselec(_In_ FLAGS &flags)->void {

	int i;
	constexpr int flags_size{ 24 };
	for (i{ 0 }; i != flags_size; ++i) {
		if (i != 9) {
			if (flags.switches[i] == 1)
				flags.sw[i] = 1.0;
			else
				flags.sw[i] = 0.0;
			if (flags.switches[i] > 0)
				flags.swc[i] = 1.0;
			else
				flags.swc[i] = 0.0
		}
		else {
			flags.sw[i] = static_cast<T>(flags.switches[i]);
			flags.swc[i] = static_cast<T>(flags.switches[i]);
		}
	}
}



template<typename T, class INPUT, class FLAGS, class OUTPUT, class SPLINE, class SPLINT, class SPLINI> 
std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
atmosphere::GTD7<T, INPUT, FLAGS, OUTPUT, SPLINE, SPLINT, SPLINI>::fgts7(_In_ INPUT& input, _In_ const FLAGS& flags, _In_ OUTPUT& output) {
	T za, ddum, z;
	int i, j;
    T zn1[5] = { (120.0), (110.0), (100.0), (90.0), (72.5) };
	constexpr T alpha[9] = { (-0.38), (0.0), (0.0), (0.0), (0.17), (0.0), (-0.38), (0.0), (0.0) };
	constexpr T altl[8] = { (200.0), (300.0), (160.0), (250.0), (240.0), (450.0), (320.0), (450.0) };
	constexpr T dgtr{ 1.74533E-2 };
	constexpr dr{ 1.72142E-2 };
	
	T tinf, g0, tlb, s, xmd, tz, zhf, xmm, r1,dd,hc216,hcc232;
	constexpr int mn1{ 5 };
	T db01, db04, db14, db16, db28, db32, db40;
	T zh28, zh04, zh16, zh32, zh40, zh01, zh14;
	T zhm28, zhm04, zhm16, zhm3, zhm40, zhm01;
	T b28, b04, b16, b32, b40, b01, b14;
	T g28, g4, g16, g32, g40, g1, g14;
	T zc04, zc16, zc32, zc40, zc01, zc14;
	T hc04, hc16, hc32, hc40, hc01, hc14;
	T hcc16, hcc32, hcc01, hcc14;
	T zcc16, zcc32, zcc01, zcc14;
	T rc16, rc32, rc01, rc14;
	T g16h, db16h, tho, zsht, zmho, zsho;
	atmosphere::Turbo<T> turbo;
	atmosphere::LowBoundary<T> lobound;
	atmosphere::Temperature<T> temp;
	atmosphere::SPARAM<T> sparam;
	atmosphere::Density<T> dens;
	atmosphere::GLOBE7<T, INPUT, OUTPUT> glb;
	atmosphere::GLOBE7S<T, INPUT, FLAGS> glbs;
	atmosphere::DENSM<T, SPLINE, SPLINT, SPLINI> densm;
	atmosphere::DNET<T> dnt;
	atmosphere::CCOR<T> ccr;
	atmosphere::CCOR2<T> ccr2;
	atmosphere::SCALH<T> sclh;
	za = turbo.pdl[1][15];
	const T sw18(flags.sw[18]);
	const T one_sw18(1.0 - sw18);
	zn1[0] = za;
	for (j{ 0 }; j < 9; ++j) output.d[i] = 0.0;
	/* TINF VARIATIONS NOT IMPORTANT BELOW ZA OR ZN1(1) */
	if (input.alt > zn1[0])
		tinf = lobound.ptm[0] * temp.pt[0] * (1.0 + flags.sw[16] * glb.fglobe7(temp.pt, input, flags));
	else
		tinf = lobound.ptm[0] * temp.pt[0];
	output.t[0] = tinf;
	/*  GRADIENT VARIATIONS NOT IMPORTANT BELOW ZN1(5) */
	if (input.alt > zn1[4])
		g0 = lobound.ptm[3] * sparam.ps[0] * (1.0 + flags.sw[19] * glb.fglobe7(sparam.ps, input, flags));
	else
		g0 = lobound.ptm[3] * sparam.ps[0];
	tlb = lobound.ptm[1] * (1.0 + flags.sw[17] * glb.fglobe7(dens.pd[3], input, flags)) * dens.pd[3][0];
	s = g0 / (tinf - tlb);
	/*      Lower thermosphere temp variations not significant for
	*       density above 300 km */
	if (input.alt < 300.0) {
		amg::meso_tn1[1] = lobound.ptm[6] * lobound.ptl[0][0] / (one_sw18 * glbs.fglobe7s(lobound.ptl[0], input, flags));
		amg::meso_tn1[2] = lobound.ptm[2] * lobound.ptl[1][0] / (one_sw18 * glbs.fglobe7s(lobound.ptl[1], input, flags));
		amg::meso_tn1[3] = lobound.ptm[7] * lobound.ptl[2][0] / (one_sw18 * glbs.fglobe7s(lobound.ptl[2], input, flags));
		amg::meso_tn1[4] = lobound.ptm[4] * lobound.ptl[3][0] / (one_sw18 * flags.sw[20] * glbs.fglobe7s(lobound.ptl[3], input, flags));
		amg::meso_tgn1[1] = lobound.ptm[8] * lobound.pma[8][0] * (1.0 + flags.sw[18] * flags.sw[20] * glbs.fglobe7s(lobound.pma[8], input, flags)) * amg::meso_tn1[4] /
			(lobound.ptm[4] * lobound.ptl[3][0] * lobound.ptm[4] * lobound.ptl[3][0]);
	}
	else {
		amg::meso_tn1[1] = lobound.ptm[6] * lobound.ptl[0][0];
		amg::meso_tn1[2] = lobound.ptm[2] * lobound.ptl[1][0];
		amg::meso_tn1[3] = lobound.ptm[7] * lobound.ptl[2][0];
		amg::meso_tn1[4] = lobound.ptm[4] * lobound.ptl[3][0];
		amg::meso_tgn1[1] = lobound.ptm[8] * lobound.pma[8][0] * amg::meso_tn1[4] * amg::meso_tn1[4] /
			(lobound.ptm[4] * lobound.ptl[3][0] * lobound.ptm[4] * lobound.ptl[3][0]);
	}
	/* N2 variation factor at Zlb */
	g28 = flags.sw[21] * glb.fglobe7(dens.pd[2], input, flags);
	/* VARIATION OF TURBOPAUSE HEIGHT */
	zhf = turbo.pdl[1][24] * (1.0 + flags.sw[5] * turbo.pdl[0][24] * sin(dgtr*input.g_lat)*cos(dr*(input.doy - temp.pt[13])));
	output.t[0] = tinf;
	xmm = lobound.pdm[2][4];
	z = input.alt;
	/**** N2 DENSITY ****/

	/* Diffusive density at Zlb */
	db28 = lobound.pdm[2][0] * exp(g28)*dens.pd[2][0];
	/* Diffusive density at Alt */
	output.d[2] = densm.densuprof(z, db28, tinf, tlb, 28.0, alpha[2], &output.t[1], lobound.ptm[5], s, mn1, zn1, amg::meso_tn1,
		amg::meso_tgn1);
	dd = output.d[2];
	/* Turbopause */
	zh28 = lobound.pdm[2][2] * zhf;
	zhm28 = lobound.pdm[2][3] * turbo.pdl[1][5];
	xmd = 28.0 - xmm;
	/* Mixed density at Zlb */
	b28 = densm.densuprof(zh28, db28, tinf, tlb, xmd, (alpha[2] - 1.0), &tz, lobound.ptm[5], s, mn1, zn1,
		amg::meso_tn1, amg::meso_tgn1);
	if (((std::fabs(flags.sw[15])) > 0.0) && (z <= alt[2])) {
		/*  Mixed density at Alt */
		dm28 = densm.densuprof(z, b28, tinf, tlb, xmm, alpha[2], &tz, lobound.ptm[5], s, mn1, zn1,
			amg::meso_tn1, amg::meso_tgn1);
		/*  Net density at Alt */
		output.d[2] = dnt.operator()(output.d[2], dm28, zhm28, xmm, 28.0);
	}

	/**** HE DENSITY ****/

	/*   Density variation factor at Zlb */
	g4 = flags.sw[21] * glb.fglobe7(dens.pd[0], input, flags);
	/*  Diffusive density at Zlb */
	db04 = lobound.pdm[0][0] * exp(g4) * dens.pd[0][0];
	/*  Diffusive density at Alt */
	output.d[0] = densm.densuprof(z, db04, tinf, tlb, 4.0, alpha[0], &output.t[1], lobound.ptm[5],
		mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[0];
	if (((std::fabs(flags.sw[15])) > 0.0) && (z < altl[0])) {
		/*  Turbopause */
		zh04 = lobound.pdm[0][2];
		/*  Mixed density at Zlb */
		b04 = densm.densuprof(zh04, db04, tinf, tlb, 4.0, -xmm, (alpha[0] - 1.0), &output.t[1], lobound.ptm[5],
			s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		/*  Mixed density at Alt */
		dm04 = densm.densuprof(z, b04, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5], s, mn1, zn1,
			amg::meso_tn1, amg::meso_tgn1);
		zhm04 = zhm28;
		/*  Net density at Alt */
		output.d[0] = dnt.operator()(output.d[0], dm04, zhm04, xmm, 4.0);
		/*  Correction to specified mixing ratio at ground */
		rl = log(b28*lobound.pdm[0][1] / b04);
		zc04 = lobound.pdm[0][4] * turbo.pdl[1][0];
		hc04 = lobound.pdm[0][5] * turbo.pdl[1][1];
		/*  Net density corrected at Alt */
		output.d[0] = output.d[0] * ccr.operator()(z, rl, hc04, zc04);
	}
	/**** O DENSITY ****/

	/*  Density variation factor at Zlb */
	g16 = flags.sw[21] * glb.fglobe7(dens.pd[1], input, flags);
	/*  Diffusive density at Zlb */
	db16 = lobound.pdm[1][0] * exp(g16) * dens.pd[1][0];
	/*   Diffusive density at Alt */
	output.d[1] = densm.densuprof(z, db16, tinf, tlb, 16.0, alpha[1], &output.t[1],
		lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[1];
	if (((std::fabs(flags.sw[15])) > 0.0) && (z <= altl[1])){
		/*   Turbopause */
		zh16 = lobound.pdm[1][2];
		/*  Mixed density at Zlb */
		b16 = densm.densuprof(zh16, db16, tinf, tlb, 16.0 - xmm, (alpha[1] - 1.0), &output.t[1],
			lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		/*  Mixed density at Alt */
		dm16 = densm.densuprof(z, b16, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5],
			s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		zhm16 = zhm28;
		/*  Net density at Alt */
		output.d[1] = dnt.operator()(output.d[1], dm16, zhm16, xmm, 16.0);
		rl = lobound.pdm[1][1] * turbo.pdl[1][16] * (1.0 + flags.sw[1] * turbo.pdl[0][23] * (input.F107A - 150.0));
		hc16 = lobound.pdm[1][5] * turbo.pdl[1][3];
		zc16 = lobound.pdm[1][4] * turbo.pdl[1][2];
		hc216 = lobound.pdm[1][5] * turbo.pdl[1][4];
		output.d[1] = output.d[1] * ccr2.operator()(z, rl, hc16, zc16, hc216);
		/*   Chemistry correction */
		hcc16 = lobound.pdm[1][7] * turbo.pdl[1][13];
		zcc16 = lobound.pdm[1][6] * turbo.pdl[1][12];
		rc16 = lobound.pdm[1][3] * turbo.pdl[1][14];
		/*  Net density corrected at Alt */
		output.d[1] = output.d[1] * ccr.operator()(z, rc16, hcc16, zcc16);
	}
	/**** O2 DENSITY ****/
	/*   Density variation factor at Zlb */
	g32 = flags.sw[21] * glb.fglobe7(dens.pd[4], input, flags);
	/*  Diffusive density at Zlb */
	db32 = lobound.pdm[3][0] * exp(g32) * dens.pd[4][0];
	/*   Diffusive density at Alt */
	output.d[3] = densm.densuprof(z, db32, tinf, tlb, 32.0, alpha[3], &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[3];
	if ((std::fabs(flags.sw[15])) > 0.0) {
		if (z <= altl[3]){
			/*   Turbopause */
			zh32 = lobound.pdm[3][2];
			/*  Mixed density at Zlb */
			b32 = densm.densuprof(zh32, db32, tinf, tlb, 32.0 - xmm, alpha[3] - 1.0, &output.t[1],
				lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
			/*  Mixed density at Alt */
			dm32 = densm.densuprof(z, b32, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5],
				s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
			zhm32 = zhm28;
			/*  Net density at Alt */
			output.d[3] = dnt.operator()(output.d[3], dm32, zhm32, xmm, 32.0);
			/*   Correction to specified mixing ratio at ground */
			rl = log(b28*lobound.pdm[3][1] / b32);
			hc32 = lobound.pdm[3][5] * turbo.pdl[1][7];
			zc32 = lobound.pdm[3][4] * turbo.pdl[1][6];
			output.d[3] = output.d[3] * ccr.operator()(z, rl, hc32, zc32);
		}
		/*  Correction for general departure from diffusive equilibrium above Zlb */
		hcc32 = lobound.pdm[3][7] * turbo.pdl[1][22];
		hcc232 = lobound.pdm[3][7] * turbo.pdl[0][22];
		zcc32 = lobound.pdm[3][6] * turbo.pdl[1][21];
		rc32 = lobound.pdm[3][3] * turbo.pdl[1][23] * (1.0 + flags.sw[1] * turbo.pdl[0][23] * (input.F107A - 150.0));
		/*  Net density corrected at Alt */
		output.d[3] = output.d[3] * ccr2.operator()(z, rc32, hcc32, zcc32, hcc232);
	}
	/**** AR DENSITY ****/

	/*   Density variation factor at Zlb */
	g40 = flags.sw[21] * glb.fglobe7(dens.pd(5), input, flags);
	/*  Diffusive density at Zlb */
	db40 = lobound.pdm[4][0] * exp(g40)  * dens.pd[5][0];
	/*   Diffusive density at Alt */
	output.d[4] = densm.densuprof(z, db40, tinf, tlb, 40.0, alpha[4], &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[4];
	if (((std::fabs(flags.sw[15])) > 0.0) && (z <= altl[4])){
		/*   Turbopause */
		zh40 = lobound.pdm[4][2];
		/*  Mixed density at Zlb */
		b40 = densm.densuprof(zh40, db40, tinf, tlb, 40.0 - xmm, alpha[4] - 1.0, &output.t[1],
			lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		/*  Mixed density at Alt */
		dm40 = densm.densuprof(z, b40, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5],
			s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		zhm40 = zhm28;
		/*  Net density at Alt */
		output.d[4] = dnt.operator()(output.d[4], dm40, zhm40, xmm, 40.0);
		/*   Correction to specified mixing ratio at ground */
		rl = log(b28*pdm[4][1] / b40);
		hc40 = pdm[4][5] * pdl[1][9];
		zc40 = pdm[4][4] * pdl[1][8];
		/*  Net density corrected at Alt */
		output.d[4] = output.d[4] * ccr.operator()(z, rl, hc40, zc40);
	}
	/**** HYDROGEN DENSITY ****/

	/*   Density variation factor at Zlb */
	g1 = flags.sw[21] * glb.fglobe7(dens.pd[6], input, flags);
	/*  Diffusive density at Zlb */
	db01 = lobound.pdm[5][0] * exp(g1) * dens.pd[6][0];
	/*   Diffusive density at Alt */
	output.d[6] = densm.densuprof(z, db01, tinf, tlb, 1.0, alpha[6], &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[6];
	if (((std::fabs(flags.sw[15])) > 0.0) && (z <= altl[6])){
		/*   Turbopause */
		zh01 = lobound.pdm[5][2];
		/*  Mixed density at Zlb */
		b01 = densm.densuprof(zh01, db01, tinf, tlb, 1.0 - xmm, alpha[6] - 1.0, &output.t[1],
			lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		/*  Mixed density at Alt */
		dm01 = densm.densuprof(z, b01, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5],
			s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		zhm01 = zhm28;
		/*  Net density at Alt */
		output.d[6] = dnt.operator()(output.d[6], dm01, zhm01, xmm, 1.0);
		/*   Correction to specified mixing ratio at ground */
		rl = log(b28*lobound.pdm[5][1] * sqrt(turbo.pdl[1][17] * turbo.pdl[1][17]) / b01);
		hc01 = lobound.pdm[5][5] * turbo.pdl[1][11];
		zc01 = lobound.pdm[5][4] * turbo.pdl[1][10];
		output.d[6] = output.d[6] * ccr.operator()(z, rl, hc01, zc01);
		/*   Chemistry correction */
		hcc01 = lobound.pdm[5][7] * turbo.pdl[1][19];
		zcc01 = lobound.pdm[5][6] * turbo.pdl[1][18];
		rc01 = lobound.pdm[5][3] * turbo.pdl[1][20];
		/*  Net density corrected at Alt */
		output.d[6] = output.d[6] * ccr.operator()(z, rl, hcc01, zcc01);
	}
	/**** ATOMIC NITROGEN DENSITY ****/

	/*   Density variation factor at Zlb */
	g14 = flags.sw[21] * glb.fglobe7(dens.pd[7], input, flags);
	/*  Diffusive density at Zlb */
	db14 = lobound.pdm[6][0] * exp(g14) * dens.pd[7][0];
	/*   Diffusive density at Alt */
	output.d[7] = densm.densuprof(z, db14, tinf, tlb, 14.0, alpha[7], &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	dd = output.d[7];
	if (((std::fabs(flags.sw[15])) > 0.0) && (z <= altl[6])){
		/*   Turbopause */
		zh14 = lobound.pdm[6][2];
		/*  Mixed density at Zlb */
		b14 = densm.densuprof(zh14, db14, tinf, tlb, 14.0 - xmm, alpha[7] - 1.0, &output.t[1],
			lobound.ptm[5], s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		/*  Mixed density at Alt */
		dm14 = densm.densuprof(z, b14, tinf, tlb, xmm, 0.0, &output.t[1], lobound.ptm[5],
			s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
		zhm14 = zhm28;
		/*  Net density at Alt */
		output.d[7] = dnt.operator()(output.d[7], dm14, zhm14, xmm, 14.0);
		/*   Correction to specified mixing ratio at ground */
		rl = log(b28*lobound.pdm[6][1] * sqrt(turbo.pdl[0][2] * turbo.pdl[0][2]) / b14);
		hc14 = lobound.pdm[6][5] * turbo.pdl[0][1];
		zc14 = lobound.pdm[6][4] * turbo.pdl[0][0];
		output.d[7] = output.d[7] * ccr.operator()(z, rl, hc14, zc14);
		/*   Chemistry correction */
		hcc14 = lobound.pdm[6][7] * turbo.pdl[0][4];
		zcc14 = lobound.pdm[6][6] * turbo.pdl[0][3];
		rc14 = lobound.pdm[6][3] * turbo.pdl[0][5];
		/*  Net density corrected at Alt */
		output.d[7] = output.d[7] * ccr.operator()(z, rc14, hcc14, zcc14);
	}
	/**** Anomalous OXYGEN DENSITY ****/
	g16h = flags.sw[21] * glb.fglobe7(dens.pd[8], input, flags);
	db16h = lobound.pdm[7][0] * exp(g16h) * dens.pd[8][0];
	tho = lobound.pdm[7][9] * turbo.pdl[0][6];
	dd = densm.densuprof(z, db16h, tho, tho, 16.0, alpha[8], &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	zsht = lobound.pdm[7][5];
	zmho = lobound.pdm[7][4];
	zsho = sclh.operator()(zmho, 16.0, tho);
	output.d[8] = dd * exp(-zsht / zsho*(exp(-(z - zmho) / zsht) - 1.0));
	/* total mass density */
	output.d[5] = 1.66E-24*(4.0*output.d[0] + 16.0*output.d[1] + 28.0*output.d[2] + 32.0*output.d[3] + 40.0*output.d[4] + output.d[6] + 14.0*output.d[7]);
	/* temperature */
	z = sqrt(input.alt * input.alt);
	ddum = densm.densuprof(z, 1.0, tinf, tlb, 0.0, 0.0, &output.t[1], lobound.ptm[5],
		s, mn1, zn1, amg::meso_tn1, amg::meso_tgn1);
	if ((std::fabs(flags.sw[0])) > 0.0) {
		for (i{ 0 }; i != 9; ++i)
			output.d[i] = output.d[i] * 1.0E+6;
		output.d[5] = output.d[5] * 1.0E-3;
	}
		
}

template<typename T, class INPUT, class FLAGS, class OUTPUT, class SPLINE, class SPLINT, class SPLINI> std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
atmosphere::GTD7<T, INPUT, FLAGS, OUTPUT, SPLINE,SPLINT,SPLINI>::fgtd7(_In_ INPUT& input, _In_ const FLAGS& flags, _Out_ OUTPUT& output) {
	T xlat, xmm;
	int mn3{ 5 };
	int mn2{ 4 };
	constexpr T zn3[5] = { (32.5), (20.0), (15.0), (10.0), (0.0) };
	constexpr T zn2[4] = { (72.5), (55.0), (45.0), (32.5) };
	T altt, tmp, dm28m, tz, dmc, dmr, dz28;
	const T one_sw20{ 1.0 - flags.sw[20] };
	const T one_sw22{ 1.0 - flags.sw[22] };
	constexpr T zmix(62.5);
	atmosphere::NRLMSISE_OUTPUT<T> sout;
	atmosphere::GLATF<T> glatf;
	atmosphere::LowBoundary<T> lobound;
	atmosphere::AtmosAverages<T> atavrg;
	atmosphere::GLOBE7S<T, INPUT, FLAGS> glbs;
	atmosphere::DENSM<T, SPLINE, SPLINT, SPLINI> densm;
	tselec(flags);
	/* Latitude variation of gravity (none for sw[2]=0) */
	xlat = input.g_lat;
	if (flags.sw2[2] == 0.0)
		xlat = 45.0;
	glatf.operator()(xlat, &amg::gsurf, &amg::re);
	xmm = lobound.pdm[2][4];
	/* THERMOSPHERE / MESOSPHERE (above zn2[0]) */
	if (input.alt > zn2[0])
		altt = input.alt;
	else
		altt = zn2[0];
	tmp = input.alt;
	input.alt = altt;
	fgts7(input, flags, sout);
	altt = input.alt;
	input.alt = tmp;
	if ((std::fabs(flags.sw[0])) > 0.0)
		dm28m = amg::dm28 * 1.0E+6;
	else
		dm28m = amg::dm28;
	output.t[0] = sout.t[0];
	output.t[1] = sout.t[1];
	if (input.alt >= zn2[0]){
		for (int i{ 0 }; i != 9; ++i)
			output.d[i] = sout.d[i];
		return;
	}
	/*LOWER MESOSPHERE / UPPER STRATOSPHERE(between zn3[0] and zn2[0])
		*         Temperature at nodes and gradients at end nodes
		*         Inverse temperature a linear function of spherical harmonics
		*/
	amg::meso_tgn2[0] = amg::meso_tgn1[1];
	amg::meso_tn2[0] = amg::meso_tn1[4];
	amg::meso_tn2[1] = lobound.pma[0][0] * atavrg.pavgm[0] / (one_sw20 * glbs.fglobe7s(lobound.pma[0], input, flags));
	amg::meso_tn2[2] = lobound.pma[1][0] * atavrg.pavgm[1] / (one_sw20 * glbs.fglobe7s(lobound.pma[1], input, flags));
	amg::meso_tn2[3] = lobound.pma[2][0] * atavrg.pavgm[2] / (one_sw20 * flags->sw[22] * glbs.fglobe7s(lobound.pma[2], input, flags));
	amg::meso_tgn2[1] = atavrg.pavgm[8] * lobound.pma[9][10] * (1.0 + flags.sw[20] * flags.sw[22] * glbs.fglobe7s(lobound.pma[9], input, flags)) *
		amg::meso_tn2[3] / (lobound.pma[2][0] * atavrg[2] * lobound.pma[2][0] * atavrg[2]);
	amg::meso_tn3[0] = amg::meso_tn2[3];
	if (input.alt < zn3[0]) {
		/*       LOWER STRATOSPHERE AND TROPOSPHERE (below zn3[0])
		*         Temperature at nodes and gradients at end nodes
		*         Inverse temperature a linear function of spherical harmonics
		*/
		amg::meso_tgn3[0] = amg::meso_tgn2[1];
		amg::meso_tn3[1] = lobound.pma[3][0] * atavrg.pavgm[3] / (one_sw22 * glbs.fglobe7s(lobound.pma[3], input, flags));
		amg::meso_tn3[2] = lobound.pma[4][0] * atavrg.pavgm[4] / (one_sw22 * glbs.fglobe7s(lobound.pma[4], input, flags));
		amg::meso_tn3[3] = lobound.pma[5][0] * atavrg.pavgm[5] / (one_sw22 * glbs.fglobe7s(lobound.pma[5], input, flags));
		amg::meso_tn3[4] = lobound.pma[6][0] * atavrg.pavgm[6] / (one_sw22 * glbs.fglobe7s(lobound.pma[6], input, flags));
		amg::meso_tgn3[1] = lobound.pma[7][0] * atavrg.pavgm[7] * (1.0 + flags.sw[22] * glbs.fglobe7s(lobound.pma[7], input, flags)) * amg::meso_tn3[4] * amg::meso_tn3[4] / 
			(lobound.pma[6][0] * atavrg.pavgm[6] * lobound.pma[6][0] * atavrg.pavgm[6]);
	}
	/* LINEAR TRANSITION TO FULL MIXING BELOW zn2[0] */
	dmc = 0.0;
	if (input.alt > zmix)
		dmc = 1.0 - (zn2[0] - input.alt) / (zn2[0] - zmix);
	dz28 = sout.d[2];
	/**** N2 density ****/
	dmr = sout.d[2] / dm28m - 1.0;
	output.d[2] = densm.densprof(input.alt, dm28m, xmm, &tz, mn3, zn3, amg::meso_tn3,
		amg::meso_tgn3, mn2, zn2, amg::meso_tn2, amg::meso_tgn2);
	output.d[2] = output.d[2] * (1.0 + dmr * dmc);
	/**** HE density ****/
	dmr = sout.d[0] / (dz28 * lobound.pdm[0][1]) - 1.0;
	output.d[0] = output.d[2] * lobound.pdm[0][1] * (1.0 + dmr*dmc);
	/**** O density ****/
	output.d[1] = 0.0;
	output.d[8] = 0.0;
	/**** O2 density ****/
	dmr = sout.d[3] / (dz28 * lobound.pdm[3][1]) - 1.0;
	output.d[3] = output.d[2] * lobound.pdm[3][1] * (1.0 + dmr*dmc);
	/**** AR density ***/
	dmr = sout.d[4] / (dz28 * lobound.pdm[4][1]) - 1.0;
	output.d[4] = output.d[2] * lobound.pdm[4][1] * (1.0 + dmr*dmc);
	/**** Hydrogen density ****/
	output.d[6] = 0.0;
	/**** Atomic nitrogen density ****/
	output.d[7] = 0.0;
	/**** Total mass density */
	output.d[5] = 1.66E-24 * (4.0 * output.d[0] + 16.0 * output.d[1] + 28.0 * output.d[2] + 32.0 * 
		output.d[3] + 40.0 * output.d[4] + output.d[6] + 14.0 * output.d[7]);
	if ((std::fabs(flags.sw[0])) > 0.0)
		output.d[5] = output.d[5] * 1.0E-3;
	/**** temperature at altitude ****/
	amg::dd = densm.densprof(input.alt, 1.0, 0.0, &tz, mn3, zn3, amg::meso_tn3,
		amg::meso_tgn3, mn2, zn2, amg::meso_tn2, amg::meso_tgn2);
  }

  template<typename T, class INPUT, class FLAGS, class OUTPUT, class SPLINE, class SPLINT, class SPLINI>
  std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value,void>::type
	  atmosphere::GTD7<T, INPUT, FLAGS, OUTPUT, SPLINE, SPLINT, SPLINI>::fgtd7d(_In_ INPUT &input,
	  _In_ const FLAGS &flags, _Out_ OUTPUT &output) {
		  fgtd7(input, flags, output);
		  output.d[5] = 1.66E-24 * (4.0 * output.d[0] + 16.0 * output.d[1] + 28.0 * output.d[2] +
			  32.0 * output.d[3] + 40.0 * output.d[4] + output.d[6]);
		  if ((std::fabs(flags.sw[0])) > 0.0)
			  output.d[5] = output.d[5] * 1.0E-3;
	  }

  template<typename T, class INPUT, class FLAGS, class OUTPUT, class SPLINE, class SPLINT, class SPLINI>
  std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value,void>::type
	  atmosphere::GTD7<T, INPUT, FLAGS, OUTPUT, SPLINE, SPLINT, SPLINI>::fghp7(_In_ INPUT& input,
	  _In_ const FLAGS& flags, _Out_ OUTPUT &output, _In_ T press) {
		  constexpr T bm(1.3806E-19);
		  constexpr T rgas(831.4);
		  constexpr T test(0.00043);
		  constexpr int converg_test{ 12 };
		  T  p, zi, z, cl, c12, ca, cd, xn, xm, diff, g, sh;
		  T pl{ log10(press) };
		  if (pl >= -5.0) {
			  if (pl > 2.5)
				  zi = 18.06 * (3.0 - pl);
			  else if ((pl > 0.075) && (pl <= 2.5))
				  zi = 14.98 * (3.08 - pl);
			  else if ((pl > -1.0) && (pl <= 0.075))
				  zi = 17.80 * (2.72 - pl);
			  else if ((pl > -2.0) && (pl <= -1.0))
				  zi = 14.28 * (3.64 - pl);
			  else if ((pl > -4.0) && (pl <= -2.0))
				  zi = 12.72 * (4.32 - pl);
			  else
				  zi = 25.3 * (0.11 - pl);
			  cl = input.g_lat * 0.0111111111111111111111111;
			  cl2 = cl*cl;
			  if (input.doy < 182)
				  cd = (1.0 - static_cast<T>(input.doy)) * 0.0109589041095890410958904109589;
			  else
				  cd = static_cast<T>(input.doy) * 0.01133144475920679886685552407932;
			  ca = 0.0;
			  if ((pl > -1.11) && (pl <= -0.23))
				  ca = 1.0;
			  if (pl > -0.23)
				  ca = (2.79 - pl) * 0.33112582781456953642384105960265;
			  if ((pl <= -1.11) && (pl > -3.0))
				  ca = (-2.93 - pl) * -0.54945054945054945054945054945055;
			  z = zi - 4.87 * cl * cd * ca - 1.64 * cl2 * ca + 0.31 * ca * cl;
		  }
		  else
			  z = 22.0 * (pl + 4.0 * pl + 4.0) + 110.0;
		  /* iteration do-while loop*/
		  int nIters{ 0 };
		  do{
			  ++nIters;
			  input.alt = z;
			  fgtd7(input, flags, output);
			  z = input.alt;
			  xn = output.d[0] + output.d[1] + output.d[2] + output.d[3] +
				  output.d[4] + output.d[5] + output.d[6] + output.d[7];
			  p = bm * xn * output.t[1];
			  if ((std::fabs(flags.sw[0])) > 0.0)
				  p = p * 1.0E-6;
			  diff = pl - log10(p);
			  if ((sqrt(diff*diff) < test) || (nIters == converg_test)){
				  std::cerr << std::showpoint << std::scientific <<
					  "ERROR: fghp7 failed to converge!!" << "for pressure:" <<
					  press << "of difference:" << diff << std::endl;
				  return;
				 
			  }
			  xm = output.d[5] / xn * 1.66E+24;
			  if ((std::fabs(flags.sw[0])) > 0.0)
				  xm *= 1.0E3;
			  g = amg::gsurf / ((1.0 + z / amg::re) * (1.0 + z / amg::re));
			  sh = rgas * output.t[1] / (xm * g);
			  /* new altitude estimate using scale height */
			  if (nIters < 6)
				  z = z - sh * diff * 2.302;
			  else
				  z = z - sh * diff;
		  } while (true);
	  }

