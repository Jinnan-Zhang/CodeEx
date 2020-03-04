@echo off
REM author:zhangjinnan@ihep.ac.cn
cd D:\
echo please enter mass number y/n:
set /p Nmass=
set Target=D:\previous measurements1\mass%Nmass%
for /d %%a in (gain_Iteration*,DCR,PDE_setpoint_3000,PDE_*_PE,Afterpulses,Meassurements,TTS) do move /-y %%a "%Target%"
move /-Y PMT_Input.txt "%Target%"

pause