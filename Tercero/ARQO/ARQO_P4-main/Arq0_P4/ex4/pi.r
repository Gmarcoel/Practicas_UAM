
#!/usr/bin/Rscript

print("Generating pi table...")
# Read data
data=read.table("pi.dat")
serial <- as.numeric(data[1,1])
times <- data[1,]
speedup <- serial / as.numeric(data[1,])



data_table <- data.frame(
    t(times), speedup
)

# data_table <- data.frame(t(data_table))
# data_table2 <- data.frame(t(data_table))
write.table(data_table,"pi.txt",sep="\t", col.names=FALSE, row.names=FALSE)

