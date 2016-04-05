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
      SUBROUTINE R1F5KB (IDO,L1,CC,IN1,CH,IN2,
     1       WA1,WA2,WA3,WA4)
      REAL   CC(IN1,IDO,5,L1)    ,CH(IN2,IDO,L1,5),
     1       WA1(IDO)     ,WA2(IDO)     ,WA3(IDO)     ,WA4(IDO)
C
      ARG=2.*4.*ATAN(1.0)/5.
      TR11=COS(ARG)
      TI11=SIN(ARG)
      TR12=COS(2.*ARG)
      TI12=SIN(2.*ARG)
      DO 101 K=1,L1
         CH(1,1,K,1) = CC(1,1,1,K)+2.*CC(1,IDO,2,K)+2.*CC(1,IDO,4,K)
         CH(1,1,K,2) = (CC(1,1,1,K)+TR11*2.*CC(1,IDO,2,K)
     1   +TR12*2.*CC(1,IDO,4,K))-(TI11*2.*CC(1,1,3,K)
     1   +TI12*2.*CC(1,1,5,K))
         CH(1,1,K,3) = (CC(1,1,1,K)+TR12*2.*CC(1,IDO,2,K)
     1   +TR11*2.*CC(1,IDO,4,K))-(TI12*2.*CC(1,1,3,K)
     1   -TI11*2.*CC(1,1,5,K))
         CH(1,1,K,4) = (CC(1,1,1,K)+TR12*2.*CC(1,IDO,2,K)
     1   +TR11*2.*CC(1,IDO,4,K))+(TI12*2.*CC(1,1,3,K)
     1   -TI11*2.*CC(1,1,5,K))
         CH(1,1,K,5) = (CC(1,1,1,K)+TR11*2.*CC(1,IDO,2,K)
     1   +TR12*2.*CC(1,IDO,4,K))+(TI11*2.*CC(1,1,3,K)
     1   +TI12*2.*CC(1,1,5,K))
  101 CONTINUE
      IF (IDO .EQ. 1) RETURN
      IDP2 = IDO+2
      DO 103 K=1,L1
         DO 102 I=3,IDO,2
            IC = IDP2-I
        CH(1,I-1,K,1) = CC(1,I-1,1,K)+(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +(CC(1,I-1,5,K)+CC(1,IC-1,4,K))
        CH(1,I,K,1) = CC(1,I,1,K)+(CC(1,I,3,K)-CC(1,IC,2,K))
     1  +(CC(1,I,5,K)-CC(1,IC,4,K))
        CH(1,I-1,K,2) = WA1(I-2)*((CC(1,I-1,1,K)+TR11*
     1  (CC(1,I-1,3,K)+CC(1,IC-1,2,K))+TR12
     1  *(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))-(TI11*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))+TI12*(CC(1,I,5,K)+CC(1,IC,4,K))))
     1  -WA1(I-1)*((CC(1,I,1,K)+TR11*(CC(1,I,3,K)-CC(1,IC,2,K))
     1  +TR12*(CC(1,I,5,K)-CC(1,IC,4,K)))+(TI11*(CC(1,I-1,3,K)
     1  -CC(1,IC-1,2,K))+TI12*(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
        CH(1,I,K,2) = WA1(I-2)*((CC(1,I,1,K)+TR11*(CC(1,I,3,K)
     1  -CC(1,IC,2,K))+TR12*(CC(1,I,5,K)-CC(1,IC,4,K)))
     1  +(TI11*(CC(1,I-1,3,K)-CC(1,IC-1,2,K))+TI12
     1  *(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))+WA1(I-1)
     1  *((CC(1,I-1,1,K)+TR11*(CC(1,I-1,3,K)
     1  +CC(1,IC-1,2,K))+TR12*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))
     1  -(TI11*(CC(1,I,3,K)+CC(1,IC,2,K))+TI12
     1  *(CC(1,I,5,K)+CC(1,IC,4,K))))
        CH(1,I-1,K,3) = WA2(I-2)
     1  *((CC(1,I-1,1,K)+TR12*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR11*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))-(TI12*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))-TI11*(CC(1,I,5,K)+CC(1,IC,4,K))))
     1 -WA2(I-1)
     1 *((CC(1,I,1,K)+TR12*(CC(1,I,3,K)-
     1  CC(1,IC,2,K))+TR11*(CC(1,I,5,K)-CC(1,IC,4,K)))
     1  +(TI12*(CC(1,I-1,3,K)-CC(1,IC-1,2,K))-TI11
     1  *(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
        CH(1,I,K,3) = WA2(I-2)
     1 *((CC(1,I,1,K)+TR12*(CC(1,I,3,K)-
     1  CC(1,IC,2,K))+TR11*(CC(1,I,5,K)-CC(1,IC,4,K)))
     1  +(TI12*(CC(1,I-1,3,K)-CC(1,IC-1,2,K))-TI11
     1  *(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
     1  +WA2(I-1)
     1  *((CC(1,I-1,1,K)+TR12*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR11*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))-(TI12*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))-TI11*(CC(1,I,5,K)+CC(1,IC,4,K))))
        CH(1,I-1,K,4) = WA3(I-2)
     1  *((CC(1,I-1,1,K)+TR12*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR11*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))+(TI12*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))-TI11*(CC(1,I,5,K)+CC(1,IC,4,K))))
     1  -WA3(I-1)
     1 *((CC(1,I,1,K)+TR12*(CC(1,I,3,K)-
     1  CC(1,IC,2,K))+TR11*(CC(1,I,5,K)-CC(1,IC,4,K)))
     1  -(TI12*(CC(1,I-1,3,K)-CC(1,IC-1,2,K))-TI11
     1  *(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
        CH(1,I,K,4) = WA3(I-2)
     1 *((CC(1,I,1,K)+TR12*(CC(1,I,3,K)-
     1  CC(1,IC,2,K))+TR11*(CC(1,I,5,K)-CC(1,IC,4,K)))
     1  -(TI12*(CC(1,I-1,3,K)-CC(1,IC-1,2,K))-TI11
     1  *(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
     1  +WA3(I-1)
     1  *((CC(1,I-1,1,K)+TR12*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR11*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))+(TI12*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))-TI11*(CC(1,I,5,K)+CC(1,IC,4,K))))
        CH(1,I-1,K,5) = WA4(I-2)
     1  *((CC(1,I-1,1,K)+TR11*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR12*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))+(TI11*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))+TI12*(CC(1,I,5,K)+CC(1,IC,4,K))))
     1  -WA4(I-1)
     1  *((CC(1,I,1,K)+TR11*(CC(1,I,3,K)-CC(1,IC,2,K))
     1  +TR12*(CC(1,I,5,K)-CC(1,IC,4,K)))-(TI11*(CC(1,I-1,3,K)
     1  -CC(1,IC-1,2,K))+TI12*(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
        CH(1,I,K,5) = WA4(I-2)
     1  *((CC(1,I,1,K)+TR11*(CC(1,I,3,K)-CC(1,IC,2,K))
     1  +TR12*(CC(1,I,5,K)-CC(1,IC,4,K)))-(TI11*(CC(1,I-1,3,K)
     1  -CC(1,IC-1,2,K))+TI12*(CC(1,I-1,5,K)-CC(1,IC-1,4,K))))
     1  +WA4(I-1)
     1  *((CC(1,I-1,1,K)+TR11*(CC(1,I-1,3,K)+CC(1,IC-1,2,K))
     1  +TR12*(CC(1,I-1,5,K)+CC(1,IC-1,4,K)))+(TI11*(CC(1,I,3,K)
     1  +CC(1,IC,2,K))+TI12*(CC(1,I,5,K)+CC(1,IC,4,K))))
  102    CONTINUE
  103 CONTINUE
      RETURN
      END
