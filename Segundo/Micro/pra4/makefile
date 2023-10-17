all: Lab4a.com Lab4b.com Snake.com

Lab4a.com: Lab4a.obj
	tlink /v /t Lab4a.obj
	
Lab4b.com: Lab4b.obj
	tlink /v /t Lab4b.obj	

Snake.com: Snake.obj
	tlink /v /t Snake.obj	


Lab4a.obj: Lab4a.asm Lab4b.asm
	tasm /zi Lab4a.asm
	
Lab4b.obj: Lab4b.asm
	tasm /zi Lab4b.asm
	
Snake.obj: Snake.asm
	tasm /zi Snake.asm