@echo off

if "%1"=="_chk_" shift

rem --- Konfiguracja ocen.bat ---
rem W przypadku opracowania wlasnego zestawu testow nalezy zmienic
rem zawartosc zmiennej TESTS a testy zabpiowac do kataloguw IN\, OUT\
rem nazwy testow powinny analogiczne do przykladowych

if "%1"=="cuk" goto cuk
if "%1"=="CUK" goto cuk
if "%1"=="gan" goto gan
if "%1"=="GAN" goto gan
if "%1"=="gra" goto gra
if "%1"=="GRA" goto gra
if "%1"=="lic" goto lic
if "%1"=="LIC" goto lic
if "%1"=="tab" goto tab
if "%1"=="TAB" goto tab


set T=%1
goto end

:cuk
set I=cuk
set T=0 1 2 3 4
set C=bin\cmp.exe
goto end
:gan
set I=gan
set T=0 1 2 3 4
set C=bin\cmp.exe
goto end
:gra
set I=gra
set T=0 1 2 3
set C=bin\cmp.exe
goto end
:lic
set I=lic
set T=0 1 2 3 4
set C=bin\cmp.exe
goto end
:tab
set I=tab
set T=0 1 2 3
set C=bin\cmp.exe
goto end


rem --- Koniec konfiguracji

:end

if "%C%"=="" goto def_chk
goto new_chk
:def_chk
set C=bin\cmp.exe
:new_chk

:real_end
