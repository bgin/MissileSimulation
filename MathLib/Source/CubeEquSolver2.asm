.model flat,c
.const

NegMask    qword   8000000000000000h,0
AbsMask    qword   7FFFFFFFFFFFFFFFh,-1
ConstCoeff_0_0     real8 0.0
ConstCoeff_1_0     real8 1.0 
ConstCoeff_2_0     real8 2.0
ConstCoeff_3_0     real8 3.0
ConstCoeff_9_0     real8 9.0
ConstCoeff_27_0    real8 27.0
ConstCoeff_54_0    real8 54.0
ConstCoeff_Neg_2_0 real8 -2.0
ConstCoeff_2PI     real8  3.1415926535897932
ConstCoeff_N_0_5   real8  -0.5
ConstCoeff_SQRT_3_2 real8 0.8660254037844386
ConstCoeff_0_3     real8  0.3333333333333333


     .code
	 extern acos:proc, cos:proc, pow:proc

	 CubeEquSolver2 proc
	 push ebp
	 mov  ebp, esp
	 sub esp,  56
	 ; Args loading from left to right
	 mov eax, [ebp + 8] ; coeffs
	 mov ecx, [ebp + 12] ; roots
	 mov edx, [ebp + 24] ; result
	 mov esi, [ebp + 28] ; coeffs_type real or complex
	 vmovsd xmm0, real8 ptr [eax] ; a
	 vmovsd xmm1, real8 ptr [eax + 8] ; b
	 vmovsd xmm2, real8 ptr [eax + 16] ; c
	 vmovsd xmm7, real8 ptr [ebp + 16] ; epsilon

	 vandpd xmm6, xmm0, [AbsMask]
	 vcomisd xmm6, xmm7
	 jb ERROR ; x^2 == 0 case of depressed cubic
	 cmp esi , 0
	 jb ERROR
	 cmp esi, 1
	 ja ERROR

	 vmulsd xmm0, xmm0, xmm0 ; a^2
	 vmovsd xmm3, xmm0, xmm0
	 vmulsd xmm1, xmm1, [ConstCoeff_3_0] ; 3b
	 vsubsd xmm0, xmm0, xmm1
	 vdivsd xmm0, xmm0, [ConstCoeff_9_0]
	 vmovsd xmm6, xmm0, xmm0 ; xmm6 = copy Q
	 vmulsd xmm3, xmm3, real8 ptr [eax] ; a^3
	 vmulsd xmm3, xmm3, [ConstCoeff_2_0]
     vmovsd xmm0, real8 ptr [eax]
	 vmulsd xmm0, xmm0, [ConstCoeff_9_0]
	 vmulsd xmm0, xmm0, real8 ptr [eax + 8]
	 vmulsd xmm2, xmm2, [ConstCoeff_27_0]
	 vsubsd xmm3, xmm3, xmm0
	 vaddsd xmm3, xmm3, xmm2
	 vdivsd xmm3, xmm3, [ConstCoeff_54_0]
	 vmovsd xmm5, xmm3, xmm3 ; xmm5 = R
	 ; xmm6 = Q , xmm5 = R
	 vmovsd real8 ptr [ebp - 8], xmm6 ; store Q
	 vmovsd real8 ptr [ebp - 16], xmm5 ; store R
	 cmp esi, 0
	 je Loc1
	 cmp esi, 1
	 je ComplexRoots  

	 Loc1:
	 vmulsd xmm0, xmm5, xmm5 ; R^2
	 vmovsd xmm1, xmm6, xmm6
	 vmulsd xmm1, xmm1, xmm1
	 vmulsd xmm1, xmm1, xmm6 ; Q^3
	 vcomisd xmm0, xmm1
	 ja ComplexRoots

	 ; RealRoots
	 vmovsd xmm5, real8 ptr [eax]
	 vdivsd xmm5, xmm5, [ConstCoeff_3_0] ; a/3
	 vmovsd real8 ptr [ebp - 48], xmm5 ; store a/3
	 vmovsd xmm2, real8 ptr [ebp - 16]
	 vsqrtsd xmm1, xmm1, xmm1
	 vdivsd xmm2, xmm2, xmm1
	 vmovsd real8 ptr [esp], xmm2
	 call acos
	 fstp real8 ptr [ebp - 24] ; store theta
	 vsqrtsd xmm0, xmm0, real8 ptr [ebp - 8]
	 vmulsd  xmm0, xmm0, [ConstCoeff_Neg_2_0]
	 vmovsd  real8 ptr [ebp - 32], xmm0 ; -2*sqrt(Q)
	 vmovsd  xmm1, real8 ptr [ebp - 24]
	 vdivsd  xmm1, xmm1, [ConstCoeff_3_0]
	 vmovsd  real8 ptr [esp], xmm1
	 call cos
	 fstp real8 ptr [ebp - 40] ; cos(theta/3.0)
	 vmovsd  xmm1, real8 ptr [ebp - 40]
	 vsubsd  xmm1 , xmm1, real8 ptr [ebp - 48]
	 vmovsd  xmm0 , real8 ptr [ebp - 32]
	 vmulsd  xmm0 , xmm0 , xmm1
	 mov   ecx, [ebp + 12] ; reload pointer
	 vmovsd real8 ptr [ecx], xmm0 ; xmm0 = root x1
	 vmovsd xmm0, real8 ptr [ebp - 24]
	 vaddsd xmm0, xmm0, [ConstCoeff_2PI]  
	 vdivsd xmm0, xmm0, [ConstCoeff_3_0]
	 vmovsd real8 ptr [esp], xmm0
     call cos
	 fstp real8 ptr [ebp - 40] ; cos(theta+2PI/3)
	 vmovsd xmm1, real8 ptr [ebp - 40]
	 vsubsd xmm1, xmm1, real8 ptr [ebp - 48]
	 vmulsd xmm1, xmm1, real8 ptr [ebp - 32]
	 mov   ecx, [ebp + 12]
	 vmovsd real8 ptr [ecx + 8], xmm1 ; xmm1 = root x2 
	 vmovsd xmm0, real8 ptr [ebp - 24]
	 vmovsd xmm1, [ConstCoeff_2PI]
	 vsubsd xmm0, xmm0, xmm1
	 vdivsd xmm0, xmm0, [ConstCoeff_3_0]
	 vmovsd real8 ptr [esp], xmm1
	 call cos
	 fstp real8 ptr [ebp - 40]
	 vmovsd xmm1, real8 ptr [ebp - 40]
	 vmovsd xmm2, real8 ptr [ebp - 48]
	 vsubsd xmm1, xmm1, xmm2
	 vmulsd xmm1, xmm1, real8 ptr [ebp - 32]
	 mov   ecx, [ebp + 12]
	 vmovsd real8 ptr [ecx + 16], xmm1 ; xmm1 = root x3
	 mov   edx, [ebp + 24]
	 mov   dword ptr [edx], 0
	 jmp Done

	 ComplexRoots:
	 vmovsd xmm0, real8 ptr [eax]
	 vdivsd xmm5, xmm0, [ConstCoeff_3_0]
	 vmovsd real8 ptr [ebp - 48], xmm5 ; store a/3
	 vmovsd xmm0, real8 ptr [ebp - 8]
	 vmovsd xmm1, real8 ptr [ebp - 16]
	 vmovsd xmm2, xmm1, xmm1 ; R ERROR HERE [ebp - 8] = Q
	 vmulsd xmm1, xmm1, xmm1 ; R^2
	 vmovsd xmm3, xmm0, xmm0
	 vmulsd xmm0, xmm0, xmm0
	 vmulsd xmm0, xmm0, xmm3 ; Q^3
	 vsubsd xmm1, xmm1, xmm0
	; vxorpd xmm0, xmm0, [NegMask] ; added this line.
	 vsqrtsd xmm1, xmm1, xmm1
	 vaddsd xmm2, xmm2, xmm1 ; cubrt(arg)
	 ;vmovsd real8 ptr [ebp - 56], xmm2
	 vmovsd real8 ptr [esp], xmm2
	 vmovsd xmm0, qword ptr [ConstCoeff_0_3]
	 vmovsd real8 ptr [esp + 8], xmm0
	 call pow
	 fstp real8 ptr [ebp - 40]
	 vmovsd xmm0, real8 ptr [ebp - 40]
	 vxorpd xmm0, xmm0, qword ptr [NegMask] ; A
	 vmovsd xmm6, xmm0, xmm0 ; copy for fabs - added.
	 vmovsd real8 ptr [ebp - 56] , xmm0 ; store A
	 vmovsd xmm7, real8 ptr [ebp + 16]
	 vandpd xmm6, xmm0, qword ptr [AbsMask] ; added
	 vcomisd xmm6, xmm7
	 jb   ERROR
	 vmovsd xmm1, real8 ptr [ebp - 8]
	 vdivsd xmm2, xmm1, xmm0 ; B = Q/A , xmm2 = B , xmm0 = A
	 vaddsd xmm3, xmm2, xmm0
	 vsubsd xmm3, xmm3, real8 ptr [ebp - 48]
	 mov    ecx, [ebp + 12]
	 vmovsd real8 ptr [ecx], xmm3 ; store root x1
	 vmovsd xmm1, [ConstCoeff_N_0_5]
	 vaddsd xmm3, xmm0, xmm2
	 vmulsd xmm1, xmm1, xmm3
	 vsubsd xmm1, xmm1, real8 ptr [ebp - 48]
	 vmovsd xmm3, [ConstCoeff_1_0]
	; vxorpd xmm3, xmm3, [NegMask]
	 vsqrtsd xmm3, xmm3, xmm3 ; i = sqrt(-1) 
	 vmulsd xmm3, xmm3, [ConstCoeff_SQRT_3_2]
	 vsubsd xmm4, xmm0, xmm2
	 vmulsd xmm3, xmm3, xmm4
	 vaddsd xmm5, xmm1, xmm3
	 vsubsd xmm6, xmm1, xmm3
	 vmovsd real8 ptr [ecx + 8], xmm5; store root x2
	 vmovsd real8 ptr [ecx + 16], xmm6 ; store root x3
	 mov    edx, [ebp + 24]
	 mov    dword ptr [edx], -1

	 Done:
	 add esp, 56
	 pop ebp
	 ret

	 ERROR:
	 mov dword ptr [edx], 9999
	 add esp, 56
	 pop ebp
	 ret

	 CubeEquSolver2 endp
	 end