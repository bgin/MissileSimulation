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
      SUBROUTINE R1FGKB (IDO,IP,L1,IDL1,CC,C1,C2,IN1,
     1          CH,CH2,IN2,WA)
      REAL      CH(IN2,IDO,L1,IP)    ,CC(IN1,IDO,IP,L1) ,
     1          C1(IN1,IDO,L1,IP)    ,C2(IN1,IDL1,IP),
     2          CH2(IN2,IDL1,IP)     ,WA(IDO)
C
      TPI=2.*4.*ATAN(1.0)
      ARG = TPI/FLOAT(IP)
      DCP = COS(ARG)
      DSP = SIN(ARG)
      IDP2 = IDO+2
      NBD = (IDO-1)/2
      IPP2 = IP+2
      IPPH = (IP+1)/2
      IF (IDO .LT. L1) GO TO 103
      DO 102 K=1,L1
         DO 101 I=1,IDO
            CH(1,I,K,1) = CC(1,I,1,K)
  101    CONTINUE
  102 CONTINUE
      GO TO 106
  103 DO 105 I=1,IDO
         DO 104 K=1,L1
            CH(1,I,K,1) = CC(1,I,1,K)
  104    CONTINUE
  105 CONTINUE
  106 DO 108 J=2,IPPH
         JC = IPP2-J
         J2 = J+J
         DO 107 K=1,L1
            CH(1,1,K,J) = CC(1,IDO,J2-2,K)+CC(1,IDO,J2-2,K)
            CH(1,1,K,JC) = CC(1,1,J2-1,K)+CC(1,1,J2-1,K)
 1007       CONTINUE
  107    CONTINUE
  108 CONTINUE
      IF (IDO .EQ. 1) GO TO 116
      IF (NBD .LT. L1) GO TO 112
      DO 111 J=2,IPPH
         JC = IPP2-J
         DO 110 K=1,L1
            DO 109 I=3,IDO,2
               IC = IDP2-I
               CH(1,I-1,K,J) = CC(1,I-1,2*J-1,K)+CC(1,IC-1,2*J-2,K)
               CH(1,I-1,K,JC) = CC(1,I-1,2*J-1,K)-CC(1,IC-1,2*J-2,K)
               CH(1,I,K,J) = CC(1,I,2*J-1,K)-CC(1,IC,2*J-2,K)
               CH(1,I,K,JC) = CC(1,I,2*J-1,K)+CC(1,IC,2*J-2,K)
  109       CONTINUE
  110    CONTINUE
  111 CONTINUE
      GO TO 116
  112 DO 115 J=2,IPPH
         JC = IPP2-J
         DO 114 I=3,IDO,2
            IC = IDP2-I
            DO 113 K=1,L1
               CH(1,I-1,K,J) = CC(1,I-1,2*J-1,K)+CC(1,IC-1,2*J-2,K)
               CH(1,I-1,K,JC) = CC(1,I-1,2*J-1,K)-CC(1,IC-1,2*J-2,K)
               CH(1,I,K,J) = CC(1,I,2*J-1,K)-CC(1,IC,2*J-2,K)
               CH(1,I,K,JC) = CC(1,I,2*J-1,K)+CC(1,IC,2*J-2,K)
  113       CONTINUE
  114    CONTINUE
  115 CONTINUE
  116 AR1 = 1.
      AI1 = 0.
      DO 120 L=2,IPPH
         LC = IPP2-L
         AR1H = DCP*AR1-DSP*AI1
         AI1 = DCP*AI1+DSP*AR1
         AR1 = AR1H
         DO 117 IK=1,IDL1
            C2(1,IK,L) = CH2(1,IK,1)+AR1*CH2(1,IK,2)
            C2(1,IK,LC) = AI1*CH2(1,IK,IP)
  117    CONTINUE
         DC2 = AR1
         DS2 = AI1
         AR2 = AR1
         AI2 = AI1
         DO 119 J=3,IPPH
            JC = IPP2-J
            AR2H = DC2*AR2-DS2*AI2
            AI2 = DC2*AI2+DS2*AR2
            AR2 = AR2H
            DO 118 IK=1,IDL1
               C2(1,IK,L) = C2(1,IK,L)+AR2*CH2(1,IK,J)
               C2(1,IK,LC) = C2(1,IK,LC)+AI2*CH2(1,IK,JC)
  118       CONTINUE
  119    CONTINUE
  120 CONTINUE
      DO 122 J=2,IPPH
         DO 121 IK=1,IDL1
            CH2(1,IK,1) = CH2(1,IK,1)+CH2(1,IK,J)
  121    CONTINUE
  122 CONTINUE
      DO 124 J=2,IPPH
         JC = IPP2-J
         DO 123 K=1,L1
            CH(1,1,K,J) = C1(1,1,K,J)-C1(1,1,K,JC)
            CH(1,1,K,JC) = C1(1,1,K,J)+C1(1,1,K,JC)
  123    CONTINUE
  124 CONTINUE
      IF (IDO .EQ. 1) GO TO 132
      IF (NBD .LT. L1) GO TO 128
      DO 127 J=2,IPPH
         JC = IPP2-J
         DO 126 K=1,L1
            DO 125 I=3,IDO,2
               CH(1,I-1,K,J) = C1(1,I-1,K,J)-C1(1,I,K,JC)
               CH(1,I-1,K,JC) = C1(1,I-1,K,J)+C1(1,I,K,JC)
               CH(1,I,K,J) = C1(1,I,K,J)+C1(1,I-1,K,JC)
               CH(1,I,K,JC) = C1(1,I,K,J)-C1(1,I-1,K,JC)
  125       CONTINUE
  126    CONTINUE
  127 CONTINUE
      GO TO 132
  128 DO 131 J=2,IPPH
         JC = IPP2-J
         DO 130 I=3,IDO,2
            DO 129 K=1,L1
               CH(1,I-1,K,J) = C1(1,I-1,K,J)-C1(1,I,K,JC)
               CH(1,I-1,K,JC) = C1(1,I-1,K,J)+C1(1,I,K,JC)
               CH(1,I,K,J) = C1(1,I,K,J)+C1(1,I-1,K,JC)
               CH(1,I,K,JC) = C1(1,I,K,J)-C1(1,I-1,K,JC)
  129       CONTINUE
  130    CONTINUE
  131 CONTINUE
  132 CONTINUE
      IF (IDO .EQ. 1) RETURN
      DO 133 IK=1,IDL1
         C2(1,IK,1) = CH2(1,IK,1)
  133 CONTINUE
      DO 135 J=2,IP
         DO 134 K=1,L1
            C1(1,1,K,J) = CH(1,1,K,J)
  134    CONTINUE
  135 CONTINUE
      IF (NBD .GT. L1) GO TO 139
      IS = -IDO
      DO 138 J=2,IP
         IS = IS+IDO
         IDIJ = IS
         DO 137 I=3,IDO,2
            IDIJ = IDIJ+2
            DO 136 K=1,L1
               C1(1,I-1,K,J) = WA(IDIJ-1)*CH(1,I-1,K,J)-WA(IDIJ)*
     1          CH(1,I,K,J)
               C1(1,I,K,J) = WA(IDIJ-1)*CH(1,I,K,J)+WA(IDIJ)*
     1          CH(1,I-1,K,J)
  136       CONTINUE
  137    CONTINUE
  138 CONTINUE
      GO TO 143
  139 IS = -IDO
      DO 142 J=2,IP
         IS = IS+IDO
         DO 141 K=1,L1
            IDIJ = IS
            DO 140 I=3,IDO,2
               IDIJ = IDIJ+2
               C1(1,I-1,K,J) = WA(IDIJ-1)*CH(1,I-1,K,J)-WA(IDIJ)*
     1          CH(1,I,K,J)
               C1(1,I,K,J) = WA(IDIJ-1)*CH(1,I,K,J)+WA(IDIJ)*
     1          CH(1,I-1,K,J)
  140       CONTINUE
  141    CONTINUE
  142 CONTINUE
  143 RETURN
      END
