#!/usr/bin/Rscript

print("Generating cache_lectura plot...")
png(file = "ex2/cache_lectura.png", bg = "white")
caches <- c(1024, 2048, 4096, 8192)

slow = list()
fast = list()

names_slow = list()
names_fast = list()
i = 1
for (cache in caches) {
    data=read.table(paste("ex2/ex2_data/cache_",cache,".dat", sep=""))
    N <- data[,1]
    names_slow[i] = paste(cache,"_slow",sep="")
    slow[[i]] <- data[,2]
    names_fast[i] = paste(cache,"_fast",sep="")
    fast[[i]] <- data[,4]
    i = i + 1 

}
names = c(names_slow,names_fast)
cl <- rainbow(length(caches)*2)

cls <- cl[1:length(caches)]
clf = tail(cl, length(caches))
#clf <- cl[length(caches)+1:(length(caches)*2)]

plot( slow[[1]], type = "l", col = cls[1], main="Cache read errors comparison", xlab="Size", ylab="nº Errors", xaxt='n', ylim = range(min(fast[[length(caches)]]), max(slow[[1]])))
axis(1, at=1:(length(N)), labels=N[1:length(N)], las=2)
lines(fast[[1]], type="l", col = clf[1]) 
i=2


while(i<=length(caches))
{
    lines(slow[[i]], type="l", col=cls[i]) 

    lines(fast[[i]], type="l", col=clf[i] ) 

    i = i + 1
}

# 


legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

# dev.off()



# Escritura
print("Generating cache_escritura plot...")
png(file = "ex2/cache_escritura.png", bg = "white")
caches <- c(1024, 2048, 4096, 8192)
slow = list()

fast = list()

names_slow = list()
names_fast = list()
i = 1
for (cache in caches) {
    data=read.table(paste("ex2/ex2_data/cache_",cache,".dat", sep=""))
    N <- data[,1]
    names_slow[i] = paste(cache,"_slow",sep="")
    slow[[i]] <- data[,3]
    names_fast[i] = paste(cache,"_fast",sep="")
    fast[[i]] <- data[,5]
    i = i + 1 

}

names = c(names_slow,names_fast)
cl <- rainbow(length(caches)*2)

cls <- cl[1:length(caches)]
clf = tail(cl, length(caches))
# clf <- cl[length(caches)+1:(length(caches)*2)]

plot( slow[[1]], type = "l", col = cls[1], main="Cache write errors comparison", xlab="Size", ylab="nº Errors", xaxt='n', ylim = range(min(fast[[length(caches)]]), max(slow[[1]])))
axis(1, at=1:(length(N)), labels=N[1:length(N)], las=2)
lines(fast[[1]], type="l", col = clf[1]) 
i=2
while(i<=length(caches))
{
    lines(slow[[i]], type="l", col=cls[i]) 

    lines(fast[[i]], type="l", col=clf[i] ) 

    i = i + 1
}

# 


legend("topleft", legend=names, lty=c(1,1), lwd=c(2,2), col=cl)

# dev.off()

# while (!is.null(dev.list())) Sys.sleep(1)

