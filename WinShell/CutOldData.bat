REM @echo off
cd D:\
set Target=D:\previous measurements1\mass%1
for /d %%a in (gain_Iteration*,DCR,PDE_setpoint_3000,PDE_*_PE,Afterpulses,Meassurements,TTS) do move /-y %%a Target
move /-Y PMT_Input.txt Target

pause