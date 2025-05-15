# MakeFile source for GDONWIIU

I="./"
C="gcc"

# Prebuild install directory
builds:
	mkdir _install
	mkdir _install/services
	mkdir _install/scripts
	mkdir _install/documents
	cp -r ./logs _install/logs

# Service makes

	$C services/aptpkg.c -o _install/services/aptpkg -I $I
	$C services/gdunpack.c -o _install/services/gdunpack -I $I

# Inital makes

	$C ini/main.c -o _install/main -I $I