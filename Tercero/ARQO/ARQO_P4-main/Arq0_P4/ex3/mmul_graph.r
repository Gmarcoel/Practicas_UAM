#!/usr/bin/Rscript

# Read data
data=read.table("mmul_graph.dat")
n           <- data[,1]
t_serial    <- data[,2]
t_best      <- data[,3]


speedup  <- t_serial / t_best


# mult time
print("Generating mult time plot...")
png(file = "mmul_graph.png", bg = "white")
plot( t_serial, type = "l", col = "blue", main="Serial & Parallel matrix time comparison", xlab="Size", ylab="Time", xaxt='n',  ylim=c(0,max(t_serial)))
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)

lines(t_best, type="l", col = "violet") 

legend("topleft", legend=c("Serial", "Parallel"), lty=c(1,1), lwd=c(2,2), col=c("blue", "violet"))


print("Generating mult speedup plot...")
png(file = "mmul_graph_speedup.png", bg = "white")
plot( speedup, type = "l", col = "violet", main="Parallel/Serial speedup", xlab="Size", ylab="Speedup", xaxt='n', ylim=c(0,max(speedup)))
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)
abline(h=1, col = "blue") 

legend("topleft", legend=c("Serial/Serial Speedup", "Parallel/Serial Speedup"), lty=c(1,1), lwd=c(2,2), col=c("blue", "violet"))

# while (!is.null(dev.list())) Sys.sleep(1)
