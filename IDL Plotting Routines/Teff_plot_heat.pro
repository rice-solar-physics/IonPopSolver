PRO TEFF_PLOT_HEAT

; Double precision variables
time = 0.0D
T = 0.0D    ; Electron temperature
Teff = 0.0D

; floating point variables
temp1 = 0.0
temp2 = 0.0
temp3 = 0.0
x = 0.0
y = 0.0

; Integer variables
alength = 2000
profile_no = 0
i = 0
A = 0
count = 0
max_index = 0

; String variables
szZ = ' '
szDensity = ' '
szTau_H = ' '
szLhalf = ' '
szfilename = ' '
szTitle = ' '

time = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
T = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )
Teff = MAKE_ARRAY( alength, /DOUBLE, VALUE = 0.0D )


; **** GRAPHICS ****

;!P.MULTI = 0
!P.MULTI = [0, 2, 2]
;WINDOW, 0, XSIZE=1024, YSIZE=768
SET_PLOT, 'ps'
DEVICE, FILE='fig.ps', /ENCAPSULATED, /INCHES, XSIZE=7.0, YSIZE=5.0

; ******************


PRINT
PRINT, 'Atomic number: '
READ, szZ

FOR iPanel = 0, 3 DO BEGIN

; **** PANEL ****

PRINT
PRINT, STRCOMPRESS( STRING( '**** PANEL ', iPanel+1, ' ****' ) )
PRINT

PRINT
PRINT, 'Loop half-length: '
READ, szLhalf

PRINT, 'Heating timescale: '
READ, szTau_H
PRINT

; LINE 1

i = 0

PRINT, 'Density: '
READ, szDensity

; Open the non-equilibrium ionisation balance file to get the time, temperature and
; effective ionisation temperature

szfilename = STRCOMPRESS( STRING( 'L_', szLhalf, '/Z', szZ, '_', szDensity, '_', szTau_H, '.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the values

    READF, 1, temp1, temp2, temp3
    time[i] = temp1
    T[i] = temp2
    Teff[i] = temp3

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    time[i] = time[count]
    T[i] = T[count]
    Teff[i] = Teff[count]
    
ENDFOR

; Plot the data

T = ALOG10(T)
Teff = ALOG10(Teff)

szTitle = STRCOMPRESS( STRING( 'T and T!leff!n for !7s!3!lH!n=', szTau_H, ' s' ) )
PLOT, time, T, xrange=[0.0,DOUBLE(szTau_H)], yrange=[4.0,7.0], xtitle='Time (s)', ytitle='Log!l10!n Temperature (K)', title=szTitle, xth=3, yth=3, linestyle=0, th=3, charsize=1, charth=3
OPLOT, time, Teff, linestyle=1, th=3

; LINE 2

i = 0

PRINT, 'Density: '
READ, szDensity

; Open the non-equilibrium ionisation balance file to get the time, temperature and
; effective ionisation temperature

szfilename = STRCOMPRESS( STRING( 'L_', szLhalf, '/Z', szZ, '_', szDensity, '_', szTau_H, '.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the values

    READF, 1, temp1, temp2, temp3
    time[i] = temp1
    T[i] = temp2
    Teff[i] = temp3

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    time[i] = time[count]
    T[i] = T[count]
    Teff[i] = Teff[count]
    
ENDFOR

; Plot the data

T = ALOG10(T)
Teff = ALOG10(Teff)

OPLOT, time, Teff, linestyle=2, th=3

; LINE 3

i = 0

PRINT, 'Density: '
READ, szDensity

; Open the non-equilibrium ionisation balance file to get the time, temperature and
; effective ionisation temperature

szfilename = STRCOMPRESS( STRING( 'L_', szLhalf, '/Z', szZ, '_', szDensity, '_', szTau_H, '.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the values

    READF, 1, temp1, temp2, temp3
    time[i] = temp1
    T[i] = temp2
    Teff[i] = temp3

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    time[i] = time[count]
    T[i] = T[count]
    Teff[i] = Teff[count]
    
ENDFOR

; Plot the data

T = ALOG10(T)
Teff = ALOG10(Teff)

OPLOT, time, Teff, linestyle=3, th=3

; LINE 4

i = 0

PRINT, 'Density: '
READ, szDensity

; Open the non-equilibrium ionisation balance file to get the time, temperature and
; effective ionisation temperature

szfilename = STRCOMPRESS( STRING( 'L_', szLhalf, '/Z', szZ, '_', szDensity, '_', szTau_H, '.txt' ), /REMOVE_ALL )

OPENR, 1, szfilename

i = 0

WHILE ( NOT EOF(1) ) DO BEGIN

    ; Get the values

    READF, 1, temp1, temp2, temp3
    time[i] = temp1
    T[i] = temp2
    Teff[i] = temp3

    i = i + 1

ENDWHILE

CLOSE, 1

count = i - 1

FOR i = count, alength - 1 DO BEGIN

    time[i] = time[count]
    T[i] = T[count]
    Teff[i] = Teff[count]
    
ENDFOR

; Plot the data

T = ALOG10(T)
Teff = ALOG10(Teff)

OPLOT, time, Teff, linestyle=4, th=3

; **** END OF PANEL ****

ENDFOR


; **** GRAPHICS ****

DEVICE, /CLOSE
SET_PLOT, 'win'
!P.MULTI = 0

; ******************

END
