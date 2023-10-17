#!/usr/bin/Rscript

# Read data
data=read.table("ex3/mult.dat")
n           <- data[,1]
t_normal    <- data[,2]
cr_normal   <- log10(data[,3])
cw_normal   <- log10(data[,4])
t_tras      <- data[,5]
cr_tras     <- log10(data[,6])
cw_tras     <- log10(data[,7])

# mult time
print("Generating mult time plot...")
png(file = "ex3/mult_time.png", bg = "white")
plot( t_normal, type = "l", col = "blue", main="Normal & Trasposed algorithm time comparison", xlab="Size", ylab="Time", xaxt='n')
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)

lines(t_tras, type="l", col = "red") 

legend("topleft", legend=c("Normal", "Trasposed"), lty=c(1,1), lwd=c(2,2), col=c("blue", "red"))





# mult cache
print("Generating mult cache plot...")
png(file = "ex3/mult_cache.png", bg = "white")

cl <- c(rgb(.6,.8,1,1),rgb(0,.4,1,1),rgb(1,.4,.4,1),rgb(.6,0,0,1))

plot( cr_normal, type = "l", col = cl[1], main="Cache read errors comparison", xlab="Size", ylab="nº Errors (log10)", xaxt='n', ylim = range(min(cw_normal), max(cr_normal))) # ylim = range(min(fast[[length(caches)]]), max(slow[[1]]))
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)
lines(cw_normal, type="l", col = cl[2]) 
lines(cr_tras, type="l", col = cl[3]) 
lines(cw_tras, type="l", col = cl[4]) 

names=c("Normal read", "Normal write", "Trasposed read","Trasposed write")
legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

# dev.off()



# while (!is.null(dev.list())) Sys.sleep(1)

