
#!/usr/bin/Rscript

print("Generating mult1000 time table...")
# Read data
data=read.table("mmul1000.dat")
threads <- data[,1]
serial  <- data[,2]
par1    <- data[,3]
par2    <- data[,4]
par3    <- data[,5]


data_table <- data.frame(
    threads, serial,par1,par2,par3
)
data_table <- data.frame(t(data_table))
# data_table2 <- data.frame(t(data_table))
write.table(data_table,"mmul_table1000.txt",sep="\t")

print("Generating speedup table1000...")

serial <- as.numeric(data[1, 2])
serial
threads_speedup <- data[,1]
serial_speedup  <- as.numeric(data[,2]) / serial
par1_speedup    <- as.numeric(data[,3]) / serial
par2_speedup    <- as.numeric(data[,4]) / serial
par3_speedup    <- as.numeric(data[,5]) / serial
data_table_speedup <- data.frame(
    threads_speedup, serial_speedup,par1_speedup,par2_speedup,par3_speedup
)
data_table_speedup <- data.frame(t(data_table_speedup))
write.table(data_table_speedup,"mmul_table1000_speedup.txt",sep="\t")
print("Generating mult2000 time table...")
# Read data
data=read.table("mmul2000.dat")
threads <- data[,1]
serial  <- data[,2]
par1    <- data[,3]
par2    <- data[,4]
par3    <- data[,5]


data_table <- data.frame(
    threads, serial,par1,par2,par3
)
data_table <- data.frame(t(data_table))
# data_table2 <- data.frame(t(data_table))
write.table(data_table,"mmul_table2000.txt",sep="\t")

print("Generating speedup table2000..")

serial <- as.numeric(data[1, 2])
serial
threads_speedup <- data[,1]
serial_speedup  <- as.numeric(data[,2]) / serial
par1_speedup    <- as.numeric(data[,3]) / serial
par2_speedup    <- as.numeric(data[,4]) / serial
par3_speedup    <- as.numeric(data[,5]) / serial
data_table_speedup <- data.frame(
    threads_speedup, serial_speedup,par1_speedup,par2_speedup,par3_speedup
)
data_table_speedup <- data.frame(t(data_table_speedup))
write.table(data_table_speedup,"mmul_table2000_speedup.txt",sep="\t")
