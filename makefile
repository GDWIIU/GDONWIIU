# MakeFile source for GDONWIIU

I="./"
C="gcc"

# Prebuild install directory
install_dir:
	mkdir _install
	mkdir _install/services
	mkdir _install/scripts
	mkdir _install/documents

# Service makes
aptpkg.c:
	$C services/aptpkg.c -o _install/services/aptpkg -i $I
gdunpack.c:
	$C services/gdunpack.c -o _install/services/gdunpack -i $I

# Inital makes
main.c:
	$C ini/main.c -o _install/main -i $I