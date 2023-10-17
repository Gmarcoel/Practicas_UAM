#!/usr/bin/Rscript

data=read.table("ex1/slow_fast_time.dat")

png(file = "ex1/slow_fast_plot.png", bg = "white")


size <- data[,1]
slow <- data[,2]
fast <- data[,3]

# plot(slow, type = "l", col = "blue",xlim = c(- 1, 5), ylim = c(0, 3))
plot( slow, type = "l", col = "blue", main="Slow & Fast algorithm comparison", xlab="Size", ylab="Time", xaxt='n')
axis(1, at=1:(length(size)), labels=size[1:length(size)], las=2)

lines(fast, type="l", col = "red") 
# plot(slow, type = "l", col = "blue", main="Slow & Fast algorithm comparison", xlab="Size", ylab="Time")
# lines(fast, type="l", col = "red") 
legend("topleft", legend=c("Slow", "Fast"), lty=c(1,1), lwd=c(2,2), col=c("blue", "red"))

# legend(1,12,legend=c("slow","fast"), col=c("blue","red"),lty=c(1,1), ncol=1)


# dev.off()

# while (!is.null(dev.list())) Sys.sleep(1)

