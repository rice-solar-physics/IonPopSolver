PRO PLOT_IB

; Double precision variables
Teq = 0.0D  ; Electron temperature
I1eq = 0.0D ; Equilibrium ionisation balance
I2eq = 0.0D
I3eq = 0.0D
I4eq = 0.0D
I5eq = 0.0D
T = 0.0D    ; Electron temperature
I1 = 0.0D   ; Ionisation balance
I2 = 0.0D
I3 = 0.0D
I4 = 0.0D
I5 = 0.0D
log_T_upper = 0.0D
log_I_lower = 0.0D

; floating point variables
time = 0.0
Te = 0.0
Teff = 0.0
temp1 = 0.0
temp2 = 0.0
temp3 = 0.0
temp4 = 0.0
temp5 = 0.0
temp6 = 0.0
temp7 = 0.0
temp8 = 0.0
temp9 = 0.0
temp10 = 0.0
temp11 = 0.0
temp12 = 0.0
temp13 = 0.0
temp14 = 0.0
temp15 = 0.0
temp16 = 0.0
temp17 = 0.0
temp18 = 0.0
temp19 = 0.0
temp20 = 0.0
temp21 = 0.0
temp22 = 0.0
temp23 = 0.0
temp24 = 0.0
temp25 = 0.0
temp26 = 0.0
temp27 = 0.0
temp28 = 0.0
temp29 = 0.0
x = 0.0
y = 0.0

; Integer variables
alength = 1000
profile_no = 0
i = 0
A = 0
count = 0
max_index = 0

; String variables
szDens=' '
szTime=' '
szfilename = ' '
sztitle = ' '

Teq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
I1eq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
I2eq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
I3eq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
I4eq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
I5eq = MAKE_ARRAY( 401, /DOUBLE, VALUE = 0.0D )
T = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
I1 = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
I2 = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
I3 = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
I4 = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
I5 = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )

; **** GRAPHICS ****

!P.MULTI = [0, 2, 2]
;WINDOW, 0, XSIZE=1024, YSIZE=768
SET_PLOT, 'ps'
DEVICE, FILE='fig.ps', /ENCAPSULATED, /INCHES, XSIZE=7.0, YSIZE=5.0

; ******************

; Open the equilibrium ionisation balance

OPENR, 1, 'fe.bal'

FOR i = 0, 400 DO BEGIN

    READF, 1, Te, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24, temp25, temp26, temp27 ; Iron
    Teq[i] = Te
    I1eq[i] = temp9
    I2eq[i] = temp12
    I3eq[i] = temp15
	I4eq[i] = temp19
	I5eq[i] = temp24

ENDFOR

CLOSE, 1

I1eq = ALOG10(I1eq)
I2eq = ALOG10(I2eq)
I3eq = ALOG10(I3eq)
I4eq = ALOG10(I4eq)
I5eq = ALOG10(I5eq)


; **** PLOTTING ****

log_T_upper = 8.0D
log_I_lower = -10.0D

; **** END OF PLOTTING ****

; **** PANEL 1 ****

PRINT
PRINT, 'Density (cm^-3): '
READ, szDens
PRINT, 'Timescale (s): '
READ, szTime
PRINT

; Open the non-equilibrium ionisation balance file to get the ion populations

szfilename = STRCOMPRESS( STRING( 'n_', szDens,'_tau_', szTime,'/Z26.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the non-equilibrium ion populations

    READF, 1, time, Te, Teff, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24;, temp25, temp26, temp27 ; Iron
	T[i] = Te
    I1[i] = temp9
    I2[i] = temp12
    I3[i] = temp15
    I4[i] = temp19
    I5[i] = temp24

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    T[i] = T[count]
    I1[i] = I1[count]
    I2[i] = I2[count]
    I3[i] = I3[count]
    I4[i] = I4[count]
    I5[i] = I5[count]


ENDFOR

; Plot the data

sztitle = STRCOMPRESS( STRING( 'n=', szDens,' cm!u-3!n, !7s!3!lH!n=', szTime,' s' ) );, /REMOVE_ALL )
T = ALOG10(T)

I1 = ALOG10(I1)
I2 = ALOG10(I2)
I3 = ALOG10(I3)
I4 = ALOG10(I4)
I5 = ALOG10(I5)

PLOT, Teq, I1eq, xrange=[5.0,log_T_upper], yrange=[log_I_lower,1.0], xtitle='Log!l10!n T (K)', ytitle='Log!l10!n Population Fraction', title=sztitle, xth=3, yth=3, linestyle=1, th=3, charsize=1, charth=3
OPLOT, Teq, I2eq, linestyle=1, th=3
OPLOT, Teq, I3eq, linestyle=1, th=3
OPLOT, Teq, I4eq, linestyle=1, th=3
OPLOT, Teq, I5eq, linestyle=1, th=3
OPLOT, T, I1, linestyle=0, th=3
OPLOT, T, I2, linestyle=0, th=3
OPLOT, T, I3, linestyle=0, th=3
OPLOT, T, I4, linestyle=0, th=3
OPLOT, T, I5, linestyle=0, th=3

y = MAX( I1, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'IX', charsize=1, charth=3

y = MAX( I2, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XII', charsize=1, charth=3

y = MAX( I3, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XV', charsize=1, charth=3

y = MAX( I4, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XIX', charsize=1, charth=3

y = MAX( I5, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XXIV', charsize=1, charth=3

; **** END OF PANEL 1 ****


; **** PANEL 2 ****

PRINT
PRINT, 'Density (cm^-3): '
READ, szDens
PRINT, 'Timescale (s): '
READ, szTime
PRINT

; Open the non-equilibrium ionisation balance file to get the ion populations

szfilename = STRCOMPRESS( STRING( 'n_', szDens,'_tau_', szTime,'/Z26.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the non-equilibrium ion populations

    READF, 1, time, Te, Teff, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24;, temp25, temp26, temp27 ; Iron
	T[i] = Te
    I1[i] = temp9
    I2[i] = temp12
    I3[i] = temp15
    I4[i] = temp19
    I5[i] = temp24

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    T[i] = T[count]
    I1[i] = I1[count]
    I2[i] = I2[count]
    I3[i] = I3[count]
    I4[i] = I4[count]
    I5[i] = I5[count]


ENDFOR

; Plot the data

sztitle = STRCOMPRESS( STRING( 'n=', szDens,' cm!u-3!n, !7s!3!lH!n=', szTime,' s' ) );, /REMOVE_ALL )
T = ALOG10(T)

I1 = ALOG10(I1)
I2 = ALOG10(I2)
I3 = ALOG10(I3)
I4 = ALOG10(I4)
I5 = ALOG10(I5)

PLOT, Teq, I1eq, xrange=[5.0,log_T_upper], yrange=[log_I_lower,1.0], xtitle='Log!l10!n T (K)', ytitle='Log!l10!n Population Fraction', title=sztitle, xth=3, yth=3, linestyle=1, th=3, charsize=1, charth=3
OPLOT, Teq, I2eq, linestyle=1, th=3
OPLOT, Teq, I3eq, linestyle=1, th=3
OPLOT, Teq, I4eq, linestyle=1, th=3
OPLOT, Teq, I5eq, linestyle=1, th=3
OPLOT, T, I1, linestyle=0, th=3
OPLOT, T, I2, linestyle=0, th=3
OPLOT, T, I3, linestyle=0, th=3
OPLOT, T, I4, linestyle=0, th=3
OPLOT, T, I5, linestyle=0, th=3

y = MAX( I1, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'IX', charsize=1, charth=3

y = MAX( I2, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XII', charsize=1, charth=3

y = MAX( I3, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XV', charsize=1, charth=3

y = MAX( I4, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XIX', charsize=1, charth=3

y = MAX( I5, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XXIV', charsize=1, charth=3

; **** END OF PANEL 2 ****


; **** PANEL 3 ****

PRINT
PRINT, 'Density (cm^-3): '
READ, szDens
PRINT, 'Timescale (s): '
READ, szTime
PRINT

; Open the non-equilibrium ionisation balance file to get the ion populations

szfilename = STRCOMPRESS( STRING( 'n_', szDens,'_tau_', szTime,'/Z26.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the non-equilibrium ion populations

    READF, 1, time, Te, Teff, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24;, temp25, temp26, temp27 ; Iron
	T[i] = Te
    I1[i] = temp9
    I2[i] = temp12
    I3[i] = temp15
    I4[i] = temp19
    I5[i] = temp24

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    T[i] = T[count]
    I1[i] = I1[count]
    I2[i] = I2[count]
    I3[i] = I3[count]
    I4[i] = I4[count]
    I5[i] = I5[count]


ENDFOR

; Plot the data

sztitle = STRCOMPRESS( STRING( 'n=', szDens,' cm!u-3!n, !7s!3!lH!n=', szTime,' s' ) );, /REMOVE_ALL )
T = ALOG10(T)

I1 = ALOG10(I1)
I2 = ALOG10(I2)
I3 = ALOG10(I3)
I4 = ALOG10(I4)
I5 = ALOG10(I5)

PLOT, Teq, I1eq, xrange=[5.0,log_T_upper], yrange=[log_I_lower,1.0], xtitle='Log!l10!n T (K)', ytitle='Log!l10!n Population Fraction', title=sztitle, xth=3, yth=3, linestyle=1, th=3, charsize=1, charth=3
OPLOT, Teq, I2eq, linestyle=1, th=3
OPLOT, Teq, I3eq, linestyle=1, th=3
OPLOT, Teq, I4eq, linestyle=1, th=3
OPLOT, Teq, I5eq, linestyle=1, th=3
OPLOT, T, I1, linestyle=0, th=3
OPLOT, T, I2, linestyle=0, th=3
OPLOT, T, I3, linestyle=0, th=3
OPLOT, T, I4, linestyle=0, th=3
OPLOT, T, I5, linestyle=0, th=3

y = MAX( I1, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'IX', charsize=1, charth=3

y = MAX( I2, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XII', charsize=1, charth=3

y = MAX( I3, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XV', charsize=1, charth=3

y = MAX( I4, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XIX', charsize=1, charth=3

y = MAX( I5, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XXIV', charsize=1, charth=3

; **** END OF PANEL 3 ****


; **** PANEL 4 ****

PRINT
PRINT, 'Density (cm^-3): '
READ, szDens
PRINT, 'Timescale (s): '
READ, szTime
PRINT

; Open the non-equilibrium ionisation balance file to get the ion populations

szfilename = STRCOMPRESS( STRING( 'n_', szDens,'_tau_', szTime,'/Z26.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the non-equilibrium ion populations

    READF, 1, time, Te, Teff, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24;, temp25, temp26, temp27 ; Iron
	T[i] = Te
    I1[i] = temp9
    I2[i] = temp12
    I3[i] = temp15
    I4[i] = temp19
    I5[i] = temp24

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    T[i] = T[count]
    I1[i] = I1[count]
    I2[i] = I2[count]
    I3[i] = I3[count]
    I4[i] = I4[count]
    I5[i] = I5[count]


ENDFOR

; Plot the data

sztitle = STRCOMPRESS( STRING( 'n=', szDens,' cm!u-3!n, !7s!3!lH!n=', szTime,' s' ) );, /REMOVE_ALL )
T = ALOG10(T)

I1 = ALOG10(I1)
I2 = ALOG10(I2)
I3 = ALOG10(I3)
I4 = ALOG10(I4)
I5 = ALOG10(I5)

PLOT, Teq, I1eq, xrange=[5.0,log_T_upper], yrange=[log_I_lower,1.0], xtitle='Log!l10!n T (K)', ytitle='Log!l10!n Population Fraction', title=sztitle, xth=3, yth=3, linestyle=1, th=3, charsize=1, charth=3
OPLOT, Teq, I2eq, linestyle=1, th=3
OPLOT, Teq, I3eq, linestyle=1, th=3
OPLOT, Teq, I4eq, linestyle=1, th=3
OPLOT, Teq, I5eq, linestyle=1, th=3
OPLOT, T, I1, linestyle=0, th=3
OPLOT, T, I2, linestyle=0, th=3
OPLOT, T, I3, linestyle=0, th=3
OPLOT, T, I4, linestyle=0, th=3
OPLOT, T, I5, linestyle=0, th=3

y = MAX( I1, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'IX', charsize=1, charth=3

y = MAX( I2, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XII', charsize=1, charth=3

y = MAX( I3, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XV', charsize=1, charth=3

y = MAX( I4, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XIX', charsize=1, charth=3

y = MAX( I5, max_index )
x = T[max_index]
IF x LT log_T_upper AND y GT log_I_lower THEN XYOUTS, x, y, 'XXIV', charsize=1, charth=3

; **** END OF PANEL 4 ****


; **** GRAPHICS ****

DEVICE, /CLOSE
SET_PLOT, 'win'
!p.multi = 0

; ******************

END
