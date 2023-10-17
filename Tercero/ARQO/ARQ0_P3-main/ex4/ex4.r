#!/usr/bin/Rscript

print("Generating cache_lectura plot...")
png(file = "ex4/cache_lectura.png", bg = "white")
associativity <- c(1, 2, 4, 8)

normal = list()
transposed = list()

names_normal = list()
names_transposed = list()
i = 1
for (a in associativity) {
    data=read.table(paste("ex4/ex4_data/associativity_",a,".dat", sep=""))
    N <- data[,1]
    names_normal[i] = paste("associativity_", a,"_normal",sep="")
    normal[[i]] <- data[,2]
    names_transposed[i] = paste("associativity_", a,"_transposed",sep="")
    transposed[[i]] <- data[,4]
    i = i + 1 

}
names = c(names_normal, names_transposed)
cl <- rainbow(length(associativity)*2)

cls <- cl[1:length(associativity)]
clf = tail(cl, length(associativity))
#clf <- cl[length(caches)+1:(length(caches)*2)]

plot( normal[[1]], type = "l", col = cls[1], main="Cache read errors comparison", xlab="Size", ylab="nº Errors", xaxt='n', ylim = range(min(transposed[[length(associativity)]]), max(normal[[1]])))
axis(1, at=1:(length(N)), labels=N[1:length(N)], las=2)
lines(transposed[[1]], type="l", col = clf[1]) 


i=2


while(i<=length(associativity))
{
    lines(normal[[i]], type="l", col=cls[i]) 

    lines(transposed[[i]], type="l", col=clf[i] ) 

    i = i + 1
}

# 


legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

# dev.off()



# Escritura
print("Generating cache_escritura plot...")
png(file = "ex4/cache_escritura.png", bg = "white")
associativity <- c(1, 2, 4, 8)

normal = list()
transposed = list()

names_normal = list()
names_transposed = list()
i = 1
for (a in associativity) {
    data=read.table(paste("ex4/ex4_data/associativity_",a,".dat", sep=""))
    N <- data[,1]
    names_normal[i] = paste("associativity_", a,"_normal",sep="")
    normal[[i]] <- data[,3]
    names_transposed[i] = paste("associativity_", a,"_transposed",sep="")
    transposed[[i]] <- data[,5]
    i = i + 1 

}
names = c(names_normal, names_transposed)
cl <- rainbow(length(associativity)*2)

cls <- cl[1:length(associativity)]
clf = tail(cl, length(associativity))
#clf <- cl[length(caches)+1:(length(caches)*2)]

plot( normal[[1]], type = "l", col = cls[1], main="Cache write errors comparison", xlab="Size", ylab="nº Errors", xaxt='n', ylim = range(min(transposed[[length(associativity)]]), max(normal[[1]])))
axis(1, at=1:(length(N)), labels=N[1:length(N)], las=2)
lines(transposed[[1]], type="l", col = clf[1]) 


i=2


while(i<=length(associativity))
{
    lines(normal[[i]], type="l", col=cls[i]) 

    lines(transposed[[i]], type="l", col=clf[i] ) 

    i = i + 1
}

# 


legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

# dev.off()




# Experiment 2
data=read.table("ex4/exp2.dat")
n           <- data[,1]
t_normal    <- data[,2]
cr_normal   <- log10(data[,3])
cw_normal   <- log10(data[,4])
t_tras      <- data[,5]
cr_tras     <- log10(data[,6])
cw_tras     <- log10(data[,7])

# mult time
print("Generating mult time plot...")
png(file = "ex4/mult_time.png", bg = "white")
plot( t_normal, type = "l", col = "blue", main="Normal & Trasposed algorithm time comparison", xlab="Size", ylab="Time", xaxt='n', ylim= range(min(t_normal), max(t_tras)))
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)

lines(t_tras, type="l", col = "red") 

legend("topleft", legend=c("Normal", "Trasposed"), lty=c(1,1), lwd=c(2,2), col=c("blue", "red"))





# mult cache
print("Generating mult cache plot...")
png(file = "ex4/mult_cache.png", bg = "white")

cl <- c(rgb(.6,.8,1,1),rgb(0,.4,1,1),rgb(1,.4,.4,1),rgb(.6,0,0,1))

plot( cr_normal, type = "l", col = cl[1], main="Cache read errors comparison", xlab="Size", ylab="nº Errors (log10)", xaxt='n', ylim = range(min(cw_normal), max(cr_normal))) # ylim = range(min(fast[[length(caches)]]), max(slow[[1]]))
axis(1, at=1:(length(n)), labels=n[1:length(n)], las=2)
lines(cw_normal, type="l", col = cl[2]) 
lines(cr_tras, type="l", col = cl[3]) 
lines(cw_tras, type="l", col = cl[4]) 

names=c("Normal read", "Normal write", "Trasposed read","Trasposed write")
legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

