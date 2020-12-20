#!/bin/bash

source ~/.bashrc

export SHELL=bash
export EDITOR=nvim
export FILE_MANAGER=lf

export PAGER=w3m
export TERMINAL_BROWSER=w3m
export DOWNLOADER=aria2c
export MUSIC_PLAYER=cmus

export MEDIA_PLAYER=mpv
export IMAGE_VIEWER=sxiv
export DOCUMENT_VIEWER=zathura

export MENU=dmenu
export TERMINAL=st
export BROWSER=chromium

export GOPATH=~/.go

#export LS_COLORS="di=1;32:ex=1;33"

if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

if [ -d "$HOME/.local/bin" ] ; then
    PATH="$HOME/.local/bin:$PATH"
fi

if [ -d "$GOPATH/bin" ] ; then
    PATH="$GOPATH/bin:$PATH"
fi

# autostart x
if [ -f ~/.xinitrc ] && systemctl -q is-active graphical.target && [[ ! $DISPLAY && $XDG_VTNR -eq 1 ]] && [ -z $TMUX ]; then
    exec startx
fi

