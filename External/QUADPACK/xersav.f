      subroutine xersav(messg,nmessg,nerr,level,icount)
c
c     abstract
c        record that this error occurred.
c
c     description of parameters
c     --input--
c       messg, nmessg, nerr, level are as in xerror,
c       except that when nmessg=0 the tables will be
c       dumped and cleared, and when nmessg is less than zero the
c       tables will be dumped and not cleared.
c     --output--
c       icount will be the number of times this message has
c       been seen, or zero if the table has overflowed and
c       does not contain this message specifically.
c       when nmessg=0, icount will not be altered.
c
c     written by ron jones, with slatec common math library subcommittee
c     latest revision ---  19 mar 1980
c
      integer f(17),lun(5)
      dimension messg(nmessg)
      dimension mestab(10),nertab(10),levtab(10),kount(10)
c     next three data statements are needed merely to satisfy
c     certain conventions for compilers which dynamically
c     allocate storage.
      data mestab(1),mestab(2),mestab(3),mestab(4),mestab(5),
     1     mestab(6),mestab(7),mestab(8),mestab(9),mestab(10)
     2     /0,0,0,0,0,0,0,0,0,0/
      data nertab(1),nertab(2),nertab(3),nertab(4),nertab(5),
     1     nertab(6),nertab(7),nertab(8),nertab(9),nertab(10)
     2     /0,0,0,0,0,0,0,0,0,0/
      data levtab(1),levtab(2),levtab(3),levtab(4),levtab(5),
     1     levtab(6),levtab(7),levtab(8),levtab(9),levtab(10)
     2     /0,0,0,0,0,0,0,0,0,0/
c     next two data statements are necessary to provide a blank
c     error table initially
      data kount(1),kount(2),kount(3),kount(4),kount(5),
     1     kount(6),kount(7),kount(8),kount(9),kount(10)
     2     /0,0,0,0,0,0,0,0,0,0/
      data kountx/0/
c     next data statement sets up output format
      data f(1),f(2),f(3),f(4),f(5),f(6),f(7),f(8),f(9),f(10),
     1     f(11),f(12),f(13),f(14),f(15),f(16),f(17)
     2     /1h( ,1h1 ,1hx ,1h, ,1ha ,1h  ,1h  ,1h, ,1hi ,1h  ,
     3      1h  ,1h, ,1h2 ,1hi ,1h1 ,1h0 ,1h) /
      if (nmessg.gt.0) go to 80
c     dump the table
         if (kount(1).eq.0) return
c        prepare format
         nchar = i1mach(6)
         call s88fmt(2,nchar,f(6))
         ncol = 20 - nchar
         call s88fmt(2,ncol,f(10))
c        print to each unit
         call xgetua(lun,nunit)
         do 60 kunit=1,nunit
            iunit = lun(kunit)
            if (iunit.eq.0) iunit = i1mach(4)
c           print table header
            write (iunit,10)
   10       format (32h0          error message summary/
     1              41h first word      nerr     level     count)
c           print body of table
            do 20 i=1,10
               if (kount(i).eq.0) go to 30
               write (iunit,f) mestab(i),nertab(i),levtab(i),kount(i)
   20       continue
   30       continue
c           print number of other errors
            if (kountx.ne.0) write (iunit,40) kountx
   40       format (41h0other errors not individually tabulated=,i10)
            write (iunit,50)
   50       format (1x)
   60    continue
         if (nmessg.lt.0) return
c        clear the error tables
         do 70 i=1,10
   70       kount(i) = 0
         kountx = 0
         return
   80 continue
c     process a message...
c     search for this messg, or else an empty slot for this messg,
c     or else determine that the error table is full.
      do 90 i=1,10
         ii = i
         if (kount(i).eq.0) go to 110
         if (messg(1).ne.mestab(i)) go to 90
         if (nerr.ne.nertab(i)) go to 90
         if (level.ne.levtab(i)) go to 90
         go to 100
   90 continue
c     three possible cases...
c     table is full
         kountx = kountx+1
         icount = 1
         return
c     message found in table
  100    kount(ii) = kount(ii) + 1
         icount = kount(ii)
         return
c     empty slot found for new message
  110    mestab(ii) = messg(1)
         nertab(ii) = nerr
         levtab(ii) = level
         kount(ii)  = 1
         icount = 1
         return
      end
