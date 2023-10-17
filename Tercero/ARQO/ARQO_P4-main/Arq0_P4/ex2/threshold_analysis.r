#!/usr/bin/Rscript



data1=read.table("threshold_serial.dat")
data2=read.table("threshold_parallel.dat")

png(file = "threshold_times.png", bg = "white")


size <- data1[,1]
time_serial <- data1[,2]
time_parallel <- data2[,2]

speedup  <- time_serial / time_parallel

plot( time_serial, type = "l", col = "blue", main="time_serial & time_parallel time comparison", xlab="Size (n in matrix)", ylab="Time (sec)", xaxt='n')
axis(1, at=1:(length(size)), labels=size[1:length(size)], las=2)

lines(time_parallel, type="l", col = "red") 

legend("topleft", legend=c("time serial", "time parallel"), lty=c(1,1), lwd=c(2,2), col=c("blue", "red"))


png(file = "threshold_speedup.png", bg = "white")

plot( speedup, col = ifelse(speedup>1, "green", "red"), main="Total speedup of parallel over serial", xlab="Size", ylab="Speedup", xaxt='n', ylim=c(0,max(speedup)))
abline(h=1, col = "blue") 
legend("topleft", legend=c( "Over threshold", "Below threshold", "Threshold"), lty=c(1,1), lwd=c(2,2), col=c("green", "red", "blue"))
axis(1, at=1:(length(size)), labels=size[1:length(size)], las=2)



