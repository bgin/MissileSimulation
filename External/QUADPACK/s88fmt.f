      subroutine s88fmt(n,ivalue,ifmt)
c
c     abstract
c        s88fmt replaces ifmt(1), ... ,ifmt(n) with the
c        characters corresponding to the n least significant
c        digits of ivalue.
c
c     taken from the bell laboratories port library error handler
c     latest revision ---  7 june 1978
c
      dimension ifmt(n),idigit(10)
      data idigit(1),idigit(2),idigit(3),idigit(4),idigit(5),
     1     idigit(6),idigit(7),idigit(8),idigit(9),idigit(10)
     2     /1h0,1h1,1h2,1h3,1h4,1h5,1h6,1h7,1h8,1h9/
      nt = n
      it = ivalue
   10    if (nt .eq. 0) return
         index = mod(it,10)
         ifmt(nt) = idigit(index+1)
         it = it/10
         nt = nt - 1
         go to 10
      end
