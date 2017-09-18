#  Makefile for server
server:	servereb.c
		gcc servereb.c -o server -lev

