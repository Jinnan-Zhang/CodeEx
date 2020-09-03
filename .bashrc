# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines in the history. See bash(1) for more options
# ... or force ignoredups and ignorespace
HISTCONTROL=ignoredups:ignorespace

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.

shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\W\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\W\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \W\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias rm='rm -i'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias duh1='du -h --max-depth=1'
alias cdc='cd /mnt/c/Users/zjnti/OneDrive/Work/Code'
alias cdb='cd /mnt/c/Users/zjnti/OneDrive/Work/Code/Reactor/JUNO_Atm_Rea/JunoARCon/build'
alias cdO='cd "/mnt/c/Users/zjnti/OneDrive/Work/Code/Reactor/ShellScript/OutputPlots"'
alias cdT='cd "/mnt/c/Users/zjnti/OneDrive/Work/Code/Reactor/RecreateCode/PyAnalysisJuno/srcCpp"'
alias cdA='cd "/mnt/c/Users/zjnti/OneDrive/Work/Code/CNAF_Atm/Project/Py_AtmJUNO"'
export Bpath="../../JUNO_Atm_Rea/JunoARCon/build"
export DPath="../../JUNO_Atm_Rea/JunoARCon/data"


# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
#if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
#    . /etc/bash_completion
#fi

# source ~/tools/bin/thisroot.sh
alias ssrootpyhong2='source ~/SoftWare/ROOT/root_v6.20.04/bin/thisroot.sh'
# source ~/SoftWare/ROOT/root_v6.20.04_python3/bin/thisroot.sh
source /home/jinnan/SoftWare/ROOT/root_v6.22.00/bin/thisroot.sh
export DISPLAY=localhost:0.0
# export DISPLAY=172.18.144.1:0
# export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
# export LIBRARY_PATH=${LIBRARY_PATH}:${ROOTSYS}/lib
# export PYTHONPATH=${PYTHONPATH}:${ROOTSYS}/lib
# export CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}:${ROOTSYS}
# export JUPYTER_PATH=${JUPYTER_PATH}:${ROOTSYS}/etc/notebook
# export PATH=${PATH}:${ROOTSYS}/bin
#alias python='/usr/bin/python3'

#G4
#export G4SAIDXSDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4SAIDDATA1.1
#export G4LEDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4EMLOW7.3
#export G4LEVELGAMMADATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/PhotonEvaporation5.2
#export G4NEUTRONXSDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4NEUTRONXS1.4
#export G4PIIDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4PII1.3
#export G4RADIOACTIVEDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/RadioactiveDecay5.2
#export G4REALSURFACEDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/RealSurface2.1
#export G4ABLADATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4ABLA3.1
#export G4NEUTRONHPDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4NDL4.5
#export G4ENSDFSTATEDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4ENSDFSTATE2.2
#export G4TENDLDATA=/home/G4/geant4.10.05.p01/geant4.10.05.p01-data/G4TENDL1.3.2

#source /home/jinnan/geant4.10.05.p01/bin/geant4.sh

export PS1='\[\033[01;34m\]\W\[\033[01;32m\] % \[\033[00m\]'


# export CC="clang"
# export CXX="clang++"
