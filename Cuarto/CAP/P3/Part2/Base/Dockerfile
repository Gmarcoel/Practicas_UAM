# Base dockerfile: it should download and install Apache Spark and Hadoop in /opt

# Set base image to Ubuntu
FROM ubuntu

# Download and install Apache Spark and Hadoop
RUN apt-get update && apt-get install -y wget
RUN wget http://archive.apache.org/dist/spark/spark-3.3.1/spark-3.3.1-bin-hadoop3.tgz
RUN tar -xvzf spark-3.3.1-bin-hadoop3.tgz
RUN mv spark-3.3.1-bin-hadoop3 /opt
RUN rm spark-3.3.1-bin-hadoop3.tgz



