C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
C     *                                                               *
C     *                  copyright (c) 2011 by UCAR                   *
C     *                                                               *
C     *       University Corporation for Atmospheric Research         *
C     *                                                               *
C     *                      all rights reserved                      *
C     *                                                               *
C     *                     FFTPACK  version 5.1                      *
C     *                                                               *
C     *                 A Fortran Package of Fast Fourier             *
C     *                                                               *
C     *                Subroutines and Example Programs               *
C     *                                                               *
C     *                             by                                *
C     *                                                               *
C     *               Paul Swarztrauber and Dick Valent               *
C     *                                                               *
C     *                             of                                *
C     *                                                               *
C     *         the National Center for Atmospheric Research          *
C     *                                                               *
C     *                Boulder, Colorado  (80307)  U.S.A.             *
C     *                                                               *
C     *                   which is sponsored by                       *
C     *                                                               *
C     *              the National Science Foundation                  *
C     *                                                               *
C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
C
      SUBROUTINE MRADB3 (M,IDO,L1,CC,IM1,IN1,CH,IM2,IN2,WA1,WA2)
      REAL       CC(IN1,IDO,3,L1)    ,CH(IN2,IDO,L1,3),
     1           WA1(IDO)   ,WA2(IDO)
C
      M1D = (M-1)*IM1+1
      M2S = 1-IM2
      ARG=2.*4.*ATAN(1.0)/3.
      TAUR=COS(ARG)
      TAUI=SIN(ARG)
      DO 101 K=1,L1
          M2 = M2S
          DO 1001 M1=1,M1D,IM1
          M2 = M2+IM2
         CH(M2,1,K,1) = CC(M1,1,1,K)+2.*CC(M1,IDO,2,K)
         CH(M2,1,K,2) = CC(M1,1,1,K)+(2.*TAUR)*CC(M1,IDO,2,K)
     1   -(2.*TAUI)*CC(M1,1,3,K)
         CH(M2,1,K,3) = CC(M1,1,1,K)+(2.*TAUR)*CC(M1,IDO,2,K)
     1   +2.*TAUI*CC(M1,1,3,K)
 1001     CONTINUE
  101 CONTINUE
      IF (IDO .EQ. 1) RETURN
      IDP2 = IDO+2
      DO 103 K=1,L1
         DO 102 I=3,IDO,2
            IC = IDP2-I
               M2 = M2S
               DO 1002 M1=1,M1D,IM1
               M2 = M2+IM2
        CH(M2,I-1,K,1) = CC(M1,I-1,1,K)+(CC(M1,I-1,3,K)+CC(M1,IC-1,2,K))
        CH(M2,I,K,1) = CC(M1,I,1,K)+(CC(M1,I,3,K)-CC(M1,IC,2,K))
        CH(M2,I-1,K,2) = WA1(I-2)*
     1 ((CC(M1,I-1,1,K)+TAUR*(CC(M1,I-1,3,K)+CC(M1,IC-1,2,K)))-
     * (TAUI*(CC(M1,I,3,K)+CC(M1,IC,2,K))))
     2                   -WA1(I-1)*
     3 ((CC(M1,I,1,K)+TAUR*(CC(M1,I,3,K)-CC(M1,IC,2,K)))+
     * (TAUI*(CC(M1,I-1,3,K)-CC(M1,IC-1,2,K))))
            CH(M2,I,K,2) = WA1(I-2)*
     4 ((CC(M1,I,1,K)+TAUR*(CC(M1,I,3,K)-CC(M1,IC,2,K)))+
     8 (TAUI*(CC(M1,I-1,3,K)-CC(M1,IC-1,2,K))))
     5                  +WA1(I-1)*
     6 ((CC(M1,I-1,1,K)+TAUR*(CC(M1,I-1,3,K)+CC(M1,IC-1,2,K)))-
     8 (TAUI*(CC(M1,I,3,K)+CC(M1,IC,2,K))))
              CH(M2,I-1,K,3) = WA2(I-2)*
     7 ((CC(M1,I-1,1,K)+TAUR*(CC(M1,I-1,3,K)+CC(M1,IC-1,2,K)))+
     8 (TAUI*(CC(M1,I,3,K)+CC(M1,IC,2,K))))
     8   -WA2(I-1)*
     9 ((CC(M1,I,1,K)+TAUR*(CC(M1,I,3,K)-CC(M1,IC,2,K)))-
     8 (TAUI*(CC(M1,I-1,3,K)-CC(M1,IC-1,2,K))))
            CH(M2,I,K,3) = WA2(I-2)*
     1 ((CC(M1,I,1,K)+TAUR*(CC(M1,I,3,K)-CC(M1,IC,2,K)))-
     8 (TAUI*(CC(M1,I-1,3,K)-CC(M1,IC-1,2,K))))
     2                 +WA2(I-1)*
     3 ((CC(M1,I-1,1,K)+TAUR*(CC(M1,I-1,3,K)+CC(M1,IC-1,2,K)))+
     8 (TAUI*(CC(M1,I,3,K)+CC(M1,IC,2,K))))
 1002          CONTINUE
  102    CONTINUE
  103 CONTINUE
      RETURN
      END
