      subroutine xerprt(messg,nmessg)
c
c     abstract
c        print the hollerith message in messg, of length messg,
c        on each file indicated by xgetua.
c        this version prints exactly the right number of characters,
c        not a number of words, and thus should work on machines
c        which do not blank fill the last word of the hollerith.
c
c     ron jones, june 1980
c
      integer f(10),g(14),lun(5)
      dimension messg(nmessg)
      data f(1),f(2),f(3),f(4),f(5),f(6),f(7),f(8),f(9),f(10)
     1   / 1h( ,1h1 ,1hx ,1h, ,1h  ,1h  ,1ha ,1h  ,1h  ,1h) /
      data g(1),g(2),g(3),g(4),g(5),g(6),g(7),g(8),g(9),g(10)
     1   / 1h( ,1h1 ,1hx ,1h  ,1h  ,1h  ,1h  ,1h  ,1h  ,1h  /
      data g(11),g(12),g(13),g(14)
     1   / 1h   ,1h   ,1h   ,1h)  /
      data la/1ha/,lcom/1h,/,lblank/1h /
c     prepare format for whole lines
      nchar = i1mach(6)
      nfield = 72/nchar
      call s88fmt(2,nfield,f(5))
      call s88fmt(2,nchar,f(8))
c     prepare format for last, partial line, if needed
      ncharl = nfield*nchar
      nlines = nmessg/ncharl
      nword  = nlines*nfield
      nchrem = nmessg - nlines*ncharl
      if (nchrem.le.0) go to 40
         do 10 i=4,13
10          g(i) = lblank
         nfield = nchrem/nchar
         if (nfield.le.0) go to 20
c        prepare whole word fields
            g(4) = lcom
            call s88fmt(2,nfield,g(5))
            g(7) = la
            call s88fmt(2,nchar,g(8))
20       continue
         nchlst = mod(nchrem,nchar)
         if (nchlst.le.0) go to 30
c        prepare partial word field
            g(10) = lcom
            g(11) = la
            call s88fmt(2,nchlst,g(12))
30       continue
40    continue
c     print the message
      nword1 = nword+1
      nword2 = (nmessg+nchar-1)/nchar
      call xgetua(lun,nunit)
      do 50 kunit = 1,nunit
         iunit = lun(kunit)
         if (iunit.eq.0) iunit = i1mach(4)
         if (nword.gt.0) write (iunit,f) (messg(i),i=1,nword)
         if (nchrem.gt.0) write (iunit,g) (messg(i),i=nword1,nword2)
50    continue
      return
      end
