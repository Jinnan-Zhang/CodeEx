@echo off
echo please enter mass number y/n:
set /p Nmass=
set /a massToday=Nmass+1
set FromPath=../Template/containerA/
echo "%FromPath%PMT_Ath.xlsx"
